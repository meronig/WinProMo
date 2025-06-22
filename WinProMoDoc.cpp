/* ==========================================================================
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

CWinProMoDoc::~CWinProMoDoc()
{
	delete m_objs;
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
			int horzSize = round((double)dc.GetDeviceCaps(HORZSIZE) / (double)screenResolutionX);
			int vertSize = round((double)dc.GetDeviceCaps(VERTSIZE) / (double)screenResolutionX);
			
			m_objs->SetVirtualSize(CSize(8 * screenResolutionX, 11 * screenResolutionX));

		}
	}
	

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWinProMoDoc serialization

void CWinProMoDoc::Serialize(CArchive& ar)
{
	CString str;
	CStringArray arr;
	CFile* pFile = ar.GetFile();
	
	if (m_objs) {
		if (ar.IsStoring())
		{
			m_objs->Save(arr);
			// Revise this part, as there is no control on the encoding (currently UTF-16 LE, incompatible with loading)
			for (int i = 0; i < arr.GetSize(); i++) {
				CString line = arr.GetAt(i) + "\r\n";
				ar.WriteString(line);
			}

		}
		else
		{
			// Loading can handle ANSI or UTF8 encoding only

			m_objs->Clear();
			CProMoControlFactory fact;

			DWORD size = (DWORD)pFile->GetLength();
			char* buffer = new char[size + 1];
			pFile->Read(buffer, size);
			buffer[size] = '\0';

			CString content(buffer);
			delete[] buffer;

			int pos = 0;
			while (pos >= 0)
			{
				int next = content.Find(_T("\r\n"), pos);
				CString line;
				if (next == -1)
				{
					line = content.Mid(pos);
					pos = -1;
				}
				else
				{
					line = content.Mid(pos, next - pos);
					pos = next + 2;
				}
				arr.Add(line);
			}

			m_objs->Load(arr, fact);
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
