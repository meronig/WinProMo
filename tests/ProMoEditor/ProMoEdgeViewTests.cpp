#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoEdgeView.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include <vector>
#include "../WinProMoTests.h"

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

namespace CProMoEdgeViewTests
{
    TEST_CLASS(CProMoEdgeViewTests)
    {

    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region ConstructionAndDefaults

        TEST_METHOD(Constructor_WhenCalled_InitializesDefaults)
        {
            CProMoEdgeView view;

            TestHelpers::PointerAssert::IsNotNull(view.GetModel());
        }

#pragma endregion

#pragma region CopyAndClone

        TEST_METHOD(Clone_WhenCalled_ReturnsIndependentCopy)
        {
            CProMoEdgeView view;
            
            std::unique_ptr<CDiagramEntity> clone(view.Clone());
            auto* clonedView = dynamic_cast<CProMoEdgeView*>(clone.get());

            TestHelpers::PointerAssert::IsNotNull(clonedView);
            TestHelpers::PointerAssert::AreNotEqual(dynamic_cast<CProMoEdgeView*>(&view), clonedView);
            TestHelpers::PointerAssert::AreNotEqual(view.GetModel(), clonedView->GetModel());
        }

#pragma endregion

#pragma region HitCode

        TEST_METHOD(GetHitCode_WhenCenterPassed_ReturnsCorrectConstant)
        {
            CProMoEdgeView view;

            int code = view.GetHitCode(CPoint(10, 10), CRect(0, 0, 20, 20));
            
            Assert::AreEqual(DEHT_CENTER, code);
        }

#pragma endregion

#pragma region Path

        TEST_METHOD(SetSource_WhenEdgeViewPassed_ConnectEdgeViews)
        {
            CProMoEdgeView view1;
            
            CProMoEdgeView view2;
            
            view2.SetSource(&view1);

            CProMoEdgeView view3;
            
            view3.SetSource(&view2);

            TestHelpers::PointerAssert::IsNull(view1.GetSource());
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view1.GetDestination()), &view2);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view2.GetSource()), &view1);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view2.GetDestination()), &view3);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view3.GetSource()), &view2);
            TestHelpers::PointerAssert::IsNull(view3.GetDestination());

            Assert::IsTrue(view1.IsFirstSegment());
            Assert::IsFalse(view2.IsFirstSegment());
            Assert::IsFalse(view3.IsFirstSegment());
            Assert::IsFalse(view1.IsLastSegment());
            Assert::IsFalse(view2.IsLastSegment());
            Assert::IsTrue(view3.IsLastSegment());
        }

        TEST_METHOD(SetSource_WhenBlockViewPassed_ConnectEdgeToBlock)
        {
            CProMoEdgeView edgeView;
            CProMoBlockViewTestStub blockView;

            edgeView.SetSource(&blockView);

            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockView*>(edgeView.GetSource()));
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockModel*>(edgeView.GetModel()->GetSource())->GetMainView());
            TestHelpers::PointerAssert::IsNotNull(blockView.GetModel()->GetOutgoingEdges());
            Assert::AreEqual((INT_PTR)1, blockView.GetModel()->GetOutgoingEdges()->GetSize());
            TestHelpers::PointerAssert::AreEqual(edgeView.GetModel(), dynamic_cast<CProMoEdgeModel*>(blockView.GetModel()->GetOutgoingEdges()->GetAt(0)));
            
            Assert::IsTrue(edgeView.IsFirstSegment());
            Assert::IsTrue(edgeView.IsLastSegment());
        }

        TEST_METHOD(SetSource_WhenNullIsPassed_DisconnectEdgeViews)
        {
            CProMoEdgeView view1;
            
            CProMoEdgeView view2;
            
            view2.SetSource(&view1);

            CProMoEdgeView view3;
            
            view3.SetSource(&view2);

            view2.SetSource(NULL);
            view3.SetSource(NULL);

            TestHelpers::PointerAssert::IsNull(view1.GetSource());
            TestHelpers::PointerAssert::IsNull(view2.GetSource());
            TestHelpers::PointerAssert::IsNull(view3.GetSource());
            TestHelpers::PointerAssert::IsNull(view1.GetDestination());
            TestHelpers::PointerAssert::IsNull(view2.GetDestination());
            TestHelpers::PointerAssert::IsNull(view3.GetDestination());

            Assert::IsTrue(view1.IsFirstSegment());
            Assert::IsTrue(view2.IsFirstSegment());
            Assert::IsTrue(view3.IsFirstSegment());
            Assert::IsTrue(view1.IsLastSegment());
            Assert::IsTrue(view2.IsLastSegment());
            Assert::IsTrue(view3.IsLastSegment());

        }

        TEST_METHOD(SetDestination_WhenEdgeViewPassed_ConnectEdgeViews)
        {
            CProMoEdgeView view1;

            CProMoEdgeView view2;

            view1.SetDestination(&view2);

            CProMoEdgeView view3;

            view2.SetDestination(&view3);

            TestHelpers::PointerAssert::IsNull(view1.GetSource());
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view1.GetDestination()), &view2);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view2.GetSource()), &view1);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view2.GetDestination()), &view3);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view3.GetSource()), &view2);
            TestHelpers::PointerAssert::IsNull(view3.GetDestination());

            Assert::IsTrue(view1.IsFirstSegment());
            Assert::IsFalse(view2.IsFirstSegment());
            Assert::IsFalse(view3.IsFirstSegment());
            Assert::IsFalse(view1.IsLastSegment());
            Assert::IsFalse(view2.IsLastSegment());
            Assert::IsTrue(view3.IsLastSegment());
        }

        TEST_METHOD(SetDestination_WhenBlockViewPassed_ConnectEdgeToBlock)
        {
            CProMoEdgeView edgeView;
            CProMoBlockViewTestStub blockView;

            edgeView.SetDestination(&blockView);

            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockView*>(edgeView.GetDestination()));
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockModel*>(edgeView.GetModel()->GetDestination())->GetMainView());
            TestHelpers::PointerAssert::IsNotNull(blockView.GetModel()->GetIncomingEdges());
            Assert::AreEqual((INT_PTR)1, blockView.GetModel()->GetIncomingEdges()->GetSize());
            TestHelpers::PointerAssert::AreEqual(edgeView.GetModel(), dynamic_cast<CProMoEdgeModel*>(blockView.GetModel()->GetIncomingEdges()->GetAt(0)));

            Assert::IsTrue(edgeView.IsFirstSegment());
            Assert::IsTrue(edgeView.IsLastSegment());
        }

        TEST_METHOD(SetDestination_WhenNullIsPassed_DisconnectEdgeViews)
        {
            CProMoEdgeView view1;

            CProMoEdgeView view2;

            view1.SetDestination(&view2);

            CProMoEdgeView view3;

            view2.SetDestination(&view3);

            view1.SetDestination(NULL);
            view2.SetDestination(NULL);

            TestHelpers::PointerAssert::IsNull(view1.GetSource());
            TestHelpers::PointerAssert::IsNull(view2.GetSource());
            TestHelpers::PointerAssert::IsNull(view3.GetSource());
            TestHelpers::PointerAssert::IsNull(view1.GetDestination());
            TestHelpers::PointerAssert::IsNull(view2.GetDestination());
            TestHelpers::PointerAssert::IsNull(view3.GetDestination());

            Assert::IsTrue(view1.IsFirstSegment());
            Assert::IsTrue(view2.IsFirstSegment());
            Assert::IsTrue(view3.IsFirstSegment());
            Assert::IsTrue(view1.IsLastSegment());
            Assert::IsTrue(view2.IsLastSegment());
            Assert::IsTrue(view3.IsLastSegment());
        }

        TEST_METHOD(Split_WhenInvoked_KeepEdgesConnected)
        {
            CProMoEdgeView view;

            view.SetRect(CRect(100, 50, 250, 120));
            
            CProMoEdgeView* splitView = view.Split();

            TestHelpers::PointerAssert::AreNotEqual(&view,splitView);
            TestHelpers::PointerAssert::AreEqual(view.GetModel(), splitView->GetModel());
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view.GetDestination()), splitView);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(splitView->GetSource()), &view);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(view.GetDestination()), splitView);
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoEdgeView*>(splitView->GetSource()), &view);


            Assert::IsTrue(view.IsFirstSegment());
            Assert::IsFalse(splitView->IsFirstSegment());
            Assert::IsFalse(view.IsLastSegment());
            Assert::IsTrue(splitView->IsLastSegment());
        }

        TEST_METHOD(Split_WhenInvoked_KeepEdgePositionContinuous)
        {
            CProMoEdgeView view;

            view.SetRect(CRect(100, 50, 250, 120));
            
            CProMoEdgeView* splitView = view.Split();

            Assert::AreEqual(CRect(100, 50, 175, 85), view.GetRect());
            Assert::AreEqual(CRect(175, 85, 250, 120), splitView->GetRect());

        }

        TEST_METHOD(Split_WhenInvoked_ClearAttributes)
        {
            CProMoEdgeView view;

            view.SetRect(CRect(100, 50, 250, 120));
            view.SetName("View");
            view.SetTitle("My View");
            view.Select(TRUE);

            CProMoEdgeView* splitView = view.Split();

            Assert::AreNotEqual(CString("View"), splitView->GetName());
            Assert::AreNotEqual(CString("My View"), splitView->GetTitle());
            Assert::IsFalse(splitView->IsSelected());

        }


