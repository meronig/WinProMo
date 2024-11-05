/* ==========================================================================
	CPropertyDialog

	Author :		Giovanni Meroni

	Purpose :		CPropertyDialog is a dialog box wrapper derived from 
					CDiagramPropertyDlg, used by CDiagramEntity-derived 
					objects to edit the object title attribute.

	Description :	Class-Wizard created class.

	Usage :			In the CDiagramEntity-derived class, add a member of 
					the CPropertyDialog-derived class, and call 
					SetPropertyDialog in the constructor.

					The dialog is displayed as a modeless dialog. The 
					editor will hide the dialog automatically when another
					object is selected, no special Close-button is 
					necessary.

					The dialog template with the res id IDD_DIALOG_PROPERTY 
					must be added to the project.
   ========================================================================*/

#include "../stdafx.h"
#include "ProcessEditor.h"
#include "PropertyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyDialog dialog

CPropertyDialog::CPropertyDialog(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CPropertyDialog::IDD, pParent)
/* ============================================================
	Function :		CPropertyDialog::CPropertyDialog
	Description :	constructor
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	//{{AFX_DATA_INIT(CPropertyDialog)
	m_text = _T("");
	//}}AFX_DATA_INIT

}

CPropertyDialog::~CPropertyDialog()
/* ============================================================
	Function :		CPropertyDialog::~CPropertyDialog
	Description :	destructor
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

void CPropertyDialog::DoDataExchange(CDataExchange* pDX)
{

	CDiagramPropertyDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyDialog)
	DDX_Text(pDX, IDC_EDIT_TEXT, m_text);
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CPropertyDialog, CDiagramPropertyDlg)
	//{{AFX_MSG_MAP(CPropertyDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyDialog message handlers

void CPropertyDialog::OnOK() 
/* ============================================================
	Function :		CPropertyDialog::OnOK
	Description :	Called when the Apply-key is pressed.
					
	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Updates the attached object 
					and hides the modeless dialog.

   ============================================================*/
{

	UpdateData();
	GetEntity()->SetTitle( m_text );
	Redraw();
	ShowWindow( SW_HIDE );
	GetRedrawWnd()->SetFocus();

}

void CPropertyDialog::OnCancel() 
/* ============================================================
	Function :		CPropertyDialog::OnCancel
	Description :	Called when the ESC-key is pressed.
					
	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Overridden to close the 
					dialog.

   ============================================================*/
{

	CDialog::OnCancel();
	GetRedrawWnd()->SetFocus();

}

/////////////////////////////////////////////////////////////////////////////
// CPropertyDialog overrides

void CPropertyDialog::SetValues() 
/* ============================================================
	Function :		CPropertyDialog::SetValues
	Description :	Set the values in the dialog from the 
					attached object.
					
	Return :		void
	Parameters :	none

	Usage :			Will be called by the framework and the 
					attached object to initialize the dialog. 
					The editbox is filled with the contents of 
					the object title attribute.

   ============================================================*/
{

	m_text = GetEntity()->GetTitle();

}
