#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/PropertyItem/CustomPropertyItem.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CCustomPropertyItemTests
{
    BOOL DummyCustomFunction(CDiagramEntity* entity, CDiagramEditor* editor) {
        return TRUE;
    }

    TEST_CLASS(CCustomPropertyItemTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region InvocationTests
        TEST_METHOD(SetValue_WhenInvoked_InvokeSetterFunction)
        {
            CDiagramEntity entity;
            CDiagramEditor editor;
            CString test("test");
            CCustomPropertyItem item(test, &entity, &editor, &DummyCustomFunction);

            Assert::IsTrue(item.SetValue());
        }

        TEST_METHOD(SetValue_WhenEditorIsMissing_ReturnFalse)
        {
            CDiagramEntity entity;
            CString test("test");
            CCustomPropertyItem item(test, &entity, NULL, &DummyCustomFunction);

            Assert::IsFalse (item.SetValue());
        }

#pragma endregion

    };
}