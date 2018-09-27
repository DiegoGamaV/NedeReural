#include "netFlow.h"
#include "debug.h"

const unsigned int NUM_PIXELS = 784;
const unsigned int SIZE_HIDDEN = 16;
const std::string DATA_PATH = "./data/info.data";
const std::string INPUT_PATH = "./input/image.txt";
Network network;

bool existsFile(std::string path);

std::string execute() {

    InputReader reader;
    Output output;

    /* Checar casos de execucao */
    bool isFirstExec = !existsFile(DATA_PATH);

    if (isFirstExec) {
        network = Network(NUM_PIXELS, SIZE_HIDDEN);
    } else {
        Data info = reader.fileToData(DATA_PATH); 
        network = Network(NUM_PIXELS, SIZE_HIDDEN, info);
    }

    /* Ler arquivo */
    if (!existsFile(INPUT_PATH)) {
        throw "No file " + INPUT_PATH;
    }

    // Criar matriz coluna que representa as ativacoes
    // de entrada da rede neural
    Narray image = reader.readMatrix(INPUT_PATH, NUM_PIXELS, 1);

    network.feedfoward(image);

    DEBUG_MATRIX(network.output.zeta);
    std::string answer = output.print(network.output.value);

    return answer;
}

std::string train(){

}

bool existsFile(std::string path) {
    InputReader ir;
    return !ir.empty(path);
}