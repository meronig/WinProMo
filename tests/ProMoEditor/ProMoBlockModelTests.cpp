#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoBlockModel.h"
#include "../../src/ProMoEditor/ProMoEdgeModel.h"
#include "../WinProMoTests.h"

class CProMoBlockModelTestStub : public CProMoBlockModel
{
public:
    void LinkChildBlock(CProMoBlockModel* subblock, unsigned int attachment) {
        CProMoBlockModel::LinkChildBlock(subblock, attachment);
    }
    void UnlinkChildBlock(CProMoBlockModel* subblock) {
        CProMoBlockModel::UnlinkChildBlock(subblock);
    }
    void UnlinkAllChildBlocks() {
        CProMoBlockModel::UnlinkAllChildBlocks();
    }
    void SetParentBlock(CProMoBlockModel* parent, unsigned int attachment) {
        CProMoBlockModel::SetParentBlock(parent, attachment);
    }

    BOOL Contains(CProMoBlockModel* block, BOOL recursive) const {
        return CProMoBlockModel::Contains(block, recursive);
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

            parent.LinkChildBlock(&child, DEHT_BODY);
            
            CObArray subBlocks;
            parent.GetSubBlocks(subBlocks);

            Assert::AreEqual((INT_PTR)1, subBlocks.GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&child, (CProMoBlockModel*)subBlocks.GetAt(0));
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&parent, child.GetParentBlock());
        }

        TEST_METHOD(UnlinkSubBlock_WhenBlockPresent_RemovesFromList)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.LinkChildBlock(&child, DEHT_BODY);
            parent.UnlinkChildBlock(&child);

            CObArray subBlocks;
            parent.GetSubBlocks(subBlocks);

            Assert::AreEqual((INT_PTR)0, subBlocks.GetSize());
            TestHelpers::PointerAssert::IsNull(child.GetParentBlock());
        }

        TEST_METHOD(UnlinkAllSubBlocks_WhenMultipleBlocks_LinkArrayIsCleared)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub c1, c2;

            parent.LinkChildBlock(&c1, DEHT_BODY);
            parent.LinkChildBlock(&c2, DEHT_BODY);

            parent.UnlinkAllChildBlocks();

            CObArray subBlocks;
            parent.GetSubBlocks(subBlocks);

            Assert::AreEqual((INT_PTR)0, subBlocks.GetSize());
            TestHelpers::PointerAssert::IsNull(c1.GetParentBlock());
            TestHelpers::PointerAssert::IsNull(c2.GetParentBlock());
        }

        TEST_METHOD(Contains_WhenRecursiveCheck_ReturnsTrueForDeepNesting)
        {
            CProMoBlockModelTestStub root, mid, leaf;

            root.LinkChildBlock(&mid, DEHT_BODY);
            mid.LinkChildBlock(&leaf, DEHT_BODY);

            Assert::IsTrue(root.Contains(&leaf, TRUE));
        }

        TEST_METHOD(CanBeNestedBy_WhenNoParentSame_ReturnsTrue)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;
            Assert::IsTrue(child.CanBeSubBlockOf(&parent));
        }

        TEST_METHOD(CanBeNestedBy_WhenParentIsSame_ReturnsFalse)
        {
            CProMoBlockModelTestStub block;
            Assert::IsFalse(block.CanBeSubBlockOf(&block));
        }
        
        TEST_METHOD(CanBeNestedBy_WhenCircularDependency_ReturnsFalse)
        {
            CProMoBlockModelTestStub root, mid, leaf;

            root.LinkChildBlock(&mid, DEHT_BODY);
            mid.LinkChildBlock(&leaf, DEHT_BODY);
            
            Assert::IsFalse(root.CanBeSubBlockOf(&leaf));
        }
        TEST_METHOD(SetParentBlock_WhenBlockHasNoParent_SetParent)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            child.SetParentBlock(&parent, DEHT_BODY);

            CObArray subBlocks;
            parent.GetSubBlocks(subBlocks);

            Assert::AreEqual((INT_PTR)1, subBlocks.GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&child, (CProMoBlockModel*)subBlocks.GetAt(0));
        }

        TEST_METHOD(SetParentBlock_WhenBlockHasParent_ChangeParent)
        {
            CProMoBlockModelTestStub oldParent;
            CProMoBlockModelTestStub newParent;
            CProMoBlockModelTestStub child;

            child.SetParentBlock(&oldParent, DEHT_BODY);
            child.SetParentBlock(&newParent, DEHT_BODY);

            CObArray oldSubBlocks;
            oldParent.GetSubBlocks(oldSubBlocks);

            CObArray newSubBlocks;
            newParent.GetSubBlocks(newSubBlocks);

            Assert::AreEqual((INT_PTR)0, oldSubBlocks.GetSize());
            Assert::AreEqual((INT_PTR)1, newSubBlocks.GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&child, (CProMoBlockModel*)newSubBlocks.GetAt(0));
        }

        TEST_METHOD(SetParentBlock_WhenNullIsPassed_RemoveParent)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            child.SetParentBlock(&parent, DEHT_BODY);
            child.SetParentBlock(NULL, DEHT_BODY);

            CObArray subBlocks;
            parent.GetSubBlocks(subBlocks);

            Assert::AreEqual((INT_PTR)0, subBlocks.GetSize());
            TestHelpers::PointerAssert::IsNull(child.GetParentBlock());
        }

#pragma endregion

