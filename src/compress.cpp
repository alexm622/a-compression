#include "compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define START true
#define END false

#define ONE true
#define ZERO false


processed_t *Compression::compressed(raw_t *data) { 
    processed_t_t* return_value = (processed_t*) malloc(sizeof(processed_t_t));
    
    uint8_t* buffer = (uint8_t*) malloc(sizeof(uint8_t) * 16); //16 bits or 2 char

    bool ooz = false;

    if ((data->data[0] & 0b10000000) == 0b10000000) {
        ooz = ONE;
    }

    int buf_offset = 0;
    bool start_or_end = END
    uint8_t curr;
    while (true) {
        //write to buffer
        for (int i = 0; i < 16; i++) {
          buffer[i] = data->data[buf_offset + i];
        }
        if (buffer[0] == ooz) {
            //enter a value of 0 for run length
            curr = curr & 0x0f;
            start_or_end = !start_or_end;
            
        }

        uint8_t comp = compress(toBin(buffer), 16);
        start_or_end = !start_or_end;
        ooz = !ooz;
        if (start_or_end == START) {
            curr = (comp & 0x0f) << 4;
        } else {
            curr = (comp & 0x0f);
            write_data(return_value,curr);
        }
        buf_offset += comp & 0xf0 >> 4;
        if (data->length - buf_offset < 16) {
            break;
        }
    }
    if(data->length - buf_offset != 0){

    //cleanup/ending stuff
    while (true) {
        buffer = (uint8_t*) realloc(buffer, sizeof(uint8_t) * data->length - buf_offset);
    }
    } else {
        free(buffer);
    }

    return {};
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
