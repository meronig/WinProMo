#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoEditor.h"
#include "../../src/ProMoEditor/ProMoEntityContainer.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoEditorTests
{

    TEST_CLASS(CProMoEditorTests)
    {
    private:
        CProMoEditor m_editor;
        
        CProMoBlockView* m_a;
        CProMoBlockView* m_a1;
        CProMoBlockView* m_a2;
        CProMoBlockView* m_b;
        CProMoBlockView* m_b1;
        CProMoBlockView* m_b2;

        CProMoEdgeView* m_x;
        CProMoEdgeView* m_y;
        CProMoEdgeView* m_z;

    
    public:
        
        TEST_METHOD_INITIALIZE(SetUp)
        {
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

            m_a1->GetModel()->SetParentBlock(m_a->GetModel());
            m_a2->GetModel()->SetParentBlock(m_a->GetModel());
            m_b1->GetModel()->SetParentBlock(m_b->GetModel());
            m_b2->GetModel()->SetParentBlock(m_b->GetModel());
            m_x->SetModel(m_y->GetModel());
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

            m_a->SetTitle(CString("A"));
            m_a1->SetTitle(CString("A1"));
            m_a2->SetTitle(CString("A2"));
            m_b->SetTitle(CString("B"));
            m_b1->SetTitle(CString("B1"));
            m_b2->SetTitle(CString("B2"));
            m_x->SetTitle(CString("x"));
            m_y->SetTitle(CString("y"));
            m_z->SetTitle(CString("z"));

            m_a->SetRect(182.000000, 100.000000, 489.000000, 158.000000);
            m_a1->SetRect(216.000000, 121.000000, 344.000000, 153.000000);
            m_a2->SetRect(356.000000, 117.000000, 484.000000, 149.000000);
            m_b->SetRect(324.000000, 238.000000, 492.000000, 344.000000);
            m_b1->SetRect(348.000000, 266.000000, 476.000000, 298.000000);
            m_b2->SetRect(348.000000, 303.000000, 476.000000, 335.000000);
            m_x->SetRect(CRect(210.000000, 158.000000, 353.000000, 245.000000));
            m_y->SetRect(CRect(353.000000, 245.000000, 348.000000, 266.000000));
            m_z->SetRect(CRect(446.000000, 238.000000, 446.000000, 149.000000));

            c->Add(m_a);
            c->Add(m_a1);
            c->Add(m_a2);
            c->Add(m_b);
            c->Add(m_b1);
            c->Add(m_b2);
            c->Add(m_x);
            c->Add(m_y);
            c->Add(m_z);
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

            Assert::AreEqual(CRect(348.000000, 100.000000, 655.000000, 158.000000), m_a->GetRect());
            Assert::AreEqual(CRect(382.000000, 121.000000, 510.000000, 153.000000), m_a1->GetRect());
            Assert::AreEqual(CRect(522.000000, 117.000000, 650.000000, 149.000000), m_a2->GetRect());
            Assert::AreEqual(CRect(324.000000, 238.000000, 492.000000, 344.000000), m_b->GetRect());
            Assert::AreEqual(CRect(348.000000, 266.000000, 476.000000, 298.000000), m_b1->GetRect());
            Assert::AreEqual(CRect(348.000000, 303.000000, 476.000000, 335.000000), m_b2->GetRect());
            Assert::AreEqual(CRect(376.000000, 158.000000, 353.000000, 245.000000), m_x->GetRect());
            Assert::AreEqual(CRect(353.000000, 245.000000, 348.000000, 266.000000), m_y->GetRect());
            Assert::AreEqual(CRect(446.000000, 238.000000, 613.000000, 149.000000), m_z->GetRect());
        }

        TEST_METHOD(RightAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.RightAlignSelected();

            Assert::AreEqual(CRect(169.000000, 100.000000, 476.000000, 158.000000), m_a->GetRect());
            Assert::AreEqual(CRect(203.000000, 121.000000, 331.000000, 153.000000), m_a1->GetRect());
            Assert::AreEqual(CRect(343.000000, 117.000000, 471.000000, 149.000000), m_a2->GetRect());
            Assert::AreEqual(CRect(324.000000, 238.000000, 492.000000, 344.000000), m_b->GetRect());
            Assert::AreEqual(CRect(348.000000, 266.000000, 476.000000, 298.000000), m_b1->GetRect());
            Assert::AreEqual(CRect(348.000000, 303.000000, 476.000000, 335.000000), m_b2->GetRect());
            Assert::AreEqual(CRect(197.000000, 158.000000, 353.000000, 245.000000), m_x->GetRect());
            Assert::AreEqual(CRect(353.000000, 245.000000, 348.000000, 266.000000), m_y->GetRect());
            Assert::AreEqual(CRect(446.000000, 238.000000, 433.000000, 149.000000), m_z->GetRect());
        }

        TEST_METHOD(CenterAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.CenterAlignSelected();

            Assert::AreEqual(CRect(258.500000, 100.000000, 565.500000, 158.000000), m_a->GetRect());
            Assert::AreEqual(CRect(292.500000, 121.000000, 420.500000, 153.000000), m_a1->GetRect());
            Assert::AreEqual(CRect(432.500000, 117.000000, 560.500000, 149.000000), m_a2->GetRect());
            Assert::AreEqual(CRect(324.000000, 238.000000, 492.000000, 344.000000), m_b->GetRect());
            Assert::AreEqual(CRect(348.000000, 266.000000, 476.000000, 298.000000), m_b1->GetRect());
            Assert::AreEqual(CRect(348.000000, 303.000000, 476.000000, 335.000000), m_b2->GetRect());
            Assert::AreEqual(CRect(287.000000, 158.000000, 353.000000, 245.000000), m_x->GetRect());
            Assert::AreEqual(CRect(353.000000, 245.000000, 348.000000, 266.000000), m_y->GetRect());
            Assert::AreEqual(CRect(446.000000, 238.000000, 523.000000, 149.000000), m_z->GetRect());
        }

        TEST_METHOD(TopAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a1->Select(TRUE);
            m_b->Select(TRUE);

            m_editor.TopAlignSelected();

            Assert::AreEqual(CRect(182.000000, 100.000000, 489.000000, 275.000000), m_a->GetRect());
            Assert::AreEqual(CRect(216.000000, 238.000000, 344.000000, 270.000000), m_a1->GetRect());
            Assert::AreEqual(CRect(356.000000, 117.000000, 484.000000, 149.000000), m_a2->GetRect());
            Assert::AreEqual(CRect(324.000000, 238.000000, 492.000000, 344.000000), m_b->GetRect());
            Assert::AreEqual(CRect(348.000000, 266.000000, 476.000000, 298.000000), m_b1->GetRect());
            Assert::AreEqual(CRect(348.000000, 303.000000, 476.000000, 335.000000), m_b2->GetRect());
            Assert::AreEqual(CRect(210.000000, 275.000000, 353.000000, 245.000000), m_x->GetRect());
            Assert::AreEqual(CRect(353.000000, 245.000000, 348.000000, 266.000000), m_y->GetRect());
            Assert::AreEqual(CRect(446.000000, 238.000000, 446.000000, 149.000000), m_z->GetRect());
        }

        TEST_METHOD(BottomAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a1->Select(TRUE);
            m_b->Select(TRUE);

            m_editor.BottomAlignSelected();

            Assert::AreEqual(CRect(182.000000, 100.000000, 489.000000, 349.000000), m_a->GetRect());
            Assert::AreEqual(CRect(216.000000, 312.000000, 344.000000, 344.000000), m_a1->GetRect());
            Assert::AreEqual(CRect(356.000000, 117.000000, 484.000000, 149.000000), m_a2->GetRect());
            Assert::AreEqual(CRect(324.000000, 238.000000, 492.000000, 344.000000), m_b->GetRect());
            Assert::AreEqual(CRect(348.000000, 266.000000, 476.000000, 298.000000), m_b1->GetRect());
            Assert::AreEqual(CRect(348.000000, 303.000000, 476.000000, 335.000000), m_b2->GetRect());
            Assert::AreEqual(CRect(210.000000, 349.000000, 353.000000, 245.000000), m_x->GetRect());
            Assert::AreEqual(CRect(353.000000, 245.000000, 348.000000, 266.000000), m_y->GetRect());
            Assert::AreEqual(CRect(446.000000, 238.000000, 446.000000, 149.000000), m_z->GetRect());
        }

        TEST_METHOD(MiddleAlignSelected_WhenInvoked_PositionIsCorrect) {
            m_a1->Select(TRUE);
            m_b->Select(TRUE);

            m_editor.MiddleAlignSelected();

            Assert::AreEqual(CRect(182.000000, 100.000000, 489.000000, 312.000000), m_a->GetRect());
            Assert::AreEqual(CRect(216.000000, 275.000000, 344.000000, 307.000000), m_a1->GetRect());
            Assert::AreEqual(CRect(356.000000, 117.000000, 484.000000, 149.000000), m_a2->GetRect());
            Assert::AreEqual(CRect(324.000000, 238.000000, 492.000000, 344.000000), m_b->GetRect());
            Assert::AreEqual(CRect(348.000000, 266.000000, 476.000000, 298.000000), m_b1->GetRect());
            Assert::AreEqual(CRect(348.000000, 303.000000, 476.000000, 335.000000), m_b2->GetRect());
            Assert::AreEqual(CRect(210.000000, 312.000000, 353.000000, 245.000000), m_x->GetRect());
            Assert::AreEqual(CRect(353.000000, 245.000000, 348.000000, 266.000000), m_y->GetRect());
            Assert::AreEqual(CRect(446.000000, 238.000000, 446.000000, 149.000000), m_z->GetRect());
        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(Load_WhenStringArrayIsPassed_CreateDiagramElements)
        {
            CStringArray diagram;
            CProMoControlFactory factory;

            diagram.Add(CString("custom:762,1091;"));
            diagram.Add(CString("promo_block_view:6,183.000000,105.000000,490.000000,163.000000,A,0,4;"));
            diagram.Add(CString("promo_block_view:32,217.000000,126.000000,345.000000,158.000000,A1,0,30;"));
            diagram.Add(CString("promo_block_view:74,357.000000,122.000000,485.000000,154.000000,A2,0,72;"));
            diagram.Add(CString("promo_block_view:17,316.000000,238.000000,484.000000,344.000000,B,0,15;"));
            diagram.Add(CString("promo_edge_view:523,438.000000,237.000000,447.000000,154.000000,z,0,522,,;"));
            diagram.Add(CString("promo_block_view:51,340.000000,266.000000,468.000000,298.000000,B1,0,49;"));
            diagram.Add(CString("promo_edge_view:392,211.000000,163.000000,210.000000,275.000000,x,0,391,,452;"));
            diagram.Add(CString("promo_edge_view:452,210.000000,275.000000,340.000000,266.000000,y,0,391,392,;"));
            diagram.Add(CString("promo_block_view:121,340.000000,303.000000,468.000000,335.000000,B2,0,119;"));
            diagram.Add(CString("promo_block_model:4,;"));
            diagram.Add(CString("promo_block_model:30,4;"));
            diagram.Add(CString("promo_block_model:72,4;"));
            diagram.Add(CString("promo_block_model:15,;"));
            diagram.Add(CString("promo_edge_model:522,15,72;"));
            diagram.Add(CString("promo_block_model:49,15;"));
            diagram.Add(CString("promo_edge_model:391,4,49;"));
            diagram.Add(CString("promo_block_model:119,15;"));

            m_editor.Load(diagram, &factory);

            CProMoEntityContainer* c = dynamic_cast<CProMoEntityContainer*>(m_editor.GetDiagramEntityContainer());

            Assert::AreEqual(9, c->GetSize());
            Assert::AreEqual(CString("custom"), c->GetModelType());
            Assert::AreEqual((LONG)762, c->GetVirtualSize().cx);
            Assert::AreEqual((LONG)1091, c->GetVirtualSize().cy);

        }

        TEST_METHOD(Save_WhenInvoked_CreateStringArray)
        {
            CStringArray result;

            m_editor.Save(result);
            
            Assert::AreEqual((INT_PTR)18, result.GetSize());

        }

#pragma endregion

#pragma region ClipboardTests
        
        TEST_METHOD(Cut_WhenInvoked_RemoveElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.Cut();
            
            Assert::AreEqual(7, m_editor.GetDiagramEntityContainer()->GetSize());
            
        }

        TEST_METHOD(Paste_WhenInvoked_AddElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            m_x->Select(TRUE);

            m_editor.Copy();
            m_editor.Paste();

            Assert::AreEqual(12, m_editor.GetDiagramEntityContainer()->GetSize());

        }

#pragma endregion

#pragma region UndoTests

        TEST_METHOD(Undo_WhenInvoked_RevertChanges) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.DeleteAllSelected();

            Assert::AreEqual(5, m_editor.GetDiagramEntityContainer()->GetSize());

            m_editor.Undo();

            Assert::AreEqual(9, m_editor.GetDiagramEntityContainer()->GetSize());

        }

        TEST_METHOD(Redo_WhenInvoked_RestoreChanges) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.DeleteAllSelected();

            Assert::AreEqual(5, m_editor.GetDiagramEntityContainer()->GetSize());

            m_editor.Undo();

            Assert::AreEqual(9, m_editor.GetDiagramEntityContainer()->GetSize());

            m_editor.Redo();

            Assert::AreEqual(5, m_editor.GetDiagramEntityContainer()->GetSize());

        }

#pragma endregion

#pragma region SelectionTests

        TEST_METHOD(SelectAll_WhenInvoked_SelectAllElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            
            m_editor.SelectAll();

            Assert::AreEqual(9, m_editor.GetSelectCount());

        }
        
        TEST_METHOD(UnselectAll_WhenInvoked_SelectNoElements) {

            m_a->Select(TRUE);
            m_b1->Select(TRUE);

            m_editor.UnselectAll();

            Assert::AreEqual(0, m_editor.GetSelectCount());

        }

#pragma endregion

        //TODO: OnXX

#pragma region GDISmokeTests

        TEST_METHOD(Draw_WhenCalledWithMemoryDC_DoesNotCrash) {
            
            // Create memory DC
            CDC memDC;
            CBitmap bmp;
            memDC.CreateCompatibleDC(NULL);
            bmp.CreateCompatibleBitmap(&memDC, 2000, 2000);
            memDC.SelectObject(&bmp);

            CRect rect(0, 0, 2000, 2000);

            m_editor.SetPageLayout(&memDC);
            m_editor.ShowPageBreaks(TRUE);

            m_editor.Draw(&memDC, rect);

        }

#pragma endregion


    };

}
