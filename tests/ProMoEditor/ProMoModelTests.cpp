#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../../src/ProMoEditor/ProMoModel.h"
#include "../WinProMoTests.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CProMoModelTests
{

    TEST_CLASS(ProMoModelTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region ViewTests

        TEST_METHOD(LinkView_WhenNewViewAdded_ViewAppearsInList)
        {
            CProMoModel model;
            CDiagramEntity view;

            model.LinkView(&view);

            Assert::AreEqual((INT_PTR)1, model.GetViews()->GetSize());
            TestHelpers::PointerAssert::AreEqual(&view, (CDiagramEntity*)model.GetViews()->GetAt(0));
        }

        TEST_METHOD(UnlinkView_WhenViewPresent_RemovesFromList)
        {
            CProMoModel model;
            CDiagramEntity view;

            model.LinkView(&view);
            model.UnlinkView(&view);

            Assert::AreEqual((INT_PTR)0, model.GetViews()->GetSize());
        }

        TEST_METHOD(UnlinkAllViews_WhenMultipleViews_LinkArrayIsCleared)
        {
            CProMoModel model;
            CDiagramEntity v1, v2;

            model.LinkView(&v1);
            model.LinkView(&v2);

            model.UnlinkAllViews();

            Assert::AreEqual((INT_PTR)0, model.GetViews()->GetSize());
        }

#pragma endregion

#pragma region SerializationTests

        TEST_METHOD(CreateFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoModel model;
            
            model.CreateFromString(CString("promo_model:Model,;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(CreateFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoModel model;
            
            model.CreateFromString(CString("promo_model:Model,,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(CreateFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoModel model;
            
            model.CreateFromString(CString("wrong_type:;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());
        }

        TEST_METHOD(LoadFromString_WhenCorrectStringIsPassed_ParsesCorrectly)
        {
            CProMoModel model;

            model.LoadFromString(CString("promo_model:Model,;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(LoadFromString_WhenStringWithExtraParametersIsPassed_ParsesCorrectly)
        {
            CProMoModel model;

            model.LoadFromString(CString("promo_model:Model,,Extra1,Extra2;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());

        }

        TEST_METHOD(LoadFromString_WhenIncorrectStringIsPassed_IgnoreParameters)
        {
            CProMoModel model;

            model.LoadFromString(CString("wrong_type:;"));

            Assert::AreEqual(CString("promo_model"), model.GetType());
        }

#pragma endregion

#pragma region CloneTests

        TEST_METHOD(Clone_WhenCalled_ReturnsIndependentCopy)
        {
            CProMoModel model;
            CDiagramEntity view;

            model.LinkView(&view);

            std::unique_ptr<CProMoModel> clone(model.Clone());

            Assert::IsNotNull(clone.get());
            Assert::AreNotEqual((void*)&model, (void*)clone.get());

            auto* blockClone = dynamic_cast<CProMoModel*>(clone.get());
            Assert::IsNotNull(blockClone);

            Assert::AreEqual((INT_PTR)0, blockClone->GetViews()->GetSize());
        }

#pragma endregion
    };

}
