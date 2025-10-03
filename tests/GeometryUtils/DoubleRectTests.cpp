#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/GeometryUtils/DoubleRect.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CDoubleRectTests
{

    TEST_CLASS(CDoubleRectTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region ConstructorTests
        TEST_METHOD(Constructor_WhenInvokedWithoutParameters_Create0x0Rect)
        {
            CDoubleRect rect;
            Assert::AreEqual(0.0, rect.top);
            Assert::AreEqual(0.0, rect.left);
            Assert::AreEqual(0.0, rect.bottom);
            Assert::AreEqual(0.0, rect.right);
        }

        TEST_METHOD(Constructor_WhenCRectIsPassed_SetCorrectMeasures)
        {
            CDoubleRect rect(CRect(10, 20, 30, 40));
            Assert::AreEqual(20.0, rect.top);
            Assert::AreEqual(10.0, rect.left);
            Assert::AreEqual(40.0, rect.bottom);
            Assert::AreEqual(30.0, rect.right);
        }

        TEST_METHOD(Constructor_WhenMeasuresArePassed_SetCorrectMeasures)
        {
            CDoubleRect rect(10.1, 20.2, 30.3, 40.4);
            Assert::AreEqual(20.2, rect.top);
            Assert::AreEqual(10.1, rect.left);
            Assert::AreEqual(40.4, rect.bottom);
            Assert::AreEqual(30.3, rect.right);
        }

        TEST_METHOD(Constructor_WhenCDoubleRectIsPassed_SetCorrectMeasures)
        {
            CDoubleRect rect(10.1, 20.2, 30.3, 40.4);
            CDoubleRect rect2(rect);
            Assert::AreEqual(20.2, rect2.top);
            Assert::AreEqual(10.1, rect2.left);
            Assert::AreEqual(40.4, rect2.bottom);
            Assert::AreEqual(30.3, rect2.right);
        }

#pragma endregion

#pragma region PropertyComputationTests

        TEST_METHOD(Width_WhenInvoked_ReturnsCorrectWidth)
        {
            CDoubleRect rect(10.1, 20.2, 30.3, 40.4);
            Assert::AreEqual(20.2, rect.Height());
        }

        TEST_METHOD(Height_WhenInvoked_ReturnsCorrectHeight)
        {
            CDoubleRect rect(10.1, 20.2, 30.3, 40.4);
            Assert::AreEqual(20.2, rect.Height());

        }

        TEST_METHOD(Ratio_WhenInvoked_ReturnsCorrectRatio)
        {
            CDoubleRect rect(10.1, 20.2, 30.3, 60.6);
            Assert::AreEqual(2.0, rect.Ratio());

        }

#pragma endregion

#pragma region RectManipulationTests

        TEST_METHOD(SetRect_WhenCRectIsPassed_SetCorrectMeasures)
        {
            CDoubleRect rect;
            rect.SetRect(CRect(10.1, 20.2, 30.3, 40.4));
            
            Assert::AreEqual(20.0, rect.top);
            Assert::AreEqual(10.0, rect.left);
            Assert::AreEqual(40.0, rect.bottom);
            Assert::AreEqual(30.0, rect.right);
        }

        TEST_METHOD(SetRect_WhenMeasuresArePassed_SetCorrectMeasures)
        {
            CDoubleRect rect;
            rect.SetRect(10.1, 20.2, 30.3, 40.4);
            Assert::AreEqual(20.2, rect.top);
            Assert::AreEqual(10.1, rect.left);
            Assert::AreEqual(40.4, rect.bottom);
            Assert::AreEqual(30.3, rect.right);
        }

        TEST_METHOD(ToCRect_WhenInvoked_ReturnCorrectMeasures)
        {
            CDoubleRect rect(10.1, 20.2, 30.3, 40.4);
            CRect crect = rect.ToCRect();
            Assert::AreEqual(CRect(10,20,30,40), crect);
        }
        
        TEST_METHOD(Assignment_WhenPerformed_ReturnCorrectMeasures)
        {
            CDoubleRect rect(10.1, 20.2, 30.3, 40.4);
            CDoubleRect rect2(50.5,60.6,70.7,80.8);
            rect2 = rect;

            Assert::AreEqual(20.2, rect2.top);
            Assert::AreEqual(10.1, rect2.left);
            Assert::AreEqual(40.4, rect2.bottom);
            Assert::AreEqual(30.3, rect2.right);
        }
#pragma endregion

    };
}