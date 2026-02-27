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
#include "ProMoPropertyAuto.h"

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

CProMoLabel* CProMoLabelAuto::GetLabel()
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();
	
	return dynamic_cast<CProMoLabel*>(m_pInternalObject);
}

CProMoElementAuto* CProMoLabelAuto::GetElementAutoObject() const
{
	ThrowIfNoDiagramAutoObject();
	return m_pElementAuto;
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
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontSize", GetFontSize, SetFontSize, VT_I2)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I2)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "BkMode", GetBkMode, SetBkMode, VT_I2)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextMultiLine", GetTextMultiLine, SetTextMultiLine, VT_BOOL)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoLabelAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoLabelAuto, "ID", GetID, SetID, VT_BSTR)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Property", GetProperty, SetProperty, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Top", GetTop, SetTop, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Bottom", GetBottom, SetBottom, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Left", GetLeft, SetLeft, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Right", GetRight, SetRight, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Width", GetWidth, SetWidth, VT_R8)
	DISP_PROPERTY_EX(CProMoLabelAuto, "Height", GetHeight, SetHeight, VT_R8)
	DISP_FUNCTION(CProMoLabelAuto, "Cut", Cut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Copy", Copy, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Delete", Delete, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoLabelAuto, "Duplicate", Duplicate, VT_DISPATCH, VTS_NONE)
	//Common to CProMoElementChildAuto
	DISP_FUNCTION(CProMoElementChildAuto, "Element", Element, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoLabelAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3767-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoLabelAuto =
{ 0x38ea3767, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoLabelAuto, CProMoElementChildAuto)
	INTERFACE_PART(CProMoLabelAuto, IID_IProMoLabelAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoLabelAuto message handlers

double CProMoLabelAuto::GetTop() 
{
	if (GetLabel()) {
		return GetLabel()->GetTop();
	}

	return 0.0;
}

void CProMoLabelAuto::SetTop(double newValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(GetLabel()->GetLeft(), newValue, GetLabel()->GetRight(), GetLabel()->GetBottom() - GetLabel()->GetTop() + newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetBottom() 
{
	if (GetLabel()) {
		return GetLabel()->GetBottom();
	}

	return 0.0;
}

void CProMoLabelAuto::SetBottom(double newValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(GetLabel()->GetLeft(), GetLabel()->GetTop() - GetLabel()->GetBottom() + newValue, GetLabel()->GetRight(), newValue);
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetLeft() 
{
	if (GetLabel()) {
		return GetLabel()->GetLeft();
	}

	return 0.0;
}

void CProMoLabelAuto::SetLeft(double newValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(newValue, GetLabel()->GetTop(), GetLabel()->GetRight() - GetLabel()->GetLeft() + newValue, GetLabel()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetRight() 
{
	if (GetLabel()) {
		return GetLabel()->GetRight();
	}

	return 0.0;
}

void CProMoLabelAuto::SetRight(double newValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetRect(GetLabel()->GetLeft() - GetLabel()->GetRight() + newValue, GetLabel()->GetTop(), newValue, GetLabel()->GetBottom());
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetWidth() 
{
	if (GetLabel()) {
		return GetLabel()->GetRect().Width();
	}

	return 0.0;
}

void CProMoLabelAuto::SetWidth(double newValue) 
{
	if (GetLabel()) {

		CDoubleRect oldRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetRight(), GetLabel()->GetBottom());
		CDoubleRect newRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetLeft() + newValue, GetLabel()->GetBottom());

		GetContainer()->Snapshot();
		GetLabel()->SetRect(newRect.ToCRect());
		GetLabel()->AutoResize();
		GetDiagramAutoObject()->NotifyChange();

	}

}

double CProMoLabelAuto::GetHeight() 
{
	if (GetLabel()) {
		return GetLabel()->GetRect().Height();
	}

	return 0.0;
}

void CProMoLabelAuto::SetHeight(double newValue) 
{
	if (GetLabel()) {
		CDoubleRect oldRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetRight(), GetLabel()->GetBottom());
		CDoubleRect newRect(GetLabel()->GetLeft(), GetLabel()->GetTop(), GetLabel()->GetRight(), GetLabel()->GetTop() + newValue);

		GetContainer()->Snapshot();
		GetLabel()->SetRect(newRect.ToCRect());
		GetLabel()->AutoResize();
		GetDiagramAutoObject()->NotifyChange();

	}

}

BSTR CProMoLabelAuto::GetFontName() 
{
	CString strResult;
	
	if (GetLabel()) {
		strResult = GetLabel()->GetFontName();
	}

	return strResult.AllocSysString();
}

void CProMoLabelAuto::SetFontName(LPCTSTR lpszNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetFontName(lpszNewValue);
		GetDiagramAutoObject()->NotifyChange();
	}

}

short CProMoLabelAuto::GetFontSize() 
{
	if (GetLabel()) {
		return GetLabel()->GetFontSize();
	}

	return 0;
}

void CProMoLabelAuto::SetFontSize(short nNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetFontSize(nNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
}

short CProMoLabelAuto::GetFontWeight() 
{
	if (GetLabel()) {
		return GetLabel()->GetFontWeight();
	}

	return 0;
}

void CProMoLabelAuto::SetFontWeight(short nNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetFontWeight(nNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
}

BOOL CProMoLabelAuto::GetFontItalic() 
{
	if (GetLabel()) {
		return GetLabel()->IsFontItalic();
	}

	return TRUE;
}

void CProMoLabelAuto::SetFontItalic(BOOL bNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetFontItalic(bNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
}

BOOL CProMoLabelAuto::GetFontUnderline() 
{
	if (GetLabel()) {
		return GetLabel()->IsFontUnderline();
	}

	return TRUE;
}

void CProMoLabelAuto::SetFontUnderline(BOOL bNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetFontUnderline(bNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
}

BOOL CProMoLabelAuto::GetFontStrikeOut() 
{
	if (GetLabel()) {
		return GetLabel()->IsFontStrikeOut();
	}

	return TRUE;
}

void CProMoLabelAuto::SetFontStrikeOut(BOOL bNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetFontStrikeOut(bNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
}

OLE_COLOR CProMoLabelAuto::GetTextColor() 
{
	if (GetLabel()) {
		COLORREF color = GetLabel()->GetTextColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoLabelAuto::SetTextColor(OLE_COLOR nNewValue) 
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	if (FAILED(hr))
		AfxThrowOleException(hr);
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetTextColor(color);
		GetDiagramAutoObject()->NotifyChange();

	}
}

OLE_COLOR CProMoLabelAuto::GetBkColor() 
{
	if (GetLabel()) {
		COLORREF color = GetLabel()->GetBkColor();
		return RGB(GetRValue(color), GetGValue(color), GetBValue(color));
	}

	return RGB(0,0,0);
}

void CProMoLabelAuto::SetBkColor(OLE_COLOR nNewValue) 
{
	COLORREF color;
	HRESULT hr = OleTranslateColor(nNewValue, NULL, &color);
	if (FAILED(hr))
		AfxThrowOleException(hr);
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetBkColor(color);
		GetDiagramAutoObject()->NotifyChange();

	}
}

short CProMoLabelAuto::GetBkMode() 
{
	if (GetLabel()) {
		return GetLabel()->GetBkMode();
	}

	return 0;
}

void CProMoLabelAuto::SetBkMode(short nNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetBkMode(nNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
}

short CProMoLabelAuto::GetTextHorizontalAlignment() 
{
	if (GetLabel()) {
		return GetLabel()->GetTextHorizontalAlignment();
	}

	return 0;
}

void CProMoLabelAuto::SetTextHorizontalAlignment(short nNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetTextHorizontalAlignment(nNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
}

short CProMoLabelAuto::GetTextVerticalAlignment() 
{
	if (GetLabel()) {
		return GetLabel()->GetTextVerticalAlignment();
	}

	return 0;
}

void CProMoLabelAuto::SetTextVerticalAlignment(short nNewValue) 
{
	if (GetLabel()) {
		GetContainer()->Snapshot();
		GetLabel()->SetTextVerticalAlignment(nNewValue);
		GetDiagramAutoObject()->NotifyChange();

	}
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
	if (GetLabel()) {
		CProMoProperty* pProperty = GetLabel()->GetProperty();
		if (pProperty) {
			CProMoPropertyAuto* pPropertyAuto = dynamic_cast<CProMoPropertyAuto*>(pProperty->GetAutomationObject());
			if (pPropertyAuto) {
				pPropertyAuto->SetElementAutoObject(GetElementAutoObject());
				return pPropertyAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoLabelAuto::SetProperty(LPDISPATCH newValue) 
{
	SetNotSupported();

}

BSTR CProMoLabelAuto::GetID() 
{
	CString strResult;
	// TODO: Add your property handler here

	return strResult.AllocSysString();
}

void CProMoLabelAuto::SetID(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoLabelAuto::GetTextMultiLine() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoLabelAuto::SetTextMultiLine(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}
