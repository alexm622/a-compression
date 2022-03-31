#include "compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

processed_t *Compression::compressed(raw_t *data) { 
    raw_t* return_value = (raw_t*) malloc(sizeof(raw_t));
    char* buffer = (char*) malloc(sizeof(char) * 16); //16 bits or 2 char
    bool done = false;
    int buf_offset = 0;
    while (!done) {
        
        if (buf_offset == -1) {
            done = true;
        }
    }

    return {};
}

char* Compression::toBin(char *chars) {
    int i;
    int n = 0;
    char* out = (char*) malloc(sizeof(char) * 16);
    n = chars[0];
    n = (n << 8) | chars[1];
    printf("n: %d", n); 
    for (i = 0; n > 0; i++) {
        out[i] = n%2;
        n /= 2;
    }
    return out;
}
