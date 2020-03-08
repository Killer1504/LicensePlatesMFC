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
int CaculateAvgScalar(Mat im); // tinh gia tri gray trung binh
BOOL FitNoise(Mat src, Mat& dst, double nNoise, BOOL m_bSoSanh = 1);

void InitPointer();
