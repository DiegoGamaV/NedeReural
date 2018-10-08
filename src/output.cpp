#include "output.h"
#include <iostream>

//Recebe o numero atual e a chance entre 0 e 1 de ser o mesmo
//Retorna uma string formatada do numero em porcentagem
std::string Output::toPercentage(int index, double number) {
    char ret[100];
    int n = sprintf(ret, "[%d - %.2lf%%]", index, number);
    return ret;
}

//Recebe os valores de ativacao do layer
//Retorna as porcentagens
std::string Output::print(Narray activations_values) {
    std::string ret;
    double bestSigmoid = -1;
    int retNumber = 0;
    double total = 0.0;

    for (int i = 0; i < activations_values.row; i++) {
        total += activations_values.at(i, 0);
    }

    for(int i = 0; i < activations_values.row; i++) {
        if(activations_values.at(i, 0) > bestSigmoid) {
            bestSigmoid = activations_values.at(i, 0);
            retNumber = i;
        }

        ret += toPercentage(i, activations_values.at(i, 0) * 100.0 / total);

        if(i <= 8) {
            ret += ", ";
        }
    }

    ret += "\n Resposta definitiva: " + toPercentage(retNumber, bestSigmoid * 100.0 / total);

    return ret;
}
