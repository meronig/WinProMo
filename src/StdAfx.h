// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__742BE222_95D9_420F_89F0_B89A183076EC__INCLUDED_)
#define AFX_STDAFX_H__742BE222_95D9_420F_89F0_B89A183076EC__INCLUDED_

#if _MSC_VER >= 1020 // pragma once introduced with MSVC 4.2
#pragma once
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#if _MSC_VER < 1200 // fix for UINT_PTR and INT_PTR not defined before MSVC 6.0
#ifndef UINT_PTR 
typedef unsigned int UINT_PTR;
#endif
#ifndef INT_PTR
typedef int INT_PTR;
#endif
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>		// MFC OLE and automation support

#if _MSC_VER >= 1200 // MFC support for Internet Explorer 4 Common Controls introduced with MSVC 6.0
#include <afxdtctl.h>		
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#ifdef WINPROMO_EXPORTS
#define WINPROMO_API __declspec(dllexport)
#else
#define WINPROMO_API __declspec(dllimport)
#endif

#endif // !defined(AFX_STDAFX_H__742BE222_95D9_420F_89F0_B89A183076EC__INCLUDED_)

