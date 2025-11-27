#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoEditor.h"
#include "../../src/ProMoEditor/ProMoEntityContainer.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include "../../src/ProMoEditor/ProMoLabel.h"
#include "../WinProMoTests.h"

class CProMoEditorTestStub : public CProMoEditor {
public:
    void IdentifyTarget(CPoint point) {
        CProMoEditor::IdentifyTarget(point);
    }
    CProMoBlockView* GetConnectedBlock(CProMoEdgeView* line, BOOL backwards) {
        return CProMoEditor::GetConnectedBlock(line, backwards);
    }
    void DeselectSubBlocks(CProMoBlockView* block) {
        CProMoEditor::DeselectSubBlocks(block);
    }
    void SelectBoundaryBlocks(CProMoBlockView* block) {
        CProMoEditor::SelectBoundaryBlocks(block);
    }
    void DeselectInvalidElements() {
        CProMoEditor::DeselectInvalidElements();
    }
    void ResetTarget() {
        CProMoEditor::ResetTarget();
    }
    void SetTarget(CProMoBlockView* obj, BOOL select) {
        CProMoEditor::SetTarget(obj, select);
    }
    void HandleSelectedElements(CProMoBlockView* target, BOOL isNew) {
        CProMoEditor::HandleSelectedElements(target, isNew);
    }
    void HandlePostResize(CDiagramEntity* element, UINT nFlags, CDoubleRect& oldRect, CPoint& point) {
        CProMoEditor::HandlePostResize(element, nFlags, oldRect, point);
    }
    BOOL RepositionSelectedBoundaryBlock() {
        return CProMoEditor::RepositionSelectedBoundaryBlock();
    }
    void SetInteractMode(int interactMode, int subMode) {
        CProMoEditor::SetInteractMode(interactMode, subMode);
    }
    void SplitSelectedEdge() {
        CProMoEditor::SplitSelectedEdge();
    }
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoEditorTests
{

    TEST_CLASS(CProMoEditorTests)
    {
    private:
        CProMoEditorTestStub m_editor;
        
        CProMoBlockView* m_a;
        CProMoBlockView* m_a1;
        CProMoBlockView* m_a2;
        CProMoBlockView* m_b;
        CProMoBlockView* m_b1;
        CProMoBlockView* m_b2;

        CProMoEdgeView* m_x;
        CProMoEdgeView* m_y;
        CProMoEdgeView* m_z;

        CProMoLabel* m_la;
        CProMoLabel* m_la1;
        CProMoLabel* m_la2;
        CProMoLabel* m_lb;
        CProMoLabel* m_lb1;
        CProMoLabel* m_lb2;
        CProMoLabel* m_lx;
        CProMoLabel* m_lz;
    
    public:
        
        TEST_METHOD_INITIALIZE(SetUp)
        {
            //Some MFC-rem_lated assertions still fail
            WinProMoTestHelpers::BootstrapMFC(); 
            CProMoEntityContainer* c = new CProMoEntityContainer(CString("custom"));
            m_editor.SetDiagramEntityContainer(c);
            m_editor.SetVirtualSize(CSize(2000, 2000));
            
            m_a = new CProMoBlockView();
            m_a1 = new CProMoBlockView();
            m_a2 = new CProMoBlockView();
            m_b = new CProMoBlockView();
            m_b1 = new CProMoBlockView();
            m_b2 = new CProMoBlockView();

            m_x = new CProMoEdgeView();
            m_y = new CProMoEdgeView();
            m_z = new CProMoEdgeView();

            m_a->LinkSubBlock(m_a1);
            m_a->LinkSubBlock(m_a2);
            m_b->LinkSubBlock(m_b1);
            m_b->LinkBoundaryBlock(m_b2, DEHT_BOTTOM);

            m_x->SetSource(m_a);
            m_x->SetDestination(m_y);
            m_y->SetDestination(m_b1);
            m_z->SetSource(m_b);
            m_z->SetDestination(m_a2);

            m_a->SetName(CString("6"));
            m_a1->SetName(CString("32"));
            m_a2->SetName(CString("74"));
            m_b->SetName(CString("17"));
            m_b1->SetName(CString("51"));
            m_b2->SetName(CString("121"));
            m_x->SetName(CString("392"));
            m_y->SetName(CString("452"));
            m_z->SetName(CString("523"));

            m_a->GetModel()->SetName(CString("4"));
            m_a1->GetModel()->SetName(CString("30"));
            m_a2->GetModel()->SetName(CString("72"));
            m_b->GetModel()->SetName(CString("15"));
            m_b1->GetModel()->SetName(CString("49"));
            m_b2->GetModel()->SetName(CString("119"));
            m_x->GetModel()->SetName(CString("391"));
            m_z->GetModel()->SetName(CString("522"));

            CVariantWrapper titleA;
            CVariantWrapper titleA1;
            CVariantWrapper titleA2;
            CVariantWrapper titleB;
            CVariantWrapper titleB1;
            CVariantWrapper titleB2;
            CVariantWrapper titleX;
            CVariantWrapper titleZ;
            
            titleA.SetString(CString("A"));
            titleA1.SetString(CString("A1"));
            titleA2.SetString(CString("A2"));
            titleB.SetString(CString("B"));
            titleB1.SetString(CString("B1"));
            titleB2.SetString(CString("B2"));
            titleX.SetString(CString("x"));
            titleZ.SetString(CString("z"));
            
            m_a->GetModel()->SetPropertyValue(CString("Title"), titleA);
            m_a1->GetModel()->SetPropertyValue(CString("Title"), titleA1);
            m_a2->GetModel()->SetPropertyValue(CString("Title"), titleA2);
            m_b->GetModel()->SetPropertyValue(CString("Title"), titleB);
            m_b1->GetModel()->SetPropertyValue(CString("Title"), titleB1);
            m_b2->GetModel()->SetPropertyValue(CString("Title"), titleB2);
            m_x->GetModel()->SetPropertyValue(CString("Title"), titleX);
            m_z->GetModel()->SetPropertyValue(CString("Title"), titleZ);

            m_a->SetRect(182.000000, 100.000000, 489.000000, 158.000000);
            m_a1->SetRect(216.000000, 121.000000, 344.000000, 153.000000);
            m_a2->SetRect(356.000000, 117.000000, 484.000000, 149.000000);
            m_b->SetRect(324.000000, 238.000000, 492.000000, 344.000000);
            m_b1->SetRect(348.000000, 266.000000, 476.000000, 298.000000);
            m_b2->SetRect(348.000000, 303.000000, 476.000000, 335.000000);
            m_x->SetRect(CDoubleRect(210.000000, 158.000000, 353.000000, 245.000000).ToCRect());
            m_y->SetRect(CDoubleRect(353.000000, 245.000000, 348.000000, 266.000000).ToCRect());
            m_z->SetRect(CDoubleRect(446.000000, 238.000000, 446.000000, 149.000000).ToCRect());

            CObArray labels;
            m_a->GetModel()->RecreateLabels(labels);
            m_la = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m_a1->GetModel()->RecreateLabels(labels);
            m_la1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m_a2->GetModel()->RecreateLabels(labels);
            m_la2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m_b->GetModel()->RecreateLabels(labels);
            m_lb = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m_b1->GetModel()->RecreateLabels(labels);
            m_lb1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m_b2->GetModel()->RecreateLabels(labels);
            m_lb2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m_x->GetModel()->RecreateLabels(labels);
            m_lx = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m_z->GetModel()->RecreateLabels(labels);
            m_lz = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            c->Add(m_a);
            c->Add(m_a1);
            c->Add(m_a2);
            c->Add(m_b);
            c->Add(m_b1);
            c->Add(m_b2);

            c->Add(m_x);
            c->Add(m_y);
            c->Add(m_z);

            c->Add(m_la);
            c->Add(m_la1);
            c->Add(m_la2);
            c->Add(m_lb);
            c->Add(m_lb1);
            c->Add(m_lb2);
            c->Add(m_lx);
            c->Add(m_lz);

        }

#pragma region ConstructionAndDefaults

        TEST_METHOD(Constructor_WhenCalled_InitializesDefaults) {

            int lMargin, tMargin, rMargin, bMargin;

            Assert::AreEqual(RGB(250, 250, 230), m_editor.GetBackgroundColor());
            Assert::IsFalse(m_editor.GetSnapToGrid());
            Assert::IsTrue(m_editor.IsPageBreaksVisible());
            Assert::AreEqual(RESTRAINT_VIRTUAL, m_editor.GetRestraints());
            m_editor.GetMargins(lMargin, tMargin, rMargin, bMargin);
            Assert::AreEqual(CRect(0, 0, 0, 0), CRect(lMargin, tMargin, rMargin, bMargin));
        }

#pragma endregion

#pragma region AlignmentTests
        TEST_METHOD(LeftAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.LeftAlignSelected();

            Assert::AreEqual(CDoubleRect(348.000000, 100.000000, 655.000000, 158.000000).ToCRect(), m_a->GetRect());
            Assert::AreEqual(CDoubleRect(382.000000, 121.000000, 510.000000, 153.000000).ToCRect(), m_a1->GetRect());
            Assert::AreEqual(CDoubleRect(522.000000, 117.000000, 650.000000, 149.000000).ToCRect(), m_a2->GetRect());
            Assert::AreEqual(CDoubleRect(324.000000, 238.000000, 492.000000, 344.000000).ToCRect(), m_b->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 266.000000, 476.000000, 298.000000).ToCRect(), m_b1->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 328.000000, 476.000000, 360.000000).ToCRect(), m_b2->GetRect());
            Assert::AreEqual(CDoubleRect(376.000000, 158.000000, 353.000000, 245.000000).ToCRect(), m_x->GetRect());
            Assert::AreEqual(CDoubleRect(353.000000, 245.000000, 348.000000, 266.000000).ToCRect(), m_y->GetRect());
            Assert::AreEqual(CDoubleRect(446.000000, 238.000000, 613.000000, 149.000000).ToCRect(), m_z->GetRect());
        }

