#include "doriNum.h"
#include "debug.h"

// Implementação do construtor
Narray::Narray(unsigned int _row, unsigned int _colunm){
    
    // Aloca dinamicamente a matriz na memória
    values = (double**) malloc(sizeof(double*) * _row);
    for(register int i = 0; i < _row; i++)
        values[i] = (double*) malloc(sizeof(double) * _colunm);
    
    // guarda o tamanho da matriz
    row = _row;
    colunm = _colunm;
    for(register int i = 0; i < row; i++)
        for(register int j = 0; j < colunm; j++)
            values[i][j] = 0;
}

Narray::Narray(){
    unsigned int _row = 1;
    unsigned int _colunm = 1;
    // Aloca dinamicamente a matriz na memória
    values = (double**) malloc(sizeof(double*) * _row);
    for(register int i = 0; i < _row; i++)
        values[i] = (double*) malloc(sizeof(double) * _colunm);
    
    // guarda o tamanho da matriz
    row = _row;
    colunm = _colunm;
    for(register int i = 0; i < row; i++)
        for(register int j = 0; j < colunm; j++)
            values[i][j] = 0;
}

Narray::Narray(const Narray &a){
    unsigned int _row = a.row;
    unsigned int _colunm = a.colunm;
    // Aloca dinamicamente a matriz na memória
    values = (double**) malloc(sizeof(double*) * _row);
    for(register int i = 0; i < _row; i++)
        values[i] = (double*) malloc(sizeof(double) * _colunm);
    
    // guarda o tamanho da matriz
    row = _row;
    colunm = _colunm;

    // insere valores nulos na matriz
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            values[i][j] = a.values[i][j];
        }
    }
}

// Dividir a matriz por escalar
Narray Narray::operator/ (const double &a){
    Narray ret(row, colunm);
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
    Narray ret(row, colunm);
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
    Narray ret(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = a.values[i][j] - values[i][j];
        }
    }
    return ret;
}

// Mapear elementos de matrizes
Narray Narray::operator() (double (*f)(double)){
    Narray ret(row, colunm);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[i][j] = f(values[i][j]);
        }
    }
    return ret;
}

// Multiplicação de matrizes
Narray Narray::operator* (const Narray &a){

    // if(std::min(colunm, row) == 1 && std::min(a.colunm, a.row) == 1){
    //     int range = std::max(colunm, std::max(row, std::max(a.colunm, a.row)));
    //     Narray ret = Narray(range, 1);
    //     for(register int i = 0; i < range; i++)ret.values[i][0] = 1;

    //     if(colunm > row)for(register int i = 0; i < colunm; i++)ret.values[i][0] *= values[0][i];
    //     else for(register int i = 0; i < colunm; i++)ret.values[i][0] *= values[i][0];

    //     if(a.colunm > a.row)for(register int i = 0; i < colunm; i++)ret.values[i][0] *= a.values[0][i];
    //     else for(register int i = 0; i < colunm; i++)ret.values[i][0] *= a.values[i][0];

    //     return ret;
    // }else if(colunm != a.row){
    //     exit(1);
    // }

    if(colunm != a.row){
        exit(1);
    }

    Narray ret(row, a.colunm);

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

// Definir matriz de valores
void Narray::operator>> (double** a){
    memcpy(a, values, sizeof(double) * row * colunm);
}

// Colocar valores aleatórios entre 0 e 1 na matriz
void Narray::randomValues(){
    srand(time(NULL));
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            values[i][j] = rand()/(RAND_MAX / 1.0);
            values[i][j] *= rand()%2 == 0? 1 : -1;  
        }
    }
}

void Narray::zeroValues(){
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            values[i][j] = 0;
        }
    }
}

// Soma de escalar por matriz
Narray operator+ (const double &a, const Narray &b){
    Narray ret(b.row, b.colunm);
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
    Narray ret(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = a - b.values[i][j];
        }
    } 
    return ret;
}

// Subtração de matriz por escalar
Narray operator- (Narray &b, double a){
    Narray ret(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = b.values[i][j] - a;
        }
    } 
    return ret;
}

// Multiplicação de escalar por matriz
Narray operator* (const double &a, const Narray &b){
    Narray ret(b.row, b.colunm);
    for(register int i = 0; i < b.row; i++){
        for(register int j = 0; j < b.colunm; j++){
            ret.values[i][j] = a * b.values[i][j];
        }
    }
    return ret;
}

// Produto de Hadammad
Narray hadamard(const Narray &a, const Narray &b){

    if(a.row != b.row || a.colunm != b.colunm){
        exit(1);
    }

    Narray ret = Narray(a.row, a.colunm);

    for(register int i = 0; i < a.row; i++){
        for(register int j = 0; j < a.colunm; j++){
            ret.values[i][j] = b.values[i][j] * a.values[i][j];                
        }
    }

    return ret;
}

// Multiplicação de matriz por escalar
Narray operator* (const Narray &a, const double &b){
    return b * a;
}

// Get matrix row
Narray Narray::getRow(int id){
    if(id < 0 || id >= row) exit(1);
    Narray ret(1, colunm);
    for(register int i = 0; i < colunm; i++)ret.values[0][i] = values[id][i];
    return ret;
}

// Get matrix colunm
Narray Narray::getColunm(int id){
    if(id < 0 || id >= colunm) exit(1);
    Narray ret(row, 1);
    for(register int i = 0; i < row; i++)ret.values[i][0] = values[i][id];
    return ret;
}

// Pega a matriz transposta
Narray Narray::transposta(){
    Narray ret(colunm, row);
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < colunm; j++){
            ret.values[j][i] = values[i][j];
        }
    }

    return ret;
}

void Narray::close(){
    for(register int i = 0; i < row; i++){
        free(values[i]);
    }
    row = 0;
    colunm = 0;
}

double sigmoid(double val){
    return 1.0 / (1.0 + exp(-val));
}

double derivateSigmoid(double val){
    return sigmoid(val) * (1.0 - sigmoid(val));
}