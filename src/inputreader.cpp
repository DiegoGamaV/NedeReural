#include "inputreader.h"

// transforma os valores no arquivo em um Narray
Narray InputReader::readMatrix(std::string path, int row, int column){
    std::ifstream archive (path);

    Narray ret = Narray(row, column);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            archive >> ret.values[i][j];
        }
    }

    return ret;
}

// verifica se o arquivo esta vazio
bool InputReader::empty(std::string path){
    std::ifstream archive (path);
    return archive.tellg() == 0;
}