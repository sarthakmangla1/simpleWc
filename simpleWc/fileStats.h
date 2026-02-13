#ifndef FILESTATS_H // Guards for preventing the file to be included multiple times by th comiler as used in several files
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
