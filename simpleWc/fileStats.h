#ifndef FILESTATS_H
#define FILESTATS_H

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <assert.h>


typedef struct fileStats fileStats;
struct fileStats{
    long lines;
    long words;
    long bytes;
};
int simplewc_str(const char* str, fileStats* stats);

int simplewc_file(const char* filename, fileStats* stats);

int simplewc(const char** fileNames, int filesCount);

#endif // FILESTATS_H
