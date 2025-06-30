#ifndef _WINPROMOPLUGININTERFACE_H_
#define _WINPROMOPLUGININTERFACE_H_

#include "ProMoEditor/ProMoClipboardHandler.h"

class CWinProMoPluginInterface
{
public:
	virtual ~CWinProMoPluginInterface() {}
	virtual CMultiDocTemplate* RegisterPlugin(CRuntimeClass* pFrameClass, CProMoClipboardHandler* pClip) = 0;
	virtual CObArray* GetElements() = 0;
	virtual CObArray* GetCommands() = 0;
	virtual const CString GetDocumentType() = 0;
	virtual const UINT GetDocumentID() = 0;
	virtual CRuntimeClass* GetPluginDoc() = 0;
	virtual CRuntimeClass* GetPluginView() = 0;
	virtual void Destroy() = 0;
};

class AFX_EXT_CLASS CWinProMoPluginCommand : public CObject
{
public:
	UINT m_commandID;
	CString m_caption;
	HICON m_icon;
	CObArray* m_subCommands;
};

#endif //_WINPROMOPLUGININTERFACE_H_
