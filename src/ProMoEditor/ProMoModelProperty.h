/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOMODELPROPERTY_H_
#define _PROMOMODELPROPERTY_H_
#include "../StdAfx.h"
#include "ProMoModel.h"

#define TYPE_UNKNOWN   0
#define TYPE_INT       1
#define TYPE_DOUBLE    2
#define TYPE_STRING    3
#define TYPE_BOOL      4

class AFX_EXT_CLASS CProMoModelProperty :
    public CObject
{
protected:
	typedef BOOL(*ValidationFuction)(CProMoModelProperty*, const COleVariant& newVal);
	typedef BOOL(*ChangeFuction)(CProMoModelProperty*, const COleVariant& newVal);
	ValidationFuction m_validationFunction;
	ChangeFuction m_changeFunction;
	CString        m_name;
	unsigned int   m_type;
	COleVariant    m_value;
	BOOL		  m_readOnly;
	BOOL		  m_labelVisible;
	BOOL		  m_persistent;
	CProMoModel* m_model;
	CArray <COleVariant, COleVariant> m_options;

public:
	CProMoModelProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, 
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent, CProMoModel* model,
		ValidationFuction validationFct, ChangeFuction changeFct);
	CProMoModelProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue,
		const BOOL& readOnly, const BOOL& showLabel, const BOOL& persistent);
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
    
};

#endif //_PROMOMODELPROPERTY_H_

