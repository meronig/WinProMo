// GridSizeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DiagramEditorDemo.h"
#include "GridSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridSizeDialog dialog


CGridSizeDialog::CGridSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGridSizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGridSizeDialog)
	m_height = 0;
	m_width = 0;
	//}}AFX_DATA_INIT
}


void CGridSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridSizeDialog)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGridSizeDialog, CDialog)
	//{{AFX_MSG_MAP(CGridSizeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridSizeDialog message handlers
