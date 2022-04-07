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
  static uint8_t* toBinByte(const uint8_t byte);
  static processed_t *compressed(raw_t *data);
private:
  static uint8_t compress(const uint8_t* buffer, uint8_t constraint);
  static void write_data(processed_t* data, const uint8_t byte);
};

#endif
