/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _WINPROMOPLUGININTERFACE_H_
#define _WINPROMOPLUGININTERFACE_H_

#include "ProMoEditor/ProMoClipboardHandler.h"
#include "ProMoEditor/ProMoEntityContainer.h"
#include "WinProMoCmdHandler.h"
#include "ProMoEditor/ProMoRenderer.h"

class CWinProMoPluginInterface
{
public:
	virtual ~CWinProMoPluginInterface() {}
	virtual CObArray* GetElements() = 0;
	virtual CObArray* GetCommands() = 0;
	virtual const CString GetDocumentType() = 0;
	virtual const UINT GetDocumentID() = 0;
	virtual void Destroy() = 0;
	virtual CWinProMoCmdHandler* GetCmdHandler() = 0;
	virtual CProMoEntityContainer* GetContainer() = 0;
	virtual CProMoControlFactory* GetControlFactory() = 0;
	virtual CProMoRenderer* GetRenderer() = 0;
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
