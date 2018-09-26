#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <dirent.h>
#include <string>
#include <vector>
#include "doriNum.h"
#include "trainingExample.h"

struct InputReader{

    // transforma os valores no arquivo em um Narray
    Narray readMatrix(std::string path, int line, int column);    

    //pega todos os arquivos presentes no diretorio "path"
    std::vector<std::string> getDirectory(std::string path);

    // verifica se o arquivo esta vazio
    bool empty(std::string path);

    // esvazia o arquivo
    void clear(std::string path);

    // preenche o arquivo
    void fillArchive(std::string path, Narray value);

    // pega o previsto
    int getforeseen(std::string path);
    
    // cria os exemplos de treino
    TrainingExample createTrainingExample(int foreseen, Narray activity);

    // faz o vector de exemplos de treino
    std::vector<TrainingExample> makeTrainings(std::string path, int row, int column);
};