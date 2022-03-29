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
    std::ifstream file (fname);
    if (file.is_open()) {
      while (std::getline(file, line)) {
          //add to the data format.
          int len = line.length();
          data->data = (char *) malloc(sizeof(char));
          //data->data = (char*) malloc(sizeof(char));
          for (int i = 0; i < len; i++) { //this is -1 because we don't want the null terminator
            data->data = (char *) realloc(data->data, sizeof(char) * data->length + 1);
            data->data[data->length + i] = line.data()[i];
          }
          data->length += len;
      }
    }
    file.close();
    return std::optional<raw_t*>{data};
}
