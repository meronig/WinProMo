#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoEntityContainer.h"
#include "../../src/ProMoEditor/ProMoClipboardHandler.h"
#include "../../src/ProMoEditor/ProMoEdgeView.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include "../WinProMoTests.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoEntityContainerTests
{

    TEST_CLASS(CProMoEntityContainerTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region ConstructorTests

        TEST_METHOD(Constructor_WhenInvokedWithoutParameters_SetDefaultModelType)
        {
            CProMoEntityContainer c;

            Assert::AreEqual(CString("promo"), c.GetModelType());
            Assert::AreEqual(10, c.GetUndoStackSize());
            TestHelpers::PointerAssert::IsNull(c.GetClipboardHandler());
            
        }

        TEST_METHOD(Constructor_WhenInvokedWithParameters_SetCustomModelTypeAndClipboardHandler)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

            Assert::AreEqual(CString("custom"), c.GetModelType());
            Assert::AreEqual(10, c.GetUndoStackSize());
            TestHelpers::PointerAssert::AreEqual(&clip, dynamic_cast<CProMoClipboardHandler*>(c.GetClipboardHandler()));

        }

#pragma endregion

#pragma region RemovalTests

        TEST_METHOD(RemoveAt_WhenInvoked_RemoveElement)
        {
            CProMoEntityContainer c;
            CProMoBlockView* block = new CProMoBlockView();
            CProMoEdgeView* edge = new CProMoEdgeView();

            c.Add(block);
            c.Add(edge);

            c.RemoveAt(0);
            c.RemoveAt(0);

            Assert::AreEqual(0, c.GetSize());
        }

        TEST_METHOD(RemoveAt_WhenInvokedOverParentBlock_RemoveSubBlocks)
        {
            CProMoEntityContainer c;
            CProMoBlockView* parent = new CProMoBlockView();
            CProMoBlockView* child = new CProMoBlockView();
            child->GetModel()->SetParentBlock(parent->GetModel());

            c.Add(parent);
            c.Add(child);

            c.RemoveAt(0);
            
            Assert::AreEqual(0, c.GetSize());
        }

#pragma endregion

#pragma region SelectionTests

        TEST_METHOD(SetTarget_WhenInvoked_MarkBlockAsTarget)
        {
            CProMoEntityContainer c;
            CProMoBlockView* block = new CProMoBlockView();
            CProMoBlockView* block2 = new CProMoBlockView();

            c.Add(block);
            c.Add(block2);

            c.SetTarget(block, TRUE);
            
            Assert::IsTrue(block->IsTarget());
            Assert::IsFalse(block2->IsTarget());
        }

        TEST_METHOD(GetTarget_WhenInvoked_ReturnTargetBlock)
        {
            CProMoEntityContainer c;
            CProMoBlockView* block = new CProMoBlockView();
            CProMoBlockView* block2 = new CProMoBlockView();

            c.Add(block);
            c.Add(block2);

            block->SetTarget(TRUE);
            
            TestHelpers::PointerAssert::AreEqual(block, c.GetTarget());
        }

        TEST_METHOD(GetSelectCount_WhenInvoked_CountOnlyBlocks)
        {
            CProMoEntityContainer c;
            CProMoBlockView* block = new CProMoBlockView();
            CProMoEdgeView* edge = new CProMoEdgeView();

            c.Add(block);
            c.Add(edge);
            
            block->Select(TRUE);
            edge->Select(TRUE);

            Assert::AreEqual(1, c.GetSelectCount());
        }

#pragma endregion

#pragma region OrderingTest

        TEST_METHOD(Reorder_WhenInvoked_ReorderElements)
        {
            CProMoEntityContainer c;
            
            CProMoBlockView* a = new CProMoBlockView();
            CProMoBlockView* a1 = new CProMoBlockView();
            CProMoBlockView* a2 = new CProMoBlockView();
            CProMoBlockView* b = new CProMoBlockView();
            CProMoBlockView* b1 = new CProMoBlockView();
            CProMoBlockView* b2 = new CProMoBlockView();

            CProMoEdgeView* x = new CProMoEdgeView();
            CProMoEdgeView* y = new CProMoEdgeView();
            CProMoEdgeView* z = new CProMoEdgeView();

            a1->GetModel()->SetParentBlock(a->GetModel());
            a2->GetModel()->SetParentBlock(a->GetModel());
            b1->GetModel()->SetParentBlock(b->GetModel());
            b2->GetModel()->SetParentBlock(b->GetModel());
            
            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);
            z->SetSource(b);
            z->SetDestination(a2);
            
            c.Add(x);
            c.Add(y);
            c.Add(z);
            c.Add(a1);
            c.Add(a2);
            c.Add(a);
            c.Add(b1);
            c.Add(b2);
            c.Add(b);
            
            c.Reorder();

            TestHelpers::PointerAssert::AreEqual(a, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(0)));
            TestHelpers::PointerAssert::AreEqual(a1, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(1)));
            TestHelpers::PointerAssert::AreEqual(a2, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(2)));
            TestHelpers::PointerAssert::AreEqual(b, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(3)));
            TestHelpers::PointerAssert::AreEqual(z, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(4)));
            TestHelpers::PointerAssert::AreEqual(b1, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(5)));
            TestHelpers::PointerAssert::AreEqual(y, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(6)));
            TestHelpers::PointerAssert::AreEqual(x, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(7)));
            TestHelpers::PointerAssert::AreEqual(b2, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(8)));
            
        }

