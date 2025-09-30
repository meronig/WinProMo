#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/FileUtils/FileSerializer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CFileSerializerTests
{
    
    TEST_CLASS(CFileSerializerTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region FileTests
        TEST_METHOD(SaveLoad_AnsiCStringArray_RoundTripPreservesData)
        {
            // Arrange: original data
            CStringArray original;
            original.Add(_T("Line1"));
            original.Add(_T("Line2"));
            original.Add(_T("Line3"));

            CMemFile memFile;
            {
                CArchive ar(&memFile, CArchive::store);

                // Act: Save
                CFileSerializer::Save(ar, original);
            }

            // Reset memory file for reading
            memFile.SeekToBegin();

            CStringArray loaded;
            {
                CArchive ar(&memFile, CArchive::load);

                // Act: Load
                CFileSerializer::Load(ar, loaded);
            }

            // Assert: arrays match
            Assert::AreEqual(original.GetCount(), loaded.GetCount()-1, L"Line count should match");

            for (int i = 0; i < original.GetCount()-1; ++i)
            {
                Assert::AreEqual(original.GetAt(i), loaded.GetAt(i), L"Lines should match");
            }
        }

        TEST_METHOD(SaveLoad_UnicodeCStringArray_RoundTripPreservesData)
        {
            // Arrange: Unicode data
            CStringArray original;
            original.Add(_T("Line1"));
            original.Add(_T("Líne2")); // contains accented character
            original.Add(_T("Line3"));

            CMemFile memFile;
            {
                CArchive ar(&memFile, CArchive::store);

                // Act: Save
                CFileSerializer::Save(ar, original);
            }

            // Reset memory file for reading
            memFile.SeekToBegin();

            CStringArray loaded;
            {
                CArchive ar(&memFile, CArchive::load);

                // Act: Load
                CFileSerializer::Load(ar, loaded);
            }

            // Assert: arrays match
            Assert::AreEqual(original.GetCount(), loaded.GetCount()-1, L"Line count should match");

            for (int i = 0; i < original.GetCount()-1; ++i)
            {
                Assert::AreEqual(original.GetAt(i), loaded.GetAt(i), L"Lines should match");
            }
        }

#pragma endregion

    };
}