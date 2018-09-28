#include "network.h"
#include "debug.h"
#include "logger.h"

// Constroi uma network sem informacao
Network::Network(){
    hidden = Layer(16, 784);
    output = Layer(10, 16);
    input = Layer(784, 1);
}

// Constroi uma network com valores arbitrarios
Network::Network(int pixels, int sizeHidden){
    hidden = Layer(sizeHidden, pixels);
    output = Layer(10, sizeHidden);
    input = Layer(pixels, 1);
}

// Constroi uma rede recebendo todas as informacoes dela
Network::Network(int pixels, int sizeHidden, Data data){
    hidden = Layer(sizeHidden, pixels);
    output = Layer(10, sizeHidden);
    input = Layer(pixels, 1);
    hidden.weight = data.weightsHidden;
    output.weight = data.weightsOutput;
    hidden.bias = data.biasesHidden;
    output.bias = data.biasesOutput;
}

void Network::feedfoward(Narray activation){

    input.value = activation;
    Narray hidden_result = hidden.activate(activation);
    output.activate(hidden_result);
}


Data Network::backpropagation(Narray expected){
    log("Iniciando Data com valores arbitrarios");
    Data data = Data(hidden.weight, output.weight, hidden.bias, output.bias);

    log("Zerando valores do Data gerado");
    data.zeroValues();
    
    double A_output, A_hidden, A_input, Z_output, Z_hidden, y;

    // Iterar pelos neuronios da camada output
    for (int i = 0; i < output.numNeuronsThis; i++){

        A_output = output.value.values[i][0];
        Z_output = output.zeta.values[i][0];
        y = expected.values[i][0];

        // Derivada parcial (da/dz) * (dC0/da)
        double recurrentPart = derivateSigmoid(Z_output) * 2 * (A_output - y);
        // Gerar modificacao necessaria no bias do output
        data.biasesOutput.values[i][0] -= recurrentPart;

        // Iterar pelos neuronios da camada hidden
        for (int j = 0; j < hidden.numNeuronsThis; j++){
            double W_output = output.weight.values[i][j];
            A_hidden = hidden.value.values[j][0];
            Z_hidden = hidden.zeta.values[j][0];

            // Guardar a mudanca necessaria para esse peso 
            data.weightsOutput.values[i][j] -= A_hidden * recurrentPart;
            
            double internalRecurrent = derivateSigmoid(Z_hidden) * W_output * recurrentPart;

            // Atualiza biases da hidden
            data.biasesHidden.values[j][0] -= internalRecurrent;

            // Iterar pelos pesos entre a camada input e hidden
            for (int k = 0; k < input.numNeuronsThis; k++){
                A_input = input.value.values[k][0];
                // (dz/dw) * (da/dz) * (dz/da) * recurrentPart
                double calc = A_input * internalRecurrent;
                data.weightsHidden.values[j][k] -= calc;
            }
        }
    }
    log("Terminando de computar backpropagation");
    return data;
}

// Recebe o output como uma matriz
// coluna e o numero esperado
// de uma interpretacao correta e avalia o custo
// do treinamento associado a essa resposta
double Network::quadraticCost(Narray output, int expected){
	double totalCost = 0;
    
    unsigned int size = output.row;
    Narray expectedOutput = buildExpectedOutput(expected);
    Narray costs = expectedOutput - output;
    for (int i = 0; i < size; i++){
    	costs.values[i][0] = costs.values[i][0] * costs.values[i][0];
    }

    double sumOfCosts = sumCosts(costs);
    expectedOutput.close();
    return sumOfCosts;
}

// Cria uma matriz coluna que sera
// a melhor resposta possivel
Narray Network::buildExpectedOutput(int expected){
    Narray expectedOutput = Narray(10, 1);

    for (int i = 0; i < 10; i++) {
        expectedOutput.values[i][0] = 0;
    }
    expectedOutput.values[expected][0] = 1.0;

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
    Narray hiddenBiases = Narray(hidden.bias.row, 1);
    Narray outputBiases = Narray(output.bias.row, 1);

    Data desiredChanges;
    Data averageDesiredChanges = Data(hiddenWeights, outputWeights, hiddenBiases, outputBiases);

    log("Comecando a execucao de cada sample do minibatch");
    for (int i = 0; i < size; i++){
        sample = minibatch[i];
        //imageData <<= sample.imageData;
        imageData = Narray(sample.imageData);
        log("Iniciando feedfoward de um sample");
        feedfoward(imageData);

        //cost = quadraticCost(output, sample.representedValue);
        //averageCost = averageCost + cost;

        log("Construindo matriz de output esperado");
        Narray expected = buildExpectedOutput(sample.representedValue);

        log("Iniciando backpropagation");
        desiredChanges = backpropagation(expected);

        log("Computando quais sao as mudancas desejadas");
        averageDesiredChanges = averageDesiredChanges + desiredChanges;
    }
    //averageCost = averageCost / size;
    outputBiases.close();
    hiddenBiases.close();
    outputWeights.close();
    hiddenWeights.close();
    desiredChanges.close();
    sample.close();
    averageDesiredChanges = averageDesiredChanges / size;

    return averageDesiredChanges;
}

void Network::trainingEpoch(std::vector<TrainingExample> trainingSamples, int batchSize, int batchAmount){

    log("Randomizando trainingSamples");
    std::random_shuffle(trainingSamples.begin(), trainingSamples.end());

    TrainingExample miniBatches[batchAmount][batchSize];

    // popula os mini-batches
    int k = 0;
    for (int i = 0; i < batchAmount; i++){
        for (int j = 0; j < batchSize; j++){
            miniBatches[i][j] = trainingSamples[k++]; 
        }
    }
        
    Data changes;

    // executa os treinos e faz as mudancas
    // para cada minibatch
    log("Comecando a executar os minibatches");
    for (int i = 0; i < batchAmount; i++){

        log("Iniciando minibatch evaluation");
        changes = minibatchEvaluation(miniBatches[i], batchSize);

        log("Salvando mudanças do minibatch evaluation");
        output.weight = output.weight + changes.weightsOutput;
        output.bias = output.bias + changes.biasesOutput;
        hidden.weight = hidden.weight + changes.weightsHidden;
        hidden.bias = hidden.bias + changes.biasesHidden;
    }
    changes.close();
    for (int i = 0; i < batchAmount; i++){
        for (int j = 0; j < batchSize; j++){
            miniBatches[i][j].close(); 
        }
    }
}

// Retorna a quantidade de acertos da rede neural para um conjunto
// de test samples
int Network::testEpoch(std::vector<TrainingExample> testSamples){
    int correctAnswerCnt = 0;

    for (TrainingExample test : testSamples){

        feedfoward(test.imageData);

        int answer;
        double higher = output.value.values[0][0];

        for (int i = 0; i < 10; i++) {
            if (output.value.values[i][0] > higher) {
                answer = i;
            }
        }
        if (answer == test.representedValue) {
            correctAnswerCnt++;
        }
    }
    return correctAnswerCnt;
}

void Network::close(){
    hidden.close();
    output.close();
    input.close();
}