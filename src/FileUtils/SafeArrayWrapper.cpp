/* ==========================================================================

    Copyright © 2026 Technical University of Denmark

    CSafeArrayWrapper

    Author :		Giovanni Meroni

    Purpose :		"CSafeArrayWrapper" is a class that encapsulates the
                    SAFEARRAY datatype, normally used for OLE and automation.

   ========================================================================*/
#include "stdafx.h"
#include "SafeArrayWrapper.h"

CSafeArrayWrapper::CSafeArrayWrapper()
/* ============================================================
    Function :		CSafeArrayWrapper::CSafeArrayWrapper
    Description :	Constructor
    Access :		Public

    Return :		void
    Parameters :	none


    ============================================================*/
{
    m_psa = NULL;
}

CSafeArrayWrapper::~CSafeArrayWrapper()
/* ============================================================
    Function :		CSafeArrayWrapper::~CSafeArrayWrapper
    Description :	Destructor
    Access :		Public

    Return :		void
    Parameters :	none


    ============================================================*/
{
    Destroy();
}

void CSafeArrayWrapper::Destroy()
/* ============================================================
    Function :		CSafeArrayWrapper::Destroy
    Description :	Destroys the SAFEARRAY if it exists
    Access :		Public
    Return :		void
	Parameters :	none
	============================================================*/
{
    if (m_psa)
    {
        SafeArrayDestroy(m_psa);
        m_psa = NULL;
    }
}

BOOL CSafeArrayWrapper::Create(VARTYPE vt, DWORD dwDims, SAFEARRAYBOUND* pBounds)
/* ============================================================
    Function :		CSafeArrayWrapper::Create
    Description :	Creates a SAFEARRAY with the specified parameters
    Access :		Public
    Return :		BOOL	                -	TRUE if creation 
                                                succeeded, FALSE 
                                                otherwise.
    Parameters :	VARTYPE vt				-	The VARTYPE of 
                                                the elements in 
                                                the array.
                    DWORD dwDims			-	The number of 
                                                dimensions of 
                                                the array.
                    SAFEARRAYBOUND* pBounds	-	Array of 
                                                SAFEARRAYBOUND 
                                                structures 
                                                specifying the 
                                                bounds for each 
                                                dimension.
	============================================================*/
{
    Destroy();

    m_psa = SafeArrayCreate(vt, dwDims, pBounds);
    return (m_psa != NULL);
}

BOOL CSafeArrayWrapper::Attach(SAFEARRAY* psa)\
/* ============================================================
    Function :		CSafeArrayWrapper::Attach
    Description :	Attaches an existing SAFEARRAY to the wrapper.
                    The wrapper will take ownership of the 
                    SAFEARRAY and will destroy it when the 
                    wrapper is destroyed or when another array is 
                    attached.
    Access :		Public
    Return :		BOOL	        -	TRUE if attachment 
                                        succeeded, FALSE 
                                        otherwise.
    Parameters :	SAFEARRAY* psa	-	The SAFEARRAY to 
                                        attach.
	============================================================*/
{
    Destroy();
    m_psa = psa;
    return TRUE;
}

SAFEARRAY* CSafeArrayWrapper::Detach()
/* ============================================================
    Function :		CSafeArrayWrapper::Detach
    Description :	Detaches the SAFEARRAY from the wrapper and 
                    returns it. The caller takes ownership of the 
                    SAFEARRAY and is responsible for destroying it.
    Access :		Public
    Return :		SAFEARRAY*	    -	The detached SAFEARRAY, or 
                                        NULL if there was no 
                                        SAFEARRAY attached.
    Parameters :	none
	============================================================*/
{
    SAFEARRAY* psa = m_psa;
    m_psa = NULL;
    return psa;
}

CSafeArrayWrapper::CSafeArrayWrapper(const CSafeArrayWrapper& src)
/* ============================================================
    Function :		CSafeArrayWrapper::CSafeArrayWrapper
    Description :	Copy constructor
    Access :		Public

    Return :		void
    Parameters :	none


    ============================================================*/
{
    m_psa = NULL;
    CopyFrom(src);
}

