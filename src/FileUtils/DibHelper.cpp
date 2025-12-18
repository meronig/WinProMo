/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CFileParser

	Author :		Giovanni Meroni

	Purpose :		"CDibHelperHelper" is a class to assist handling 
					device-independent bitmap images.

   ========================================================================*/
#include "stdafx.h"
#include "DibHelper.h"

CDibHelper::CDibHelper()
    : m_hBitmap(NULL)
    , m_pBits(NULL)
    , m_width(0)
    , m_height(0)
    , m_bitCount(0)
    , m_rowBytes(0)
    , m_ownsBitmap(FALSE)
/* ============================================================
    Function :		CDibHelper::CDibHelper
    Description :	Constructor.
    Access :		Public

    Return :		void
    Parameters :	none

    ============================================================*/
{
    ZeroMemory(&m_bmih, sizeof(m_bmih));
}

CDibHelper::~CDibHelper()
/* ============================================================
    Function :		CDibHelper::~CDibHelper
    Description :	Destructor.
    Access :		Public

    Return :		void
    Parameters :	none

    ============================================================*/
{
    Destroy();
}

void CDibHelper::Destroy()
/* ============================================================
    Function :		CDibHelper::Destroy
	Description :	Frees resources.
    Access :		Public

    Return :		void
    Parameters :	none

    ============================================================*/
{
    if (m_ownsBitmap && m_hBitmap)
        ::DeleteObject(m_hBitmap);
    m_hBitmap = NULL;
    m_pBits = NULL;
    ZeroMemory(&m_bmih, sizeof(m_bmih));
    m_width = m_height = m_bitCount = m_rowBytes = 0;
    m_ownsBitmap = FALSE;
}

BOOL CDibHelper::Create(int width, int height, int bitCount)
/* ============================================================
    Function :		CDibHelper::Destroy
	Description :	Creates a DIBSection with specified properties.
    Access :		Public

	Return :		BOOL            -   "TRUE" on success, 
                                        "FALSE" on failure.
	Parameters :	int width       -   width
					int height      -   height
					int bitCount    -   bits per pixel 
                                        (typically 24 or 32)

    ============================================================*/
{
    Destroy();

    if (width <= 0 || height <= 0)
        return FALSE;

    m_width = width;
    m_height = height;
    m_bitCount = bitCount;

    // compute row bytes (DWORD aligned)
    m_rowBytes = ((m_width * m_bitCount + 31) / 32) * 4;

    // Prepare BITMAPINFOHEADER for a top-down DIB (negative height)
    m_bmih.biSize = sizeof(BITMAPINFOHEADER);
    m_bmih.biWidth = m_width;
    m_bmih.biHeight = -m_height; // top-down for easy drawing
    m_bmih.biPlanes = 1;
    m_bmih.biBitCount = (WORD)m_bitCount;
    m_bmih.biCompression = BI_RGB;
    m_bmih.biSizeImage = m_rowBytes * m_height;
    m_bmih.biXPelsPerMeter = 0;
    m_bmih.biYPelsPerMeter = 0;
    m_bmih.biClrUsed = 0;
    m_bmih.biClrImportant = 0;

    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader = m_bmih;

    // CreateDIBSection with NULL hSection -> memory managed by GDI; returns pointer to pixel bits
    HDC screenDC = ::GetDC(NULL);
    m_hBitmap = ::CreateDIBSection(screenDC, &bmi, DIB_RGB_COLORS, &m_pBits, NULL, 0);
    ::ReleaseDC(NULL, screenDC);

    if (!m_hBitmap || !m_pBits)
    {
        Destroy();
        return FALSE;
    }

    m_ownsBitmap = TRUE;
    return TRUE;
}

