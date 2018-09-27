#include "netFlow.h"

enum Type
{
    TRAIN,
    EXEC
};

void printUsage();
Type readInput(std::string str);
void treatInvalidInput(std::string str);

int main(int argc, char* argv[]){

    if (argc < 2) {
        printUsage();
        exit(1);
    }

    std::string str(argv[1]);
    treatInvalidInput(str);
    Type type = readInput(str);

    std::string answer;
    
    switch (type)
    {
        case TRAIN:    
            /* Codigo para treinamento da rede */         
            break;
            
        case EXEC:
            /* Codigo para execucao normal da rede */
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

void printUsage() {
    std::cout << "Usage:" << std::endl;
    std::cout << "  ./run (--train | --exec)" << std::endl;
}