#include "network.h"


void Network::feedfoward(Narray activation){
    Narray hidden_result = hidden.activate(activation);

    output.activate(hidden_result);
}

Data Network::backpropagation(int expected){
    Data data = Data();

    data.weightsHidden = evaluateWeights(hidden, input, expected);
    data.weightsOutput = evaluateWeights(output, hidden, expected);

    data.biasesHidden = evaluateBiases(hidden, input, expected);
    data.biasesOutput = evaluateBiases(output, hidden, expected);
}

Data Network::backpropagation(Layer input, Layer output, unsigned int representedValue){}

Narray Network::evaluateWeights(Layer current, Layer previous, int expecten) {
    int sizeCurrent = current.numNeuronsThis;
    int sizePrevious = previous.numNeuronsThis;

    Narray ret = Narray(sizeCurrent, sizePrevious);

    for (int i = 0; i < sizeCurrent; i++) {
        double actCurr = current.value.values[i][0];

        for (int j = 0; j < sizePrevious; j++) {
            double actPrev = previous.value.values[j][i];
            double weight = current.weight.values[i][j];
            
            //double variance = actPrev * derivateSigmoid()

            // TODO
        }
    }
}

// Recebe o output como uma matriz
// coluna e o numero esperado
// de uma interpretacao correta e avalia o custo
// do treinamento associado a essa resposta
double Network::quadraticCost(Narray output, int expected){
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
Narray Network::buildExpectedOutput(unsigned int size, int expected){
    Narray expectedOutput = Narray(size, 1);

    for (int i = 0; i < size; i++) {
        expectedOutput.values[i][0] = 0;
    }
    expectedOutput.values[expected][0] = 1;

    return expectedOutput;
}

// Soma todos os valores da matriz coluna de custos
double Network::sumCosts(Narray costs){
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
Data Network::minibatchEvaluation(TrainingExample minibatch[], int size){
    TrainingExample sample;
    Narray imageData;
    //double cost = 0.0;
    //double averageCost = 0.0;
    Narray hiddenWeights = Narray(hidden.weight.row, hidden.weight.colunm);
    Narray outputWeights = Narray(output.weight.row, output.weight.colunm);
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