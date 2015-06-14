


#include "AggregateCostVolume.h"
#include "stdafx.h"


#include <stdio.h> 
//#include <math.h>
#include <opencv2\opencv.hpp> 
#include "guidedfilter.h"

using namespace cv;

void aggregateCostVolume(const Mat &imgLeft, const Mat &imgRight, vector<Mat> &costVolumeLeft, vector<Mat> &costVolumeRight, int r, double eps){

	for(int disp=0; disp<costVolumeLeft.size(); disp++){
		costVolumeLeft.at(disp) = guidedFilter(imgLeft, costVolumeLeft.at(disp), r, eps);
		costVolumeRight.at(disp) = guidedFilter(imgLeft, costVolumeRight.at(disp), r, eps);
	}
}

