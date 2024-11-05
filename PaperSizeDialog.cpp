// PaperSizeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DiagramEditorDemo.h"
#include "PaperSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaperSizeDialog dialog


CPaperSizeDialog::CPaperSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPaperSizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPaperSizeDialog)
	m_width = 0;
	m_height = 0;
	//}}AFX_DATA_INIT
}


void CPaperSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaperSizeDialog)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaperSizeDialog, CDialog)
	//{{AFX_MSG_MAP(CPaperSizeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaperSizeDialog message handlers
