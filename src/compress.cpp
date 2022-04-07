#include "compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define START true
#define END false

#define ONE true
#define ZERO false


processed_t *Compression::compressed(raw_t *data) { 
    processed_t* return_value = (processed_t*) malloc(sizeof(processed_t));
    
    uint8_t* binary;

    bool ooz = false;

    if ((data->data[0] & 0b10000000) == 0b10000000) {
        ooz = ONE;
    }

    int buf_offset = 0; // 
    uint8_t comp_count = 0; // the number of bytes already compressed
    return_value->length = 0;
    return_value->data = (uint8_t*) malloc(sizeof(uint8_t));

    if (ooz == ZERO) {
        return_value->data[0] = 0;
        return_value->length++;
    }
    uint8_t* buffer = (uint8_t*) malloc(sizeof(uint8_t) * 2);
    buffer[0] = data->data[buf_offset];
    buffer[1] = data->data[buf_offset+ 1];
    binary = toBin(buffer);
    buf_offset += 2;
    uint8_t bit_offset = 0;


    while (true) {
        uint8_t* bin_buf;
        printf("binary: ");
        for (int i = 0; i < 16; i++) {
          printf("%c", binary[i]);
        }
                buf_offset += 2;
        uint8_t comp = compress(binary, 16);
        printf("\ncompressed: %d\n", comp);
        uint8_t count = comp >> 4;
        printf("count: %d", count);

        //ditch count bits from binary
        for (int i = count; i < 16; i++) {
            binary[i-count]=binary[i];
        }
        return_value->data = (uint8_t*) realloc(return_value->data, return_value->length + 1);
        return_value->data[return_value->length] = comp;
        return_value->length++;
        
        bit_offset += count;
        while(bit_offset >= 8) {
            bit_offset -= 8;
            comp_count++;
        }


        break;
    }
    return return_value;
}

uint8_t* Compression::toBin(const uint8_t *bytes) {
    int i;
    int n = 0;
    uint8_t* out = (uint8_t*) malloc(sizeof(uint8_t) * 16);
    n = bytes[0];
    n = (n << 8) | bytes[1];
    printf("n: %d\n", n); 
    for (i = 15; i >= 0; i--) {
        out[i] = (n%2 == 1)? '1' : '0';
        n /= 2;
    }
    return out;
}

uint8_t* Compression::toBinByte(const uint8_t byte) {
    int i;
    int n = 0;
    uint8_t* out = (uint8_t*) malloc(sizeof(uint8_t) * 8);
    n = byte;
    printf("n: %d\n", n); 
    for (i = 7; i >= 0; i--) {
        out[i] = (n%2 == 1)? '1' : '0';
        n /= 2;
    }
    return out;

}

uint8_t Compression::compress(const uint8_t *buffer, uint8_t constraint) {
    uint8_t compressed=1;
    uint8_t offset;

    for (offset = 1; offset < constraint; offset++) {
      if (buffer[offset] == buffer[0]) {
          compressed++;
      } else {
          break;
      }
    }
    return compressed | (offset << 4);
}

void Compression::write_data(processed_t *data, const uint8_t byte) {
    data->data = (uint8_t*) realloc(data->data, data->length + 1);
    data->data[data->length] = byte;
    data->length++;
}
