#pragma once

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <vector>

struct Narray{

    // Valores da matriz
    std::vector<double> values;

    // Quantidade de linhas e colunas
    unsigned int row, column;

    // Construtor
    Narray(unsigned int _row, unsigned int _column);
    Narray();
    Narray(const Narray &a);

    inline double& at(int i, int j) { return values[column * i + j]; }
    inline double at(int i, int j) const { return values[column * i + j]; }

    // Operador de dividir todos os elementos por um escalar
    Narray operator/ (const double &a);

    // Somar matrizes
    Narray operator+ (const Narray &a);

    // Subtrair matrizes
    Narray operator- (const Narray &a);

    // Multiplicação de matrizes
    Narray operator* (const Narray &a);

    // Mapear valores da matriz
    Narray operator() (double (*f)(double));

    // Elementos aleatórios na matriz
    void randomValues();

    // Zera os elementos da matriz
    void zeroValues();

    // Pega a linha da matriz
    Narray getRow(int id);

    // Pega a coluna da matriz
    Narray getColunm(int id);

    // Pega a matriz transposta
    Narray transposta();
};

Narray operator+ (const double &a, const Narray &b);

Narray operator+ (const Narray &b, const double &a);

Narray operator- (double a, Narray &b);

Narray operator- (Narray &b, double a);

Narray operator* (const double &a, const Narray &b);

Narray operator* (const Narray &a, const double &b);

double sigmoid(double val);

double derivateSigmoid(double val);
