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

    for (int i = 0; i < data->length; i++) {
        printf("%u", data->data[i]);
    }

    Compression::compressed(data);

    return 1;
}
