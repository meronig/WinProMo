# Microsoft Developer Studio Project File - Name="DiagramEditorDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DiagramEditorDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DiagramEditorDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DiagramEditorDemo.mak" CFG="DiagramEditorDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DiagramEditorDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DiagramEditorDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DiagramEditorDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DiagramEditorDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x41d /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DiagramEditorDemo - Win32 Release"
# Name "DiagramEditorDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DiagramEditor\DiagramClipboardHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramClipboardHandler.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditorDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditorDemo.rc
# End Source File
# Begin Source File

SOURCE=.\DiagramEditorDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEntityContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramLine.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramPropertyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GridSizeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\GroupFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\PaperSizeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\Tokenizer.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\UndoItem.cpp
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\UndoItem.h
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEditor.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditorDemo.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditorDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEntity.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEntityContainer.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramLine.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramMenu.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\DiagramPropertyDlg.h
# End Source File
# Begin Source File

SOURCE=.\GridSizeDialog.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\GroupFactory.h
# End Source File
# Begin Source File

SOURCE=.\PaperSizeDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TextFile.h
# End Source File
# Begin Source File

SOURCE=.\DiagramEditor\Tokenizer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DiagramEditorDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\DiagramEditorDemo.rc2
# End Source File
# End Group
# End Target
# End Project
