#pragma once
#include "pch.h"
#include "WorkerThread.h"
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
	status.Format(_T("(x, y) = (%d, %d)"), x, y);

	/*switch (event)
	{
	default:
		break;
	}*/

	switch (pImage->type())
	{
	case CV_8UC1:
	{
		status.AppendFormat(_T(" | (Gray) = (%d)"), pImage->at<uchar>(_y, _x));
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
