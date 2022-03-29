#ifndef READ_H
#define READ_H

#include <optional>

#include "compress.h"

class Read{
    public:
        static std::optional<raw_t> read(char* fname);

    private:
};



#endif