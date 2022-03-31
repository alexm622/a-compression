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
    std::string line;
    raw_t* data = (raw_t*) malloc(sizeof(raw_t));

    data->length = 0;
    std::ifstream file;
    file.open(fname, std::ios::binary | std::ios::in);
    if (file) {
        file.seekg(0, file.end);
        int len =   file.tellg();
        file.seekg(0, file.beg);
        data->data = (char*) malloc(sizeof(char) * (len + 1));
        printf("reading %i characters\n", len);
        file.read(data->data, len);
        data->length = len;

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
