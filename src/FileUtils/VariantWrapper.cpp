/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CFileParser

	Author :		Giovanni Meroni

	Purpose :		"CVariantWrapper" is a class that encapsulates the
					VARIANT datatype, normally used for OLE and automation.

   ========================================================================*/
#include "stdafx.h"
#include "VariantWrapper.h"
#if _MSC_VER < 1400   // MSVC 4.x–6.x
#include <winnls.h>
#else
#include <windows.h>
#endif
#include <math.h>

CVariantWrapper::CVariantWrapper()
/* ============================================================
	Function :		CVariantWrapper::CVariantWrapper
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	
	============================================================*/
{
	VariantInit(&m_var);
}

CVariantWrapper::CVariantWrapper(const CVariantWrapper& var)
/* ============================================================
	Function :		CVariantWrapper::CVariantWrapper
	Description :	Copy constructor
	Access :		Public

	Return :		void
	Parameters :	none


	============================================================*/
{
	VariantInit(&m_var);
	VariantCopy(&m_var, (VARIANT*)&var.m_var);
}

CVariantWrapper& CVariantWrapper::operator=(const CVariantWrapper& var)
/* ============================================================
	Function :		CDoublePoint::operator=
	Description :	Assignment operator
	Access :		Public

   ============================================================*/
{
	if (this != &var)
	{
		VariantClear(&m_var);
		VariantCopy(&m_var, (VARIANT*)&var.m_var);
	}
	return *this;
}

CVariantWrapper::~CVariantWrapper()
/* ============================================================
	Function :		CProMoModel::~CProMoModel
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{
	VariantClear(&m_var);
}

void CVariantWrapper::Clear()
{
	VariantClear(&m_var);
	VariantInit(&m_var);
}

void CVariantWrapper::SetBool(const BOOL& val)
/* ============================================================
	Function :		CVariantWrapper::SetBool
	Description :	Sets the value of the variant to a boolean
					value
	Access :		Public

	Return :		void
	Parameters :	BOOL& val	-	The value to set.

   ============================================================*/
{
	Clear();
	m_var.vt = VT_BOOL;
	m_var.boolVal = val ? VARIANT_TRUE : VARIANT_FALSE;
}

void CVariantWrapper::SetInt(const int& val)
/* ============================================================
	Function :		CVariantWrapper::SetInt
	Description :	Sets the value of the variant to an integer
					value
	Access :		Public

	Return :		void
	Parameters :	int& val	-	The value to set.

   ============================================================*/
{
	Clear();
	m_var.vt = VT_I4;
	m_var.lVal = val;
}

void CVariantWrapper::SetDouble(const double& val)
/* ============================================================
	Function :		CVariantWrapper::SetDouble
	Description :	Sets the value of the variant to a floating
					point value
	Access :		Public

	Return :		void
	Parameters :	double& val	-	The value to set.

   ============================================================*/
{
	Clear();
	m_var.vt = VT_R8;
	m_var.dblVal = val;
}

void CVariantWrapper::SetString(const CString& val)
/* ============================================================
	Function :		CVariantWrapper::SetString
	Description :	Sets the value of the variant to a string 
					value
	Access :		Public

	Return :		void
	Parameters :	CString& val	-	The value to set.

   ============================================================*/
{
	Clear();
	m_var.vt = VT_BSTR;

#ifdef _UNICODE
    // CString already stores wide chars, just cast explicitly
    m_var.bstrVal = SysAllocString(val);
#else
    // Convert from ANSI to Unicode for SysAllocString
	int len = MultiByteToWideChar(CP_ACP, 0, val, -1, NULL, 0);
    OLECHAR* wideStr = new OLECHAR[len];
    MultiByteToWideChar(CP_ACP, 0, val, -1, wideStr, len);
    m_var.bstrVal = SysAllocString(wideStr);
    delete[] wideStr;
#endif

}