#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(GetDefaultGetString_WhenInvoked_ReturnsCorrectString)
        {
            CProMoEdgeView view1;
            CString viewString1;

            view1.SetName(CString("View1"));
            view1.SetTitle(CString("My View"));
            view1.GetModel()->SetName(CString("Model"));
            view1.SetRect(CRect(100, 50, 250, 120));

            CProMoEdgeView view2;
            CString viewString2;

            view2.SetName(CString("View2"));
            view2.SetRect(CRect(250, 120, 200, 150));

            view2.SetSource(&view1);

            CProMoEdgeView view3;
            CString viewString3;

            view3.SetName(CString("View3"));
            view3.SetTitle(CString("My View"));
            view3.SetRect(CRect(200, 150, 200, 100));

            view3.SetSource(&view2);

            viewString1 = view1.GetString();
            viewString2 = view2.GetString();
            viewString3 = view3.GetString();

            Assert::AreEqual(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model,,View2;"), viewString1);
            Assert::AreEqual(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model,View1,View3;"), viewString2);
            Assert::AreEqual(CString("promo_edge_view:View3,200.000000,150.000000,200.000000,100.000000,My View,0,Model,View2,;"), viewString3);

        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoEdgeView viewStub;
            CProMoEdgeView* view1 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model,,View2;")));
            CProMoEdgeView* view2 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model,View1,View3;")));
            CProMoEdgeView* view3 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View3,200.000000,150.000000,200.000000,100.000000,My View,0,Model,View2,;")));

            Assert::AreEqual(CString("promo_edge_view"), view1->GetType());
            Assert::AreEqual(CString("View1"), view1->GetName());
            Assert::AreEqual(CString("My View"), view1->GetTitle());
            Assert::AreEqual(100.0, view1->GetLeft());
            Assert::AreEqual(50.0, view1->GetTop());
            Assert::AreEqual(250.0, view1->GetRight());
            Assert::AreEqual(120.0, view1->GetBottom());

            Assert::AreEqual(CString("promo_edge_view"), view2->GetType());
            Assert::AreEqual(CString("View2"), view2->GetName());
            Assert::AreEqual(CString(""), view2->GetTitle());
            Assert::AreEqual(250.0, view2->GetLeft());
            Assert::AreEqual(120.0, view2->GetTop());
            Assert::AreEqual(200.0, view2->GetRight());
            Assert::AreEqual(150.0, view2->GetBottom());

            Assert::AreEqual(CString("promo_edge_view"), view3->GetType());
            Assert::AreEqual(CString("View3"), view3->GetName());
            Assert::AreEqual(CString("My View"), view3->GetTitle());
            Assert::AreEqual(200.0, view3->GetLeft());
            Assert::AreEqual(150.0, view3->GetTop());
            Assert::AreEqual(200.0, view3->GetRight());
            Assert::AreEqual(100.0, view3->GetBottom());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoEdgeView viewStub;
            CProMoEdgeView* view1 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model,,View2,Extra1,Extra2;")));
            CProMoEdgeView* view2 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model,View1,View3,Extra1,Extra2;")));
            CProMoEdgeView* view3 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View3,200.000000,150.000000,200.000000,100.000000,My View,0,Model,View2,,Extra1,Extra2;")));

            Assert::AreEqual(CString("promo_edge_view"), view1->GetType());
            Assert::AreEqual(CString("View1"), view1->GetName());
            Assert::AreEqual(CString("My View"), view1->GetTitle());
            Assert::AreEqual(100.0, view1->GetLeft());
            Assert::AreEqual(50.0, view1->GetTop());
            Assert::AreEqual(250.0, view1->GetRight());
            Assert::AreEqual(120.0, view1->GetBottom());

            Assert::AreEqual(CString("promo_edge_view"), view2->GetType());
            Assert::AreEqual(CString("View2"), view2->GetName());
            Assert::AreEqual(CString(""), view2->GetTitle());
            Assert::AreEqual(250.0, view2->GetLeft());
            Assert::AreEqual(120.0, view2->GetTop());
            Assert::AreEqual(200.0, view2->GetRight());
            Assert::AreEqual(150.0, view2->GetBottom());

            Assert::AreEqual(CString("promo_edge_view"), view3->GetType());
            Assert::AreEqual(CString("View3"), view3->GetName());
            Assert::AreEqual(CString("My View"), view3->GetTitle());
            Assert::AreEqual(200.0, view3->GetLeft());
            Assert::AreEqual(150.0, view3->GetTop());
            Assert::AreEqual(200.0, view3->GetRight());
            Assert::AreEqual(100.0, view3->GetBottom());
        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoEdgeView viewStub;
            CProMoEdgeView* view = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("wrong_type:View,100.000000,50.000000,250.000000,120.000000,My View,0,Model;")));

            TestHelpers::PointerAssert::IsNull(view);
        }

        TEST_METHOD(GetNameFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoEdgeView::GetNameFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model1,,View2;"));
            CString str2 = CProMoEdgeView::GetNameFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model2,View1,View3;"));
            Assert::AreEqual(CString("View1"), str1);
            Assert::AreEqual(CString("View2"), str2);
        }

        TEST_METHOD(GetModelFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoEdgeView::GetModelFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model1,,View2;"));
            CString str2 = CProMoEdgeView::GetModelFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model2,View1,View3;"));
            Assert::AreEqual(CString("Model1"), str1);
            Assert::AreEqual(CString("Model2"), str2);
        }

        TEST_METHOD(GetSourceFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoEdgeView::GetSourceFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model1,,View2;"));
            CString str2 = CProMoEdgeView::GetSourceFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model2,View1,View3;"));
            Assert::AreEqual(CString(""), str1);
            Assert::AreEqual(CString("View1"), str2);
        }

        TEST_METHOD(GetDestinationFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoEdgeView::GetDestinationFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model1,View2,;"));
            CString str2 = CProMoEdgeView::GetDestinationFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model2,View1,View3;"));
            Assert::AreEqual(CString(""), str1);
            Assert::AreEqual(CString("View3"), str2);
        }

