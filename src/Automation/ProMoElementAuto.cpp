/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoElementAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoElementAuto" is an automation object that
					represents an element in a diagram. It provides methods
					to access the properties and the labels of the element, 
					to copy, cut, delete, and duplicate the element, and to 
					change its visual appearance (line color, line width, etc.).

	Description :	"CProMoElementAuto" provides the implementation of the
					methods and properties that are common to all diagram 
					elements.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoElementAuto.h"
#include "..\ProMoEditor\ProMoModel.h"
#include "ProMoLabelsAuto.h"
#include "ProMoPropertiesAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoElementAuto

IMPLEMENT_DYNCREATE(CProMoElementAuto, CProMoDiagramChildAuto)

CProMoElementAuto::CProMoElementAuto()
{
	m_pLabels = NULL;
	m_pProperties = NULL;
}

CProMoModel* CProMoElementAuto::GetModel()
{
	ThrowIfDetached();

	return dynamic_cast<CProMoModel*>(m_pInternalObject);
}

CProMoElementAuto::~CProMoElementAuto()
{
}

CProMoLabelsAuto* CProMoElementAuto::GetLabelsAutoObject()
{
	if (!m_pLabels) {
		m_pLabels = new CProMoLabelsAuto();
		if (m_pLabels) {
			m_pLabels->SetElementAutoObject(this);
		}
	}
	return m_pLabels;
}

void CProMoElementAuto::ReleaseLabelsAutoObject()
{
	if (m_pLabels) {
		m_pLabels->SetElementAutoObject(NULL);
		m_pLabels->GetIDispatch(FALSE)->Release();
		m_pLabels = NULL;
	}
}

CProMoPropertiesAuto* CProMoElementAuto::GetPropertiesAutoObject()
{
	if (!m_pProperties) {
		m_pProperties = new CProMoPropertiesAuto();
		if (m_pProperties) {
			m_pProperties->SetElementAutoObject(this);
		}
	}
	return m_pProperties;
}

void CProMoElementAuto::ReleasePropertiesAutoObject()
{
	if (m_pProperties) {
		m_pProperties->SetElementAutoObject(NULL);
		m_pProperties->GetIDispatch(FALSE)->Release();
		m_pProperties = NULL;
	}
}


void CProMoElementAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
	ReleasePropertiesAutoObject();
	ReleaseLabelsAutoObject();
	CProMoDiagramChildAuto::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CProMoElementAuto, CProMoDiagramChildAuto)
	//{{AFX_MSG_MAP(CProMoElementAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoElementAuto, CProMoDiagramChildAuto)
	//{{AFX_DISPATCH_MAP(CProMoElementAuto)
	DISP_PROPERTY_EX(CProMoElementAuto, "LockAspectRatio", GetLockAspectRatio, SetLockAspectRatio, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineColor", GetLineColor, SetLineColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineWidth", GetLineWidth, SetLineWidth, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineStyle", GetLineStyle, SetLineStyle, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontSize", GetFontSize, SetFontSize, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkMode", GetBkMode, SetBkMode, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextAlignment", GetTextAlignment, SetTextAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "Name", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "Labels", GetLabels, SetLabels, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Properties", GetProperties, SetProperties, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Type", GetType, SetType, VT_BSTR)
	DISP_FUNCTION(CProMoElementAuto, "Copy", Copy, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Cut", Cut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Delete", Delete, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Duplicate", Duplicate, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoElementAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {7E3C6CD5-01D3-11F1-9743-000C2976A615}
static const IID IID_IProMoElementAuto =
{ 0x7e3c6cd5, 0x1d3, 0x11f1, { 0x97, 0x43, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoElementAuto, CProMoDiagramChildAuto)
	INTERFACE_PART(CProMoElementAuto, IID_IProMoElementAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoElementAuto message handlers

void CProMoElementAuto::Copy() 
{
	// TODO: Add your dispatch handler code here

}

void CProMoElementAuto::Cut() 
{
	// TODO: Add your dispatch handler code here

}

void CProMoElementAuto::Delete() 
{
	// TODO: Add your dispatch handler code here

}

LPDISPATCH CProMoElementAuto::Duplicate() 
{
	// TODO: Add your dispatch handler code here

	return NULL;
}

BOOL CProMoElementAuto::GetLockAspectRatio() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoElementAuto::SetLockAspectRatio(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

OLE_COLOR CProMoElementAuto::GetLineColor() 
{
	// TODO: Add your property handler here

	return RGB(0,0,0);
}

void CProMoElementAuto::SetLineColor(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetLineWidth() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetLineWidth(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetLineStyle() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetLineStyle(long nNewValue) 
{
	// TODO: Add your property handler here

}

BSTR CProMoElementAuto::GetFontName() 
{
	CString strResult;
	// TODO: Add your property handler here

	return strResult.AllocSysString();
}

void CProMoElementAuto::SetFontName(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetFontSize() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetFontSize(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetFontWeight() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetFontWeight(long nNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoElementAuto::GetFontItalic() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoElementAuto::SetFontItalic(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoElementAuto::GetFontUnderline() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoElementAuto::SetFontUnderline(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

BOOL CProMoElementAuto::GetFontStrikeOut() 
{
	// TODO: Add your property handler here

	return TRUE;
}

void CProMoElementAuto::SetFontStrikeOut(BOOL bNewValue) 
{
	// TODO: Add your property handler here

}

OLE_COLOR CProMoElementAuto::GetTextColor() 
{
	// TODO: Add your property handler here

	return RGB(0,0,0);
}

void CProMoElementAuto::SetTextColor(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here

}

OLE_COLOR CProMoElementAuto::GetBkColor() 
{
	// TODO: Add your property handler here

	return RGB(0,0,0);
}

void CProMoElementAuto::SetBkColor(OLE_COLOR nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetBkMode() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetBkMode(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetTextAlignment() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetTextAlignment(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetTextHorizontalAlignment() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetTextHorizontalAlignment(long nNewValue) 
{
	// TODO: Add your property handler here

}

long CProMoElementAuto::GetTextVerticalAlignment() 
{
	// TODO: Add your property handler here

	return 0;
}

void CProMoElementAuto::SetTextVerticalAlignment(long nNewValue) 
{
	// TODO: Add your property handler here

}

BSTR CProMoElementAuto::GetName() 
{
	CString strResult;
	// TODO: Add your property handler here

	return strResult.AllocSysString();
}

void CProMoElementAuto::SetName(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoElementAuto::GetLabels() 
{
	if (GetLabelsAutoObject())
	{
		return GetLabelsAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoElementAuto::SetLabels(LPDISPATCH newValue) 
{
	SetNotSupported();

}

LPDISPATCH CProMoElementAuto::GetProperties() 
{
	if (GetPropertiesAutoObject())
	{
		return GetPropertiesAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoElementAuto::SetProperties(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}

BSTR CProMoElementAuto::GetType() 
{
	ThrowIfNoDiagramAutoObject();

	CString strResult;
	if (GetModel()) {
		strResult = GetModel()->GetType();
	}
	
	return strResult.AllocSysString();
}

void CProMoElementAuto::SetType(LPCTSTR lpszNewValue) 
{
	// TODO: Add your property handler here

}
