#include "pch.h"
#include "CppUnitTest.h"
#include <afxwin.h>

//using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//namespace WinProMoTests
//{
//	TEST_CLASS(WinProMoTests)
//	{
//	public:
//		
//        // Runs once for the entire derived test class
//        TEST_CLASS_INITIALIZE(ClassSetUp)
//        {
//            HINSTANCE hInst = ::GetModuleHandle(nullptr);
//            AfxWinInit(hInst, nullptr, ::GetCommandLine(), 0);
//
//            // Common controls init (if your UI code needs it)
//            INITCOMMONCONTROLSEX icc{ sizeof(icc), ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES };
//            InitCommonControlsEx(&icc);
//        }
//
//        TEST_CLASS_CLEANUP(ClassTearDown)
//        {
//            OleUninitialize();
//            CoUninitialize();
//        }
//
//        // Runs before every test
//        TEST_METHOD_INITIALIZE(SetUp)
//        {
//            // e.g., reset test data, clear containers
//        }
//
//        TEST_METHOD_CLEANUP(TearDown)
//        {
//            // e.g., free per-test resources
//        }
//	};
//}

namespace WinProMoTestHelpers
{
    inline void BootstrapMFC()
    {
        HINSTANCE hInst = ::GetModuleHandle(nullptr);
        AfxWinInit(hInst, nullptr, ::GetCommandLine(), 0);
    }
}