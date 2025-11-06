/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOPROPERTY_H_
#define _PROMOPROPERTY_H_

#include "../StdAfx.h"
#include "ProMoModel.h"
#include "ProMoPropertyOwner.h"
#include <afxtempl.h>
#include "../FileUtils/VariantWrapper.h"

#define PROPTYPE_COMPOSITE     0
#define PROPTYPE_INT       1
#define PROPTYPE_DOUBLE    2
#define PROPTYPE_STRING    3
#define PROPTYPE_BOOL      4
#define PROPTYPE_UNKNOWN   999

class AFX_EXT_CLASS CProMoProperty :
    public CObject
{
protected:
	typedef BOOL(*ValidationFuction)(CProMoProperty*, const CVariantWrapper& newVal);
	typedef BOOL(*ChangeFuction)(CProMoProperty*, const CVariantWrapper& newVal);
	typedef BOOL(*EditFunction)(CProMoProperty*, CWnd*);
	ValidationFuction m_validationFunction;
	ChangeFuction m_changeFunction;
	EditFunction m_editFunction;
	CString			m_name;
	unsigned int	m_type;
	CVariantWrapper		m_value;
	BOOL			m_readOnly;
	BOOL			m_labelVisible;
	BOOL			m_persistent;
	IProMoPropertyOwner*	m_owner;
	CObArray		m_options;
	CProMoProperty* m_parentProperty;
	CProMoProperty* m_template;
	CObArray		m_childProperties;

public:
	CProMoProperty(const CString& name, const unsigned int& type, const CVariantWrapper& initValue,
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner,
		ValidationFuction valFct, ChangeFuction changeFct, EditFunction editFct,
		CProMoProperty* parent, CProMoProperty* templ);
	CProMoProperty(const CString& name, const unsigned int& type, const CVariantWrapper& initValue,
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner,
		ValidationFuction valFct, ChangeFuction changeFct);
	CProMoProperty(const CString& name, const unsigned int& type, const CVariantWrapper& initValue,
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner);
	virtual ~CProMoProperty();
	virtual BOOL SetValue(const CVariantWrapper& val);
	virtual CVariantWrapper& GetValue();
	virtual const CString& GetName();
	virtual const unsigned int& GetType();
	virtual BOOL IsReadOnly() const;
	virtual BOOL IsLabelVisible() const;
	virtual BOOL IsPersistent() const;
	virtual BOOL HasHandler() const;
	virtual BOOL IsMultiValue() const;
	virtual BOOL InvokeHandler(CWnd* parent);

	virtual CProMoProperty* Clone();
	
	virtual CProMoProperty* AddChild();
	virtual void ClearChildren();
	virtual int GetChildrenCount() const;
	virtual CProMoProperty* GetChild(const int& index) const;

	virtual CProMoProperty* AddOption();
	virtual int GetOptionsCount() const;
	virtual CProMoProperty* GetOption(const int& index);

	
	virtual CString GetFullName() const;
	
	static CString GetElementFromString(const CString& str);
	virtual BOOL	FromString(const CString& str);
	virtual CString	GetString() const;
	
	BOOL			LoadFromString(CString& data);


protected:
	CProMoProperty();
	virtual CString				GetDefaultGetString() const;
	virtual CString				GetHeaderFromString(CString& str);
	virtual BOOL				GetDefaultFromString(CString& str);
	
	virtual CProMoProperty* HandleChild(const CString& str);
};

#endif //_PROMOPROPERTY_H_

