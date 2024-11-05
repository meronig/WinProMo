#ifndef _PROCESSENTITYCONTAINER_H_
#define _PROCESSENTITYCONTAINER_H_

#include "../DiagramEditor/DiagramEntityContainer.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProcessEntityBlock.h"

class CProcessEntityContainer : public CDiagramEntityContainer {
public:
	// Construction/initialization/destruction
	CProcessEntityContainer();
	virtual ~CProcessEntityContainer();

	// Implementation

	// Selection
	int					GetSelectCount();
	CProcessEntityBlock* GetPrimarySelected();
	CProcessEntityBlock* GetSecondarySelected();

	// Overrides
	virtual void	RemoveAt(int index);

	virtual void	Undo();
	virtual void	Snapshot();
	virtual void	ClearUndo();

	virtual void reorder();
	virtual void SetTarget(CProcessEntityBlock* obj, BOOL select);
	virtual CProcessEntityBlock* getTarget();

private:
	// Private helpers
	double	Dist(CPoint point1, CPoint point2);
	void reorderR(CProcessEntityBlock* block, CObArray* m_newOrder);
	void removeR(CProcessEntityBlock* block);
};
#endif //_PROCESSENTITYCONTAINER_H_
