#include "layer.h"
#include "debug.h"

// implementacao do construtor
Layer::Layer(unsigned int _numNeuronsThis, unsigned int _numNeuronsPrevious){
    numNeuronsThis = _numNeuronsThis;
    numNeuronsPrevious = _numNeuronsPrevious;
    weight = Narray(_numNeuronsThis, _numNeuronsPrevious);
    bias = Narray(_numNeuronsThis, 1);
    value = Narray(_numNeuronsThis, 1);
    zeta = Narray(_numNeuronsThis, 1);
    weight.randomValues();
    bias.randomValues();
}

Layer::Layer() {
    weight = Narray();
    bias = Narray();
    zeta = Narray();
    value = Narray();
}

//preenche os valores de weight com os valores presentes em actual
void Layer::fillWeight(Narray &actual){
    if(actual.row == weight.row && actual.colunm == weight.colunm){
        weight = actual;
    }
}

//preenche os valores de bias com os valores presentes em actual
void Layer::fillBias(Narray &actual){
    if(actual.row == bias.row && actual.colunm == bias.colunm){
        bias = actual;
    }
}

//preenche os valores de value com os valores presentes em actual
void Layer::fillValue(Narray &actual){
    if(actual.row == value.row && actual.colunm == value.colunm){
        value = actual;
    }
}

// Funcao de ativacao dos neuronios da camada
Narray Layer::activate(Narray previousValues){
    zeta = (weight * previousValues) + bias;
    value = zeta(sigmoid);
    return value;
}

void Layer::close(){
    weight.close();
    bias.close();
    zeta.close();;
    value.close();;
}