BOOL CDibHelper::Attach(HBITMAP hBmp, const BITMAPINFOHEADER* pBIH, BOOL attachOwn)
/* ============================================================
    Function :		CDibHelper::Attach
    Description :	Attaches an existing HBITMAP to the CDibHelper.
                    If pBIH is NULL, the BITMAPINFOHEADER is built
                    from the HBITMAP properties.
                    If attachOwn == TRUE, the CDibHelper will
					DeleteObject(hBmp) in Destroy().
    Access :		Public

    Return :		BOOL                    -   "TRUE" on success,
                                                "FALSE" on failure.
	Parameters :	HBITMAP hBmp            -   bitmap handle to 
                                                attach
                    BITMAPINFOHEADER* pBIH  -   optional pointer to 
												BITMAPINFOHEADER
                    BOOL attachOwn          -   "TRUE" if CDibHelper 
                                                assumes ownership of 
												hBmp

    ============================================================*/
{
    Destroy();
    if (!hBmp) return FALSE;

    // Query bitmap properties
    BITMAP bm;
    if (::GetObject(hBmp, sizeof(bm), &bm) == 0)
        return FALSE;

    // If caller provided BITMAPINFOHEADER, use it; else build a conservative header
    if (pBIH)
    {
        m_bmih = *pBIH;
        m_width = m_bmih.biWidth;
        m_height = abs(m_bmih.biHeight);
        m_bitCount = m_bmih.biBitCount;
    }
    else
    {
        m_width = bm.bmWidth;
        m_height = bm.bmHeight;
        m_bitCount = bm.bmBitsPixel;
        ZeroMemory(&m_bmih, sizeof(m_bmih));
        m_bmih.biSize = sizeof(BITMAPINFOHEADER);
        m_bmih.biWidth = m_width;
        m_bmih.biHeight = -m_height; // assume top-down
        m_bmih.biPlanes = 1;
        m_bmih.biBitCount = (WORD)m_bitCount;
        m_bmih.biCompression = BI_RGB;
        m_bmih.biSizeImage = ((m_width * m_bitCount + 31) / 32) * 4 * m_height;
    }

    // Obtain bits pointer via GetDIBits (if possible)
    HDC hdc = ::GetDC(NULL);
    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(bmi));
    bmi.bmiHeader = m_bmih;
    // allocate temp buffer
    // Try to allocate bits buffer by calling GetDIBits with NULL to compute size
    int rowsCopied = ::GetDIBits(hdc, hBmp, 0, m_height, NULL, &bmi, DIB_RGB_COLORS);
    // Now create a DIBSection and copy bits into it
    void* pBits = NULL;
    HBITMAP hNew = ::CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
    if (!hNew)
    {
        ::ReleaseDC(NULL, hdc);
        return FALSE;
    }
    // Copy pixels
    ::GetDIBits(hdc, hBmp, 0, m_height, pBits, &bmi, DIB_RGB_COLORS);
    ::ReleaseDC(NULL, hdc);

    // Attach the newly created DIBSection
    m_hBitmap = hNew;
    m_pBits = pBits;
    m_ownsBitmap = TRUE;
    // overwrite m_bmih with bmi (in case it changed)
    m_bmih = bmi.bmiHeader;
    m_width = m_bmih.biWidth;
    m_height = abs(m_bmih.biHeight);
    m_bitCount = m_bmih.biBitCount;
    m_rowBytes = ((m_width * m_bitCount + 31) / 32) * 4;

    // If caller wanted to keep original hBmp, we didn't delete it.
    return TRUE;
}

HBITMAP CDibHelper::DetachBitmap()
/* ============================================================
    Function :		CDibHelper::DetachBitmap
    Description :	Detaches ownership of the HBITMAP from the 
                    CDibHelper. Caller becomes owner of the 
                    HBITMAP.
    Access :		Public

	Return :		HBITMAP     -   bitmap handle
    Parameters :	none

    ============================================================*/
{
    HBITMAP h = m_hBitmap;
    m_hBitmap = NULL;
    m_pBits = NULL;
    m_ownsBitmap = FALSE;
    ZeroMemory(&m_bmih, sizeof(m_bmih));
    m_width = m_height = m_bitCount = m_rowBytes = 0;
    return h;
}

static inline const BYTE* RowPtrTopDown(const BYTE* base, int rowBytes, int y)
/* ============================================================
    Function :		RowPtrTopDown
    Description :	Returns pointer to the start of row y in a 
					top-down bitmap.

	Return :		BYTE*   -   Pointer to the start of row y
    Parameters :	BYTE*   -   base pointer
                    int     -   row bytes
					int     -   y coordinate (from top)

    ============================================================*/
{
    return base + (size_t)y * rowBytes;
}
static inline BYTE* RowPtrBottomUp(BYTE* base, int rowBytes, int yFromBottom)
/* ============================================================
    Function :		RowPtrBottomUp
    Description :	Returns pointer to the start of row y in a 
					bottom-up bitmap.

    Return :		BYTE*   -   Pointer to the start of row y
    Parameters :	BYTE*   -   base pointer
                    int     -   row bytes
                    int     -   y coordinate (from bottom)

    ============================================================*/
{
    return base + (size_t)yFromBottom * rowBytes;
}

HGLOBAL CDibHelper::CreateDibGlobalForClipboard() const
/* ============================================================
    Function :		CDibHelper::CreateDibGlobalForClipboard
    Description :	Builds a global memory block containing
                    a DIB (BITMAPINFOHEADER + pixel data)
                    suitable for placing on the clipboard
                    with CF_DIB format. Converts internal
					top-down pixel data to bottom-up format.
    Access :		Public

	Return :		HGLOBAL     -   global memory handle
    Parameters :	none

    ============================================================*/
{
    if (!m_pBits) return NULL;

    // Prepare BITMAPINFOHEADER for bottom-up (positive height)
    BITMAPINFOHEADER bih = m_bmih;
    BITMAPINFOHEADER bihOut = bih;
    bihOut.biHeight = m_height; // positive -> bottom-up
    bihOut.biSizeImage = m_rowBytes * m_height;

    size_t totalSize = sizeof(BITMAPINFOHEADER) + (size_t)bihOut.biSizeImage;
    HGLOBAL hGlobal = ::GlobalAlloc(GHND | GMEM_SHARE, totalSize);
    if (!hGlobal) return NULL;

    BYTE* p = (BYTE*)::GlobalLock(hGlobal);
    // Copy header
    memcpy(p, &bihOut, sizeof(bihOut));
    BYTE* dstBits = p + sizeof(bihOut);

    // Convert top-down internal to bottom-up for clipboard/BMP
    const BYTE* srcBase = (const BYTE*)m_pBits;
    for (int row = 0; row < m_height; ++row)
    {
        // src row from top-down: row
        const BYTE* srcRow = RowPtrTopDown(srcBase, m_rowBytes, row);
        // dst row bottom-up: (height - 1 - row)
        BYTE* dstRow = dstBits + (size_t)(m_height - 1 - row) * m_rowBytes;
        memcpy(dstRow, srcRow, m_rowBytes);
    }

    ::GlobalUnlock(hGlobal);
    return hGlobal;
}

