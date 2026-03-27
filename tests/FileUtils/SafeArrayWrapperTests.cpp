#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/FileUtils/SafeArrayWrapper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CSafeArrayWrapperTests
{
    TEST_CLASS(CSafeArrayWrapperTests)
    {
    public:

        SAFEARRAYBOUND CreateBound(ULONG count, LONG lBound = 0)
        {
            SAFEARRAYBOUND b;
            b.cElements = count;
            b.lLbound = lBound;
            return b;
        }
        
#pragma region CreationDestruction

        TEST_METHOD(Create_Valid1DimIntArray_Succeeds)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(5);

            BOOL result = wrapper.Create(VT_I4, 1, &bound);

            Assert::IsTrue(result);
            Assert::IsNotNull(wrapper.GetSafeArray());
            Assert::AreEqual((UINT)1, wrapper.GetDim());

            wrapper.Destroy();
        }
        
        TEST_METHOD(Destroy_AfterCreate_ArrayIsNull)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(3);
            wrapper.Create(VT_I4, 1, &bound);

            wrapper.Destroy();

            Assert::IsNull(wrapper.GetSafeArray());
        }

#pragma endregion

        
#pragma region AttachDetach

        TEST_METHOD(Attach_ValidSafeArray_AssignsPointer)
        {
            SAFEARRAY* psa = SafeArrayCreateVector(VT_I4, 0, 3);

            CSafeArrayWrapper wrapper;
            BOOL result = wrapper.Attach(psa);

            Assert::IsTrue(result);
            TestHelpers::PointerAssert::AreEqual(psa, wrapper.GetSafeArray());
        }

        TEST_METHOD(Detach_WithAttachedArray_ReturnsSamePointer)
        {
            SAFEARRAY* psa = SafeArrayCreateVector(VT_I4, 0, 3);

            CSafeArrayWrapper wrapper;
            wrapper.Attach(psa);

            SAFEARRAY* detached = wrapper.Detach();

            TestHelpers::PointerAssert::AreEqual(psa, detached);
            Assert::IsNull(wrapper.GetSafeArray());

            SafeArrayDestroy(detached);
        }
        
#pragma endregion

#pragma region ElementManipulation

        TEST_METHOD(PutElement_ValidIndex_StoresValue)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(3);
            wrapper.Create(VT_I4, 1, &bound);

            LONG index[1] = { 1 };
            LONG value = 42;

            HRESULT hr = wrapper.PutElement(index, &value);

            Assert::AreEqual(S_OK, hr);

            wrapper.Destroy();
        }

        TEST_METHOD(GetElement_AfterPut_ReturnsSameValue)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(3);
            wrapper.Create(VT_I4, 1, &bound);

            LONG index[1] = { 2 };
            LONG value = 99;

            wrapper.PutElement(index, &value);

            LONG result = 0;
            wrapper.GetElement(index, &result);

            Assert::AreEqual((LONG)99, result);

            wrapper.Destroy();
        }
        
#pragma endregion

#pragma region DataAccess

        TEST_METHOD(AccessData_ValidArray_ReturnsPointer)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(4);
            wrapper.Create(VT_I4, 1, &bound);

            void* pData = NULL;
            HRESULT hr = wrapper.AccessData(&pData);

            Assert::AreEqual(S_OK, hr);
            Assert::IsNotNull(pData);

            wrapper.UnaccessData();
            wrapper.Destroy();
        }

        TEST_METHOD(UnaccessData_AfterAccess_Succeeds)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(4);
            wrapper.Create(VT_I4, 1, &bound);

            void* pData = NULL;
            wrapper.AccessData(&pData);

            HRESULT hr = wrapper.UnaccessData();

            Assert::AreEqual(S_OK, hr);

            wrapper.Destroy();
        }


#pragma endregion

#pragma region Bounds

        TEST_METHOD(GetDim_AfterCreate_ReturnsCorrectDimension)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bounds[2];
            bounds[0] = CreateBound(3);
            bounds[1] = CreateBound(2);

            wrapper.Create(VT_I4, 2, bounds);

            Assert::AreEqual((UINT)2, wrapper.GetDim());

            wrapper.Destroy();
        }

        TEST_METHOD(GetLBound_ValidDimension_ReturnsCorrectValue)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(5, 10);
            wrapper.Create(VT_I4, 1, &bound);

            LONG lb = 0;
            wrapper.GetLBound(1, &lb);

            Assert::AreEqual((LONG)10, lb);

            wrapper.Destroy();
        }

        TEST_METHOD(GetUBound_ValidDimension_ReturnsCorrectValue)
        {
            CSafeArrayWrapper wrapper;

            SAFEARRAYBOUND bound = CreateBound(5, 10);
            wrapper.Create(VT_I4, 1, &bound);

            LONG ub = 0;
            wrapper.GetUBound(1, &ub);

            Assert::AreEqual((LONG)14, ub);

            wrapper.Destroy();
        }


#pragma endregion
        
#pragma region Cloning

        TEST_METHOD(CopyConstructor_ValidArray_PerformsDeepCopy)
        {
            CSafeArrayWrapper src;

            SAFEARRAYBOUND bound = CreateBound(3);
            src.Create(VT_I4, 1, &bound);

            LONG index[1] = { 0 };
            LONG value = 7;
            src.PutElement(index, &value);

            CSafeArrayWrapper copy(src);

            LONG result = 0;
            copy.GetElement(index, &result);

            Assert::AreEqual((LONG)7, result);
            TestHelpers::PointerAssert::AreNotEqual(src.GetSafeArray(), copy.GetSafeArray());

            src.Destroy();
            copy.Destroy();
        }

        TEST_METHOD(AssignmentOperator_ValidArray_PerformsDeepCopy)
        {
            CSafeArrayWrapper src;

            SAFEARRAYBOUND bound = CreateBound(3);
            src.Create(VT_I4, 1, &bound);

            LONG index[1] = { 1 };
            LONG value = 11;
            src.PutElement(index, &value);

            CSafeArrayWrapper dst;
            dst = src;

            LONG result = 0;
            dst.GetElement(index, &result);

            Assert::AreEqual((LONG)11, result);

            src.Destroy();
            dst.Destroy();
        }


#pragma endregion

#pragma region StaticHelpers

        TEST_METHOD(CreateVariantFromCStringArray_ValidInput_CreatesSafeArray)
        {
            CStringArray arr;
            arr.Add(L"A");
            arr.Add(L"B");

            VARIANT var;
            VariantInit(&var);

            HRESULT hr = CSafeArrayWrapper::CreateVariantFromCStringArray(arr, var);

            Assert::AreEqual(S_OK, hr);
            Assert::AreEqual((VARTYPE)(VT_ARRAY | VT_BSTR), var.vt);

            SAFEARRAY* psa = var.parray;
            Assert::IsNotNull(psa);

            LONG index[1] = { 0 };
            BSTR bstr = NULL;

            SafeArrayGetElement(psa, index, &bstr);

            Assert::IsTrue(wcscmp(bstr, L"A") == 0);

            SysFreeString(bstr);
            VariantClear(&var);
        }

#pragma endregion

    };
}