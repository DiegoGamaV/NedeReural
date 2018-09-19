#pragma once

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "doriNum.h"

struct InputReader{

    // transforma os valores no arquivo em um Narray
    Narray readMatrix(std::string path, int line, int column);

    // verifica se o arquivo esta vazio
    bool empty(std::string path);
};