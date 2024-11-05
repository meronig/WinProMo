#ifndef _PROCESSCLIPBOARDHANDLER_H_
#define _PROCESSCLIPBOARDHANDLER_H_

#include "../DiagramEditor/DiagramClipboardHandler.h"

class CProcessClipboardHandler : public CDiagramClipboardHandler
{
public:
// Construction/initialization/desturction
	CProcessClipboardHandler();
	virtual ~CProcessClipboardHandler();

// Overrides
	virtual void	Copy( CDiagramEntity* obj );
	virtual void	Paste( CDiagramEntityContainer* container );
	virtual void	CopyAllSelected( CDiagramEntityContainer* container );
	virtual void	ClearPaste();

private:
// Private data
	void ReplicateRelations(CObArray* source, CObArray* destination);

};

#endif // _PROCESSCLIPBOARDHANDLER_H_