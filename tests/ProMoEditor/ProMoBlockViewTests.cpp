#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoBlockView.h"
#include "../../src/ProMoEditor/ProMoEdgeView.h"
#include <vector>
#include "../WinProMoTests.h"

class CProMoBlockViewTestStub : public CProMoBlockView
{
public:
    CPoint fixedIntersection = CPoint(123, 456);

    virtual void SetShape(const int& type) override
    {
        CProMoBlockView::SetShape(type);
    }
    virtual BOOL AddVertex(const CDoublePoint& point) override
    {
        return CProMoBlockView::AddVertex(point);
    }
    virtual CObArray* GetVertices() override
    {
        return CProMoBlockView::GetVertices();
    }


protected:
    CPoint GetIntersection(CPoint /*inner*/, CPoint /*outer*/) override
    {
        return fixedIntersection;
    }
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoBlockViewTests
{
    TEST_CLASS(CProMoBlockViewTests)
    {
        
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region ConstructionAndDefaults

        TEST_METHOD(Constructor_WhenCalled_InitializesDefaults)
        {
            CProMoBlockViewTestStub view;

            Assert::IsFalse(view.IsTarget());
            Assert::IsFalse(view.HasLockedProportions());
            TestHelpers::PointerAssert::IsNotNull(view.GetModel());
        }

#pragma endregion

#pragma region FormattingTests
        TEST_METHOD(SetFontName_ValidName_SetsFontName)
        {
            // Arrange
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            CString expected = _T("Arial");

            // Act
            BOOL result = view.SetFontName(expected);

            // Assert
            Assert::IsTrue(result);
            Assert::AreEqual(expected, view.GetFontName());

            view.SetLock(LOCK_FONTNAME);

            result = view.SetFontName(CString("Times New Roman"));

            Assert::IsFalse(result);
            Assert::AreEqual(expected, view.GetFontName());

        }

        TEST_METHOD(SetFontSize_ValidSize_SetsFontSize)
        {
            CProMoBlockView view;
			view.GetBlockModel()->RecreateLabels();
            unsigned int size = 14;

            BOOL result = view.SetFontSize(size);

            Assert::IsTrue(result);
            Assert::AreEqual(size, view.GetFontSize());

            result = view.SetFontSize(0);

            Assert::IsFalse(result);
            Assert::AreEqual(size, view.GetFontSize());

            view.SetLock(LOCK_FONTSIZE);

            result = view.SetFontSize(20);

            Assert::IsFalse(result);
            Assert::AreEqual(size, view.GetFontSize());
        }

        TEST_METHOD(SetFontWeight_ValidWeight_SetsFontWeight)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int weight = FW_BOLD;

            BOOL result = view.SetFontWeight(weight);

            Assert::IsTrue(result);
            Assert::AreEqual(weight, view.GetFontWeight());

            view.SetLock(LOCK_FONTWEIGHT);

            result = view.SetFontWeight(FW_HEAVY);

            Assert::IsFalse(result);
            Assert::AreEqual(weight, view.GetFontWeight());
        }

        TEST_METHOD(SetFontItalic_True_SetsItalic)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            BOOL italic = TRUE;

            BOOL result = view.SetFontItalic(italic);

            Assert::IsTrue(result);
            Assert::IsTrue(view.IsFontItalic());

            view.SetLock(LOCK_FONTITALIC);

            result = view.SetFontItalic(FALSE);

            Assert::IsFalse(result);
            Assert::IsTrue(view.IsFontItalic());
        }

        TEST_METHOD(SetFontUnderline_True_SetsUnderline)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            BOOL underline = TRUE;

            BOOL result = view.SetFontUnderline(underline);

            Assert::IsTrue(result);
            Assert::IsTrue(view.IsFontUnderline());

            view.SetLock(LOCK_FONTUNDERLINE);

            result = view.SetFontUnderline(FALSE);

