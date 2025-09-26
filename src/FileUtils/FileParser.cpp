/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CFileParser

	Author :		Giovanni Meroni

	Purpose :		"CFileParser" is a class to assist parsing WinProMo text 
					files.

   ========================================================================*/
#include "stdafx.h"
#include "FileParser.h"

void CFileParser::GetHeaderFromString(const CString& str, CString& header)
/* ============================================================
	Function :		CFileParser::GetHeaderFromString
	Description :	Gets the header from "str".
	Access :		Protected

	Return :		none	
	Parameters :	CString& str	-	"CString" to get type from.
					CString& header	-	The type of "str".

   ============================================================*/
{
	CTokenizer main(str, _T(":"));
	if (main.GetSize() >= 1)
	{
		main.GetAt(0, header);
		header.TrimLeft();
		header.TrimRight();
	}
}

void CFileParser::GetDataFromString(const CString& str, CString& data)
/* ============================================================
	Function :		CFileParser::GetDataFromString
	Description :	Gets the default properties from "str"
	Access :		Protected

	Return :		none
	Parameters :	CString& str	-	"CString" to get the
										default properties from.
					CString& data	-	The default properties 
										of "str".

   ============================================================*/
{
	CTokenizer main(str, _T(":"));
	if (main.GetSize() >= 2)
	{
		main.GetAt(1, data);
		data.TrimLeft();
		data.TrimRight();

	}
}

void CFileParser::EncodeString(CString& str)
/* ============================================================
	Function :		CFileParser::EncodeString
	Description :	Encodes the input string by replacing 
					special characters with tags
	Access :		Public

	Return :		none
	Parameters :	CString& str	-	"CString" to encode.

   ============================================================*/
{
	CStringReplace(str, _T(":"), _T("\\colon"));
	CStringReplace(str, _T(";"), _T("\\semicolon"));
	CStringReplace(str, _T(","), _T("\\comma"));
	CStringReplace(str, _T("\r\n"), _T("\\newline"));

}

void CFileParser::DecodeString(CString& str)
/* ============================================================
	Function :		CFileParser::DecodeString
	Description :	Decodes the input string by replacing
					tags with special characters
	Access :		Public

	Return :		none
	Parameters :	CString& str	-	"CString" to decode.

   ============================================================*/
{
	CStringReplace(str, _T("\\colon"), _T(":"));
	CStringReplace(str, _T("\\semicolon"), _T(";"));
	CStringReplace(str, _T("\\comma"), _T(","));
	CStringReplace(str, _T("\\newline"), _T("\r\n"));

}

CTokenizer* CFileParser::Tokenize(const CString& str) 
/* ============================================================
	Function :		CFileParser::Tokenize
	Description :	Tokenizes the default properties from "str"
	Access :		Protected

	Return :		CTokenizer*		-	Pointer to a CTokenizer
										object containing the
										default properties
	Parameters :	CString& str	-	"CString" to get the
										default properties from.

   ============================================================*/
{
	CString data;
	CFileParser::GetDataFromString(str, data);
	
	if (data.GetLength() > 0) {

		if (data[data.GetLength() - 1] == _TCHAR(';'))
			data = data.Left(data.GetLength() - 1); // Strip the ';'

		CTokenizer* tok = new CTokenizer(data);
		return tok;
	}
	return NULL;

}

void CFileParser::CStringReplace(CString& str, const CString& from, const CString& to) 
/* ============================================================
	Function :		CFileParser::CStringReplace
	Description :	Replaces every occurrence of "from" with 
					"to" in "str"
	Access :		Protected

	Return :		none
	Parameters :	CString& str	-	"CString" to perform
										the operation.
					CString& from	-	"CString" containing the
										string to find.
					CString& to		-	"CString" containing the
										string to replace.

   ============================================================*/
{
	int pos = 0;
	int fromLen = from.GetLength();
	int toLen = to.GetLength();

	if (from.IsEmpty())
		return;

	while ((pos = str.Find(from)) != -1)
	{
		str = str.Left(pos) + to + str.Mid(pos + fromLen);
	}
}