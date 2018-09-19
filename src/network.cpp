#include "doriNum.h"

// Recebe o output como uma matriz
// coluna e o numero esperado
// de uma interpretacao correta e avalia o custo
// do treinamento associado a essa resposta
double quadraticCost(Narray output, int expected){

    double totalCost = 0;
    
    unsigned int size = output.row;
    Narray expectedOutput = buildExpectedOutput();
    Narray costs = expectedOutput - output;

    double sumOfCosts = sumColunmValues(costs);
    totalCost = sumOfCosts * sumOfCosts;

    return totalCost;
}

// Cria uma matriz coluna que sera
// a melhor resposta possivel
Narray buildExpectedOutput(unsigned int size, int expected){
    Narray expectedOutput = Narray(size, 1);

    for (int i = 0; i < size; i++) {
        expectedOutput.values[i][0] = 0;
    }
    expectedOutput.values[expected][0] = 1;

    return expectedOutput;
}


// Soma todos os valores da matriz coluna de custos
double sumCosts(Narray costs){
    double sum = 0;

    for (int j = 0; j < costs.row; j++) {
        double val = costs.values[i][0];
        sum += val;
    }
    return sum;
}



