#ifndef COMPRESS_H
#define COMPRESS_H

typedef struct {
    char* data;
    long long int length;
}raw_t;

typedef struct {
    char** data;
    long long int length;
}processed_t;

#endif