#pragma region OutgoingEdgeTests

        TEST_METHOD(LinkOutgoingEdge_WhenEdgeAdded_AppearsInList)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel edge;

            model.LinkOutgoingEdge(&edge);

            CObArray edges;
            model.GetOutgoingEdges(edges);

            Assert::AreEqual((INT_PTR)1, edges.GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoEdgeModel*)&edge, (CProMoEdgeModel*)edges.GetAt(0));
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&model, edge.GetSource());
        }

        TEST_METHOD(UnlinkOutgoingEdge_WhenEdgePresent_RemovesFromList)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel edge;

            model.LinkOutgoingEdge(&edge);
            model.UnlinkOutgoingEdge(&edge);

            CObArray edges;
            model.GetOutgoingEdges(edges);

            Assert::AreEqual((INT_PTR)0, edges.GetSize());
            TestHelpers::PointerAssert::IsNull(edge.GetSource());
        }

        TEST_METHOD(UnlinkAllOutgoingEdges_WhenMultipleEdges_LinkArrayIsCleared)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel e1, e2;

            model.LinkOutgoingEdge(&e1);
            model.LinkOutgoingEdge(&e2);
            
            model.UnlinkAllOutgoingEdges();

            CObArray edges;
            model.GetOutgoingEdges(edges);

            Assert::AreEqual((INT_PTR)0, edges.GetSize()); 
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

            CObArray edges;
            model.GetIncomingEdges(edges);

            Assert::AreEqual((INT_PTR)1, edges.GetSize());
            TestHelpers::PointerAssert::AreEqual((CProMoEdgeModel*)&edge, (CProMoEdgeModel*)edges.GetAt(0));
            TestHelpers::PointerAssert::AreEqual((CProMoBlockModel*)&model, edge.GetDestination());
        }

        TEST_METHOD(UnlinkIncomingEdge_WhenEdgePresent_RemovesFromList)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel edge;

            model.LinkIncomingEdge(&edge);
            model.UnlinkIncomingEdge(&edge);

            CObArray edges;
            model.GetIncomingEdges(edges);

            Assert::AreEqual((INT_PTR)0, edges.GetSize());
            TestHelpers::PointerAssert::IsNull(edge.GetDestination());
        }

        TEST_METHOD(UnlinkAllIncomingEdges_WhenMultipleEdges_LinkArrayIsCleared)
        {
            CProMoBlockModelTestStub model;
            CProMoEdgeModel e1, e2;

            model.LinkIncomingEdge(&e1);
            model.LinkIncomingEdge(&e2);

            model.UnlinkAllIncomingEdges();

            CObArray edges;
            model.GetIncomingEdges(edges);

            Assert::AreEqual((INT_PTR)0, edges.GetSize());
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
            child.SetParentBlock(&parent, DEHT_BODY);

            parentString = parent.GetString();
            childString = child.GetString();
            
            Assert::AreEqual(CString("promo_block_model:Parent,,0;"), parentString);
            Assert::AreEqual(CString("promo_block_model:Child,Parent,1;"), childString);
            
        }

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.CreateFromString(CString("promo_block_model:Parent,,0;"));

            Assert::AreEqual(CString("promo_block_model"), parent.GetType());
            
            child.CreateFromString(CString("promo_block_model:Child,Parent,1;"));

            Assert::AreEqual(CString("promo_block_model"), child.GetType());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoBlockModelTestStub parent;
            CProMoBlockModelTestStub child;

            parent.CreateFromString(CString("promo_block_model:Parent,,0,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_block_model"), parent.GetType());

            child.CreateFromString(CString("promo_block_model:Child,Parent,1,Extra1,Extra2;"));

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

        TEST_METHOD(GetParentFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            CString str1 = CProMoBlockModelTestStub::GetParentFromString(CString("promo_block_model:Parent,,0;"));
            CString str2 = CProMoBlockModelTestStub::GetParentFromString(CString("promo_block_model:Child,Parent,1;"));
            Assert::AreEqual(CString(""), str1);
            Assert::AreEqual(CString("Parent"), str2);
        }

        TEST_METHOD(GetAttachmentTypeFromString_WhenCorrectStringIsPassed_ExtractsCorrectValue) {
            int i1 = CProMoBlockModelTestStub::GetAttachmentTypeFromString(CString("promo_block_model:Parent,,0;"));
            int i2 = CProMoBlockModelTestStub::GetAttachmentTypeFromString(CString("promo_block_model:Child,Parent,1;"));
            Assert::AreEqual(DEHT_NONE, i1);
            Assert::AreEqual(DEHT_BODY, i2);
        }

#pragma endregion

#pragma region CloneTests

        TEST_METHOD(Clone_WhenCalled_ReturnsIndependentCopy)
        {
            CProMoBlockModelTestStub model;
            CProMoBlockModelTestStub child;
            model.LinkChildBlock(&child, DEHT_BODY);

            std::unique_ptr<CProMoModel> clone(model.Clone());

            Assert::IsNotNull(clone.get());
            Assert::AreNotEqual((void*)&model, (void*)clone.get());

            auto* blockClone = dynamic_cast<CProMoBlockModel*>(clone.get());
            Assert::IsNotNull(blockClone);

            CObArray subBlocks;
            blockClone->GetSubBlocks(subBlocks);

            Assert::AreEqual((INT_PTR)0, subBlocks.GetSize());
        }

#pragma endregion
    };

}