            Assert::IsFalse(result);
            Assert::IsTrue(view.IsFontUnderline());
        }

        TEST_METHOD(SetFontStrikeOut_True_SetsStrikeOut)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            BOOL strikeOut = TRUE;

            BOOL result = view.SetFontStrikeOut(strikeOut);

            Assert::IsTrue(result);
            Assert::IsTrue(view.IsFontStrikeOut());

            view.SetLock(LOCK_FONTSTRIKEOUT);

            result = view.SetFontStrikeOut(FALSE);

            Assert::IsFalse(result);
            Assert::IsTrue(view.IsFontStrikeOut());
        }

        TEST_METHOD(SetFontColor_ValidColor_SetsColor)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            COLORREF color = RGB(255, 0, 0);

            BOOL result = view.SetTextColor(color);

            Assert::IsTrue(result);
            Assert::AreEqual(color, view.GetTextColor());

            view.SetLock(LOCK_TEXTCOLOR);

            result = view.SetTextColor(RGB(0, 255, 0));

            Assert::IsFalse(result);
            Assert::AreEqual(color, view.GetTextColor());
        }

        TEST_METHOD(SetBkColor_ValidColor_SetsColor)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            COLORREF color = RGB(255, 0, 0);

            BOOL result = view.SetBkColor(color);

            Assert::IsTrue(result);
            Assert::AreEqual(color, view.GetBkColor());

            view.SetLock(LOCK_BKCOLOR);

            result = view.SetBkColor(RGB(0, 255, 0));

            Assert::IsFalse(result);
            Assert::AreEqual(color, view.GetBkColor());
        }

        TEST_METHOD(SetBkMode_ValidMode_SetsBkMode)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int mode = OPAQUE;

            BOOL result = view.SetBkMode(mode);

            Assert::IsTrue(result);
            Assert::AreEqual(mode, view.GetBkMode());

            view.SetLock(LOCK_BKMODE);

            result = view.SetBkMode(TRANSPARENT);

            Assert::IsFalse(result);
            Assert::AreEqual(mode, view.GetBkMode());
        }

        TEST_METHOD(SetTextAlignment_ValidValue_SetsAlignment)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int alignment = DT_VCENTER;

            BOOL result = view.SetTextAlignment(alignment);

            Assert::IsTrue(result);
            Assert::AreEqual(alignment, view.GetTextAlignment());

            view.SetLock(LOCK_ALIGNMENT);

            result = view.SetTextAlignment(DT_RIGHT);

            Assert::IsFalse(result);
            Assert::AreEqual(alignment, view.GetTextAlignment());
        }

        TEST_METHOD(SetTextAlignment_ValidValue_SetsOnlyAppropriateFlags)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int hAlignment = DT_LEFT;
            unsigned int vAlignment = DT_BOTTOM;
            unsigned int otherFlag = DT_WORDBREAK;

            BOOL result = view.SetTextAlignment(hAlignment | vAlignment | otherFlag);

            Assert::IsTrue(result);
            Assert::AreEqual(hAlignment | vAlignment | otherFlag, view.GetTextAlignment());

            result = view.SetTextHorizontalAlignment(DT_RIGHT);

            Assert::IsTrue(result);
            Assert::AreEqual(DT_RIGHT, (int)view.GetTextHorizontalAlignment());
            Assert::AreEqual(vAlignment, view.GetTextVerticalAlignment());
            Assert::AreEqual(DT_RIGHT | vAlignment | otherFlag, view.GetTextAlignment());

            result = view.SetTextVerticalAlignment(DT_TOP);

            Assert::IsTrue(result);
            Assert::AreEqual(DT_RIGHT, (int)view.GetTextHorizontalAlignment());
            Assert::AreEqual(DT_TOP, (int)view.GetTextVerticalAlignment());
            Assert::AreEqual(DT_RIGHT | DT_TOP | otherFlag, view.GetTextAlignment());

        }

        TEST_METHOD(SetTextAlignmentFlag_ValidValue_SetsAlignment)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int hAlignment = DT_RIGHT;
            unsigned int vAlignment = DT_BOTTOM;
            unsigned int groupFlag = DT_WORDBREAK;
            unsigned int otherFlag = DT_NOPREFIX;
            view.SetTextAlignment(0);

            BOOL result = view.SetTextAlignmentFlag(vAlignment, TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(view.HasTextAlignmentFlag(vAlignment));
            Assert::AreEqual(vAlignment, view.GetTextAlignment());

            result = view.SetTextAlignmentFlag(hAlignment, TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(view.HasTextAlignmentFlag(hAlignment));
            Assert::AreEqual(vAlignment | hAlignment, view.GetTextAlignment());

            result = view.SetTextAlignmentFlag(groupFlag, TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(view.HasTextAlignmentFlag(groupFlag));
            Assert::AreEqual(vAlignment | hAlignment | groupFlag, view.GetTextAlignment());

            result = view.SetTextAlignmentFlag(otherFlag, TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(view.HasTextAlignmentFlag(otherFlag));
            Assert::AreEqual(vAlignment | hAlignment | groupFlag | otherFlag, view.GetTextAlignment());

            result = view.SetTextAlignmentFlag(vAlignment, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(view.HasTextAlignmentFlag(vAlignment));
            Assert::AreEqual(hAlignment | groupFlag | otherFlag, view.GetTextAlignment());

            result = view.SetTextAlignmentFlag(otherFlag, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(view.HasTextAlignmentFlag(otherFlag));
            Assert::AreEqual(hAlignment | groupFlag, view.GetTextAlignment());

            result = view.SetTextAlignmentFlag(hAlignment, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(view.HasTextAlignmentFlag(hAlignment));
            Assert::AreEqual(groupFlag, view.GetTextAlignment());

            result = view.SetTextAlignmentFlag(groupFlag, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(view.HasTextAlignmentFlag(groupFlag));
            Assert::AreEqual(0, (int)view.GetTextAlignment());

        }

        TEST_METHOD(SetLineColor_ValidColor_SetsColor)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            COLORREF color = RGB(255, 0, 0);

            BOOL result = view.SetLineColor(color);

            Assert::IsTrue(result);
            Assert::AreEqual(color, view.GetLineColor());

            view.SetLock(LOCK_LINECOLOR);

            result = view.SetLineColor(RGB(0, 255, 0));

            Assert::IsFalse(result);
            Assert::AreEqual(color, view.GetLineColor());
        }

        TEST_METHOD(SetLineWidth_ValidWidth_SetsWidth)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int width = 3;

            BOOL result = view.SetLineWidth(width);

            Assert::IsTrue(result);
            Assert::AreEqual(width, view.GetLineWidth());

            view.SetLock(LOCK_LINEWIDTH);

            result = view.SetLineWidth(5);

            Assert::IsFalse(result);
            Assert::AreEqual(width, view.GetLineWidth());
        }

        TEST_METHOD(SetLineStyle_ValidStyle_SetsStyle)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int style = PS_DASHDOT;

            BOOL result = view.SetLineStyle(style);

            Assert::IsTrue(result);
            Assert::AreEqual(style, view.GetLineStyle());

            view.SetLock(LOCK_LINESTYLE);

            result = view.SetLineStyle(PS_DOT);

            Assert::IsFalse(result);
            Assert::AreEqual(style, view.GetLineStyle());
        }

        TEST_METHOD(SetFillColor_ValidColor_SetsColor)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            COLORREF color = RGB(255, 0, 0);

            BOOL result = view.SetFillColor(color);

            Assert::IsTrue(result);
            Assert::AreEqual(color, view.GetFillColor());

            view.SetLock(LOCK_FILLCOLOR);

            result = view.SetFillColor(RGB(0, 255, 0));

            Assert::IsFalse(result);
            Assert::AreEqual(color, view.GetFillColor());
        }

        TEST_METHOD(SetFillPattern_WhenInvoked_SetsPattern)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int width = 3;

            BOOL result = view.SetFillPattern(TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(view.IsFillPattern());

            view.SetLock(LOCK_FILLSTYLE);

            result = view.SetFillPattern(FALSE);

            Assert::IsFalse(result);
            Assert::IsTrue(view.IsFillPattern());
        }

        TEST_METHOD(SetFillStyle_ValidStyle_SetsStyle)
        {
            CProMoBlockView view;
            view.GetBlockModel()->RecreateLabels();
            unsigned int style = HS_CROSS;

            BOOL result = view.SetFillStyle(style);

            Assert::IsTrue(result);
            Assert::AreEqual(style, view.GetFillStyle());

            view.SetLock(LOCK_FILLSTYLE);

            result = view.SetFillStyle(PS_DOT);

            Assert::IsFalse(result);
            Assert::AreEqual(style, view.GetFillStyle());
        }

#pragma endregion

#pragma region LayoutTests

        TEST_METHOD(SetVisible_False_HidesView)
        {
            CProMoBlockView view;

            view.SetVisible(FALSE);

            Assert::IsFalse(view.IsVisible());
        }

#pragma endregion

#pragma region TargetFlag

        TEST_METHOD(SetTarget_WhenTrue_IsTargetReturnsTrue)
        {
            CProMoBlockViewTestStub view;
            view.SetTarget(TRUE);

            Assert::IsTrue(view.IsTarget());
        }

        TEST_METHOD(SetTarget_WhenFalse_IsTargetReturnsFalse)
        {
            CProMoBlockViewTestStub view;
            view.SetTarget(FALSE);

            Assert::IsFalse(view.IsTarget());
        }

#pragma endregion

#pragma region LockedProportions

        TEST_METHOD(SetLockedProportions_WhenTrue_HasLockedProportionsReturnsTrue)
        {
            CProMoBlockViewTestStub view;
            view.SetLockedProportions(TRUE);

            Assert::IsTrue(view.HasLockedProportions());
        }

        TEST_METHOD(SetLockedProportions_WhenFalse_HasLockedProportionsReturnsFalse)
        {
            CProMoBlockViewTestStub view;
            view.SetLockedProportions(FALSE);

            Assert::IsFalse(view.HasLockedProportions());
        }

#pragma endregion

#pragma region CopyAndClone

        TEST_METHOD(Clone_WhenCalled_ReturnsIndependentCopy)
        {
            CProMoBlockViewTestStub view;
            view.SetTarget(TRUE);
            view.SetLockedProportions(TRUE);

            std::unique_ptr<CDiagramEntity> clone(view.Clone());
            auto* clonedView = dynamic_cast<CProMoBlockView*>(clone.get());

            TestHelpers::PointerAssert::IsNotNull(clonedView);
            TestHelpers::PointerAssert::AreNotEqual((CProMoBlockView*)(&view), clonedView);
            TestHelpers::PointerAssert::AreNotEqual(view.GetModel(), clonedView->GetModel());
            Assert::AreNotEqual(view.IsTarget(), clonedView->IsTarget());
            Assert::AreEqual(view.HasLockedProportions(), clonedView->HasLockedProportions());
        }

        TEST_METHOD(Clone_NewObject_PropertiesCopied)
        {
            CProMoBlockView original;
            original.SetRect(100, 50, 250, 120);
            original.SetBkColor(RGB(0, 255, 0));
            original.SetBkMode(OPAQUE);
            original.SetLineColor(RGB(0, 0, 255));
            original.SetLineWidth(4);
            original.SetLineStyle(PS_DASH);
            original.SetFillColor(RGB(255, 0, 0));
            original.SetFillStyle(HS_CROSS);
            original.SetFillPattern(TRUE);

            // Act
            std::unique_ptr<CDiagramEntity> clone(original.Clone());

            // Assert
            CProMoBlockView* clonedBlock = dynamic_cast<CProMoBlockView*>(clone.get());
            Assert::IsNotNull(clonedBlock);

            Assert::AreEqual(original.GetLeft(), clonedBlock->GetLeft());
            Assert::AreEqual(original.GetTop(), clonedBlock->GetTop());
            Assert::AreEqual(original.GetRight(), clonedBlock->GetRight());
            Assert::AreEqual(original.GetBottom(), clonedBlock->GetBottom());
            Assert::AreEqual(original.GetBkColor(), clonedBlock->GetBkColor());
            Assert::AreEqual(original.GetBkMode(), clonedBlock->GetBkMode());
            Assert::AreEqual(original.GetLineColor(), clonedBlock->GetLineColor());
            Assert::AreEqual(original.GetLineWidth(), clonedBlock->GetLineWidth());
            Assert::AreEqual(original.GetLineStyle(), clonedBlock->GetLineStyle());
            Assert::AreEqual(original.GetFillColor(), clonedBlock->GetFillColor());
            Assert::AreEqual(original.IsFillPattern(), clonedBlock->IsFillPattern());
            Assert::AreEqual(original.GetFillStyle(), clonedBlock->GetFillStyle());
        }

#pragma endregion

#pragma region Geometry

        TEST_METHOD(SetRect_WhenCRectPassed_UpdatesCoordinates)
        {
            CProMoBlockViewTestStub view;
            CRect rect(10, 20, 210, 120);

            view.SetRect(rect);

            Assert::AreEqual(10.0, view.GetLeft());
            Assert::AreEqual(20.0, view.GetTop());
            Assert::AreEqual(210.0, view.GetRight());
            Assert::AreEqual(120.0, view.GetBottom());
        }

        TEST_METHOD(SetRect_WhenCoordinatesPassed_UpdatesCoordinates)
        {
            CProMoBlockViewTestStub view;
            view.SetRect(5.0, 15.0, 155.0, 65.0);

            Assert::AreEqual(5.0, view.GetLeft());
            Assert::AreEqual(15.0, view.GetTop());
            Assert::AreEqual(155.0, view.GetRight());
            Assert::AreEqual(65.0, view.GetBottom());
        }

#pragma endregion

#pragma region AutoResize

        TEST_METHOD(AutoResize_WhenChildBottomExceedsParent_ParentBottomExpands)
        {
            CProMoBlockViewTestStub parent;
            parent.SetRect(0, 0, 100, 100); // smaller than min width (128), height ok

            CProMoBlockViewTestStub child;
            child.SetRect(10, 10, 50, 120); // bottom protrudes

            child.SetParentBlock(&parent);

            parent.AutoResize();

            Assert::IsTrue(parent.GetBottom() >= 125.0, L"Parent bottom should expand to child's bottom + 5.");
            Assert::IsTrue(parent.GetRight() - parent.GetLeft() >= 128, L"Width must respect minimum of 128.");
            Assert::IsTrue(parent.GetBottom() - parent.GetTop() >= 32, L"Height must respect minimum of 32.");
        }

        TEST_METHOD(AutoResize_WhenChildRightExceedsParent_ParentRightExpands)
        {
            CProMoBlockViewTestStub parent;
            parent.SetRect(0, 0, 100, 100);

            CProMoBlockViewTestStub child;
            child.SetRect(10, 10, 140, 50); // right protrudes

            child.SetParentBlock(&parent);

            parent.AutoResize();

            Assert::IsTrue(parent.GetRight() >= 145.0, L"Parent right should expand to child's right + 5.");
            Assert::IsTrue(parent.GetRight() - parent.GetLeft() >= 128, L"Width must respect minimum of 128.");
            Assert::IsTrue(parent.GetBottom() - parent.GetTop() >= 32, L"Height must respect minimum of 32.");
        }

        TEST_METHOD(AutoResize_WhenChildTopIsAboveParent_ParentTopShrinksUpwardButNotBelowMinHeight)
        {
            CProMoBlockViewTestStub parent;
            parent.SetRect(0, 0, 100, 40); // height is just above minimum

            CProMoBlockViewTestStub child;
            child.SetRect(10, -20, 50, 50); // top protrudes

            child.SetParentBlock(&parent);

            parent.AutoResize();

            Assert::IsTrue(parent.GetTop() <= -25.0, L"Parent top should shrink to child's top - 5.");
            Assert::IsTrue(parent.GetRight() - parent.GetLeft() >= 128, L"Width must respect minimum of 128.");
            Assert::IsTrue(parent.GetBottom() - parent.GetTop() >= 32, L"Height must respect minimum of 32.");
        }

        TEST_METHOD(AutoResize_WhenChildLeftIsLeftOfParent_ParentLeftShrinksLeftwardButNotBelowMinWidth)
        {
            CProMoBlockViewTestStub parent;
            parent.SetRect(0, 0, 130, 100); // width is just above minimum

            CProMoBlockViewTestStub child;
            child.SetRect(-30, 10, 50, 50); // left protrudes

            child.SetParentBlock(&parent);

            parent.AutoResize();

            Assert::IsTrue(parent.GetLeft() <= -35.0, L"Parent left should shrink to child's left - 5.");
            Assert::IsTrue(parent.GetRight() - parent.GetLeft() >= 128, L"Width must respect minimum of 128.");
            Assert::IsTrue(parent.GetBottom() - parent.GetTop() >= 32, L"Height must respect minimum of 32.");
        }

        TEST_METHOD(AutoResize_WhenParentExists_PropagatesToParentAutoResize)
        {
            CProMoBlockViewTestStub grandParent;
            grandParent.SetRect(0, 0, 100, 100);

            CProMoBlockViewTestStub parent;
            parent.SetRect(10, 10, 80, 80);

            parent.SetParentBlock(&grandParent);

            CProMoBlockViewTestStub child;
            child.SetRect(10, 10, 200, 50); // right protrudes

            child.SetParentBlock(&parent);

            parent.AutoResize();

            Assert::IsTrue(grandParent.GetRight() >= 200, L"AutoResize should propagate to parent.");
            Assert::IsTrue(grandParent.GetRight() - parent.GetLeft() >= 128, L"Width must respect minimum of 128.");
            Assert::IsTrue(grandParent.GetBottom() - parent.GetTop() >= 32, L"Height must respect minimum of 32.");
        }

#pragma endregion

#pragma region RecomputeIntersectionLinks

        TEST_METHOD(RecomputeIntersectionLinks_WhenIncomingAndOutgoingEdgesExist_UpdatesEdgePositions)
        {
            // Arrange
            CProMoBlockViewTestStub parent;
            parent.SetRect(0, 0, 200, 100);

            // Add incoming edge
            CProMoEdgeView inEdgeView;
            inEdgeView.SetRect(CRect(0, 0, 10, 10));
            inEdgeView.SetDestination(&parent);
            
            // Add outgoing edge
            CProMoEdgeView outEdgeView;
            outEdgeView.SetRect(CRect(0, 0, 10, 10));
            outEdgeView.SetSource(&parent);

            // Add a child block
            CProMoBlockView child;
            child.SetRect(150, 50, 250, 120);
            child.SetParentBlock(&parent);
            
            // Act
            parent.AutoResize(); // indirectly calls RecomputeIntersectionLinks

            // Assert
            Assert::AreEqual(123.0, inEdgeView.GetRight());
            Assert::AreEqual(456.0, inEdgeView.GetBottom());
            Assert::AreEqual(123.0, outEdgeView.GetLeft());
            Assert::AreEqual(456.0, outEdgeView.GetTop());
        }

        TEST_METHOD(RecomputeIntersectionLinks_WhenMultipleEdgesAndChildrenExist_UpdatesAllEdgePositions)
        {
            // Arrange
            CProMoBlockViewTestStub parent;
            parent.SetRect(0, 0, 200, 100);

            // Add multiple incoming edges
            std::vector<CProMoEdgeView> incomingEdges(3);
            for (auto& edgeView : incomingEdges)
            {
                edgeView.SetRect(CRect(0, 0, 10, 10));
                edgeView.SetDestination(&parent);
            }

            // Add multiple outgoing edges
            std::vector<CProMoEdgeView> outgoingEdges(2);
            for (auto& edgeView : outgoingEdges)
            {
                edgeView.SetRect(CRect(0, 0, 10, 10));
                edgeView.SetSource(&parent);
            }

            // Add multiple child blocks
            std::vector<CProMoBlockView> children(2);
            for (auto& child : children)
            {
                child.SetRect(100, 50, 250, 120);
                child.SetParentBlock(&parent);
            }

            // Act
            parent.AutoResize(); // triggers RecomputeIntersectionLinks recursively

            // Assert
            // All incoming edges updated
            for (auto& edgeView : incomingEdges)
            {
                Assert::AreEqual(123.0, edgeView.GetRight(), L"Incoming edge right updated");
                Assert::AreEqual(456.0, edgeView.GetBottom(), L"Incoming edge bottom updated");
            }

            // All outgoing edges updated
            for (auto& edgeView : outgoingEdges)
            {
                Assert::AreEqual(123.0, edgeView.GetLeft(), L"Outgoing edge left updated");
                Assert::AreEqual(456.0, edgeView.GetTop(), L"Outgoing edge top updated");
            }

            // All child blocks' edges updated via recursion
            for (auto& child : children)
            {
                // Children have no edges themselves, but RecomputeIntersectionLinks runs
                // We can at least assert the child rects remain unchanged
                Assert::AreEqual(100.0, child.GetLeft(), L"Child left unchanged");
                Assert::AreEqual(50.0, child.GetTop(), L"Child top unchanged");
                Assert::AreEqual(250.0, child.GetRight(), L"Child right unchanged");
                Assert::AreEqual(120.0, child.GetBottom(), L"Child bottom unchanged");
            }
        }
#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(GetDefaultGetString_WhenInvoked_ReturnsCorrectString)
        {
            CProMoBlockViewTestStub view;
            CString viewString;
            
            view.SetName(CString("View"));
            view.SetTitle(CString("My View"));
            view.GetModel()->SetName(CString("Model"));
            view.SetRect(100, 50, 250, 120);
            view.SetBkColor(RGB(255, 255, 0));
            view.SetBkMode(OPAQUE);
            view.SetLineColor(RGB(0, 255, 0));
            view.SetLineStyle(PS_DOT);
            view.SetLineWidth(1);
            view.SetFillColor(RGB(255, 0, 0));
            view.SetFillStyle(HS_DIAGCROSS);
            view.SetFillPattern(TRUE);
            view.SetLock(LOCK_FILLSTYLE);
            
            viewString = view.GetString();
            
            Assert::AreEqual(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model,524288,65535,2,65280,1,2,255,1,5;"), viewString);

        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoBlockViewTestStub viewStub;
            CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(viewStub.CreateFromString(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model,524288,65535,2,65280,1,2,255,1,5;")));

            Assert::AreEqual(CString("promo_block_view"), view->GetType());
            Assert::AreEqual(CString("View"), view->GetName());
            Assert::AreEqual(CString("My View"), view->GetTitle());
            Assert::AreEqual(100.0, view->GetLeft());
            Assert::AreEqual(50.0, view->GetTop());
            Assert::AreEqual(250.0, view->GetRight());
            Assert::AreEqual(120.0, view->GetBottom());
            Assert::AreEqual(RGB(255, 255, 0), view->GetBkColor());
            Assert::AreEqual(OPAQUE, (int)view->GetBkMode());
            Assert::AreEqual(RGB(0, 255, 0), view->GetLineColor());
            Assert::AreEqual(PS_DOT, (int)view->GetLineStyle());
            Assert::AreEqual(1, (int)view->GetLineWidth());
            Assert::AreEqual(RGB(255, 0, 0), view->GetFillColor());
            Assert::AreEqual(HS_DIAGCROSS, (int)view->GetFillStyle());
            Assert::IsTrue(view->IsFillPattern());
            Assert::AreEqual(LOCK_FILLSTYLE, (int)view->GetLock());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoBlockViewTestStub viewStub;
            CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(viewStub.CreateFromString(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model,524288,65535,2,65280,1,2,255,1,5,Extra1,Extra2;")));

            Assert::AreEqual(CString("promo_block_view"), view->GetType());
            Assert::AreEqual(CString("View"), view->GetName());
            Assert::AreEqual(CString("My View"), view->GetTitle());
            Assert::AreEqual(100.0, view->GetLeft());
            Assert::AreEqual(50.0, view->GetTop());
            Assert::AreEqual(250.0, view->GetRight());
            Assert::AreEqual(120.0, view->GetBottom());
            Assert::AreEqual(RGB(255, 255, 0), view->GetBkColor());
            Assert::AreEqual(OPAQUE, (int)view->GetBkMode());
            Assert::AreEqual(RGB(0, 255, 0), view->GetLineColor());
            Assert::AreEqual(PS_DOT, (int)view->GetLineStyle());
            Assert::AreEqual(1, (int)view->GetLineWidth());
            Assert::AreEqual(RGB(255, 0, 0), view->GetFillColor());
            Assert::AreEqual(HS_DIAGCROSS, (int)view->GetFillStyle());
            Assert::IsTrue(view->IsFillPattern());
            Assert::AreEqual(LOCK_FILLSTYLE, (int)view->GetLock());
        }

        TEST_METHOD(CreateFromString_WhenStringWithMissingParametersIsPassed_UseDefaultFormatting)
        {
            CProMoBlockViewTestStub viewStub;
            CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(viewStub.CreateFromString(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model,524288,65535;")));

            Assert::AreEqual(CString("promo_block_view"), view->GetType());
            Assert::AreEqual(CString("View"), view->GetName());
            Assert::AreEqual(CString("My View"), view->GetTitle());
            Assert::AreEqual(100.0, view->GetLeft());
            Assert::AreEqual(50.0, view->GetTop());
            Assert::AreEqual(250.0, view->GetRight());
            Assert::AreEqual(120.0, view->GetBottom());
            Assert::AreEqual(CLR_NONE, view->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view->GetBkMode());
            Assert::AreEqual(RGB(0, 0, 0), view->GetLineColor());
            Assert::AreEqual(PS_SOLID, (int)view->GetLineStyle());
            Assert::AreEqual(1, (int)view->GetLineWidth());
            Assert::AreEqual(RGB(255, 255, 255), view->GetFillColor());
            Assert::AreEqual(HS_CROSS, (int)view->GetFillStyle());
            Assert::IsFalse(view->IsFillPattern());
            Assert::AreEqual(0, (int)view->GetLock());

        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoBlockViewTestStub viewStub;
            CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(viewStub.CreateFromString(CString("wrong_type:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model;")));

            TestHelpers::PointerAssert::IsNull(view);
        }

        TEST_METHOD(GetNameFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoBlockView::GetNameFromString(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model;"));
            Assert::AreEqual(CString("View"), str1);
        }

        TEST_METHOD(GetModelFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoBlockView::GetModelFromString(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model;"));
            Assert::AreEqual(CString("Model"), str1);
        }

#pragma endregion

#pragma region ShapeTests

        TEST_METHOD(GetVertices_WhenShapeIsPolygon_GetVertices) {
            CProMoBlockViewTestStub block;
            block.SetShape(SHAPE_POLYGON);

            TestHelpers::PointerAssert::IsNotNull(block.GetVertices());
        }

        TEST_METHOD(GetVertices_WhenShapeIsNotPolygon_ReturnNull) {
            CProMoBlockViewTestStub block;
            block.SetShape(SHAPE_ELLIPSE);

            TestHelpers::PointerAssert::IsNull(block.GetVertices());
        }
        
        TEST_METHOD(AddVertex_WhenShapeIsPolygon_AddVertex) {
            CProMoBlockViewTestStub block;
            block.SetShape(SHAPE_POLYGON);
            BOOL result = block.AddVertex(CDoublePoint(0, 0));

            Assert::IsTrue(result);
            TestHelpers::PointerAssert::IsNotNull(block.GetVertices());
            Assert::AreEqual((INT_PTR)1, block.GetVertices()->GetSize());
        }

        TEST_METHOD(AddVertex_WhenVertexIsNotNormalized_DoesNotAddVertex) {
            CProMoBlockViewTestStub block;
            block.SetShape(SHAPE_POLYGON);
            BOOL result = block.AddVertex(CDoublePoint(2, 0));

            Assert::IsFalse(result);
        }

        TEST_METHOD(AddVertex_WhenShapeIsNotPolygon_DoesNotAddVertex) {
            CProMoBlockViewTestStub block;
            block.SetShape(SHAPE_ELLIPSE);
            BOOL result = block.AddVertex(CDoublePoint(0, 0));

            Assert::IsFalse(result);
        }


#pragma endregion

#pragma region GDISmokeTests

        TEST_METHOD(Draw_WhenCalledWithMemoryDC_DoesNotCrash)
        {
            // Arrange
            CProMoBlockViewTestStub parent;
            parent.SetLockedProportions(TRUE);
            parent.SetRect(0, 0, 200, 100);
            parent.SetTitle(CString("Parent with a very long long title"));
            parent.SetShape(SHAPE_RECTANGLE);
            
            CProMoBlockViewTestStub child;
            child.SetTarget(TRUE);
            child.SetRect(0, 0, 150, 80);
            child.SetTitle(CString("Child"));
            child.SetParentBlock(&parent);
            child.SetShape(SHAPE_ELLIPSE);

            CProMoBlockViewTestStub unrelated;
            unrelated.SetTarget(TRUE);
            unrelated.SetRect(300, 300, 350, 380);
            unrelated.SetTitle(CString("Unrelated"));
            unrelated.SetParentBlock(&parent);
            unrelated.SetShape(SHAPE_POLYGON);

            unrelated.AddVertex(CDoublePoint(0, 0));
            unrelated.AddVertex(CDoublePoint(0, 1)); 
            unrelated.AddVertex(CDoublePoint(1, 1));
            
            // Create memory DC
            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 200, 100);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 200, 100);

            // Act / Assert: should not crash
            parent.Draw(&memDC, rect);
            child.Draw(&memDC, rect);
            unrelated.Draw(&memDC, rect);
        }

        TEST_METHOD(ShowPopup_WhenCalledWithDesktopWindow_DoesNotCrash)
        {
            // Arrange
            CProMoBlockView block;
            block.SetRect(0, 0, 200, 100);

            CPoint point(50, 50);
            CWnd* parent = CWnd::FromHandle(::GetDesktopWindow());

            // Act / Assert
            block.ShowPopup(point, parent);
        }
#pragma endregion
    };
}
