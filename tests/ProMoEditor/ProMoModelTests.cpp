#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoModel.h"
#include "../../src/ProMoEditor/ProMoProperty.h"
#include "../../src/ProMoEditor/ProMoLabel.h"
#include "../WinProMoTests.h"

class CProMoModelTestStub : public CProMoModel
{
public:
    void LinkView(CDiagramEntity* view) {
        CProMoModel::LinkView(view);
    }
    void UnlinkView(CDiagramEntity* view) {
        CProMoModel::UnlinkView(view);
    }
    void UnlinkAllViews() {
        CProMoModel::UnlinkAllViews();
    }

    void CreateProperties() {
        ClearProperties();
        CVariantWrapper nullVal;
        CVariantWrapper intVal;
        intVal.SetInt(42);
        CProMoProperty* root = new CProMoProperty(_T("root"), PROPTYPE_COMPOSITE, nullVal, FALSE, FALSE, TRUE, NULL);
        CProMoProperty* child = new CProMoProperty(_T("child"), PROPTYPE_INT, intVal, FALSE, TRUE, TRUE, this, NULL, NULL, NULL, root, NULL);
        AddProperty(root);
    }
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoModelTests
{

    TEST_CLASS(ProMoModelTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region ViewTests

        TEST_METHOD(LinkView_WhenNewViewAdded_ViewAppearsInList)
        {
            CProMoModelTestStub model;
            CDiagramEntity view;

            model.LinkView(&view);

            Assert::AreEqual((INT_PTR)1, model.GetViews()->GetSize());
            TestHelpers::PointerAssert::AreEqual(&view, (CDiagramEntity*)model.GetViews()->GetAt(0));
        }

        TEST_METHOD(UnlinkView_WhenViewPresent_RemovesFromList)
        {
            CProMoModelTestStub model;
            CDiagramEntity view;

            model.LinkView(&view);
            model.UnlinkView(&view);

            Assert::AreEqual((INT_PTR)0, model.GetViews()->GetSize());
        }

        TEST_METHOD(UnlinkAllViews_WhenMultipleViews_LinkArrayIsCleared)
        {
            CProMoModelTestStub model;
            CDiagramEntity v1, v2;

            model.LinkView(&v1);
            model.LinkView(&v2);

            model.UnlinkAllViews();

            Assert::AreEqual((INT_PTR)0, model.GetViews()->GetSize());
        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoModelTestStub model;
            
            model.CreateFromString(CString("promo_model:Model,;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoModelTestStub model;
            
            model.CreateFromString(CString("promo_model:Model,,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoModelTestStub model;
            
            model.CreateFromString(CString("wrong_type:;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());
        }

        TEST_METHOD(LoadFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoModelTestStub model;

            model.LoadFromString(CString("promo_model:Model,;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(LoadFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoModelTestStub model;

            model.LoadFromString(CString("promo_model:Model,,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(LoadFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoModelTestStub model;

            model.LoadFromString(CString("wrong_type:;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());
        }

        TEST_METHOD(GetNameFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoModelTestStub::GetNameFromString(CString("promo_model:Model,;"));
            Assert::AreEqual(CString("Model"), str1);
        }

#pragma endregion

#pragma region CloneTests

        TEST_METHOD(Clone_WhenCalled_ReturnsIndependentCopy)
        {
            CProMoModelTestStub model;
            CDiagramEntity view;

            model.LinkView(&view);

            std::unique_ptr<CProMoModel> clone(model.Clone());

            Assert::IsNotNull(clone.get());
            Assert::AreNotEqual((void*)&model, (void*)clone.get());

            auto* blockClone = dynamic_cast<CProMoModel*>(clone.get());
            Assert::IsNotNull(blockClone);

            Assert::AreEqual((INT_PTR)0, blockClone->GetViews()->GetSize());
        }

        TEST_METHOD(Copy_WhenCalled_CopyPropertyValues)
        {
            CProMoModel model, modelCopy;
            CVariantWrapper value, value2;
            value.SetString(CString("Original"));
            value2.SetString(CString("Copy"));

            model.SetPropertyValue(CString("Title"), value);
            modelCopy.SetPropertyValue(CString("Title"), value2);

            Assert::AreEqual(CString("Original"), model.GetPropertyValue(CString("Title")).GetString());
            model.Copy(&modelCopy);
            Assert::AreEqual(CString("Copy"), model.GetPropertyValue(CString("Title")).GetString());
        }

#pragma endregion

#pragma region PropertyTests

        TEST_METHOD(FindProperty_IfPropertyExist_ReturnProperty)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            CProMoProperty* prop = NULL;

            prop = model.FindProperty(CString("root.child"));

            Assert::IsNotNull(prop);
            Assert::AreEqual(CString("child"), prop->GetName());
        }

        TEST_METHOD(FindProperty_IfPropertyDoesNotExist_ReturnNull)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            CProMoProperty* prop = NULL;

            prop = model.FindProperty(CString("Foobar"));

            Assert::IsNull(prop);
        }

        TEST_METHOD(GetPropertyNames_WhenInvoked_ReturnNames)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            CStringArray array;
            model.GetPropertyNames(array, TRUE);

            Assert::AreEqual((INT_PTR)2, array.GetSize());
            Assert::AreEqual(CString("root"), array.GetAt(0));
            Assert::AreEqual(CString("root.child"), array.GetAt(1));
        }

        TEST_METHOD(GetPropertyType_IfPropertyExist_ReturnCorrectType)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            unsigned int type = model.GetPropertyType(CString("root.child"));

            Assert::AreEqual(PROPTYPE_INT, (int)type);
        }

        TEST_METHOD(GetPropertyType_IfPropertyDoesNotExist_ReturnUnknownType)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            unsigned int type = model.GetPropertyType(CString("Foobar"));

            Assert::AreEqual(PROPTYPE_UNKNOWN, (int)type);
        }

        TEST_METHOD(SetPropertyValue_IfPropertyExist_SetValue)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            CVariantWrapper value;
            value.SetInt(42);
            BOOL result = model.SetPropertyValue(CString("root.child"),value);
            
            Assert::IsTrue(result);
            
            CVariantWrapper readValue = model.GetPropertyValue(CString("root.child"));
            
            Assert::AreEqual(42, readValue.GetInt());
        }

        TEST_METHOD(SetPropertyValue_IfPropertyDoesNotExist_ReturnFalse)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            CVariantWrapper value;
            value.SetString(CString("Test"));
            BOOL result = model.SetPropertyValue(CString("Foobar"), value);
            
            Assert::IsFalse(result);
        }

        TEST_METHOD(GetPropertiesCount_WhenInvoked_ReturnCorrectCount)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            int count = model.GetPropertiesCount();
            
            Assert::AreEqual(1, count);
        }
        
        TEST_METHOD(GetProperty_IfPropertyExist_ReturnProperty)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            CProMoProperty* prop = NULL;

            prop = model.GetProperty(0);

            Assert::IsNotNull(prop);
        }

        TEST_METHOD(GetProperty_IfPropertyDoesNotExist_ReturnNull)
        {
            CProMoModelTestStub model;
            model.CreateProperties();
            CProMoProperty* prop = NULL;

            prop = model.GetProperty(10);

            Assert::IsNull(prop);
        }
#pragma endregion

#pragma region LabelTests

        TEST_METHOD(RecreateLabels_IfPropertyExist_CreateLabel)
        {
            CProMoModelTestStub model;
            CProMoLabel* label = NULL;
            model.CreateProperties();
            model.RecreateLabels();
            
            Assert::AreEqual((INT_PTR)1, model.GetLabels()->GetSize());
            
            label = dynamic_cast<CProMoLabel*>(model.GetLabels()->GetAt(0));

            Assert::IsNotNull(label);
            Assert::AreEqual(CString("root.child"), label->GetProperty());
        }

        TEST_METHOD(GetLabel_IfPropertyExist_GetLabel)
        {
            CProMoModelTestStub model;
            CProMoLabel* label = NULL;
            model.CreateProperties();
            model.RecreateLabels();

            label = dynamic_cast<CProMoLabel*>(model.GetLabel(CString("root.child")));

            Assert::IsNotNull(label);
            Assert::AreEqual(CString("root.child"), label->GetProperty());
        }

#pragma endregion
    };

}
