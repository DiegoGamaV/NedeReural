#pragma once

#include "trainingExample.h"
#include "data.h"
#include "layer.h"
#include <vector>

struct Network {

    Layer hidden;
    Layer output;
    Layer input;

    Network();
    
    Network(int pixels, int sizeHidden);

    Network(int pixels, int sizeHidden, Data data);

    void feedfoward(Narray activation);

    Narray evaluateBiases(Layer current, Layer previous, int expected);

    Narray evaluateWeights(Layer current, Layer previous, int expecten);

    Data backpropagation(Narray expected);

    // Cria uma matriz coluna que sera
    // a melhor resposta possivel
    Narray buildExpectedOutput(int expected);

    // Recebe o minibatch e o tamanho do minibatch,
    // e computa todas as mudancas desejadas nos pesos e biases
    // para cada um dos exemplos do minibatch, e retorna
    // a as mudancas medias desejadas.
    Data minibatchEvaluation(TrainingExample minibatch[], int size);

    void trainingEpoch(std::vector<TrainingExample> trainingSamples, int batchSize, int batchAmount);

    int testEpoch(std::vector<TrainingExample> testSamples);

    void close();
};  
