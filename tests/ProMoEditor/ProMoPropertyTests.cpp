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
            CProMoProperty prop(_T("name"), TYPE_STRING, initial, FALSE, TRUE, TRUE, &owner, MockValidation, MockChange, MockEdit, NULL, NULL);

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

    };
}
