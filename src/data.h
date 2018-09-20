#include "doriNum.h"

// Estrutura de dados da rede neural
struct Data {

    // Informacao sobre os pesos das arestas da camada hidden
    Narray weightsHidden;

    // Informacao sobre os pesos das arestas da camada output
    Narray weightsOutput;

    // Informacao sobre os biases de todos os neuronios
    Narray allBiases;
};