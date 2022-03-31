#ifndef COMPRESS_H
#define COMPRESS_H

typedef struct {
    char* data;
    long long int length;
}raw_t;

typedef struct {
    char* data;
    long long int length;
}processed_t;

class Compression {
    public:
        static processed_t* compressed(raw_t* data);
    private:
        private char* toBin(char* chars);
};

#endif
