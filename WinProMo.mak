# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=WinProMo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to WinProMo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WinProMo - Win32 Release" && "$(CFG)" !=\
 "WinProMo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinProMo.mak" CFG="WinProMo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinProMo - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WinProMo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "WinProMo - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "WinProMo - Win32 Release"

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
OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\Release\WinProMo.dll"

CLEAN : 
	-@erase "$(INTDIR)\CustomPropertyItem.obj"
	-@erase "$(INTDIR)\DiagramClipboardHandler.obj"
	-@erase "$(INTDIR)\DiagramEditor.obj"
	-@erase "$(INTDIR)\DiagramEntity.obj"
	-@erase "$(INTDIR)\DiagramEntityContainer.obj"
	-@erase "$(INTDIR)\DiagramLine.obj"
	-@erase "$(INTDIR)\DiagramMenu.obj"
	-@erase "$(INTDIR)\DiagramPropertyDlg.obj"
	-@erase "$(INTDIR)\GroupFactory.obj"
	-@erase "$(INTDIR)\ProMoBlockModel.obj"
	-@erase "$(INTDIR)\ProMoBlockView.obj"
	-@erase "$(INTDIR)\ProMoClipboardHandler.obj"
	-@erase "$(INTDIR)\ProMoControlFactory.obj"
	-@erase "$(INTDIR)\ProMoEdgeModel.obj"
	-@erase "$(INTDIR)\ProMoEdgeView.obj"
	-@erase "$(INTDIR)\ProMoEditor.obj"
	-@erase "$(INTDIR)\ProMoEntityContainer.obj"
	-@erase "$(INTDIR)\ProMoModel.obj"
	-@erase "$(INTDIR)\ProMoNameFactory.obj"
	-@erase "$(INTDIR)\PropertyDialog.obj"
	-@erase "$(INTDIR)\PropertyItem.obj"
	-@erase "$(INTDIR)\PropertyWrappers.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tokenizer.obj"
	-@erase "$(INTDIR)\UndoItem.obj"
	-@erase "$(INTDIR)\WinProMo.obj"
	-@erase "$(INTDIR)\WinProMo.pch"
	-@erase "$(INTDIR)\WinProMo.res"
	-@erase "$(INTDIR)\WinProMoDoc.obj"
	-@erase "$(INTDIR)\WinProMoDocTemplate.obj"
	-@erase "$(INTDIR)\WinProMoView.obj"
	-@erase "$(OUTDIR)\WinProMo.exp"
	-@erase "$(OUTDIR)\WinProMo.lib"
	-@erase "..\Release\WinProMo.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D WINPROMO_EXPORTS=1 /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D WINPROMO_EXPORTS=1\
 /Fp"$(INTDIR)/WinProMo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WinProMo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WinProMo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /base:0x10000000 /subsystem:windows /dll /machine:I386 /out:"../Release/WinProMo.dll"
LINK32_FLAGS=/nologo /base:0x10000000 /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/WinProMo.pdb" /machine:I386 /def:".\WinProMo.def"\
 /out:"../Release/WinProMo.dll" /implib:"$(OUTDIR)/WinProMo.lib" 
DEF_FILE= \
	".\WinProMo.def"
LINK32_OBJS= \
	"$(INTDIR)\CustomPropertyItem.obj" \
	"$(INTDIR)\DiagramClipboardHandler.obj" \
	"$(INTDIR)\DiagramEditor.obj" \
	"$(INTDIR)\DiagramEntity.obj" \
	"$(INTDIR)\DiagramEntityContainer.obj" \
	"$(INTDIR)\DiagramLine.obj" \
	"$(INTDIR)\DiagramMenu.obj" \
	"$(INTDIR)\DiagramPropertyDlg.obj" \
	"$(INTDIR)\GroupFactory.obj" \
	"$(INTDIR)\ProMoBlockModel.obj" \
	"$(INTDIR)\ProMoBlockView.obj" \
	"$(INTDIR)\ProMoClipboardHandler.obj" \
	"$(INTDIR)\ProMoControlFactory.obj" \
	"$(INTDIR)\ProMoEdgeModel.obj" \
	"$(INTDIR)\ProMoEdgeView.obj" \
	"$(INTDIR)\ProMoEditor.obj" \
	"$(INTDIR)\ProMoEntityContainer.obj" \
	"$(INTDIR)\ProMoModel.obj" \
	"$(INTDIR)\ProMoNameFactory.obj" \
	"$(INTDIR)\PropertyDialog.obj" \
	"$(INTDIR)\PropertyItem.obj" \
	"$(INTDIR)\PropertyWrappers.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tokenizer.obj" \
	"$(INTDIR)\UndoItem.obj" \
	"$(INTDIR)\WinProMo.obj" \
	"$(INTDIR)\WinProMo.res" \
	"$(INTDIR)\WinProMoDoc.obj" \
	"$(INTDIR)\WinProMoDocTemplate.obj" \
	"$(INTDIR)\WinProMoView.obj"

