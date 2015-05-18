#ifndef COMPUTECOSTVOLUME
#define COMPUTECOSTVOLUME

#include <stdio.h>
#include <opencv2\opencv.hpp>

cv::Mat loadImage(char* imagepath);

void convertToGrayscale(const cv::Mat &img, cv::Mat &imgGray);

void computeCostVolume(const cv::Mat &imgLeft, const cv::Mat &imgRight, std::vector<cv::Mat> *costVolumeLeft, std::vector<cv::Mat> *costVolumeRight, int windowSize=5, int maxDisp=15);

#endif