/* ==========================================================================
	CProMoDocTemplate

	Author :		Giovanni Meroni

	Purpose :		"CWinProMoDocTemplate" is used as part of the MFC 
                    document/view architecture to register document 
                    templates. It allows to pass a pointer to a shared 
                    "CProMoClipboardHandler" object to all documents being
                    created, so that one can copy/paste across models.

	Description :	"CWinProMoDocTemplate" is derived from 
                    "CMultiDocTemplate".

   ========================================================================*/
#include "stdafx.h"
#include "WinProMoDocTemplate.h"

CWinProMoDocTemplate::CWinProMoDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass, CProMoClipboardHandler* pClip)
	: CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
	m_pClip = pClip;
}

CDocument* CWinProMoDocTemplate::CreateNewDocument()
{
    CDocument* pDoc = CMultiDocTemplate::CreateNewDocument();
    if (pDoc && m_pClip)
    {
        // Cast only if doc implements the shared interface
        CWinProMoDoc* pMyDoc = dynamic_cast<CWinProMoDoc*>(pDoc);
        if (pMyDoc)
        {
            pMyDoc->CreateContainer();
            pMyDoc->CreateControlFactory();
            pMyDoc->SetClipboardHandler(m_pClip);
        }
    }
    return pDoc;
}
