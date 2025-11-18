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

#pragma region FormattingTests
        TEST_METHOD(SetFontName_ValidName_SetsFontName)
        {
            // Arrange
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
            unsigned int alignment = DT_LEFT | DT_BOTTOM;

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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
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
            CProMoEdgeView view;
            CObArray labels;
            view.GetEdgeModel()->RecreateLabels(labels);
            unsigned int style = PS_DASHDOT;

            BOOL result = view.SetLineStyle(style);

            Assert::IsTrue(result);
            Assert::AreEqual(style, view.GetLineStyle());

            view.SetLock(LOCK_LINESTYLE);

            result = view.SetLineStyle(PS_DOT);

            Assert::IsFalse(result);
            Assert::AreEqual(style, view.GetLineStyle());
        }

#pragma endregion

#pragma region LayoutTests
        
        TEST_METHOD(SetVisible_False_HidesView)
        {
            CProMoEdgeView view;
            
            view.SetVisible(FALSE);

            Assert::IsFalse(view.IsVisible());
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

        TEST_METHOD(Clone_NewObject_PropertiesCopied)
        {
            CProMoEdgeView original;
            original.SetRect(100, 50, 250, 120);
            original.SetBkColor(RGB(0, 255, 0));
            original.SetBkMode(OPAQUE);
            original.SetLineColor(RGB(0, 0, 255));
            original.SetLineWidth(4);
            original.SetLineStyle(PS_DASH);

            // Act
            std::unique_ptr<CDiagramEntity> clone(original.Clone());

            // Assert
            CProMoEdgeView* clonedEdge = dynamic_cast<CProMoEdgeView*>(clone.get());
            Assert::IsNotNull(clonedEdge);

            Assert::AreEqual(original.GetLeft(), clonedEdge->GetLeft());
            Assert::AreEqual(original.GetTop(), clonedEdge->GetTop());
            Assert::AreEqual(original.GetRight(), clonedEdge->GetRight());
            Assert::AreEqual(original.GetBottom(), clonedEdge->GetBottom());
            Assert::AreEqual(original.GetBkColor(), clonedEdge->GetBkColor());
            Assert::AreEqual(original.GetBkMode(), clonedEdge->GetBkMode());
            Assert::AreEqual(original.GetLineColor(), clonedEdge->GetLineColor());
            Assert::AreEqual(original.GetLineWidth(), clonedEdge->GetLineWidth());
            Assert::AreEqual(original.GetLineStyle(), clonedEdge->GetLineStyle());
        }

#pragma endregion

#pragma region HitCode

        TEST_METHOD(GetHitCode_WhenCenterPassed_ReturnsCorrectConstant)
        {
            CProMoEdgeView view;

            int code = view.GetHitCode(CPoint(10, 10), CRect(0, 0, 20, 20));
            
            Assert::AreEqual(DEHT_CENTER, code);
        }

        TEST_METHOD(GetHitCode_WhenInside_ReturnsCorrectConstant)
        {
            CProMoEdgeView view;

            int code = view.GetHitCode(CPoint(15, 15), CRect(0, 0, 20, 20));

            Assert::AreEqual(DEHT_BODY, code);
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

            CObArray edges;
            blockView.GetBlockModel()->GetOutgoingEdges(edges);

            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockView*>(edgeView.GetSource()));
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockModel*>(edgeView.GetEdgeModel()->GetSource())->GetMainView());
            Assert::AreEqual((INT_PTR)1, edges.GetSize());
            TestHelpers::PointerAssert::AreEqual(edgeView.GetEdgeModel(), dynamic_cast<CProMoEdgeModel*>(edges.GetAt(0)));
            
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

            CObArray edges;
            blockView.GetBlockModel()->GetIncomingEdges(edges);

            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockView*>(edgeView.GetDestination()));
            TestHelpers::PointerAssert::AreEqual(dynamic_cast<CProMoBlockView*>(&blockView), dynamic_cast<CProMoBlockModel*>(edgeView.GetEdgeModel()->GetDestination())->GetMainView());
            Assert::AreEqual((INT_PTR)1, edges.GetSize());
            TestHelpers::PointerAssert::AreEqual(edgeView.GetEdgeModel(), dynamic_cast<CProMoEdgeModel*>(edges.GetAt(0)));

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
            view1.SetBkColor(RGB(255, 255, 0));
            view1.SetBkMode(OPAQUE);
            view1.SetLineColor(RGB(0, 255, 0));
            view1.SetLineStyle(PS_DOT);
            view1.SetLineWidth(1);

            CProMoEdgeView view2;
            CString viewString2;

            view2.SetName(CString("View2"));
            view2.SetRect(CRect(250, 120, 200, 150));
            view2.SetLineColor(RGB(0, 0, 255));
            view2.SetLineStyle(PS_DASH);
            view2.SetLineWidth(1);

            view2.SetSource(&view1);

            CProMoEdgeView view3;
            CString viewString3;

            view3.SetName(CString("View3"));
            view3.SetTitle(CString("My View"));
            view3.SetRect(CRect(200, 150, 200, 100));
            view3.SetLineColor(RGB(255, 0, 0));
            view3.SetLineStyle(PS_SOLID);
            view3.SetLineWidth(4);
            view3.SetLock(LOCK_LINESTYLE);

            view3.SetSource(&view2);

            viewString1 = view1.GetString();
            viewString2 = view2.GetString();
            viewString3 = view3.GetString();

            Assert::AreEqual(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model,,View2,0,65535,2,65280,1,2;"), viewString1);
            Assert::AreEqual(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model,View1,View3,0,-1,1,16711680,1,1;"), viewString2);
            Assert::AreEqual(CString("promo_edge_view:View3,200.000000,150.000000,200.000000,100.000000,My View,0,Model,View2,,131072,-1,1,255,4,0;"), viewString3);

        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoEdgeView viewStub;
            CProMoEdgeView* view1 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model,,View2,0,65535,2,65280,1,2;")));
            CProMoEdgeView* view2 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model,View1,View3,0,-1,1,16711680,1,1;")));
            CProMoEdgeView* view3 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View3,200.000000,150.000000,200.000000,100.000000,My View,0,Model,View2,,131072,-1,1,255,4,0;")));

            Assert::AreEqual(CString("promo_edge_view"), view1->GetType());
            Assert::AreEqual(CString("View1"), view1->GetName());
            Assert::AreEqual(CString("My View"), view1->GetTitle());
            Assert::AreEqual(100.0, view1->GetLeft());
            Assert::AreEqual(50.0, view1->GetTop());
            Assert::AreEqual(250.0, view1->GetRight());
            Assert::AreEqual(120.0, view1->GetBottom());
            Assert::AreEqual(RGB(255, 255, 0), view1->GetBkColor());
            Assert::AreEqual(OPAQUE, (int)view1->GetBkMode());
            Assert::AreEqual(RGB(0, 255, 0), view1->GetLineColor());
            Assert::AreEqual(PS_DOT, (int)view1->GetLineStyle());
            Assert::AreEqual(1, (int)view1->GetLineWidth());
            Assert::AreEqual(0, (int)view1->GetLock());

            Assert::AreEqual(CString("promo_edge_view"), view2->GetType());
            Assert::AreEqual(CString("View2"), view2->GetName());
            Assert::AreEqual(CString(""), view2->GetTitle());
            Assert::AreEqual(250.0, view2->GetLeft());
            Assert::AreEqual(120.0, view2->GetTop());
            Assert::AreEqual(200.0, view2->GetRight());
            Assert::AreEqual(150.0, view2->GetBottom());
            Assert::AreEqual(CLR_NONE, view2->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view2->GetBkMode());
            Assert::AreEqual(RGB(0, 0, 255), view2->GetLineColor());
            Assert::AreEqual(PS_DASH, (int)view2->GetLineStyle());
            Assert::AreEqual(1, (int)view2->GetLineWidth());
            Assert::AreEqual(0, (int)view2->GetLock());

            Assert::AreEqual(CString("promo_edge_view"), view3->GetType());
            Assert::AreEqual(CString("View3"), view3->GetName());
            Assert::AreEqual(CString("My View"), view3->GetTitle());
            Assert::AreEqual(200.0, view3->GetLeft());
            Assert::AreEqual(150.0, view3->GetTop());
            Assert::AreEqual(200.0, view3->GetRight());
            Assert::AreEqual(100.0, view3->GetBottom());
            Assert::AreEqual(CLR_NONE, view3->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view3->GetBkMode());
            Assert::AreEqual(RGB(255, 0, 0), view3->GetLineColor());
            Assert::AreEqual(PS_SOLID, (int)view3->GetLineStyle());
            Assert::AreEqual(4, (int)view3->GetLineWidth());
            Assert::AreEqual(LOCK_LINESTYLE, (int)view3->GetLock());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoEdgeView viewStub;
            CProMoEdgeView* view1 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model,,View2,0,65535,2,65280,1,2,Extra1,Extra2;")));
            CProMoEdgeView* view2 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model,View1,View3,0,-1,1,16711680,1,1,Extra1,Extra2;")));
            CProMoEdgeView* view3 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View3,200.000000,150.000000,200.000000,100.000000,My View,0,Model,View2,,131072,-1,1,255,4,0,Extra1,Extra2;")));

            Assert::AreEqual(CString("promo_edge_view"), view1->GetType());
            Assert::AreEqual(CString("View1"), view1->GetName());
            Assert::AreEqual(CString("My View"), view1->GetTitle());
            Assert::AreEqual(100.0, view1->GetLeft());
            Assert::AreEqual(50.0, view1->GetTop());
            Assert::AreEqual(250.0, view1->GetRight());
            Assert::AreEqual(120.0, view1->GetBottom());
            Assert::AreEqual(RGB(255, 255, 0), view1->GetBkColor());
            Assert::AreEqual(OPAQUE, (int)view1->GetBkMode());
            Assert::AreEqual(RGB(0, 255, 0), view1->GetLineColor());
            Assert::AreEqual(PS_DOT, (int)view1->GetLineStyle());
            Assert::AreEqual(1, (int)view1->GetLineWidth());
            Assert::AreEqual(0, (int)view1->GetLock());

            Assert::AreEqual(CString("promo_edge_view"), view2->GetType());
            Assert::AreEqual(CString("View2"), view2->GetName());
            Assert::AreEqual(CString(""), view2->GetTitle());
            Assert::AreEqual(250.0, view2->GetLeft());
            Assert::AreEqual(120.0, view2->GetTop());
            Assert::AreEqual(200.0, view2->GetRight());
            Assert::AreEqual(150.0, view2->GetBottom());
            Assert::AreEqual(CLR_NONE, view2->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view2->GetBkMode());
            Assert::AreEqual(RGB(0, 0, 255), view2->GetLineColor());
            Assert::AreEqual(PS_DASH, (int)view2->GetLineStyle());
            Assert::AreEqual(1, (int)view2->GetLineWidth());
            Assert::AreEqual(0, (int)view2->GetLock());

            Assert::AreEqual(CString("promo_edge_view"), view3->GetType());
            Assert::AreEqual(CString("View3"), view3->GetName());
            Assert::AreEqual(CString("My View"), view3->GetTitle());
            Assert::AreEqual(200.0, view3->GetLeft());
            Assert::AreEqual(150.0, view3->GetTop());
            Assert::AreEqual(200.0, view3->GetRight());
            Assert::AreEqual(100.0, view3->GetBottom());
            Assert::AreEqual(CLR_NONE, view3->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view3->GetBkMode());
            Assert::AreEqual(RGB(255, 0, 0), view3->GetLineColor());
            Assert::AreEqual(PS_SOLID, (int)view3->GetLineStyle());
            Assert::AreEqual(4, (int)view3->GetLineWidth());
            Assert::AreEqual(LOCK_LINESTYLE, (int)view3->GetLock());

        }

        TEST_METHOD(CreateFromString_WhenStringWithMissingParametersIsPassed_UseDefaultFormatting)
        {
            CProMoEdgeView viewStub;
            CProMoEdgeView* view1 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View1,100.000000,50.000000,250.000000,120.000000,My View,0,Model,,View2,0,65535,2;")));
            CProMoEdgeView* view2 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View2,250.000000,120.000000,200.000000,150.000000,,0,Model,View1,View3,0,-1,1;")));
            CProMoEdgeView* view3 = dynamic_cast<CProMoEdgeView*>(viewStub.CreateFromString(CString("promo_edge_view:View3,200.000000,150.000000,200.000000,100.000000,My View,0,Model,View2,,131072,-1,1;")));

            Assert::AreEqual(CString("promo_edge_view"), view1->GetType());
            Assert::AreEqual(CString("View1"), view1->GetName());
            Assert::AreEqual(CString("My View"), view1->GetTitle());
            Assert::AreEqual(100.0, view1->GetLeft());
            Assert::AreEqual(50.0, view1->GetTop());
            Assert::AreEqual(250.0, view1->GetRight());
            Assert::AreEqual(120.0, view1->GetBottom());
            Assert::AreEqual(CLR_NONE, view1->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view1->GetBkMode());
            Assert::AreEqual(RGB(0, 0, 0), view1->GetLineColor());
            Assert::AreEqual(PS_SOLID, (int)view1->GetLineStyle());
            Assert::AreEqual(1, (int)view1->GetLineWidth());
            Assert::AreEqual(0, (int)view1->GetLock());

            Assert::AreEqual(CString("promo_edge_view"), view2->GetType());
            Assert::AreEqual(CString("View2"), view2->GetName());
            Assert::AreEqual(CString(""), view2->GetTitle());
            Assert::AreEqual(250.0, view2->GetLeft());
            Assert::AreEqual(120.0, view2->GetTop());
            Assert::AreEqual(200.0, view2->GetRight());
            Assert::AreEqual(150.0, view2->GetBottom());
            Assert::AreEqual(CLR_NONE, view2->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view2->GetBkMode());
            Assert::AreEqual(RGB(0, 0, 0), view2->GetLineColor());
            Assert::AreEqual(PS_SOLID, (int)view2->GetLineStyle());
            Assert::AreEqual(1, (int)view2->GetLineWidth());
            Assert::AreEqual(0, (int)view2->GetLock());

            Assert::AreEqual(CString("promo_edge_view"), view3->GetType());
            Assert::AreEqual(CString("View3"), view3->GetName());
            Assert::AreEqual(CString("My View"), view3->GetTitle());
            Assert::AreEqual(200.0, view3->GetLeft());
            Assert::AreEqual(150.0, view3->GetTop());
            Assert::AreEqual(200.0, view3->GetRight());
            Assert::AreEqual(100.0, view3->GetBottom());
            Assert::AreEqual(CLR_NONE, view3->GetBkColor());
            Assert::AreEqual(TRANSPARENT, (int)view3->GetBkMode());
            Assert::AreEqual(RGB(0, 0, 0), view3->GetLineColor());
            Assert::AreEqual(PS_SOLID, (int)view3->GetLineStyle());
            Assert::AreEqual(1, (int)view3->GetLineWidth());
            Assert::AreEqual(0, (int)view3->GetLock());

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
            view.GetCursor(DEHT_TOPLEFT);
        }

#pragma endregion
    };
}
