#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/PropertyItem/TypedPropertyItem.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CTypedPropertyItemTests
{

    BOOL DummyStringFunction(CDiagramEntity* entity, CDiagramEditor* editor, const CString& val) {
        if (val == CString("correct"))
            return TRUE;
        return FALSE;
    }

    BOOL DummyUIntFunction(CDiagramEntity* entity, CDiagramEditor* editor, const unsigned int& val) {
        if (val < 10)
            return TRUE;
        return FALSE;
    }

    TEST_CLASS(CTypedPropertyItemTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region StringInvocationTests
        TEST_METHOD(SetValue_WhenStringFunctionReturnsTrue_UpdateValue)
        {
            CDiagramEntity entity;
            CDiagramEditor editor;
            CString test("test");
            CTypedPropertyItem<CString> item(test, &entity, &editor, &DummyStringFunction, test);

            Assert::IsTrue(item.SetValue(CString("correct")));
            Assert::AreEqual(CString("correct"), item.GetValue());            
        }

        TEST_METHOD(SetValue_WhenStringFunctionReturnsFalse_DoNotUpdateValue)
        {
            CDiagramEntity entity;
            CDiagramEditor editor;
            CString test("test");
            CTypedPropertyItem<CString> item(test, &entity, &editor, &DummyStringFunction, test);

            Assert::AreEqual(test, item.GetValue());
            Assert::IsFalse(item.SetValue(CString("wrong")));
            Assert::AreEqual(test, item.GetValue());

        }

#pragma endregion

#pragma region UIntInvocationTests
        TEST_METHOD(SetValue_WhenUIntFunctionReturnsTrue_UpdateValue)
        {
            CDiagramEntity entity;
            CDiagramEditor editor;
            CString test("test");
            CTypedPropertyItem<unsigned int> item(test, &entity, &editor, &DummyUIntFunction, 0);

            Assert::IsTrue(item.SetValue(3));
            Assert::AreEqual((unsigned int)3, item.GetValue());
        }

        TEST_METHOD(SetValue_WhenUIntFunctionReturnsFalse_DoNotUpdateValue)
        {
            CDiagramEntity entity;
            CDiagramEditor editor;
            CString test("test");
            CTypedPropertyItem<unsigned int> item(test, &entity, &editor, &DummyUIntFunction, 0);

            Assert::AreEqual((unsigned int)0, item.GetValue());
            Assert::IsFalse(item.SetValue(12));
            Assert::AreEqual((unsigned int)0, item.GetValue());

        }

#pragma endregion

    };
}