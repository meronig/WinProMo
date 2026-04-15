/* ==========================================================================

    Copyright © 2025-26 Technical University of Denmark

    Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOCOMMANDHANDLER_H_
#define _PROMOCOMMANDHANDLER_H_

#include "ProMoEditor.h"

class AFX_EXT_CLASS CProMoCmdHandler :
    public CObject
{
public:
	CProMoCmdHandler(CProMoEditor* editor);
    virtual ~CProMoCmdHandler();

    virtual BOOL OnPluginCommand(UINT cmdID) = 0;
    virtual BOOL OnPluginUpdateCommandUI(CCmdUI * pCmdUI) = 0;
    virtual CProMoEditor* GetEditor();

private:
	CProMoEditor* m_editor;

};

#endif //_PROMOCOMMANDHANDLER_H_

