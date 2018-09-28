#pragma once

#include "network.h"
#include "inputreader.h"
#include "output.h"
#include "binaryReader.h"
#include <opencv2/opencv.hpp>

// Funcao que executa a rede neural
// apenas para fornecer uma resposta
std::string execute();


// Funcao que executa a rede neural no
// modo de treinamento
void train();

void save(InputReader);

Narray desenhar();
void draw_circle(int event, int x, int y, int flags, void* param);