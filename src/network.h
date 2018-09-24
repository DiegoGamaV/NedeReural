#pragma once

#include "trainingExample.h"
#include "data.h"
#include "layer.h"

struct Network {
    Layer hidden;
    Layer output;
    Layer input;

    void feedfoward(Narray activation);

    Narray evaluateBiases(Layer current, Layer previous, int expected);

    Narray evaluateWeights(Layer current, Layer previous, int expecten);

    Data backpropagation(int expected);
    Data backpropagation(Layer input, Layer output, unsigned int representedValue);

    // Recebe o output como uma matriz
    // coluna e o numero esperado
    // de uma interpretacao correta e avalia o custo
    // do treinamento associado a essa resposta
    double quadraticCost(Narray output, int expected);

    // Cria uma matriz coluna que sera
    // a melhor resposta possivel
    Narray buildExpectedOutput(unsigned int size, int expected);

    // Soma todos os valores da matriz coluna de custos
    double sumCosts(Narray costs);

    // Recebe o minibatch e o tamanho do minibatch,
    // e computa todas as mudancas desejadas nos pesos e biases
    // para cada um dos exemplos do minibatch, e retorna
    // a as mudancas medias desejadas.
    Data minibatchEvaluation(TrainingExample minibatch[], int size);

};
