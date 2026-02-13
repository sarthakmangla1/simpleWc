/*
 * main.c
 *
 * Entry point for the simplewc program.  This program performs a
 * minimal emulation of the UNIX `wc` command.  It also runs a set of
 * unit tests defined in tests/wcStrUnits.c and tests/wcFileUnits.c to
 * verify correctness before processing any files supplied on the
 * command line.  To see usage information run with `-h` or without
 * any file arguments.
 */

#include "fileStats.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

/* Forward declarations of unit test runners defined in the tests */
void run_wcStrTests(void);
void run_wcFileTests(void);

/*
 * print_usage
 *
 * Display a brief usage message on stdout.  This function does not
 * exit so that the caller can choose an appropriate exit code.
 */
static void print_usage(const char *progname) {
    printf("Usage: %s [file ...]\n", progname);
    printf("Counts lines, words and bytes in each listed file and prints the result.\n");
    printf("When multiple files are provided, a final \"total\" line is printed.\n");
    printf("Options:\n");
    printf("  -h, --help   Display this help message\n");
}

int main(int argc, char **argv) {
    /* Run unit tests first.  They will abort the program via assert
     * if a failure is encountered.  If you wish to skip tests in
     * production builds, guard these calls behind a compile‑time
     * macro such as NDEBUG.
     */
    run_wcStrTests();
    run_wcFileTests();

    /* After tests, process command‑line arguments. */
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }
    /* Handle help options */
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
       // print_usage(argv[0]);
        return 0;
    }
    /* There is at least one file argument; call simplewc */
    const char **files = (const char **)&argv[1];
    int filesCount = argc - 1;
    int rc = simplewc(files, filesCount);
    if (rc != 0) {
        /* On error print a message to stderr using perror */
        perror("simplewc");
        return 1;
    }
    return 0;
}
