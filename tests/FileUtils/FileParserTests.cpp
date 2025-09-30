#include "CppUnitTest.h"
#include "../Helpers/MfcAssertHelpers.h"
#include "../Helpers/PointerAssertHelpers.h"
#include "../WinProMoTests.h"
#include "../../src/FileUtils/FileParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CFileSerializerTests
{

    TEST_CLASS(CFileParserTests)
    {
    public:
        TEST_METHOD_INITIALIZE(SetUp)
        {
            WinProMoTestHelpers::BootstrapMFC();
        }


#pragma region DataExtractionTests
        TEST_METHOD(GetHeaderFromString_WhenInvoked_ParseStringCorrectly)
        {
            
            CString header;
            CFileParser::GetHeaderFromString(CString("custom:762,1091;"), header);
            Assert::AreEqual(CString("custom"), header);
        }

        TEST_METHOD(GetDataFromString_WhenInvoked_ParseStringCorrectly)
        {

            CString header;
            CFileParser::GetDataFromString(CString("custom:762,1091;"), header);
            Assert::AreEqual(CString("762,1091;"), header);
        }

        TEST_METHOD(Tokenize_WhenInvoked_ParseStringCorrectly)
        {

            CTokenizer* tok;
            int value;
            tok = CFileParser::Tokenize(CString("custom:762,1091;"));
            Assert::AreEqual(2, tok->GetSize());
            tok->GetAt(0, value);
            Assert::AreEqual(762,value);
            tok->GetAt(1, value);
            Assert::AreEqual(1091, value);
            delete tok;
        }

#pragma endregion

#pragma region StringConversionTests
        
        TEST_METHOD(EncodeStringDecodeString_WhenInvoked_PreserveData)
        {

            CString string("a\r\nstring;with:special,characters");
            CString encodedString = string;
            CFileParser::EncodeString(encodedString);
            Assert::AreNotEqual(string, encodedString);
            CFileParser::DecodeString(encodedString);
            Assert::AreEqual(string, encodedString);
        }

#pragma endregion

    };
}