#pragma once
#include "pch.h"
#include "Assit.h"



string CString2string(CString cstr)
{
	string str;
	str = CT2A(cstr);
	return str;
}

CString double2CString(double db)
{
	string str = to_string(db);
	CString cstr = string2CString(str);
	return cstr;
}

int CString2int(CString cstr)
{
	return _tstoi(cstr);
}

double CString2double(CString cstr)
{
	double db = _ttof(cstr);
	return db;
}

CString string2CString(string str)
{
	CString cstr = _T("");
	cstr = str.c_str();
	return cstr;
}

int CaculateAvgScalar(Mat im)
{
	if (im.empty()) return 0;
	if (im.channels() > 1) cvtColor(im, im, COLOR_BGR2GRAY);

	int cols = im.cols;
	int rows = im.rows;

	int avg = 0;

	for (int j = 0; j < cols; j++)
	{
		for (int i = 0; i < rows; i++)
		{
			int scalar_gray = im.at<uchar>(i, j);
			avg += scalar_gray;
		}
	}

	avg = (int)avg / (rows * cols);
	return avg;
}

BOOL FitNoise(Mat src, Mat& dst, double nNoise, BOOL m_bSoSanh)
{
	double mArea = nNoise;
	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	if (src.channels() == 3)
		cvtColor(src, src, COLOR_BGR2GRAY);
	findContours(src, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	int nSizeContour = (int)contours1.size();

	dst = Mat::zeros(src.size(), CV_8UC1);
	if (nSizeContour <= 0)
	{
		return FALSE;
	}
	if (mArea < 0)
		mArea = 0;
	for (int i = 0; i < nSizeContour; i++)
	{

		double bufferArea = contourArea(contours1[i]);
		if (m_bSoSanh)
		{
			if (bufferArea >= mArea)
			{
				Mat _dst = Mat::zeros(dst.size(), CV_8UC1);
				drawContours(_dst, contours1, i, Scalar(255, 255, 255), -1, 8);
				bitwise_xor(dst, _dst, dst);
			}
		}
		else
		{
			if (bufferArea <= mArea)
			{
				Mat _dst = Mat::zeros(dst.size(), CV_8UC1);
				drawContours(_dst, contours1, i, Scalar(255, 255, 255), -1, 8);
				bitwise_xor(dst, _dst, dst);
			}
		}

	}
	return TRUE;
}

BOOL FitWidthHeight(Mat src, Mat& dst, int nMin, int nMax, BOOL m_bWH)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	if (src.channels() == 3)
		cvtColor(src, src, COLOR_BGR2GRAY);
	findContours(src, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	int nSizeContour = (int)contours.size();

	dst = Mat::zeros(src.size(), CV_8UC1);
	if (nSizeContour <= 0)
	{
		return FALSE;
	}
	for (int i = 0; i < nSizeContour; i++)
	{
		//double bufferArea = contourArea(contours1[i]);
		cv::Rect rc = boundingRect(contours[i]);
		int width = rc.width;
		int hight = rc.height;
		if (m_bWH)
		{
			if ( nMin <= width && width <= nMax)
			{
				Mat _dst = Mat::zeros(dst.size(), CV_8UC1);
				drawContours(_dst, contours, i, Scalar(255, 255, 255), -1, 8);
				bitwise_xor(dst, _dst, dst);
			}
			
		}
		else
		{
			if (nMin <= hight &&  hight<= nMax)
			{
				Mat _dst = Mat::zeros(dst.size(), CV_8UC1);
				drawContours(_dst, contours, i, Scalar(255, 255, 255), -1, 8);
				bitwise_xor(dst, _dst, dst);
			}
		}

	}
	return TRUE;
}

BOOL Fit_ratio(Mat src, Mat& dst, double ratio1, double ratio2)
{
	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	if (src.channels() == 3)
		cvtColor(src, src, COLOR_BGR2GRAY);
	findContours(src, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	int nSizeContour = (int)contours1.size();

	dst = Mat::zeros(src.size(), CV_8UC1);
	if (nSizeContour <= 0)
	{
		return FALSE;
	}
	if (ratio1 < 0 || ratio2 < 0)
		return FALSE;
	for (int i = 0; i < nSizeContour; i++)
	{
		//double bufferArea = contourArea(contours1[i]);
		cv::Rect rc = boundingRect(contours1[i]);
		double nRate = (double)rc.width / (double)rc.height;
		if (ratio1 <= nRate && nRate <= ratio2)
		{
			Mat _dst = Mat::zeros(dst.size(), CV_8UC1);
			drawContours(_dst, contours1, i, Scalar(255, 255, 255), -1, 8);
			bitwise_xor(dst, _dst, dst);
		}
		
	}
	return TRUE;
}

BOOL Fit_ratio_contour(Mat src, Mat& dst, double ratio1, double ratio2)
{

	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	if (src.channels() == 3)
		cvtColor(src, src, COLOR_BGR2GRAY);
	findContours(src, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	int nSizeContour = (int)contours1.size();

	dst = Mat::zeros(src.size(), CV_8UC1);
	if (nSizeContour <= 0)
	{
		return FALSE;
	}
	if (ratio1 < 0 || ratio2 < 0)
		return FALSE;
	for (int i = 0; i < nSizeContour; i++)
	{
		double dContour = contourArea(contours1[i]);
		cv::Rect rc = boundingRect(contours1[i]);
		int width = rc.width;
		int height = rc.height;
		double nRate = dContour / double(width * height);
		if (ratio1 <= nRate && nRate <= ratio2)
		{
			Mat _dst = Mat::zeros(dst.size(), CV_8UC1);
			drawContours(_dst, contours1, i, Scalar(255, 255, 255), -1, 8);
			bitwise_xor(dst, _dst, dst);
		}

	}
	return TRUE;
}

BOOL My_morphologyEx(Mat src, Mat& dst, int morph_elem, int morph_x, int morph_y, int morph_operator)
{
	if (!src.data) return FALSE;
	dst = Mat::zeros(src.size(), CV_8UC1);
	Mat element = getStructuringElement(morph_elem, Size(morph_x, morph_y));
	morphologyEx(src, dst, morph_operator, element);
	return TRUE;
}

BOOL FindRectLicense(Mat src, cv::Rect& rc)
{
	if (!src.data) return FALSE;
	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	if (src.channels() == 3)
		cvtColor(src, src, COLOR_BGR2GRAY);
	findContours(src, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	int nSizeContour = (int)contours1.size();

	if (nSizeContour != 1)
	{
		return FALSE;
	}
	rc = boundingRect(contours1[0]);
	return TRUE;
}

