#include "layer.h"

// implementacao do construtor
Layer::Layer(unsigned int _numNeuronsThis, unsigned int _numNeuronsPrevious){
    weight = Narray(_numNeuronsThis, _numNeuronsPrevious);

    bias = Narray(1, _numNeuronsThis);
}


// ativa os feedforwards de cada layer e 
// retornar o array de ativação final.
Narray feedfoward(Narray a){
    for(int i = 0; i < colunm; i++){
        a << sigmoid(weight.getColunm(i)*a.values[0][i] + bias.values[0][i]);
    }

    return a;
}