
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"

#include "LicensePlates.h"
#include "MainFrm.h"
#include "Assit.h"
#include "CRunningDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(WM_SETTEXTSTATUS, &CMainFrame::SetTextStatus)
	ON_COMMAND(ID_TOOL_TAKEPICTURE, &CMainFrame::OnToolTakepicture)
	ON_COMMAND(ID_CAMERA_CONNECT, &CMainFrame::OnCameraConnect)
	ON_COMMAND(ID_CAMERA_DISCONNECT, &CMainFrame::OnCameraDisconnect)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style = WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
		FWS_ADDTOTITLE;
		
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



LRESULT CMainFrame::SetTextStatus(WPARAM wParam, LPARAM lParam)
{
	int index = (int)wParam;
	LPCTSTR lpszNewText = (LPCTSTR)lParam;
	m_wndStatusBar.SetPaneText(index, lpszNewText);
	return 0;
}

void CMainFrame::OnToolTakepicture()
{
	// TODO: Add your command handler code here

	if (pDoc->m_pCamera[0]->m_bOpen)
	{
		Mat im;
		if (pDoc->m_pCamera[0]->TakeImage(pDoc->m_imgOrigin[0]))
		{
			pView->DisplayImage(pDoc->m_imgOrigin[0]);
		}
		else
			im.release();

	}
	else
	{
		CFileDialog image_file(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
			_T("Image Files (*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png|All Files(*.*)|*.*||"));
		if (image_file.DoModal() == IDOK)
		{
			pDoc->m_imgOrigin[0] = cv::imread(CString2string(image_file.GetPathName()), IMREAD_UNCHANGED);
			pView->DisplayImage(pDoc->m_imgOrigin[0]);
			//pView->m_pRunningDlg->OnBnClickedTabRunningBtnTest();
		}
	}
	
}


void CMainFrame::OnCameraConnect()
{
	// TODO: Add your command handler code here
	if(!pDoc->m_pCamera[0]->m_bOpen)
		pDoc->m_pCamera[0]->Connect();
}


void CMainFrame::OnCameraDisconnect()
{
	// TODO: Add your command handler code here
	if (pDoc->m_pCamera[0]->m_bOpen)
		pDoc->m_pCamera[0]->Disconnect();
}