"..\Release\WinProMo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

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
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\Debug\WinProMo.dll"

CLEAN : 
	-@erase "$(INTDIR)\CustomPropertyItem.obj"
	-@erase "$(INTDIR)\DiagramClipboardHandler.obj"
	-@erase "$(INTDIR)\DiagramEditor.obj"
	-@erase "$(INTDIR)\DiagramEntity.obj"
	-@erase "$(INTDIR)\DiagramEntityContainer.obj"
	-@erase "$(INTDIR)\DiagramLine.obj"
	-@erase "$(INTDIR)\DiagramMenu.obj"
	-@erase "$(INTDIR)\DiagramPropertyDlg.obj"
	-@erase "$(INTDIR)\GroupFactory.obj"
	-@erase "$(INTDIR)\ProMoBlockModel.obj"
	-@erase "$(INTDIR)\ProMoBlockView.obj"
	-@erase "$(INTDIR)\ProMoClipboardHandler.obj"
	-@erase "$(INTDIR)\ProMoControlFactory.obj"
	-@erase "$(INTDIR)\ProMoEdgeModel.obj"
	-@erase "$(INTDIR)\ProMoEdgeView.obj"
	-@erase "$(INTDIR)\ProMoEditor.obj"
	-@erase "$(INTDIR)\ProMoEntityContainer.obj"
	-@erase "$(INTDIR)\ProMoModel.obj"
	-@erase "$(INTDIR)\ProMoNameFactory.obj"
	-@erase "$(INTDIR)\PropertyDialog.obj"
	-@erase "$(INTDIR)\PropertyItem.obj"
	-@erase "$(INTDIR)\PropertyWrappers.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tokenizer.obj"
	-@erase "$(INTDIR)\UndoItem.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WinProMo.obj"
	-@erase "$(INTDIR)\WinProMo.pch"
	-@erase "$(INTDIR)\WinProMo.res"
	-@erase "$(INTDIR)\WinProMoDoc.obj"
	-@erase "$(INTDIR)\WinProMoDocTemplate.obj"
	-@erase "$(INTDIR)\WinProMoView.obj"
	-@erase "$(OUTDIR)\WinProMo.exp"
	-@erase "$(OUTDIR)\WinProMo.lib"
	-@erase "$(OUTDIR)\WinProMo.pdb"
	-@erase "..\Debug\WinProMo.dll"
	-@erase "..\Debug\WinProMo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D WINPROMO_EXPORTS=1 /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D\
 WINPROMO_EXPORTS=1 /Fp"$(INTDIR)/WinProMo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/WinProMo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WinProMo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /base:0x10000000 /subsystem:windows /dll /debug /machine:I386 /out:"../Debug/WinProMo.dll"
LINK32_FLAGS=/nologo /base:0x10000000 /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/WinProMo.pdb" /debug /machine:I386 /def:".\WinProMo.def"\
 /out:"../Debug/WinProMo.dll" /implib:"$(OUTDIR)/WinProMo.lib" 
DEF_FILE= \
	".\WinProMo.def"
