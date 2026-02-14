#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoEntityContainer.h"
#include "../../src/ProMoEditor/ProMoClipboardHandler.h"
#include "../../src/ProMoEditor/ProMoEdgeView.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include "../../src/ProMoEditor/ProMoLabel.h"
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
            CProMoEntityContainer c(new CProMoControlFactory);

            Assert::AreEqual(CString("promo"), c.GetModelType());
            Assert::AreEqual(10, c.GetUndoStackSize());
            TestHelpers::PointerAssert::IsNull(c.GetClipboardHandler());
            
        }

        TEST_METHOD(Constructor_WhenInvokedWithParameters_SetCustomModelTypeAndClipboardHandler)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

            Assert::AreEqual(CString("custom"), c.GetModelType());
            Assert::AreEqual(10, c.GetUndoStackSize());
            TestHelpers::PointerAssert::AreEqual(&clip, dynamic_cast<CProMoClipboardHandler*>(c.GetClipboardHandler()));

        }

#pragma endregion

#pragma region RemovalTests

        TEST_METHOD(RemoveAt_WhenInvoked_RemoveElementAndLabels)
        {
            CProMoEntityContainer c(new CProMoControlFactory);
            CProMoBlockView* block = new CProMoBlockView();
            CProMoEdgeView* edge = new CProMoEdgeView();

            CObArray labels;
            block->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            edge->GetModel()->RecreateLabels(labels);
            CProMoLabel* le = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            c.Add(block);
            c.Add(edge);
            c.Add(lb);
            c.Add(le);

            c.RemoveAt(0);
            c.RemoveAt(0);

            Assert::AreEqual(0, c.GetSize());
        }

        TEST_METHOD(RemoveAt_WhenInvokedOverParentBlock_RemoveSubBlocks)
        {
            CProMoEntityContainer c(new CProMoControlFactory);
            CProMoBlockView* parent = new CProMoBlockView();
            CProMoBlockView* child = new CProMoBlockView();
            parent->LinkSubBlock(child);

            c.Add(parent);
            c.Add(child);

            c.RemoveAt(0);
            
            Assert::AreEqual(0, c.GetSize());
        }

#pragma endregion

