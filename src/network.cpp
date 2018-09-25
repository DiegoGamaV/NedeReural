#include "network.h"

Layer hidden;
Layer output;
Layer input;

void Network::feedfoward(Narray activation){
    Narray hidden_result = hidden.activate(activation);

    output.activate(hidden_result);
}

Data Network::backpropagation(Narray expected){
    Data data = Data();
    
    // TODO: Zerar data
    double A_output, A_hidden, A_input, Z_output, Z_hidden, y;

    // Iterar pelos neuronios da camada output
    for (int i = 0; i < output.numNeuronsThis; i++){

        A_output = output.value.values[i][0];
        Z_output = output.zeta.values[i][0];
        y = expected.values[i][0];

        // Derivada parcial (da/dz) * (dC0/da)
        double recurrentPart = derivateSigmoid(Z_output) * 2 * (A_output - y);
        // Gerar modificacao necessaria no bias do output
        data.biasesOutput.values[i][0] += recurrentPart;

        // Iterar pelos neuronios da camada hidden
        for (int j = 0; j < hidden.numNeuronsThis; j++){
            A_hidden = hidden.value.values[j][0];
            Z_hidden = hidden.zeta.values[j][0];

            // Guardar a mudanca necessaria para esse peso 
            data.weightsOutput.values[i][j] += A_hidden * recurrentPart;
            
            // Iterar pelos pesos entre a camada input e hidden
            for (int k = 0; k < input.numNeuronsThis; k++){

                // (dz/dw) * (da/dz) * (dz/da) * recurrentPart
                // TODO: Corrigir formula e atualizar biases da hidden
                // TODO: Conectar isso com a nocao de criacao de uma layer para o input
                data.weightsHidden.values[j][k] += A_input * derivateSigmoid(Z_hidden);
            }
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

    // TODO: Zerar narrays
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

        //desiredChanges = backpropagation(input, output, sample.representedValue);

        averageDesiredChanges = averageDesiredChanges + desiredChanges;
    }

    //averageCost = averageCost / size;

    averageDesiredChanges = averageDesiredChanges / size;

    return averageDesiredChanges;
}