LINK32_OBJS= \
	"$(INTDIR)\CustomPropertyItem.obj" \
	"$(INTDIR)\DiagramClipboardHandler.obj" \
	"$(INTDIR)\DiagramEditor.obj" \
	"$(INTDIR)\DiagramEntity.obj" \
	"$(INTDIR)\DiagramEntityContainer.obj" \
	"$(INTDIR)\DiagramLine.obj" \
	"$(INTDIR)\DiagramMenu.obj" \
	"$(INTDIR)\DiagramPropertyDlg.obj" \
	"$(INTDIR)\GroupFactory.obj" \
	"$(INTDIR)\ProMoBlockModel.obj" \
	"$(INTDIR)\ProMoBlockView.obj" \
	"$(INTDIR)\ProMoClipboardHandler.obj" \
	"$(INTDIR)\ProMoControlFactory.obj" \
	"$(INTDIR)\ProMoEdgeModel.obj" \
	"$(INTDIR)\ProMoEdgeView.obj" \
	"$(INTDIR)\ProMoEditor.obj" \
	"$(INTDIR)\ProMoEntityContainer.obj" \
	"$(INTDIR)\ProMoModel.obj" \
	"$(INTDIR)\ProMoNameFactory.obj" \
	"$(INTDIR)\PropertyDialog.obj" \
	"$(INTDIR)\PropertyItem.obj" \
	"$(INTDIR)\PropertyWrappers.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tokenizer.obj" \
	"$(INTDIR)\UndoItem.obj" \
	"$(INTDIR)\WinProMo.obj" \
	"$(INTDIR)\WinProMo.res" \
	"$(INTDIR)\WinProMoDoc.obj" \
	"$(INTDIR)\WinProMoDocTemplate.obj" \
	"$(INTDIR)\WinProMoView.obj"

"..\Debug\WinProMo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "WinProMo - Win32 Release"
# Name "WinProMo - Win32 Debug"

!IF  "$(CFG)" == "WinProMo - Win32 Release"

!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "WinProMo - Win32 Release"

!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMo.cpp
DEP_CPP_WINPR=\
	".\StdAfx.h"\
	

