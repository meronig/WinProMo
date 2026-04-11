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
/* ============================================================
	Function :		CProMoEdgeAuto::CProMoEdgeAuto
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	m_pSegments = NULL;
}

CProMoEdgeModel* CProMoEdgeAuto::GetEdgeModel() 
/* ============================================================
	Function :		CProMoEdgeAuto::GetEdgeModel
	Description :	Get the edge model associated with this edge
	Access :		Public
	Return :		CProMoEdgeModel*	-	the edge model 
											associated with 
											this edge
	Parameters :	none
   ============================================================ */
{
	return dynamic_cast<CProMoEdgeModel*>(GetModel());
}

CProMoEdgeSegmentsAuto* CProMoEdgeAuto::GetSegmentsAutoObject()
/* ============================================================
	Function :		CProMoEdgeAuto::GetSegmentsAutoObject
	Description :	Returns a pointer to the automation object that
					represents the collection of segments composing
					this edge. If the automation object does not
					exist, it is created.
	Access :		Public

	Return :		CProMoSubBlocksAuto*	-	a pointer to the
												automation object
												that represents the
												collection of
												segments composing 
												this edge.
	Parameters :	none
   ============================================================*/
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
/* ============================================================
	Function :		CProMoEdgeAuto::ReleaseSegmentsAutoObject
	Description :	Releases the automation object that represents
					the collection of segments composing this edge,
					if it exists.
	Access :		Public

	Return :		void
	Parameters :	none
   ============================================================*/
{
	if (m_pSegments) {
		m_pSegments->SetElementAutoObject(NULL);
		m_pSegments->GetIDispatch(FALSE)->Release();
		m_pSegments = NULL;
	}
}

