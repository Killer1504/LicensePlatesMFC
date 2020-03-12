// CRunningDlg.cpp : implementation file
//

#include "pch.h"
#include "LicensePlates.h"
#include "CRunningDlg.h"
#include "afxdialogex.h"

#include "LicensePlatesDoc.h"
#include "LicensePlatesView.h"
#include "Assit.h"


// CRunningDlg dialog

IMPLEMENT_DYNAMIC(CRunningDlg, CDialogEx)

CRunningDlg::CRunningDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_RUNNING, pParent)
{

}

CRunningDlg::~CRunningDlg()
{
}

void CRunningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRunningDlg, CDialogEx)
	ON_BN_CLICKED(IDC_TAB_RUNNING_BTN_TEST, &CRunningDlg::OnBnClickedTabRunningBtnTest)
END_MESSAGE_MAP()


// CRunningDlg message handlers


void CRunningDlg::OnBnClickedTabRunningBtnTest()
{
	// TODO: Add your control notification handler code here
	if (m_pDoc->m_imgOrigin[0].empty()) return;
	Mat m_imgGray;
	Mat m_imgThreshold;
	if (m_pDoc->m_imgOrigin[0].channels() > 1)
		cvtColor(m_pDoc->m_imgOrigin[0], m_imgGray, COLOR_BGR2GRAY);
	else
		m_imgGray = m_pDoc->m_imgOrigin[0].clone();

	cv::normalize(m_imgGray, m_imgGray, 0, 255, CV_MINMAX);
	//m_pView->DisplayImage(m_imgGray);

	int nAvgTheshold;
	nAvgTheshold = CaculateAvgScalar(m_imgGray);
	cv::threshold(m_imgGray, m_imgThreshold, nAvgTheshold / 2, 255, THRESH_TOZERO);
	int Delta = 25;
	int nThresh = nAvgTheshold + Delta;
	cv::threshold(m_imgThreshold, m_imgThreshold, nThresh, 255, THRESH_BINARY);
	//cv::imshow("m_imgThreshold", m_imgThreshold);
	m_pView->DisplayImage(m_imgThreshold);

	Mat src = m_imgThreshold.clone();
	Mat dst1;
	double nNoise1 = 1000;
	double nNoise2 = 6000;
	if (!FitNoise(src, dst1, nNoise1))
		dst1 = src.clone();
	//cv::imshow("dst1", dst1);
	Mat dst2;
	if (!FitNoise(dst1, dst2, nNoise2, FALSE))
		dst2 = src.clone();
	//cv::imshow("dst2", dst2);
	Mat dst3;
	if (!Fit_ratio(dst2, dst3, 0.8, 1.5))
		dst3 = dst2.clone();
	//cv::imshow("dst3", dst3);
	Mat dst4;
	if (!My_morphologyEx(dst3, dst4, 1, 25, 5, 3))
		dst4 = dst3.clone();

	//cv::imshow("dst4", dst4);

	Mat dst5;

	if (!Fit_ratio_contour(dst4, dst5, 0.7, 1.3))
		dst5 = dst4.clone();

	Rect rc;
	Mat _im = m_pDoc->m_imgOrigin[0].clone();
	if (FindRectLicense(dst5, rc))
		cv::rectangle(_im, rc, Scalar(0, 255, 0));
	m_pView->DisplayImage(_im);
}
