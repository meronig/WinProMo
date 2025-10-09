/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _PROMOMODELPROPERTY_H_
#define _PROMOMODELPROPERTY_H_
#include "../StdAfx.h"

#define TYPE_UNKNOWN   0
#define TYPE_INT       1
#define TYPE_DOUBLE    2
#define TYPE_STRING    3
#define TYPE_BOOL      4

class AFX_EXT_CLASS CProMoModelProperty :
    public CObject
{
public:
	CProMoModelProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, const BOOL& readOnly, const BOOL& showLabel);

    CString        m_name;
    unsigned int   m_type;
    COleVariant    m_value;
	BOOL		  m_readOnly;
	BOOL		  m_showLabel;
};

#endif //_PROMOMODELPROPERTY_H_

