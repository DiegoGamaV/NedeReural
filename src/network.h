#pragma once
#include <bits/stdc++.h>

// Header da Rede

// Estrutura que representa uma camada de neuronios da rede neural
struct Layer {

    // Numero de neuronios da camada atual
    unsigned int numNeuronsThis;

    // Numero de neuronios da camada anterior
    unsigned int numNeuronsPrevious;

    // Matriz de pesos; w[i][j] representa o peso da aresta
    // que conecta o i-esimo neuronio da camada anterior
    // com o j-esimo neuronio da camada atual
    double** weight;

    // Biases da camada
    double* bias;

    // Valores de ativacao dos neuronios das camadas
    double* value;

    // Construtor da camada
    Layer(unsigned int _numNeuronsThis, unsigned int _numNeuronsPrevious);
    
    // Funcao de ativacao dos neuronios da camada
    double activate(double &previousValues);
};