CSafeArrayWrapper& CSafeArrayWrapper::operator=(const CSafeArrayWrapper& src)
/* ============================================================
    Function :		CSafeArrayWrapper::operator=
    Description :	Assignment operator
    Access :		Public

   ============================================================*/
{
    if (this != &src)
    {
        Destroy();
        CopyFrom(src);
    }
    return *this;
}

HRESULT CSafeArrayWrapper::CreateVariantFromCStringArray(const CStringArray& arr, VARIANT& var)
/* ============================================================
    Function :		CSafeArrayWrapper::CreateVariantFromCStringArray
    Description :	Creates a VARIANT containing a SAFEARRAY of BSTRs 
                    from a CStringArray.
    Access :		Public
    Return :		HRESULT	             -	S_OK if successful, 
                                            or an error code 
                                            otherwise.
    Parameters :	CStringArray& arr	-	The input array of 
                                            strings.
                    VARIANT& var		-	The output VARIANT 
                                            that will contain 
                                            the SAFEARRAY. 
                                            The caller is 
                                            responsible for 
                                            clearing this VARIANT
                                            when it is no longer 
                                            needed.
	============================================================*/
{
    // Clear incoming VARIANT first
    VariantClear(&var);

    DWORD cElements = arr.GetSize();

    SAFEARRAYBOUND bound;
    bound.lLbound = 0;
    bound.cElements = cElements;

    SAFEARRAY* psa = SafeArrayCreate(VT_BSTR, 1, &bound);
    if (!psa)
        return E_OUTOFMEMORY;

    if (cElements > 0)
    {
        BSTR* pData = NULL;

        HRESULT hr = SafeArrayAccessData(psa, (void**)&pData);
        if (FAILED(hr))
        {
            SafeArrayDestroy(psa);
            return hr;
        }

        for (LONG i = 0; i < (LONG)cElements; ++i)
        {
            pData[i] = arr[i].AllocSysString();
            if (!pData[i])
            {
                SafeArrayUnaccessData(psa);
                SafeArrayDestroy(psa);
                return E_OUTOFMEMORY;
            }
        }

        SafeArrayUnaccessData(psa);
    }

    var.vt = VT_ARRAY | VT_BSTR;
    var.parray = psa;

    return S_OK;
}

void CSafeArrayWrapper::CopyFrom(const CSafeArrayWrapper& src)
/* ============================================================
    Function :		CSafeArrayWrapper::CopyFrom
    Description :	Copies the SAFEARRAY from another wrapper. 
                    This is a deep copy, meaning that the 
                    SAFEARRAY is duplicated, not just the pointer.
    Access :		Private
    Return :		void
    Parameters :	CSafeArrayWrapper& src	-	The source wrapper to 
                                                copy from.
	============================================================*/
{
    if (!src.m_psa)
        return;

    SafeArrayCopy(src.m_psa, &m_psa);
}

HRESULT CSafeArrayWrapper::PutElement(LONG* pIndices, void* pvData)
/* ============================================================
    Function :		CSafeArrayWrapper::PutElement
    Description :	Puts an element into the SAFEARRAY at the specified 
                    indices.
    Access :		Public
    Return :		HRESULT	             -	S_OK if successful, 
                                            or an error code 
                                            otherwise.
    Parameters :	LONG* pIndices		-	Array of indices specifying 
                                            the location of the 
                                            element to put. The number 
                                            of indices must match the 
                                            number of dimensions of the 
                                            SAFEARRAY.
                    void* pvData		-	Pointer to the data to put. 
                                            The type of data must match
                                            the VARTYPE of the 
                                            SAFEARRAY elements.
	============================================================*/
{
    if (!m_psa)
        return E_FAIL;

    return SafeArrayPutElement(m_psa, pIndices, pvData);
}

