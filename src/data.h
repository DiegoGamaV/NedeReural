#pragma once

#include "doriNum.h"

// Estrutura de dados da rede neural
struct Data {

    // Informacao sobre os pesos das arestas da camada hidden
    Narray weightsHidden;

    // Informacao sobre os pesos das arestas da camada output
    Narray weightsOutput;

    // Informacao sobre os biases dos neuronios da camada hidden
    Narray biasesHidden;

    // Informacao sobre os biases dos neuronios da camada output
    Narray biasesOutput;

    // Construtor do tipo data.
    Data(Narray _hiddenWeights, Narray _outputWeights, Narray _hiddenBiases, Narray _outputBiases);
    Data();

    // Somar Datas
    Data operator+ (const Data &a);

    // Dividir Data por escalar
    Data operator/ (const double &a);

    void close();
    // Zera todos os elementos da Data
    void zeroValues();
};