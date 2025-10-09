/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CPropertyItem

	Author :		Giovanni Meroni

	Purpose :		"CProMoModelProperty" is a class to keep track of custom
					model properties and on how they should be displayed.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoModelProperty.h"

CProMoModelProperty::CProMoModelProperty(const CString& name, const unsigned int& type, const COleVariant& initialValue, const BOOL& readOnly, const BOOL& showLabel)
/* ============================================================
	Function :		CProMoModelProperty::CProMoModelProperty
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	const CString& name			-	Name of the
													property 
													to change 
					unsigned int& type			-	Type of the 
													property
					COleVariant& initialValue	-	Initial value
													of the
													property
					BOOL& readOnly				-	"TRUE" if the
													property is
													read-only
					BOOL& showLabel				-	"TRUE" if the
													property should
													be shown as a
													label

   ============================================================*/
{
	m_name = name;
	m_type = type;
	m_value = initialValue;
	m_readOnly = readOnly;
	m_showLabel = showLabel;
}