HRESULT CSafeArrayWrapper::GetElement(LONG* pIndices, void* pvData) const
/* ============================================================
    Function :		CSafeArrayWrapper::GetElement
    Description :	Gets an element from the SAFEARRAY at the specified 
                    indices.
    Access :		Public
    Return :		HRESULT	             -	S_OK if successful, 
                                            or an error code 
                                            otherwise.
    Parameters :	LONG* pIndices		-	Array of indices specifying 
                                            the location of the 
                                            element to get. The number 
                                            of indices must match the 
                                            number of dimensions of the 
                                            SAFEARRAY.
                    void* pvData		-	Pointer to a variable that will 
                                            receive the data. The type 
                                            of data must match the 
                                            VARTYPE of the SAFEARRAY 
                                            elements.
	============================================================*/
{
    if (!m_psa)
        return E_FAIL;

    return SafeArrayGetElement(m_psa, pIndices, pvData);
}

HRESULT CSafeArrayWrapper::AccessData(void** ppData)
/* ============================================================
    Function :		CSafeArrayWrapper::AccessData
    Description :	Provides direct access to the data in the SAFEARRAY. 
                    This is a bulk access method that allows you to 
                    read or write multiple elements at once. You must call 
                    UnaccessData() when you are done accessing the data.
    Access :		Public
    Return :		HRESULT	             -	S_OK if successful, 
                                            or an error code 
                                            otherwise.
    Parameters :	void** ppData		-	Pointer to a variable that will 
                                            receive the pointer to the 
                                            data. The type of data must 
                                            match the VARTYPE of the 
                                            SAFEARRAY elements.
	============================================================*/
{
    if (!m_psa)
        return E_FAIL;

    return SafeArrayAccessData(m_psa, ppData);
}

HRESULT CSafeArrayWrapper::UnaccessData()
/* ============================================================
    Function :		CSafeArrayWrapper::UnaccessData
    Description :	Releases direct access to the data in the SAFEARRAY. 
                    You must call this method after calling AccessData() 
                    when you are done accessing the data.
    Access :		Public
    Return :		HRESULT	             -	S_OK if successful, 
                                            or an error code 
                                            otherwise.
    Parameters :	none
	============================================================*/
{
    if (!m_psa)
        return E_FAIL;

    return SafeArrayUnaccessData(m_psa);
}

UINT CSafeArrayWrapper::GetDim() const
/* ============================================================
    Function :		CSafeArrayWrapper::GetDim
    Description :	Returns the number of dimensions of the SAFEARRAY.
    Access :		Public
    Return :		UINT    -	The number of dimensions, or 0 if 
                                there is no SAFEARRAY.
    Parameters :	none
	============================================================*/
{
    if (!m_psa)
        return 0;

    return SafeArrayGetDim(m_psa);
}

HRESULT CSafeArrayWrapper::GetLBound(UINT nDim, LONG* plLBound) const
/* ============================================================
    Function :		CSafeArrayWrapper::GetLBound
    Description :	Returns the lower bound of the specified dimension of 
                    the SAFEARRAY.
    Access :		Public
    Return :		HRESULT	             -	S_OK if successful, 
                                            or an error code 
                                            otherwise.
    Parameters :	UINT nDim			-	The dimension for which to get the 
                                            lower bound. Dimensions are 
                                            zero-based, so the first 
                                            dimension is 0.
                    LONG* plLBound		-	Pointer to a variable that will 
                                            receive the lower bound of the 
                                            specified dimension.
	============================================================*/
{
    if (!m_psa)
        return E_FAIL;

    return SafeArrayGetLBound(m_psa, nDim, plLBound);
}

HRESULT CSafeArrayWrapper::GetUBound(UINT nDim, LONG* plUBound) const
/* ============================================================
    Function :		CSafeArrayWrapper::GetUBound
    Description :	Returns the upper bound of the specified dimension of 
                    the SAFEARRAY.
    Access :		Public
    Return :		HRESULT	             -	S_OK if successful, 
                                            or an error code 
                                            otherwise.
    Parameters :	UINT nDim			-	The dimension for which to get the 
                                            upper bound. Dimensions are 
                                            zero-based, so the first 
                                            dimension is 0.
                    LONG* plUBound		-	Pointer to a variable that will 
                                            receive the upper bound of the 
                                            specified dimension.
	============================================================*/
{
    if (!m_psa)
        return E_FAIL;

    return SafeArrayGetUBound(m_psa, nDim, plUBound);
}
