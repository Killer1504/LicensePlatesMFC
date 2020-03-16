#pragma once
#include "pch.h"
#include "WorkerThread.h"
#include "LicensePlates.h"
#include "Assit.h"

void onMouse(int event, int x, int y, int flags, void* userdata)
{
	if (pDoc->m_bContinous || pDoc->m_bIsprocessing) return;

	Mat* pImage = (Mat*)userdata;

	CString status, str;
	static int dragX = -1, dragY = -1;
	int _x = x;
	int _y = y;

	if (x< 0 || y < 0 || x > pImage->cols || y > pImage->rows) return;
	status.Format(_T("(x, y) = (%d, %d) "), x, y);

	/*switch (event)
	{
	default:
		break;
	}*/

	switch (pImage->type())
	{
	case CV_8UC1:
	{
		status.AppendFormat(_T("| (Gray) = (%d)"), pImage->at<uchar>(_y, _x));
	}
	break;
	case CV_8UC3:
	{
		status.AppendFormat(_T("| (B, G, R) = (%d, %d, %d)"), 
			pImage->at<Vec3b>(_y,_x).val[0], pImage->at<Vec3b>(_y, _x).val[1], pImage->at<Vec3b>(_y, _x).val[2]);
	}
		break;
	default:
		break;
	}

	pMainFrame->SendMessage(WM_SETTEXTSTATUS, 0, (LPARAM)(LPCTSTR)status);
}

UINT ImageProcessThread(LPVOID pParam)
{
	if (!pDoc->m_imgOrigin[0].data) return -1;
	Mat src, dst;

	src = pDoc->m_imgOrigin[0].clone();
	cv::normalize(src, src, 0, 255, CV_MINMAX);
	if (src.channels() > 1) cv::cvtColor(src, src, COLOR_BGR2GRAY);
	int nAvgGray = CaculateAvgScalar(src);

	Mat m_imgThreshold;
	int nDelta = 20;
	int nThresh = nAvgGray + nDelta;
	cv::threshold(src, m_imgThreshold, nThresh, 255, THRESH_BINARY);

	Mat dst1;
	int nNoise1 = 500;
	FitNoise(m_imgThreshold, dst1, nNoise1);

	Mat dst2;
	
	int nNoise2 = 5000;
	FitNoise(dst1, dst2, nNoise2, 0);

	Mat dst3;
	int nWidthMin = 30;
	int nWidthMax = 200;
	FitWidthHeight(dst2, dst3, nWidthMin, nWidthMax);

	Mat dst4;
	int nHightMin = 30;
	int nHightMax = 100;
	FitWidthHeight(dst3, dst4, nHightMin, nHightMax, 0);


	dst = dst4.clone();
	pView->DisplayImage(dst);

	return 0;
}
