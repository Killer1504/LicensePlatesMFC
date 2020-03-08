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

	cv::threshold(m_imgThreshold, m_imgThreshold, nAvgTheshold, 255, THRESH_BINARY);
	m_pView->DisplayImage(m_imgThreshold);

	Mat src = m_imgThreshold.clone();
	Mat dst1;
	double nNoise1 = 500;
	double nNoise2 = 6000;
	if (!FitNoise(src, dst1, nNoise1))
		dst1 = src.clone();
	Mat dst2;
	if (!FitNoise(dst1, dst2, nNoise2, FALSE))
		dst2 = src.clone();
	m_pView->DisplayImage(dst2);
}
