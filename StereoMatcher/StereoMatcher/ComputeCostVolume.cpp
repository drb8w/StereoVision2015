//#define TEST
#include "ComputeCostVolume.h"

#include "stdafx.h"
#include <stdio.h> 
#include <math.h>
#include <opencv2\opencv.hpp> 

using namespace cv;

Mat loadImage(char* imagepath)
{
	Mat image = imread(imagepath);//, CV_LOAD_IMAGE_COLOR);
	return image;
}

void convertToGrayscale(const Mat &img, Mat &imgGray)
{
	for(int rowNr = 0; rowNr < img.rows; rowNr++ )
	{
		for(int columnNr = 0; columnNr < img.cols; columnNr++ )
		{
			int y = rowNr; // see OpenCV userguide
			int x = columnNr;

			Vec3b intensity = img.at<Vec3b>(y, x);
			uchar blue = intensity.val[0];
			uchar green = intensity.val[1];
			uchar red = intensity.val[2];
			// formula from script
			uchar luminance = 0.21*red + 0.72*green + 0.07*blue;
			imgGray.at<uchar>(y, x) = luminance;
		}
	}
}

void computeCostVolume(const Mat &imgLeft, const Mat &imgRight, vector<Mat> *costVolumeLeft, vector<Mat> *costVolumeRight, int windowSize=5, int maxDisp=15)
{	
	// assumption: windowSize odd
	int windowOffset = floor((float)(windowSize/2));

	for(int disp=0; disp<=maxDisp; disp++)
	{
		// cleared image
#ifndef TEST
		Mat imgCostLeft(imgLeft.rows,imgLeft.cols, CV_32FC1, double(0));
#else
		Mat imgCostLeft(imgLeft.rows,imgLeft.cols, CV_8U, double(0));
#endif
		costVolumeLeft->push_back(imgCostLeft);
#ifndef TEST
		Mat imgCostRight(imgRight.rows,imgRight.cols, CV_32FC1, double(0));
#else
		Mat imgCostRight(imgRight.rows,imgRight.cols, CV_8U, double(0));
#endif
		costVolumeRight->push_back(imgCostRight);
		for(int rowNr = windowOffset; rowNr < imgLeft.rows-windowOffset; rowNr++ )
		{
			for(int columnNr = windowOffset + disp; columnNr < imgLeft.cols-windowOffset; columnNr++ )
			{
				// leftwindow: rowNr, columnNr
				// rightwindow: rowNr, columnNr - disp
				
				// generate comparisonwindow
				// -------------------------
				// TODO: use sliding window technique
				float SAD_p_d = 0;
				for(int u=rowNr-windowOffset; u<rowNr+windowOffset; u++)
					for(int v=columnNr-windowOffset; v<columnNr+windowOffset; v++)
						SAD_p_d += abs(imgLeft.at<uchar>(u,v) - imgRight.at<uchar>(u,v-disp));
#ifdef TEST
				SAD_p_d /= windowSize*windowSize;
#endif
				// -------------------------
				//
#ifndef TEST
				imgCostLeft.at<float>(rowNr, columnNr) = SAD_p_d;
				imgCostRight.at<float>(rowNr, columnNr - disp) = SAD_p_d;
#else
				imgCostLeft.at<uchar>(rowNr, columnNr) = SAD_p_d;
				imgCostRight.at<uchar>(rowNr, columnNr - disp) = SAD_p_d;
#endif
			}
		}
	}
}
