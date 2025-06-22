#ifndef _WINPROMODOCTEMPLATE_H_
#define _WINPROMODOCTEMPLATE_H_

#include "stdafx.h"
#include "./ProMoEditor/ProMoClipboardHandler.h"
#include "WinProMoDoc.h"
class AFX_EXT_CLASS CWinProMoDocTemplate :
    public CMultiDocTemplate
{
public:
    CWinProMoDocTemplate(UINT nIDResource,
        CRuntimeClass* pDocClass,
        CRuntimeClass* pFrameClass,
        CRuntimeClass* pViewClass,
        CProMoClipboardHandler* pClip);
    
// Overrides
protected:
    virtual CDocument* CreateNewDocument();

private:
    CProMoClipboardHandler* m_pClip;
};

#endif //_WINPROMODOCTEMPLATE_H_

