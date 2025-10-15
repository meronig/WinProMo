/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CProMoControlFactory

	Author :		Giovanni Meroni

	Purpose :		CProMoControlFactory is a factory-class with members 
					allowing the creation of CDiagramEntity and CProMoModel
					-derived objects from a string.	

	Description :	CreateFromString tries to instantiate one of the control 
					objects by testing the control object static function 
					CreateFromString until it hits a valid one. The 
					resulting pointer is then returned and can be added to 
					the application data.

	Usage :			Call CProMoControlFactory::CreateViewFromString and if 
					a non-NULL pointer is returned, add it to the 
					editor data.

   ========================================================================*/

#include "stdafx.h"
#include "ProMoControlFactory.h"

#include "ProMoBlockView.h"
#include "ProMoEdgeView.h"
#include "ProMoEdgeModel.h"
#include "ProMoLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProMoControlFactory

CDiagramEntity* CProMoControlFactory::CreateViewFromString(const CString& str)
/* ============================================================
	Function :		CProMoControlFactory::CreateViewFromString
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

	obj = CProMoBlockView::CreateFromString(str);

	if (!obj)
		obj = CProMoEdgeView::CreateFromString(str);

	return obj;
}

CDiagramEntity* CProMoControlFactory::CreateViewFromString(const CString& str, CProMoModel* model)
/* ============================================================
	Function :		CProMoControlFactory::CreateViewFromString
	Description :	The function returns an object from the
					parameter str.

	Return :		CDiagramEntity*		-	The new object, or
											NULL is str is not a
											valid representation.
	Parameters :	const CString& str	-	The string to create
											a new object from
					CProMoModel* model	-	The model that will
											be linked to the
											created object

	Usage :			Call this static function while reading
					string representations of objects from a
					text file. Note that the caller is
					responsible for the allocated memory of
					the created object only. The created object
					will take ownership of the model being
					passed, which should be created on the heap.

   ============================================================*/
{
	CDiagramEntity* obj;

	obj = CProMoBlockView::CreateFromString(str, model);

	if (!obj)
		obj = CProMoEdgeView::CreateFromString(str, model);

	return obj;
}

CDiagramEntity* CProMoControlFactory::CreateLabelFromString(const CString& str)
/* ============================================================
	Function :		CProMoControlFactory::CreateLabelFromString
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

	obj = CProMoLabel::CreateFromString(str);

	return obj;
}

CDiagramEntity* CProMoControlFactory::CreateLabelFromString(const CString& str, CProMoModel* model)
/* ============================================================
	Function :		CProMoControlFactory::CreateLabelFromString
	Description :	The function returns an object from the
					parameter str.

	Return :		CDiagramEntity*		-	The new object, or
											NULL is str is not a
											valid representation.
	Parameters :	const CString& str	-	The string to create
											a new object from
					CProMoModel* model	-	The model that will
											be linked to the
											created object

	Usage :			Call this static function while reading
					string representations of objects from a
					text file. Note that the caller is
					responsible for the allocated memory of
					the created object only. The created object
					will take ownership of the model being
					passed, which should be created on the heap.

   ============================================================*/
{
	CDiagramEntity* obj;

	obj = CProMoLabel::CreateFromString(str, model);

	return obj;
}

CProMoModel* CProMoControlFactory::CreateModelFromString(const CString& str)
/* ============================================================
	Function :		CProMoControlFactory::CreateModelFromString
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
	CProMoModel* obj;

	obj = CProMoBlockModel::CreateFromString(str);

	if (!obj)
		obj = CProMoEdgeModel::CreateFromString(str);


	return obj;
}
