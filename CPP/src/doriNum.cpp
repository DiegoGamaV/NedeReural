#include "doriNum.h"
#include <stdexcept>


// Implementação do construtor
Narray::Narray(unsigned int _row, unsigned int _column)
    : values(_row * _column)
    , row{_row}
    , column{_column}
{
}

Narray::Narray()
    : Narray(1, 1)
{
}

Narray::Narray(const Narray &a)
    : values(a.values)
    , row{a.row}
    , column{a.column}
{
}

// Dividir a matriz por escalar
Narray Narray::operator/ (const double &a){
    Narray ret = Narray(row, column);
    for (auto& d : ret.values) d /= a;
    return ret;
}

// Somar matrizes
Narray Narray::operator+ (const Narray &a){
    if(a.row != row || a.column != column){
        throw std::runtime_error("Row and column do not match for the sum of two matrices");
    }
    Narray ret = Narray(row, column);
    std::transform(values.begin(), values.end(),
                   a.values.begin(),
                   ret.values.begin(),
                   std::plus<>());
    return ret;
}

// Subtrair matrizes
Narray Narray::operator- (const Narray &a){
    if(a.row != row || a.column != column){
        throw std::runtime_error("Row and column do not match for the sum of two matrices");
    }
    Narray ret = Narray(row, column);
    std::transform(a.values.begin(), a.values.end(),
                   values.begin(),
                   ret.values.begin(),
                   std::minus<>());
    return ret;
}

// Mapear elementos de matrizes
Narray Narray::operator() (double (*f)(double)){
    Narray ret = Narray(row, column);
    std::transform(ret.values.begin(), ret.values.end(),
                   ret.values.begin(), f);
    return ret;
}

// Multiplicação de matrizes
Narray Narray::operator* (const Narray &a){
    if(std::min(column, row) == 1 && std::min(a.column, a.row) == 1){
        int range = std::max(column, std::max(row, std::max(a.column, a.row)));
        Narray ret = Narray(range, 1);
        for(register int i = 0; i < range; i++) ret.at(i, 0) = 1;

        if(column > row){
            for(register int i = 0; i < column; i++)
                ret.at(i, 0) *= at(0, i);
        }else{
            for(register int i = 0; i < column; i++)
                ret.at(i, 0) *= at(i, 0);
        }

        if(a.column > a.row){
            for(register int i = 0; i < column; i++)
                ret.at(i, 0) *= a.at(0, i);
        }else{
            for(register int i = 0; i < column; i++)
                ret.at(i, 0) *= a.at(i, 0);
        }

        return ret;
    }else if(column != a.row){
        throw std::runtime_error("Row and column do not match for the sum of two matrices");
    }

    Narray ret = Narray(row, a.column);

    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < a.column; j++){
            for(register int k = 0; k < column; k++){
                ret.at(i, j) += at(i, k) * a.at(k, j);
            }
        }
    }

    return ret;
}

// Colocar valores aleatórios entre 0 e 1 na matriz
void Narray::randomValues(){
    srand(time(NULL));
    for(register int i = 0; i < row; i++){
        for(register int j = 0; j < column; j++){
            at(i, j) = rand()/(RAND_MAX / 1);
            at(i, j) *= rand()%2 == 0? 1 : -1;  
        }
    }
}

void Narray::zeroValues(){
    values.assign(values.size(), 0.0);
}

// Soma de escalar por matriz
Narray operator+ (const double &a, const Narray &b){
    Narray ret = Narray(b.row, b.column);
    std::transform(b.values.begin(), b.values.end(),
                   ret.values.begin(),
                   [a](auto&& d) { return d + a; });
    return ret;
}

// Soma de matriz por escalar
Narray operator+(const Narray &a, const double &b){
    return b + a;
}

// Subtração de escalar por matriz
Narray operator- (double a, Narray &b){
    Narray ret = Narray(b.row, b.column);
    std::transform(b.values.begin(), b.values.end(),
                   ret.values.begin(),
                   [a](auto&& d) { return a - d; });
    return ret;
}

// Subtração de matriz por escalar
Narray operator- (Narray &b, double a){
    Narray ret = Narray(b.row, b.column);
    std::transform(b.values.begin(), b.values.end(),
                   ret.values.begin(),
                   [a](auto&& d) { return d - a; });
    return ret;
}

// Multiplicação de escalar por matriz
Narray operator* (const double &a, const Narray &b){
    Narray ret = Narray(b.row, b.column);
    std::transform(b.values.begin(), b.values.end(),
                   ret.values.begin(),
                   [a](auto&& d) { return d * a; });
    return ret;
}

// Multiplicação de matriz por escalar
Narray operator* (const Narray &a, const double &b){
    return b * a;
}

// Get matrix row
Narray Narray::getRow(int id){
    if(id < 0 || id >= row) exit(1);
    Narray ret = Narray(1, column);
    for(register int i = 0; i < column; i++) ret.at(0, i) = at(id, i);
    return ret;
}

// Get matrix column
Narray Narray::getColunm(int id){
    if(id < 0 || id >= column) exit(1);
    Narray ret = Narray(row, 1);
    for(register int i = 0; i < row; i++) ret.at(i, 0) = at(i, id);
    return ret;
}

// Pega a matriz transposta
Narray Narray::transposta(){
    Narray ret = Narray(column, row);
    for(register int i = 0; i < row; i++){
        for(register int j = i + 1; j < column; j++){
            std::swap(ret.at(j, i), ret.at(i, j));
        }
    }
    return ret;
}

double sigmoid(double val){
    return 1.0 / (1.0 + exp(-val));
}

double derivateSigmoid(double val){
    return sigmoid(val) * (1.0 - sigmoid(val));
}
