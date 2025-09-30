/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#include "../DiagramEditor/DiagramEntityContainer.h"
#ifndef _FILESERIALIZER_H_
#define _FILESERIALIZER_H_

class AFX_EXT_CLASS CFileSerializer
{
public:
	static void Save(CArchive& ar, const CStringArray& data);
	static void Load(CArchive& ar, CStringArray& data);
};

#endif //_FILESERIALIZER_H_
