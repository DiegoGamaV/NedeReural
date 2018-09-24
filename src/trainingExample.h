#pragma once

#include "doriNum.h"

// Estrutura que representa um exemplo de treino, o par
// (matriz de valores, inteiro representado)
struct TrainingExample {

    // Matriz de dados da imagem. A matriz tem
    // valores que representam os tons de cinza
    // da imagem, onde cada espaco imageData[i][j]
    // representa um pixel da imagem. Os valores
    // variam no intervalo [0.0, 1.0], tal que
    // 0.0 representa preto e 1.0 representa o
    // branco.
    Narray imageData;

    // O valor entre 0 e 9 que a imagem representa.
    unsigned int representedValue;

    // Construtor do exemplo de treino.
    TrainingExample(Narray &data, unsigned int _representedValue){
        //TODO
    }
    TrainingExample(){
        //TODO
    }
    
};