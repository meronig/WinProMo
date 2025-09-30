#include "stdafx.h"
#include "FileSerializer.h"

void CFileSerializer::Save(CArchive& ar, const CStringArray& data)
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
