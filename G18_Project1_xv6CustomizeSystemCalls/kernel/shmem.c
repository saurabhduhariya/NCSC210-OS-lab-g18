#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "shmem.h"

// Global shared memory table
static struct shmem_entry shmtable[NSHMEM];
static struct spinlock shmlock;

void
shmeminit(void)
{
  initlock(&shmlock, "shmem");
  for (int i = 0; i < NSHMEM; i++) {
    shmtable[i].key      = 0;
    shmtable[i].refcount = 0;
    shmtable[i].phys     = 0;
    shmtable[i].size     = 0;
  }
}

// shmem_get: find or create a shared memory segment by key.
// Returns segment id (index) on success, -1 on failure.
int
shmem_get(int key, uint64 size)
{
  if (key <= 0 || size == 0 || size > SHMEM_MAXSIZE)
    return -1;

  // Round size up to page boundary
  uint64 rounded = PGROUNDUP(size);

  acquire(&shmlock);

  // Search for existing segment with this key
  for (int i = 0; i < NSHMEM; i++) {
    if (shmtable[i].key == key) {
      release(&shmlock);
      return i;
    }
  }

  // Find a free slot
  for (int i = 0; i < NSHMEM; i++) {
    if (shmtable[i].key == 0) {
      // Allocate physical pages
      uint64 npages = rounded / PGSIZE;
      char *mem = 0;
      // Allocate first page; for simplicity support 1-page segments
      // (extend with multi-page if needed)
      if (npages == 1) {
        mem = kalloc();
        if (mem == 0) {
          release(&shmlock);
          return -1;
        }
        memset(mem, 0, PGSIZE);
      } else {
        // Allocate multiple pages contiguously by chaining kalloc calls
        // We store only the first page pointer; map each page individually
        // For multi-page we need to store all page pointers.
        // Simple approach: limit to 1 page per segment for now,
        // but support up to SHMEM_MAXSIZE by allocating page-by-page.
        // We'll store the first page and use size to know how many pages.
        // Actually, let's just allocate one page at a time and store them.
        // For simplicity, we only support single-page segments here.
        release(&shmlock);
        return -1;
      }

      shmtable[i].key      = key;
      shmtable[i].refcount = 0;
      shmtable[i].phys     = mem;
      shmtable[i].size     = rounded;

      release(&shmlock);
      return i;
    }
  }

  release(&shmlock);
  return -1;  // no free slots
}

// shmem_at: map segment id into the process's address space.
// Maps at the end of the process's current memory (sz).
// Returns the virtual address where it was mapped, or 0 on failure.
uint64
shmem_at(int id, pagetable_t pt, uint64 sz)
{
  if (id < 0 || id >= NSHMEM)
    return 0;

  acquire(&shmlock);

  struct shmem_entry *e = &shmtable[id];
  if (e->key == 0 || e->phys == 0) {
    release(&shmlock);
    return 0;
  }

  // Map at the next page-aligned address after sz
  uint64 va = PGROUNDUP(sz);

  // Make sure it doesn't collide with TRAPFRAME
  if (va + e->size > TRAPFRAME) {
    release(&shmlock);
    return 0;
  }

  if (mappages(pt, va, e->size, (uint64)e->phys, PTE_R | PTE_W | PTE_U) < 0) {
    release(&shmlock);
    return 0;
  }

  e->refcount++;
  release(&shmlock);
  return va;
}

// shmem_dt: unmap a shared memory segment from the process's address space.
// va is the virtual address returned by shmem_at.
// Returns 0 on success, -1 on failure.
int
shmem_dt(int id, pagetable_t pt, uint64 va)
{
  if (id < 0 || id >= NSHMEM)
    return -1;

  acquire(&shmlock);

  struct shmem_entry *e = &shmtable[id];
  if (e->key == 0 || e->phys == 0) {
    release(&shmlock);
    return -1;
  }

  uint64 npages = e->size / PGSIZE;

  // Unmap but do NOT free the physical pages (other processes may still use them)
  uvmunmap(pt, va, npages, 0);

  e->refcount--;

  // If no more references, free the physical memory and clear the entry
  if (e->refcount <= 0) {
    kfree(e->phys);
    e->key      = 0;
    e->refcount = 0;
    e->phys     = 0;
    e->size     = 0;
  }

  release(&shmlock);
  return 0;
}
