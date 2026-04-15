/* ==========================================================================

    Copyright © 2025-26 Technical University of Denmark

    CProMoCmdHandler

    Author :		Giovanni Meroni

	Purpose :		CProMoCmdHandler implements the command handler for WinProMo
                    plugins. It is responsible for handling the commands of the 
                    plugin and updating the UI accordingly.

    Description :	This is an abstract class. To create a command handler, you need to
                    derive from this class and implement the pure virtual methods
					(OnPluginCommand, OnPluginUpdateCommandUI).
                    The constructor of the derived class should call the base 
					constructor with appropriate parameters to set the editor of 
                    the plugin.

   ========================================================================*/

#include "stdafx.h"
#include "ProMoCmdHandler.h"

CProMoCmdHandler::CProMoCmdHandler(CProMoEditor* editor)
/* =========================================================================
    Function :		CProMoCmdHandler::CProMoCmdHandler
    Description :	Constructor
    Access :		Public

    Return :    	void
    Parameters :	CProMoEditor* editor    -   Editor of the plugin
* ========================================================================*/

{
	ASSERT(editor);
	m_editor = editor;
}

CProMoCmdHandler::~CProMoCmdHandler()
/* =========================================================================
    Function :		CProMoCmdHandler::~CProMoCmdHandler
    Description :	Destructor
    Access :		Public

    Return :    	void
    Parameters :	none
* ========================================================================*/
{
	delete m_editor;
}

CProMoEditor* CProMoCmdHandler::GetEditor()
/* =========================================================================
    Function :		CProMoCmdHandler::GetEditor
    Description :	Returns a pointer to the editor of the plugin. The editor
                    is responsible for managing the diagram and its elements,
                    and provides methods to manipulate them.
    Access :		Public
    Return :    	CProMoEditor*  -   pointer to the editor
    Parameters :	none
* ========================================================================*/
{
	return m_editor;
}
