#include "doriNum.h"

Narray::Narray(unsigned int _row, unsigned int _colunm){
    values = (double**) malloc(sizeof(double*) * _row);
    for(register int i = 0; i < _row; i++)
        values[i] = (double*) malloc(sizeof(double) * _colunm);
    row = _row;
    colunm = _colunm;
    randomValues();
}

Narray Narray::operator+ (const double &a){
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = values[i][j] + a;
        }
    }
    return ret;
}

Narray Narray::operator- (){
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = values[i][j] * (-1);
        }
    }
    return ret;
}

Narray Narray::operator* (const double &a){
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = a * values[i][j];
        }
    }
    return ret;
}

Narray Narray::operator/ (const double &a){
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = values[i][j] / a;
        }
    }
    return ret;
}

Narray Narray::operator+ (const Narray &a){
    if(a.row != row || a.colunm != colunm){
        exit(1);
    }
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = a.values[i][j] + values[i][j];
        }
    }
    return ret;
}
Narray Narray::operator- (const Narray &a){
    if(a.row != row || a.colunm != colunm){
        exit(1);
    }
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = a.values[i][j] - values[i][j];
        }
    }
    return ret;
}

Narray Narray::operator() (auto func){
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = func(values[i][j]);
        }
    }
    return ret;
}

Narray Narray::operator* (const Narray &a){
    if(colunm != a.row){
        exit(1);
    }
    Narray ret = Narray(row, a.colunm);
    memset(ret.values, 0, sizeof ret.values);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < a.colunm; j++){
            for(register int k = 0; k < colunm; k++){
                ret.values[i][j] += values[i][k] * a.values[k][j];
            }
        }
    }
    return ret;
}

void Narray::randomValues(){
    srand(time(NULL));
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            values[i][j] = rand() / ((double) RAND_MAX);
        }
    }
}

Narray operator- (double a, Narray &b){
    Narray ret = Narray(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = a - b.values[i][j];
        }
    } 
    return ret;
}

Narray operator- (Narray &b, double a){
    Narray ret = Narray(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = b.values[i][j] - a;
        }
    } 
    return ret;
}

auto sigmoid = [](double val){
    return 1 / (1 + exp(-val));
};

auto fastSigmoid = [](double val){
    return val / (1 +  fabs(val)); 
};

auto derivateSigmoid = [](double val){
    return sigmoid(val) * (1 - sigmoid(val)); 
};

int main(){
    Narray n = Narray(2, 2);
    n.randomValues();
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            std::cout << n.values[i][j] << " \n"[j + 1 == 2];
        }
    }
    return 0;
}