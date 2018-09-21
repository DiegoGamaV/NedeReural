#include "layer.h"

// implementacao do construtor
Layer::Layer(std::string path, unsigned int _numNeuronsThis, unsigned int _numNeuronsPrevious){
    InputReader archive;
    if(archive.empty(path) ){
        weight = archive.readMatrix(path, _numNeuronsThis, _numNeuronsPrevious);
    }else weight = Narray(_numNeuronsThis, _numNeuronsPrevious);

    if(archive.empty(path)){
        bias = archive.readMatrix(path, _numNeuronsThis, 1);
    }else bias = Narray(_numNeuronsThis, 1);
}

Layer::Layer() {
    weight = Narray();
    bias = Narray();
}

// Funcao de ativacao dos neuronios da camada
Narray Layer::activate(Narray previousValues){
    for(int i = 0; i < previousValues.colunm; i++){
        previousValues = ((weight.getColunm(i)*previousValues.getRow(i)) + bias.values[i][0])(sigmoid);
    }

    return previousValues;
}