

#include "RefineDisparity.h"
#include "StdAfx.h"

#include <opencv2\opencv.hpp> 

using namespace cv;

void refineDisparity(Mat &dispLeft, Mat &dispRight, int scaleDispFactor){

	Mat consistencyMapLeft(dispLeft.rows,dispLeft.cols, CV_8U, (uchar)255);
	Mat consistencyMapRight(dispRight.rows,dispRight.cols, CV_8U, (uchar)255);


	for(int rowNr = 1; rowNr < dispLeft.rows; rowNr++ ){
		for(int columnNr = 1; columnNr < dispLeft.cols; columnNr++ ){
			int disp = dispLeft.at<uchar>(rowNr, columnNr);
			int colRight =  columnNr - disp/scaleDispFactor;

				if(colRight <0 || disp != dispRight.at<uchar>(rowNr, colRight))
					consistencyMapLeft.at<uchar>(rowNr, columnNr) = (uchar)0;
				else
					consistencyMapLeft.at<uchar>(rowNr, columnNr) = (uchar)255;
		}
	}

		for(int rowNr = 1; rowNr < dispRight.rows; rowNr++ ){
		for(int columnNr = 1; columnNr < dispRight.cols; columnNr++ ){
			int disp = dispRight.at<uchar>(rowNr, columnNr);
			int colLeft =  columnNr + disp/scaleDispFactor;

			if(colLeft >=dispLeft.cols || disp != dispLeft.at<uchar>(rowNr, colLeft))
					consistencyMapRight.at<uchar>(rowNr, columnNr) = 0;
				else
					consistencyMapRight.at<uchar>(rowNr, columnNr) = 255;
		}
	}

	//imwrite("./output/consMapLeft.png", consistencyMapLeft);
	//imwrite("./output/consMapRight.png", consistencyMapRight);


	for(int rowNr = 1; rowNr < dispLeft.rows; rowNr++ ){
		for(int columnNr = 1; columnNr < dispLeft.cols; columnNr++ ){
			if(consistencyMapLeft.at<uchar>(rowNr, columnNr) == (uchar)0){
				int min = columnNr;
				while(min>0){
					if(consistencyMapLeft.at<uchar>(rowNr, min) == (uchar)255)
						break;
					min--;
				}
			

				int max = columnNr;
				while(max<dispLeft.rows){
					if(consistencyMapLeft.at<uchar>(rowNr, max) == (uchar)255)
						break;
					max++;
				}

				
				if(dispLeft.at<uchar>(rowNr, min) <= dispLeft.at<uchar>(rowNr, max))
					dispLeft.at<uchar>(rowNr, columnNr) = dispLeft.at<uchar>(rowNr, min);
				else 
					dispLeft.at<uchar>(rowNr, columnNr) = dispLeft.at<uchar>(rowNr, max);
			}

		}
	}

	for(int rowNr = 1; rowNr < dispRight.rows; rowNr++ ){
		for(int columnNr = 1; columnNr < dispRight.cols; columnNr++ ){
			if(consistencyMapRight.at<uchar>(rowNr, columnNr) == (uchar)0){
				int min = columnNr;
				while(min>0){
					if(consistencyMapRight.at<uchar>(rowNr, min) == (uchar)255)
						break;
					min--;
				}
			

				int max = columnNr;
				while(max<dispRight.rows){
					if(consistencyMapRight.at<uchar>(rowNr, max) == (uchar)255)
						break;
					max++;
				}

				
				if(dispRight.at<uchar>(rowNr, min) <= dispRight.at<uchar>(rowNr, max))
					dispRight.at<uchar>(rowNr, columnNr) = dispRight.at<uchar>(rowNr, min);
				else 
					dispRight.at<uchar>(rowNr, columnNr) = dispRight.at<uchar>(rowNr, max);
			}

		}
	}



}
