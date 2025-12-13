/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	Author :		Giovanni Meroni

   ========================================================================*/
#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include "../DiagramEditor/Tokenizer.h"

class AFX_EXT_CLASS CFileParser
{
public:
	static void GetHeaderFromString(const CString& str, CString& header);
	static void GetDataFromString(const CString& str, CString& data);
	static void EncodeString(CString& str);
	static void DecodeString(CString& str);
	static CTokenizer* Tokenize(const CString& str);
	static void CStringReplace(CString& str, const CString& from, const CString& to);

protected:
	
};

#endif //_FILEPARSER_H_
