#pragma once

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "doriNum.h"

struct InputReader{
    Narray readMatrix(string path, int line, int column);
};
