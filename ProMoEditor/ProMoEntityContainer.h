#ifndef _PROMOENTITYCONTAINER_H_
#define _PROMOENTITYCONTAINER_H_

#include "../DiagramEditor/DiagramEntityContainer.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoBlockView.h"

class AFX_EXT_CLASS CProMoEntityContainer : public CDiagramEntityContainer {
public:
	// Construction/initialization/destruction
	CProMoEntityContainer();
	virtual ~CProMoEntityContainer();

	virtual void Reorder();
	virtual void SetTarget(CProMoBlockView* obj, BOOL select);
	virtual CProMoBlockView* GetTarget();

	void ReplicateRelations(CObArray* source, CObArray* destination);

private:
	// Private helpers
	void ReorderR(CProMoBlockView* block, CObArray* m_newOrder);

// Overrides
public:
	int				GetSelectCount();
	virtual void	RemoveAt(int index);

protected:
	void			AddCurrentToStack(CObArray& arr);
	void			GetCurrentFromStack(CObArray& arr);

};
#endif //_PROMOENTITYCONTAINER_H_
