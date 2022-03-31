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
  static char *toBin(char *chars);
  static processed_t *compressed(raw_t *data);

private:
};

#endif
