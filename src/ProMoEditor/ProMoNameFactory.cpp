/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CProMoNameFactory

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-04-29

	Purpose :		CProMoNameFactory is a simple class with one single static 
					function, returning and updating a single static int 
					value to use as a unique id for drawing objects.	

	Description :	See below

	Usage :			Call CProMoNameFactory::GetID to get a unique id during this 
					session.

   ========================================================================*/

#include "stdafx.h"
#include "ProMoNameFactory.h"

int CProMoNameFactory::s_currentID = 0;

CString CProMoNameFactory::GetID()
/* ============================================================
	Function :		CProMoNameFactory::GetID
	Description :	Returns a unique int every time it is 
					called.
					
	Return :		CString	-	CString with the unique id.
	Parameters :	none

	Usage :			Call to get a unique id. Used to get unique 
					ids for the object name attributes.

   ============================================================*/
{
	CString str;

	str.Format( _T( "%i" ), CProMoNameFactory::s_currentID );
	CProMoNameFactory::s_currentID++;

	return str;

}