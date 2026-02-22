// DummyClass.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// DummyClass command target

class DummyClass : public CCmdTarget
{
	DECLARE_DYNCREATE(DummyClass)

	DummyClass();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DummyClass)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~DummyClass();

	// Generated message map functions
	//{{AFX_MSG(DummyClass)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(DummyClass)
	afx_msg BOOL GetProp();
	afx_msg void SetProp(BOOL bNewValue);
	afx_msg LPDISPATCH Method(short foo, const VARIANT FAR& bar);
	afx_msg OLE_COLOR Method2();
	afx_msg LPUNKNOWN Method3();
	afx_msg double GetPropIdx(short param);
	afx_msg void SetPropIdx(short param, double newValue);
	afx_msg LPDISPATCH GetPropDisp(const VARIANT FAR& idx);
	afx_msg void SetPropDisp(const VARIANT FAR& idx, LPDISPATCH newValue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
