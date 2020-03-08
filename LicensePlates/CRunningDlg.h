#pragma once


// CRunningDlg dialog

class CRunningDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRunningDlg)

public:
	CRunningDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRunningDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_RUNNING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTabRunningBtnTest();
};