"$(INTDIR)\WinProMo.obj" : $(SOURCE) $(DEP_CPP_WINPR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMo.def

!IF  "$(CFG)" == "WinProMo - Win32 Release"

!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D WINPROMO_EXPORTS=1\
 /Fp"$(INTDIR)/WinProMo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WinProMo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D\
 WINPROMO_EXPORTS=1 /Fp"$(INTDIR)/WinProMo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WinProMo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMo.rc
DEP_RSC_WINPRO=\
	".\res\DiagramEditorDemo.ico"\
	".\res\DiagramEditorDemo.rc2"\
	

"$(INTDIR)\WinProMo.res" : $(SOURCE) $(DEP_RSC_WINPRO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\UndoItem.cpp
DEP_CPP_UNDOI=\
	".\DiagramEditor\UndoItem.h"\
	
NODEP_CPP_UNDOI=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\UndoItem.obj" : $(SOURCE) $(DEP_CPP_UNDOI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEditor.cpp
DEP_CPP_DIAGR=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGR=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramEditor.obj" : $(SOURCE) $(DEP_CPP_DIAGR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEntity.cpp
DEP_CPP_DIAGRA=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRA=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramEntity.obj" : $(SOURCE) $(DEP_CPP_DIAGRA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramEntityContainer.cpp
DEP_CPP_DIAGRAM=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\GroupFactory.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRAM=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramEntityContainer.obj" : $(SOURCE) $(DEP_CPP_DIAGRAM)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramLine.cpp
DEP_CPP_DIAGRAML=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRAML=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramLine.obj" : $(SOURCE) $(DEP_CPP_DIAGRAML) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramMenu.cpp
DEP_CPP_DIAGRAMM=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRAMM=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramMenu.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramPropertyDlg.cpp
DEP_CPP_DIAGRAMP=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRAMP=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramPropertyDlg.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\GroupFactory.cpp
DEP_CPP_GROUP=\
	".\DiagramEditor\GroupFactory.h"\
	
NODEP_CPP_GROUP=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\GroupFactory.obj" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\Tokenizer.cpp
DEP_CPP_TOKEN=\
	".\DiagramEditor\Tokenizer.h"\
	
NODEP_CPP_TOKEN=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\Tokenizer.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramClipboardHandler.cpp
DEP_CPP_DIAGRAMC=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\GroupFactory.h"\
	".\DiagramEditor\UndoItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRAMC=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMC)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\PropertyDialog.cpp
DEP_CPP_PROPE=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEditor.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROPE=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\PropertyDialog.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoBlockView.cpp
DEP_CPP_PROMO=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMO=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoBlockView.obj" : $(SOURCE) $(DEP_CPP_PROMO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoClipboardHandler.cpp
DEP_CPP_PROMOC=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\GroupFactory.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoClipboardHandler.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOC=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_PROMOC) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoControlFactory.cpp
DEP_CPP_PROMOCO=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOCO=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoControlFactory.obj" : $(SOURCE) $(DEP_CPP_PROMOCO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoEdgeModel.cpp
DEP_CPP_PROMOE=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOE=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeModel.obj" : $(SOURCE) $(DEP_CPP_PROMOE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoEdgeView.cpp
DEP_CPP_PROMOED=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOED=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeView.obj" : $(SOURCE) $(DEP_CPP_PROMOED) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoEditor.cpp
DEP_CPP_PROMOEDI=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEditor.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\PropertyItem\CustomPropertyItem.h"\
	".\PropertyItem\PropertyItem.h"\
	".\PropertyItem\PropertyWrappers.h"\
	".\PropertyItem\TypedPropertyItem.h"\
	".\PropertyItem\TypedPropertyItem.hxx"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOEDI=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoEditor.obj" : $(SOURCE) $(DEP_CPP_PROMOEDI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoEntityContainer.cpp
DEP_CPP_PROMOEN=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoClipboardHandler.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOEN=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoEntityContainer.obj" : $(SOURCE) $(DEP_CPP_PROMOEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoModel.cpp
DEP_CPP_PROMOM=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOM=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoModel.obj" : $(SOURCE) $(DEP_CPP_PROMOM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoNameFactory.cpp
DEP_CPP_PROMON=\
	".\ProMoEditor\ProMoNameFactory.h"\
	
NODEP_CPP_PROMON=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoNameFactory.obj" : $(SOURCE) $(DEP_CPP_PROMON) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoBlockModel.cpp
DEP_CPP_PROMOB=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOB=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoBlockModel.obj" : $(SOURCE) $(DEP_CPP_PROMOB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMoView.cpp
DEP_CPP_WINPROM=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoClipboardHandler.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEditor.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	".\WinProMoDoc.h"\
	".\WinProMoView.h"\
	

"$(INTDIR)\WinProMoView.obj" : $(SOURCE) $(DEP_CPP_WINPROM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMoDocTemplate.cpp
DEP_CPP_WINPROMO=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoClipboardHandler.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	".\WinProMoDoc.h"\
	".\WinProMoDocTemplate.h"\
	

"$(INTDIR)\WinProMoDocTemplate.obj" : $(SOURCE) $(DEP_CPP_WINPROMO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMoDoc.cpp
DEP_CPP_WINPROMOD=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoClipboardHandler.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEditor.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\StdAfx.h"\
	".\WinProMoDoc.h"\
	".\WinProMoView.h"\
	

"$(INTDIR)\WinProMoDoc.obj" : $(SOURCE) $(DEP_CPP_WINPROMOD) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropertyItem\CustomPropertyItem.cpp
DEP_CPP_CUSTO=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\PropertyItem\CustomPropertyItem.h"\
	".\PropertyItem\PropertyItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CUSTO=\
	".\PropertyItem\stdafx.h"\
	

"$(INTDIR)\CustomPropertyItem.obj" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropertyItem\PropertyItem.cpp
DEP_CPP_PROPER=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\PropertyItem\PropertyItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROPER=\
	".\PropertyItem\stdafx.h"\
	

"$(INTDIR)\PropertyItem.obj" : $(SOURCE) $(DEP_CPP_PROPER) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropertyItem\PropertyWrappers.cpp
DEP_CPP_PROPERT=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\UndoItem.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\PropertyDialog.h"\
	".\PropertyItem\PropertyWrappers.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROPERT=\
	".\PropertyItem\stdafx.h"\
	

"$(INTDIR)\PropertyWrappers.obj" : $(SOURCE) $(DEP_CPP_PROPERT) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
