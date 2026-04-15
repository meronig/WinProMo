#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoRenderer.h"
#include "../WinProMoTests.h"
#include "../../src/ProMoEditor/ProMoEntityContainer.h"
#include "../../src/ProMoEditor/ProMoEdgeView.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoRendererTests
{
    TEST_CLASS(ProMoRendererTests)
    {

    private:
		CProMoEntityContainer* m_container;
		CProMoRenderer m_renderer;

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
            WinProMoTestHelpers::BootstrapMFC();

			m_container = new CProMoEntityContainer(NULL, CString("custom"));

            m_container->SetVirtualSize(CSize(2000, 2000));

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

            m_container->Add(m_a);
            m_container->Add(m_a1);
            m_container->Add(m_a2);
            m_container->Add(m_b);
            m_container->Add(m_b1);
            m_container->Add(m_b2);

            m_container->Add(m_x);
            m_container->Add(m_y);
            m_container->Add(m_z);

            m_container->Add(m_la);
            m_container->Add(m_la1);
            m_container->Add(m_la2);
            m_container->Add(m_lb);
            m_container->Add(m_lb1);
            m_container->Add(m_lb2);
            m_container->Add(m_lx);
            m_container->Add(m_lz);

			m_renderer.SetEntityContainer(m_container);
			m_renderer.SetScreenResolution(96);
        }
#pragma region SmokeTests
        
        TEST_METHOD(RenderCanvasAsMetafile_WhenInvoked_DeterminesCorrectSize) {
            CDC dc;
            dc.CreateCompatibleDC(NULL);
			
            m_a2->Select(TRUE);
            m_b->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderCanvasAsMetafile(dc, 1.0);

            Assert::AreEqual(CPoint(0,0), dc.GetWindowOrg());
        }

        TEST_METHOD(RenderDiagramAsMetafile_WhenInvoked_DeterminesCorrectSize) {
            CDC dc;
            dc.CreateCompatibleDC(NULL);
            
            m_a2->Select(TRUE);
            m_b->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderDiagramAsMetafile(dc, 1.0);

            Assert::AreEqual(CPoint(182, 100), dc.GetWindowOrg());
        }

        TEST_METHOD(RenderSelectionAsMetafile_WhenInvoked_DeterminesCorrectSize) {
            CDC dc;
            dc.CreateCompatibleDC(NULL);

            m_a2->Select(TRUE);
            m_b->Select(TRUE);
			m_x->Select(TRUE);

            m_renderer.RenderSelectionAsMetafile(dc, 1.0);

            Assert::AreEqual(CPoint(210, 117), dc.GetWindowOrg());
        }

        TEST_METHOD(RenderCanvasAsRaster_WhenInvoked_DeterminesCorrectSize) {
            CDibHelper dib;
            
            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderCanvasAsRaster(dib, 150);

            Assert::AreEqual(3125, dib.GetWidth());
            Assert::AreEqual(3125, dib.GetHeight());
        }

        TEST_METHOD(RenderDiagramAsRaster_WhenInvoked_DeterminesCorrectSize) {
            CDibHelper dib;
            
            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderDiagramAsRaster(dib, 150);

            Assert::AreEqual(484, dib.GetWidth());
            Assert::AreEqual(406, dib.GetHeight());
        }

        TEST_METHOD(RenderSelectionAsRaster_WhenInvoked_DeterminesCorrectSize) {
            CDibHelper dib;
            
            m_a->Select(TRUE);
            m_b1->Select(TRUE);
			m_x->Select(TRUE);
            
            m_renderer.RenderSelectionAsRaster(dib, 150);

            Assert::AreEqual(479, dib.GetWidth());
            Assert::AreEqual(309, dib.GetHeight());
        }

#pragma endregion

#pragma region InvariantTests

        TEST_METHOD(RenderCanvasAsMetafile_WhenInvoked_PreservesSelection) {
            CDC dc;
            dc.CreateCompatibleDC(NULL);

            m_a2->Select(TRUE);
            m_b->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderCanvasAsMetafile(dc, 1.0);

			Assert::IsTrue(m_a2->IsSelected());
			Assert::IsTrue(m_b->IsSelected());
			Assert::IsTrue(m_x->IsSelected());
        }

        TEST_METHOD(RenderDiagramAsMetafile_WhenInvoked_PreservesSelection) {
            CDC dc;
            dc.CreateCompatibleDC(NULL);
            
            m_a2->Select(TRUE);
            m_b->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderDiagramAsMetafile(dc, 1.0);

            Assert::IsTrue(m_a2->IsSelected());
            Assert::IsTrue(m_b->IsSelected());
            Assert::IsTrue(m_x->IsSelected());
        }

        TEST_METHOD(RenderSelectionAsMetafile_WhenInvoked_PreservesSelection) {
            CDC dc;
            dc.CreateCompatibleDC(NULL);

            m_a2->Select(TRUE);
            m_b->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderSelectionAsMetafile(dc, 1.0);

            Assert::IsTrue(m_a2->IsSelected());
            Assert::IsTrue(m_b->IsSelected());
            Assert::IsTrue(m_x->IsSelected());
        }

        TEST_METHOD(RenderCanvasAsRaster_WhenInvoked_PreservesSelection) {
            CDibHelper dib;

            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderCanvasAsRaster(dib, 150);

            Assert::IsTrue(m_a->IsSelected());
            Assert::IsTrue(m_b1->IsSelected());
            Assert::IsTrue(m_x->IsSelected());
        }

        TEST_METHOD(RenderDiagramAsRaster_WhenInvoked_PreservesSelection) {
            CDibHelper dib;

            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderDiagramAsRaster(dib, 150);

            Assert::IsTrue(m_a->IsSelected());
            Assert::IsTrue(m_b1->IsSelected());
            Assert::IsTrue(m_x->IsSelected());
        }

        TEST_METHOD(RenderSelectionAsRaster_WhenInvoked_PreservesSelection) {
            CDibHelper dib;

            m_a->Select(TRUE);
            m_b1->Select(TRUE);
            m_x->Select(TRUE);

            m_renderer.RenderSelectionAsRaster(dib, 150);

            Assert::IsTrue(m_a->IsSelected());
            Assert::IsTrue(m_b1->IsSelected());
            Assert::IsTrue(m_x->IsSelected());
        }

#pragma endregion
    };
}