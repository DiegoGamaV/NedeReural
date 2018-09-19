#include "layer.h"

// implementacao do construtor
Layer::Layer(unsigned int _numNeuronsThis, unsigned int _numNeuronsPrevious){
    if(empty("arquivo com o peso") ){
        weight = readMatrix("arquivo com o peso", _numNeuronsThis, _numNeuronsPrevious);
    }else weight = Narray(_numNeuronsThis, _numNeuronsPrevious);

    if(empty("arquivo com a bias")){
        bias = readMatrix("arquivo com a bias", _numNeuronsThis, 1);
    }else bias = Narray(_numNeuronsThis, 1);
}


// Funcao de ativacao dos neuronios da camada
Narray activate(Narray a){
    for(int i = 0; i < colunm; i++){
        a << sigmoid(weight.getColunm(i)*a.values[i][0] + bias.values[i][0]);
    }

    return a;
}