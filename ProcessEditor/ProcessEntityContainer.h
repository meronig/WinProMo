#ifndef _PROCESSENTITYCONTAINER_H_
#define _PROCESSENTITYCONTAINER_H_

#include "../DiagramEditor/DiagramEntityContainer.h"
//#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProcessEntityBlockView.h"

class CProcessEntityContainer : public CDiagramEntityContainer {
public:
	// Construction/initialization/destruction
	CProcessEntityContainer();
	virtual ~CProcessEntityContainer();

	// Implementation

	// Selection
	int					GetSelectCount();
	CProcessEntityBlockView* GetPrimarySelected();
	CProcessEntityBlockView* GetSecondarySelected();

	// Overrides
	virtual void	RemoveAt(int index);

	virtual void reorder();
	virtual void SetTarget(CProcessEntityBlockView* obj, BOOL select);
	virtual CProcessEntityBlockView* getTarget();

	void ReplicateRelations(CObArray* source, CObArray* destination);

protected:
	// Overrides
	void			AddCurrentToStack(CObArray& arr);
	void			GetCurrentFromStack(CObArray& arr);


private:
	// Private helpers
	double	Dist(CPoint point1, CPoint point2);
	void reorderR(CProcessEntityBlockView* block, CObArray* m_newOrder);
	void removeR(CProcessEntityBlockView* block);
};
#endif //_PROCESSENTITYCONTAINER_H_
