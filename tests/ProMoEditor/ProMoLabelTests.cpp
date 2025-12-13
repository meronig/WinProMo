#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoLabel.h"
#include "../WinProMoTests.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoLabelTests
{
    TEST_CLASS(ProMoLabelTests)
    {
    public:

        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region ConstructorTests
        TEST_METHOD(Constructor_DefaultValues_AreInitialized)
        {
            // Arrange
            CProMoLabel label;

            // Assert
            Assert::AreEqual(CString("Courier New"), label.GetFontName());
            Assert::AreEqual((unsigned int)12, label.GetFontSize());
            Assert::AreEqual((unsigned int)FW_NORMAL, label.GetFontWeight());
            Assert::IsFalse(label.IsFontItalic());
            Assert::IsFalse(label.IsFontUnderline());
            Assert::IsFalse(label.IsFontStrikeOut());
            Assert::AreEqual(RGB(0, 0, 0), label.GetTextColor());
            Assert::AreEqual(CLR_NONE, label.GetBkColor());
            Assert::AreEqual((unsigned int)TRANSPARENT, label.GetBkMode());
            Assert::AreEqual((unsigned int)DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER, label.GetTextAlignment());
            Assert::AreEqual((unsigned int)DEHT_CENTER, label.GetViewAnchorPoint());
            Assert::AreEqual((unsigned int)DEHT_CENTER, label.GetLabelAnchorPoint());
            Assert::AreEqual((unsigned int)VIEW_FIRST, label.GetAnchorView());
            double lMargin, rMargin, tMargin, bMargin;
            label.GetMargins(lMargin, tMargin, rMargin, bMargin);
            Assert::AreEqual(0.0, lMargin);
            Assert::AreEqual(0.0, tMargin);
            Assert::AreEqual(0.0, rMargin);
            Assert::AreEqual(0.0, bMargin);
            
            Assert::IsFalse(label.HasFitTitle());
            Assert::IsFalse(label.HasFitView());
            Assert::IsTrue(label.IsVisible());
            Assert::AreEqual((unsigned int)0, label.GetLock());
        }

#pragma endregion

#pragma region FormattingTests
        TEST_METHOD(SetFontName_ValidName_SetsFontName)
        {
            // Arrange
            CProMoLabel label;
            CString expected = _T("Arial");

            // Act
            BOOL result = label.SetFontName(expected);

            // Assert
            Assert::IsTrue(result);
            Assert::AreEqual(expected, label.GetFontName());

            label.SetLock(LOCK_FONTNAME);

            result = label.SetFontName(CString("Times New Roman"));

            Assert::IsFalse(result);
            Assert::AreEqual(expected, label.GetFontName());

        }

        TEST_METHOD(SetFontSize_ValidSize_SetsFontSize)
        {
            CProMoLabel label;
            unsigned int size = 14;

            BOOL result = label.SetFontSize(size);

            Assert::IsTrue(result);
            Assert::AreEqual(size, label.GetFontSize());

            result = label.SetFontSize(0);

            Assert::IsFalse(result);
            Assert::AreEqual(size, label.GetFontSize());
            
            label.SetLock(LOCK_FONTSIZE);

            result = label.SetFontSize(20);
            
            Assert::IsFalse(result);
            Assert::AreEqual(size, label.GetFontSize());
        }

        TEST_METHOD(SetFontWeight_ValidWeight_SetsFontWeight)
        {
            CProMoLabel label;
            unsigned int weight = FW_BOLD;

            BOOL result = label.SetFontWeight(weight);

            Assert::IsTrue(result);
            Assert::AreEqual(weight, label.GetFontWeight());

            label.SetLock(LOCK_FONTWEIGHT);

            result = label.SetFontWeight(FW_HEAVY);

            Assert::IsFalse(result);
            Assert::AreEqual(weight, label.GetFontWeight());
        }

        TEST_METHOD(SetFontItalic_True_SetsItalic)
        {
            CProMoLabel label;
            BOOL italic = TRUE;

            BOOL result = label.SetFontItalic(italic);

            Assert::IsTrue(result);
            Assert::IsTrue(label.IsFontItalic());

            label.SetLock(LOCK_FONTITALIC);

            result = label.SetFontItalic(FALSE);

            Assert::IsFalse(result);
            Assert::IsTrue(label.IsFontItalic());
        }

        TEST_METHOD(SetFontUnderline_True_SetsUnderline)
        {
            CProMoLabel label;
            BOOL underline = TRUE;

            BOOL result = label.SetFontUnderline(underline);

            Assert::IsTrue(result);
            Assert::IsTrue(label.IsFontUnderline());

            label.SetLock(LOCK_FONTUNDERLINE);

            result = label.SetFontUnderline(FALSE);

            Assert::IsFalse(result);
            Assert::IsTrue(label.IsFontUnderline());
        }
        
        TEST_METHOD(SetFontStrikeOut_True_SetsStrikeOut)
        {
            CProMoLabel label;
            BOOL strikeOut = TRUE;

            BOOL result = label.SetFontStrikeOut(strikeOut);

            Assert::IsTrue(result);
            Assert::IsTrue(label.IsFontStrikeOut());

            label.SetLock(LOCK_FONTSTRIKEOUT);

            result = label.SetFontStrikeOut(FALSE);

            Assert::IsFalse(result);
            Assert::IsTrue(label.IsFontStrikeOut());
        }

        TEST_METHOD(SetFontColor_ValidColor_SetsColor)
        {
            CProMoLabel label;
            COLORREF color = RGB(255,0,0);

            BOOL result = label.SetTextColor(color);

            Assert::IsTrue(result);
            Assert::AreEqual(color, label.GetTextColor());

            label.SetLock(LOCK_TEXTCOLOR);

            result = label.SetTextColor(RGB(0,255,0));

            Assert::IsFalse(result);
            Assert::AreEqual(color, label.GetTextColor());
        }
        
        TEST_METHOD(SetBkColor_ValidColor_SetsColor)
        {
            CProMoLabel label;
            COLORREF color = RGB(255, 0, 0);

            BOOL result = label.SetBkColor(color);

            Assert::IsTrue(result);
            Assert::AreEqual(color, label.GetBkColor());

            label.SetLock(LOCK_BKCOLOR);

            result = label.SetBkColor(RGB(0, 255, 0));

            Assert::IsFalse(result);
            Assert::AreEqual(color, label.GetBkColor());
        }
        
        TEST_METHOD(SetBkMode_ValidMode_SetsBkMode)
        {
            CProMoLabel label;
            unsigned int mode = OPAQUE;

            BOOL result = label.SetBkMode(mode);

            Assert::IsTrue(result);
            Assert::AreEqual(mode, label.GetBkMode());

            label.SetLock(LOCK_BKMODE);

            result = label.SetBkMode(TRANSPARENT);

            Assert::IsFalse(result);
            Assert::AreEqual(mode, label.GetBkMode());
        }

        TEST_METHOD(SetTextAlignment_ValidValue_SetsAlignment)
        {
            CProMoLabel label;
            unsigned int alignment = DT_VCENTER;

            BOOL result = label.SetTextAlignment(alignment);

            Assert::IsTrue(result);
            Assert::AreEqual(alignment, label.GetTextAlignment());

            label.SetLock(LOCK_ALIGNMENT);

            result = label.SetTextAlignment(DT_RIGHT);

            Assert::IsFalse(result);
            Assert::AreEqual(alignment, label.GetTextAlignment());
        }

        TEST_METHOD(SetTextAlignment_ValidValue_SetsOnlyAppropriateFlags)
        {
            CProMoLabel label;
            unsigned int hAlignment = DT_LEFT;
			unsigned int vAlignment = DT_BOTTOM;
			unsigned int otherFlag = DT_WORDBREAK;

            BOOL result = label.SetTextAlignment(hAlignment | vAlignment | otherFlag);

            Assert::IsTrue(result);
            Assert::AreEqual(hAlignment | vAlignment | otherFlag, label.GetTextAlignment());

			result = label.SetTextHorizontalAlignment(DT_RIGHT);
            
            Assert::IsTrue(result);
            Assert::AreEqual(DT_RIGHT, (int)label.GetTextHorizontalAlignment());
			Assert::AreEqual(vAlignment, label.GetTextVerticalAlignment());
            Assert::AreEqual(DT_RIGHT | vAlignment | otherFlag, label.GetTextAlignment());

            result = label.SetTextVerticalAlignment(DT_TOP);

            Assert::IsTrue(result);
            Assert::AreEqual(DT_RIGHT, (int)label.GetTextHorizontalAlignment());
            Assert::AreEqual(DT_TOP, (int)label.GetTextVerticalAlignment());
            Assert::AreEqual(DT_RIGHT | DT_TOP | otherFlag, label.GetTextAlignment());

        }

        TEST_METHOD(SetTextAlignmentFlag_ValidValue_SetsAlignment)
        {
            CProMoLabel label;
            unsigned int hAlignment = DT_RIGHT;
            unsigned int vAlignment = DT_BOTTOM;
            unsigned int groupFlag = DT_WORDBREAK;
            unsigned int otherFlag = DT_NOPREFIX;
            label.SetTextAlignment(0);

            BOOL result = label.SetTextAlignmentFlag(vAlignment, TRUE);

            Assert::IsTrue(result);
			Assert::IsTrue(label.HasTextAlignmentFlag(vAlignment));
            Assert::AreEqual(vAlignment, label.GetTextAlignment());

            result = label.SetTextAlignmentFlag(hAlignment, TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(label.HasTextAlignmentFlag(hAlignment));
            Assert::AreEqual(vAlignment | hAlignment, label.GetTextAlignment());

            result = label.SetTextAlignmentFlag(groupFlag, TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(label.HasTextAlignmentFlag(groupFlag));
            Assert::AreEqual(vAlignment | hAlignment | groupFlag, label.GetTextAlignment());

            result = label.SetTextAlignmentFlag(otherFlag, TRUE);

            Assert::IsTrue(result);
            Assert::IsTrue(label.HasTextAlignmentFlag(otherFlag));
            Assert::AreEqual(vAlignment | hAlignment | groupFlag | otherFlag, label.GetTextAlignment());
            
            result = label.SetTextAlignmentFlag(vAlignment, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(label.HasTextAlignmentFlag(vAlignment));
            Assert::AreEqual(hAlignment | groupFlag | otherFlag, label.GetTextAlignment());

            result = label.SetTextAlignmentFlag(otherFlag, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(label.HasTextAlignmentFlag(otherFlag));
            Assert::AreEqual(hAlignment | groupFlag, label.GetTextAlignment());

            result = label.SetTextAlignmentFlag(hAlignment, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(label.HasTextAlignmentFlag(hAlignment));
            Assert::AreEqual(groupFlag, label.GetTextAlignment());

            result = label.SetTextAlignmentFlag(groupFlag, FALSE);

            Assert::IsTrue(result);
            Assert::IsFalse(label.HasTextAlignmentFlag(groupFlag));
            Assert::AreEqual(0, (int)label.GetTextAlignment());

        }

#pragma endregion

#pragma region Geometry

        TEST_METHOD(SetRect_WhenCRectPassed_UpdatesCoordinates)
        {
            CProMoLabel label;
            CRect rect(10, 20, 210, 120);

            label.SetRect(rect);

            Assert::AreEqual(10.0, label.GetLeft());
            Assert::AreEqual(20.0, label.GetTop());
            Assert::AreEqual(210.0, label.GetRight());
            Assert::AreEqual(120.0, label.GetBottom());
        }

        TEST_METHOD(SetRect_WhenCoordinatesPassed_UpdatesCoordinates)
        {
            CProMoLabel label;
            label.SetRect(5.0, 15.0, 155.0, 65.0);

            Assert::AreEqual(5.0, label.GetLeft());
            Assert::AreEqual(15.0, label.GetTop());
            Assert::AreEqual(155.0, label.GetRight());
            Assert::AreEqual(65.0, label.GetBottom());
        }

#pragma endregion

#pragma region LayoutTests

        TEST_METHOD(SetLabelAnchorPoint_ValidValue_SetsAnchor)
        {
            CProMoLabel label;
            unsigned int labelAnchoring = DEHT_TOPLEFT;

            BOOL result = label.SetLabelAnchorPoint(labelAnchoring);

            Assert::IsTrue(result);
            Assert::AreEqual(labelAnchoring, label.GetLabelAnchorPoint());

            label.SetLock(LOCK_ANCHORING);

            result = label.SetLabelAnchorPoint(DEHT_BOTTOMRIGHT);

            Assert::IsFalse(result);
            Assert::AreEqual(labelAnchoring, label.GetLabelAnchorPoint());
        }

        TEST_METHOD(SetViewAnchorPoint_ValidValue_SetsAnchor)
        {
            CProMoLabel label;
            unsigned int labelAnchoring = DEHT_TOPLEFT;

            BOOL result = label.SetViewAnchorPoint(labelAnchoring);

            Assert::IsTrue(result);
            Assert::AreEqual(labelAnchoring, label.GetViewAnchorPoint());

            label.SetLock(LOCK_ANCHORING);

            result = label.SetViewAnchorPoint(DEHT_BOTTOMRIGHT);

            Assert::IsFalse(result);
            Assert::AreEqual(labelAnchoring, label.GetViewAnchorPoint());
        }

        TEST_METHOD(SetAnchorView_ValidValue_SetsAnchor)
        {
            CProMoLabel label;
            unsigned int labelAnchoring = VIEW_LAST;

            BOOL result = label.SetAnchorView(labelAnchoring);

            Assert::IsTrue(result);
            Assert::AreEqual(labelAnchoring, label.GetAnchorView());

            label.SetLock(LOCK_ANCHORING);

            result = label.SetAnchorView(VIEW_FIRST);

            Assert::IsFalse(result);
            Assert::AreEqual(labelAnchoring, label.GetAnchorView());
        }

        TEST_METHOD(SetVisible_False_HidesLabel)
        {
            CProMoLabel label;

            label.SetVisible(FALSE);

            Assert::IsFalse(label.IsVisible());
        }

        TEST_METHOD(SetFitTitle_True_UpdatesFlag)
        {
            CProMoLabel label;

            label.SetFitTitle(TRUE);

            Assert::IsTrue(label.HasFitTitle());
        }

        TEST_METHOD(SetFitView_True_UpdatesFlag)
        {
            CProMoLabel label;

            label.SetFitView(TRUE);

            Assert::IsTrue(label.HasFitView());
        }

#pragma endregion

#pragma region CopyAndClone

        TEST_METHOD(Clone_NewObject_PropertiesCopied)
        {
            // Arrange
            CProMoLabel original;
            original.SetFontName(_T("Tahoma"));
            original.SetFontSize(18);
            original.SetRect(100, 50, 250, 120);
            original.SetFontWeight(FW_BOLD);
            original.SetFontItalic(TRUE);
            original.SetFontUnderline(TRUE);
            original.SetFontStrikeOut(TRUE);
            original.SetTextColor(RGB(255, 0, 0));
            original.SetBkColor(RGB(0, 255, 0));
            original.SetBkMode(OPAQUE);
            original.SetTextAlignment(DT_NOPREFIX | DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
            original.SetViewAnchorPoint(DEHT_TOPLEFT);
            original.SetLabelAnchorPoint(DEHT_BOTTOMRIGHT);
            original.SetAnchorView(VIEW_MID);
            original.SetMargins(1.0, 2.0, 3.0, 4.0);

            // Act
            std::unique_ptr<CDiagramEntity> clone(original.Clone());

            // Assert
            CProMoLabel* clonedLabel = dynamic_cast<CProMoLabel*>(clone.get());
            Assert::IsNotNull(clonedLabel);
            
            Assert::AreEqual(original.GetPropertyName(), clonedLabel->GetPropertyName());
            Assert::AreEqual(original.GetLeft(), clonedLabel->GetLeft());
            Assert::AreEqual(original.GetTop(), clonedLabel->GetTop());
            Assert::AreEqual(original.GetRight(), clonedLabel->GetRight());
            Assert::AreEqual(original.GetBottom(), clonedLabel->GetBottom());
            Assert::AreEqual(original.GetFontName(), clonedLabel->GetFontName());
            Assert::AreEqual(original.GetFontSize(), clonedLabel->GetFontSize());
            Assert::AreEqual(original.GetFontWeight(), clonedLabel->GetFontWeight());
            Assert::AreEqual(original.IsFontItalic(), clonedLabel->IsFontItalic());
            Assert::AreEqual(original.IsFontUnderline(), clonedLabel->IsFontUnderline());
            Assert::AreEqual(original.IsFontStrikeOut(), clonedLabel->IsFontStrikeOut());
            Assert::AreEqual(original.GetTextColor(), clonedLabel->GetTextColor());
            Assert::AreEqual(original.GetBkColor(), clonedLabel->GetBkColor());
            Assert::AreEqual(original.GetBkMode(), clonedLabel->GetBkMode());
            Assert::AreEqual(original.GetTextAlignment(), clonedLabel->GetTextAlignment());
            Assert::AreEqual(original.GetViewAnchorPoint(), clonedLabel->GetViewAnchorPoint());
            Assert::AreEqual(original.GetLabelAnchorPoint(), clonedLabel->GetLabelAnchorPoint());
            Assert::AreEqual(original.GetAnchorView(), clonedLabel->GetAnchorView());
            double lMargin, rMargin, tMargin, bMargin;
            original.GetMargins(lMargin, tMargin, rMargin, bMargin);
            double clMargin, crMargin, ctMargin, cbMargin;
            clonedLabel->GetMargins(clMargin, ctMargin, crMargin, cbMargin);
            Assert::AreEqual(clMargin, lMargin);
            Assert::AreEqual(ctMargin, tMargin);
            Assert::AreEqual(crMargin, rMargin);
            Assert::AreEqual(cbMargin, bMargin);

        }

#pragma endregion

#pragma region PropertyTests
        TEST_METHOD(GetProperty_NoLinkedModel_ReturnsLabelTitle)
        {
            CProMoLabel label;
			CProMoProperty* property = label.GetProperty();

            Assert::IsNotNull(property);

            CVariantWrapper wrapper;
            wrapper.SetString(CString("Test"));
			property->SetValue(wrapper);

			Assert::AreEqual(CString("Test"), label.GetTitle());
		}

#pragma region HitCode

        TEST_METHOD(GetHitCode_WhenUnlocked_ReturnsCorrectConstant)
        {
            CProMoLabel label;

            int code = label.GetHitCode(CPoint(20, 20), CRect(0, 0, 20, 20));

            Assert::AreEqual(DEHT_BOTTOMRIGHT, code);
        }

        TEST_METHOD(GetHitCode_WhenRepositionIsLocked_ReturnsCorrectConstant)
        {
            CProMoLabel label;
            label.SetLock(LOCK_REPOSITIONING);

            int code = label.GetHitCode(CPoint(10, 10), CRect(0, 0, 20, 20));

            Assert::AreEqual(DEHT_BODY, code);

            code = label.GetHitCode(CPoint(20, 20), CRect(0, 0, 20, 20));

            Assert::AreEqual(DEHT_NONE, code);
        }

        TEST_METHOD(GetHitCode_WhenSelectionIsLocked_ReturnsCorrectConstant)
        {
            CProMoLabel label;
            label.SetLock(LOCK_SELECTION);

            int code = label.GetHitCode(CPoint(10, 10), CRect(0, 0, 20, 20));

            Assert::AreEqual(DEHT_NONE, code);
        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(GetDefaultGetString_WhenInvoked_ReturnsCorrectString)
        {
            CProMoLabel label;
            CString viewString;

            label.SetFitTitle(FALSE);
            label.SetName(CString("Label"));
            label.SetTitle(CString("My Label"));
            label.SetRect(100, 50, 250, 120);
            label.SetFontName(CString("Arial"));
            label.SetFontSize(14);
            label.SetFontWeight(FW_BOLD);
            label.SetFontItalic(TRUE);
            label.SetFontUnderline(TRUE);
            label.SetFontStrikeOut(TRUE);
            label.SetTextColor(RGB(255, 0, 0));
            label.SetBkColor(RGB(0, 255, 0));
            label.SetBkMode(OPAQUE);
            label.SetTextAlignment(DT_NOPREFIX | DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
            label.SetViewAnchorPoint(DEHT_TOPLEFT);
            label.SetLabelAnchorPoint(DEHT_BOTTOMRIGHT);
            label.SetAnchorView(VIEW_MID);
            label.SetMargins(1.0, 2.0, 3.0, 4.0);
            
            viewString = label.GetString();

            Assert::AreEqual(CString("promo_label:Label,100.000000,50.000000,250.000000,120.000000,My Label,0,,,0,Arial,14,700,1,1,1,255,65280,2,2090,7,2,2,0.000000,0.000000,2.000000,1.000000,4.000000,3.000000,0;"), viewString);

        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoLabel labelStub;
            CProMoLabel* label = dynamic_cast<CProMoLabel*>(labelStub.CreateFromString(CString("promo_label:Label,100.000000,50.000000,250.000000,120.000000,My Label,0,,Property,0,Arial,14,700,1,1,1,255,65280,2,2090,7,2,2,0.000000,0.000000,2.000000,1.000000,4.000000,3.000000,0;")));

            Assert::AreEqual(CString("promo_label"), label->GetType());
            Assert::AreEqual(CString("Label"), label->GetName());
            Assert::AreEqual(CString("Property"), label->GetPropertyName());
            Assert::AreEqual(100.0, label->GetLeft());
            Assert::AreEqual(50.0, label->GetTop());
            Assert::AreEqual(250.0, label->GetRight());
            Assert::AreEqual(120.0, label->GetBottom());
            Assert::AreEqual(CString("Arial"), label->GetFontName());
            Assert::AreEqual((unsigned int)14, label->GetFontSize());
            Assert::AreEqual((unsigned int)FW_BOLD, label->GetFontWeight());
            Assert::IsTrue(label->IsFontItalic());
            Assert::IsTrue(label->IsFontUnderline());
            Assert::IsTrue(label->IsFontStrikeOut());
            Assert::AreEqual(RGB(255, 0, 0), label->GetTextColor());
            Assert::AreEqual(RGB(0, 255, 0), label->GetBkColor());
            Assert::AreEqual((unsigned int)OPAQUE, label->GetBkMode());
            Assert::AreEqual((unsigned int)DT_NOPREFIX | DT_SINGLELINE | DT_BOTTOM | DT_RIGHT, label->GetTextAlignment());
            Assert::AreEqual((unsigned int)DEHT_TOPLEFT, label->GetViewAnchorPoint());
            Assert::AreEqual((unsigned int)DEHT_BOTTOMRIGHT, label->GetLabelAnchorPoint());
            Assert::AreEqual((unsigned int)VIEW_MID, label->GetAnchorView());
            double lMargin, rMargin, tMargin, bMargin;
            label->GetMargins(lMargin, tMargin, rMargin, bMargin);
            Assert::AreEqual(1.0, lMargin);
            Assert::AreEqual(2.0, tMargin);
            Assert::AreEqual(3.0, rMargin);
            Assert::AreEqual(4.0, bMargin);

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoLabel labelStub;
            CProMoLabel* label = dynamic_cast<CProMoLabel*>(labelStub.CreateFromString(CString("promo_label:Label,100.000000,50.000000,250.000000,120.000000,My Label,0,,Property,0,Arial,14,700,1,1,1,255,65280,2,2090,7,2,2,0.000000,0.000000,2.000000,1.000000,4.000000,3.000000,0,Other,Other2;")));

            Assert::AreEqual(CString("promo_label"), label->GetType());
            Assert::AreEqual(CString("Label"), label->GetName());
            Assert::AreEqual(CString("Property"), label->GetPropertyName());
            Assert::AreEqual(100.0, label->GetLeft());
            Assert::AreEqual(50.0, label->GetTop());
            Assert::AreEqual(250.0, label->GetRight());
            Assert::AreEqual(120.0, label->GetBottom());
            Assert::AreEqual(CString("Arial"), label->GetFontName());
            Assert::AreEqual((unsigned int)14, label->GetFontSize());
            Assert::AreEqual((unsigned int)FW_BOLD, label->GetFontWeight());
            Assert::IsTrue(label->IsFontItalic());
            Assert::IsTrue(label->IsFontUnderline());
            Assert::IsTrue(label->IsFontStrikeOut());
            Assert::AreEqual(RGB(255, 0, 0), label->GetTextColor());
            Assert::AreEqual(RGB(0, 255, 0), label->GetBkColor());
            Assert::AreEqual((unsigned int)OPAQUE, label->GetBkMode());
            Assert::AreEqual((unsigned int)DT_NOPREFIX | DT_SINGLELINE | DT_BOTTOM | DT_RIGHT, label->GetTextAlignment());
            Assert::AreEqual((unsigned int)DEHT_TOPLEFT, label->GetViewAnchorPoint());
            Assert::AreEqual((unsigned int)DEHT_BOTTOMRIGHT, label->GetLabelAnchorPoint());
            Assert::AreEqual((unsigned int)VIEW_MID, label->GetAnchorView());
            double lMargin, rMargin, tMargin, bMargin;
            label->GetMargins(lMargin, tMargin, rMargin, bMargin);
            Assert::AreEqual(1.0, lMargin);
            Assert::AreEqual(2.0, tMargin);
            Assert::AreEqual(3.0, rMargin);
            Assert::AreEqual(4.0, bMargin);

        }

        TEST_METHOD(CreateFromString_WhenStringWithMissingParametersIsPassed_UseDefaultFormatting)
        {
            CProMoLabel labelStub;
            CProMoLabel* label = dynamic_cast<CProMoLabel*>(labelStub.CreateFromString(CString("promo_label:Label,100.000000,50.000000,250.000000,120.000000,My Label,0,,Property,0,Arial;")));

            Assert::AreEqual(CString("promo_label"), label->GetType());
            Assert::AreEqual(CString("Label"), label->GetName());
            Assert::AreEqual(CString("Property"), label->GetPropertyName());
            Assert::AreEqual(100.0, label->GetLeft());
            Assert::AreEqual(50.0, label->GetTop());
            Assert::AreEqual(250.0, label->GetRight());
            Assert::AreEqual(120.0, label->GetBottom());

            Assert::AreEqual(CString("Courier New"), label->GetFontName());
            Assert::AreEqual((unsigned int)12, label->GetFontSize());
            Assert::AreEqual((unsigned int)FW_NORMAL, label->GetFontWeight());
            Assert::IsFalse(label->IsFontItalic());
            Assert::IsFalse (label->IsFontUnderline());
            Assert::IsFalse(label->IsFontStrikeOut());
            Assert::AreEqual(RGB(0, 0, 0), label->GetTextColor());
            Assert::AreEqual(CLR_NONE, label->GetBkColor());
            Assert::AreEqual((unsigned int)TRANSPARENT, label->GetBkMode());
            Assert::AreEqual((unsigned int)DT_NOPREFIX | DT_SINGLELINE | DT_VCENTER | DT_CENTER, label->GetTextAlignment());
            Assert::AreEqual((unsigned int)DEHT_CENTER, label->GetViewAnchorPoint());
            Assert::AreEqual((unsigned int)DEHT_CENTER, label->GetLabelAnchorPoint());
            Assert::AreEqual((unsigned int)VIEW_FIRST, label->GetAnchorView());
            double lMargin, rMargin, tMargin, bMargin;
            label->GetMargins(lMargin, tMargin, rMargin, bMargin);
            Assert::AreEqual(0.0, lMargin);
            Assert::AreEqual(0.0, tMargin);
            Assert::AreEqual(0.0, rMargin);
            Assert::AreEqual(0.0, bMargin);

        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoLabel labelStub;
            CProMoLabel* label = dynamic_cast<CProMoLabel*>(labelStub.CreateFromString(CString("wrong_type:Label,376.000000,54.000000,411.000000,69.000000,,0,Model,Title,8192,Courier New,12,400,1,1,1,-1,1,2085,3,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000;")));

            TestHelpers::PointerAssert::IsNull(label);
        }
        TEST_METHOD(GetModelFromString_ValidInput_ReturnsModelName)
        {
            CString input = _T("promo_label:Label,100.000000,50.000000,250.000000,120.000000,My Label,0,Model,Property,0,Arial,14,700,1,1,1,255,65280,2,2090,7,2,2,0.000000,0.000000,2.000000,1.000000,4.000000,3.000000,0;");
            CString result = CProMoLabel::GetModelFromString(input);

            Assert::AreEqual(_T("Model"), result);
        }

        TEST_METHOD(GetNameFromString_ValidInput_ReturnsName)
        {
            CString input = _T("promo_label:Label,100.000000,50.000000,250.000000,120.000000,My Label,0,,Property,0,Arial,14,700,1,1,1,255,65280,2,2090,7,2,2,0.000000,0.000000,2.000000,1.000000,4.000000,3.000000,0;");
            CString result = CProMoLabel::GetNameFromString(input);

            Assert::AreEqual(_T("Label"), result);
        }

#pragma endregion

#pragma region GDISmokeTests

        TEST_METHOD(Draw_WhenCalledWithMemoryDC_DoesNotCrash)
        {
            // Arrange
            CProMoLabel label;
            CString viewString;

            label.SetFitTitle(FALSE);
            label.SetName(CString("Label"));
            label.SetTitle(CString("My Label with a quite long title"));
            label.SetRect(100, 50, 250, 120);
            label.SetFontName(CString("Arial"));
            label.SetFontSize(14);
            label.SetFontWeight(FW_BOLD);
            label.SetFontItalic(TRUE);
            label.SetFontUnderline(TRUE);
            label.SetFontStrikeOut(TRUE);
            label.SetTextColor(RGB(255, 0, 0));
            label.SetBkColor(RGB(0, 255, 0));
            label.SetBkMode(OPAQUE);
            label.SetTextAlignment(DT_NOPREFIX | DT_SINGLELINE | DT_BOTTOM | DT_RIGHT);
            label.SetViewAnchorPoint(DEHT_TOPLEFT);
            label.SetLabelAnchorPoint(DEHT_BOTTOMRIGHT);
            label.SetAnchorView(VIEW_MID);
            label.SetMargins(1.0, 2.0, 3.0, 4.0);

            // Create memory DC
            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 200, 100);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 200, 100);

            // Act / Assert: should not crash
            label.Draw(&memDC, rect);

            label.DrawObject(&memDC, 0.5);

            label.SetTextAlignment(DT_NOPREFIX | DT_SINGLELINE | DT_BOTTOM | DT_RIGHT | DT_WORDBREAK);
            label.SetBkMode(TRANSPARENT);

            label.Draw(&memDC, rect);

            label.DrawObject(&memDC, 1.0);

        }

        TEST_METHOD(ShowPopup_WhenCalledWithDesktopWindow_DoesNotCrash)
        {
            // Arrange
            CProMoLabel label;
            label.SetRect(0, 0, 200, 100);

            CPoint point(50, 50);
            CWnd* parent = CWnd::FromHandle(::GetDesktopWindow());

            // Act / Assert
            label.ShowPopup(point, parent);
        }
#pragma endregion
    };
}