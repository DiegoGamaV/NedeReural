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

    void clear(std::string path);

    void fillArchive(std::string path, Narray value);

    int InputReader::getforeseen(std::string path);
    
    TrainingExample createTrainingExample(int foreseen, Narray activity);

    std::vector<TrainingExample> makeTrainings(std::string path, int row, int column);
};