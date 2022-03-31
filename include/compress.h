#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdint.h>

typedef struct {
    uint8_t* data;
    long long int length;
}raw_t;

typedef struct {
    uint8_t* data;
    long long int length;
}processed_t;

class Compression {
public:
  static uint8_t *toBin(const uint8_t *bytes);
  static processed_t *compressed(raw_t *data, uint8_t constraint);
private:
  static uint8_t compress(const uint8_t* buffer);
  static void write_data(processed_t* data, const uint8_t byte);
};

#endif
