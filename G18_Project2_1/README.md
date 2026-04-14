# G18 Project 2: UNIX-like Mini Shell and Utilities

## 1. Project Overview

This project implements a lightweight UNIX-like shell and a set of custom file/text utilities in C.

The shell prompt is:

`g18-shell>`

Each command runs as an external executable from the `bin/` directory.

## 2. Objectives

1. Build a working shell that accepts user commands and executes utilities.
2. Implement common UNIX-style commands from scratch in C.
3. Keep the build process simple and reproducible using `make`.
4. Maintain a clean source layout for team development.

## 3. Project Structure

```text
G18_Project2_1/
├── Makefile
├── README.md
├── include/
│   └── common.h
├── src/
│   ├── shell/
│   │   └── main_shell.c
│   └── utils/
│       ├── g18_cat.c
│       ├── g18_cp.c
│       ├── g18_grep.c
│       ├── g18_ls.c
│       ├── g18_mkdir.c
│       ├── g18_mv.c
│       ├── g18_rm.c
│       ├── g18_touch.c
│       └── g18_wc.c
├── bin/                 # Generated binaries
└── tests/
```

## 4. Build and Run

### Build all binaries

```bash
make
```

### Run shell

```bash
./bin/g18-shell
```

### Clean build outputs

```bash
make clean
```

Notes:
1. `make` auto-compiles every `.c` file inside `src/utils/` into `bin/`.
2. If old binaries are present, run `make clean` before rebuilding.

## 5. Shell Design

File: `src/shell/main_shell.c`

Features:
1. Shows prompt `g18-shell>`.
2. Reads one command line from `stdin`.
3. Splits command and arguments by spaces.
4. Supports built-in `exit`.
5. Uses `fork()` + `execv()` to run utilities from `./bin/<command>`.
6. Parent process waits for child completion using `wait()`.

## 6. Implemented Utilities

All utilities are implemented and available in `src/utils/`.

### 6.1 g18_ls

File: `src/utils/g18_ls.c`

Purpose:
List directory contents.

Usage:
```bash
g18_ls [-a] [-l] [directory]
```

Supported options:
1. `-a`: include hidden files.
2. `-l`: long listing format.

Implementation highlights:
1. Uses `scandir()` with `alphasort` for ordered output.
2. Uses `lstat()` for metadata in long mode.
3. Shows colored directory names.

### g18_ls Screenshot

![g18_ls output screenshot](images/g18_ls_output.png)

### 6.2 g18_cat

File: `src/utils/g18_cat.c`

Purpose:
Display file content, optionally with line numbers.

Usage:
```bash
g18_cat [-n] [file...]
```

Supported options:
1. `-n`: print line numbers.

Implementation highlights:
1. Reads from `stdin` if no file is provided.
2. Uses buffered reads and writes for normal mode.
3. Uses line-based reading for numbered output.

### 6.3 g18_wc

File: `src/utils/g18_wc.c`

Purpose:
Count lines, words, and characters.

Usage:
```bash
g18_wc [-l] [-w] [-c] <file>
```

Supported options:
1. `-l`: show line count only.
2. `-w`: show word count only.
3. `-c`: show character count only.

Implementation highlights:
1. If no flag is given, prints all three counts.
2. Uses simple whitespace boundary logic for words.

### 6.4 g18_touch

File: `src/utils/g18_touch.c`

Purpose:
Create empty files if missing and update timestamps.

Usage:
```bash
g18_touch <file...>
```

Implementation highlights:
1. Uses `open(..., O_CREAT, 0666)` to create file.
2. Uses `utime(..., NULL)` to update access/modification times.

### 6.5 g18_cp

File: `src/utils/g18_cp.c`

Purpose:
Copy source file to destination file.

Usage:
```bash
g18_cp <source_file> <destination_file>
```

Implementation highlights:
1. Opens source in read mode and destination in write mode.
2. Copies data byte by byte using `fgetc()` and `fputc()`.

### g18_cp screenshot

![g18_cp output screenshot](images/g18_cp_output.jpeg)

### 6.6 g18_mv

File: `src/utils/g18_mv.c`

Purpose:
Move or rename a file.

Usage:
```bash
g18_mv <source> <destination>
```

Implementation highlights:
1. Uses `rename()` for move/rename operation.

### 6.7 g18_rm

File: `src/utils/g18_rm.c`

Purpose:
Remove files and directories.

Usage:
```bash
g18_rm [-r] <path...>
```

Supported options:
1. `-r`: allow directory removal via `rmdir()`.

Implementation highlights:
1. Tries `unlink()` first.
2. If `-r` is set, attempts `rmdir()` for directory paths.

### 6.8 g18_mkdir

File: `src/utils/g18_mkdir.c`

Purpose:
Create one or more directories.

Usage:
```bash
g18_mkdir [-p] <directory...>
```

Supported options:
1. `-p`: create parent directories as needed.

Implementation highlights:
1. Normal mode uses `mkdir(path, 0777)`.
2. `-p` mode creates intermediate directories safely.

### g18_mkdir screenshot

![g18_mkdir output screenshot](images/g18_mkdir_output.png)

### 6.9 g18_grep

File: `src/utils/g18_grep.c`

Purpose:
Search for a pattern in one or more files.

Usage:
```bash
g18_grep [-i] [-n] [-c] [-v] <pattern> <file...>
```

Supported options:
1. `-i`: case-insensitive search.
2. `-n`: print line numbers.
3. `-c`: print match count only.
4. `-v`: invert match.

Implementation highlights:
1. Supports single-file and multi-file output formatting.
2. Returns exit code `0` if at least one match is found, otherwise `1`.

## 7. Example Session

```bash
$ make
$ ./bin/g18-shell
g18-shell> g18_mkdir demo
g18-shell> g18_touch demo/a.txt
g18-shell> g18_ls -l demo
g18-shell> g18_cp demo/a.txt demo/b.txt
g18-shell> g18_wc demo/b.txt
g18-shell> g18_grep -n hello demo/b.txt
g18-shell> exit
```

## 8. Error Handling Approach

1. Invalid usage prints a usage message.
2. File and directory failures report system errors (`perror` or equivalent messages).
3. Shell prints a clear message if command is not found in `./bin/`.

## 9. Team Development Workflow

1. Add new utility in `src/utils/` using naming pattern `g18_<name>.c`.
2. Rebuild with `make`.
3. Test directly (`./bin/<utility> ...`) and through shell (`./bin/g18-shell`).
4. Commit only source/docs changes; avoid committing generated binaries.

## 10. Deliverables Checklist

1. Source code for shell and all listed utilities.
2. Working `Makefile` for build and clean.
3. Updated `README.md` with build, usage, and implementation details.
4. Execution screenshots (add below if required by submission format).

## 11. Screenshot Section

Add screenshots of:
1. `make` build output.
2. Shell startup (`g18-shell>` prompt).
3. Execution of each utility command.