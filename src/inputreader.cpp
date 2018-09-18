#include "inputreader.h"

Narray InputReader::readMatrix(string path, int row, int column){
    ifstream archive (path);

    Narray ret = Narray(row, column);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            archive >> ret.value[i][j];
        }
    }

    return ret;
}