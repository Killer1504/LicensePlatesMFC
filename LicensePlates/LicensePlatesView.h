
// LicensePlatesView.h : interface of the CLicensePlatesView class
//

#pragma once

#include "CRunningDlg.h"

class CLicensePlatesView : public CFormView
{
protected: // create from serialization only
	CLicensePlatesView() noexcept;
	DECLARE_DYNCREATE(CLicensePlatesView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_LICENSEPLATES_FORM };
#endif

// Attributes
public:
	CLicensePlatesDoc* GetDocument() const;

// Operations
public:
// Overrides
	cv::Mat m_imgDisplay;
	//Display Image in picture main
	void DisplayImage(Mat& image, BOOL bSetMouseCallback = TRUE, BOOL bDrawROI = TRUE);
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate(); // called first time after construct

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLicensePlatesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	enum { Running = 0, ROITeaching, RefPointTeaching };
	CTabCtrl m_tabCtrl;
	CWnd* m_pCurTab;		// Tab hien tai
	CRunningDlg* m_pRunningDlg;
};

#ifndef _DEBUG  // debug version in LicensePlatesView.cpp
inline CLicensePlatesDoc* CLicensePlatesView::GetDocument() const
   { return reinterpret_cast<CLicensePlatesDoc*>(m_pDocument); }
#endif

