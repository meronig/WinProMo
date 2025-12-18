/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#include "ProMoEntityContainer.h"
#include "../FileUtils/DibHelper.h"
#ifndef _PROMORENDERER_H_
#define _PROMORENDERER_H_

class AFX_EXT_CLASS CProMoRenderer :
    public CObject
{
public:
	CProMoRenderer();
	virtual ~CProMoRenderer();

	virtual void SetEntityContainer(CProMoEntityContainer* container);
	virtual void SetScreenResolution(unsigned int res);
	
	virtual void RenderCanvasAsMetafile(CDC& dc, double zoom);
	virtual void RenderCanvasAsRaster(CDibHelper& dib, unsigned int resolution);
	
	virtual void RenderDiagramAsMetafile(CDC& dc, double zoom);
	virtual void RenderDiagramAsRaster(CDibHelper& dib, unsigned int resolution);
	
	virtual void RenderSelectionAsMetafile(CDC& dc, double zoom);
	virtual void RenderSelectionAsRaster(CDibHelper& dib, unsigned int resolution);


protected:
	CProMoEntityContainer* m_container;
	unsigned int m_screenRes;

	virtual void RenderAsRaster(const CObArray &elements, CDibHelper& dib, unsigned int resolution, CPoint start, CSize size);
	virtual void RenderAsMetafile(const CObArray &elements, CDC& dc, double zoom, CPoint start, CSize size);
	
	virtual void PickSelectedElements(CObArray &elements);
	virtual void PickElement(CObArray& elements, CObject* element);
	virtual void PickAllElements(CObArray& elements);
	virtual BOOL IsPicked(CObArray& elements, CObject* element);
	virtual void SelectElements(CObArray& elements);
	virtual void CopySelection(CObArray& elements);
};

#endif // _PROMORENDERER_H_