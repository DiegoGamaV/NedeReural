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

    Narray outputError(output.numNeuronsThis, 1);

    log("Calculando o vetor de erro da camada Output");    
    outputError = hadamard((output.value - expected), output.zeta(derivateSigmoid)); 

    Narray hiddenError(hidden.numNeuronsThis, 1);

    log("Calculando o vetor de erro da camada Hidden");
    hiddenError = hadamard((output.weight.transposta() * outputError), hidden.zeta(derivateSigmoid));

    log("Computando as mudancas na output desejadas para este treino");
    data.weightsOutput = outputError * hidden.value.transposta();
    data.biasesOutput = outputError;

    log("Computando as mudancas na hidden desejadas para este treino");

    data.weightsHidden = hiddenError * input.value.transposta();
    data.biasesHidden = hiddenError;
    
    log("Terminando de computar backpropagation");
    return data;
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
        log("Iniciando feedfoward de um sample");
        feedfoward(sample.imageData);

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

void Network::trainingEpoch(std::vector<TrainingExample> trainingSamples, int batchSize, int batchAmount, double rate){

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
        output.weight = output.weight - rate * changes.weightsOutput;
        output.bias = output.bias - rate * changes.biasesOutput;
        hidden.weight = hidden.weight - rate * changes.weightsHidden;
        hidden.bias = hidden.bias - rate * changes.biasesHidden;
    }
    // changes.close();
    // for (int i = 0; i < batchAmount; i++){
    //     for (int j = 0; j < batchSize; j++){
    //         miniBatches[i][j].close(); 
    //     }
    // }
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