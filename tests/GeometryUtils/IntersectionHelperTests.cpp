#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/GeometryUtils/IntersectionHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CIntersectionHelperTests
{

    TEST_CLASS(CIntersectionHelperTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region SegmentIntersectsRect

        TEST_METHOD(SegmentIntersectsRect_VerticalLine_IntersectionFound)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(50, 50);
            CDoublePoint outside(50, 150); // vertical line

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::IsTrue(result.x >= rect.left && result.x <= rect.right);
            Assert::IsTrue(result.y >= rect.top && result.y <= rect.bottom);
        }

        TEST_METHOD(SegmentIntersectsRect_HorizontalLine_IntersectionFound)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(50, 50);
            CDoublePoint outside(150, 50); // horizontal line

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::IsTrue(result.x >= rect.left && result.x <= rect.right);
            Assert::IsTrue(result.y >= rect.top && result.y <= rect.bottom);
        }

        TEST_METHOD(SegmentIntersectsRect_Diagonal_Q1_IntersectionFound)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(50, 50);
            CDoublePoint outside(150, 150); // right-bottom

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::IsTrue(result.x >= rect.left && result.x <= rect.right);
            Assert::IsTrue(result.y >= rect.top && result.y <= rect.bottom);
        }

        TEST_METHOD(SegmentIntersectsRect_Diagonal_Q2_IntersectionFound)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(50, 50);
            CDoublePoint outside(150, -50); // right-top

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::IsTrue(result.x >= rect.left && result.x <= rect.right);
            Assert::IsTrue(result.y >= rect.top && result.y <= rect.bottom);
        }

        TEST_METHOD(SegmentIntersectsRect_Diagonal_Q3_IntersectionFound)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(50, 50);
            CDoublePoint outside(-50, 150); // left-bottom

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::IsTrue(result.x >= rect.left && result.x <= rect.right);
            Assert::IsTrue(result.y >= rect.top && result.y <= rect.bottom);
        }

        TEST_METHOD(SegmentIntersectsRect_Diagonal_Q4_IntersectionFound)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(50, 50);
            CDoublePoint outside(-50, -50); // left-top

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::IsTrue(result.x >= rect.left && result.x <= rect.right);
            Assert::IsTrue(result.y >= rect.top && result.y <= rect.bottom);
        }

        TEST_METHOD(SegmentIntersectsRect_InnerOutsideOutside_NoIntersection)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(150, 150); // outside
            CDoublePoint outside(200, 200);

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::AreEqual(-1.0, result.x);
            Assert::AreEqual(-1.0, result.y);
        }

        TEST_METHOD(SegmentIntersectsRect_InnerInsideOutsideInside_NoIntersection)
        {
            CDoubleRect rect(0, 0, 100, 100);
            CDoublePoint inside(50, 50); // inside
            CDoublePoint outside(50, 50); // also inside

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsRect(inside, outside, rect);

            Assert::AreEqual(-1.0, result.x);
            Assert::AreEqual(-1.0, result.y);
        }

#pragma endregion

#pragma region SegmentIntersectsEllipse

        TEST_METHOD(SegmentIntersectsEllipse_InsideToOutside_IntersectionFound)
        {
            CDoubleRect rect(0, 0, 100, 50); // ellipse inscribed
            CDoublePoint inside(50, 25);
            CDoublePoint outside(150, 25);

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsEllipse(inside, outside, rect);

            Assert::IsTrue(result.x >= rect.left && result.x <= rect.right);
            Assert::IsTrue(result.y >= rect.top && result.y <= rect.bottom);
        }

#pragma endregion

#pragma region SegmentIntersectsPolygon

        TEST_METHOD(SegmentIntersectsPolygon_Triangle_IntersectionFound)
        {
            CObArray vertices;
            vertices.Add(new CDoublePoint(0.0, 0.0));
            vertices.Add(new CDoublePoint(1.0, 0.0));
            vertices.Add(new CDoublePoint(0.5, 1.0));

            CDoubleRect bounds(0, 0, 100, 100);
            CDoublePoint inside(50, 25);
            CDoublePoint outside(50, -50);

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsPolygon(inside, outside, bounds, vertices);

            Assert::IsTrue(result.x != -1 && result.y != -1);

            // cleanup
            for (int i = 0; i < vertices.GetSize(); ++i) delete (CDoublePoint*)vertices.GetAt(i);
        }

        TEST_METHOD(SegmentIntersectsPolygon_InvalidPolygon_NoIntersection)
        {
            CObArray vertices; // empty

            CDoubleRect bounds(0, 0, 100, 100);
            CDoublePoint inside(50, 50);
            CDoublePoint outside(150, 50);

            CDoublePoint result = CIntersectionHelper::SegmentIntersectsPolygon(inside, outside, bounds, vertices);

            Assert::AreEqual(-1.0, result.x);
            Assert::AreEqual(-1.0, result.y);
        }

#pragma endregion
    };
}