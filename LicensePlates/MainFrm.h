
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#define WM_SETTEXTSTATUS	(WM_USER + 0)
#define WM_START			(WM_USER + 1)
#define WM_STOP				(WM_USER + 2)

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT SetTextStatus(WPARAM wParam, LPARAM lParam);

	afx_msg void OnToolTakepicture();
};


