#include "stdafx.h"
#include "VariantWrapper.h"

CVariantWrapper::CVariantWrapper()
{
	VariantInit(&m_var);
}

CVariantWrapper::CVariantWrapper(const CVariantWrapper& var)
{
	VariantInit(&m_var);
	VariantCopy(&m_var, (VARIANT*)&var.m_var);
}

CVariantWrapper& CVariantWrapper::operator=(const CVariantWrapper& var)
{
	if (this != &var)
	{
		VariantClear(&m_var);
		VariantCopy(&m_var, (VARIANT*)&var.m_var);
	}
	return *this;
}

CVariantWrapper::~CVariantWrapper()
{
	VariantClear(&m_var);
}

void CVariantWrapper::Clear()
{
	VariantClear(&m_var);
	VariantInit(&m_var);
}

void CVariantWrapper::SetBool(const BOOL& val)
{
	Clear();
	m_var.vt = VT_BOOL;
	m_var.boolVal = val ? VARIANT_TRUE : VARIANT_FALSE;
}

void CVariantWrapper::SetInt(const int& val)
{
	Clear();
	m_var.vt = VT_I4;
	m_var.lVal = val;
}

void CVariantWrapper::SetDouble(const double& val)
{
	Clear();
	m_var.vt = VT_R8;
	m_var.dblVal = val;
}

void CVariantWrapper::SetString(const CString& val)
{
	Clear();
	m_var.vt = VT_BSTR;
	m_var.bstrVal = SysAllocString(val);
}

BOOL CVariantWrapper::SetFromString(const CString& val, const VARTYPE& type)
{
	Clear();
	switch (type)
	{
	case VT_BSTR:
		SetString(val);
		break;
	case VT_I4:
		SetInt(_ttoi(val));
		break;
	case VT_R8:
		SetDouble(_ttof(val));
		break;
	case VT_BOOL:
		SetBool((_ttoi(val) != 0));
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CVariantWrapper::GetBool() const
{
	switch (m_var.vt)
	{
	case VT_BOOL:
		return m_var.boolVal == VARIANT_TRUE;
	case VT_I4:
		return m_var.lVal != 0;
	case VT_R8:
		return fabs(m_var.dblVal) > DBL_EPSILON;
	case VT_BSTR:
		return m_var.bstrVal && *m_var.bstrVal != 0;
	}
	return FALSE;
}

int CVariantWrapper::GetInt() const
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
{
	switch (m_var.vt)
	{
	case VT_R8:
		return m_var.dblVal;
	}
	return GetInt();
}

CString CVariantWrapper::GetString() const
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
{ 
	return m_var.vt; 
}

VARIANT* CVariantWrapper::GetVARIANT()
{
	return &m_var;
}

const VARIANT* CVariantWrapper::GetVARIANT() const
{
	return &m_var;
}
