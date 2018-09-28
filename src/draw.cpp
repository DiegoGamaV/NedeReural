#include "draw.h"

Narray desenhar(){
    drawing = false;
    img = cv::Mat(28, 28, CV_8UC3, cv::Scalar(0,0,0));
    cv::namedWindow("Desenhe");
    cv::setMouseCallback("Desenhe", draw_circle);
    while(1){
        cv::imshow("Desenhe",img);
        int k = cv::waitKey(1) & 0xFF;
        if (k == 's'){
            Narray ret(28 * 28, 1);
            for(int i = 0; i < 28; i++){
                for(int j = 0; j < 28; j++){
                    ret.values[i * 28 + j][0] = img.at<uchar>(cv::Point(i, j)) / 255.0;
                }
            }
            cv::destroyAllWindows();
            return ret;
        }
    }
}

void draw_circle(int event, int x, int y, int flags, void* param){
    if (event == cv::EVENT_LBUTTONDOWN){
        drawing = true;
    }else if(event == cv::EVENT_MOUSEMOVE){
        if (drawing == true)
            cv::circle(img,cv::Point(x,y),1,cv::Scalar(255,255,255),-1, cv::LINE_AA);
    }else if(event == cv::EVENT_LBUTTONUP){
        drawing = false;
        cv::circle(img,cv::Point(x,y),1,cv::Scalar(255,255,255),-1, cv::LINE_AA);
    }
}