        TEST_METHOD(RightAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.RightAlignSelected();

            Assert::AreEqual(CDoubleRect(169.000000, 100.000000, 476.000000, 158.000000).ToCRect(), m_a->GetRect());
            Assert::AreEqual(CDoubleRect(203.000000, 121.000000, 331.000000, 153.000000).ToCRect(), m_a1->GetRect());
            Assert::AreEqual(CDoubleRect(343.000000, 117.000000, 471.000000, 149.000000).ToCRect(), m_a2->GetRect());
            Assert::AreEqual(CDoubleRect(324.000000, 238.000000, 492.000000, 344.000000).ToCRect(), m_b->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 266.000000, 476.000000, 298.000000).ToCRect(), m_b1->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 328.000000, 476.000000, 360.000000).ToCRect(), m_b2->GetRect());
            Assert::AreEqual(CDoubleRect(197.000000, 158.000000, 353.000000, 245.000000).ToCRect(), m_x->GetRect());
            Assert::AreEqual(CDoubleRect(353.000000, 245.000000, 348.000000, 266.000000).ToCRect(), m_y->GetRect());
            Assert::AreEqual(CDoubleRect(446.000000, 238.000000, 433.000000, 149.000000).ToCRect(), m_z->GetRect());
        }

        TEST_METHOD(CenterAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.CenterAlignSelected();

            Assert::AreEqual(CDoubleRect(258.500000, 100.000000, 565.500000, 158.000000).ToCRect(), m_a->GetRect());
            Assert::AreEqual(CDoubleRect(292.500000, 121.000000, 420.500000, 153.000000).ToCRect(), m_a1->GetRect());
            Assert::AreEqual(CDoubleRect(432.500000, 117.000000, 560.500000, 149.000000).ToCRect(), m_a2->GetRect());
            Assert::AreEqual(CDoubleRect(324.000000, 238.000000, 492.000000, 344.000000).ToCRect(), m_b->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 266.000000, 476.000000, 298.000000).ToCRect(), m_b1->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 328.000000, 476.000000, 360.000000).ToCRect(), m_b2->GetRect());
            Assert::AreEqual(CDoubleRect(287.000000, 158.000000, 353.000000, 245.000000).ToCRect(), m_x->GetRect());
            Assert::AreEqual(CDoubleRect(353.000000, 245.000000, 348.000000, 266.000000).ToCRect(), m_y->GetRect());
            Assert::AreEqual(CDoubleRect(446.000000, 238.000000, 523.000000, 149.000000).ToCRect(), m_z->GetRect());
        }

        TEST_METHOD(TopAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a1->Select(TRUE);
            m_b->Select(TRUE);

            m_editor.TopAlignSelected();

            Assert::AreEqual(CDoubleRect(182.000000, 100.000000, 489.000000, 275.000000).ToCRect(), m_a->GetRect());
            Assert::AreEqual(CDoubleRect(216.000000, 238.000000, 344.000000, 270.000000).ToCRect(), m_a1->GetRect());
            Assert::AreEqual(CDoubleRect(356.000000, 117.000000, 484.000000, 149.000000).ToCRect(), m_a2->GetRect());
            Assert::AreEqual(CDoubleRect(324.000000, 238.000000, 492.000000, 344.000000).ToCRect(), m_b->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 266.000000, 476.000000, 298.000000).ToCRect(), m_b1->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 328.000000, 476.000000, 360.000000).ToCRect(), m_b2->GetRect());
            Assert::AreEqual(CDoubleRect(210.000000, 275.000000, 353.000000, 245.000000).ToCRect(), m_x->GetRect());
            Assert::AreEqual(CDoubleRect(353.000000, 245.000000, 348.000000, 266.000000).ToCRect(), m_y->GetRect());
            Assert::AreEqual(CDoubleRect(446.000000, 238.000000, 446.000000, 149.000000).ToCRect(), m_z->GetRect());
        }

        TEST_METHOD(BottomAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a1->Select(TRUE);
            m_b->Select(TRUE);

            m_editor.BottomAlignSelected();

            Assert::AreEqual(CDoubleRect(182.000000, 100.000000, 489.000000, 349.000000).ToCRect(), m_a->GetRect());
            Assert::AreEqual(CDoubleRect(216.000000, 312.000000, 344.000000, 344.000000).ToCRect(), m_a1->GetRect());
            Assert::AreEqual(CDoubleRect(356.000000, 117.000000, 484.000000, 149.000000).ToCRect(), m_a2->GetRect());
            Assert::AreEqual(CDoubleRect(324.000000, 238.000000, 492.000000, 344.000000).ToCRect(), m_b->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 266.000000, 476.000000, 298.000000).ToCRect(), m_b1->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 328.000000, 476.000000, 360.000000).ToCRect(), m_b2->GetRect());
            Assert::AreEqual(CDoubleRect(210.000000, 349.000000, 353.000000, 245.000000).ToCRect(), m_x->GetRect());
            Assert::AreEqual(CDoubleRect(353.000000, 245.000000, 348.000000, 266.000000).ToCRect(), m_y->GetRect());
            Assert::AreEqual(CDoubleRect(446.000000, 238.000000, 446.000000, 149.000000).ToCRect(), m_z->GetRect());
        }

        TEST_METHOD(MiddleAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a1->Select(TRUE);
            m_b->Select(TRUE);

            m_editor.MiddleAlignSelected();

            Assert::AreEqual(CDoubleRect(182.000000, 100.000000, 489.000000, 312.000000).ToCRect(), m_a->GetRect());
            Assert::AreEqual(CDoubleRect(216.000000, 275.000000, 344.000000, 307.000000).ToCRect(), m_a1->GetRect());
            Assert::AreEqual(CDoubleRect(356.000000, 117.000000, 484.000000, 149.000000).ToCRect(), m_a2->GetRect());
            Assert::AreEqual(CDoubleRect(324.000000, 238.000000, 492.000000, 344.000000).ToCRect(), m_b->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 266.000000, 476.000000, 298.000000).ToCRect(), m_b1->GetRect());
            Assert::AreEqual(CDoubleRect(348.000000, 328.000000, 476.000000, 360.000000).ToCRect(), m_b2->GetRect());
            Assert::AreEqual(CDoubleRect(210.000000, 312.000000, 353.000000, 245.000000).ToCRect(), m_x->GetRect());
            Assert::AreEqual(CDoubleRect(353.000000, 245.000000, 348.000000, 266.000000).ToCRect(), m_y->GetRect());
            Assert::AreEqual(CDoubleRect(446.000000, 238.000000, 446.000000, 149.000000).ToCRect(), m_z->GetRect());
        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(Load_WhenStringArrayIsPassed_CreateDiagramElements)
        {
            CStringArray diagram;
            CProMoControlFactory factory;

            diagram.Add(CString("custom:762,1091;"));
            diagram.Add(CString("promo_block_view:6,183.000000,105.000000,490.000000,163.000000,,0,4;"));
            diagram.Add(CString("promo_block_view:32,217.000000,126.000000,345.000000,158.000000,,0,30;"));
            diagram.Add(CString("promo_block_view:74,357.000000,122.000000,485.000000,154.000000,,0,72;"));
            diagram.Add(CString("promo_block_view:17,316.000000,238.000000,484.000000,344.000000,,0,15;"));
            diagram.Add(CString("promo_edge_view:523,438.000000,237.000000,447.000000,154.000000,,0,522,,;"));
            diagram.Add(CString("promo_block_view:51,340.000000,266.000000,468.000000,298.000000,,0,49;"));
            diagram.Add(CString("promo_edge_view:392,211.000000,163.000000,210.000000,275.000000,,0,391,,452;"));
            diagram.Add(CString("promo_edge_view:452,210.000000,275.000000,340.000000,266.000000,,0,391,392,;"));
            diagram.Add(CString("promo_block_view:121,340.000000,303.000000,468.000000,335.000000,,0,119;"));
            diagram.Add(CString("promo_block_model:4,,0;"));
            diagram.Add(CString("promo_block_model:30,4,1;"));
            diagram.Add(CString("promo_block_model:72,4,1;"));
            diagram.Add(CString("promo_block_model:15,,0;"));
            diagram.Add(CString("promo_edge_model:522,15,72;"));
            diagram.Add(CString("promo_block_model:49,15,1;"));
            diagram.Add(CString("promo_edge_model:391,4,49;"));
            diagram.Add(CString("promo_block_model:119,15,1;"));
            diagram.Add(CString("promo_label:3620,333.000000,105.000000,340.000000,120.000000,,0,4,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3835,274.000000,135.500000,288.000000,150.500000,,0,30,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:4050,414.000000,130.500000,428.000000,145.500000,,0,72,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:914,460.000000,185.000000,467.000000,200.000000,,0,522,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,20.000000,-3.500000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3405,396.500000,238.000000,403.500000,253.000000,,0,15,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:965,186.000000,203.000000,193.000000,218.000000,,0,391,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,-21.000000,-8.500000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:2975,397.000000,274.500000,411.000000,289.500000,,0,49,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3136,397.000000,311.500000,411.000000,326.500000,,0,119,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:1174,97.000000,47.000000,153.000000,62.000000,My Label,0,,,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("property:Title,3,A,4;"));
            diagram.Add(CString("property:Title,3,A1,30;"));
            diagram.Add(CString("property:Title,3,A2,72;"));
            diagram.Add(CString("property:Title,3,B,15;"));
            diagram.Add(CString("property:Title,3,z,522;"));
            diagram.Add(CString("property:Title,3,B1,49;"));
            diagram.Add(CString("property:Title,3,x,391;"));
            diagram.Add(CString("property:Title,3,B2,119;"));
            
            m_editor.Load(diagram, factory);

            CProMoEntityContainer* c = dynamic_cast<CProMoEntityContainer*>(m_editor.GetDiagramEntityContainer());

            Assert::AreEqual(18, c->GetSize());
            Assert::AreEqual(CString("custom"), c->GetModelType());
            Assert::AreEqual((LONG)762, c->GetVirtualSize().cx);
            Assert::AreEqual((LONG)1091, c->GetVirtualSize().cy);

        }

        TEST_METHOD(Save_WhenInvoked_CreateStringArray)
        {
            CStringArray result;

            m_editor.Save(result);
            
            Assert::AreEqual((INT_PTR)34, result.GetSize());

        }

#pragma endregion

#pragma region ClipboardTests
        
        TEST_METHOD(Cut_WhenInvoked_RemoveElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.Cut();
            
            Assert::AreEqual(13, m_editor.GetDiagramEntityContainer()->GetSize());
            
        }

        TEST_METHOD(Paste_WhenInvoked_AddElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            m_x->Select(TRUE);

            m_editor.Copy();
            m_editor.Paste();

            Assert::AreEqual(20, m_editor.GetDiagramEntityContainer()->GetSize());

        }

#pragma endregion

#pragma region UndoTests

        TEST_METHOD(Undo_WhenInvoked_RevertChanges) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.DeleteAllSelected();

            Assert::AreEqual(9, m_editor.GetDiagramEntityContainer()->GetSize());

            m_editor.Undo();

            Assert::AreEqual(17, m_editor.GetDiagramEntityContainer()->GetSize());

        }

        TEST_METHOD(Redo_WhenInvoked_RestoreChanges) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.DeleteAllSelected();

            Assert::AreEqual(9, m_editor.GetDiagramEntityContainer()->GetSize());

            m_editor.Undo();

            Assert::AreEqual(17, m_editor.GetDiagramEntityContainer()->GetSize());

            m_editor.Redo();

            Assert::AreEqual(9, m_editor.GetDiagramEntityContainer()->GetSize());

        }

