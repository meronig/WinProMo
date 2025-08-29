#pragma once
#include "CppUnitTest.h"
#include <sstream>
#include <iomanip>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHelpers
{
    class PointerAssert
    {
    private:
        static std::wstring ToHex(const void* ptr)
        {
            std::wostringstream oss;
            oss << L"0x"
                << std::uppercase
                << std::setfill(L'0')
                << std::setw(sizeof(void*) * 2)
                << std::hex
                << reinterpret_cast<uintptr_t>(ptr);
            return oss.str();
        }

    public:
        template<typename T>
        static void AreEqual(const T* expected, const T* actual, const wchar_t* message = nullptr)
        {
            if (expected != actual)
            {
                std::wstring fullMsg = L"Expected: " + ToHex(expected) +
                    L" but was: " + ToHex(actual);
                if (message)
                    fullMsg += L" (" + std::wstring(message) + L")";
                Assert::Fail(fullMsg.c_str());
            }
        }

        template<typename T>
        static void AreNotEqual(const T* expected, const T* actual, const wchar_t* message = nullptr)
        {
            if (expected == actual)
            {
                std::wstring fullMsg = L"Did not expect both to be " + ToHex(actual);
                if (message)
                    fullMsg += L" (" + std::wstring(message) + L")";
                Assert::Fail(fullMsg.c_str());
            }
        }

        template<typename T>
        static void IsNull(const T* actual, const wchar_t* message = nullptr)
        {
            if (actual != nullptr)
            {
                std::wstring fullMsg = L"Expected null but was " + ToHex(actual);
                if (message)
                    fullMsg += L" (" + std::wstring(message) + L")";
                Assert::Fail(fullMsg.c_str());
            }
        }

        template<typename T>
        static void IsNotNull(const T* actual, const wchar_t* message = nullptr)
        {
            if (actual == nullptr)
            {
                std::wstring fullMsg = L"Expected non-null but was null";
                if (message)
                    fullMsg += L" (" + std::wstring(message) + L")";
                Assert::Fail(fullMsg.c_str());
            }
        }
    };
}
