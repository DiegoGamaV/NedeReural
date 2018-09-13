#include "doriNum.h"

// Implementação do construtor
Narray::Narray(unsigned int _row, unsigned int _colunm){
    
    // Aloca dinamicamente a matriz na memória
    values = (double**) malloc(sizeof(double*) * _row);
    for(register int i = 0; i < _row; i++)
        values[i] = (double*) malloc(sizeof(double) * _colunm);
    
    // guarda o tamanho da matriz
    row = _row;
    colunm = _colunm;
    
    // insere valores aleatórios na matriz
    randomValues();
}

// Dividir a matriz por escalar
Narray Narray::operator/ (const double &a){
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = values[i][j] / a;
        }
    }
    return ret;
}

// Somar matrizes
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

// Subtrair matrizes
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

// Mapear elementos de matrizes
Narray Narray::operator() (auto func){
    Narray ret = Narray(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = func(values[i][j]);
        }
    }
    return ret;
}

// Multiplicação de matrizes
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

// Definir matriz de valores
void Narray::operator<< (double** a){
    memcpy(values, a, sizeof(double) * row * colunm);
}

// Colocar valores aleatórios entre 0 e 1 na matriz
void Narray::randomValues(){
    srand(time(NULL));
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            values[i][j] = (rand()%101);
            values[i][j] *= rand()%2 == 0? 1 : -1;
        }
    }
}

// Soma de escalar por matriz
Narray operator+ (const double &a, const Narray &b){
    Narray ret = Narray(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = b.values[i][j] + a;
        }
    }
    return ret;
}

// Soma de matriz por escalar
Narray operator+(const Narray &a, const double &b){
    return b + a;
}

// Subtração de escalar por matriz
Narray operator- (double a, Narray &b){
    Narray ret = Narray(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = a - b.values[i][j];
        }
    } 
    return ret;
}

// Subtração de matriz por escalar
Narray operator- (Narray &b, double a){
    Narray ret = Narray(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = b.values[i][j] - a;
        }
    } 
    return ret;
}

// Multiplicação de escalar por matriz
Narray operator* (const double &a, const Narray &b){
    Narray ret = Narray(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = a * b.values[i][j];
        }
    }
    return ret;
}

// Multiplicação de matriz por escalar
Narray operator* (const Narray &a, const double &b){
    return b * a;
}

// Sigmoid já definida
auto sigmoid = [](double val){
    return 1.0 / (1.0 + exp(-val));
};

// Derivada da Sigmoida já definida
auto derivateSigmoid = [](double val){
    return sigmoid(val) * (1.0 - sigmoid(val)); 
};
