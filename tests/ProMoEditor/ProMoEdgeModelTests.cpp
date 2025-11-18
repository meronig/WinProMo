#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoBlockModel.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include "../WinProMoTests.h"

class CProMoEdgeModelTestStub : public CProMoEdgeModel
{
public:
    void SetSource(CProMoBlockModel* source) {
        CProMoEdgeModel::SetSource(source);
    }
    
    void SetDestination(CProMoBlockModel* source) {
        CProMoEdgeModel::SetDestination(source);
    }

    void LinkView(CDiagramEntity* view) {
        CProMoModel::LinkView(view);
    }
    void UnlinkView(CDiagramEntity* view) {
        CProMoModel::UnlinkView(view);
    }
    void UnlinkAllViews() {
        CProMoModel::UnlinkAllViews();
    }
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoEdgeModelTests
{

    TEST_CLASS(ProMoEdgeModelTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region SourceBlockTests

        TEST_METHOD(SetSource_WhenBlockAdded_ReturnBlock)
        {
            CProMoBlockModel model;
            CProMoEdgeModelTestStub edge;

            edge.SetSource(&model);

            CObArray edges;
            model.GetOutgoingEdges(edges);

            Assert::AreEqual((INT_PTR)1, edges.GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoEdgeModel*)&edge, (CProMoEdgeModel*)edges.GetAt(0));
            TestHelpers::PointerAssert::AreEqual(&model, edge.GetSource());
        }

        TEST_METHOD(SetSource_WhenNullIsPassed_ReturnNull)
        {
            CProMoBlockModel model;
            CProMoEdgeModelTestStub edge;

            edge.SetSource(&model);
            edge.SetSource(NULL);

            CObArray edges;
            model.GetOutgoingEdges(edges);

            Assert::AreEqual((INT_PTR)0, edges.GetSize());
            TestHelpers::PointerAssert::IsNull(edge.GetSource());
        }

        TEST_METHOD(GetSource_WhenNoBlockExists_ReturnNull)
        {
            CProMoEdgeModelTestStub edge;
            
            TestHelpers::PointerAssert::IsNull(edge.GetSource());
        }

#pragma endregion

#pragma region DestinationBlockTests

        TEST_METHOD(SetDestination_WhenBlockAdded_ReturnBlock)
        {
            CProMoBlockModel model;
            CProMoEdgeModelTestStub edge;

            edge.SetDestination(&model);

            CObArray edges;
            model.GetIncomingEdges(edges);

            Assert::AreEqual((INT_PTR)1, edges.GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoEdgeModel*)&edge, (CProMoEdgeModel*)edges.GetAt(0));
            TestHelpers::PointerAssert::AreEqual(&model, edge.GetDestination());
        }

        TEST_METHOD(SetDestination_WhenNullIsPassed_ReturnNull)
        {
            CProMoBlockModel model;
            CProMoEdgeModelTestStub edge;

            edge.SetSource(&model);
            edge.SetSource(NULL);

            CObArray edges;
            model.GetIncomingEdges(edges);

            Assert::AreEqual((INT_PTR)0, edges.GetSize());
            TestHelpers::PointerAssert::IsNull(edge.GetDestination());
        }

        TEST_METHOD(GetDestination_WhenNoBlockExists_ReturnNull)
        {
            CProMoEdgeModelTestStub edge;

            TestHelpers::PointerAssert::IsNull(edge.GetDestination());
        }

#pragma endregion

#pragma region SegmentViewTests

        TEST_METHOD(GetLastSegment_WhenOneViewExists_ReturnView)
        {
            CProMoEdgeModelTestStub model;
            CProMoEdgeView view;

            model.LinkView(&view);

            TestHelpers::PointerAssert::AreEqual(&view, model.GetLastSegment());
        }

        TEST_METHOD(GetLastSegment_WhenNoViewExists_ReturnNull)
        {
            CProMoEdgeModelTestStub model;

            TestHelpers::PointerAssert::IsNull(model.GetLastSegment());
        }

        TEST_METHOD(GetLastSegment_WhenManyViewsExist_ReturnLastSegment)
        {
            CProMoEdgeModelTestStub model;
            CProMoEdgeView v1, v2, v3;

            v1.SetDestination(&v2);
            v2.SetDestination(&v3);

            model.LinkView(&v1);
            model.LinkView(&v2);
            model.LinkView(&v3);

            TestHelpers::PointerAssert::AreEqual(&v3, model.GetLastSegment());
        }

        TEST_METHOD(GetFirstSegment_WhenOneViewExists_ReturnView)
        {
            CProMoEdgeModelTestStub model;
            CProMoEdgeView view;

            model.LinkView(&view);

            TestHelpers::PointerAssert::AreEqual(&view, model.GetFirstSegment());
        }

