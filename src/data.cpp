#include "data.h"


Data::Data(Narray &hiddenWeights, Narray &outputWeights, Narray &hiddenBiases, Narray &outputBiases){
    //TODO
}

Data::Data(){
    //TODO
}

// Somar datas
Data Data::operator+ (const Data &a){

    Data ret = Data();
    ret.weightsHidden = weightsHidden + a.weightsHidden;
    ret.weightsOutput = weightsOutput + a.weightsOutput;
    ret.biasesOutput = biasesOutput + a.biasesOutput;
    ret.biasesHidden = biasesHidden + a.biasesHidden;

    return ret;
}