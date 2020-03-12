#pragma once

#include "framework.h"
#include "MainFrm.h"
#include "LicensePlatesDoc.h"
#include "LicensePlatesView.h"


//bien toan cuc cho toan chuong trinh

extern CMainFrame* pMainFrame;
extern CLicensePlatesDoc* pDoc;
extern CLicensePlatesView* pView;


string CString2string(CString cstr);
CString double2CString(double db);
int CString2int(CString cstr);
double CString2double(CString cstr);
CString string2CString(string str);
// tinh gia tri gray trung binh
int CaculateAvgScalar(Mat im); 
BOOL FitNoise(Mat src, Mat& dst, double nNoise, BOOL m_bSoSanh = 1);
// ratio = width/height
BOOL Fit_ratio(Mat src, Mat &dst, double ratio1, double ratio2);
//ratio = contourArea / boudingrect
BOOL Fit_ratio_contour(Mat src, Mat& dst, double ratio1, double ratio2);
BOOL My_morphologyEx(Mat src, Mat& dst, int morph_elem, int morph_x, int morph_y, int morph_operator);
BOOL FindRectLicense(Mat src, cv::Rect& rc);

void InitPointer();
