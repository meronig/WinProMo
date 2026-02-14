/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoLabelAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoLabelAuto" is an automation object that
					represents a label in a diagram. It provides methods
					to access the property whose value is displayed by the 
					label (if any), to copy, cut, delete, and duplicate the 
					label, to change its visual appearance (fill color, 
					fill pattern, etc.), and to move and resize it.

	Description :	"CProMoLabelAuto" provides the implementation of the
					methods and properties that are common to all labels.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoLabelAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelAuto

IMPLEMENT_DYNCREATE(CProMoLabelAuto, CProMoElementChildAuto)

CProMoLabelAuto::CProMoLabelAuto()
{
}

CProMoLabelAuto::~CProMoLabelAuto()
{
}

BEGIN_MESSAGE_MAP(CProMoLabelAuto, CProMoElementChildAuto)
	//{{AFX_MSG_MAP(CProMoLabelAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoLabelAuto, CProMoElementChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoLabelAuto)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Top", GetTop, SetTop, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Bottom", GetBottom, SetBottom, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Left", GetLeft, SetLeft, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Right", GetRight, SetRight, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Width", GetWidth, SetWidth, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Height", GetHeight, SetHeight, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontSize", GetFontSize, SetFontSize, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "BkMode", GetBkMode, SetBkMode, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextAlignment", GetTextAlignment, SetTextAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Property", GetProperty, SetProperty, VT_DISPATCH)
	DISP_FUNCTION(CProMoLabelAuto, "Cut", Cut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Copy", Copy, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Delete", Delete, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Duplicate", Duplicate, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoLabelAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {18EA3776-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoLabelAuto =
{ 0x18ea3776, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoLabelAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoLabelAuto, IID_IProMoLabelAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelAuto message handlers

double CProMoLabelAuto::GetTop() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoLabelAuto::SetTop(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoLabelAuto::GetBottom() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoLabelAuto::SetBottom(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoLabelAuto::GetLeft() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoLabelAuto::SetLeft(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoLabelAuto::GetRight() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoLabelAuto::SetRight(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoLabelAuto::GetWidth() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoLabelAuto::SetWidth(double newValue) 
{
	// TODO: Add your property handler here

}

double CProMoLabelAuto::GetHeight() 
{
	// TODO: Add your property handler here

	return 0.0;
}

void CProMoLabelAuto::SetHeight(double newValue) 
{
	// TODO: Add your property handler here

}

BSTR CProMoLabelAuto::GetFontName() 
{
	CString strResult;
	// TODO: Add your property handler here

	return strResult.AllocSysString();
}

void CProMoLabelAuto::SetFontName(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoLabelAuto::GetFontSize() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoLabelAuto::SetFontSize(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoLabelAuto::GetFontWeight() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoLabelAuto::SetFontWeight(long nNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoLabelAuto::GetFontItalic() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoLabelAuto::SetFontItalic(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoLabelAuto::GetFontUnderline() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoLabelAuto::SetFontUnderline(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoLabelAuto::GetFontStrikeOut() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoLabelAuto::SetFontStrikeOut(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

OLE_COLOR CProMoLabelAuto::GetTextColor() 
{
	// TODO: Add your property handler here

	return RGB(0,0,0);
}

void CProMoLabelAuto::SetTextColor(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here

}

OLE_COLOR CProMoLabelAuto::GetBkColor() 
{
	// TODO: Add your property handler here

	return RGB(0,0,0);
}

void CProMoLabelAuto::SetBkColor(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoLabelAuto::GetBkMode() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoLabelAuto::SetBkMode(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoLabelAuto::GetTextAlignment() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoLabelAuto::SetTextAlignment(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoLabelAuto::GetTextHorizontalAlignment() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoLabelAuto::SetTextHorizontalAlignment(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoLabelAuto::GetTextVerticalAlignment() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoLabelAuto::SetTextVerticalAlignment(long nNewValue) 
{
	// TODO: Add your property handler here

}

void CProMoLabelAuto::Cut() 
{
	// TODO: Add your dispatch handler code here

}

void CProMoLabelAuto::Copy() 
{
	// TODO: Add your dispatch handler code here

}

void CProMoLabelAuto::Delete() 
{
	// TODO: Add your dispatch handler code here

}

LPDISPATCH CProMoLabelAuto::Duplicate() 
{
	// TODO: Add your dispatch handler code here

	return NULL;
}

LPDISPATCH CProMoLabelAuto::GetProperty() 
{
	// TODO: Add your property handler here

	return NULL;
}

void CProMoLabelAuto::SetProperty(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}
