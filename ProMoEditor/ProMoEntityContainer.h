#ifndef _PROMOENTITYCONTAINER_H_
#define _PROMOENTITYCONTAINER_H_

#include "../DiagramEditor/DiagramEntityContainer.h"
//#include "../DiagramEditor/DiagramEntity.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoBlockView.h"

class CProMoEntityContainer : public CDiagramEntityContainer {
public:
	// Construction/initialization/destruction
	CProMoEntityContainer();
	virtual ~CProMoEntityContainer();

	// Implementation

	// Selection
	int					GetSelectCount();
	CProMoBlockView* GetPrimarySelected();
	CProMoBlockView* GetSecondarySelected();

	// Overrides
	virtual void	RemoveAt(int index);

	virtual void reorder();
	virtual void SetTarget(CProMoBlockView* obj, BOOL select);
	virtual CProMoBlockView* getTarget();

	void ReplicateRelations(CObArray* source, CObArray* destination);

protected:
	// Overrides
	void			AddCurrentToStack(CObArray& arr);
	void			GetCurrentFromStack(CObArray& arr);


private:
	// Private helpers
	double	Dist(CPoint point1, CPoint point2);
	void reorderR(CProMoBlockView* block, CObArray* m_newOrder);
	void removeR(CProMoBlockView* block);
};
#endif //_PROMOENTITYCONTAINER_H_
