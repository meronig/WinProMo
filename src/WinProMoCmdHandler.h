#ifndef _PROMOCOMMANDHANDLER_H_
#define _PROMOCOMMANDHANDLER_H_

#include "ProMoEditor/ProMoEditor.h"

class AFX_EXT_CLASS CWinProMoCmdHandler :
    public CObject
{
public:
    CWinProMoCmdHandler();
    virtual ~CWinProMoCmdHandler();

    virtual BOOL OnPluginCommand(UINT cmdID) = 0;
    virtual BOOL OnPluginUpdateCommandUI(CCmdUI * pCmdUI) = 0;
    virtual CProMoEditor* GetEditor() = 0;

};

#endif //_PROMOCOMMANDHANDLER_H_

