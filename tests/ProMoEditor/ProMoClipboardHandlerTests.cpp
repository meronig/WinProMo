#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoEntityContainer.h"
#include "../../src/ProMoEditor/ProMoClipboardHandler.h"
#include "../../src/ProMoEditor/ProMoEdgeView.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include "../WinProMoTests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoClipboardHandlerTests
{

    TEST_CLASS(CProMoClipboardHandlerTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region ClipboardTest

        TEST_METHOD(Copy_WhenInvoked_CopyElement) {
            
            CProMoClipboardHandler clip;
            CProMoBlockView* a = new CProMoBlockView();

            clip.Copy(a);
            Assert::AreEqual((INT_PTR)1, clip.GetData()->GetSize());
        }

        TEST_METHOD(CopyAllSelected_WhenInvoked_CopySelection)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer sourceC(NULL, CString("custom"));
            
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
            b->LinkSubBlock(b2);

            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);
            z->SetSource(b);
            z->SetDestination(a2);

            // If one element which is part of the group is copied, all other elements are copied as well
            a->SetGroup(1);
            a1->SetGroup(1);
            a2->SetGroup(1);

            sourceC.Add(x);
            sourceC.Add(y);
            sourceC.Add(z);
            sourceC.Add(a1);
            sourceC.Add(a2);
            sourceC.Add(a);
            sourceC.Add(b1);
            sourceC.Add(b2);
            sourceC.Add(b);

            a->Select(TRUE);
            x->Select(TRUE);
            b->Select(TRUE);
            z->Select(TRUE);
            a2->Select(TRUE);

            clip.CopyAllSelected(&sourceC);

            Assert::AreEqual(CString("custom"), clip.GetModelType());
            Assert::AreEqual((INT_PTR)6, clip.GetData()->GetSize());

        }

        TEST_METHOD(Paste_WhenInvoked_PasteObjects)
        {
            CProMoClipboardHandler clip;
            CProMoEntityContainer sourceC(NULL, CString("custom"), &clip);
            CProMoEntityContainer destC(NULL, CString("custom"), &clip);

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
            b->LinkSubBlock(b2);

            x->SetSource(a);
            x->SetDestination(y);
            y->SetDestination(b1);
            z->SetSource(b);
            z->SetDestination(a2);

            sourceC.Add(x);
            sourceC.Add(y);
            sourceC.Add(z);
            sourceC.Add(a1);
            sourceC.Add(a2);
            sourceC.Add(a);
            sourceC.Add(b1);
            sourceC.Add(b2);
            sourceC.Add(b);

            // If one element which is part of the group is copied, all other elements are copied as well
            a->SetGroup(1);
            a1->SetGroup(1);
            a2->SetGroup(1);

            a->Select(TRUE);
            x->Select(TRUE);
            b->Select(TRUE);
            z->Select(TRUE);
            a2->Select(TRUE);

            sourceC.CopyAllSelected();
            destC.Paste();

            Assert::AreEqual(4, destC.GetSelectCount());

        }

#pragma endregion


    };

}
