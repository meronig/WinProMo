#ifndef _PROMOCLIPBOARDHANDLER_H_
#define _PROMOCLIPBOARDHANDLER_H_

#include "../DiagramEditor/DiagramClipboardHandler.h"

class AFX_EXT_CLASS CProMoClipboardHandler : public CDiagramClipboardHandler
{
public:
// Construction/initialization/desturction
	CProMoClipboardHandler();
	virtual ~CProMoClipboardHandler();

// Overrides
	virtual void	Copy( CDiagramEntity* obj );
	virtual void	Paste( CDiagramEntityContainer* container );
	virtual void	CopyAllSelected( CDiagramEntityContainer* container );

private:
// Private data
	
};

#endif // _PROMOCLIPBOARDHANDLER_H_