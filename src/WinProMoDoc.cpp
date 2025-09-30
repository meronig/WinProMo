/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CWinProMoDoc

	Author :		Giovanni Meroni

	Purpose :		"CWinProMoDoc" is used as part of the MFC document/view
					architecture to represent documents. It contains a 
					reference to "CProMoEntityContainer", which holds the
					model elements.

	Description :	"CWinProMoDoc" is derived from "CDocument".

	Usage :			Classes should be derived from "CWinProMoDoc". For 
					derived classes to properly work, IMPLEMENT_DYNCREATE 
					and DECLARE_DYNCREATE macros must be present. If a
					container different than "CProMoEntityContainer" is 
					needed,	"CreateContainer" should be overridden.

   ========================================================================*/

#include "stdafx.h"
#include "WinProMoDoc.h"
#include "WinProMoView.h"
#include "FileUtils/FileSerializer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinProMoDoc

IMPLEMENT_DYNCREATE(CWinProMoDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinProMoDoc, CDocument)
	//{{AFX_MSG_MAP(CWinProMoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinProMoDoc construction/destruction

CWinProMoDoc::CWinProMoDoc()
{
	m_objs = NULL;
	m_fact = NULL;
}

CProMoEntityContainer* CWinProMoDoc::GetData()
{
	return m_objs;
}

void CWinProMoDoc::SetClipboardHandler(CProMoClipboardHandler* clip)
{
	if(m_objs)
		m_objs->SetClipboardHandler(clip);
}

void CWinProMoDoc::CreateContainer()
{
	if (!m_objs) {
		m_objs = new CProMoEntityContainer("demoPlugin");
	}
}

void CWinProMoDoc::CreateControlFactory()
{
	if (!m_fact) {
		m_fact = new CProMoControlFactory;
	}
}

CWinProMoDoc::~CWinProMoDoc()
{
	if (m_objs)
		delete m_objs;
	if (m_fact)
		delete m_fact;
}

BOOL CWinProMoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CreateContainer();

	m_objs->Clear();
	CWinProMoView* pView = NULL;
	POSITION pos = GetFirstViewPosition();
	if (pos != NULL) {
		pView = (CWinProMoView*)GetNextView(pos);
		if (pView) {
			CClientDC dc(pView);

			int screenResolutionX = dc.GetDeviceCaps(LOGPIXELSX);
			int screenResolutionY = dc.GetDeviceCaps(LOGPIXELSY);

			CDC printDC;
			
			// Canvas size equals to current page size
			if (pView->GetPrinterDC(printDC)) {
				int printResolutionX = printDC.GetDeviceCaps(LOGPIXELSX);
				int printResolutionY = printDC.GetDeviceCaps(LOGPIXELSY);
				
				int horzSize = round((double)printDC.GetDeviceCaps(HORZRES) * (double)screenResolutionX / printResolutionX);
				int vertSize = round((double)printDC.GetDeviceCaps(VERTRES) * (double)screenResolutionY / printResolutionY);

				m_objs->SetVirtualSize(CSize(horzSize - 1, vertSize - 1));

				printDC.DeleteDC();
			}
			// No printer, so default to 8x11
			else {
				m_objs->SetVirtualSize(CSize(8 * screenResolutionX, 11 * screenResolutionX));
			}

		}
	}
	

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWinProMoDoc serialization

void CWinProMoDoc::Serialize(CArchive& ar)
{
	CString str;
	CStringArray data;
	
	if (m_objs) {
		if (ar.IsStoring())
		{
			m_objs->Save(data);
			
			CFileSerializer::Save(ar, data);
		}
		else
		{
			m_objs->Clear();
			
			CFileSerializer::Load(ar, data);
			
			if (m_fact) {
				m_objs->Load(data, *m_fact);
			}
			
		}
	}
}

BOOL CWinProMoDoc::SaveModified()
{
	if (m_objs) {
		SetModifiedFlag(m_objs->IsModified());
	}
	return CDocument::SaveModified();
}

/////////////////////////////////////////////////////////////////////////////
// CWinProMoDoc diagnostics

#ifdef _DEBUG
void CWinProMoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinProMoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinProMoDoc commands
