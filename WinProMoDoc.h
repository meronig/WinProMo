// WinProMoDoc.h : interface of the CWinProMoDoc class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _WINPROMODOC_H_
#define _WINPROMODOC_H_


#include "stdafx.h"
#include "./ProMoEditor/ProMoEntityContainer.h"
#include "./ProMoEditor/ProMoClipboardHandler.h"

class WINPROMO_API CWinProMoDoc : public CDocument
{
public: // create from serialization only
	DECLARE_DYNCREATE(CWinProMoDoc)

// Attributes
public:

// Operations
public:
	CWinProMoDoc();

	virtual CProMoEntityContainer* GetData();
	virtual void SetClipboardHandler(CProMoClipboardHandler* clip);
	virtual void CreateContainer();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinProMoDoc)
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinProMoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinProMoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CProMoEntityContainer* m_objs;
};

#endif // _WINPROMODOC_H_
/////////////////////////////////////////////////////////////////////////////