void* CDibHelper::GetBits() const
/* ============================================================
    Function :		CDibHelper::GetBits
    Description :	Returns pointer to DIB pixel bits.
    Access :		Public
    Return :		void*   -   pointer to pixel bits
    Parameters :	none
    ============================================================*/
{
	return m_pBits;
}

int CDibHelper::GetWidth() const
/* ============================================================
    Function :		CDibHelper::GetWidth
    Description :	Returns DIB width.
    Access :		Public

    Return :		int   -   DIB width
    Parameters :	none

    ============================================================*/
{
    return m_width;
}

int CDibHelper::GetHeight() const
/* ============================================================
    Function :		CDibHelper::GetHeight
	Description :	Returns DIB height.
    Access :		Public

	Return :		int   -   DIB height
    Parameters :	none

    ============================================================*/
{
    return m_height;
}

int CDibHelper::GetBitCount() const
/* ============================================================
    Function :		CDibHelper::GetBitCount
	Description :	Returns bits per pixel.
    Access :		Public

	Return :		int   -   bits per pixel
    Parameters :	none

    ============================================================*/
{
    return m_bitCount;
}

int CDibHelper::GetRowBytes() const
/* ============================================================
    Function :		CDibHelper::GetRowBytes
	Description :	Returns number of bytes per row.
    Access :		Public

	Return :		int   -   number of bytes per row
    Parameters :	none

    ============================================================*/
{
    return m_rowBytes;
}

HBITMAP CDibHelper::GetBitmap() const
/* ============================================================
    Function :		CDibHelper::GetBitmap
	Description :	Returns the HBITMAP handle.
    Access :		Public

	Return :		HBITMAP   -   HBITMAP handle
    Parameters :	none

    ============================================================*/
{
    return m_hBitmap;
}

const BITMAPINFOHEADER* CDibHelper::GetBitmapInfoHeader() const
/* ============================================================
    Function :		CDibHelper::GetBitmapInfoHeader
	Description :	Returns pointer to internal BITMAPINFOHEADER.
    Access :		Public

    Return :		BITMAPINFOHEADER*   -   Pointer to 
										    BITMAPINFOHEADER
    Parameters :	none

    ============================================================*/
{
    return &m_bmih;
}

BOOL CDibHelper::SaveBMP(LPCTSTR path) const
/* ============================================================
    Function :		CDibHelper::SaveBMP
	Description :	Saves the DIB as a BMP file to disk.
    Access :		Public

    Return :		BOOL            -   "TRUE" on success,
                                        "FALSE" on failure.
	Parameters :	LPCTSTR path    -   path to save BMP file to

    ============================================================*/
{
    if (!m_pBits) return FALSE;

    // Build BITMAPFILEHEADER and BITMAPINFOHEADER (bottom-up positive height)
    BITMAPFILEHEADER bfh;
    ZeroMemory(&bfh, sizeof(bfh));
    bfh.bfType = 0x4D42; // 'BM'

    BITMAPINFOHEADER bihOut = m_bmih;
    bihOut.biHeight = m_height; // positive (bottom-up)
    bihOut.biSizeImage = m_rowBytes * m_height;

    size_t dibSize = sizeof(BITMAPINFOHEADER) + bihOut.biSizeImage;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    bfh.bfSize = (DWORD)(bfh.bfOffBits + bihOut.biSizeImage);
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;

    CFile file;
    if (!file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
        return FALSE;

    // Write headers
    file.Write(&bfh, sizeof(bfh));
    file.Write(&bihOut, sizeof(bihOut));

    // Write pixel data bottom-up
    const BYTE* srcBase = (const BYTE*)m_pBits;
    // For each row of bottom-up BMP, write row (height-1 .. 0)
    for (int row = m_height - 1; row >= 0; --row)
    {
        const BYTE* srcRow = RowPtrTopDown(srcBase, m_rowBytes, row); // top-down internal
        file.Write(srcRow, m_rowBytes);
    }

    file.Close();
    return TRUE;
}