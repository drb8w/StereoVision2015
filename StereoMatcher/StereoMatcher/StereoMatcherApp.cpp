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

#include <iostream>
using namespace std;

using namespace cv;

int main(int argc, char *argv[])
{
	// ===============================================================
	// Load Images
	// ===============================================================
	
	cout << "start matching" << endl;

	string imgNames[] = {"tsukuba", "venus", "teddy", "cones"};
	int maxDisps[] = {15, 19, 59, 59};
	int scales[] = {16, 8, 4, 4};

	for(int i=0; i<4; i++){

		//int i = 1;
		
		cout << imgNames[i] << endl;

		int windowSize=13;
		int maxDisp=maxDisps[i];
		int scaleDispFactor = scales[i];


		string imgLeftPath = "./testdata/stereo-pairs/"+ imgNames[i] + "/imL.png";
		ImgPath(argc, argv, 1, imgLeftPath);
	
		string imgRightPath = "./testdata/stereo-pairs/"+ imgNames[i] + "/imR.png";
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
		computeCostVolume(imgLeftGray, imgRightGray, *costVolumeLeft, *costVolumeRight, windowSize, maxDisp);



	#ifdef TEST
	
			cout << "showimg";
		for(int i=0; i<costVolumeLeft->size();i++)
		{
			char intStr[10];
			itoa (i,intStr,10);
		
			cout << i;
			string str = "Display window " + string(intStr);

			namedWindow( str, WINDOW_AUTOSIZE );// Create a window for display.
			imshow( str, (*costVolumeLeft)[i] ); 

			imwrite("./tsukuba_left_cost_volume"+ string(intStr) +".png", (*costVolumeLeft)[i]);
		}
			cout << "showimg end";
	#endif

		// ===============================================================
		// Select Disparity 
		// ===============================================================
	

		Mat displayLeft(imgLeft.rows,imgLeft.cols, CV_8U, (uchar)255);
		Mat displayRight(imgRight.rows,imgRight.cols, CV_8U, (uchar)255);

		selectDisparity(displayLeft, displayRight, *costVolumeLeft, *costVolumeRight, scaleDispFactor);

		// ===============================================================
		// Write Displays 
		// ===============================================================

		//string displayLeftStr = imgLeftPath.substr(0,imgLeftPath.size()-4) + "_display.png";
		string displayLeftStr = "./" + imgNames[i] + "_left.png";
		imwrite(displayLeftStr, displayLeft);
		//string displayRightStr = imgRightPath.substr(0,imgRightPath.size()-4) + "_display.png";
		string displayRightStr = "./" + imgNames[i] + "_right.png";
		imwrite(displayRightStr, displayRight);
	}
	
	cout << "end matching" << endl;
	

	return 0;
}



