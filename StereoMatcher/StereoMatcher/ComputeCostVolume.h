#ifndef COMPUTECOSTVOLUME
#define COMPUTECOSTVOLUME

#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <string.h> 

cv::Mat loadImage(const char* imagepath);

std::vector<cv::Mat> * loadImages(std::string &path, std::string &fileName, std::string &fileSuffix, int frameNo, int nrDigits=4);

void convertToGrayscale(const cv::Mat &img, cv::Mat &imgGray);

void computeCostVolume(const cv::Mat &imgLeft, const cv::Mat &imgRight, std::vector<cv::Mat> &costVolumeLeft, std::vector<cv::Mat> &costVolumeRight, int windowSize=5, int maxDisp=15);

#endif