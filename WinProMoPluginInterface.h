#ifndef _WINPROMOPLUGININTERFACE_H_
#define _WINPROMOPLUGININTERFACE_H_

#include "ProMoEditor/ProMoClipboardHandler.h"

class CWinProMoPluginInterface
{
public:
	virtual ~CWinProMoPluginInterface() {}
	virtual CMultiDocTemplate* RegisterPlugin(CRuntimeClass* pFrameClass, CProMoClipboardHandler* pClip) = 0;
	virtual CObArray* GetElements() = 0;
	virtual const CString GetDocumentType() = 0;
	virtual void Destroy() = 0;
};

#endif //_WINPROMOPLUGININTERFACE_H_
