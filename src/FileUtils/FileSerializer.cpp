/* ==========================================================================

	Copyright © 2025 Technical University of Denmark

	CFileParser

	Author :		Giovanni Meroni

	Purpose :		"CFileSerializer" is a class to assist loading and saving
					text files using ANSI or UTF8 encoding, avoiding file
					incompatibilities when compiled under old versions of 
					Windows and/or MSVC.

   ========================================================================*/
#include "stdafx.h"
#include "FileSerializer.h"

void CFileSerializer::Save(CArchive& ar, const CStringArray& data)
/* ============================================================
	Function :		CFileSerializer::Save
	Description :	Saves the content of a "CStringArray" to
					a file using ANSI or UTF8 encoding, depending
					on the compilation settings.
	Access :		Public

	Return :		none
	Parameters :	CArchive& ar		-	Archive to save to.
					CStringArray& data	-	Data to save.

   ============================================================*/
{
#ifndef _UNICODE 

	for (int i = 0; i < data.GetSize(); i++) {
		CString line = data.GetAt(i) + "\r\n";
		ar.WriteString(line);
	}

#else
	CFile* pFile = ar.GetFile();

	for (int i = 0; i < data.GetSize(); i++) {
		CStringW wideLine = data.GetAt(i) + L"\r\n";

		// Convert UTF-16 to UTF-8
		int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideLine, -1, NULL, 0, NULL, NULL);
		char* utf8Line = new char[utf8Len];
		WideCharToMultiByte(CP_UTF8, 0, wideLine, -1, utf8Line, utf8Len, NULL, NULL);

		// Write excluding null terminator
		pFile->Write(utf8Line, utf8Len - 1);
		delete[] utf8Line;
	}
#endif
}

void CFileSerializer::Load(CArchive& ar, CStringArray& data)
/* ============================================================
	Function :		CFileSerializer::Load
	Description :	Loads the content of a text file into
					a "CStringArray", handling ANSI or UTF8
					encoding.
	Access :		Public

	Parameters :	CArchive& ar		-	Archive to load from.
					CStringArray& data	-	Data to load.

   ============================================================*/
{
	// Loading can handle ANSI or UTF8 encoding only
	CFile* pFile = ar.GetFile();

	DWORD size = (DWORD)pFile->GetLength();
	char* buffer = new char[size + 1];
	pFile->Read(buffer, size);
	buffer[size] = '\0';

	CString content(buffer);
	delete[] buffer;

	int pos = 0;
	while (pos >= 0)
	{
		CString rest = content.Mid(pos);
		int rel = rest.Find(_T("\r\n"));
		CString line;

		if (rel == -1)
		{
			line = rest;
			pos = -1;
		}
		else
		{
			line = rest.Left(rel);
			pos += rel + 2;
		}

		data.Add(line);
	}
}
