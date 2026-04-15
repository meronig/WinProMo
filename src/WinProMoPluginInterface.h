/* ==========================================================================

	Copyright © 2025-26 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _WINPROMOPLUGININTERFACE_H_
#define _WINPROMOPLUGININTERFACE_H_

#include "ProMoEditor/ProMoClipboardHandler.h"
#include "ProMoEditor/ProMoEntityContainer.h"
#include "ProMoEditor/ProMoCmdHandler.h"
#include "ProMoEditor/ProMoRenderer.h"

class AFX_EXT_CLASS CWinProMoPluginInterface
{
public:
	CWinProMoPluginInterface(UINT documentID, const CString& documentType, const CString& documentDescrm, CProMoControlFactory* controlFactory);
	virtual ~CWinProMoPluginInterface();
	virtual CObArray* GetElements() = 0;
	virtual CObArray* GetCommands() = 0;
	virtual const CString& GetDocumentType();
	virtual const UINT& GetDocumentID();
	virtual const CString& GetDocumentDescr();
	virtual void Destroy();
	virtual CProMoControlFactory* GetControlFactory();
	virtual CProMoCmdHandler* GetCmdHandler() = 0;
	virtual CProMoEntityContainer* GetContainer();
	virtual CProMoRenderer* GetRenderer();

private:
	CString m_documentType;
	CString m_documentDescr;
	UINT m_documentID;
	CProMoControlFactory* m_controlFactory;
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
