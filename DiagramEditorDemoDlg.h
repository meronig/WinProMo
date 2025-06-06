// DiagramEditorDemoDlg.h : header file
//

#if !defined(AFX_DIAGRAMEDITORDEMODLG_H__5BF6AB73_E2FA_4020_94F1_DDA7E9C4713F__INCLUDED_)
#define AFX_DIAGRAMEDITORDEMODLG_H__5BF6AB73_E2FA_4020_94F1_DDA7E9C4713F__INCLUDED_

#if _MSC_VER >= 1020 // pragma once introduced with MSVC 4.2
#pragma once
#endif

#include "ProMoEditor/ProMoEditor.h"
#include "ProMoEditor/ProMoEntityContainer.h"
#include "ProMoEditor/ProMoClipboardHandler.h"

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditorDemoDlg dialog

class CDiagramEditorDemoDlg : public CDialog
{
// Construction
public:
	CDiagramEditorDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDiagramEditorDemoDlg)
	enum { IDD = IDD_DIAGRAMEDITORDEMO_DIALOG };
	CButton	m_grid;
	CButton	m_snap;
	CStatic	m_placeholder;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagramEditorDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDiagramEditorDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonBox();
	afx_msg void OnButtonLine();
	afx_msg void OnCheckSnap();
	afx_msg void OnCheckShowGrid();
	afx_msg void OnButtonGridSize();
	afx_msg void OnButtonSize();
	afx_msg void OnButtonCut();
	afx_msg void OnButtonCopy();
	afx_msg void OnButtonPaste();
	afx_msg void OnButtonUndo();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonLoad();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CProMoEditor			m_editor;
	CString					m_filename;

	//NEW
	CProMoEntityContainer	m_objs;
	CProMoClipboardHandler	m_clip;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGRAMEDITORDEMODLG_H__5BF6AB73_E2FA_4020_94F1_DDA7E9C4713F__INCLUDED_)
