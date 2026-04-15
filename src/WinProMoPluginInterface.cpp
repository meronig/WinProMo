/* ==========================================================================

    Copyright © 2025-26 Technical University of Denmark

    CWinProMoPluginInterface

    Author :		Giovanni Meroni

	Purpose :		CWinProMoPluginInterface implements the plugin interface 
                    for WinProMo. It provides information about the plugin, 
                    such as the document type, ID, description, control factory, 
                    entity container, and renderer. It also defines methods 
                    to get the list of elements and commands to be added to the 
                    Insert menu and the tool palette, and to get the command 
                    handler for the plugin.

    Description :	This is an abstract class. To create a plugin, you need to 
                    derive from this class and implement the pure virtual methods 
                    (GetElements, GetCommands, GetCmdHandler). 
                    You can also override the other virtual methods if you need to 
                    customize the behavior of the plugin. The constructor of the 
                    derived class should call the base constructor with appropriate 
                    parameters to set the document ID, type, description, and control 
					factory of the plugin.

   ========================================================================*/
#include "stdafx.h"
#include "WinProMoPluginInterface.h"
#include "resource.h"
#include "ProMoEditor/ProMoEditor.h"
#include "ProMoEditor/ProMoEntityContainer.h"

CWinProMoPluginInterface::CWinProMoPluginInterface(UINT documentID, const CString& documentType, const CString& documentDescr, CProMoControlFactory* controlFactory)
/* =========================================================================
    Function :		CWinProMoPluginInterface::CWinProMoPluginInterface
    Description :	Constructor
    Access :		Public
    Return :    	void
    Parameters :	UINT documentID                     -   Unique ID for 
                                                            the document
                                                            type of the 
                                                            plugin (e.g., 1234)
                    CString& documentType               -   Unique string 
                                                            for the document
                                                            type of the 
                                                            plugin (e.g., 
                                                            "demoPlugin")
					CString& documentDescr              -   Descriptive 
                                                            string for the 
                                                            document type 
                                                            of the plugin, 
                                                            shown in the 
                                                            "New" dialog
					CProMoControlFactory* controlFactory -  Control factory 
                                                            for the plugin
* ========================================================================*/
{
	ASSERT(controlFactory);
    
    m_documentID = documentID;
    m_documentType = documentType;
    m_documentDescr = documentDescr;
	m_controlFactory = controlFactory;
}

CWinProMoPluginInterface::~CWinProMoPluginInterface()
/* =========================================================================
    Function :		CWinProMoPluginInterface::~CWinProMoPluginInterface
    Description :	Destructor
    Access :		Public
    Return :    	void
    Parameters :	none
* ========================================================================*/
{
}

const CString& CWinProMoPluginInterface::GetDocumentType()
/* =========================================================================
    Function :		CWinProMoPluginInterface::GetDocumentType
    Description :	Returns the document type of the plugin.
    Access :		Public
    Return :    	CString&    -   document type
    Parameters :	none
* ========================================================================*/
{
    return m_documentType;
}

const UINT& CWinProMoPluginInterface::GetDocumentID()
/* =========================================================================
    Function :		CWinProMoPluginInterface::GetDocumentID
    Description :	Returns the document ID of the plugin.
    Access :		Public
    Return :    	UINT&   -   document ID
    Parameters :	none
* ========================================================================*/
{
    return m_documentID;
}

const CString& CWinProMoPluginInterface::GetDocumentDescr()
/* =========================================================================
    Function :		CWinProMoPluginInterface::GetDocumentDescr
    Description :	Returns a descriptive string for the document type of the
                    plugin. This description will be shown in the "New" dialog
                    when the user creates a new document, and can be used to
                    provide more information about the diagram being created.
    Access :		Public
    Return :    	CString&    -   document description
    Parameters :	none
* ========================================================================*/
{
    return m_documentDescr;
}

void CWinProMoPluginInterface::Destroy()
/* =========================================================================
    Function :		CWinProMoPluginInterface::Destroy
    Description :	Destroys the plugin interface and releases all resources.
    Access :		Public
    Return :    	void
    Parameters :	none
* ========================================================================*/
{
	delete m_controlFactory;
    delete this;
}

CProMoControlFactory* CWinProMoPluginInterface::GetControlFactory()
/* =========================================================================
    Function :		CWinProMoPluginInterface::GetControlFactory
    Description :	Returns a pointer to the control factory of the plugin. The
                    control factory is responsible for creating the controls of
                    the diagram (e.g., nodes, edges, labels, etc.) and their
                    properties.
    Access :		Public
    Return :    	CProMoControlFactory*  -   pointer to the control factory
	Parameters :	none
* ========================================================================*/
{
    return m_controlFactory;
}

CProMoEntityContainer* CWinProMoPluginInterface::GetContainer()
/* =========================================================================
    Function :		CWinProMoPluginInterface::GetContainer
    Description :	Returns a pointer to the entity container of the plugin. The
                    entity container is responsible for managing the entities of
                    the diagram (e.g., nodes, edges, labels, etc.) and their
                    properties.
    Access :		Public
    Return :    	CProMoEntityContainer*  -   pointer to the entity container
    Parameters :	none
* ========================================================================*/
{
    return new CProMoEntityContainer(m_controlFactory, m_documentType);
}

CProMoRenderer* CWinProMoPluginInterface::GetRenderer()
/* =========================================================================
    Function :		CWinProMoPluginInterface::GetRenderer
    Description :	Returns a pointer to the renderer of the plugin. The renderer
                    is responsible for rendering the diagram on the screen and
                    in printouts.
    Access :		Public
    Return :    	CProMoRenderer*    -   pointer to the renderer
    Parameters :	none
* ========================================================================*/
{
    return new CProMoRenderer;
}
