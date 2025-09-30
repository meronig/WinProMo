#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/GeometryUtils/GeometryHelper.h"
#include "../../src/DiagramEditor/DiagramEntity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CGeometryHelperTests
{

    TEST_CLASS(CGeometryHelperTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region AspectRatioTests

        TEST_METHOD(EnforceAspectRatio_TopMiddle_AdjustsWidth)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(0, -10, 100, 50); // moved top
            CPoint cursor(50, -10);

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_TOPMIDDLE, cursor);

            // Width should expand/contract according to deltaY / ratio
            double expectedWidth = oldRect.Width() + (oldRect.top - newRect.top) / oldRect.Ratio();
            Assert::AreEqual(expectedWidth, newRect.Width(), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_BottomMiddle_AdjustsWidth)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(0, 60, 100, 60); // moved bottom
            CPoint cursor(50, 60);

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_BOTTOMMIDDLE, cursor);

            double expectedWidth = oldRect.Width() + (newRect.bottom - oldRect.bottom) / oldRect.Ratio();
            Assert::AreEqual(expectedWidth, newRect.Width(), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_LeftMiddle_AdjustsHeight)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(-10, 0, 100, 50); // moved left
            CPoint cursor(-10, 25);

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_LEFTMIDDLE, cursor);

            double expectedHeight = oldRect.Height() + (oldRect.left - newRect.left) * oldRect.Ratio();
            Assert::AreEqual(expectedHeight, newRect.Height(), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_RightMiddle_AdjustsHeight)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(110, 0, 110, 50); // moved right
            CPoint cursor(110, 25);

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_RIGHTMIDDLE, cursor);

            double expectedHeight = oldRect.Height() + (newRect.right - oldRect.right) * oldRect.Ratio();
            Assert::AreEqual(expectedHeight, newRect.Height(), 1e-6);
        }
        TEST_METHOD(EnforceAspectRatio_TopLeft_CursorPrioritizesHorizontal)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(-10, -5, 100, 50);
            CPoint cursor(-20, 1); // horizontal difference larger than vertical

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_TOPLEFT, cursor);

            // Horizontal branch taken: left adjusted
            Assert::AreEqual(newRect.left, oldRect.left - ((oldRect.top - newRect.top) / oldRect.Ratio()), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_TopLeft_CursorPrioritizesVertical)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(-5, -10, 100, 50);
            CPoint cursor(-1, -20); // vertical difference larger than horizontal

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_TOPLEFT, cursor);

            // Vertical branch taken: top adjusted
            Assert::AreEqual(newRect.top, oldRect.top - ((oldRect.left - newRect.left) * oldRect.Ratio()), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_TopRight_CursorPrioritizesHorizontal)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(110, -5, 110, 50);
            CPoint cursor(120, 0); // horizontal difference larger

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_TOPRIGHT, cursor);

            // Horizontal branch: right adjusted
            Assert::AreEqual(newRect.right, oldRect.right + ((oldRect.top - newRect.top) / oldRect.Ratio()), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_TopRight_CursorPrioritizesVertical)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(105, -10, 105, 50);
            CPoint cursor(101, -20); // vertical difference larger

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_TOPRIGHT, cursor);

            // Vertical branch: top adjusted
            Assert::AreEqual(newRect.top, oldRect.top - ((newRect.right - oldRect.right) * oldRect.Ratio()), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_BottomLeft_CursorPrioritizesHorizontal)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(-10, 55, 100, 55);
            CPoint cursor(-20, 55); // horizontal difference larger

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_BOTTOMLEFT, cursor);

            // Horizontal branch: left adjusted
            Assert::AreEqual(newRect.left, oldRect.left - ((newRect.bottom - oldRect.bottom) / oldRect.Ratio()), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_BottomLeft_CursorPrioritizesVertical)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(-5, 55, 100, 55);
            CPoint cursor(-1, 60); // vertical difference larger

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_BOTTOMLEFT, cursor);

            // Vertical branch: bottom adjusted
            Assert::AreEqual(newRect.bottom, oldRect.bottom + ((oldRect.left - newRect.left) * oldRect.Ratio()), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_BottomRight_CursorPrioritizesHorizontal)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(110, 60, 110, 60);
            CPoint cursor(120, 60); // horizontal difference larger

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_BOTTOMRIGHT, cursor);

            // Horizontal branch: right adjusted
            Assert::AreEqual(newRect.right, oldRect.right + ((newRect.bottom - oldRect.bottom) / oldRect.Ratio()), 1e-6);
        }

        TEST_METHOD(EnforceAspectRatio_BottomRight_CursorPrioritizesVertical)
        {
            CDoubleRect oldRect(0, 0, 100, 50);
            CDoubleRect newRect(105, 60, 105, 60);
            CPoint cursor(101, 65); // vertical difference larger

            CGeometryHelper::EnforceAspectRatio(oldRect, newRect, DEHT_BOTTOMRIGHT, cursor);

            // Vertical branch: bottom adjusted
            Assert::AreEqual(newRect.bottom, oldRect.bottom + ((newRect.right - oldRect.right) * oldRect.Ratio()), 1e-6);
        }

