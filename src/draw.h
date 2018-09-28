#pragma once

#include <opencv2/opencv.hpp>
#include "doriNum.h"

bool drawing;
cv::Mat img;

Narray desenhar();

void draw_circle(int event, int x, int y, int flags, void* param);