BOOL CProMoEdgeAuto::SetSourceBlock(CProMoBlockModel* pSource)
/* ============================================================
	Function :		CProMoEdgeAuto::SetSourceBlock
	Description :	Sets the source block of this edge to the given
					block.
	Access :		Public
	Return :		BOOL						-	"TRUE" if the 
													source block has been
													successfully set, 
													"FALSE" otherwise
	Parameters :	CProMoBlockModel* pSource	-	a pointer to the 
													block model to be set 
													as source block of 
													this edge.
   ============================================================*/
{
	if (GetEdgeModel()) {
		CProMoBlockModel* pOldSource = GetEdgeModel()->GetSource();
		CProMoEdgeView* pFirstSegment = GetEdgeModel()->GetFirstSegment();
		if (pSource) {
			// check if the source has changed
			if (pSource != pOldSource) {
				// check if the edge can be connected
				if (GetEdgeModel()->CanConnectSource(pSource)) {
					GetContainer()->Snapshot();
					// disconnect from old source block (if any)
					pFirstSegment->SetSource(NULL);
					CRect blockRect = pSource->GetMainBlockView()->GetRect();
					if (!blockRect.PtInRect(pFirstSegment->GetRect().TopLeft())) {
						// move starting point of the edge inside new source block
						CDoublePoint center = CDoubleRect(blockRect).CenterPoint();
						pFirstSegment->SetRect(center.x, center.y, pFirstSegment->GetRight(), pFirstSegment->GetBottom());
					}
					pFirstSegment->SetSource(pSource->GetMainBlockView());
					GetDiagramAutoObject()->NotifyChange();
					return TRUE;
				}
			}
		}
		// NULL is passed
		else {
			if (!pOldSource) {
				GetContainer()->Snapshot();
				pFirstSegment->SetSource(NULL);
				GetDiagramAutoObject()->NotifyChange();
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

BOOL CProMoEdgeAuto::SetDestinationBlock(CProMoBlockModel* pDest)
/* ============================================================
	Function :		CProMoEdgeAuto::SetDestinationBlock
	Description :	Sets the destination block of this edge to the 
					given block.
	Access :		Public
	Return :		BOOL						-	"TRUE" if the 
													destination block has been
													successfully set, 
													"FALSE" otherwise
	Parameters :	CProMoBlockModel* pDest		-	a pointer to the 
													block model to be set 
													as destination block of 
													this edge.
   ============================================================*/
{
	if (GetEdgeModel()) {
		CProMoBlockModel* pOldDest = GetEdgeModel()->GetDestination();
		CProMoEdgeView* pLastSegment = GetEdgeModel()->GetLastSegment();
		if (pDest) {
			// check if the source has changed
			if (pDest != pOldDest) {
				// check if the edge can be connected
				if (GetEdgeModel()->CanConnectDestination(pDest)) {
					GetContainer()->Snapshot();
					// disconnect from old source block (if any)
					pLastSegment->SetDestination(NULL);
					CRect blockRect = pDest->GetMainBlockView()->GetRect();
					if (!blockRect.PtInRect(pLastSegment->GetRect().TopLeft())) {
						// move starting point of the edge inside new source block
						CDoublePoint center = CDoubleRect(blockRect).CenterPoint();
						pLastSegment->SetRect(pLastSegment->GetLeft(), pLastSegment->GetTop(), center.x, center.y);
					}
					pLastSegment->SetDestination(pDest->GetMainBlockView());
					GetDiagramAutoObject()->NotifyChange();
					return TRUE;
				}
			}
		}
		
		// NULL is passed
		else {
			if (!pOldDest) {
				GetContainer()->Snapshot();
				pLastSegment->SetDestination(NULL);
				GetDiagramAutoObject()->NotifyChange();
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

CProMoEdgeAuto::~CProMoEdgeAuto()
/* ============================================================
	Function :		CProMoEdgeAuto::~CProMoEdgeAuto
	Description :	Destructor
	Access :		Public
	Return :		void
	Parameters :	none
   ============================================================ */
{
}

CProMoEdgeAuto* CProMoEdgeAuto::FromIDispatch(LPDISPATCH obj)
/* ============================================================
	Function :		CProMoEdgeAuto::FromIDispatch
	Description :	Returns a pointer to the "CProMoEdgeAuto" 
					object that corresponds to the given IDispatch
					interface pointer.
	Access :		Public
	Return :		CProMoEdgeAuto*	-	a pointer to the 
										"CProMoEdgeAuto" object that 
										corresponds to the given 
										IDispatch interface pointer.
	Parameters :	LPDISPATCH obj	-	the IDispatch interface 
										pointer for which the 
										corresponding "CProMoEdgeAuto"
										object is to be returned.
   ============================================================*/
{
	CCmdTarget* pTarget = CCmdTarget::FromIDispatch(obj);

	if (!pTarget || !pTarget->IsKindOf(RUNTIME_CLASS(CProMoEdgeAuto))) {
		AfxThrowOleDispatchException(
			1001,
			_T("Invalid edge automation object"));
	}

	return (CProMoEdgeAuto*)pTarget;
}

CProMoEdgeModel* CProMoEdgeAuto::GetModelFromIDispatch(LPDISPATCH obj)
/* ============================================================
	Function :		CProMoEdgeAuto::GetModelFromIDispatch
	Description :	Returns a pointer to the "CProMoEdgeModel" 
					object that corresponds to the given IDispatch
					interface pointer.
	Access :		Public
	Return :		CProMoEdgeModel*	-	a pointer to the 
											"CProMoEdgeModel" object that 
											corresponds to the given 
											IDispatch interface pointer.
	Parameters :	LPDISPATCH obj		-	the IDispatch interface 
											pointer for which the 
											corresponding "CProMoEdgeModel"
											object is to be returned.
   ============================================================*/
{
	CProMoEdgeAuto* pAuto = FromIDispatch(obj);
	if (pAuto) {
		return pAuto->GetEdgeModel();
	}
	return NULL;
}

void CProMoEdgeAuto::OnFinalRelease()
/* ============================================================
	Function :		CProMoEdgeAuto::OnFinalRelease
	Description :	Release the automation object. Called when
					the last reference for an automation object
					is released. The base class will
					automatically delete the object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage:			Overridden to release the automation objects
					for the segments of this edge, if
					it exist. The base class implementation will
					delete the object when the application
					automation object is released.

   ============================================================*/

{
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
	DISP_PROPERTY_EX(CProMoElementAuto, "LineColor", GetLineColor, SetLineColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineWidth", GetLineWidth, SetLineWidth, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "LineStyle", GetLineStyle, SetLineStyle, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontName", GetFontName, SetFontName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontSize", GetFontSize, SetFontSize, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontWeight", GetFontWeight, SetFontWeight, VT_I2)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontItalic", GetFontItalic, SetFontItalic, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontUnderline", GetFontUnderline, SetFontUnderline, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "FontStrikeOut", GetFontStrikeOut, SetFontStrikeOut, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextColor", GetTextColor, SetTextColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkColor", GetBkColor, SetBkColor, VT_COLOR)
	DISP_PROPERTY_EX(CProMoElementAuto, "BkMode", GetBkMode, SetBkMode, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextMultiLine", GetTextMultiLine, SetTextMultiLine, VT_BOOL)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextHorizontalAlignment", GetTextHorizontalAlignment, SetTextHorizontalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "TextVerticalAlignment", GetTextVerticalAlignment, SetTextVerticalAlignment, VT_I4)
	DISP_PROPERTY_EX(CProMoElementAuto, "ID", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "Labels", GetLabels, SetLabels, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Properties", GetProperties, SetProperties, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoElementAuto, "Type", GetType, SetType, VT_BSTR)
	DISP_PROPERTY_EX(CProMoElementAuto, "LockFlags", GetLockFlags, SetLockFlags, VT_I2)
	//Specific to CProMoEdgeAuto
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Source", GetSource, SetSource, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Destination", GetDestination, SetDestination, VT_DISPATCH)
	DISP_PROPERTY_EX(CProMoEdgeAuto, "Segments", GetSegments, SetSegments, VT_DISPATCH)
	//Common to CProMoElementAuto
	DISP_FUNCTION(CProMoElementAuto, "Copy", Copy, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Cut", Cut, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Delete", Delete, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CProMoElementAuto, "Duplicate", Duplicate, VT_DISPATCH, VTS_NONE)
	//Common to CProMoDiagramChildAuto
	DISP_FUNCTION(CProMoDiagramChildAuto, "Diagram", Diagram, VT_DISPATCH, VTS_NONE)
	//Common to CProMoAppChildAuto
	DISP_FUNCTION(CProMoAppChildAuto, "Application", Application, VT_DISPATCH, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IProMoEdgeAuto to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {38EA3762-08C3-11F1-9744-000C2976A615}
static const IID IID_IProMoEdgeAuto =
{ 0x38ea3762, 0x8c3, 0x11f1, { 0x97, 0x44, 0x0, 0xc, 0x29, 0x76, 0xa6, 0x15 } };

BEGIN_INTERFACE_MAP(CProMoEdgeAuto, CProMoElementAuto)
	INTERFACE_PART(CProMoEdgeAuto, IID_IProMoEdgeAuto, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProMoEdgeAuto message handlers

LPDISPATCH CProMoEdgeAuto::GetSource() 
/* ============================================================
	Function :		CProMoEdgeAuto::GetSource
	Description :	Returns the source block of this edge.
	Access :		Public
	Return :		LPDISPATCH	-	a pointer to the IDispatch 
									interface of the source block 
									of this edge. "NULL" if no 
									source block is connected to 
									this edge.
	Parameters :	none
   ============================================================*/
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
/* ============================================================
	Function :		CProMoEdgeAuto::SetSource
	Description :	Sets the source block of this edge to the block
					corresponding to the given IDispatch interface
					pointer.
	Access :		Public
	Return :		void
	Parameters :	LPDISPATCH newValue	-	the IDispatch interface 
											pointer corresponding to 
											the block to be set as 
											source block of this edge. 
											If "NULL" is passed, the 
											source block of this edge 
											is set to "NULL".
   ============================================================*/
{
	// something is passed
	if (newValue) {
		// decode newValue
		CProMoBlockModel* pSource = CProMoBlockAuto::GetModelFromIDispatch(newValue);
		if (pSource) {
			SetSourceBlock(pSource);
		}
	}
	// NULL is passed
	else {
		SetSourceBlock(NULL);
	}

}

LPDISPATCH CProMoEdgeAuto::GetDestination() 
/* ============================================================
	Function :		CProMoEdgeAuto::GetDestination
	Description :	Returns the destination block of this edge.
	Access :		Public
	Return :		LPDISPATCH	-	a pointer to the IDispatch 
									interface of the destination 
									block of this edge. "NULL" if 
									no destination block is 
									connected to this edge.
	Parameters :	none
   ============================================================*/
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
/* ============================================================
	Function :		CProMoEdgeAuto::SetDestination
	Description :	Sets the destination block of this edge to the 
					block corresponding to the given IDispatch 
					interface pointer.
	Access :		Public
	Return :		void
	Parameters :	LPDISPATCH newValue	-	the IDispatch interface 
											pointer corresponding to 
											the block to be set as 
											destination block of this 
											edge. If "NULL" is passed, 
											the destination block of 
											this edge is set to "NULL".
   ============================================================*/
{
	// something is passed
	if (newValue) {
		// decode newValue
		CProMoBlockModel* pDest = CProMoBlockAuto::GetModelFromIDispatch(newValue);
		if (pDest) {
			SetDestinationBlock(pDest);
		}
	}
	// NULL is passed
	else {
		SetDestinationBlock(NULL);
	}

}

LPDISPATCH CProMoEdgeAuto::GetSegments() 
/* ============================================================
	Function :		CProMoEdgeAuto::GetSegments
	Description :	Returns a pointer to the automation object that 
					represents the collection of segments composing
					this edge.
	Access :		Public
	Return :		LPDISPATCH	-	a pointer to the automation object 
									that represents the collection of 
									segments composing this edge.
	Parameters :	none
   ============================================================*/
{
	if (GetSegmentsAutoObject())
	{
		return GetSegmentsAutoObject()->GetIDispatch(TRUE);
	}

	return NULL;
}

void CProMoEdgeAuto::SetSegments(LPDISPATCH newValue) 
/* ============================================================
	Function :		CProMoEdgeAuto::SetSegments
	Description :	Sets the collection of segments composing this 
					edge to the collection represented by the given 
					automation object.
					This property is read-only, so this function
					simply raises an exception. To modify the 
					segments composing this edge, the "Segments" collection 
					of this edge should be used.
	Access :		Public
	
	Return :		void
	Parameters :	newValue	-	a pointer to the automation object that 
									represents the new collection of 
									segments composing this edge.

   ============================================================*/
{
	SetNotSupported();

}
