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
	void Clear();
	void SetBool(const BOOL& val);
	void SetInt(const int& val);
	void SetDouble(const double& val);
	void SetString(const CString& val);
	BOOL SetFromString(const CString& val, const VARTYPE& type);

	BOOL GetBool() const;
	int GetInt() const;
	double GetDouble() const;
	CString GetString() const;

	VARTYPE GetType() const;
	VARIANT* GetVARIANT();
	const VARIANT* GetVARIANT() const;

private:
	VARIANT m_var;
};
#endif //_VARIANTWRAPPER_H_
