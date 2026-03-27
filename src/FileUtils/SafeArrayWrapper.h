/* ==========================================================================

    Copyright © 2026 Technical University of Denmark

    Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _SAFEARRAYWRAPPER_H_
#define _SAFEARRAYWRAPPER_H_

#include "../StdAfx.h"

class AFX_EXT_CLASS CSafeArrayWrapper
{
public:
    CSafeArrayWrapper();
    CSafeArrayWrapper(const CSafeArrayWrapper& src);          // deep copy
    ~CSafeArrayWrapper();

    CSafeArrayWrapper& operator=(const CSafeArrayWrapper& src);

    static HRESULT CreateVariantFromCStringArray(
        const CStringArray& arr,
        VARIANT& var);

    BOOL Create(VARTYPE vt, DWORD dwDims, SAFEARRAYBOUND* pBounds);
    void Destroy();

    BOOL Attach(SAFEARRAY* psa);
    SAFEARRAY* Detach();

    SAFEARRAY* GetSafeArray() const { return m_psa; }

    // Element access
    HRESULT PutElement(LONG* pIndices, void* pvData);
    HRESULT GetElement(LONG* pIndices, void* pvData) const;

    // Bulk access
    HRESULT AccessData(void** ppData);
    HRESULT UnaccessData();

    // Info
    UINT GetDim() const;
    HRESULT GetLBound(UINT nDim, LONG* plLBound) const;
    HRESULT GetUBound(UINT nDim, LONG* plUBound) const;
    
private:
    void CopyFrom(const CSafeArrayWrapper& src);

private:
    SAFEARRAY* m_psa;
};

#endif //_SAFEARRAYWRAPPER_H_