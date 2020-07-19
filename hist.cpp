#include "hist.hpp"

void getHist(const Mat &img, Mat &histImg) {
    Mat hist;
    int dims = 1;
    float range[] = {0, 256};
    const float *ranges[] = {range};
    int size = 256;
    int channels = 0;
    calcHist(&img, 1, &channels, Mat(), hist, dims, &size, ranges);
    
    double minVal = 0;
    double maxVal = 0;
    minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    
    histImg.create(size, size, CV_8U);
    for (int i = 0; i < size; i++) {
        float binVal = hist.at<float>(i);
        int height = cvRound(binVal * 255 / maxVal);
        line(histImg, Point(i, size - 1), Point(i, size - height), Scalar(255));
    }
}

void equalizeHist(const Mat &srcImg, Mat &dstImg) {
    dstImg.create(srcImg.size(), srcImg.type());
    
    uchar *srcImgData = srcImg.data;
    uchar *dstImgData = dstImg.data;
    
    int *hist = new int[256];
    memset(hist, 0, 256 * sizeof(int));
    int pixNum = srcImg.cols * srcImg.rows;
    for (int i = 0; i < pixNum; i++)
        hist[srcImgData[i]]++;
    for (int i = 1; i < 256; i++)
        hist[i] += hist[i-1];
    
    uchar *map = new uchar[256];
    for (int i = 0; i < 256; i++)
        map[i] = cvRound((double)hist[i] / pixNum * 255);
    
    for (int i = 0; i < pixNum; i++)
        dstImgData[i] = map[srcImgData[i]];
}

void linearTransform(const Mat &srcImg, Mat &dstImg, double k, double b) {
    dstImg.create(srcImg.size(), srcImg.type());
    
    uchar *srcImgData = srcImg.data;
    uchar *dstImgData = dstImg.data;
    
    uchar *map = new uchar[256];
    for (int i = 0; i < 256; i++) {
        int temp = cvRound(k * i + b);
        if (temp > 255) temp = 255;
        else if (temp < 0) temp = 0;
        map[i] = temp;
    }
    
    int pixNum = srcImg.cols * srcImg.rows;
    for (int i = 0; i < pixNum; i++)
        dstImgData[i] = map[srcImgData[i]];
}
