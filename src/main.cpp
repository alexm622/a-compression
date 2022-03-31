#include "read.hpp"

#include <cstring>

#include <stdio.h>
#include <string>

int main(){
    std::string fname = "test.txt";
    std::optional<raw_t*> data_o = Read::read(fname.data());
    if (!data_o.has_value()) {
        printf("file %s does not exist!", fname.data());
        return 0;
    }
    raw_t* data = data_o.value();

    char* fdata = (char*) malloc(sizeof(char)*data->length + 1);
    fdata = (char*) memcpy(fdata,data->data,sizeof(char) * data->length + 1);
    //add null terminator
    fdata[data->length]= '\0';
    printf("data\n");
    printf("--------------------------------\n");
    for (int i = 0; i < data->length; i++) {
        //test binary converter
        
    }
    std::string temp = "az";
    printf("%s", Compression::toBin(temp.data()));
    return 1;
}
