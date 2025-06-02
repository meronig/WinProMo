// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__742BE222_95D9_420F_89F0_B89A183076EC__INCLUDED_)
#define AFX_STDAFX_H__742BE222_95D9_420F_89F0_B89A183076EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#if _MSC_VER < 1100 //TODO: identify correct version
#ifndef UINT_PTR // fix for UINT_PTR not defined for older versions of Windows
typedef unsigned int UINT_PTR;
#endif
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#if _MSC_VER > 1100 //TODO: identify correct version
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif // _MSC_VER > 1000

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__742BE222_95D9_420F_89F0_B89A183076EC__INCLUDED_)
