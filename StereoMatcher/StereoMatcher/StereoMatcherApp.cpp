//#define TEST
// OpenCV_Test.cpp : Defines the entry point for the console application.
// Author:  Christian Brändle
//			Sebastian Metzler 

#include "stdafx.h"
#include <stdio.h> 
#include <math.h>       /* floor */
#include <opencv2\opencv.hpp> 

#include "ComputeCostVolume.h"
#include "SelectDisparity.h"

using namespace cv;

int main(int argc, char *argv[])
{
	
	Mat imgLeft = loadImage("./tsukuba_left.png");
	Mat imgRight = loadImage("./tsukuba_right.png");

	Mat imgLeftGray(imgLeft.rows,imgLeft.cols, CV_8U);
	convertToGrayscale(imgLeft, imgLeftGray); 
	Mat imgRightGray(imgRight.rows,imgRight.cols, CV_8U);
	convertToGrayscale(imgRight, imgRightGray); 
	
	vector<Mat> *costVolumeLeft = new vector<Mat>();
	vector<Mat> *costVolumeRight = new vector<Mat>();
	int windowSize=5;
	int maxDisp=15;
	computeCostVolume(imgLeftGray, imgRightGray, costVolumeLeft, costVolumeRight, windowSize, maxDisp);

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
	
	return 0;
}