        TEST_METHOD(GetFirstSegment_WhenNoViewExists_ReturnNull)
        {
            CProMoEdgeModelTestStub model;

            TestHelpers::PointerAssert::IsNull(model.GetFirstSegment());
        }

        TEST_METHOD(GetFirstSegment_WhenManyViewsExist_ReturnFirstSegment)
        {
            CProMoEdgeModelTestStub model;
            CProMoEdgeView v1, v2, v3;

            v1.SetDestination(&v2);
            v2.SetDestination(&v3);

            model.UnlinkAllViews();

            model.LinkView(&v1);
            model.LinkView(&v2);
            model.LinkView(&v3);

            TestHelpers::PointerAssert::AreEqual(&v1, model.GetFirstSegment());
        }

#pragma endregion


#pragma region SerializationTests

        TEST_METHOD(GetDefaultGetString_WhenInvoked_ReturnsCorrectString)
        {
            CProMoEdgeModelTestStub edge1;
            CProMoEdgeModelTestStub edge2;
            CProMoEdgeModelTestStub edge3;
            CProMoBlockModel sourceBlock;
            CProMoBlockModel destBlock;
            CString edge1String;
            CString edge2String;
            CString edge3String;

            edge1.SetName("Edge1");
            edge2.SetName("Edge2");
            edge3.SetName("Edge3");

            sourceBlock.SetName("Source");
            destBlock.SetName("Destination");

            edge1.SetSource(&sourceBlock);
            edge2.SetSource(&sourceBlock);
            edge1.SetDestination(&destBlock);
            edge3.SetDestination(&destBlock);
            
            edge1String = edge1.GetString();
            edge2String = edge2.GetString();
            edge3String = edge3.GetString();

            Assert::AreEqual(CString("promo_edge_model:Edge1,Source,Destination;"), edge1String);
            Assert::AreEqual(CString("promo_edge_model:Edge2,Source,;"), edge2String);
            Assert::AreEqual(CString("promo_edge_model:Edge3,,Destination;"), edge3String);
        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoEdgeModelTestStub edge1;
            CProMoEdgeModelTestStub edge2;
            CProMoEdgeModelTestStub edge3;

            edge1.CreateFromString(CString("promo_edge_model:Edge1,Source,Destination;"));

            Assert::AreEqual(CString("promo_edge_model"), edge1.GetType());

            edge2.CreateFromString(CString("promo_edge_model:Edge2,Source,;"));

            Assert::AreEqual(CString("promo_edge_model"), edge2.GetType());

            edge3.CreateFromString(CString("promo_edge_model:Edge3,,Destination;"));

            Assert::AreEqual(CString("promo_edge_model"), edge3.GetType());
        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoEdgeModelTestStub edge1;
            CProMoEdgeModelTestStub edge2;
            CProMoEdgeModelTestStub edge3;

            edge1.CreateFromString(CString("promo_edge_model:Edge1,Source,Destination,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_edge_model"), edge1.GetType());

            edge2.CreateFromString(CString("promo_edge_model:Edge2,Source,,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_edge_model"), edge2.GetType());

            edge3.CreateFromString(CString("promo_edge_model:Edge3,,Destination,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_edge_model"), edge3.GetType());
        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoEdgeModelTestStub edge1;
            CProMoEdgeModelTestStub edge2;

            edge1.CreateFromString(CString("wrong_type:;"));

            Assert::AreEqual(CString("promo_edge_model"), edge1.GetType());

            edge2.CreateFromString(CString("wrong_type:Foobar;"));

            Assert::AreEqual(CString("promo_edge_model"), edge2.GetType());
        }

        TEST_METHOD(GetSourceFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoEdgeModelTestStub::GetSourceFromString(CString("promo_edge_model:Edge1,,Destination;"));
            CString str2 = CProMoEdgeModelTestStub::GetSourceFromString(CString("promo_edge_model:Edge1,Source,Destination;"));
            Assert::AreEqual(CString(""), str1);
            Assert::AreEqual(CString("Source"), str2);
        }

        TEST_METHOD(GetDestinationFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoEdgeModelTestStub::GetDestinationFromString(CString("promo_edge_model:Edge1,Source,;"));
            CString str2 = CProMoEdgeModelTestStub::GetDestinationFromString(CString("promo_edge_model:Edge1,Source,Destination;"));
            Assert::AreEqual(CString(""), str1);
            Assert::AreEqual(CString("Destination"), str2);
        }

#pragma endregion

#pragma region CloneTests

        TEST_METHOD(Clone_WhenCalled_ReturnsIndependentCopy)
        {
            CProMoEdgeModelTestStub model;
            
            std::unique_ptr<CProMoModel> clone(model.Clone());

            Assert::IsNotNull(clone.get());
            Assert::AreNotEqual((void*)&model, (void*)clone.get());

            auto* blockClone = dynamic_cast<CProMoEdgeModel*>(clone.get());
            Assert::IsNotNull(blockClone);
        }

#pragma endregion
    };

}
