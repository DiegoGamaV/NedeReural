#pragma once

#include "doriNum.h"
#include <vector>

struct Output {
    
    //Retorna uma string do numero formatado em porcentagem
    std::string toPercentage(int index, double number);

    //Le os valores de ativacao da Layer
    //Retorna as porcentagens e a resposta final
    std::string print(Narray activations_values);
};