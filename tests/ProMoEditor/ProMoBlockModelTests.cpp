#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoBlockModel.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include "../WinProMoTests.h"

class CProMoBlockModelTestStub : public CProMoBlockModel
{
public:
    void LinkSubBlock(CProMoBlockModel* subblock) {
        CProMoBlockModel::LinkSubBlock(subblock);
    }
    void UnlinkSubBlock(CProMoBlockModel* subblock) {
        CProMoBlockModel::UnlinkSubBlock(subblock);
    }
    void UnlinkAllSubBlocks() {
        CProMoBlockModel::UnlinkAllSubBlocks();
    }
    void SetParentBlock(CProMoBlockModel* parent) {
        CProMoBlockModel::SetParentBlock(parent);
    }

    void LinkOutgoingEdge(CProMoEdgeModel* edge) {
        CProMoBlockModel::LinkOutgoingEdge(edge);
    }
    void UnlinkOutgoingEdge(CProMoEdgeModel* edge) {
        CProMoBlockModel::UnlinkOutgoingEdge(edge);
    }
    void UnlinkAllOutgoingEdges() {
        CProMoBlockModel::UnlinkAllOutgoingEdges();
    }

    void LinkIncomingEdge(CProMoEdgeModel* edge) {
        CProMoBlockModel::LinkIncomingEdge(edge);
    }
    void UnlinkIncomingEdge(CProMoEdgeModel* edge) {
        CProMoBlockModel::UnlinkIncomingEdge(edge);
    }
    void UnlinkAllIncomingEdges() {
        CProMoBlockModel::UnlinkAllIncomingEdges();
    }

    void LinkView(CDiagramEntity* view) {
        CProMoModel::LinkView(view);
    }

};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoBlockModelTests
{

    TEST_CLASS(ProMoBlockModelTests)
    {
    public:

        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }

#pragma region SubBlockTests

        TEST_METHOD(LinkSubBlock_WhenNewBlockAdded_SubblockAppearsInList)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.LinkSubBlock(&child);

            Assert::AreEqual((INT_PTR)1, parent.GetSubBlocks()->GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&child, (CProMoBlockModel*)parent.GetSubBlocks()->GetAt(0));
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&parent, child.GetParentBlock());
        }

        TEST_METHOD(UnlinkSubBlock_WhenBlockPresent_RemovesFromList)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.LinkSubBlock(&child);
            parent.UnlinkSubBlock(&child);

            Assert::AreEqual((INT_PTR)0, parent.GetSubBlocks()->GetSize());
            TestHelpers::PointerAssert::IsNull(child.GetParentBlock());
        }

        TEST_METHOD(UnlinkAllSubBlocks_WhenMultipleBlocks_LinkArrayIsCleared)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub c1, c2;

            parent.LinkSubBlock(&c1);
            parent.LinkSubBlock(&c2);

            parent.UnlinkAllSubBlocks();

            Assert::AreEqual((INT_PTR)0, parent.GetSubBlocks()->GetSize());
            TestHelpers::PointerAssert::IsNull(c1.GetParentBlock());
            TestHelpers::PointerAssert::IsNull(c2.GetParentBlock());
        }

        TEST_METHOD(Contains_WhenRecursiveCheck_ReturnsTrueForDeepNesting)
        {
            CProMoBlockModelTestStub root, mid, leaf;

            root.LinkSubBlock(&mid);
            mid.LinkSubBlock(&leaf);

            Assert::IsTrue(root.Contains(&leaf, TRUE));
        }

        TEST_METHOD(CanBeNestedBy_WhenNoParentSame_ReturnsTrue)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;
            Assert::IsTrue(child.CanBeNestedBy(&parent));
        }

        TEST_METHOD(CanBeNestedBy_WhenParentIsSame_ReturnsFalse)
        {
            CProMoBlockModelTestStub block;
            Assert::IsFalse(block.CanBeNestedBy(&block));
        }
        
        TEST_METHOD(CanBeNestedBy_WhenCircularDependency_ReturnsFalse)
        {
            CProMoBlockModelTestStub root, mid, leaf;

            root.LinkSubBlock(&mid);
            mid.LinkSubBlock(&leaf);
            
            Assert::IsFalse(root.CanBeNestedBy(&leaf));
        }
        TEST_METHOD(SetParentBlock_WhenBlockHasNoParent_SetParent)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            child.SetParentBlock(&parent);

            Assert::AreEqual((INT_PTR)1, parent.GetSubBlocks()->GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&child, (CProMoBlockModel*)parent.GetSubBlocks()->GetAt(0));
        }

        TEST_METHOD(SetParentBlock_WhenBlockHasParent_ChangeParent)
        {
            CProMoBlockModelTestStub oldParent;
            CProMoBlockModelTestStub newParent;
            CProMoBlockModelTestStub child;

            child.SetParentBlock(&oldParent);
            child.SetParentBlock(&newParent);

            Assert::AreEqual((INT_PTR)0, oldParent.GetSubBlocks()->GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&child, (CProMoBlockModel*)newParent.GetSubBlocks()->GetAt(0));
        }

        TEST_METHOD(SetParentBlock_WhenNullIsPassed_RemoveParent)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            child.SetParentBlock(&parent);
            child.SetParentBlock(NULL);

            Assert::AreEqual((INT_PTR)0, parent.GetSubBlocks()->GetSize());
            TestHelpers::PointerAssert::IsNull(child.GetParentBlock());
        }

#pragma endregion

