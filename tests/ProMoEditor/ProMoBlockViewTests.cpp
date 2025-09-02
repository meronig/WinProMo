#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoBlockView.h"
#include "../../src/ProMoEditor/ProMoEdgeView.h"
#include <vector>

class CProMoBlockViewTestStub : public CProMoBlockView
{
public:
    CPoint fixedIntersection = CPoint(123, 456);

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

#pragma region ConstructionAndDefaults

        TEST_METHOD(Constructor_WhenCalled_InitializesDefaults)
        {
            CProMoBlockViewTestStub view;

            Assert::IsFalse(view.IsTarget());
            Assert::IsFalse(view.HasLockedProportions());
            TestHelpers::PointerAssert::IsNotNull(view.GetModel());
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

#pragma region ModelLinking

        TEST_METHOD(SetModel_WhenAssigned_GetModelReturnsSamePointer)
        {
            CProMoBlockViewTestStub* view = new CProMoBlockViewTestStub();
            CProMoBlockModel* model = new CProMoBlockModel();

            view->SetModel(model);

            TestHelpers::PointerAssert::AreEqual(model, view->GetModel());
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
            TestHelpers::PointerAssert::AreNotEqual(dynamic_cast<CProMoBlockView*>(&view), clonedView);
            TestHelpers::PointerAssert::AreNotEqual(view.GetModel(), clonedView->GetModel());
            Assert::AreNotEqual(view.IsTarget(), clonedView->IsTarget());
            Assert::AreEqual(view.HasLockedProportions(), clonedView->HasLockedProportions());
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

            child.GetModel()->SetParentBlock(parent.GetModel());

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

            child.GetModel()->SetParentBlock(parent.GetModel());

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

            child.GetModel()->SetParentBlock(parent.GetModel());

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

            child.GetModel()->SetParentBlock(parent.GetModel());

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

            parent.GetModel()->SetParentBlock(grandParent.GetModel());

            CProMoBlockViewTestStub child;
            child.SetRect(10, 10, 200, 50); // right protrudes

            child.GetModel()->SetParentBlock(parent.GetModel());

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
            parent.GetModel()->LinkIncomingEdge(inEdgeView.GetModel());
            
            // Add outgoing edge
            CProMoEdgeView outEdgeView;
            outEdgeView.SetRect(CRect(0, 0, 10, 10));
            parent.GetModel()->LinkOutgoingEdge(outEdgeView.GetModel());

            // Add a child block
            CProMoBlockView child;
            child.SetRect(150, 50, 250, 120);
            child.GetModel()->SetParentBlock(parent.GetModel());
            
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
                parent.GetModel()->LinkIncomingEdge(edgeView.GetModel());
            }

            // Add multiple outgoing edges
            std::vector<CProMoEdgeView> outgoingEdges(2);
            for (auto& edgeView : outgoingEdges)
            {
                edgeView.SetRect(CRect(0, 0, 10, 10));
                parent.GetModel()->LinkOutgoingEdge(edgeView.GetModel());
            }

            // Add multiple child blocks
            std::vector<CProMoBlockView> children(2);
            for (auto& child : children)
            {
                child.SetRect(100, 50, 250, 120);
                child.GetModel()->SetParentBlock(parent.GetModel());
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
            
            viewString = view.GetString();
            
            Assert::AreEqual(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model;"), viewString);

        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoBlockViewTestStub viewStub;
            CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(viewStub.CreateFromString(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model;")));

            Assert::AreEqual(CString("promo_block_view"), view->GetType());
            Assert::AreEqual(CString("View"), view->GetName());
            Assert::AreEqual(CString("My View"), view->GetTitle());
            Assert::AreEqual(100.0, view->GetLeft());
            Assert::AreEqual(50.0, view->GetTop());
            Assert::AreEqual(250.0, view->GetRight());
            Assert::AreEqual(120.0, view->GetBottom());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoBlockViewTestStub viewStub;
            CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(viewStub.CreateFromString(CString("promo_block_view:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model,Extra1,Extra2;")));

            Assert::AreEqual(CString("promo_block_view"), view->GetType());
            Assert::AreEqual(CString("View"), view->GetName());
            Assert::AreEqual(CString("My View"), view->GetTitle());
            Assert::AreEqual(100.0, view->GetLeft());
            Assert::AreEqual(50.0, view->GetTop());
            Assert::AreEqual(250.0, view->GetRight());
            Assert::AreEqual(120.0, view->GetBottom());
        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoBlockViewTestStub viewStub;
            CProMoBlockView* view = dynamic_cast<CProMoBlockView*>(viewStub.CreateFromString(CString("wrong_type:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model;")));

            TestHelpers::PointerAssert::IsNull(view);
        }

#pragma region GDISmokeTests

        TEST_METHOD(Draw_WhenCalledWithMemoryDC_DoesNotCrash)
        {
            // Arrange
            CProMoBlockView block;
            block.SetRect(0, 0, 200, 100);

            // Create memory DC
            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 200, 100);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 200, 100);

            // Act / Assert: should not crash
            block.Draw(&memDC, rect);
        }

        TEST_METHOD(Highlight_WhenCalledWithMemoryDC_DoesNotCrash)
        {
            // Arrange
            CProMoBlockView block;
            block.SetRect(0, 0, 200, 100);

            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 200, 100);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 200, 100);

            // Act / Assert
            block.Highlight(&memDC, rect);
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
