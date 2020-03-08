#pragma once
#include "pch.h"
#include "Assit.h"


CMainFrame* pMainFrame;
CLicensePlatesDoc* pDoc;
CLicensePlatesView* pView;

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
	int size_contour = (int)contours1.size();

	dst = Mat::zeros(src.size(), CV_8UC1);
	if (size_contour <= 0)
	{
		return FALSE;
	}
	if (mArea < 0)
		mArea = 0;
	for (int i = 0; i < size_contour; i++)
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

void InitPointer()
{
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pDoc = (CLicensePlatesDoc*)pMainFrame->GetActiveDocument();
	pView = (CLicensePlatesView*)pMainFrame->GetActiveView();
}
