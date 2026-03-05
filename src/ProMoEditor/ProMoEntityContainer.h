/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOENTITYCONTAINER_H_
#define _PROMOENTITYCONTAINER_H_

#include "../DiagramEditor/DiagramEntityContainer.h"
#include "../DiagramEditor/Tokenizer.h"
#include "ProMoBlockView.h"
#include "ProMoControlFactory.h"
#include "ProMoProperty.h"
#include "../Automation/ProMoAutomationHost.h"

class AFX_EXT_CLASS CProMoEntityContainer : public CDiagramEntityContainer, public IProMoAutomationHost {
public:
	// Construction/initialization/destruction
	CProMoEntityContainer(CProMoControlFactory* factory, CDiagramClipboardHandler* clip = NULL);
	CProMoEntityContainer(CProMoControlFactory* factory, CString modelType, CDiagramClipboardHandler* clip = NULL);
	virtual ~CProMoEntityContainer();

	virtual void Reorder();
	virtual void SetTarget(CProMoBlockView* obj, unsigned int attachment);
	virtual CProMoBlockView* GetTarget() const;

	virtual CDiagramEntity* CloneEntity(IProMoEntity* obj);

	virtual void ReplicateRelations(const CObArray& source, CObArray& destination);
	virtual void Load(const CStringArray& stra);
	virtual void Save(CStringArray& stra);
	virtual void SaveObjects(CStringArray& stra);

	virtual CDiagramEntity* GetNamedView(const CString& name) const;
	virtual CProMoModel* GetNamedModel(const CObArray& array, const CString& name) const;

	virtual void GetModels(CObArray& models) const;
	virtual void GetLabels(CObArray& labels, BOOL ifDetached) const;
	
	virtual CProMoControlFactory* GetControlFactory() const;

	virtual CString GetModelType() const;

	virtual CSize	GetSelectionTotalSize();
	virtual CPoint	GetSelectionStartPoint();

protected:
	void LoadModels(const CStringArray& stra, CObArray& models);
	void LoadViews(const CStringArray& stra, const CObArray& models);
	void LoadLabels(const CStringArray& stra, const CObArray& models);
	void LoadProperties(const CStringArray& stra, const CObArray& models);
	void LinkModels(const CStringArray& stra, const CObArray& models);
	void LinkViews(const CStringArray& stra, const CObArray& models);

	void SaveProperties(CStringArray& stra, CProMoProperty* prop);
private:
	// Private helpers
	void ReorderR(CProMoBlockView* block, CObArray& m_newOrder);
	CString m_modelType;
	CProMoAppChildAuto* m_autoObject;
	CProMoControlFactory* m_factory;

// Implements
public:
	virtual CProMoAppChildAuto* GetAutomationObject();
	virtual void ReleaseAutomationObject();

// Overrides
public:
	int				GetSelectCount();
	virtual void	RemoveAt(int index);

	virtual void	Duplicate(CDiagramEntity* obj);

	virtual CString GetString() const;
	virtual BOOL FromString(const CString& str);

	virtual int ObjectsInPaste();

protected:
	void			AddCurrentToStack(CObArray& arr);
	void			GetCurrentFromStack(CObArray& arr);

};

#endif //_PROMOENTITYCONTAINER_H_