#pragma endregion

#pragma region GDISmokeTests

        TEST_METHOD(Draw_WhenCalledWithMemoryDC_DoesNotCrash)
        {
            // Arrange
            CProMoEdgeView view1;
            CString viewString1;

            view1.SetTitle(CString("My View"));
            view1.SetRect(CRect(100, 50, 250, 120));

            CProMoEdgeView view2;
            CString viewString2;

            view2.SetRect(CRect(250, 120, 200, 150));

            view2.SetSource(&view1);

            CProMoEdgeView view3;
            CString viewString3;

            view3.SetTitle(CString("My View")); 
            view3.SetRect(CRect(200, 150, 200, 120));

            view3.SetSource(&view2);

            // Create memory DC
            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 200, 100);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 200, 100);

            // Act / Assert: should not crash
            view1.Draw(&memDC, rect);
            view2.Draw(&memDC, rect);
            view3.Draw(&memDC, rect);
        }

        TEST_METHOD(ShowPopup_WhenCalledWithDesktopWindow_DoesNotCrash)
        {
            // Arrange
            CProMoEdgeView view;
            
            view.SetRect(CRect(100, 50, 250, 120));

            CPoint point(50, 50);
            CWnd* parent = CWnd::FromHandle(::GetDesktopWindow());

            // Act / Assert
            view.ShowPopup(point, parent);
        }

        TEST_METHOD(DrawSelectionMarkers_WhenCalledWithMemoryDC_DoesNotCrash)
        {
            // Arrange
            CProMoEdgeView view;

            view.SetRect(CRect(100, 50, 250, 120));

            // Create memory DC
            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 200, 100);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 10, 10);

            // Act / Assert
            view.DrawSelectionMarkers(&memDC, rect);
        }

        TEST_METHOD(GetCursor_WhenCalledWithConstant_DoesNotCrash)
        {
            // Arrange
            CProMoEdgeView view;

            view.SetRect(CRect(100, 50, 250, 120));

            // Act / Assert
            view.GetCursor(DEHT_CENTER);
        }

#pragma endregion
    };
}