#pragma region SelectionTests

        TEST_METHOD(SetTarget_WhenInvoked_MarkBlockAsTarget)
        {
            CProMoEntityContainer c(new CProMoControlFactory);
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
            CProMoEntityContainer c(new CProMoControlFactory);
            CProMoBlockView* block = new CProMoBlockView();
            CProMoBlockView* block2 = new CProMoBlockView();

            c.Add(block);
            c.Add(block2);

            block->SetTarget(TRUE);
            
            TestHelpers::PointerAssert::AreEqual(block, c.GetTarget());
        }

        TEST_METHOD(GetSelectCount_WhenInvoked_CountOnlyBlocks)
        {
            CProMoEntityContainer c(new CProMoControlFactory);
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
            CProMoEntityContainer c(new CProMoControlFactory);
            
            CProMoBlockView* a = new CProMoBlockView();
            CProMoBlockView* a1 = new CProMoBlockView();
            CProMoBlockView* a2 = new CProMoBlockView();
            CProMoBlockView* b = new CProMoBlockView();
            CProMoBlockView* b1 = new CProMoBlockView();
            CProMoBlockView* b2 = new CProMoBlockView();

            CProMoEdgeView* w = new CProMoEdgeView();
            CProMoEdgeView* x = new CProMoEdgeView();
            CProMoEdgeView* y = new CProMoEdgeView();
            CProMoEdgeView* z = new CProMoEdgeView();
            CProMoEdgeView* m = new CProMoEdgeView();
            CProMoEdgeView* n = new CProMoEdgeView();

            CProMoLabel* l = new CProMoLabel();
            
            a->LinkSubBlock(a1);
            a->LinkSubBlock(a2);
            b->LinkSubBlock(b1);
            b->LinkSubBlock(b2);
            
            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);
            z->SetSource(b);
            z->SetDestination(a2);

            m->SetSource(a1);
            n->SetDestination(b2);

            CObArray labels;
            a->GetModel()->RecreateLabels(labels);
            CProMoLabel* la = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a1->GetModel()->RecreateLabels(labels);
            CProMoLabel* la1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a2->GetModel()->RecreateLabels(labels);
            CProMoLabel* la2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b1->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b2->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            w->GetModel()->RecreateLabels(labels);
            CProMoLabel* lw = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            x->GetModel()->RecreateLabels(labels);
            CProMoLabel* lx = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            z->GetModel()->RecreateLabels(labels);
            CProMoLabel* lz = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            m->GetModel()->RecreateLabels(labels);
            CProMoLabel* lm = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();
            
            n->GetModel()->RecreateLabels(labels);
            CProMoLabel* ln = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();
            
            c.Add(l);
            c.Add(x);
            c.Add(y);
            c.Add(z);
            c.Add(a1);
            c.Add(a2);
            c.Add(a);
            c.Add(w);
            c.Add(b1);
            c.Add(b2);
            c.Add(b);
            c.Add(m);
            c.Add(n);

            c.Add(la);
            c.Add(la1);
            c.Add(la2);
            c.Add(lb);
            c.Add(lb1);
            c.Add(lb2);
            c.Add(lw);
            c.Add(lx);
            c.Add(lz);
            c.Add(lm);
            c.Add(ln);

            c.Reorder();

            TestHelpers::PointerAssert::AreEqual(l, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(0)));
            TestHelpers::PointerAssert::AreEqual(a, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(1)));
            TestHelpers::PointerAssert::AreEqual(la, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(2)));
            TestHelpers::PointerAssert::AreEqual(a1, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(3)));
            TestHelpers::PointerAssert::AreEqual(m, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(4)));
            TestHelpers::PointerAssert::AreEqual(lm, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(5)));
            TestHelpers::PointerAssert::AreEqual(la1, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(6)));
            TestHelpers::PointerAssert::AreEqual(a2, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(7)));
            TestHelpers::PointerAssert::AreEqual(la2, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(8)));
            TestHelpers::PointerAssert::AreEqual(w, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(9)));
            TestHelpers::PointerAssert::AreEqual(lw, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(10)));
            TestHelpers::PointerAssert::AreEqual(b, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(11)));
            TestHelpers::PointerAssert::AreEqual(z, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(12)));
            TestHelpers::PointerAssert::AreEqual(lz, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(13)));
            TestHelpers::PointerAssert::AreEqual(lb, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(14)));
            TestHelpers::PointerAssert::AreEqual(b1, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(15)));
            TestHelpers::PointerAssert::AreEqual(y, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(16)));
            TestHelpers::PointerAssert::AreEqual(x, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(17)));
            TestHelpers::PointerAssert::AreEqual(lx, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(18)));
            TestHelpers::PointerAssert::AreEqual(lb1, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(19)));
            TestHelpers::PointerAssert::AreEqual(b2, dynamic_cast<CProMoBlockView*>(c.GetData()->GetAt(20)));
            TestHelpers::PointerAssert::AreEqual(n, dynamic_cast<CProMoEdgeView*>(c.GetData()->GetAt(21)));
            TestHelpers::PointerAssert::AreEqual(ln, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(22)));
            TestHelpers::PointerAssert::AreEqual(lb2, dynamic_cast<CProMoLabel*>(c.GetData()->GetAt(23)));
            

        }

