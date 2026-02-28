# simpleWc

A minimal clone of the Unix `wc` utility. Counts lines, words, and bytes for one or more files.

```
$ ./simplewc main.c fileStats.c
  38   95  893 main.c
  88  264 2131 fileStats.c
 126  359 3024 total
```

---

## Build

```sh
make          # build ./simplewc
make test     # run unit tests
make fuzz     # run functional + fuzz tests against system wc
make clean    # remove binaries
```

Requires gcc and a POSIX-2008 environment (Linux, macOS).

---

## Usage

```sh
./simplewc file [file ...]
./simplewc -h
```

Exits 0 on success, 1 if any file could not be read. Errors go to stderr; results go to stdout.

---

## Structure

```
simpleWc/
├── fileStats.h          public API and fileStats struct
├── fileStats.c          all counting logic
├── main.c               CLI entry point
├── tests/
│   ├── wcStrUnits.c     unit tests for simplewc_str()
│   └── wcFileUnits.c    unit tests for simplewc_file()
├── fuzzTest.sh          functional comparison against system wc + fuzz
└── Makefile
```

### Layers

The implementation is split into three layers, each depending only on the one below.

```
main()            parse args, dispatch
simplewc()        iterate files, print results, accumulate total
simplewc_file()   open a file, read lines, delegate to simplewc_str()
simplewc_str()    count lines/words/bytes in a string
```

**`simplewc_str(const char *str, fileStats *stats)`**
Pure computation. Walks the string once, counting `\n` for lines and whitespace transitions for words. Adds into `stats` (does not reset it), so it is composable — callers accumulate across multiple calls.

**`simplewc_file(const char *filename, fileStats *stats)`**
Opens the file in binary mode (`"rb"`) for accurate byte counts. Uses `getline()` with a self-managed buffer so lines of any length are handled without overflow. Distinguishes EOF from read errors via `feof()`. Accumulates into the caller-supplied `stats`.

**`simplewc(const char **fileNames, int filesCount)`**
Iterates over all files. On error, prints a per-file message to stderr and continues — remaining files are still processed. Prints the `total` line only when more than one file is given.

**`main()`**
Handles `-h`/`--help` and passes the file list directly to `simplewc()`. Contains no logic of its own.

### `fileStats` struct

```c
struct fileStats {
    long lines;
    long words;
    long bytes;
};
```

`long` is used (not `int`) to safely hold byte counts for large files on 64-bit systems.

---

## Testing

Unit tests live in `tests/` and use `assert()`. They are compiled into a separate binary only when `make test` is run (`-DRUN_TESTS`). The production binary contains no test code.

`fuzzTest.sh` creates a set of known files, runs `simplewc` and system `wc` on each, and compares the output. It then runs 50 random binary files through the program to check for crashes.

---

## Known limitations

- No stdin support (`wc` with no arguments reads stdin; this prints usage).
- Word counting uses `isspace()` — ASCII/C-locale only, not Unicode-aware.
- Files with no trailing newline report 0 lines (same as most `wc` implementations).