#pragma endregion

#pragma region SelectionTests

        TEST_METHOD(SelectAll_WhenInvoked_SelectAllElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            
            m_editor.SelectAll();

            Assert::AreEqual(17, m_editor.GetSelectCount());

        }
        
        TEST_METHOD(UnselectAll_WhenInvoked_SelectNoElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.UnselectAll();

            Assert::AreEqual(0, m_editor.GetSelectCount());

        }

        TEST_METHOD(DeselectInvalidElements_WhenInvoked_DeselectDanglingEdges) {
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_a2->Select(TRUE);
            m_z->Select(TRUE);

            m_editor.DeselectInvalidElements();

            Assert::IsFalse(m_a2->IsSelected());
            Assert::IsFalse(m_x->IsSelected());
            Assert::IsFalse(m_z->IsSelected());
            Assert::IsTrue(m_a->IsSelected());
        }

        TEST_METHOD(DeselectInvalidElements_WhenInvoked_DeselectLabels) {
            
            m_a->Select(TRUE);
            m_a2->Select(TRUE);
            m_la->Select(TRUE);
            m_la2->Select(TRUE);

            m_editor.DeselectInvalidElements();
            
            Assert::IsFalse(m_la2->IsSelected());
            Assert::IsFalse(m_la->IsSelected());
            
        }

        TEST_METHOD(DeselectInvalidElements_WhenInvoked_KeepEdgesWhenBothEndsAreSelected) {
            m_b->Select(TRUE);
            m_x->Select(TRUE);
            m_a2->Select(TRUE);
            m_z->Select(TRUE);

            m_editor.DeselectInvalidElements();

            Assert::IsTrue(m_a2->IsSelected());
            Assert::IsFalse(m_x->IsSelected());
            Assert::IsTrue(m_z->IsSelected());
            Assert::IsTrue(m_b->IsSelected());
        }

        TEST_METHOD(DeselectChildBlocks_WhenInvoked_DeselectChildBlocks) {
            m_a1->Select(TRUE);
            m_a->Select(TRUE);

            m_editor.DeselectSubBlocks(m_a);
            Assert::IsFalse(m_a1->IsSelected());
            Assert::IsFalse(m_a2->IsSelected());
            Assert::IsTrue(m_a->IsSelected());
        }

        TEST_METHOD(SelectChildBlocks_WhenInvoked_SelectChildBlocks) {
            m_a1->Select(TRUE);
            
            m_editor.SelectBoundaryBlocks(m_a);
            Assert::IsFalse(m_a->IsSelected());
            Assert::IsTrue(m_a1->IsSelected());
            Assert::IsTrue(m_a2->IsSelected());
        }

        TEST_METHOD(IsAnyLabelSelected_WhenLabelSelected_ReturnTrue) {
            m_a->Select(TRUE);
            m_x->Select(TRUE);

            Assert::IsFalse(m_editor.IsAnyLabelSelected());

            m_la->Select(TRUE);

            Assert::IsTrue(m_editor.IsAnyLabelSelected());

        }

        TEST_METHOD(IsAnyBlockSelected_WhenBlockSelected_ReturnTrue) {
            m_la->Select(TRUE);
            m_x->Select(TRUE);

            Assert::IsFalse(m_editor.IsAnyBlockSelected());

            m_a->Select(TRUE);

            Assert::IsTrue(m_editor.IsAnyBlockSelected());

        }

        TEST_METHOD(IsAnyEdgeSelected_WhenEdgeSelected_ReturnTrue) {
            m_a->Select(TRUE);
            m_la->Select(TRUE);
            
            Assert::IsFalse(m_editor.IsAnyEdgeSelected());

            m_x->Select(TRUE);

            Assert::IsTrue(m_editor.IsAnyEdgeSelected());

        }
