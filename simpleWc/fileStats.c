#include "fileStats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int simplewc_str(const char* str, fileStats* stats){

    if( str == NULL || stats == NULL)
        return -1;

    stats->bytes+= (long)strlen(str); // returns an int

    int in_word = 0;

    for (const unsigned char* p = &str; *p != '\0'; ++p) {
        if (*p == '\n') {
            stats->lines += 1;
        }

        if (isspace(*p)) {
            in_word = 0;
        } else {
            if (!in_word) {
                stats->words += 1;
                in_word = 1;
            }
        }
    }

    return 0;

};


/*
 * Reads file line-by-line (getline) and calls simplewc_str() to update stats.
 * Prints: "<lines> <words> <bytes> <filename>\n"
 *
 * Returns 0 on success, -1 on error (errno set).
 */
int simplewc_file(const char* filename, fileStats* stats) {
    if (filename == NULL || stats == NULL) {
        errno = EINVAL;
        return -1;
    }

    FILE* f = fopen(filename, "rb");
    if (!f) {
        // errno set by fopen (e.g. ENOENT)
        return -1;
    }

    char* line = NULL;
    size_t cap = 0;

    while (1) {
        errno = 0;
        ssize_t nread = getline(&line, &cap, f);
        if (nread < 0) {
            if (feof(f)) break;   // normal EOF
            // read error
            int saved = errno ? errno : EIO;
            free(line);
            fclose(f);
            errno = saved;
            return -1;
        }

        // getline returns a NUL-terminated buffer; safe for strlen/scan.
        if (simplewc_str(line, stats) != 0) {
            int saved = errno;
            free(line);
            fclose(f);
            errno = saved;
            return -1;
        }
    }

    free(line);

    if (fclose(f) != 0) {
        // errno set by fclose
        return -1;
    }

    printf("%ld %ld %ld %s\n", stats->lines, stats->words, stats->bytes, filename);
    return 0;
}

int simplewc(const char** fileNames, int filesCount){
    
    return 0;
};

