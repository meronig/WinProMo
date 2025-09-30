#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/PropertyItem/PropertyItem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CPropertyItemTests
{

    TEST_CLASS(CPropertyItemTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region ConstructorTests
        TEST_METHOD(Constructor_WhenInvoked_SetName)
        {
            CDiagramEntity entity;
            CDiagramEditor editor;
            CString test("test");
            CPropertyItem item(test, &entity, &editor);

            Assert::AreEqual(test, item.GetName());
            Assert::AreEqual((unsigned int)0, item.GetCtrlID());
        }

#pragma endregion

#pragma region IdentificationTests
        TEST_METHOD(SetCtrlID_WhenInvoked_SetControlID)
        {
            CDiagramEntity entity;
            CDiagramEditor editor;
            CString test("test");
            CPropertyItem item(test, &entity, &editor);

            item.SetCtrlID(10);
            Assert::AreEqual((unsigned int)10, item.GetCtrlID());
        }

#pragma endregion

    };
}