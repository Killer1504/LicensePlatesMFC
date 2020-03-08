
// LicensePlatesView.cpp : implementation of the CLicensePlatesView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LicensePlates.h"
#endif

#include "LicensePlatesDoc.h"
#include "LicensePlatesView.h"
#include "WorkerThread.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLicensePlatesView

IMPLEMENT_DYNCREATE(CLicensePlatesView, CFormView)

BEGIN_MESSAGE_MAP(CLicensePlatesView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLicensePlatesView construction/destruction

CLicensePlatesView::CLicensePlatesView() noexcept
	: CFormView(IDD_LICENSEPLATES_FORM)
{
	// TODO: add construction code here

}

CLicensePlatesView::~CLicensePlatesView()
{
	delete m_pRunningDlg;
}

void CLicensePlatesView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tabCtrl);
}

void CLicensePlatesView::DisplayImage(Mat& image, BOOL bSetMouseCallback, BOOL bDrawROI)
{
	if (image.empty()) return;
	Mat _im;
	std::string winname = std::to_string(IDC_PICTURE_MAIN);
	if (image.channels() == 1) cv::cvtColor(image, _im, COLOR_GRAY2BGR);
	else
		_im = image.clone();
	if (bSetMouseCallback)
	{
		//
		cv::setMouseCallback(winname, NULL);
		m_imgDisplay = image.clone();
		cv::setMouseCallback(winname, onMouse, &m_imgDisplay);
	}
	else
		m_imgDisplay.release();


	if (bDrawROI)
	{
		Sleep(1);
	}

	cv::imshow(winname, _im);
}

BOOL CLicensePlatesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLicensePlatesView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();

	static int nUpdate = 0;
	CRect rc; HWND hWnd; std::string winname;
	
	if (nUpdate == 0)
	{
		//insert tab Ctrl
		

		m_tabCtrl.InsertItem(Running, _T("Running"));
		m_tabCtrl.InsertItem(ROITeaching, _T("ROITeaching"));
		m_tabCtrl.InsertItem(RefPointTeaching, _T("ROITeaching"));

		m_pRunningDlg = new CRunningDlg(this);
		m_pRunningDlg->Create(IDD_TAB_RUNNING, &m_tabCtrl);
		m_pRunningDlg->SetWindowPos(&wndTop, 0, 25, 0, 0, SWP_HIDEWINDOW | SWP_NOSIZE);

		m_pCurTab = (CWnd*)m_pRunningDlg;
		m_pCurTab->ShowWindow(SW_SHOW);

	}
	if (nUpdate == 1)
	{
		winname = to_string(IDC_PICTURE_MAIN);
		GetDlgItem(IDC_PICTURE_MAIN)->GetWindowRect(&rc);
		namedWindow(winname, WINDOW_NORMAL);
		resizeWindow(winname, rc.Width(), rc.Height());
		hWnd = (HWND)cvGetWindowHandle(winname.c_str());
		::ShowWindow(::GetParent(hWnd), SW_HIDE);
		::SetParent(hWnd, GetDlgItem(IDC_PICTURE_MAIN)->m_hWnd);
	}

	if (nUpdate > 0)
	{
		Mat _im = Mat::zeros(3, 4, CV_8UC1);
		DisplayImage(_im, FALSE, FALSE);
	}
	nUpdate++;

}


// CLicensePlatesView printing

BOOL CLicensePlatesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLicensePlatesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLicensePlatesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLicensePlatesView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}


// CLicensePlatesView diagnostics

#ifdef _DEBUG
void CLicensePlatesView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLicensePlatesView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLicensePlatesDoc* CLicensePlatesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLicensePlatesDoc)));
	return (CLicensePlatesDoc*)m_pDocument;
}
#endif //_DEBUG


// CLicensePlatesView message handlers
