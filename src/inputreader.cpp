#include "inputreader.h"

// transforma os valores no arquivo em um Narray
Narray InputReader::readMatrix(std::string path, int row, int column){
    std::ifstream archive (path);

    Narray ret = Narray(row, column);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            archive >> ret.values[i][j];
        }
    }
    archive.close();
    return ret;
}

//pega todos os arquivos presentes no diretorio "path"
std::vector<std::string> InputReader::getDirectory(std::string path){
    DIR *dr;
    struct dirent *drnt;
    std::vector<std::string> ret;

    dr = opendir(path.c_str());
    if(dr){
        while((drnt = readdir(dr)) != NULL){
            ret.push_back(path + "/" + drnt->d_name);
        }
    }else std::cout << "Directory not found :(\n";

    return ret;
}

// verifica se o arquivo esta vazio
bool InputReader::empty(std::string path){
    std::ifstream archive (path);
    return archive.tellg() == 0;
}

// Esvazia o arquivo recebido
void clear(std::string path){
    std::ofstream archive (path);

    archive << " ";

    archive.close();
}

// Preenche o arquivo com os valores da matriz
void InputReader::fillArchive(std::string path, Narray content){
    std::ofstream archive (path);

    for(int i = 0; i < content.row; i++){
        for(int j = 0; j < content.colunm; j++){
            archive << content.values[i][j];
            archive << " ";
        }
        archive << "\n";
    }

    archive.close();
}

// Cria um exemplo de treino "TrainingExample"
TrainingExample InputReader::createTrainingExample(int foreseen, Narray activity){
    TrainingExample ret = TrainingExample(activity, foreseen);

    return ret;
}

// Recebe o arquivo
// Retorna o valor previsto do arquivo
int InputReader::getforeseen(std::string path){
    bool number = false;
    for(int i = 0; i < path.size(); i++){
        if(path[i] == '-') number = true;

        if(number) return path[i]-'0';
    }
}

// Faz um vector de treinos
// Retorna o vector criado
std::vector<TrainingExample> InputReader::makeTrainings(std::string path, int row, int column){
    std::vector<std::string> archive = getDirectory(path);

    std::vector<TrainingExample> ret;
    for(int i = 0; i < archive.size(); i++){
        TrainingExample aux = createTrainingExample(getforeseen(archive[i]) , readMatrix(archive[i], row, column));
        ret.push_back(aux);
    }

    return ret;
}

