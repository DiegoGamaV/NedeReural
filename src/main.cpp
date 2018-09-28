#include "netFlow.h"
#include "debug.h"
#include "logger.h"

enum Type
{
    TRAIN,
    EXEC
};

void printUsage();
Type readInput(std::string str);
void treatInvalidInput(std::string str);
void checkVerbosity(std::string);

int main(int argc, char* argv[]){

    log("Comecando a execucao do programa");

    if (argc < 2) {
        printUsage();
        exit(1);
    }

    std::string str(argv[1]);
    treatInvalidInput(str);
    Type type = readInput(str);

    if (argc >= 3) {
        std::string str2(argv[2]);
        checkVerbosity(str2);
    }

    std::string answer = "";
    
    switch (type)
    {
        case TRAIN:
            /* Codigo para treinamento da rede */
            log("Indo para execucao de treino");
            train();
            break;
            
        case EXEC:
            /* Codigo para execucao normal da rede */
            log("Indo para execucao padrao");
            answer = execute();
            break;

        default:
            break;
    }

    std::cout << answer << std::endl;

    return 0;
}

Type readInput(std::string str) {
    Type typeOfExecution;

    if (str == "--exec") {
        typeOfExecution = EXEC;
    } else if (str == "--train") {
        typeOfExecution = TRAIN;
    }

    return typeOfExecution;
}

void treatInvalidInput(std::string str){
    bool error = false;
    if ((str != "--exec") && (str != "--train")) {
        error = true;
    }
    if (error) {
        printUsage();
        exit(1);
    }
}

void checkVerbosity(std::string str){
    if (str == "--v") {
        setVerbosity(1);
    }
}

void printUsage() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  ./run (--train | --exec)" << std::endl;
    std::cout << "  ./run (--train | --exec) (--v)" << std::endl;
}