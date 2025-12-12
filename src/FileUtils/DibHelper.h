/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _DIBHELPER_H_
#define _DIBHELPER_H_


class AFX_EXT_CLASS CDibHelper :
    public CObject
{
public:
    CDibHelper();
    ~CDibHelper();
    
    // Create a DIBSection. bitCount typically 24 or 32.
    BOOL Create(int width, int height, int bitCount = 24);

    // Destroy resources
    void Destroy();

    // Attach existing HBITMAP + BITMAPINFOHEADER (optionally)
    // If attachOwn == true CDib will DeleteObject(hBmp) in Destroy()
    BOOL Attach(HBITMAP hBmp, const BITMAPINFOHEADER* pBIH = NULL, BOOL attachOwn = TRUE);

    // Detach ownership of HBITMAP (caller becomes owner)
    HBITMAP DetachBitmap();

    // Accessors
    HBITMAP GetBitmap() const { return m_hBitmap; }
    void* GetBits() const { return m_pBits; }
    int      GetWidth() const { return m_width; }
    int      GetHeight() const { return m_height; }    // logical height (positive)
    int      GetBitCount() const { return m_bitCount; }
    int      GetRowBytes() const { return m_rowBytes; } // bytes per row (DWORD aligned)

    // Return pointer to internal BITMAPINFOHEADER (for StretchDIBits)
    const BITMAPINFOHEADER* GetBitmapInfoHeader() const { return &m_bmih; }

    // Save as a 24/32-bit BMP file. Returns true on success.
    BOOL SaveBMP(LPCTSTR path) const;

    // Copy as CF_DIB to the clipboard (hwnd may be NULL)
    BOOL CopyToClipboard(HWND hwnd = NULL) const;

private:
    HBITMAP m_hBitmap;
    void* m_pBits;
    BITMAPINFOHEADER m_bmih;
    int     m_width;
    int     m_height;   // positive height = number of rows
    int     m_bitCount;
    int     m_rowBytes;
    BOOL    m_ownsBitmap;

    // helper: convert top-down internal pixels to bottom-up buffer for BMP/CF_DIB
    // returns allocated HGLOBAL (caller must GlobalFree) containing BITMAPINFOHEADER + pixel data
    HGLOBAL CreateDibGlobalForClipboard() const;
};

#endif //_DIBHELPER_H_