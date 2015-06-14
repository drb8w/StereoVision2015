#ifndef AGGREGATECOSTVOLUME
#define AGGREGATECOSTVOLUME

#include <stdio.h> 
#include <opencv2\opencv.hpp>

void aggregateCostVolume(const cv::Mat &imgLeft, const cv::Mat &imgRight, std::vector<cv::Mat> &costVolumeLeft, std::vector<cv::Mat> &costVolumeRight, int r, double eps);


#endif