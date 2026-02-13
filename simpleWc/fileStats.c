#include "fileStats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int simplewc_str(const char *str, fileStats *stats) {
    if (!str || !stats) return -1;
    stats->bytes += strlen(str);
    int in_word = 0;
    for (const unsigned char *p = (const unsigned char *)str; *p; ++p) {
        if (*p == '\n') stats->lines++;
        if (isspace(*p)) {
            in_word = 0;
        } else if (!in_word) {
            stats->words++;
            in_word = 1;
        }
    }
    return 0;
}

int simplewc_file(const char *filename, fileStats *stats)
{
    if (filename == NULL || stats == NULL) {
        errno = EINVAL;
        return -1;
    }

    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        return -1;
    }

    char *line = NULL;
    size_t cap = 0;
    int retval = 0;

    while (1) {
        errno = 0;
        ssize_t nread = getline(&line, &cap, f);
        if (nread < 0) {
            if (feof(f)) {
                /* normal end of file */
                break;
            }
            /* read error */
            retval = -1;
            break;
        }

        /* update stats based on the line contents */
        if (simplewc_str(line, stats) != 0) {
            retval = -1;
            break;
        }
    }

    free(line);

    int saved_errno = errno;

    if (fclose(f) != 0) {

        if (retval == 0) {
            retval = -1;
            saved_errno = errno;
        }
    }

    if (retval == 0) {
        printf("%ld %ld %ld %s\n", stats->lines, stats->words, stats->bytes, filename);
    }
    if (retval != 0) {
        errno = saved_errno;
    }
    return retval;
}

int simplewc(const char **fileNames, int filesCount)
{
    if (filesCount <= 0 || fileNames == NULL) {
        return 1;
    }
    fileStats total = {0, 0, 0};
    for (int i = 0; i < filesCount; i++) {
        fileStats s = {0, 0, 0};
        int rc = simplewc_file(fileNames[i], &s);
        if (rc != 0) {
            /* propagate errno to caller; simplewc_file already set errno */
            return rc;
        }
        /* accumulate totals */
        total.lines += s.lines;
        total.words += s.words;
        total.bytes += s.bytes;
    }
    if (filesCount > 1) {
        printf("%ld %ld %ld total\n", total.lines, total.words, total.bytes);
    }
    return 0;
}