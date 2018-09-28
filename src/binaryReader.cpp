#include "binaryReader.h"

void gmbARUMAITO(buffer &size);

binaryReader::binaryReader(std::string image_path, std::string label_path){
    image.open(image_path, std::ifstream::in);
    label.open(label_path, std::ifstream::in);
}

std::vector <std::pair<Narray, byte > > binaryReader::allData(){
    std::vector <std::pair<Narray, byte > > ret;
    buffer size;
    label.read(size.chars, 4);
    gmbARUMAITO(size);
    label.read(size.chars, 4);
    gmbARUMAITO(size);
    std::vector < byte > labels;
    byte l;
    for(register int i = 0; i < size.integer / 50; i++){
        label.read(&l, 1);
        labels.push_back(l);
    }
    buffer rows, colunms;
    image.read(size.chars, 4);image.read(size.chars, 4);gmbARUMAITO(size);
    image.read(rows.chars, 4);gmbARUMAITO(rows);
    image.read(colunms.chars, 4);gmbARUMAITO(colunms);
    std::vector < Narray > Narrays;
    for(int a = 0; a < size.integer / 50; a++){
        Narray temp = Narray(colunms.integer * rows.integer, 1);
        for(register int i = 0; i < rows.integer; i++){
            for(register int j = 0; j < colunms.integer; j++){
                image.read(&l, 1);
                temp.values[i * colunms.integer + j][0] = ((int)((unsigned char)l))/255.0;
            }
        }
        Narrays.push_back(temp);
    }
    for(register int i = 0; i < size.integer / 50; i++){
        ret.push_back({Narrays[i], labels[i]});
    }
    image.close();
    label.close();
    return ret;
}

void gmbARUMAITO(buffer &size){
    byte aux = size.chars[3];
    size.chars[3] = size.chars[0];
    size.chars[0] = aux;
    aux = size.chars[2];
    size.chars[2] = size.chars[1];
    size.chars[1] = aux;
}