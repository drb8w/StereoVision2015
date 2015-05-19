//#define TEST
// OpenCV_Test.cpp : Defines the entry point for the console application.
// Author:  Christian Brändle
//			Sebastian Metzler 

#include "stdafx.h"
#include <stdio.h> 
#include <string> 
#include <list>
#include <vector>
#include <cmath>
#include <opencv2\opencv.hpp> 

#include "ComputeCostVolume.h"
#include "SelectDisparity.h"
#include "StringExtensions.h"

using namespace cv;

int main(int argc, char *argv[])
{
	// ===============================================================
	// Load Images
	// ===============================================================

	string imgLeftPath = "./tsukuba_left.png";
	ImgPath(argc, argv, 1, imgLeftPath);
	
	string imgRightPath = "./tsukuba_right.png";
	ImgPath(argc, argv, 2, imgRightPath);
	
	Mat imgLeft = loadImage(imgLeftPath.c_str());
	Mat imgRight = loadImage(imgRightPath.c_str());

	// ===============================================================
	// Convert Images 
	// ===============================================================

	Mat imgLeftGray(imgLeft.rows,imgLeft.cols, CV_8U);
	convertToGrayscale(imgLeft, imgLeftGray); 
	Mat imgRightGray(imgRight.rows,imgRight.cols, CV_8U);
	convertToGrayscale(imgRight, imgRightGray); 

	// ===============================================================
	// Compute Cost Volume 
	// ===============================================================
	
	vector<Mat> *costVolumeLeft = new vector<Mat>();
	vector<Mat> *costVolumeRight = new vector<Mat>();
	int windowSize=5;
	int maxDisp=15;
	computeCostVolume(imgLeftGray, imgRightGray, *costVolumeLeft, *costVolumeRight, windowSize, maxDisp);

#ifdef TEST
	for(int i=0; i<costVolumeLeft->size();i++)
	{
		char intStr[10];
		itoa (i,intStr,10);
		string str = "Display window " + string(intStr);

		namedWindow( str, WINDOW_AUTOSIZE );// Create a window for display.
		imshow( str, (*costVolumeLeft)[i] ); 

		imwrite("./tsukuba_left_cost_volume"+ string(intStr) +".png", (*costVolumeLeft)[i]);
	}
#endif

	// ===============================================================
	// Select Disparity 
	// ===============================================================
	
	Mat displayLeft(imgLeft.rows,imgLeft.cols, CV_8U, (uchar)255);
	Mat displayRight(imgRight.rows,imgRight.cols, CV_8U, (uchar)255);
	int scaleDispFactor = 16;

	selectDisparity(displayLeft, displayRight, *costVolumeLeft, *costVolumeRight, scaleDispFactor);

	// ===============================================================
	// Write Displays 
	// ===============================================================

	string displayLeftStr = imgLeftPath.substr(0,imgLeftPath.size()-4) + "_display.png";
	imwrite(displayLeftStr, displayLeft);
	string displayRightStr = imgRightPath.substr(0,imgRightPath.size()-4) + "_display.png";
	imwrite(displayRightStr, displayRight);
	
	return 0;
}



