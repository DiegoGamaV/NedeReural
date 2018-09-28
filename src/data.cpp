#include "data.h"
#include "debug.h"


Data::Data(Narray _hiddenWeights, Narray _outputWeights, Narray _hiddenBiases, Narray _outputBiases){

    weightsHidden = Narray(_hiddenWeights);
//    weightsHidden <<= _hiddenWeights;

    weightsOutput = Narray(_outputWeights);
//    weightsOutput <<= _outputWeights;

    biasesHidden = Narray(_hiddenBiases);
//    biasesHidden <<= _hiddenBiases;

    biasesOutput = Narray(_outputBiases);
//    biasesOutput <<= _outputBiases;

}

Data::Data(){
    weightsHidden = Narray();
    weightsOutput = Narray();
    biasesHidden = Narray();
    biasesOutput = Narray();
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

// Dividir Data por escalar
Data Data::operator/ (const double &a){

    Data ret = Data();
    ret.weightsHidden = weightsHidden / a;
    ret.weightsOutput = weightsOutput / a;
    ret.biasesOutput = biasesOutput / a;
    ret.biasesHidden = biasesHidden / a;

    return ret;
}

void Data::zeroValues(){
    weightsHidden.zeroValues();
    weightsOutput.zeroValues();
    biasesHidden.zeroValues();
    biasesOutput.zeroValues();
}

void Data::close(){
    weightsHidden.close();
    weightsOutput.close();
    biasesHidden.close();
    biasesOutput.close();
}