BOOL CVariantWrapper::SetFromString(const CString& val, const VARTYPE& type)
/* ============================================================
	Function :		CVariantWrapper::SetFromString
	Description :	Sets the value of the variant to a value of
					the specified type
	Access :		Public

	Return :		void
	Parameters :	CString& val	-	The value to set.
					VARTYPE& type	-	The type of value to set.

   ============================================================*/
{
	Clear();
	switch (type)
	{
	case VT_BSTR:
		SetString(val);
		break;
	case VT_I4:
#ifdef _UNICODE
		SetInt(_wtoi(val));
#else
		SetInt(atoi((LPCTSTR)val));
#endif
		break;
	case VT_R8:
#ifdef _UNICODE
		SetInt(_wtof(val));
#else
		SetInt(atof((LPCTSTR)val));
#endif
		break;
	case VT_BOOL:
#ifdef _UNICODE
		SetBool(_wtoi(val) != 0);
#else
		SetBool(atoi((LPCTSTR)val) != 0);
#endif
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CVariantWrapper::GetBool() const
/* ============================================================
	Function :		CVariantWrapper::GetBool
	Description :	Returns the value of the variant as a 
					boolean value
	Access :		Public

	Return :		BOOL&	-	The value of the variant.
	Parameters :	none

   ============================================================*/
{
	switch (m_var.vt)
	{
	case VT_BOOL:
		return m_var.boolVal == VARIANT_TRUE;
	case VT_I4:
		return m_var.lVal != 0;
	case VT_R8:
		return m_var.dblVal != 0;
	case VT_BSTR:
		return m_var.bstrVal && *m_var.bstrVal != 0;
	}
	return FALSE;
}

int CVariantWrapper::GetInt() const
/* ============================================================
	Function :		CVariantWrapper::GetInt
	Description :	Returns the value of the variant as an 
					integer value
	Access :		Public

	Return :		int&	-	The value of the variant.
	Parameters :	none

   ============================================================*/
{
	switch (m_var.vt)
	{
		case VT_I4:
			return m_var.lVal;
		case VT_BOOL:
			return GetBool();
		case VT_EMPTY:
		case VT_NULL:
			return 0;
	}
	return 0;
}

double CVariantWrapper::GetDouble() const
/* ============================================================
	Function :		CVariantWrapper::GetDouble
	Description :	Returns the value of the variant as a 
					floating point value
	Access :		Public

	Return :		double&		-	The value of the variant.
	Parameters :	none

   ============================================================*/
{
	switch (m_var.vt)
	{
	case VT_R8:
		return m_var.dblVal;
	}
	return GetInt();
}

CString CVariantWrapper::GetString() const
/* ============================================================
	Function :		CVariantWrapper::GetString
	Description :	Returns the value of the variant as a 
					string value
	Access :		Public

	Return :		CString&	-	The value of the variant.
	Parameters :	none

   ============================================================*/
{
	CString result;
	switch (m_var.vt)
	{
		case VT_BSTR:
			if (m_var.bstrVal) {
				result = CString(m_var.bstrVal);
			}
			break;
		case VT_R8:
			result.Format(_T("%f"), GetDouble());
			break;
		case VT_I4:
		case VT_BOOL:
			result.Format(_T("%d"), GetInt());
			break;
	}
	return result;
}

VARTYPE CVariantWrapper::GetType() const 
/* ============================================================
	Function :		CVariantWrapper::GetType
	Description :	Returns which type of value is stored in
					the variant
	Access :		Public

	Return :		VARTYPE	-	The type of value stored.
	Parameters :	none

   ============================================================*/
{
	return m_var.vt; 
}

VARIANT* CVariantWrapper::GetVARIANT()
/* ============================================================
	Function :		CVariantWrapper::GetVARIANT
	Description :	Returns the value of the variant
	Access :		Public

	Return :		VARIANT*	-	The value of the variant.
	Parameters :	none

   ============================================================*/
{
	return &m_var;
}

const VARIANT* CVariantWrapper::GetVARIANT() const
/* ============================================================
	Function :		CVariantWrapper::GetVARIANT
	Description :	Returns the value of the variant
	Access :		Public

	Return :		VARIANT*	-	The value of the variant.
	Parameters :	none

   ============================================================*/
{
	return &m_var;
}