#pragma endregion
#pragma region UndoTest

        TEST_METHOD(Undo_WhenInvoked_RevertChanges)
        {
            CProMoEntityContainer c(new CProMoControlFactory);
            
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
            a->LinkSubBlock(a1);
            a->LinkSubBlock(a2);
            
            CObArray labels;
            a->GetModel()->RecreateLabels(labels);
            CProMoLabel* la = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a1->GetModel()->RecreateLabels(labels);
            CProMoLabel* la1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a2->GetModel()->RecreateLabels(labels);
            CProMoLabel* la2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            c.Snapshot();

            c.Add(x);
            c.Add(y);
            c.Add(b1);
            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);

            x->GetModel()->RecreateLabels(labels);
            CProMoLabel* lx = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b1->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            c.Snapshot();

            c.Add(z);
            c.Add(b2);
            c.Add(b);
            b->LinkSubBlock(b1);
            b->LinkSubBlock(b2);
            z->SetSource(b);
            z->SetDestination(a2);

            z->GetModel()->RecreateLabels(labels);
            CProMoLabel* lz = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b2->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            Assert::AreEqual((INT_PTR)17, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsFalse(c.IsRedoPossible());

            c.Undo();

            Assert::AreEqual((INT_PTR)11, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());

            c.Undo();

            Assert::AreEqual((INT_PTR)6, c.GetData()->GetSize());
            Assert::IsFalse(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());
        }

        TEST_METHOD(Redo_WhenInvoked_RestoreChanges)
        {
            CProMoEntityContainer c(new CProMoControlFactory);

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
            a->LinkSubBlock(a1);
            a->LinkSubBlock(a2);

            CObArray labels;
            a->GetModel()->RecreateLabels(labels);
            CProMoLabel* la = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a1->GetModel()->RecreateLabels(labels);
            CProMoLabel* la1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a2->GetModel()->RecreateLabels(labels);
            CProMoLabel* la2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            c.Snapshot();

            c.Add(x);
            c.Add(y);
            c.Add(b1);
            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);

            x->GetModel()->RecreateLabels(labels);
            CProMoLabel* lx = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b1->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            c.Snapshot();

            c.Add(z);
            c.Add(b2);
            c.Add(b);
            b->LinkSubBlock(b1);
            b->LinkSubBlock(b2);
            z->SetSource(b);
            z->SetDestination(a2);

            z->GetModel()->RecreateLabels(labels);
            CProMoLabel* lz = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b2->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            Assert::AreEqual((INT_PTR)17, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsFalse(c.IsRedoPossible());

            c.Undo();
            c.Undo();

            Assert::AreEqual((INT_PTR)6, c.GetData()->GetSize());
            Assert::IsFalse(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());

            c.Redo();

            Assert::AreEqual((INT_PTR)11, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsTrue(c.IsRedoPossible());

            c.Redo();
            Assert::AreEqual((INT_PTR)17, c.GetData()->GetSize());
            Assert::IsTrue(c.IsUndoPossible());
            Assert::IsFalse(c.IsRedoPossible());

        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(GetString_WhenInvoked_ReturnCorrectString)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

            c.SetVirtualSize(CSize(300, 400));
            
            Assert::AreEqual(CString("custom:300,400;"), c.GetString());

        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParseCorrectly)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

            BOOL result = c.FromString(CString("custom:300,400;"));

            Assert::IsTrue(result);
            Assert::AreEqual(CString("custom"), c.GetModelType());
            Assert::AreEqual((LONG)300, c.GetVirtualSize().cx);
            Assert::AreEqual((LONG)400, c.GetVirtualSize().cy);

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParseCorrectly)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

            BOOL result = c.FromString(CString("custom:300,400,Extra1,Extra2;"));

            Assert::IsTrue(result);
            Assert::AreEqual(CString("custom"), c.GetModelType());
            Assert::AreEqual((LONG)300, c.GetVirtualSize().cx);
            Assert::AreEqual((LONG)400, c.GetVirtualSize().cy);

        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

            BOOL result = c.FromString(CString("wrong_type:300,400;"));

            Assert::IsFalse(result);
        }

        TEST_METHOD(Load_WhenStringArrayIsPassed_CreateDiagramElements)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

            CStringArray diagram;
            
            diagram.Add(CString("custom:762,1091;"));
            diagram.Add(CString("promo_block_view:6,183.000000,105.000000,490.000000,163.000000,,0,4;"));
            diagram.Add(CString("promo_block_view:32,217.000000,126.000000,345.000000,158.000000,,0,30;"));
            diagram.Add(CString("promo_block_view:74,357.000000,122.000000,485.000000,154.000000,,0,72;"));
            diagram.Add(CString("promo_block_view:17,316.000000,238.000000,484.000000,344.000000,,0,15;"));
            diagram.Add(CString("promo_edge_view:523,438.000000,237.000000,447.000000,154.000000,,0,522,,;"));
            diagram.Add(CString("promo_block_view:51,340.000000,266.000000,468.000000,298.000000,,0,49;"));
            diagram.Add(CString("promo_edge_view:392,211.000000,163.000000,210.000000,275.000000,,0,391,,452;"));
            diagram.Add(CString("promo_edge_view:452,210.000000,275.000000,340.000000,266.000000,,0,391,392,;"));
            diagram.Add(CString("promo_block_view:121,340.000000,328.000000,468.000000,360.000000,,0,119;"));
            diagram.Add(CString("promo_block_model:4,,0;"));
            diagram.Add(CString("promo_block_model:30,4,1;"));
            diagram.Add(CString("promo_block_model:72,4,1;"));
            diagram.Add(CString("promo_block_model:15,,0;"));
            diagram.Add(CString("promo_edge_model:522,15,72;"));
            diagram.Add(CString("promo_block_model:49,15,1;"));
            diagram.Add(CString("promo_edge_model:391,4,49;"));
            diagram.Add(CString("promo_block_model:119,15,12;"));
            diagram.Add(CString("promo_label:3620,333.000000,105.000000,340.000000,120.000000,,0,4,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3835,274.000000,135.500000,288.000000,150.500000,,0,30,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:4050,414.000000,130.500000,428.000000,145.500000,,0,72,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:914,460.000000,185.000000,467.000000,200.000000,,0,522,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,20.000000,-3.500000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3405,396.500000,238.000000,403.500000,253.000000,,0,15,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:965,186.000000,203.000000,193.000000,218.000000,,0,391,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,-21.000000,-8.500000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:2975,397.000000,274.500000,411.000000,289.500000,,0,49,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3136,397.000000,336.500000,411.000000,351.500000,,0,119,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:1174,97.000000,47.000000,153.000000,62.000000,My Label,0,,,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("property:Title,3,A,4;"));
            diagram.Add(CString("property:Title,3,A1,30;"));
            diagram.Add(CString("property:Title,3,A2,72;"));
            diagram.Add(CString("property:Title,3,B,15;"));
            diagram.Add(CString("property:Title,3,z,522;"));
            diagram.Add(CString("property:Title,3,B1,49;"));
            diagram.Add(CString("property:Title,3,x,391;"));
            diagram.Add(CString("property:Title,3,B2,119;"));

            c.Load(diagram);

            Assert::AreEqual(18, c.GetSize());
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
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

            CStringArray diagram;
            
            diagram.Add(CString("custom:762,1091;"));
            diagram.Add(CString("promo_block_view:6,183.000000,105.000000,490.000000,163.000000,,0,4;"));
            diagram.Add(CString("promo_block_view:32,217.000000,126.000000,345.000000,158.000000,,0,30;"));
            diagram.Add(CString("promo_block_view:74,357.000000,122.000000,485.000000,154.000000,,0,72;"));
            diagram.Add(CString("promo_block_view:17,316.000000,238.000000,484.000000,344.000000,,0,15;"));
            diagram.Add(CString("promo_edge_view:523,438.000000,237.000000,447.000000,154.000000,,0,522,,;"));
            diagram.Add(CString("promo_block_view:51,340.000000,266.000000,468.000000,298.000000,,0,49;"));
            diagram.Add(CString("promo_edge_view:392,211.000000,163.000000,210.000000,275.000000,,0,391,,452;"));
            diagram.Add(CString("promo_edge_view:452,210.000000,275.000000,340.000000,266.000000,,0,391,392,;"));
            diagram.Add(CString("promo_block_view:121,340.000000,328.000000,468.000000,360.000000,,0,119;"));
            diagram.Add(CString("promo_block_model:4,,0;"));
            diagram.Add(CString("promo_block_model:30,4,1;"));
            diagram.Add(CString("promo_block_model:72,4,1;"));
            diagram.Add(CString("promo_block_model:15,,0;"));
            diagram.Add(CString("promo_edge_model:522,15,72;"));
            diagram.Add(CString("promo_block_model:49,15,1;"));
            diagram.Add(CString("promo_edge_model:391,4,49;"));
            diagram.Add(CString("promo_block_model:119,15,12;"));
            diagram.Add(CString("promo_label:3620,333.000000,105.000000,340.000000,120.000000,,0,4,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3835,274.000000,135.500000,288.000000,150.500000,,0,30,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:4050,414.000000,130.500000,428.000000,145.500000,,0,72,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:914,460.000000,185.000000,467.000000,200.000000,,0,522,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,20.000000,-3.500000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3405,396.500000,238.000000,403.500000,253.000000,,0,15,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:965,186.000000,203.000000,193.000000,218.000000,,0,391,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,-21.000000,-8.500000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:2975,397.000000,274.500000,411.000000,289.500000,,0,49,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:3136,397.000000,336.500000,411.000000,351.500000,,0,119,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("promo_label:1174,97.000000,47.000000,153.000000,62.000000,My Label,0,,,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.Add(CString("property:Title,3,A,4;"));
            diagram.Add(CString("property:Title,3,A1,30;"));
            diagram.Add(CString("property:Title,3,A2,72;"));
            diagram.Add(CString("property:Title,3,B,15;"));
            diagram.Add(CString("property:Title,3,z,522;"));
            diagram.Add(CString("property:Title,3,B1,49;"));
            diagram.Add(CString("property:Title,3,x,391;"));
            diagram.Add(CString("property:Title,3,B2,119;"));

            c.Load(diagram);

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
            TestHelpers::PointerAssert::AreEqual(a, dynamic_cast<CProMoBlockView* > (x->GetSource()));
            TestHelpers::PointerAssert::AreEqual(b1, dynamic_cast<CProMoBlockView*>(y->GetDestination()));
            TestHelpers::PointerAssert::AreEqual(x->GetModel(), y->GetModel());
            TestHelpers::PointerAssert::AreEqual(b, dynamic_cast<CProMoBlockView*> (z->GetSource()));
            TestHelpers::PointerAssert::AreEqual(a2, dynamic_cast<CProMoBlockView*>(z->GetDestination()));
            TestHelpers::PointerAssert::AreNotEqual(z->GetModel(), y->GetModel());

            TestHelpers::PointerAssert::AreEqual(a, a1->GetBlockModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::AreEqual(a, a2->GetBlockModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::AreEqual(b, b1->GetBlockModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::AreEqual(b, b2->GetBlockModel()->GetParentBlock()->GetMainView());
            TestHelpers::PointerAssert::IsNull(a->GetBlockModel()->GetParentBlock());
            TestHelpers::PointerAssert::IsNull(b->GetBlockModel()->GetParentBlock());
            
            TestHelpers::PointerAssert::AreEqual(a->GetBlockModel(), x->GetEdgeModel()->GetSource());
            TestHelpers::PointerAssert::AreEqual(b1->GetBlockModel(), x->GetEdgeModel()->GetDestination());
            TestHelpers::PointerAssert::AreEqual(b->GetBlockModel(), z->GetEdgeModel()->GetSource());
            TestHelpers::PointerAssert::AreEqual(a2->GetBlockModel(), z->GetEdgeModel()->GetDestination());

        }

        TEST_METHOD(Save_WhenInvoked_CreateStringArray)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer c(new CProMoControlFactory, CString("custom"), &clip);

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

            a->LinkSubBlock(a1);
            a->LinkSubBlock(a2);
            b->LinkSubBlock(b1);
            b->LinkBoundaryBlock(b2, DEHT_BOTTOM);

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

            a->GetModel()->SetPropertyValue(CString("Title"), titleA);
            a1->GetModel()->SetPropertyValue(CString("Title"), titleA1);
            a2->GetModel()->SetPropertyValue(CString("Title"), titleA2);
            b->GetModel()->SetPropertyValue(CString("Title"), titleB);
            b1->GetModel()->SetPropertyValue(CString("Title"), titleB1);
            b2->GetModel()->SetPropertyValue(CString("Title"), titleB2);
            x->GetModel()->SetPropertyValue(CString("Title"), titleX);
            z->GetModel()->SetPropertyValue(CString("Title"), titleZ);
            
            a->SetRect(183.000000, 105.000000, 490.000000, 163.000000);
            a1->SetRect(217.000000, 126.000000, 345.000000, 158.000000);
            a2->SetRect(357.000000, 122.000000, 485.000000, 154.000000);
            b->SetRect(316.000000, 238.000000, 484.000000, 344.000000);
            b1->SetRect(340.000000, 266.000000, 468.000000, 298.000000);
            b2->SetRect(340.000000, 303.000000, 468.000000, 335.000000);
            x->SetRect(CDoubleRect(211.000000, 163.000000, 210.000000, 275.000000).ToCRect());
            y->SetRect(CDoubleRect(210.000000, 275.000000, 340.000000, 266.000000).ToCRect());
            z->SetRect(CDoubleRect(438.000000, 237.000000, 447.000000, 154.000000).ToCRect());

            CObArray labels;
            a->GetModel()->RecreateLabels(labels);
            CProMoLabel* la = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a1->GetModel()->RecreateLabels(labels);
            CProMoLabel* la1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            a2->GetModel()->RecreateLabels(labels);
            CProMoLabel* la2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b1->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb1 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            b2->GetModel()->RecreateLabels(labels);
            CProMoLabel* lb2 = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            x->GetModel()->RecreateLabels(labels);
            CProMoLabel* lx = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            z->GetModel()->RecreateLabels(labels);
            CProMoLabel* lz = dynamic_cast<CProMoLabel*>(labels.GetAt(0));
            labels.RemoveAll();

            la->SetName(CString("1000"));
            la1->SetName(CString("1001"));
            la2->SetName(CString("1002"));
            lb->SetName(CString("1003"));
            lb1->SetName(CString("1004"));
            lb2->SetName(CString("1005"));
            lx->SetName(CString("1006"));
            lz->SetName(CString("1007"));
            
            c.Add(a);
            c.Add(a1);
            c.Add(a2);
            c.Add(b);
            c.Add(b1);
            c.Add(b2);
            c.Add(x);
            c.Add(y);
            c.Add(z);

            c.Add(la);
            c.Add(la1);
            c.Add(la2);
            c.Add(lb);
            c.Add(lb1);
            c.Add(lb2);
            c.Add(lx);
            c.Add(lz);

            diagram.AddTail(CString("custom:800,1000;"));
            diagram.AddTail(CString("promo_block_view:6,183.000000,105.000000,490.000000,163.000000,,0,4,0,-1,1,0,1,0,16777215,0,4;"));
            diagram.AddTail(CString("promo_block_view:32,217.000000,126.000000,345.000000,158.000000,,0,30,0,-1,1,0,1,0,16777215,0,4;"));
            diagram.AddTail(CString("promo_block_view:74,357.000000,122.000000,485.000000,154.000000,,0,72,0,-1,1,0,1,0,16777215,0,4;"));
            diagram.AddTail(CString("promo_block_view:17,316.000000,238.000000,484.000000,344.000000,,0,15,0,-1,1,0,1,0,16777215,0,4;"));
            diagram.AddTail(CString("promo_edge_view:523,438.000000,238.000000,447.000000,154.000000,,0,522,,,0,-1,1,0,1,0;"));
            diagram.AddTail(CString("promo_block_view:51,340.000000,266.000000,468.000000,298.000000,,0,49,0,-1,1,0,1,0,16777215,0,4;"));
            diagram.AddTail(CString("promo_edge_view:392,211.000000,163.000000,210.000000,275.000000,,0,391,,452,0,-1,1,0,1,0;"));
            diagram.AddTail(CString("promo_edge_view:452,210.000000,275.000000,340.000000,266.000000,,0,391,392,,0,-1,1,0,1,0;"));
            diagram.AddTail(CString("promo_block_view:121,340.000000,328.000000,468.000000,360.000000,,0,119,0,-1,1,0,1,0,16777215,0,4;"));
            diagram.AddTail(CString("promo_block_model:4,,0;"));
            diagram.AddTail(CString("promo_block_model:30,4,1;"));
            diagram.AddTail(CString("promo_block_model:72,4,1;"));
            diagram.AddTail(CString("promo_block_model:15,,0;"));
            diagram.AddTail(CString("promo_edge_model:522,15,72;"));
            diagram.AddTail(CString("promo_block_model:49,15,1;"));
            diagram.AddTail(CString("promo_edge_model:391,4,49;"));
            diagram.AddTail(CString("promo_block_model:119,15,12;"));

            diagram.AddTail(CString("property:Title,3,A,4;"));
            diagram.AddTail(CString("property:Title,3,A1,30;"));
            diagram.AddTail(CString("property:Title,3,A2,72;"));
            diagram.AddTail(CString("property:Title,3,B,15;"));
            diagram.AddTail(CString("property:Title,3,z,522;"));
            diagram.AddTail(CString("property:Title,3,B1,49;"));
            diagram.AddTail(CString("property:Title,3,x,391;"));
            diagram.AddTail(CString("property:Title,3,B2,119;"));

            diagram.AddTail(CString("promo_label:1000,333.000000,105.000000,340.000000,120.000000,,0,4,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.AddTail(CString("promo_label:1001,274.000000,134.500000,288.000000,149.500000,,0,30,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.AddTail(CString("promo_label:1002,414.000000,130.500000,428.000000,145.500000,,0,72,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.AddTail(CString("promo_label:1003,396.500000,238.000000,403.500000,253.000000,,0,15,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,3,3,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.AddTail(CString("promo_label:1004,397.000000,274.500000,411.000000,289.500000,,0,49,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.AddTail(CString("promo_label:1005,397.000000,336.500000,411.000000,351.500000,,0,119,Title,8192,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.AddTail(CString("promo_label:1006,207.000000,211.500000,214.000000,226.500000,,0,391,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));
            diagram.AddTail(CString("promo_label:1007,439.000000,188.500000,446.000000,203.500000,,0,522,Title,0,Courier New,12,400,0,0,0,0,-1,1,2085,10,10,0,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1;"));

            CStringArray result;

            c.Save(result);

            Assert::AreEqual((INT_PTR)34, result.GetSize());

            for (unsigned int i = 0; i < result.GetSize(); i++) {
                CString value = result.GetAt(i);
                Assert::IsNotNull(diagram.Find(value),"Could not find string "+value+" in serialized diagram");
            }

        }

#pragma endregion


    };

}
