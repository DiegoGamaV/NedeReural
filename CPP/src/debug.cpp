#include "debug.h"

void DEBUG_MATRIX(Narray a){
    for (int i = 0; i < a.row; i++) {
        for (int j = 0; j < a.column; j++) {
            std::cout << a.at(i, j) << " ";
        } std::cout << std::endl;
    }
}

void DEBUG_TEST(){
    std::cout << "D" << std::endl;
}

void DEBUG_TYPE(int a){
    std::cout << a << std::endl;
}