#pragma endregion

#pragma region TargetTests

        TEST_METHOD(SetTarget_WhenInvoked_SetsBlockAsTarget) {
            m_editor.SetTarget(m_a1, TRUE);

            Assert::IsTrue(m_a1->IsTarget());
        }

        TEST_METHOD(ResetTarget_WhenInvoked_ResetTarget) {
            m_a1->SetTarget(TRUE);
            
            m_editor.ResetTarget();

            Assert::IsFalse(m_a1->IsTarget());
        }

        TEST_METHOD(IdentifyTarget_WhenMovingBlock_SelectTopmostBlock) {

			m_b->Select(TRUE);
            m_editor.SetInteractMode(MODE_MOVING, NULL);
            
            m_editor.IdentifyTarget(CPoint(400,140));

            Assert::IsTrue(m_a2->IsTarget());
        }

        TEST_METHOD(IdentifyTarget_WhenChangingEdgeDest_SelectTopmostBlock) {

            m_x->Select(TRUE);

            m_editor.SetInteractMode(MODE_RESIZING, DEHT_BOTTOMRIGHT);

            m_editor.IdentifyTarget(CPoint(400, 140));

            Assert::IsTrue(m_a2->IsTarget());
        }

        TEST_METHOD(IdentifyTarget_WhenChangingEdgeSource_SelectTopmostBlock) {

            m_x->Select(TRUE);

            m_editor.SetInteractMode(MODE_RESIZING, DEHT_TOPLEFT);

            m_editor.IdentifyTarget(CPoint(400, 140));

            Assert::IsTrue(m_a2->IsTarget());
        }

        TEST_METHOD(IdentifyTarget_WhenCreatingNewBlock_SelectTopmostBlock) {

            CProMoBlockView* newBlock = new CProMoBlockView;

            m_editor.StartDrawingObject(newBlock);

            m_editor.IdentifyTarget(CPoint(400, 140));

            Assert::IsTrue(m_a2->IsTarget());
        }

        TEST_METHOD(IdentifyTarget_WhenCreatingNewEdge_SelectTopmostBlock) {

            CProMoEdgeView* newEdge = new CProMoEdgeView;

            m_editor.StartDrawingObject(newEdge);

            m_editor.IdentifyTarget(CPoint(400, 140));

            Assert::IsTrue(m_a2->IsTarget());
        }

