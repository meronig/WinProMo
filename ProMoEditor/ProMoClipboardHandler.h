#ifndef _PROMOCLIPBOARDHANDLER_H_
#define _PROMOCLIPBOARDHANDLER_H_

#include "../DiagramEditor/DiagramClipboardHandler.h"

class AFX_EXT_CLASS CProMoClipboardHandler : public CDiagramClipboardHandler
{
public:
// Construction/initialization/desturction
	CProMoClipboardHandler();
	virtual ~CProMoClipboardHandler();

	virtual CString GetModelType();

// Overrides
	virtual void	Copy( CDiagramEntity* obj );
	virtual void	Paste( CDiagramEntityContainer* container );
	virtual void	CopyAllSelected( CDiagramEntityContainer* container );

private:
// Private data
	CString m_modelType;
	
};

#endif // _PROMOCLIPBOARDHANDLER_H_