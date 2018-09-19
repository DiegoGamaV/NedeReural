#include "layer.h"

// implementacao do construtor
Layer::Layer(unsigned int _numNeuronsThis, unsigned int _numNeuronsPrevious){
    weight = Narray(_numNeuronsThis, _numNeuronsPrevious);

    bias = Narray(_numNeuronsThis, 1);
}


// Funcao de ativacao dos neuronios da camada
Narray activate(Narray a){
    for(int i = 0; i < colunm; i++){
        a << sigmoid(weight.getColunm(i)*a.values[i][0] + bias.values[i][0]);
    }

    return a;
}