#pragma endregion

#pragma region ModelEditingTests

        TEST_METHOD(HandleSelectedElements_WhenCreatingNewBlock_NestBlock) {
            
            m_b->Select(TRUE);

            m_editor.StartDrawingObject(m_b);

            m_a->SetTarget(DEHT_BODY);

            m_editor.HandleSelectedElements(m_a, TRUE);

            TestHelpers::PointerAssert::AreEqual(m_a->GetBlockModel(), m_b->GetBlockModel()->GetParentBlock());
        }

        TEST_METHOD(HandleSelectedElements_WhenCreatingNewEdge_ChangeSource) {
            
            m_x->Select(TRUE);
            
            m_editor.StartDrawingObject(m_x);

            m_editor.HandleSelectedElements(m_a, TRUE);

            TestHelpers::PointerAssert::AreEqual(m_a, dynamic_cast<CProMoBlockView*>(m_x->GetSource()));
        }

        TEST_METHOD(HandleSelectedElements_WhenMovingBlock_NestBlock) {
            
            m_b->Select(TRUE);

            m_editor.SetInteractMode(MODE_MOVING, NULL);

            m_a->SetTarget(DEHT_BODY);

            m_editor.HandleSelectedElements(m_a, FALSE);

            TestHelpers::PointerAssert::AreEqual(m_a->GetBlockModel(), m_b->GetBlockModel()->GetParentBlock());
        }

        TEST_METHOD(HandleSelectedElements_WhenResizingEdgeTopLeft_ChangeSource) {
            
            m_x->Select(TRUE);

            m_editor.SetInteractMode(MODE_RESIZING, DEHT_TOPLEFT);

            m_editor.HandleSelectedElements(m_a1, FALSE);
            
            TestHelpers::PointerAssert::AreEqual(m_a1, dynamic_cast<CProMoBlockView*>(m_x->GetSource()));
        }

        TEST_METHOD(HandleSelectedElements_WhenResizingEdgeBottomRight_ChangeDestination) {
            
            m_y->Select(TRUE);

            m_editor.SetInteractMode(MODE_RESIZING, DEHT_BOTTOMRIGHT);

            m_editor.HandleSelectedElements(m_b, FALSE);
            
            TestHelpers::PointerAssert::AreEqual(m_b, dynamic_cast<CProMoBlockView*>(m_y->GetDestination()));
        }

        TEST_METHOD(HandlePostResize_WhenShiftIsPressed_KeepBlockProportions) {
            
            CDoubleRect oldRect;

            oldRect.SetRect(m_a->GetLeft(), m_a->GetTop(), m_a->GetRight(), m_a->GetBottom());

            m_a->SetRight(m_a->GetRight() + 50);
            m_editor.SetInteractMode(MODE_RESIZING, DEHT_RIGHTMIDDLE);
            m_editor.HandlePostResize(m_a, MK_SHIFT, oldRect, CPoint(0,0));

            Assert::AreEqual(oldRect.right + 50, m_a->GetRight());
            Assert::AreEqual(oldRect.left, m_a->GetLeft());
            Assert::IsTrue((m_a->GetTop() - oldRect.top - 5) < 1);
            Assert::IsTrue((oldRect.bottom - 5 - m_a->GetBottom()) < 1);

        }

        TEST_METHOD(HandlePostResize_WhenShiftIsPressed_AlignEdgeToAxis) {
            
            CDoubleRect oldRect;

            oldRect.SetRect(m_z->GetLeft(), m_z->GetTop(), m_z->GetRight(), m_z->GetBottom());

            m_z->SetRight(m_z->GetRight() + 50);
            m_editor.SetInteractMode(MODE_RESIZING, DEHT_BOTTOMRIGHT);
            m_editor.HandlePostResize(m_z, MK_SHIFT, oldRect, CPoint(0, 0));

            Assert::AreEqual(oldRect.right + 50, m_z->GetRight());
            Assert::AreEqual(oldRect.left, m_z->GetLeft());
            Assert::AreEqual(oldRect.top, m_z->GetTop());
            Assert::AreEqual(oldRect.top - 50 , m_z->GetBottom());
        }

        TEST_METHOD(SplitSelectedEdge_WhenInvoked_SplitEdge) {
            m_z->Select(TRUE);

            m_editor.SplitSelectedEdge();

            TestHelpers::PointerAssert::AreNotEqual(m_a2, dynamic_cast<CProMoBlockView*>(m_z->GetDestination()));
            TestHelpers::PointerAssert::IsNotNull(dynamic_cast<CProMoEdgeView*>(m_z->GetDestination()));
        }

        TEST_METHOD(RepositionSelectedBoundaryBlock_IfNotMovedOutsideBoundaryLimit_DoNotDisconnect) {
            m_b2->Select(TRUE);

            m_editor.SetInteractMode(MODE_MOVING, NULL);

            BOOL result = m_editor.RepositionSelectedBoundaryBlock();

            Assert::IsFalse(result);
        }

        TEST_METHOD(RepositionSelectedBoundaryBlock_IfMovedOutsideBoundaryLimit_Disconnect) {
            m_b2->Select(TRUE);

            m_editor.SetInteractMode(MODE_MOVING, NULL);

            m_b2->SetRect(0, 0, 150, 150);

            BOOL result = m_editor.RepositionSelectedBoundaryBlock();

            Assert::IsTrue(result);
        }

