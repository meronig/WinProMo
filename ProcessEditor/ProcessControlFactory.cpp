/* ==========================================================================
	CFlowchartControlFactory

	Author :		Giovanni Meroni

	Purpose :		CProcessControlFactory is a factory-class with one 
					single member, allowing the creation of CDiagramEntity-
					derived objects from a string.	

	Description :	CreateFromString tries to instantiate one of the control 
					objects by testing the control object static function 
					CreateFromString until it hits a valid one. The 
					resulting pointer is then returned and can be added to 
					the application data.

	Usage :			Call CProcessControlFactory::CreateFromString and if 
					a non-NULL pointer is returned, add it to the 
					editor data.

   ========================================================================*/
#include "../stdafx.h"
#include "ProcessControlFactory.h"

#include "ProcessEntityBlockView.h"
#include "ProcessLineEdgeView.h"
#include "ProcessLineEdgeModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProcessControlFactory

CDiagramEntity* CProcessControlFactory::CreateViewFromString( const CString& str )
/* ============================================================
	Function :		CProcessControlFactory::CreateFromString
	Description :	The function returns an object from the 
					parameter str.
					
	Return :		CDiagramEntity*		-	The new object, or 
											NULL is str is not a 
											valid representation.
	Parameters :	const CString& str	-	The string to create 
											a new object from
					
	Usage :			Call this static function while reading 
					string representations of objects from a 
					text file. Note that the caller is 
					responsible for the allocated memory.

   ============================================================*/
{
	CDiagramEntity* obj;

	obj = CProcessEntityBlockView::CreateFromString( str );
	
	if( !obj )
		obj = CProcessLineEdgeView::CreateFromString( str );
	
	
	return obj;
}

CProcessModel* CProcessControlFactory::CreateModelFromString(const CString& str)
{
	CProcessModel* obj;

	obj = CProcessEntityBlockModel::CreateFromString(str);

	if (!obj)
		obj = CProcessLineEdgeModel::CreateFromString(str);


	return obj;
}
