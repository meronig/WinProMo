/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _VARIANTWRAPPER_H_
#define _VARIANTWRAPPER_H_

//#include <variant.h>
#include "../StdAfx.h"

class AFX_EXT_CLASS CVariantWrapper
{
public:
	CVariantWrapper();
	CVariantWrapper(const CVariantWrapper& var);
	
	CVariantWrapper& operator=(const CVariantWrapper& var);
	virtual ~CVariantWrapper();
	virtual void Clear();
	virtual void SetBool(const BOOL& val);
	virtual void SetInt(const int& val);
	virtual void SetDouble(const double& val);
	virtual void SetString(const CString& val);
	virtual BOOL SetFromString(const CString& val, const VARTYPE& type);

	virtual BOOL GetBool() const;
	virtual int GetInt() const;
	virtual double GetDouble() const;
	virtual CString GetString() const;

	virtual VARTYPE GetType() const;
	virtual VARIANT* GetVARIANT();
	virtual const VARIANT* GetVARIANT() const;

private:
	VARIANT m_var;
	
	virtual BOOL ParseInt(const CString& str, int& outValue);
	virtual BOOL ParseDouble(const CString& str, double& outValue);
};
#endif //_VARIANTWRAPPER_H_
