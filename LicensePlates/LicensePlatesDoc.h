
// LicensePlatesDoc.h : interface of the CLicensePlatesDoc class
//


#pragma once


#include "Camera.h"



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

// Overrides
public:
	virtual BOOL OnNewDocument();
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
