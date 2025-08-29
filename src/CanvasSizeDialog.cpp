// CCanvasSizeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CanvasSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaperSizeDialog dialog


CCanvasSizeDialog::CCanvasSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCanvasSizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCanvasSizeDialog)
	m_width = 0;
	m_height = 0;
	//}}AFX_DATA_INIT
}


void CCanvasSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCanvasSizeDialog)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCanvasSizeDialog, CDialog)
	//{{AFX_MSG_MAP(CCanvasSizeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCanvasSizeDialog message handlers
