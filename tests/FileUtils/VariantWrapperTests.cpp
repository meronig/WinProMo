#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/FileUtils/VariantWrapper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CVariantWrapperTests
{
	TEST_CLASS(CVariantWrapperTests)
	{
	public:
		TEST_METHOD_INITIALIZE(SetUp)
		{
			WinProMoTestHelpers::BootstrapMFC();
		}

#pragma region CoreBehavior

		TEST_METHOD(Constructor_Default_CreatesEmptyVariant)
		{
			CVariantWrapper var;
			Assert::AreEqual((VARTYPE)VT_EMPTY, var.GetType());
		}

		TEST_METHOD(Constructor_VARIANT_CopyVariant)
		{
			VARIANT v;
			VariantInit(&v);
			v.lVal = 42;
			v.vt = VT_I4;
			CVariantWrapper var(v);
			Assert::AreEqual((VARTYPE)VT_I4, var.GetType());
			Assert::AreEqual((int)v.lVal, var.GetInt());
		}

		TEST_METHOD(Constructor_VARIANT_DereferenceBool)
		{
			VARIANT v;
			VariantInit(&v);
			VARIANT_BOOL val = VARIANT_TRUE;
			v.piVal = &val;
			v.vt = VT_BOOL | VT_BYREF;
			CVariantWrapper var(v);
			Assert::AreEqual((VARTYPE)VT_BOOL, var.GetType());
			Assert::IsTrue(var.GetBool());
		}

		TEST_METHOD(Constructor_VARIANT_DereferenceInt)
		{
			VARIANT v;
			VariantInit(&v);
			long val = 42;
			v.plVal = &val;
			v.vt = VT_I4 | VT_BYREF;
			CVariantWrapper var(v);
			Assert::AreEqual((VARTYPE)VT_I4, var.GetType());
			Assert::AreEqual((int)val, var.GetInt());
		}
		
		TEST_METHOD(Constructor_VARIANT_DereferenceDouble)
		{
			VARIANT v;
			VariantInit(&v);
			double val = 3.14;
			v.pdblVal = &val;
			v.vt = VT_R8 | VT_BYREF;
			CVariantWrapper var(v);
			Assert::AreEqual((VARTYPE)VT_R8, var.GetType());
			Assert::AreEqual(val, var.GetDouble());
		}

		TEST_METHOD(Constructor_VARIANT_DereferenceString)
		{
			BSTR src = SysAllocString(L"Hello");

			VARIANT v;
			VariantInit(&v);
			v.vt = VT_BSTR | VT_BYREF;
			v.pbstrVal = &src;

			CVariantWrapper var(v);

			Assert::AreEqual((VARTYPE)VT_BSTR, var.GetType());
			Assert::AreEqual(src, var.GetString());
		}

		TEST_METHOD(SetBool_WhenValueIsSet_SetsTypeAndValue)
		{
			CVariantWrapper var;
			var.SetBool(TRUE);

			Assert::AreEqual((VARTYPE)VT_BOOL, var.GetType());
			Assert::IsTrue(var.GetBool());
		}

		TEST_METHOD(SetInt_WhenValueIsSet_SetsTypeAndValue)
		{
			CVariantWrapper var;
			var.SetInt(123);

			Assert::AreEqual((VARTYPE)VT_I4, var.GetType());
			Assert::AreEqual(123, var.GetInt());
			Assert::AreEqual(CString(L"123"), var.GetString());
		}

		TEST_METHOD(SetDouble_WhenValueIsSet_SetsTypeAndValue)
		{
			CVariantWrapper var;
			var.SetDouble(3.14159);

			Assert::AreEqual((VARTYPE)VT_R8, var.GetType());
			Assert::AreEqual(3.14159, var.GetDouble(), 1e-9);
			Assert::IsTrue(var.GetString().Find(L"3.141") == 0);
		}

		TEST_METHOD(SetString_WhenValueIsSet_SetsTypeAndValue)
		{
			CVariantWrapper var;
			var.SetString(L"Hello");

			Assert::AreEqual((VARTYPE)VT_BSTR, var.GetType());
			Assert::AreEqual(CString(L"Hello"), var.GetString());
		}

		TEST_METHOD(SetVariant_WhenValueIsSet_SetsTypeAndValue)
		{
			CVariantWrapper var;
			VARIANT v;
			VariantInit(&v);
			v.lVal = 42;
			v.vt = VT_I4;
			var.SetVariant(v);

			Assert::AreEqual((VARTYPE)VT_I4, var.GetType());
			Assert::AreEqual((int)v.lVal, var.GetInt());
		}

		TEST_METHOD(CopyConstructor_WithExistingValue_CreatesEquivalentCopy)
		{
			CVariantWrapper a;
			a.SetInt(42);

			CVariantWrapper b(a);

			Assert::AreEqual(a.GetType(), b.GetType());
			Assert::AreEqual(a.GetInt(), b.GetInt());
		}

		TEST_METHOD(AssignmentOperator_WithExistingValue_OverwritesTarget)
		{
			CVariantWrapper a, b;
			a.SetString(L"test");
			b.SetDouble(1.5);

			b = a;

			Assert::AreEqual((VARTYPE)VT_BSTR, b.GetType());
			Assert::AreEqual(CString(L"test"), b.GetString());
		}

		TEST_METHOD(Clear_WithExistingValue_ResetsToEmpty)
		{
			CVariantWrapper var;
			var.SetInt(10);
			var.Clear();

			Assert::AreEqual((VARTYPE)VT_EMPTY, var.GetType());
		}

		TEST_METHOD(GetVARIANT_ValidAccess_returnsExpectedVariant)
		{
			// Arrange
			CVariantWrapper wrapper;
			wrapper.SetInt(123);

			// Act
			VARIANT* pVar = wrapper.GetVARIANT();

			// Assert
			Assert::IsNotNull(pVar, L"Returned VARIANT pointer should not be null");
			Assert::AreEqual((VARTYPE)VT_I4, pVar->vt, L"VARIANT type should be VT_I4");
			Assert::AreEqual(123L, pVar->lVal, L"VARIANT value should match the one set via SetInt");

			// Defensive check: verify const version returns same pointer
			const CVariantWrapper& constRef = wrapper;
			const VARIANT* pConstVar = constRef.GetVARIANT();
			Assert::IsTrue(pConstVar == pVar, L"Const and non-const accessors should return the same pointer");
		}

		TEST_METHOD(GetVARIANT_AfterClear_returnsVTEmpty)
		{
			// Arrange
			CVariantWrapper wrapper;
			wrapper.SetString(L"Test");
			wrapper.Clear();

			// Act
			const VARIANT* pVar = wrapper.GetVARIANT();

			// Assert
			Assert::AreEqual((VARTYPE)VT_EMPTY, pVar->vt, L"After Clear, VARIANT type should be VT_EMPTY");
		}

#pragma endregion

#pragma region ConversionBehavior

		TEST_METHOD(SetFromString_WithString_CreatesBSTRVariant)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"hello", VT_BSTR);

			Assert::IsTrue(ok);
			Assert::AreEqual((VARTYPE)VT_BSTR, var.GetType());
			Assert::AreEqual(CString(L"hello"), var.GetString());
		}

		TEST_METHOD(SetFromString_WithInt_CreatesIntegerVariant)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"123", VT_I4);

			Assert::IsTrue(ok);
			Assert::AreEqual((VARTYPE)VT_I4, var.GetType());
			Assert::AreEqual(123, var.GetInt());
		}

		TEST_METHOD(SetFromString_WithDouble_CreatesDoubleVariant)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"2.718", VT_R8);

			Assert::IsTrue(ok);
			Assert::AreEqual((VARTYPE)VT_R8, var.GetType());
			Assert::AreEqual(2.718, var.GetDouble(), 1e-9);
		}

		TEST_METHOD(SetFromString_WithBoolTrue_CreatesBooleanVariant)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"1", VT_BOOL);

			Assert::IsTrue(ok);
			Assert::AreEqual((VARTYPE)VT_BOOL, var.GetType());
			Assert::IsTrue(var.GetBool());
		}

		TEST_METHOD(SetFromString_WithBoolFalse_CreatesBooleanVariant)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"0", VT_BOOL);

			Assert::IsTrue(ok);
			Assert::AreEqual((VARTYPE)VT_BOOL, var.GetType());
			Assert::IsFalse(var.GetBool());
		}

		TEST_METHOD(SetVariant_WhenValueIsShort_CastToLong)
		{
			CVariantWrapper var;
			short val = 42;
			VARIANT v;
			VariantInit(&v);
			v.piVal = &val;
			v.vt = VT_I2 | VT_BYREF;
			var.SetVariant(v);

			Assert::AreEqual((VARTYPE)VT_I4, var.GetType());
			Assert::AreEqual((int)val, var.GetInt());
		}

		TEST_METHOD(SetVariant_WhenValueIsFloat_CastToDouble)
		{
			CVariantWrapper var;
			float val = 3.14;
			VARIANT v;
			VariantInit(&v);
			v.pfltVal = &val;
			v.vt = VT_R4 | VT_BYREF;
			var.SetVariant(v);

			Assert::AreEqual((VARTYPE)VT_R8, var.GetType());
			Assert::AreEqual((double)val, var.GetDouble());
		}

