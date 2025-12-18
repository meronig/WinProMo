#ifndef _PROMOCOMMANDHANDLER_H_
#define _PROMOCOMMANDHANDLER_H_

#include "ProMoEditor.h"

class AFX_EXT_CLASS CProMoCmdHandler :
    public CObject
{
public:
    virtual ~CProMoCmdHandler() {};

    virtual BOOL OnPluginCommand(UINT cmdID) = 0;
    virtual BOOL OnPluginUpdateCommandUI(CCmdUI * pCmdUI) = 0;
    virtual CProMoEditor* GetEditor() = 0;

};

#endif //_PROMOCOMMANDHANDLER_H_

