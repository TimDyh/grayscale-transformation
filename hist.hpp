#ifndef hist_hpp
#define hist_hpp

#include <opencv2/opencv.hpp>

using namespace cv;

void getHist(const Mat &img, Mat &histImg);
void equalizeHist(const Mat &srcImg, Mat &dstImg);
void linearTransform(const Mat &srcImg, Mat &dstImg, double k, double b);

#endif /* hist_hpp */
