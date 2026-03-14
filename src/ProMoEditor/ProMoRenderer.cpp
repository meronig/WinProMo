/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CProMoRenderer

	Author :		Giovanni Meroni

	Purpose :		"CProMoRenderer" is the base class responsible for rendering
					diagrams stored in "CProMoEntityContainer" instances.

	Description :	"CProMoRenderer" defines how to render diagrams as metafiles
					(vectorial) or raster images. The class uses a 
					"CProMoEntityContainer" instance as data source.

   ========================================================================*/
#include "stdafx.h"
#include "ProMoRenderer.h"
#include "ProMoEdgeView.h"
#include "ProMoEdgeModel.h"

CProMoRenderer::CProMoRenderer()
/* ============================================================
	Function :		CProMoRenderer::CProMoRenderer
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

	============================================================*/
{
	m_container = NULL;

	m_screenRes = 0;
}

CProMoRenderer::~CProMoRenderer()
/* ============================================================
	Function :		CProMoRenderer::~CProMoRenderer
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :

   ============================================================*/
{

}

void CProMoRenderer::SetEntityContainer(CProMoEntityContainer* container)
/* ============================================================
	Function :		CProMoRenderer::SetEntityContainer
	Description :	Sets the entity container to use as data
					source.
	Access :		Public

	Return :		void
	Parameters :	CProMoEntityContainer* container	-	Container
															to use

   ============================================================*/
{
	m_container = container;
}

void CProMoRenderer::SetScreenResolution(unsigned int res)
/* ============================================================
	Function :		CProMoRenderer::SetScreenResolution
	Description :	Sets the screen resolution to compute the
					overall diagram resolution.
	Access :		Public

	Return :		void
	Parameters :	unsigned int res	-	screen resolution
											expressed in DPI

   ============================================================*/
{
	m_screenRes = res;
}

void CProMoRenderer::RenderCanvasAsMetafile(CDC& dc, double zoom)
/* ============================================================
	Function :		CProMoRenderer::RenderCanvasAsMetafile
	Description :	Renders the entire canvas as a metafile.
	Access :		Public

	Return :		void
	Parameters :	CDC& dc				-	DC to render to
					double zoom			-	Zoom factor

   ============================================================*/
{
	if (m_container) {
		CSize docSize = m_container->GetVirtualSize();

		CObArray objects;
		PickAllElements(objects);

		RenderAsMetafile(objects, dc, zoom, CPoint(0,0), docSize);
	}
}

void CProMoRenderer::RenderCanvasAsRaster(CDibHelper& dib, unsigned int resolution)
/* ============================================================
	Function :		CProMoRenderer::RenderCanvasAsRaster
	Description :	Renders the entire canvas as a raster image.
	Access :		Public

	Return :		void
	Parameters :	CDibHelper& dib			-	DIB to render to
					unsigned int resolution	-	Image resolution
												expressed in DPI

   ============================================================*/
{
	if (m_container) {
		CSize docSize = m_container->GetVirtualSize();

		CObArray objects;
		PickAllElements(objects);

		RenderAsRaster(objects, dib, resolution, CPoint(0, 0), docSize);
	}
}

void CProMoRenderer::RenderDiagramAsMetafile(CDC& dc, double zoom)
/* ============================================================
	Function :		CProMoRenderer::RenderDiagramAsMetafile
	Description :	Renders the diagram as a metafile. The
					diagram size is computed as the bounding
					box of all elements in the container.
	Access :		Public

	Return :		void
	Parameters :	CDC& dc				-	DC to render to
					double zoom			-	Zoom factor

   ============================================================*/
{
	if (m_container)
	{
		CSize diagramSize = m_container->GetTotalSize();
		CPoint startPoint = m_container->GetStartPoint();

		CObArray objects;
		PickAllElements(objects);

		RenderAsMetafile(objects, dc, zoom, startPoint, diagramSize);
	}
}

void CProMoRenderer::RenderDiagramAsRaster(CDibHelper& dib, unsigned int resolution)
/* ============================================================
	Function :		CProMoRenderer::RenderDiagramAsRaster
	Description :	Renders the diagram as a raster image. The
					diagram size is computed as the bounding
					box of all elements in the container.
	Access :		Public

	Return :		void
	Parameters :	CDibHelper& dib			-	DIB to render to
					unsigned int resolution	-	Image resolution
												expressed in DPI

   ============================================================*/
{
	if (m_container) {
		CSize diagramSize = m_container->GetTotalSize();
		CPoint startPoint = m_container->GetStartPoint();
		
		CObArray objects;
		PickAllElements(objects);

		RenderAsRaster(objects, dib, resolution, startPoint, diagramSize);
	}
}

