#include "SelectDisparity.h"

#include "stdafx.h"
#include <stdio.h>
#include <math.h> 
#include <opencv2\opencv.hpp>

void _selectDisparity(cv::Mat &display, std::vector<cv::Mat> &costVolume)
{
	int maxDisp = costVolume.size();

	for(int disp=0; disp<=maxDisp; disp++)
		for(int rowNr = 0; rowNr < display.rows; rowNr++ )
			for(int columnNr = 0; columnNr < display.cols; columnNr++ )
				if (display.at<uchar>(rowNr, columnNr) > costVolume[disp].at<float>(rowNr, columnNr))
					display.at<uchar>(rowNr, columnNr) = (uchar)costVolume[disp].at<float>(rowNr, columnNr);
}

void _scaleDisplay(cv::Mat &display, int scaleDispFactor)
{
		for(int rowNr = 0; rowNr < display.rows; rowNr++ )
			for(int columnNr = 0; columnNr < display.cols; columnNr++ )
				display.at<uchar>(rowNr, columnNr) = display.at<uchar>(rowNr, columnNr) * scaleDispFactor;
}

void selectDisparity(cv::Mat &displayLeft, cv::Mat &displayRight, std::vector<cv::Mat> &costVolumeLeft, std::vector<cv::Mat> &costVolumeRight, int scaleDispFactor=16)
{
	// select min disparity per pixel
	_selectDisparity(displayLeft, costVolumeLeft);
	_selectDisparity(displayRight, costVolumeRight);
	
	// scale the result
	_scaleDisplay(displayLeft, scaleDispFactor);
	_scaleDisplay(displayRight, scaleDispFactor);


}


