#include "binaryReader.h"

binaryReader::binaryReader(std::string image_path, std::string label_path){
    image.open(image_path, std::ifstream::in);
    label.open(label_path, std::ifstream::in);
}

std::vector <std::pair<Narray, byte > > binaryReader::allData(){
    std::vector <std::pair<Narray, byte > > ret;
    buffer size;
    label.read(size.chars, 4);label.read(size.chars, 4);
    std::vector < byte > labels;
    byte l;
    for(register int i = 0; i < size.integer; i++){
        label.read(&l, 1);
        labels.push_back(l);
    }
    buffer rows, colunms;
    image.read(size.chars, 4);image.read(size.chars, 4);
    image.read(rows.chars, 4);
    image.read(colunms.chars, 4);
    std::vector < Narray > Narrays;
    for(int a = 0; a < size.integer; a++){
        Narray temp = Narray(rows.integer, colunms.integer);
        for(register int i = 0; i < rows.integer; i++){
            for(register int j = 0; j < colunms.integer; j++){
                image.read(&l, 1);
                temp.values[i][j] = l/255.0;
            }
        }
        Narrays.push_back(temp);
    }
    for(register int i = 0; i < size.integer; i++){
        ret.push_back({Narrays[i], labels[i]});
    }
    return ret;
}