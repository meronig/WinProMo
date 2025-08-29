#include "pch.h"
#include "CppUnitTest.h"
#include "../src/ProMoEditor/ProMoEdgeModel.h"
#include "Helpers/MfcAssertHelpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WinProMoTests
{
	TEST_CLASS(WinProMoTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			CProMoEdgeModel* model = new CProMoEdgeModel();
			CString modelName = CString("TestName");
			model->SetName(modelName);
			Assert::AreEqual(model->GetName(), modelName);
		}
	};
}
