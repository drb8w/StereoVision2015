#ifndef SELECTDISPARITY
#define SELECTDISPARITY

#include <stdio.h>
#include <opencv2\opencv.hpp>

void selectDisparity(cv::Mat &displayLeft, cv::Mat &displayRight, std::vector<cv::Mat> &costVolumeLeft, std::vector<cv::Mat> &costVolumeRight, int scaleDispFactor=16);

#endif