#pragma endregion

#pragma region FormattingTests
        TEST_METHOD(SetFontName_ValidName_SetsFontName)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            CString expected = _T("Arial");

            // Act
            m_editor.SetFontName(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetFontName());
            Assert::AreEqual(expected, m_a->GetFontName());
            Assert::AreEqual(expected, m_x->GetFontName());
            Assert::AreEqual(expected, m_la->GetFontName());
            Assert::AreEqual(expected, m_lx->GetFontName());
            Assert::AreEqual(expected, m_lb->GetFontName());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetFontName());

        }

        TEST_METHOD(SetFontSize_ValidSize_SetsFontSize)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = 14;

            // Act
            m_editor.SetFontSize(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetFontSize());
            Assert::AreEqual(expected, m_a->GetFontSize());
            Assert::AreEqual(expected, m_x->GetFontSize());
            Assert::AreEqual(expected, m_la->GetFontSize());
            Assert::AreEqual(expected, m_lx->GetFontSize());
            Assert::AreEqual(expected, m_lb->GetFontSize());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetFontSize());
        }

        TEST_METHOD(SetFontWeight_ValidWeight_SetsFontWeight)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = FW_BOLD;

            // Act
            m_editor.SetFontWeight(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetFontWeight());
            Assert::AreEqual(expected, m_a->GetFontWeight());
            Assert::AreEqual(expected, m_x->GetFontWeight());
            Assert::AreEqual(expected, m_la->GetFontWeight());
            Assert::AreEqual(expected, m_lx->GetFontWeight());
            Assert::AreEqual(expected, m_lb->GetFontWeight());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetFontWeight());
        }

        TEST_METHOD(SetFontItalic_True_SetsItalic)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            BOOL expected = TRUE;

            // Act
            m_editor.SetFontItalic(expected);

            // Assert
            Assert::IsTrue(m_editor.IsFontItalic());
            Assert::IsTrue(m_a->IsFontItalic());
            Assert::IsTrue(m_x->IsFontItalic());
            Assert::IsTrue(m_la->IsFontItalic());
            Assert::IsTrue(m_lx->IsFontItalic());
            Assert::IsTrue(m_lb->IsFontItalic());
            
            m_a2->Select(TRUE);
            Assert::IsFalse(m_editor.IsFontItalic());
        }

        TEST_METHOD(SetFontUnderline_True_SetsUnderline)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            BOOL expected = TRUE;

            // Act
            m_editor.SetFontUnderline(expected);

            // Assert
            Assert::IsTrue(m_editor.IsFontUnderline());
            Assert::IsTrue(m_a->IsFontUnderline());
            Assert::IsTrue(m_x->IsFontUnderline());
            Assert::IsTrue(m_la->IsFontUnderline());
            Assert::IsTrue(m_lx->IsFontUnderline());
            Assert::IsTrue(m_lb->IsFontUnderline());

            m_a2->Select(TRUE);
            Assert::IsFalse(m_editor.IsFontUnderline());
        }

        TEST_METHOD(SetFontStrikeOut_True_SetsStrikeOut)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            BOOL expected = TRUE;

            // Act
            m_editor.SetFontStrikeOut(expected);

            // Assert
            Assert::IsTrue(m_editor.IsFontStrikeOut());
            Assert::IsTrue(m_a->IsFontStrikeOut());
            Assert::IsTrue(m_x->IsFontStrikeOut());
            Assert::IsTrue(m_la->IsFontStrikeOut());
            Assert::IsTrue(m_lx->IsFontStrikeOut());
            Assert::IsTrue(m_lb->IsFontStrikeOut());

            m_a2->Select(TRUE);
            Assert::IsFalse(m_editor.IsFontStrikeOut());
        }

        TEST_METHOD(SetFontColor_ValidColor_SetsColor)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            COLORREF expected = RGB(255, 0, 0);

            // Act
            m_editor.SetTextColor(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetTextColor());
            Assert::AreEqual(expected, m_a->GetTextColor());
            Assert::AreEqual(expected, m_x->GetTextColor());
            Assert::AreEqual(expected, m_la->GetTextColor());
            Assert::AreEqual(expected, m_lx->GetTextColor());
            Assert::AreEqual(expected, m_lb->GetTextColor());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetTextColor());
        }

        TEST_METHOD(SetBkColor_ValidColor_SetsColor)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            COLORREF expected = RGB(255, 0, 0);

            // Act
            m_editor.SetBkColor(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetBkColor());
            Assert::AreEqual(expected, m_a->GetBkColor());
            Assert::AreEqual(expected, m_x->GetBkColor());
            Assert::AreEqual(expected, m_lb->GetBkColor());

            m_la->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetBkColor());
        }

        TEST_METHOD(SetBkMode_ValidMode_SetsBkMode)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = OPAQUE;

            // Act
            m_editor.SetBkMode(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetBkMode());
            Assert::AreEqual(expected, m_a->GetBkMode());
            Assert::AreEqual(expected, m_x->GetBkMode());
            Assert::AreEqual(expected, m_lb->GetBkMode());

            m_la->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetBkMode());
        }

        TEST_METHOD(SetTextAlignment_ValidValue_SetsAlignment)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = DT_LEFT | DT_BOTTOM;

            // Act
            m_editor.SetTextAlignment(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetTextAlignment());
            Assert::AreEqual(expected, m_a->GetTextAlignment());
            Assert::AreEqual(expected, m_x->GetTextAlignment());
            Assert::AreEqual(expected, m_la->GetTextAlignment());
            Assert::AreEqual(expected, m_lx->GetTextAlignment());
            Assert::AreEqual(expected, m_lb->GetTextAlignment());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetTextAlignment());
        }

        TEST_METHOD(SetTextHorizontalAlignment_ValidValue_SetsAlignment)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = DT_RIGHT;

            // Act
            m_editor.SetTextHorizontalAlignment(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetTextHorizontalAlignment());
            Assert::AreEqual(expected, m_a->GetTextHorizontalAlignment());
            Assert::AreEqual(expected, m_x->GetTextHorizontalAlignment());
            Assert::AreEqual(expected, m_la->GetTextHorizontalAlignment());
            Assert::AreEqual(expected, m_lx->GetTextHorizontalAlignment());
            Assert::AreEqual(expected, m_lb->GetTextHorizontalAlignment());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetTextHorizontalAlignment());
        }

        TEST_METHOD(SetTextVerticalAlignment_ValidValue_SetsAlignment)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = DT_BOTTOM;

            // Act
            m_editor.SetTextVerticalAlignment(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetTextVerticalAlignment());
            Assert::AreEqual(expected, m_a->GetTextVerticalAlignment());
            Assert::AreEqual(expected, m_x->GetTextVerticalAlignment());
            Assert::AreEqual(expected, m_la->GetTextVerticalAlignment());
            Assert::AreEqual(expected, m_lx->GetTextVerticalAlignment());
            Assert::AreEqual(expected, m_lb->GetTextVerticalAlignment());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetTextVerticalAlignment());
        }

        TEST_METHOD(SetTextAlignmentFlag_ValidValue_SetsAlignment)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = DT_WORDBREAK;

            // Act
            m_editor.SetTextAlignmentFlag(expected, TRUE);

            // Assert
            Assert::IsTrue(m_editor.HasTextAlignmentFlag(expected));
            Assert::IsTrue(m_a->HasTextAlignmentFlag(expected));
            Assert::IsTrue(m_x->HasTextAlignmentFlag(expected));
            Assert::IsTrue(m_la->HasTextAlignmentFlag(expected));
            Assert::IsTrue(m_lx->HasTextAlignmentFlag(expected));
            Assert::IsTrue(m_lb->HasTextAlignmentFlag(expected));

            m_a2->Select(TRUE);
            Assert::IsFalse(m_editor.HasTextAlignmentFlag(expected));
        }

        TEST_METHOD(SetLineColor_ValidColor_SetsColor)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            COLORREF expected = RGB(255, 0, 0);

            // Act
            m_editor.SetLineColor(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetLineColor());
            Assert::AreEqual(expected, m_a->GetLineColor());
            Assert::AreEqual(expected, m_x->GetLineColor());
            
            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetLineColor());
        }

        TEST_METHOD(SetLineWidth_ValidWidth_SetsWidth)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = 3;

            // Act
            m_editor.SetLineWidth(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetLineWidth());
            Assert::AreEqual(expected, m_a->GetLineWidth());
            Assert::AreEqual(expected, m_x->GetLineWidth());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetLineWidth());
        }

        TEST_METHOD(SetLineStyle_ValidStyle_SetsStyle)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = PS_DASHDOT;

            // Act
            m_editor.SetLineStyle(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetLineStyle());
            Assert::AreEqual(expected, m_a->GetLineStyle());
            Assert::AreEqual(expected, m_x->GetLineStyle());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetLineStyle());
        }

        TEST_METHOD(SetFillColor_ValidColor_SetsColor)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            COLORREF expected = RGB(255, 0, 0);

            // Act
            m_editor.SetFillColor(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetFillColor());
            Assert::AreEqual(expected, m_a->GetFillColor());

            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetFillColor());
        }

        TEST_METHOD(SetFillPattern_WhenInvoked_SetsPattern)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            BOOL expected = TRUE;

            // Act
            m_editor.SetFillPattern(expected);

            // Assert
            Assert::IsTrue(m_editor.IsFillPattern());
            Assert::IsTrue(m_a->IsFillPattern());
            
            m_a2->Select(TRUE);
            Assert::IsFalse(m_editor.IsFillPattern());
        }

        TEST_METHOD(SetFillStyle_ValidStyle_SetsStyle)
        {
            // Arrange
            m_a->Select(TRUE);
            m_x->Select(TRUE);
            m_lb->Select(TRUE);
            unsigned int expected = HS_HORIZONTAL;

            // Act
            m_editor.SetFillStyle(expected);

            // Assert
            Assert::AreEqual(expected, m_editor.GetFillStyle());
            Assert::AreEqual(expected, m_a->GetFillStyle());
            
            m_a2->Select(TRUE);
            Assert::AreNotEqual(expected, m_editor.GetFillStyle());
        }

