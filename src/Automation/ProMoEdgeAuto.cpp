/* ==========================================================================

	Copyright © 2026 Technical University of Denmark

	CProMoEdgeAuto

	Author :		Giovanni Meroni

	Purpose :		"CProMoEdgeAuto" is an automation object that
					represents an edge in a diagram. It provides methods
					to access the source and the destination blocks of the edge, 
					and the segments composing it.

	Description :	"CProMoEdgeAuto" provides the implementation of the
					methods and properties that are common to all edges.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoEdgeAuto.h"
#include "ProMoEdgeSegmentsAuto.h"
#include "ProMoBlockAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeAuto

IMPLEMENT_DYNCREATE(CProMoEdgeAuto, CProMoElementAuto)

CProMoEdgeAuto::CProMoEdgeAuto()
{
	m_pSegments = NULL;
}

CProMoEdgeModel* CProMoEdgeAuto::GetEdgeModel() {
	
	return dynamic_cast<CProMoEdgeModel*>(GetModel());
}

CProMoEdgeSegmentsAuto* CProMoEdgeAuto::GetSegmentsAutoObject()
{
	ThrowIfDetached();
	ThrowIfNoDiagramAutoObject();
	
	if (!m_pSegments) {
		m_pSegments = new CProMoEdgeSegmentsAuto();
		if (m_pSegments) {
			m_pSegments->SetElementAutoObject(this);
		}
	}
	return m_pSegments;
}

void CProMoEdgeAuto::ReleaseSegmentsAutoObject()
{
	if (m_pSegments) {
		m_pSegments->SetElementAutoObject(NULL);
		m_pSegments->GetIDispatch(FALSE)->Release();
		m_pSegments = NULL;
	}
}

CProMoEdgeAuto::~CProMoEdgeAuto()
{
}


void CProMoEdgeAuto::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
	ReleaseSegmentsAutoObject();
	CProMoElementAuto::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CProMoEdgeAuto, CProMoElementAuto)
	//{{AFX_MSG_MAP(CProMoEdgeAuto)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProMoEdgeAuto, CProMoElementAuto)
	//{{AFX_DISPATCH_MAP(CProMoEdgeAuto)
	//Common to CProMoElementAuto
	DISP_PROPERTY_EX(CProMoEdgeAuto, "LockAspectRatio", GetLockAspectRatio, SetLockAspectRatio, VT_BOOL)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "LineColor", GetLineColor, SetLineColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "LineWidth", GetLineWidth, SetLineWidth, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "LineStyle", GetLineStyle, SetLineStyle, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "FontSize", GetFontSize, SetFontSize, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "BkMode", GetBkMode, SetBkMode, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "TextAlignment", GetTextAlignment, SetTextAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I2)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "ID", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Labels", GetLabels, SetLabels, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Properties", GetProperties, SetProperties, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Type", GetType, SetType, VT_BSTR)
	//Specific to CProMoEdgeAuto
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Source", GetSource, SetSource, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Destination", GetDestination, SetDestination, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Segments", GetSegments, SetSegments, VT_DISPATCH)
	//Common to CProMoElementAuto
	DISP_FUNCTION(CProMoEdgeAuto, "Copy", Copy, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeAuto, "Cut", Cut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeAuto, "Delete", Delete, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoEdgeAuto, "Duplicate", Duplicate, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoEdgeAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoEdgeAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoEdgeAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3762-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoEdgeAuto =
{ 0x18ea3762, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoEdgeAuto, CProMoElementAuto)
	INTERFACE_PART(CProMoEdgeAuto, IID_IProMoEdgeAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeAuto message handlers

LPDISPATCH CProMoEdgeAuto::GetSource() 
{
	if (GetEdgeModel()) {
		CProMoBlockModel* pSource = GetEdgeModel()->GetSource();
		if (pSource) {
			CProMoBlockAuto* pSourceAuto = dynamic_cast<CProMoBlockAuto*>(pSource->GetAutomationObject());
			if (pSourceAuto) {
				pSourceAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pSourceAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoEdgeAuto::SetSource(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoEdgeAuto::GetDestination() 
{
	if (GetEdgeModel()) {
		CProMoBlockModel* pDest = GetEdgeModel()->GetDestination();
		if (pDest) {
			CProMoBlockAuto* pDestAuto = dynamic_cast<CProMoBlockAuto*>(pDest->GetAutomationObject());
			if (pDestAuto) {
				pDestAuto->SetDiagramAutoObject(GetDiagramAutoObject());
				return pDestAuto->GetIDispatch(TRUE);
			}
		}
	}

	return NULL;
}

void CProMoEdgeAuto::SetDestination(LPDISPATCH newValue) 
{
	// TODO: Add your property handler here

}

LPDISPATCH CProMoEdgeAuto::GetSegments() 
{
	if (GetSegmentsAutoObject())
	{
		return GetSegmentsAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoEdgeAuto::SetSegments(LPDISPATCH newValue) 
{
	SetNotSupported();

}
