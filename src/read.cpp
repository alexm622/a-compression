#include <read.hpp>

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <memory.h>

std::optional<raw_t*> Read::read(char* fname){
    //test for file
    if (!access("fname", F_OK)) {
      return {};
    }
    raw_t* data = (raw_t*) malloc(sizeof(raw_t));

    data->length = 0;
    std::ifstream file;
    file.open(fname, std::ios::binary | std::ios::in);
    if (file) {
        file.seekg(0, file.end);
        int len =   file.tellg();
        file.seekg(0, file.beg);
        data->data = (uint8_t*) malloc(sizeof(uint8_t) * (len + 1));
        printf("reading %i characters\n", len);
        char* buffer = (char*) malloc(sizeof(char) * (len));
        file.read(buffer, len);

        for (int i = 0; i < len; i++) {
            data->data[i] = (uint8_t) buffer[i];
        }

        if (file) {
            printf("all data read successfully\n");
        } else {
            printf("operation failed\n");
            printf("going to try to read anyways\n");
            printf("%s", data->data);
            free(data->data);
            free(data);
            return {};
        }
    } else {
        free(data);
        return {};
    }
    file.close();
    printf("data:\n%s", data->data);
    return std::optional<raw_t*>{data};
}