#pragma endregion
#pragma region AlignToAxisTests

        TEST_METHOD(AlignToAxis_VerticalSnap_FromBottomRight)
        {
            CDoubleRect rect(0, 0, 10, 30); // dy > dx*2
            CGeometryHelper::AlignToAxis(rect, DEHT_BOTTOMRIGHT);

            Assert::AreEqual(rect.right, rect.left, 1e-6); // snapped vertical
        }

        TEST_METHOD(AlignToAxis_HorizontalSnap_FromBottomRight)
        {
            CDoubleRect rect(0, 0, 30, 10); // dy < dx/2
            CGeometryHelper::AlignToAxis(rect, DEHT_BOTTOMRIGHT);

            Assert::AreEqual(rect.bottom, rect.top, 1e-6); // snapped horizontal
        }

        TEST_METHOD(AlignToAxis_DiagonalSnap_FromBottomRight_VerticalDominant)
        {
            CDoubleRect rect(0, 0, 10, 20); // dy > dx
            CGeometryHelper::AlignToAxis(rect, DEHT_BOTTOMRIGHT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

        TEST_METHOD(AlignToAxis_DiagonalSnap_FromBottomRight_HorizontalDominant)
        {
            CDoubleRect rect(0, 0, 20, 10); // dx > dy
            CGeometryHelper::AlignToAxis(rect, DEHT_BOTTOMRIGHT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

        TEST_METHOD(AlignToAxis_DiagonalSnapReversed_FromBottomRight_VerticalDominant)
        {
            CDoubleRect rect(10, 20, 0, 0); // dy > dx
            CGeometryHelper::AlignToAxis(rect, DEHT_BOTTOMRIGHT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

        TEST_METHOD(AlignToAxis_DiagonalSnapReversed_FromBottomRight_HorizontalDominant)
        {
            CDoubleRect rect(20, 10, 0, 0); // dx > dy
            CGeometryHelper::AlignToAxis(rect, DEHT_BOTTOMRIGHT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

        TEST_METHOD(AlignToAxis_VerticalSnap_FromTopLeft)
        {
            CDoubleRect rect(0, 0, 10, 30);
            CGeometryHelper::AlignToAxis(rect, DEHT_TOPLEFT);

            Assert::AreEqual(rect.left, rect.right, 1e-6);
        }

        TEST_METHOD(AlignToAxis_HorizontalSnap_FromTopLeft)
        {
            CDoubleRect rect(0, 0, 30, 10);
            CGeometryHelper::AlignToAxis(rect, DEHT_TOPLEFT);

            Assert::AreEqual(rect.top, rect.bottom, 1e-6);
        }

        TEST_METHOD(AlignToAxis_DiagonalSnap_FromTopLeft_VerticalDominant)
        {
            CDoubleRect rect(0, 0, 10, 20);
            CGeometryHelper::AlignToAxis(rect, DEHT_TOPLEFT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

        TEST_METHOD(AlignToAxis_DiagonalSnap_FromTopLeft_HorizontalDominant)
        {
            CDoubleRect rect(0, 0, 20, 10);
            CGeometryHelper::AlignToAxis(rect, DEHT_TOPLEFT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

        TEST_METHOD(AlignToAxis_DiagonalSnapReversed_FromTopLeft_VerticalDominant)
        {
            CDoubleRect rect(10, 20, 0, 0);
            CGeometryHelper::AlignToAxis(rect, DEHT_TOPLEFT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

        TEST_METHOD(AlignToAxis_DiagonalSnapReversed_FromTopLeft_HorizontalDominant)
        {
            CDoubleRect rect(20, 10, 0, 0);
            CGeometryHelper::AlignToAxis(rect, DEHT_TOPLEFT);

            Assert::AreEqual(rect.bottom - rect.top, rect.right - rect.left, 1e-6);
        }

#pragma endregion

    };
}
