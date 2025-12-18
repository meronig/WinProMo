#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/FileUtils/DibHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CDibHelperTests
{

    TEST_CLASS(CDibHelperTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }
#pragma region SmokeTests
        TEST_METHOD(Create_ValidSize_CreatesBitmap)
        {
            CDibHelper dib;

            BOOL result = dib.Create(100, 50, 24);

            Assert::IsTrue(result);
            Assert::IsNotNull(dib.GetBitmap());
            Assert::IsNotNull(dib.GetBits());
            Assert::AreEqual(100, dib.GetWidth());
            Assert::AreEqual(50, dib.GetHeight());
            Assert::AreEqual(24, dib.GetBitCount());
        }
        
        TEST_METHOD(Create_ValidSize_RowBytesAligned)
        {
            CDibHelper dib;
            dib.Create(13, 7, 24);

            int expected = ((13 * 24 + 31) / 32) * 4;

            Assert::AreEqual(expected, dib.GetRowBytes());
        }

        TEST_METHOD(Destroy_AfterCreate_ReleasesResources)
        {
            CDibHelper dib;
            dib.Create(10, 10);

            dib.Destroy();

            Assert::IsNull(dib.GetBitmap());
            Assert::IsNull(dib.GetBits());
        }

        TEST_METHOD(Attach_OwnedBitmap_DeletesOnDestroy)
        {
            HDC hdc = ::GetDC(nullptr);
            HBITMAP hBmp = ::CreateCompatibleBitmap(hdc, 10, 10);
            ::ReleaseDC(nullptr, hdc);

            CDibHelper dib;
            dib.Attach(hBmp, nullptr, TRUE);

            HBITMAP internal = dib.GetBitmap();
            Assert::IsNotNull(internal);

            dib.Destroy();

            BITMAP bm = {};
            int res = ::GetObject(internal, sizeof(bm), &bm);
            Assert::AreEqual(0, res);   // internal bitmap deleted

            ::DeleteObject(hBmp);       // original still caller-owned
        }

        TEST_METHOD(DetachBitmap_AfterAttach_ReleasesOwnership)
        {
            HDC hdc = ::GetDC(nullptr);
            HBITMAP hBmp = ::CreateCompatibleBitmap(hdc, 10, 10);
            ::ReleaseDC(nullptr, hdc);

            CDibHelper dib;
            dib.Attach(hBmp, nullptr, TRUE);

            HBITMAP detached = dib.DetachBitmap();
            Assert::IsNotNull(detached);

            // Must be a valid bitmap
            BITMAP bm = {};
            Assert::AreNotEqual(0, ::GetObject(detached, sizeof(bm), &bm));

            // It is NOT the original bitmap
            Assert::AreNotEqual((void*)hBmp, (void*)detached);

            // Cleanup
            ::DeleteObject(detached);
            ::DeleteObject(hBmp);
        }
        
        TEST_METHOD(CreateDibGlobalForClipboard_ValidDib_ReturnsValidGlobal)
        {
            CDibHelper dib;
            dib.Create(32, 32, 24);

            HGLOBAL h = dib.CreateDibGlobalForClipboard();

            Assert::IsNotNull(h);

            void* p = ::GlobalLock(h);
            Assert::IsNotNull(p);

            BITMAPINFOHEADER* bih = (BITMAPINFOHEADER*)p;
            Assert::AreEqual((LONG)32, bih->biWidth);
            Assert::AreEqual((LONG)32, labs(bih->biHeight));

            ::GlobalUnlock(h);
            ::GlobalFree(h);
        }

        TEST_METHOD(SaveBMP_ValidPath_CreatesFile)
        {
            CDibHelper dib;
            dib.Create(16, 16, 24);

            CString path = _T("test_output.bmp");

            Assert::IsTrue(dib.SaveBMP(path));

            DWORD attrs = ::GetFileAttributes(path);
            Assert::AreNotEqual(INVALID_FILE_ATTRIBUTES, attrs);

            ::DeleteFile(path);
        }
        
#pragma endregion
    };
}