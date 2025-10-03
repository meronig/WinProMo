#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/GeometryUtils/DoublePoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CDoublePointTests
{

    TEST_CLASS(CDoublePointTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region ConstructorTests
        TEST_METHOD(Constructor_WhenInvokedWithoutParameters_Create0x0Point)
        {
            CDoublePoint pt;
            Assert::AreEqual(0.0, pt.x);
            Assert::AreEqual(0.0, pt.y);
        }

        TEST_METHOD(Constructor_WhenCPointIsPassed_SetCorrectMeasures)
        {
            CDoublePoint pt(CPoint(10,20));
            Assert::AreEqual(10.0, pt.x);
            Assert::AreEqual(20.0, pt.y);
        }

        TEST_METHOD(Constructor_WhenMeasuresArePassed_SetCorrectMeasures)
        {
            CDoublePoint pt(10.1, 20.2);
            Assert::AreEqual(10.1, pt.x);
            Assert::AreEqual(20.2, pt.y);
        }

        TEST_METHOD(Constructor_WhenCDoublePointIsPassed_SetCorrectMeasures)
        {
            CDoublePoint pt(10.1, 20.2);
            CDoublePoint pt2(pt);
            Assert::AreEqual(10.1, pt2.x);
            Assert::AreEqual(20.2, pt2.y);
        }

#pragma endregion

#pragma region PointManipulationTests

        TEST_METHOD(SetPoint_WhenCPointIsPassed_SetCorrectMeasures)
        {
            CDoublePoint pt;
            pt.SetPoint(CPoint(10, 20));
            Assert::AreEqual(10.0, pt.x);
            Assert::AreEqual(20.0, pt.y);
        }

        TEST_METHOD(SetPoint_WhenMeasuresArePassed_SetCorrectMeasures)
        {
            CDoublePoint pt;
            pt.SetPoint(10.1, 20.2);
            Assert::AreEqual(10.1, pt.x);
            Assert::AreEqual(20.2, pt.y);
        }

        TEST_METHOD(ToCRect_WhenInvoked_ReturnCorrectMeasures)
        {
            CDoublePoint pt(10.1, 20.2);
            CPoint cpoint = pt.ToCPoint();
            Assert::AreEqual(CPoint(10, 20), cpoint);
        }

        TEST_METHOD(Assignment_WhenPerformed_ReturnCorrectMeasures) 
        {
            CDoublePoint pt(30.3, 40.4);
            CDoublePoint pt2(10.1, 20.2);
            pt = pt2;
            Assert::AreEqual(10.1, pt.x);
            Assert::AreEqual(20.2, pt.y);
        }

#pragma endregion

    };
}