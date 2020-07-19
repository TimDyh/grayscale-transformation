#include <iostream>
#include <opencv2/opencv.hpp>
#include "hist.hpp"

using namespace std;
using namespace cv;

int main(int argc, const char *argv[]) {
    Mat srcImg = imread("images/lena.bmp", 0);
    Mat dstImg;
    
    Mat srcHist;
    Mat dstHist;
    
    getHist(srcImg, srcHist);
    imshow("src", srcImg);
    imshow("src histogram", srcHist);
    
    equalizeHist(srcImg, dstImg);
    // linearTransform(srcImg, dstImg, 3.2, -350.0);
    
    getHist(dstImg, dstHist);
    imshow("dst", dstImg);
    imshow("dst histogram", dstHist);
    
    waitKey(0);
    return 0;
}
