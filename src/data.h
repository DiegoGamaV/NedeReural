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
    Data(Narray &hiddenWeights, Narray &outputWeights, Narray &hiddenBiases, Narray &outputBiases);
    Data();
};