#ifndef SHMEM_H
#define SHMEM_H

#define NSHMEM   16       // max shared memory segments
#define SHMEM_MAXSIZE (16 * 4096)  // max 16 pages per segment

struct shmem_entry {
  int    key;        // user-defined key (0 = unused)
  int    refcount;   // number of processes attached
  char  *phys;       // physical page(s) allocated
  uint64 size;       // size in bytes (rounded up to page)
};

void shmeminit(void);

// kernel-internal helpers used by sysproc
int    shmem_get(int key, uint64 size);
uint64 shmem_at(int id, pagetable_t pt, uint64 sz);
int    shmem_dt(int id, pagetable_t pt, uint64 va);

#endif
