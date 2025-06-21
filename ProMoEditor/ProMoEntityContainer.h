#ifndef _PROMOENTITYCONTAINER_H_
#define _PROMOENTITYCONTAINER_H_

#include "../DiagramEditor/DiagramEntityContainer.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoBlockView.h"
#include "ProMoControlFactory.h"

class AFX_EXT_CLASS CProMoEntityContainer : public CDiagramEntityContainer {
public:
	// Construction/initialization/destruction
	CProMoEntityContainer(CDiagramClipboardHandler* clip = NULL);
	CProMoEntityContainer(CString modelType, CDiagramClipboardHandler* clip = NULL);
	virtual ~CProMoEntityContainer();

	virtual void Reorder();
	virtual void SetTarget(CProMoBlockView* obj, BOOL select);
	virtual CProMoBlockView* GetTarget();

	virtual void ReplicateRelations(CObArray* source, CObArray* destination);
	virtual void Load(const CStringArray& stra, CProMoControlFactory& fact);
	virtual void Save(CStringArray& stra);
	virtual void SaveObjects(CStringArray& stra);

	virtual CDiagramEntity* GetNamedView(const CString& name) const;
	virtual CString GetModelType() const;

protected:
	CProMoModel* GetNamedModel(const CObArray& array, const CString& name) const;
	void DeleteModel(CObArray& array, const CString& name);

private:
	// Private helpers
	void ReorderR(CProMoBlockView* block, CObArray* m_newOrder);
	CString m_modelType;


// Overrides
public:
	int				GetSelectCount();
	virtual void	RemoveAt(int index);

	virtual CString GetString() const;
	virtual BOOL FromString(const CString& str);

	virtual int ObjectsInPaste();

protected:
	void			AddCurrentToStack(CObArray& arr);
	void			GetCurrentFromStack(CObArray& arr);

};
#endif //_PROMOENTITYCONTAINER_H_
