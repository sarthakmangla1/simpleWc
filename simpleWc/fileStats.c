#include "fileStats.h"
#include <string.h>

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


int simplewc_file(const char* filename, fileStats* stats){
    File *file =NULL;
    file = open file(filename)

    return 0;
};



int simplewc(const char** fileNames, int filesCount){
    
    return 0;
};