#pragma endregion

#pragma region LockingTests

        TEST_METHOD(IsLocked_IfLocked_ReturnTrue) {
            m_a->Select(TRUE);

            Assert::IsFalse(m_editor.IsLocked(LOCK_FONTSIZE));

            m_a->SetLock(LOCK_FONTNAME);

            Assert::IsFalse(m_editor.IsLocked(LOCK_FONTSIZE));

            m_a->SetLock(LOCK_FONTSIZE);

            Assert::IsTrue(m_editor.IsLocked(LOCK_FONTSIZE));
        }

#pragma endregion

#pragma region GDISmokeTests

        TEST_METHOD(Draw_WhenCalledWithMemoryDC_DoesNotCrash) {
            
            // Create memory DC
            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 2000, 2000);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 2000, 2000);

            m_a->Select(TRUE);
            m_x->Select(TRUE);

            m_editor.SetPageLayout(&memDC);
            m_editor.ShowPageBreaks(TRUE);

            m_editor.Draw(&memDC, rect);

            m_editor.SetInteractMode(MODE_MOVING, NULL);

            m_editor.Draw(&memDC, rect);

            m_editor.SetInteractMode(MODE_RESIZING, NULL);

            m_editor.Draw(&memDC, rect);
        }

#pragma endregion


    };

}
