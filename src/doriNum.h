#pragma once

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <iostream>

struct Narray{

    // Valores da matriz
    double** values;

    // Quantidade de linhas e colunas
    unsigned int row, colunm;

    // Construtor
    Narray(unsigned int _row, unsigned int _colunm);
    Narray();
    Narray(const Narray &a);
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

    // Definir matriz de valores
    void operator<< (double** a);

    // Retornar matriz de valores
    void operator>> (double** a);

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

    // Liberar NArray
    void close();
};

Narray operator+ (const double &a, const Narray &b);

Narray operator+ (const Narray &b, const double &a);

Narray operator- (double a, Narray &b);

Narray operator- (Narray &b, double a);

Narray operator* (const double &a, const Narray &b);

Narray operator* (const Narray &a, const double &b);

double sigmoid(double val);

double derivateSigmoid(double val);