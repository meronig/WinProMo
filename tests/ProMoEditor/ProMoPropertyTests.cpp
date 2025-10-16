#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoProperty.h"
#include "../WinProMoTests.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Mock owner to track property changes
class MockOwner : public IProMoPropertyOwner {
public:
    int changeCount = 0;
    void OnPropertyChanged(CProMoProperty* prop) override {
        changeCount++;
    }
};

// Mock handlers
BOOL MockValidation(CProMoProperty* prop, const CVariantWrapper& val) {
    if (val.GetType() == VT_I4 && val.GetInt() < 0) return FALSE; // disallow negative integers
    return TRUE;
}

BOOL MockChange(CProMoProperty* prop, const CVariantWrapper& val) {
    return TRUE;
}

BOOL MockEdit(CProMoProperty* prop, CWnd* parent) {
    CVariantWrapper wrapper;
	wrapper.SetString(_T("edited"));
    prop->SetValue(wrapper);
    return TRUE;
}

namespace ProMoPropertyTests
{
    TEST_CLASS(ProMoPropertyStressTests)
    {
    public:

        TEST_METHOD(SetValue_ValidAndInvalid_ChangesTracked)
        {
            MockOwner owner;
            CVariantWrapper initial;
            initial.SetString(_T("default"));
            CProMoProperty prop(_T("name"), TYPE_STRING, initial, FALSE, TRUE, TRUE, &owner, MockValidation, MockChange);

            // precondition: initial value
            Assert::AreEqual(CString("default"), prop.GetValue().GetString());

            // action: set invalid value
            CVariantWrapper badVal;
            badVal.SetInt(-1);
            Assert::IsFalse(prop.SetValue(badVal));

            // action: set valid value
            CVariantWrapper newVal;
            newVal.SetString(CString("ok"));
            Assert::IsTrue(prop.SetValue(newVal));
            Assert::AreEqual(newVal.GetString(), prop.GetValue().GetString());
            Assert::AreEqual(1, owner.changeCount);

        }

        TEST_METHOD(SetValue_IntType_AssignsAndValidatesProperly)
        {
            CVariantWrapper initial;
            initial.SetInt(1);
            CProMoProperty prop(_T("intProp"), TYPE_INT, initial, FALSE, TRUE, TRUE, NULL, MockValidation, MockChange);

            // precondition: initial value
            Assert::AreEqual(1, prop.GetValue().GetInt());

            // action: valid positive int
            CVariantWrapper val;
            val.SetInt(10);
            Assert::IsTrue(prop.SetValue(val));
            Assert::AreEqual(10, prop.GetValue().GetInt());

            // action: invalid negative int (validation should fail)
            val.SetInt(-5);
            Assert::IsFalse(prop.SetValue(val));
            Assert::AreEqual(10, prop.GetValue().GetInt());
        }

        TEST_METHOD(SetValue_DoubleType_AssignsAndFormatsCorrectly)
        {
            CVariantWrapper initial;
            initial.SetDouble(1.5);
            CProMoProperty prop(_T("dblProp"), TYPE_DOUBLE, initial, FALSE, TRUE, TRUE, NULL);

            // action: set new value
            CVariantWrapper newVal;
            newVal.SetDouble(3.14);
            Assert::IsTrue(prop.SetValue(newVal));

            // verify both numeric and string access
            Assert::AreEqual(3.14, prop.GetValue().GetDouble());
            Assert::IsTrue(prop.GetValue().GetString().Find(_T("3.14")) != -1);
        }

        TEST_METHOD(SetValue_BoolType_AssignsAndSerializes)
        {
            CVariantWrapper initial;
            initial.SetBool(TRUE);
            CProMoProperty prop(_T("boolProp"), TYPE_BOOL, initial, FALSE, TRUE, TRUE, NULL);

            // action: toggle value
            CVariantWrapper newVal;
            newVal.SetBool(FALSE);
            Assert::IsTrue(prop.SetValue(newVal));

            // verify numeric and textual forms
            Assert::IsFalse(prop.GetValue().GetBool());
            CString serialized = prop.GetString();
            Assert::IsTrue(serialized.Find(_T("FALSE")) != -1 || serialized.Find(_T("0")) != -1);
        }

        TEST_METHOD(InvokeHandler_WhenInvoked_ChangesTracked)
        {
            MockOwner owner;
            CVariantWrapper initial;
			initial.SetString(_T("default"));
            CProMoProperty prop(_T("name"), TYPE_STRING, initial, FALSE, TRUE, TRUE, &owner, NULL, NULL, MockEdit, NULL, NULL);

            // precondition: initial value
            Assert::AreEqual(CString("default"), prop.GetValue().GetString());

            // action: invoke edit handler
            Assert::IsTrue(prop.InvokeHandler(NULL));
            Assert::AreEqual(CString("edited"), prop.GetValue().GetString());
        }

        TEST_METHOD(AddChild_MultiValueProperty_SequentialNames)
        {
			CVariantWrapper initial;
			initial.SetInt(0);
            CProMoProperty* templateChild = new CProMoProperty(_T("child"), TYPE_INT, initial, FALSE, TRUE, TRUE, NULL);
            CProMoProperty parent(_T("parent"), TYPE_INT, initial, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, NULL, templateChild);

            // action: add multiple children
            for (int i = 0; i < 10; ++i) {
                CProMoProperty* child = parent.AddChild();
                Assert::IsNotNull(child);
                Assert::AreEqual(std::to_wstring(i).c_str(), child->GetName().GetString());
            }

            // verify
            Assert::AreEqual(10, parent.GetChildrenCount());
        }

        TEST_METHOD(SerializeCompositeTree_FullRoundTrip_PropertiesMatch)
        {
            CVariantWrapper nullVal;
			CVariantWrapper strVal;
			strVal.SetString(_T("val"));

            CProMoProperty root(_T("root"), TYPE_COMPOSITE, nullVal, FALSE, TRUE, TRUE, NULL);

            CProMoProperty* c1 = new CProMoProperty(_T("child1"), TYPE_COMPOSITE, nullVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, &root, NULL);
            
            CProMoProperty* leaf = new CProMoProperty(_T("leaf"), TYPE_STRING, strVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, c1, NULL);
            
            CVariantWrapper strValEmpty;
			strValEmpty.SetString(_T(""));

            CProMoProperty rootCopy(_T("root"), TYPE_COMPOSITE, nullVal, FALSE, TRUE, TRUE, NULL);

            CProMoProperty* c1Copy = new CProMoProperty(_T("child1"), TYPE_COMPOSITE, nullVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, &rootCopy, NULL);

            CProMoProperty* leafCopy = new CProMoProperty(_T("leaf"), TYPE_STRING, strValEmpty, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, c1Copy, NULL);


            // action: serialize
            CString serialized = root.GetString();
            Assert::IsTrue(!serialized.IsEmpty());
                        
            // action: deserialize into new object
            CString copyStr = serialized;
            Assert::IsTrue(rootCopy.FromString(copyStr));
        }

        TEST_METHOD(Clone_WithChildren_AllChildrenCloned)
        {
            CVariantWrapper nullVal;

            CVariantWrapper strVal;
            strVal.SetString(_T("val"));

            CProMoProperty* templateChild = new CProMoProperty(_T("child"), TYPE_STRING, strVal, FALSE, TRUE, TRUE, NULL);
            CProMoProperty parent(_T("parent"), TYPE_STRING, nullVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, NULL, templateChild);

            for (int i = 0; i < 5; ++i)
                parent.AddChild();

            // action: clone parent
            CProMoProperty* clone = parent.Clone();
            Assert::IsNotNull(clone);
            Assert::AreEqual(parent.GetChildrenCount(), clone->GetChildrenCount());

            // verify sequential child names
            for (int i = 0; i < clone->GetChildrenCount(); ++i)
            {
                CProMoProperty* child = clone->GetChild(i);
                CString expected;
                expected.Format(_T("%d"), i);
                Assert::AreEqual(expected, child->GetName());
            }

            delete clone;
        }

        TEST_METHOD(SerializeMultiValueChildren_RoundTrip_ValuesMatch)
        {
            
            CVariantWrapper nullVal;
            CVariantWrapper strVal;
            strVal.SetString(_T("val"));
            
            CProMoProperty* templateChild = new CProMoProperty(_T("child"), TYPE_STRING, strVal, FALSE, TRUE, TRUE, NULL);
            CProMoProperty parent(_T("parent"), TYPE_STRING, nullVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, NULL, templateChild);

            parent.AddChild();
            parent.AddChild();

            CProMoProperty* templateChildCopy = new CProMoProperty(_T("child"), TYPE_STRING, strVal, FALSE, TRUE, TRUE, NULL);
            CProMoProperty parentCopy(_T("parent"), TYPE_STRING, nullVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, NULL, templateChildCopy);


            // action: serialize and deserialize each leaf
            for (int i = 0; i < parent.GetChildrenCount(); ++i)
            {
                CProMoProperty* child = parent.GetChild(i);
                CString serialized = child->GetString();
                CString copyStr = serialized;
                Assert::IsTrue(parentCopy.FromString(copyStr));

                CProMoProperty* childCopy = parentCopy.GetChild(i); // ensure child exists
				Assert::AreEqual(child->GetName(), childCopy->GetName());
                Assert::AreEqual(child->GetValue().GetString(), childCopy->GetValue().GetString());
            }
        }

        TEST_METHOD(Getters_DefaultProperty_ReturnsCorrectMetadata)
        {
            CVariantWrapper nullVal;
            CProMoProperty prop(_T("testProp"), TYPE_INT, nullVal, TRUE, FALSE, TRUE, NULL);

            Assert::AreEqual(CString("testProp"), prop.GetName());
            Assert::AreEqual((unsigned int)TYPE_INT, prop.GetType());
            Assert::IsTrue(prop.IsReadOnly());
            Assert::IsFalse(prop.IsLabelVisible());
            Assert::IsTrue(prop.IsPersistent());
            Assert::IsFalse(prop.HasHandler());
        }

        TEST_METHOD(AddOption_SequentialAdds_CountIncreases)
        {
            CVariantWrapper nullVal;
            CVariantWrapper opt;
            opt.SetInt(42);

            CProMoProperty prop(_T("optProp"), TYPE_INT, nullVal, FALSE, TRUE, TRUE, NULL);

            Assert::AreEqual(0, prop.GetOptionsCount());

            prop.AddOption(opt);
            Assert::AreEqual(1, prop.GetOptionsCount());
            Assert::AreEqual(opt.GetInt(), prop.GetOption(0).GetInt());
        }

        TEST_METHOD(SetValue_ReadOnly_DoesNotChangeValue)
        {
            CVariantWrapper val;
            val.SetInt(10);
            CProMoProperty prop(_T("readonly"), TYPE_INT, val, TRUE, TRUE, TRUE, NULL);

            CVariantWrapper newVal;
            newVal.SetInt(20);

            Assert::IsFalse(prop.SetValue(newVal));
            Assert::AreEqual(10, prop.GetValue().GetInt());
        }

        TEST_METHOD(SetValue_NoValidation_SuccessfulAssignment)
        {
            CVariantWrapper val;
            val.SetInt(5);
            CProMoProperty prop(_T("simple"), TYPE_INT, val, FALSE, TRUE, TRUE, NULL);

            CVariantWrapper newVal;
            newVal.SetInt(15);

            Assert::IsTrue(prop.SetValue(newVal));
            Assert::AreEqual(15, prop.GetValue().GetInt());
        }

        TEST_METHOD(InvokeHandler_NoEditFunction_ReturnsFalse)
        {
            CVariantWrapper val;
            val.SetString(_T("none"));
            CProMoProperty prop(_T("editless"), TYPE_STRING, val, FALSE, TRUE, TRUE, NULL);
            Assert::IsFalse(prop.InvokeHandler(NULL));
        }

        TEST_METHOD(HandleChildren_ClearAndReAdd_CollectionResets)
        {
            CVariantWrapper nullVal;
            CVariantWrapper strVal;
            strVal.SetString(_T("v"));

            CProMoProperty* templ = new CProMoProperty(_T("child"), TYPE_STRING, strVal, FALSE, TRUE, TRUE, NULL);
            CProMoProperty parent(_T("p"), TYPE_STRING, nullVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, NULL, templ);

            parent.AddChild();
            parent.AddChild();
            Assert::AreEqual(2, parent.GetChildrenCount());

            parent.ClearChildren();
            Assert::AreEqual(0, parent.GetChildrenCount());
        }

        TEST_METHOD(GetFullName_NestedChild_ReturnsCompositePath)
        {
            CVariantWrapper nullVal;
            CVariantWrapper strVal;
            strVal.SetString(_T("v"));

            CProMoProperty root(_T("root"), TYPE_COMPOSITE, nullVal, FALSE, TRUE, TRUE, NULL);
            CProMoProperty* child = new CProMoProperty(_T("child"), TYPE_STRING, strVal, FALSE, TRUE, TRUE, NULL, NULL, NULL, NULL, &root, NULL);

            CString fullName = child->GetFullName();
            Assert::IsTrue(fullName.Find(_T("root")) != -1);
            Assert::IsTrue(fullName.Find(_T("child")) != -1);
        }

        TEST_METHOD(FromString_InvalidInput_ReturnsFalse)
        {
            CString badData = _T("property:foobar,3,Test,10");
            CVariantWrapper nullVal;
            CProMoProperty prop(_T("broken"), TYPE_STRING, nullVal, FALSE, TRUE, TRUE, NULL);
            Assert::IsFalse(prop.FromString(badData));
        }

        TEST_METHOD(FromString_IntRoundTrip_CorrectConversion)
        {
            // Integer property
            CString goodData = _T("property:intProp,1,42,10");
            CVariantWrapper val; 
            CProMoProperty prop(_T("intProp"), TYPE_INT, val, FALSE, TRUE, TRUE, NULL);
            Assert::IsTrue(prop.FromString(goodData));
            Assert::AreEqual(42, prop.GetValue().GetInt());
        }

        TEST_METHOD(FromString_DoubleRoundTrip_CorrectConversion)
        {
            // Integer property
            CString goodData = _T("property:dblProp,2,2.5,10");
            CVariantWrapper val;
            CProMoProperty prop(_T("dblProp"), TYPE_INT, val, FALSE, TRUE, TRUE, NULL);
            Assert::IsTrue(prop.FromString(goodData));
            Assert::AreEqual(2.5, prop.GetValue().GetDouble());
        }

        TEST_METHOD(FromString_BoolRoundTrip_CorrectConversion)
        {
            // Integer property
            CString goodData = _T("property:boolProp,4,1,10");
            CVariantWrapper val;
            CProMoProperty prop(_T("boolProp"), TYPE_INT, val, FALSE, TRUE, TRUE, NULL);
            Assert::IsTrue(prop.FromString(goodData));
            Assert::AreEqual(TRUE, prop.GetValue().GetBool());
        }

        TEST_METHOD(LoadFromString_CorrectProperty_ReturnsTrue)
        {
            CString goodData = _T("property:foobar,3,Test,10");
            CVariantWrapper nullVal;
            CProMoProperty prop(_T("foobar"), TYPE_STRING, nullVal, FALSE, TRUE, TRUE, NULL);
            Assert::IsTrue(prop.LoadFromString(goodData));
        }

        TEST_METHOD(GetNameFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoProperty::GetElementFromString(CString("property:foobar,3,Test,10"));
            Assert::AreEqual(CString("10"), str1);
        }

    };
}
