#ifndef FILESTATS_H // Guard against multiple inclusion by the compiler
#define FILESTATS_H

typedef struct fileStats fileStats;

struct fileStats{
    long lines;
    long words;
    long bytes;
};

int simplewc_str(const char* str, fileStats* stats);

int simplewc_file(const char* filename, fileStats* stats);

int simplewc(const char** fileNames, int filesCount);

#endif
