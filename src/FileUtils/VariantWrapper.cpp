/* ==========================================================================

	Copyright © 2025-26 Technical University of Denmark

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

CVariantWrapper::CVariantWrapper(const VARIANT& var)
/* ============================================================
	Function :		CVariantWrapper::CVariantWrapper
	Description :	Constructor from VARIANT
	Access :		Public
	Return :		void
	Parameters :	const VARIANT& var	-	The VARIANT to copy.

	============================================================*/
{
	VariantInit(&m_var);
	(void)VariantCopy(&m_var, (VARIANT*)&var);
	NormalizeVariant();
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
	(void)VariantCopy(&m_var, (VARIANT*)&var.m_var);
	NormalizeVariant();
}

CVariantWrapper& CVariantWrapper::operator=(const CVariantWrapper& var)
/* ============================================================
	Function :		CVariantWrapper::operator=
	Description :	Assignment operator
	Access :		Public

   ============================================================*/
{
	if (this != &var)
	{
		VariantClear(&m_var);
		(void)VariantCopy(&m_var, (VARIANT*)&var.m_var);
		NormalizeVariant();
	}
	return *this;
}

CVariantWrapper::~CVariantWrapper()
/* ============================================================
	Function :		CVariantWrapper::~CVariantWrapper
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
/* ============================================================
	Function :		CVariantWrapper::Clear
	Description :	Clears the value
	Access :		Public

	Return :		void
	Parameters :	none

   ============================================================*/
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

void CVariantWrapper::SetVariant(const VARIANT& val)
/* ============================================================
	Function :		CVariantWrapper::SetVariant
	Description :	Sets the value of the variant to another
					variant value
	Access :		Public

	Return :		void
	Parameters :	VARIANT& val	-	The value to set.
   ============================================================*/
{
	Clear();
	(void)VariantCopy(&m_var, (VARIANT*)&val);
	NormalizeVariant();
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
	BOOL result = FALSE;
	int intVal = 0;
	double dblVal = 0;
	switch (type)
	{
	case VT_BSTR:
		result = TRUE;
		SetString(val);
		break;
	case VT_I4:
		result = ParseInt(val, intVal);
		if (result) {
			SetInt(intVal);
		}
		break;
	case VT_R8:
		result = ParseDouble(val, dblVal);
		if (result) {
			SetDouble(dblVal);
		}
		break;
	case VT_BOOL:
		result = ParseInt(val, intVal);
		if (result) {
			if (intVal == 0) {
				SetBool(FALSE);
			}
			else {
				SetBool(TRUE);
			}
		}
		break;
	default:
		return FALSE;
	}
	return result;
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
	case VT_EMPTY:
	case VT_NULL:
	case VT_ERROR:
		return FALSE;
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
		case VT_BSTR:
		{
			int val = 0;
			ParseInt(m_var.bstrVal ? CString(m_var.bstrVal) : _T(""), val);
			return val;
		}
		case VT_R8:
			return (int)GetDouble();
		case VT_BOOL:
			return GetBool();
		case VT_EMPTY:
		case VT_NULL:
		case VT_ERROR:
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
	case VT_BSTR:
	{
		double val = 0.0;
		ParseDouble(m_var.bstrVal ? CString(m_var.bstrVal) : _T(""), val);
		return val;
	}
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
		case VT_EMPTY:
		case VT_NULL:
		case VT_ERROR:
			result = _T(""); // Safe default
			break;
		default:
			result = _T(""); // Unknown type fallback
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

void CVariantWrapper::NormalizeVariant()
/* ============================================================
	Function :		CVariantWrapper::NormalizeVariant
	Description :	Normalizes the input VARIANT by dereferencing
					it and casting the content to the most 
					expressive data type
	Access :		Private

	Return :		void
	Parameters :	none

   ============================================================*/
{
	// Handle ByRef
	if (m_var.vt & VT_BYREF)
	{
		VARTYPE baseType = m_var.vt & ~VT_BYREF;

		switch (baseType)
		{
		case VT_I2:
			if (m_var.piVal)
				m_var.iVal = *m_var.piVal;
			break;
		case VT_I4: 
			if (m_var.plVal)
				m_var.lVal = *m_var.plVal;
			break;
		case VT_R4:
			if (m_var.pfltVal)
				m_var.fltVal = *m_var.pfltVal;
			break;
		case VT_R8: 
			if (m_var.pdblVal)
				m_var.dblVal = *m_var.pdblVal; 
			break;
		case VT_BOOL:
			if (m_var.piVal)
				m_var.boolVal = *m_var.piVal; 
			break;
		case VT_BSTR: 
			VariantClear(&m_var);
			m_var.bstrVal = SysAllocString(*m_var.pbstrVal); 
			break;
		default: 
			break; // Keep original if unknown
		}

		m_var.vt = baseType;
	}
	
	// Normalize datatypes
	switch (m_var.vt)
	{
	case VT_I2:
		m_var.lVal = m_var.iVal;
		m_var.vt = VT_I4;
		break;

	case VT_R4:
		m_var.dblVal = m_var.fltVal;
		m_var.vt = VT_R8;
		break;
	case VT_ERROR:
		VariantClear(&m_var);
		m_var.vt = VT_EMPTY;
		break;
	}
}

BOOL CVariantWrapper::ParseInt(const CString& str, int& outValue)
/* ============================================================
	Function :		CVariantWrapper::ParseInt
	Description :	Tries to parse an input string into an integer
	Access :		Private

	Return :		BOOL			-	"TRUE" if the string
										was correctly parsed,
										"FALSE" otherwise.
	Parameters :	CString str		-	The string to parse.
					int outValue	-	The integer value parsed
										from the input string

   ============================================================*/
{
	if (str.IsEmpty())
		return FALSE;
#ifdef _UNICODE
	const wchar_t* start = str;
	wchar_t* end = NULL;
	long val = wcstol(start, &end, 10);
#else
	const char* start = str;
	char* end = NULL;
	long val = strtol(start, &end, 10);
#endif
	if (end == start)
		return FALSE;
	outValue = static_cast<int>(val);
	return TRUE;
}

BOOL CVariantWrapper::ParseDouble(const CString& str, double& outValue)
/* ============================================================
	Function :		CVariantWrapper::ParseDouble
	Description :	Tries to parse an input string into a double
	Access :		Private

	Return :		BOOL			-	"TRUE" if the string
										was correctly parsed,
										"FALSE" otherwise.
	Parameters :	CString str		-	The string to parse.
					double outValue	-	The double value parsed
										from the input string

   ============================================================*/
{
	if (str.IsEmpty())
		return FALSE;
#ifdef _UNICODE
	const wchar_t* start = str;
	wchar_t* end = NULL;
	double val = wcstod(start, &end);
#else
	const char* start = str;
	char* end = NULL;
	double val = strtod(start, &end);
#endif
	if (end == start)
		return FALSE;
	outValue = val;
	return TRUE;
}
