#include "fileStats.h"

#include <stdio.h>
#include <string.h>

#ifdef RUN_TESTS
void run_wcStrTests(void);
void run_wcFileTests(void);
#endif

static void print_usage(const char *progname) {
    printf("Usage: %s [file ...]\n", progname);
    printf("Counts lines, words and bytes in each listed file and prints the result.\n");
    printf("When multiple files are provided, a final \"total\" line is printed.\n");
    printf("Options:\n");
    printf("  -h, --help   Display this help message\n");
}

int main(int argc, char **argv) {
#ifdef RUN_TESTS
    run_wcStrTests();
    run_wcFileTests();
#endif
    /* Process command‑line arguments. */
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }
    /* Handle help options */
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return 0;
    }
    /* There is at least one file argument; call simplewc */
    const char **files = (const char **)&argv[1];
    int filesCount = argc - 1;
    return simplewc(files, filesCount);
}