#pragma endregion
#pragma region UndoTest

        TEST_METHOD(Undo_WhenInvoked_RevertChanges)
        {
            CProMoEntityContainer c;
            
            CProMoBlockView* a = new CProMoBlockView();
            CProMoBlockView* a1 = new CProMoBlockView();
            CProMoBlockView* a2 = new CProMoBlockView();
            CProMoBlockView* b = new CProMoBlockView();
            CProMoBlockView* b1 = new CProMoBlockView();
            CProMoBlockView* b2 = new CProMoBlockView();

            CProMoEdgeView* x = new CProMoEdgeView();
            CProMoEdgeView* y = new CProMoEdgeView();
            CProMoEdgeView* z = new CProMoEdgeView();

            c.Add(a);
            c.Add(a1);
            c.Add(a2);
            a1->GetModel()->SetParentBlock(a->GetModel());
            a2->GetModel()->SetParentBlock(a->GetModel());
            c.Snapshot();

            c.Add(x);
            c.Add(y);
            c.Add(b1);
            
            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);
            c.Snapshot();

            c.Add(z);
            c.Add(b2);
            c.Add(b);
            b1->GetModel()->SetParentBlock(b->GetModel());
            b2->GetModel()->SetParentBlock(b->GetModel());
            z->SetSource(b);
            z->SetDestination(a2);
            
            Assert::AreEqual((INT_PTR)9, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsFalse(c.IsRedoPossible());

            c.Undo();

            Assert::AreEqual((INT_PTR)6, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());

            c.Undo();

            Assert::AreEqual((INT_PTR)3, c.GetData()->GetSize());
            Assert::IsFalse(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());
        }

        TEST_METHOD(Redo_WhenInvoked_RestoreChanges)
        {
            CProMoEntityContainer c;

            CProMoBlockView* a = new CProMoBlockView();
            CProMoBlockView* a1 = new CProMoBlockView();
            CProMoBlockView* a2 = new CProMoBlockView();
            CProMoBlockView* b = new CProMoBlockView();
            CProMoBlockView* b1 = new CProMoBlockView();
            CProMoBlockView* b2 = new CProMoBlockView();

            CProMoEdgeView* x = new CProMoEdgeView();
            CProMoEdgeView* y = new CProMoEdgeView();
            CProMoEdgeView* z = new CProMoEdgeView();

            c.Add(a);
            c.Add(a1);
            c.Add(a2);
            a1->GetModel()->SetParentBlock(a->GetModel());
            a2->GetModel()->SetParentBlock(a->GetModel());
            c.Snapshot();

            c.Add(x);
            c.Add(y);
            c.Add(b1);
            
            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);
            c.Snapshot();

            c.Add(z);
            c.Add(b2);
            c.Add(b);
            b1->GetModel()->SetParentBlock(b->GetModel());
            b2->GetModel()->SetParentBlock(b->GetModel());
            z->SetSource(b);
            z->SetDestination(a2);

            Assert::AreEqual((INT_PTR)9, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsFalse(c.IsRedoPossible());

            c.Undo();
            c.Undo();

            Assert::AreEqual((INT_PTR)3, c.GetData()->GetSize());
            Assert::IsFalse(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());

            c.Redo();

            Assert::AreEqual((INT_PTR)6, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());

            c.Redo();
            Assert::AreEqual((INT_PTR)9, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsFalse(c.IsRedoPossible());

        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(GetString_WhenInvoked_ReturnCorrectString)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

            c.SetVirtualSize(CSize(300, 400));
            
            Assert::AreEqual(CString("custom:300,400;"), c.GetString());

        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParseCorrectly)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

            BOOL result = c.FromString(CString("custom:300,400;"));

            Assert::IsTrue(result);
            Assert::AreEqual(CString("custom"), c.GetModelType());
            Assert::AreEqual((LONG)300, c.GetVirtualSize().cx);
            Assert::AreEqual((LONG)400, c.GetVirtualSize().cy);

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParseCorrectly)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

            BOOL result = c.FromString(CString("custom:300,400,Extra1,Extra2;"));

            Assert::IsTrue(result);
            Assert::AreEqual(CString("custom"), c.GetModelType());
            Assert::AreEqual((LONG)300, c.GetVirtualSize().cx);
            Assert::AreEqual((LONG)400, c.GetVirtualSize().cy);

        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

            BOOL result = c.FromString(CString("wrong_type:300,400;"));

            Assert::IsFalse(result);
        }

        TEST_METHOD(Load_WhenStringArrayIsPassed_CreateDiagramElements)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

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

            c.Load(diagram, &factory);

            Assert::AreEqual(9, c.GetSize());
            Assert::AreEqual(CString("custom"), c.GetModelType());
            Assert::AreEqual((LONG)762, c.GetVirtualSize().cx);
            Assert::AreEqual((LONG)1091, c.GetVirtualSize().cy);

            CProMoBlockView* a = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("6")));
            CProMoBlockView* a1 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("32")));
            CProMoBlockView* a2 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("74")));
            CProMoBlockView* b = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("17")));
            CProMoBlockView* b1 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("51")));
            CProMoBlockView* b2 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("121")));

            CProMoEdgeView* x = dynamic_cast<CProMoEdgeView*>(c.GetNamedView(CString("392")));
            CProMoEdgeView* y = dynamic_cast<CProMoEdgeView*>(c.GetNamedView(CString("452")));
            CProMoEdgeView* z = dynamic_cast<CProMoEdgeView*>(c.GetNamedView(CString("523")));

            TestHelpers::PointerAssert::IsNotNull(a);
            TestHelpers::PointerAssert::IsNotNull(a1);
            TestHelpers::PointerAssert::IsNotNull(a2);
            TestHelpers::PointerAssert::IsNotNull(b);
            TestHelpers::PointerAssert::IsNotNull(b1);
            TestHelpers::PointerAssert::IsNotNull(b2);

            TestHelpers::PointerAssert::IsNotNull(x);
            TestHelpers::PointerAssert::IsNotNull(y);
            TestHelpers::PointerAssert::IsNotNull(z);
        }

        TEST_METHOD(Load_WhenStringArrayIsPassed_LinkDiagramElements)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

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

            c.Load(diagram, &factory);

            CProMoBlockView* a = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("6")));
            CProMoBlockView* a1 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("32")));
            CProMoBlockView* a2 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("74")));
            CProMoBlockView* b = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("17")));
            CProMoBlockView* b1 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("51")));
            CProMoBlockView* b2 = dynamic_cast<CProMoBlockView*>(c.GetNamedView(CString("121")));

            CProMoEdgeView* x = dynamic_cast<CProMoEdgeView*>(c.GetNamedView(CString("392")));
            CProMoEdgeView* y = dynamic_cast<CProMoEdgeView*>(c.GetNamedView(CString("452")));
            CProMoEdgeView* z = dynamic_cast<CProMoEdgeView*>(c.GetNamedView(CString("523")));

            TestHelpers::PointerAssert::AreEqual(x, dynamic_cast<CProMoEdgeView*>(y->GetSource()));
            TestHelpers::PointerAssert::AreEqual(y, dynamic_cast<CProMoEdgeView*>(x->GetDestination()));
            TestHelpers::PointerAssert::IsNull(x->GetSource());
            TestHelpers::PointerAssert::IsNull(y->GetDestination());
            TestHelpers::PointerAssert::AreEqual(x->GetModel(), y->GetModel());
            TestHelpers::PointerAssert::IsNull(z->GetSource());
            TestHelpers::PointerAssert::IsNull(z->GetDestination());
            TestHelpers::PointerAssert::AreNotEqual(z->GetModel(), y->GetModel());

            TestHelpers::PointerAssert::AreEqual(a, a1->GetModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::AreEqual(a, a2->GetModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::AreEqual(b, b1->GetModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::AreEqual(b, b2->GetModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::IsNull(a->GetModel()->GetParentBlock());
            TestHelpers::PointerAssert::IsNull(b->GetModel()->GetParentBlock());
            
            TestHelpers::PointerAssert::AreEqual(a->GetModel(), dynamic_cast<CProMoBlockModel*>(x->GetModel()->GetSource()));
            TestHelpers::PointerAssert::AreEqual(b1->GetModel(), dynamic_cast<CProMoBlockModel*>(x->GetModel()->GetDestination()));
            TestHelpers::PointerAssert::AreEqual(b->GetModel(), dynamic_cast<CProMoBlockModel*>(z->GetModel()->GetSource()));
            TestHelpers::PointerAssert::AreEqual(a2->GetModel(), dynamic_cast<CProMoBlockModel*>(z->GetModel()->GetDestination()));

        }

        TEST_METHOD(Save_WhenInvoked_CreateStringArray)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(CString("custom"), &clip);

            c.SetVirtualSize(CSize(800, 1000));

            CList <CString, CString&>  diagram;
            CProMoControlFactory factory;

            CProMoBlockView* a = new CProMoBlockView();
            CProMoBlockView* a1 = new CProMoBlockView();
            CProMoBlockView* a2 = new CProMoBlockView();
            CProMoBlockView* b = new CProMoBlockView();
            CProMoBlockView* b1 = new CProMoBlockView();
            CProMoBlockView* b2 = new CProMoBlockView();

            CProMoEdgeView* x = new CProMoEdgeView();
            CProMoEdgeView* y = new CProMoEdgeView();
            CProMoEdgeView* z = new CProMoEdgeView();

            a1->GetModel()->SetParentBlock(a->GetModel());
            a2->GetModel()->SetParentBlock(a->GetModel());
            b1->GetModel()->SetParentBlock(b->GetModel());
            b2->GetModel()->SetParentBlock(b->GetModel());
            
            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);
            z->SetSource(b);
            z->SetDestination(a2);
            
            a->SetName(CString("6"));
            a1->SetName(CString("32"));
            a2->SetName(CString("74"));
            b->SetName(CString("17"));
            b1->SetName(CString("51"));
            b2->SetName(CString("121"));
            x->SetName(CString("392"));
            y->SetName(CString("452"));
            z->SetName(CString("523"));
            
            a->GetModel()->SetName(CString("4"));
            a1->GetModel()->SetName(CString("30"));
            a2->GetModel()->SetName(CString("72"));
            b->GetModel()->SetName(CString("15"));
            b1->GetModel()->SetName(CString("49"));
            b2->GetModel()->SetName(CString("119"));
            x->GetModel()->SetName(CString("391"));
            z->GetModel()->SetName(CString("522"));

            a->SetTitle(CString("A"));
            a1->SetTitle(CString("A1"));
            a2->SetTitle(CString("A2"));
            b->SetTitle(CString("B"));
            b1->SetTitle(CString("B1"));
            b2->SetTitle(CString("B2"));
            x->SetTitle(CString("x"));
            y->SetTitle(CString("y"));
            z->SetTitle(CString("z"));
                
            a->SetRect(183.000000, 105.000000, 490.000000, 163.000000);
            a1->SetRect(217.000000, 126.000000, 345.000000, 158.000000);
            a2->SetRect(357.000000, 122.000000, 485.000000, 154.000000);
            b->SetRect(316.000000, 238.000000, 484.000000, 344.000000);
            b1->SetRect(340.000000, 266.000000, 468.000000, 298.000000);
            b2->SetRect(340.000000, 303.000000, 468.000000, 335.000000);
            x->SetRect(CRect(211.000000, 163.000000, 210.000000, 275.000000));
            y->SetRect(CRect(210.000000, 275.000000, 340.000000, 266.000000));
            z->SetRect(CRect(438.000000, 237.000000, 447.000000, 154.000000));

            c.Add(a);
            c.Add(a1);
            c.Add(a2);
            c.Add(b);
            c.Add(b1);
            c.Add(b2);
            c.Add(x);
            c.Add(y);
            c.Add(z);

            diagram.AddTail(CString("custom:800,1000;"));
            diagram.AddTail(CString("promo_block_view:6,183.000000,105.000000,490.000000,163.000000,A,0,4;"));
            diagram.AddTail(CString("promo_block_view:32,217.000000,126.000000,345.000000,158.000000,A1,0,30;"));
            diagram.AddTail(CString("promo_block_view:74,357.000000,122.000000,485.000000,154.000000,A2,0,72;"));
            diagram.AddTail(CString("promo_block_view:17,316.000000,238.000000,484.000000,344.000000,B,0,15;"));
            diagram.AddTail(CString("promo_edge_view:523,438.000000,237.000000,447.000000,154.000000,z,0,522,,;"));
            diagram.AddTail(CString("promo_block_view:51,340.000000,266.000000,468.000000,298.000000,B1,0,49;"));
            diagram.AddTail(CString("promo_edge_view:392,211.000000,163.000000,210.000000,275.000000,x,0,391,,452;"));
            diagram.AddTail(CString("promo_edge_view:452,210.000000,275.000000,340.000000,266.000000,y,0,391,392,;"));
            diagram.AddTail(CString("promo_block_view:121,340.000000,303.000000,468.000000,335.000000,B2,0,119;"));
            diagram.AddTail(CString("promo_block_model:4,;"));
            diagram.AddTail(CString("promo_block_model:30,4;"));
            diagram.AddTail(CString("promo_block_model:72,4;"));
            diagram.AddTail(CString("promo_block_model:15,;"));
            diagram.AddTail(CString("promo_edge_model:522,15,72;"));
            diagram.AddTail(CString("promo_block_model:49,15;"));
            diagram.AddTail(CString("promo_edge_model:391,4,49;"));
            diagram.AddTail(CString("promo_block_model:119,15;"));

            CStringArray result;

            c.Save(result);

            Assert::AreEqual((INT_PTR)18, result.GetSize());

            for (unsigned int i = 0; i < result.GetSize(); i++) {
                CString value = result.GetAt(i);
                Assert::IsNotNull(diagram.Find(value),"Could not find string "+value+" in serialized diagram");
            }

        }

#pragma endregion


    };

}
