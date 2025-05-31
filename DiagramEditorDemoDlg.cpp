// DiagramEditorDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DiagramEditorDemo.h"
#include "DiagramEditorDemoDlg.h"
#include "PaperSizeDialog.h"
#include "GridSizeDialog.h"

#include "TextFile.h"
#include "DiagramEditor/DiagramLine.h"
#include "ProcessEditor/ProcessEntityBlockView.h"
#include "ProcessEditor/ProcessLineEdgeView.h"
#include "ProcessEditor/ProcessControlFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditorDemoDlg dialog

CDiagramEditorDemoDlg::CDiagramEditorDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDiagramEditorDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiagramEditorDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDiagramEditorDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiagramEditorDemoDlg)
	DDX_Control(pDX, IDC_CHECK_SNAP, m_snap);
	DDX_Control(pDX, IDC_CHECK_SHOW_GRID, m_grid);
	DDX_Control(pDX, IDC_STATIC_PLACEHOLDER, m_placeholder);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDiagramEditorDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDiagramEditorDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_BOX, OnButtonBox)
	ON_BN_CLICKED(IDC_BUTTON_LINE, OnButtonLine)
	ON_BN_CLICKED(IDC_CHECK_SNAP, OnCheckSnap)
	ON_BN_CLICKED(IDC_CHECK_SHOW_GRID, OnCheckShowGrid)
	ON_BN_CLICKED(IDC_BUTTON_GRID_SIZE, OnButtonGridSize)
	ON_BN_CLICKED(IDC_BUTTON_SIZE, OnButtonSize)
	ON_BN_CLICKED(IDC_BUTTON_CUT, OnButtonCut)
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, OnButtonPaste)
	ON_BN_CLICKED(IDC_BUTTON_UNDO, OnButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiagramEditorDemoDlg message handlers

BOOL CDiagramEditorDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// --- DiagramEditor ---
	// Creating the editor
	CRect placeholder;
	m_placeholder.GetWindowRect( placeholder );
	ScreenToClient( placeholder );
	m_placeholder.ShowWindow( SW_HIDE );
	m_editor.SetRestraints( RESTRAINT_VIRTUAL );
	m_objs.SetClipboardHandler(&m_clip);
	m_editor.Create( WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER, placeholder, this, &m_objs );
	m_grid.SetCheck( TRUE );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDiagramEditorDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDiagramEditorDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDiagramEditorDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// --- DiagramEditor ---
// Button handlers

void CDiagramEditorDemoDlg::OnOK() 
{
}

void CDiagramEditorDemoDlg::OnButtonNew() 
{

	int answer = IDYES;

	if( m_editor.IsModified() )
	{
		answer = AfxMessageBox( IDS_CHANGED_SAVE, MB_YESNOCANCEL );
		if( answer == IDYES )
			OnButtonSave();
	}

	if( answer != IDCANCEL )
	{

		m_filename = _T( "" );
		m_editor.New();

	}

}

void CDiagramEditorDemoDlg::OnButtonBox() 
{

	/*CDiagramEntity* obj = new CDiagramEntity;
	m_editor.StartDrawingObject( obj );*/
	m_editor.UnselectAll();
	CProcessEntityBlockView* obj = new CProcessEntityBlockView;
	m_editor.StartDrawingObject(obj);

}

void CDiagramEditorDemoDlg::OnButtonLine() 
{

	/*CDiagramLine* obj = new CDiagramLine;
	m_editor.StartDrawingObject( obj );
	*/
	m_editor.UnselectAll();
	CProcessLineEdgeView* obj = new CProcessLineEdgeView;
	m_editor.StartDrawingObject(obj);

}

void CDiagramEditorDemoDlg::OnCheckSnap() 
{

	m_editor.SetSnapToGrid( m_snap.GetCheck() );
	
}

void CDiagramEditorDemoDlg::OnCheckShowGrid() 
{

	m_editor.ShowGrid( m_grid.GetCheck() );
	//deselezionare linea
	//selezionare figli
	//m_editor.LeftAlignSelected();
	//m_editor.Redo();
	
}

void CDiagramEditorDemoDlg::OnButtonGridSize() 
{

	CGridSizeDialog	dlg;

	dlg.m_width = m_editor.GetGridSize().cx;
	dlg.m_height = m_editor.GetGridSize().cy;
	if( dlg.DoModal() == IDOK )
		m_editor.SetGridSize( CSize( dlg.m_width, dlg.m_height ) );	

}

void CDiagramEditorDemoDlg::OnButtonSize() 
{

	CPaperSizeDialog	dlg;

	dlg.m_width = m_editor.GetVirtualSize().cx;
	dlg.m_height = m_editor.GetVirtualSize().cy;

	if( dlg.DoModal() )
		m_editor.SetVirtualSize( CSize( dlg.m_width, dlg.m_height ) );
	
}

void CDiagramEditorDemoDlg::OnButtonCut() 
{

	m_editor.Cut();
	
}

void CDiagramEditorDemoDlg::OnButtonCopy() 
{

	m_editor.Copy();
	
}

void CDiagramEditorDemoDlg::OnButtonPaste() 
{
	m_editor.Paste();
	
}

void CDiagramEditorDemoDlg::OnButtonUndo() 
{
	m_editor.Undo();
	
}

void CDiagramEditorDemoDlg::OnButtonSave() 
{

	CTextFile		tf( _T( "txt" ) );
	CStringArray	stra;

	m_editor.Save( stra );
	tf.WriteTextFile( m_filename, stra );
	AfxMessageBox( IDS_SAVED );

}

void CDiagramEditorDemoDlg::OnButtonLoad() 
{

	int answer = IDYES;

	if( m_editor.IsModified() )
	{
		answer = AfxMessageBox( IDS_CHANGED_SAVE, MB_YESNOCANCEL );
		if( answer == IDYES )
			OnButtonSave();
	}

	if( answer != IDCANCEL )
	{

		m_editor.New();

		CTextFile	tf( _T( "txt" ) );
		CStringArray	stra;
		CProcessControlFactory fact;

		m_filename = _T( "" );
		tf.ReadTextFile( m_filename, stra );


		m_editor.Load(stra, fact);

		m_editor.SetModified( FALSE );
		m_editor.RedrawWindow();
	}

}

void CDiagramEditorDemoDlg::OnCancel() 
{
	CDialog::OnCancel();
}



void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
