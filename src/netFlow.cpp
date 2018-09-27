#include "netFlow.h"
#include "debug.h"

const unsigned int NUM_PIXELS = 784;
const unsigned int SIZE_HIDDEN = 16;
const std::string DATA_PATH = "./data/info.data";
const std::string INPUT_PATH = "./input/image.txt";
const std::string TRAIN_PATH = "./training/train_set/";
const std::string TEST_PATH = "./training/test_set/";
const int BATCH_SIZE = 10;
const int TRAIN_SIZE = 10000;
const int EPOCH_AMOUNT = 100; // EPOCH_AMOUNT * BATCH_SIZE <= 60000

Network network;

bool existsFile(std::string path);
void initializeNetwork(InputReader);
std::vector<TrainingExample> computeReducedTrain(std::vector<TrainingExample> a);

std::string execute() {

    InputReader reader;
    Output output;

    initializeNetwork(reader);

    /* Ler arquivo */
    if (!existsFile(INPUT_PATH)) {
        throw "No file " + INPUT_PATH;
    }

    // Criar matriz coluna que representa as ativacoes
    // de entrada da rede neural
    Narray image = reader.readMatrix(INPUT_PATH, NUM_PIXELS, 1);

    network.feedfoward(image);

    std::string answer = output.print(network.output.value);

    return answer;
}

void train(){
    
    InputReader reader;
    Output output;

    initializeNetwork(reader);

    std::vector<TrainingExample> trainSet;
    std::vector<TrainingExample> testSet;
    std::vector<TrainingExample> reducedTrainSet;

    /* Computar os conjuntos de treino e teste */
    trainSet = reader.makeTrainings(TRAIN_PATH, NUM_PIXELS, 1);
    testSet = reader.makeTrainings(TEST_PATH, NUM_PIXELS, 1);
    reducedTrainSet = computeReducedTrain(trainSet);

    int batchAmount = reducedTrainSet.size() / BATCH_SIZE;

    /* Executar e testar epocas de treino */
    for (int i = 0; i < EPOCH_AMOUNT; i++) {
        
        network.trainingEpoch(reducedTrainSet, BATCH_SIZE, batchAmount);

        int correctCnt = network.testEpoch(testSet);
        int total = reducedTrainSet.size();

        std::cout << "Epoch " << i << correctCnt << "/" << total << std::endl;
    }
}

std::vector<TrainingExample> computeReducedTrain(std::vector<TrainingExample> a){
    std::vector<TrainingExample> reducedTrainSet;

    for (int i = 0; i < TRAIN_SIZE; i++){
        reducedTrainSet.push_back(a[i]);
    }

    return reducedTrainSet;
}

bool existsFile(std::string path) {
    InputReader ir;
    return !ir.empty(path);
}

void initializeNetwork(InputReader reader){
    /* Checar casos de execucao */
    bool isFirstExec = !existsFile(DATA_PATH);

    if (isFirstExec) {
        network = Network(NUM_PIXELS, SIZE_HIDDEN);
    } else {
        Data info = reader.fileToData(DATA_PATH); 
        network = Network(NUM_PIXELS, SIZE_HIDDEN, info);
    }
}