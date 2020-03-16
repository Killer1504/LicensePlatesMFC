
// LicensePlatesDoc.h : interface of the CLicensePlatesDoc class
//


#pragma once

#define MaxName		30
#define MaxRefPoint	10
#define MaxROI		30
#define	MaxStep		10
#define MaxPrm		100

#include "Camera.h"

struct Parameter
{
	struct _RefPoint
	{
		int nROI;						//thu tu RefPoit
		int nCamSelect;					//Cam cua RefPoint
		BOOL bIsProcessing;				//dang xu ly RefPoint
		TCHAR nameRefPoint[MaxName];	//Ten RefPoint
		Rect Area;						//Vung RefPoint
		int nInitStep, nFinalStep;
		byte prm[MaxStep][MaxPrm];

		//Thong so ket qua
		Point ptResult;
		BOOL bResult;
		double specA_Low, specA_High, spectA_Me; // thong so do dc
		TCHAR specA_Na[MaxName];
	};
	struct _ROI
	{
		int nROI;
		int nCamSelect;
		BOOL bIsProcessing;
		TCHAR nameROI[MaxName];
		cv::Rect Area;
		int nInitStep, nFinalStep;
		byte prm[MaxStep][MaxPrm];

		//ket qua

		//0: WAIT, 1: OK, 2: NG
		int nResultA, nResultB;
		BOOL bResult;
		TCHAR specA_Na[MaxName], specB_Na[MaxName];
		double specA_Low, specA_High, specA_Me;
		double specB_Low, specB_High, specB_Me;
	};

	_RefPoint		RefPoint[MaxRefPoint];
	_ROI			ROI[MaxROI];

	//0: WAIT, 1: OK, 2: NG
	int nResult;
	void DeleteROI(int nROI)
	{

	}
	void DeleteRefPoint(int nROI)
	{

	}
};

class CLicensePlatesDoc : public CDocument
{
protected: // create from serialization only
	CLicensePlatesDoc() noexcept;
	DECLARE_DYNCREATE(CLicensePlatesDoc)

// Attributes
public:
	//cac bien
	CCamera* m_pCamera[MAX_CAM_NUMBER];

// Operations
public:
	//cac bien

	BOOL m_bContinous; // danh dau vong lap continous
	BOOL m_bIsprocessing; // dang xu ly anh

	Mat m_imgOrigin[MAX_CAM_NUMBER];

	Parameter m_prm;

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CLicensePlatesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
