/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOPROPERTY_H_
#define _PROMOPROPERTY_H_
#include "../StdAfx.h"
#include "ProMoModel.h"
#include "ProMoPropertyOwner.h"

#define TYPE_UNKNOWN   0
#define TYPE_INT       1
#define TYPE_DOUBLE    2
#define TYPE_STRING    3
#define TYPE_BOOL      4

class AFX_EXT_CLASS CProMoProperty :
    public CObject
{
protected:
	typedef BOOL(*ValidationFuction)(CProMoProperty*, const COleVariant& newVal);
	typedef BOOL(*ChangeFuction)(CProMoProperty*, const COleVariant& newVal);
	typedef BOOL(*EditFunction)(CProMoProperty*, CWnd*);
	ValidationFuction m_validationFunction;
	ChangeFuction m_changeFunction;
	EditFunction m_editFunction;
	CString        m_name;
	unsigned int   m_type;
	COleVariant    m_value;
	BOOL		  m_readOnly;
	BOOL		  m_labelVisible;
	BOOL		  m_persistent;
	IProMoPropertyOwner* m_owner;
	CArray <COleVariant, COleVariant> m_options;

public:
	CProMoProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue,
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner,
		ValidationFuction valFct, ChangeFuction changeFct, EditFunction editFct);
	CProMoProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue,
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner,
		ValidationFuction valFct, ChangeFuction changeFct);
	CProMoProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue,
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent, IProMoPropertyOwner* owner);
	virtual BOOL SetValue(const COleVariant& val);
	virtual COleVariant& GetValue();
	virtual void AddOption(const COleVariant& option);
	virtual int GetOptionsCount();
	virtual const COleVariant& GetOption(const int& index);
	virtual const CString& GetName();
	virtual const unsigned int& GetType();
	virtual const BOOL& IsReadOnly();
	virtual const BOOL& IsLabelVisible();
	virtual const BOOL& IsPersistent();
	virtual const BOOL& HasHandler();
	virtual BOOL InvokeHandler(CWnd* parent);
    
};

#endif //_PROMOPROPERTY_H_

