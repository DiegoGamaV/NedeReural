#include "netFlow.h"

// Network network;

const unsigned int NUM_PIXELS = 784;
const unsigned int SIZE_HIDDEN = 16;

bool existsConfigFiles();

void execute() {

    InputReader reader;
    /* Checar casos de execucao */
    bool isFirstExec = !existsConfigFiles();

    if (isFirstExec) {
        // TODO: Criar network inicial 
        Network network = Network(NUM_PIXELS, SIZE_HIDDEN);
    } else {
        Data info = reader.fileToData("/data/info.data"); 
        // TODO: Criar network passando um Data
        Network network = Network(NUM_PIXELS, SIZE_HIDDEN, info);
    }
    
    /* Checar se existe arquivo de configuracao,
       se existir, configurar network com base nas
       informacoes do arquivo */
}

bool existsConfigFiles() {
    InputReader ir;

    return !((ir.empty("./data"))      || 
    (ir.empty("./data/info.data")));
}

void train();