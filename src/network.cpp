#include "doriNum.h"
#include "layer.h"

Narray buildExpectedOutput(unsigned int, int);

double sumCosts(Narray);

Data backpropagation(Layer, Layer, unsigned int);

Data minibatchEvaluation(TrainingExample[], int);

// Recebe o output como uma matriz
// coluna e o numero esperado
// de uma interpretacao correta e avalia o custo
// do treinamento associado a essa resposta
double quadraticCost(Narray output, int expected){
	double totalCost = 0;
    
    unsigned int size = output.row;
    Narray expectedOutput = buildExpectedOutput(size, expected);
    Narray costs = expectedOutput - output;
    for (int i = 0; i < size; i++){
    	costs.values[i][0] = costs.values[i][0] * costs.values[i][0];
    }

    double sumOfCosts = sumCosts(costs);
    return sumOfCosts;
}

// Cria uma matriz coluna que sera
// a melhor resposta possivel
Narray buildExpectedOutput(unsigned int size, int expected){
    Narray expectedOutput = Narray(size, 1);

    for (int i = 0; i < size; i++) {
        expectedOutput.values[i][0] = 0;
    }
    expectedOutput.values[expected][0] = 1;

    return expectedOutput;
}

// Soma todos os valores da matriz coluna de custos
double sumCosts(Narray costs){
    double sum = 0;

    for (int i = 0; i < costs.row; i++) {
        double val = costs.values[i][0];
        sum += val;
    }
    return sum;
}

// Recebe o minibatch e o tamanho do minibatch,
// e computa todas as mudancas desejadas nos pesos e biases
// para cada um dos exemplos do minibatch, e retorna
// a as mudancas medias desejadas.
Data minibatchEvaluation(TrainingExample[] minibatch, int size){
    TrainingExample sample;
    Narray imageData;
    //double cost = 0.0;
    //double averageCost = 0.0;
    Narray hiddenWeights = Narray(hidden.weight.row, hidden.weight.column);
    Narray outputWeights = Narray(output.weight.row, output.weight.column);
    Narray hiddenBiases = Narray(hidden.bias.row, 0);
    Narray outputBiases = Narray(output.bias.row, 0);
    Data desiredChanges;
    Data averageDesiredChanges = Data(hiddenWeights, outputWeights, hiddenBiases, outputBiases);

    for (int i = 0; i < size; i++){
        sample = minibatch[i];
        imageData = sample.imageData;
        feedfoward(imageData);
        
        //cost = quadraticCost(output, sample.representedValue);
        //averageCost = averageCost + cost;

        desiredChanges = backpropagation(input, output, sample.representedValue);
        averageDesiredChanges.weightsHidden = averageDesiredChanges.weightsHidden + desiredChanges.weightsHidden;
        averageDesiredChanges.weightsOutput = averageDesiredChanges.weightsOutput + desiredChanges.weightsOutput;
        averageDesiredChanges.biasesHidden = averageDesiredChanges.biasesHidden + desiredChanges.biasesHidden;
        averageDesiredChanges.biasesOutput = averageDesiredChanges.biasesOutput + desiredChanges.biasesOutput;
    }

    //averageCost = averageCost / size;
    averageDesiredChanges.weightsHidden = averageDesiredChanges.weightsHidden / size;
    averageDesiredChanges.weightsOutput = averageDesiredChanges.weightsOutput / size;
    averageDesiredChanges.biasesHidden = averageDesiredChanges.biasesHidden / size;
    averageDesiredChanges.biasesOutput = averageDesiredChanges.biasesOutput / size;

    return averageDesiredChanges;
}