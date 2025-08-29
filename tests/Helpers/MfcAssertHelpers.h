#include <string>
#include <afxwin.h>   // for CString, CPoint, CSize, CRect
#include "CppUnitTest.h"

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {

            // ---------- ToString specializations ----------

            // CString --> std::wstring
            template<> static std::wstring ToString<CString>(const CString& str)
            {
                return std::wstring(str.GetString());
            }

            // CPoint --> "(x, y)"
            template<> static std::wstring ToString<CPoint>(const CPoint& pt)
            {
                return L"(" + std::to_wstring(pt.x) + L", " + std::to_wstring(pt.y) + L")";
            }

            // CSize --> "(cx, cy)"
            template<> static std::wstring ToString<CSize>(const CSize& sz)
            {
                return L"(" + std::to_wstring(sz.cx) + L", " + std::to_wstring(sz.cy) + L")";
            }

            // CRect --> "(left, top, right, bottom)"
            template<> static std::wstring ToString<CRect>(const CRect& rc)
            {
                return L"(" + std::to_wstring(rc.left) + L", "
                    + std::to_wstring(rc.top) + L", "
                    + std::to_wstring(rc.right) + L", "
                    + std::to_wstring(rc.bottom) + L")";
            }

            // ---------- Tolerance-aware helpers ----------

            inline void AssertAreEqual(const CPoint& expected, const CPoint& actual, int tolerance,
                const wchar_t* message = nullptr, const __LineInfo* lineInfo = nullptr)
            {
                bool ok = (abs(expected.x - actual.x) <= tolerance &&
                    abs(expected.y - actual.y) <= tolerance);

                if (!ok)
                {
                    Assert::Fail(
                        (std::wstring(L"Expected: ") + ToString(expected) +
                            L", Actual: " + ToString(actual) +
                            L", Tolerance: " + std::to_wstring(tolerance)).c_str(),
                        lineInfo);
                }
            }

            inline void AssertAreEqual(const CSize& expected, const CSize& actual, int tolerance,
                const wchar_t* message = nullptr, const __LineInfo* lineInfo = nullptr)
            {
                bool ok = (abs(expected.cx - actual.cx) <= tolerance &&
                    abs(expected.cy - actual.cy) <= tolerance);

                if (!ok)
                {
                    Assert::Fail(
                        (std::wstring(L"Expected: ") + ToString(expected) +
                            L", Actual: " + ToString(actual) +
                            L", Tolerance: " + std::to_wstring(tolerance)).c_str(),
                        lineInfo);
                }
            }

            inline void AssertAreEqual(const CRect& expected, const CRect& actual, int tolerance,
                const wchar_t* message = nullptr, const __LineInfo* lineInfo = nullptr)
            {
                bool ok = (abs(expected.left - actual.left) <= tolerance &&
                    abs(expected.top - actual.top) <= tolerance &&
                    abs(expected.right - actual.right) <= tolerance &&
                    abs(expected.bottom - actual.bottom) <= tolerance);

                if (!ok)
                {
                    Assert::Fail(
                        (std::wstring(L"Expected: ") + ToString(expected) +
                            L", Actual: " + ToString(actual) +
                            L", Tolerance: " + std::to_wstring(tolerance)).c_str(),
                        lineInfo);
                }
            }

        } // namespace CppUnitTestFramework
    } // namespace VisualStudio
} // namespace Microsoft
