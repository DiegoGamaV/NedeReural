#pragma once

#include <fstream>
#include "doriNum.h"
#include <vector>
#include "debug.h"

typedef char byte;

union buffer{
    int integer;
    char chars[4];
};

struct binaryReader{
    std::ifstream image;
    std::ifstream label;

    binaryReader(std::string image_path, std::string label_path);

    std::vector <std::pair<Narray, byte > > allData(double fator);
};