#pragma endregion

#pragma region EdgeCases

		TEST_METHOD(GetBool_WithStringValue_PerformsConversion)
		{
			CVariantWrapper var;
			var.SetString(L"abc");

			Assert::IsTrue(var.GetBool());
		}
		TEST_METHOD(GetBool_WithDoubleValue_PerformsConversion)
		{
			CVariantWrapper var;
			var.SetDouble(5.7);

			Assert::IsTrue(var.GetBool());
		}

		TEST_METHOD(GetBool_WithIntValue_PerformsConversion)
		{
			CVariantWrapper var;
			var.SetInt(42);

			Assert::IsTrue(var.GetBool());
		}

		TEST_METHOD(GetBool_WithEmptyVariant_PerformsConversion)
		{
			CVariantWrapper var;
			
			Assert::IsFalse(var.GetBool());
		}

		TEST_METHOD(GetInt_WithDoubleValue_PerformsConversion)
		{
			CVariantWrapper var;
			var.SetDouble(5.7);

			Assert::AreEqual(5, var.GetInt());
		}

		TEST_METHOD(GetInt_WithEmptyVariant_PerformsConversion)
		{
			CVariantWrapper var;

			Assert::AreEqual(0, var.GetInt());
		}

		TEST_METHOD(GetDouble_WithIntValue_PerformsConversion)
		{
			CVariantWrapper var;
			var.SetInt(42);

			Assert::AreEqual(42.0, var.GetDouble(), 1e-9);
		}

		TEST_METHOD(GetDouble_WithStringValue_PerformsConversion)
		{
			CVariantWrapper var;
			var.SetString(L"42.0");

			Assert::AreEqual(42.0, var.GetDouble(), 1e-9);
		}

		TEST_METHOD(GetString_WithBoolTRUE_Returns1)
		{
			CVariantWrapper var;
			var.SetBool(TRUE);

			Assert::AreEqual(CString(L"1"), var.GetString());
		}

		TEST_METHOD(SetFromString_WithEmptyString_ReturnsFalse)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"", VT_I4);

			Assert::IsFalse(ok);
			Assert::AreEqual((VARTYPE)VT_EMPTY, var.GetType());
		}

		TEST_METHOD(SetFromString_WithInvalidNumber_ReturnsFalse)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"abc", VT_R8);

			Assert::IsFalse(ok);
			Assert::AreEqual((VARTYPE)VT_EMPTY, var.GetType());
		}

		TEST_METHOD(SetFromString_WithInvalidBoolean_ReturnsFalse)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"abc", VT_BOOL);

			Assert::IsFalse(ok);
			Assert::AreEqual((VARTYPE)VT_EMPTY, var.GetType());
		}

		TEST_METHOD(SetFromString_WithUnrecognizedType_ReturnsFalse)
		{
			CVariantWrapper var;
			BOOL ok = var.SetFromString(L"something", VT_DATE);

			Assert::IsFalse(ok);
		}

		TEST_METHOD(SetVariant_WhenInError_SetToEmpty)
		{
			CVariantWrapper var;
			VARIANT v;
			VariantInit(&v);
			v.vt = VT_ERROR;
			var.SetVariant(v);

			Assert::AreEqual((VARTYPE)VT_EMPTY, var.GetType());
		}

#pragma endregion

	};
}
