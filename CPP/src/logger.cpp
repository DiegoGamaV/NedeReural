#include "logger.h"

int verbosity_level;

void log(std::string msg) {
    if (verbosity_level > 0) {
        std::cerr << msg << std::endl; 
    }
}

void setVerbosity(int level) {
    verbosity_level = level;
}