#pragma region OutgoingEdgeTests

        TEST_METHOD(LinkOutgoingEdge_WhenEdgeAdded_AppearsInList)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel edge;

            model.LinkOutgoingEdge(&edge);

            Assert::AreEqual((INT_PTR)1, model.GetOutgoingEdges()->GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoEdgeModel*)&edge, (CProMoEdgeModel*)model.GetOutgoingEdges()->GetAt(0));
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&model, edge.GetSource());
        }

        TEST_METHOD(UnlinkOutgoingEdge_WhenEdgePresent_RemovesFromList)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel edge;

            model.LinkOutgoingEdge(&edge);
            model.UnlinkOutgoingEdge(&edge);

            Assert::AreEqual((INT_PTR)0, model.GetOutgoingEdges()->GetSize());
            TestHelpers::PointerAssert::IsNull(edge.GetSource());
        }

        TEST_METHOD(UnlinkAllOutgoingEdges_WhenMultipleEdges_LinkArrayIsCleared)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel e1, e2;

            model.LinkOutgoingEdge(&e1);
            model.LinkOutgoingEdge(&e2);
            
            model.UnlinkAllOutgoingEdges();

            Assert::AreEqual((INT_PTR)0, model.GetOutgoingEdges()->GetSize());
            TestHelpers::PointerAssert::IsNull(e1.GetSource());
            TestHelpers::PointerAssert::IsNull(e2.GetSource());
        }

#pragma endregion

#pragma region IncomingEdgeTests

        TEST_METHOD(LinkIncomingEdge_WhenEdgeAdded_AppearsInList)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel edge;
            
            model.LinkIncomingEdge(&edge);

            Assert::AreEqual((INT_PTR)1, model.GetIncomingEdges()->GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoEdgeModel*)&edge, (CProMoEdgeModel*)model.GetIncomingEdges()->GetAt(0));
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&model, edge.GetDestination());
        }

        TEST_METHOD(UnlinkIncomingEdge_WhenEdgePresent_RemovesFromList)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel edge;

            model.LinkIncomingEdge(&edge);
            model.UnlinkIncomingEdge(&edge);

            Assert::AreEqual((INT_PTR)0, model.GetIncomingEdges()->GetSize());
            TestHelpers::PointerAssert::IsNull(edge.GetDestination());
        }

        TEST_METHOD(UnlinkAllIncomingEdges_WhenMultipleEdges_LinkArrayIsCleared)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel e1, e2;

            model.LinkIncomingEdge(&e1);
            model.LinkIncomingEdge(&e2);

            model.UnlinkAllIncomingEdges();

            Assert::AreEqual((INT_PTR)0, model.GetIncomingEdges()->GetSize());
            TestHelpers::PointerAssert::IsNull(e1.GetDestination());
            TestHelpers::PointerAssert::IsNull(e2.GetDestination());
        }

#pragma endregion

#pragma region MainViewTests

        TEST_METHOD(GetMainView_WhenOneViewExists_ReturnView)
        {
            CProMoBlockModelTestStub model;
            CProMoBlockView view;

            model.LinkView(&view);

            TestHelpers::PointerAssert::AreEqual(&view, model.GetMainView());
        }

        TEST_METHOD(GetMainView_WhenNoViewExists_ReturnNull)
        {
            CProMoBlockModelTestStub model;
            
            TestHelpers::PointerAssert::IsNull(model.GetMainView());
        }

        TEST_METHOD(GetMainView_WhenManyViewsExist_ReturnFirstView)
        {
            CProMoBlockModelTestStub model;
            CProMoBlockView v1, v2;

            model.LinkView(&v1);
            model.LinkView(&v2);

            TestHelpers::PointerAssert::AreEqual(&v1, model.GetMainView());
        }

        TEST_METHOD(GetMainView_WhenManyViewTypesExist_ReturnFirstCProMoBlockView)
        {
            CProMoBlockModelTestStub model;
            CDiagramEntity v1;
            CProMoBlockView v2;

            model.LinkView(&v1);
            model.LinkView(&v2);

            TestHelpers::PointerAssert::AreEqual(&v2, model.GetMainView());
        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(GetDefaultGetString_WhenInvoked_ReturnsCorrectString)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;
            CString parentString;
            CString childString;
            
            parent.SetName(CString("Parent"));
            child.SetName(CString("Child"));
            child.SetParentBlock(&parent);

            parentString = parent.GetString();
            childString = child.GetString();
            
            Assert::AreEqual(CString("promo_block_model:Parent,;"), parentString);
            Assert::AreEqual(CString("promo_block_model:Child,Parent;"), childString);
            
        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.CreateFromString(CString("promo_block_model:Parent,;"));

            Assert::AreEqual(CString("promo_block_model"), parent.GetType());
            
            child.CreateFromString(CString("promo_block_model:Child,Parent;"));

            Assert::AreEqual(CString("promo_block_model"), child.GetType());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.CreateFromString(CString("promo_block_model:Parent,,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_block_model"), parent.GetType());

            child.CreateFromString(CString("promo_block_model:Child,Parent,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_block_model"), child.GetType());
        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.CreateFromString(CString("wrong_type:;"));

            Assert::AreEqual(CString("promo_block_model"), parent.GetType());

            child.CreateFromString(CString("wrong_type:;"));

            Assert::AreEqual(CString("promo_block_model"), child.GetType());
        }

#pragma endregion

#pragma region CloneTests

        TEST_METHOD(Clone_WhenCalled_ReturnsIndependentCopy)
        {
            CProMoBlockModelTestStub model;
            CProMoBlockModelTestStub child;
            model.LinkSubBlock(&child);

            std::unique_ptr<CProMoModel> clone(model.Clone());

            Assert::IsNotNull(clone.get());
            Assert::AreNotEqual((void*)&model, (void*)clone.get());

            auto* blockClone = dynamic_cast<CProMoBlockModel*>(clone.get());
            Assert::IsNotNull(blockClone);

            Assert::AreEqual((INT_PTR)0, blockClone->GetSubBlocks()->GetSize());
        }

#pragma endregion
    };

}