void CProMoRenderer::RenderSelectionAsMetafile(CDC& dc, double zoom)
/* ============================================================
	Function :		CProMoRenderer::RenderSelectionAsMetafile
	Description :	Renders the selected objects as a metafile.
					The diagram size is computed as the bounding
					box of all selected elements in the container.
	Access :		Public

	Return :		void
	Parameters :	CDC& dc				-	DC to render to
					double zoom			-	Zoom factor

   ============================================================*/
{
	if (m_container)
	{
		CSize diagramSize = m_container->GetSelectionTotalSize();
		CPoint startPoint = m_container->GetSelectionStartPoint();

		CObArray objects;
		PickSelectedElements(objects);
		
		RenderAsMetafile(objects, dc, zoom, startPoint, diagramSize);
	}
}

void CProMoRenderer::RenderSelectionAsRaster(CDibHelper& dib, unsigned int resolution)
/* ============================================================
	Function :		CProMoRenderer::RenderSelectionAsRaster
	Description :	Renders the selected objects as a raster 
					image. The diagram size is computed as the
					bounding box of all elements in the container.
	Access :		Public

	Return :		void
	Parameters :	CDibHelper& dib			-	DIB to render to
					unsigned int resolution	-	Image resolution
												expressed in DPI

   ============================================================*/
{
	if (m_container) {
		CSize diagramSize = m_container->GetSelectionTotalSize();
		CPoint startPoint = m_container->GetSelectionStartPoint();

		CObArray objects;
		PickSelectedElements(objects);

		RenderAsRaster(objects, dib, resolution, startPoint, diagramSize);
	}
}

void CProMoRenderer::RenderAsRaster(const CObArray& elements, CDibHelper& dib, unsigned int resolution, CPoint start, CSize size)
/* ============================================================
	Function :		CProMoRenderer::RenderAsRaster
	Description :	Renders the input objects as a raster image. 
	Access :		Protected

	Return :		void
	Parameters :	CObArray& elements		-	Objects to render
					CDibHelper& dib			-	DIB to render to
					unsigned int resolution	-	Image resolution
												expressed in DPI
					CPoint start			-	Top-left point of 
												the area to render
					CSize size				-	Size of the area

   ============================================================*/
{
	if (m_screenRes != 0) {
		CDC memDC;
		memDC.CreateCompatibleDC(NULL);

		const double MAX_DIM = 6000.0;

		double scaling = (double)resolution / (double)m_screenRes;
		double hSize = size.cx;
		double vSize = size.cy;

		double maxScaleW = MAX_DIM / hSize;
		double maxScaleH = MAX_DIM / vSize;
		double maxScale = min(maxScaleW, maxScaleH);

		if (scaling > maxScale)
			scaling = maxScale;

		int scaledStartX = (int)(start.x * scaling);
		int scaledStartY = (int)(start.y * scaling);
		int scaledWidth = (int)(size.cx * scaling);
		int scaledHeight = (int)(size.cy * scaling);
		
		dib.Create(scaledWidth, scaledHeight, 24);

		HBITMAP hOld = (HBITMAP)memDC.SelectObject(dib.GetBitmap());

		memDC.SetMapMode(MM_TEXT);
		memDC.SetViewportOrg(
			-LONG(0),
			-LONG(0));

		memDC.FillSolidRect(0, 0, scaledWidth, scaledHeight, RGB(255, 255, 255));

		RenderAsMetafile(elements, memDC, scaling, start, size);

		BITMAPINFOHEADER bih = *dib.GetBitmapInfoHeader();
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(bmi));
		bmi.bmiHeader = bih;

		memDC.SelectObject(hOld);
	}
}

void CProMoRenderer::RenderAsMetafile(const CObArray& elements, CDC& dc, double zoom, CPoint start, CSize size)
/* ============================================================
	Function :		CProMoRenderer::RenderAsRaster
	Description :	Renders the input objects as a metafile.
	Access :		Protected

	Return :		void
	Parameters :	CObArray& elements		-	Objects to render
					CDC& dc					-	DC to render to
					double zoom				-	Zoom factor
					CPoint start			-	Top-left point of
												the area to render
					CSize size				-	Size of the area

   ============================================================*/
{
	//only needed for vector
	start.x = (int)(start.x * zoom);
	start.y = (int)(start.y * zoom);

	size.cx = (int)(size.cx * zoom);
	size.cy = (int)(size.cy * zoom);
	
	dc.SetWindowOrg(start);
	dc.SetWindowExt(size); 
	
	CObArray oldSelection;

	CopySelection(oldSelection);

	m_container->UnselectAll();

	for (int i = 0; i < elements.GetSize(); i++) {
		CDiagramEntity* obj = dynamic_cast<CDiagramEntity*>(elements.GetAt(i));
		if (obj) {
			obj->DrawObject(&dc, zoom);
		}
	}
	
	SelectElements(oldSelection);
}

