#pragma once

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <algorithm>

struct Narray{

    // Valores da matriz
    double** values;

    // Quantidade de linhas e colunas
    unsigned int row, colunm;

    // Construtor
    Narray(unsigned int _row, unsigned int _colunm);

    // Operador de dividir todos os elementos por um escalar
    Narray operator/ (const double &a);

    // Somar matrizes
    Narray operator+ (const Narray &a);

    // Subtrair matrizes
    Narray operator- (const Narray &a);

    // Multiplicação de matrizes
    Narray operator* (const Narray &a);

    // Mapear valores da matriz
    Narray operator() (auto func);

    // Definir matriz de valores
    void operator<< (double** a);

    // Retornar matriz de valores
    void operator>> (double** a);

    // Elementos aleatórios na matriz
    void randomValues();

    // Get matrix row
    Narray getRow(int id);

    // Get matrix colunm
    Narray getColunm(int id);

    // Pega a matriz transposta
    Narray transposta();
};