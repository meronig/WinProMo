/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOMODEL_H_
#define _PROMOMODEL_H_

#include "../StdAfx.h"
#include "../DiagramEditor/DiagramEntity.h"
#include "ProMoPropertyOwner.h"
#include "../FileUtils/VariantWrapper.h"
#include <afxdisp.h>

class AFX_EXT_CLASS CProMoLabel;

class AFX_EXT_CLASS CProMoProperty;

class AFX_EXT_CLASS CProMoModel : public CObject, public IProMoPropertyOwner
{
public:
	friend class CProMoLabel;

	// Creation/initialization
	CProMoModel();
	virtual ~CProMoModel();
	
	virtual CProMoModel* Clone();
	virtual void	Copy(CProMoModel* obj);


	// Model-view links
	virtual CObArray* GetViews();

	virtual BOOL	FromString(const CString& str);
	virtual CString	Export(UINT format = 0) const;
	virtual CString	GetString() const;
	static	CProMoModel* CreateFromString(const CString& str);

	BOOL			LoadFromString(CString& data);

	// Standard properties
	CString			GetType() const;
	void			SetType(CString type);

	virtual CString	GetName() const;
	virtual void	SetName(CString name);

	// Custom properties
	virtual void GetPropertyNames(CStringArray& array, const BOOL& recursive) const;
	virtual unsigned int GetPropertyType(const CString& name) const;
	virtual const CVariantWrapper& GetPropertyValue(const CString& name) const;
	virtual BOOL SetPropertyValue(const CString& name, const CVariantWrapper& value);
	virtual unsigned int GetPropertiesCount() const;
	virtual CProMoProperty* GetProperty(const int& index) const;
	virtual CProMoProperty* FindProperty(const CString& name) const;

	static CString GetNameFromString(const CString& str);

	// Labels
	virtual CObArray* GetLabels();
	virtual CProMoLabel* GetLabel(CString property);
	virtual CObArray* RecreateLabels();
	

protected:
	CObArray m_views;
	CObArray m_labels;
	CObArray m_properties;

	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);

	virtual void LinkView(CDiagramEntity* view);
	virtual void UnlinkView(CDiagramEntity* view);
	virtual void UnlinkAllViews();
	
	virtual void LinkLabel(CProMoLabel* label);
	virtual void UnlinkLabel(CProMoLabel* label);
	virtual void UnlinkAllLabels();
	virtual void CustomizeLabels();
	virtual void CustomizeLabel(CProMoLabel* label);
	
	virtual void CreateProperties();
	virtual void AddProperty(CProMoProperty* prop);
	virtual void ClearProperties();
	
	virtual CProMoProperty* FindPropertyR(const CString& name, CProMoProperty* parent) const;
	virtual void RecreateLabelsR(CObArray& list, CProMoProperty* parent);
	virtual void GetPropertyNamesR(CStringArray& array, CProMoProperty* parent) const;

private:
	CString m_type;
	CString m_name;

	// implements
public:
	virtual void OnPropertyChanged(CProMoProperty* prop);

};

#endif //_PROMOMODEL_H_