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
			
#ifndef _UNICODE 

			for (int i = 0; i < arr.GetSize(); i++) {
				CString line = arr.GetAt(i) + "\r\n";
				ar.WriteString(line);
			}

#else

			for (int i = 0; i < arr.GetSize(); i++) {
				CStringW wideLine = arr.GetAt(i) + L"\r\n";

				// Convert UTF-16 to UTF-8
				int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideLine, -1, NULL, 0, NULL, NULL);
				char* utf8Line = new char[utf8Len];
				WideCharToMultiByte(CP_UTF8, 0, wideLine, -1, utf8Line, utf8Len, NULL, NULL);

				// Write excluding null terminator
				pFile->Write(utf8Line, utf8Len - 1);
				delete[] utf8Line;
			}
#endif
		}
		else
		{
			// Loading can handle ANSI or UTF8 encoding only

			m_objs->Clear();
			
			DWORD size = (DWORD)pFile->GetLength();
			char* buffer = new char[size + 1];
			pFile->Read(buffer, size);
			buffer[size] = '\0';

			CString content(buffer);
			delete[] buffer;

			int pos = 0;
			while (pos >= 0)
			{
				CString rest = content.Mid(pos);
				int rel = rest.Find(_T("\r\n"));
				CString line;

				if (rel == -1)
				{
					line = rest;
					pos = -1;
				}
				else
				{
					line = rest.Left(rel);
					pos += rel + 2;
				}

				arr.Add(line);
			}
			if (m_fact) {
				m_objs->Load(arr, m_fact);
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