void CProMoRenderer::PickSelectedElements(CObArray& elements)
/* ============================================================
	Function :		CProMoRenderer::PickSelectedElements
	Description :	Adds all selected elements in the
					container to "elements".
	Access :		Protected

	Return :		void
	Parameters :	CObArray& elements		-	List of selected
												elements

   ============================================================*/
{
	if (m_container)
	{
		int count = 0;
		CDiagramEntity* obj;
		while ((obj = m_container->GetAt(count++))) {
			if (obj->IsSelected()) {
				PickElement(elements, obj);
			}
		}
	}
}

void CProMoRenderer::PickElement(CObArray& elements, CObject* element)
/* ============================================================
	Function :		CProMoRenderer::PickElement
	Description :	Adds the input element to "elements".
					If the element is a block or an edge,
					all attached labels and sub-elements
					are also added.
	Access :		Protected

	Return :		void
	Parameters :	CObArray& elements		-	List of selected
												elements
					CObject* element		-	Element to add

   ============================================================*/
{

	if (!IsPicked(elements, element)) {
		elements.Add(element);
	}

	CObArray labels;

	CProMoBlockView* block = dynamic_cast<CProMoBlockView*>(element);
	if (block) {
		int i = 0;

		// add all attached labels
		block->GetBlockModel()->GetLabels(labels);

		for (i = 0; i < labels.GetSize(); i++) {
			PickElement(elements, labels.GetAt(i));
		}

		// add all sub-blocks
		CObArray subBlocks;
		block->GetBlockModel()->GetSubBlocks(subBlocks);
		for (i = 0; i < subBlocks.GetSize(); i++) {
			CProMoBlockModel* subBlock = dynamic_cast<CProMoBlockModel*>(subBlocks.GetAt(i));
			PickElement(elements, subBlock->GetMainBlockView());
		}

		// add all boundary blocks
		CObArray boundaryBlocks;
		block->GetBlockModel()->GetBoundaryBlocks(boundaryBlocks, DEHT_BODY);
		for (i = 0; i < boundaryBlocks.GetSize(); i++) {
			CProMoBlockModel* boundaryBlock = dynamic_cast<CProMoBlockModel*>(boundaryBlocks.GetAt(i));
			PickElement(elements, boundaryBlock->GetMainBlockView());
		}
	}

	CProMoEdgeView* edge = dynamic_cast<CProMoEdgeView*>(element);
	if (edge) {
		int i = 0;

		// add all attached labels
		edge->GetEdgeModel()->GetLabels(labels);

		for (i = 0; i < labels.GetSize(); i++) {
			PickElement(elements, labels.GetAt(i));
		}
	}

}

void CProMoRenderer::PickAllElements(CObArray& elements)
/* ============================================================
	Function :		CProMoRenderer::PickAllElements
	Description :	Adds all elements in the container to 
					"elements".
	Access :		Protected

	Return :		void
	Parameters :	CObArray& elements		-	List of selected
												elements

   ============================================================*/
{
	elements.Append(*(m_container->GetData()));
}

BOOL CProMoRenderer::IsPicked(CObArray& elements, CObject* element)
/* ============================================================
	Function :		CProMoRenderer::IsPicked
	Description :	Returns whether the input element is
					present in "elements".
	Access :		Protected

	Return :		BOOL					-	"TRUE" if present,
												"FALSE" otherwise	
	Parameters :	CObArray& elements		-	List of selected
												elements
					CObject* element		-	Element to check

   ============================================================*/
{
	for (int i = 0; i < elements.GetSize(); i++) {
		if (elements.GetAt(i) == element) {
			return TRUE;
		}
	}
	return FALSE;
}

void CProMoRenderer::SelectElements(CObArray& elements)
/* ============================================================
	Function :		CProMoRenderer::SelectElements
	Description :	Marks the elements in the input array as
					selected
	Access :		Protected

	Return :		void
	Parameters :	CObArray& elements		-	List of elements
												to be marked as
												selected

   ============================================================*/
{
	if (m_container)
	{
		for (int i = 0; i < elements.GetSize(); i++) {
			CDiagramEntity* obj = dynamic_cast<CDiagramEntity*>(elements.GetAt(i));
			if (obj) {
				m_container->Select(obj, TRUE);
			}
		}
	}
}

void CProMoRenderer::CopySelection(CObArray& elements)
/* ============================================================
	Function :		CProMoRenderer::CopySelection
	Description :	Copies all elements that are selected in 
					the input array
	Access :		Protected

	Return :		void
	Parameters :	CObArray& elements		-	List of elements
												that are selected

   ============================================================*/
{
	if (m_container)
	{
		int count = 0;
		CDiagramEntity* obj;
		while ((obj = m_container->GetAt(count++))) {
			if (obj->IsSelected()) {
				elements.Add(obj);
			}
		}
	}
}
