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
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

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

ALL : "..\..\Release\WinProMo.dll"

CLEAN : 
	-@erase "$(INTDIR)\DiagramClipboardHandler.obj"
	-@erase "$(INTDIR)\DiagramEditor.obj"
	-@erase "$(INTDIR)\DiagramEntity.obj"
	-@erase "$(INTDIR)\DiagramEntityContainer.obj"
	-@erase "$(INTDIR)\DiagramLine.obj"
	-@erase "$(INTDIR)\DiagramMenu.obj"
	-@erase "$(INTDIR)\DiagramPropertyDlg.obj"
	-@erase "$(INTDIR)\DibHelper.obj"
	-@erase "$(INTDIR)\DoublePoint.obj"
	-@erase "$(INTDIR)\DoubleRect.obj"
	-@erase "$(INTDIR)\FileParser.obj"
	-@erase "$(INTDIR)\FileSerializer.obj"
	-@erase "$(INTDIR)\GeometryHelper.obj"
	-@erase "$(INTDIR)\GroupFactory.obj"
	-@erase "$(INTDIR)\IntersectionHelper.obj"
	-@erase "$(INTDIR)\ProMoBlockModel.obj"
	-@erase "$(INTDIR)\ProMoBlockView.obj"
	-@erase "$(INTDIR)\ProMoClipboardHandler.obj"
	-@erase "$(INTDIR)\ProMoControlFactory.obj"
	-@erase "$(INTDIR)\ProMoEdgeModel.obj"
	-@erase "$(INTDIR)\ProMoEdgeView.obj"
	-@erase "$(INTDIR)\ProMoEditor.obj"
	-@erase "$(INTDIR)\ProMoEntityContainer.obj"
	-@erase "$(INTDIR)\ProMoLabel.obj"
	-@erase "$(INTDIR)\ProMoModel.obj"
	-@erase "$(INTDIR)\ProMoNameFactory.obj"
	-@erase "$(INTDIR)\ProMoProperty.obj"
	-@erase "$(INTDIR)\ProMoRenderer.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tokenizer.obj"
	-@erase "$(INTDIR)\UndoItem.obj"
	-@erase "$(INTDIR)\VariantWrapper.obj"
	-@erase "$(INTDIR)\WinProMo.obj"
	-@erase "$(INTDIR)\WinProMo.pch"
	-@erase "$(INTDIR)\WinProMo.res"
	-@erase "$(OUTDIR)\WinProMo.exp"
	-@erase "$(OUTDIR)\WinProMo.lib"
	-@erase "..\..\Release\WinProMo.dll"

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
# ADD LINK32 /nologo /base:0x10000000 /subsystem:windows /dll /machine:I386 /out:"../../Release/WinProMo.dll"
LINK32_FLAGS=/nologo /base:0x10000000 /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/WinProMo.pdb" /machine:I386 /def:".\WinProMo.def"\
 /out:"../../Release/WinProMo.dll" /implib:"$(OUTDIR)/WinProMo.lib" 
DEF_FILE= \
	".\WinProMo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiagramClipboardHandler.obj" \
	"$(INTDIR)\DiagramEditor.obj" \
	"$(INTDIR)\DiagramEntity.obj" \
	"$(INTDIR)\DiagramEntityContainer.obj" \
	"$(INTDIR)\DiagramLine.obj" \
	"$(INTDIR)\DiagramMenu.obj" \
	"$(INTDIR)\DiagramPropertyDlg.obj" \
	"$(INTDIR)\DibHelper.obj" \
	"$(INTDIR)\DoublePoint.obj" \
	"$(INTDIR)\DoubleRect.obj" \
	"$(INTDIR)\FileParser.obj" \
	"$(INTDIR)\FileSerializer.obj" \
	"$(INTDIR)\GeometryHelper.obj" \
	"$(INTDIR)\GroupFactory.obj" \
	"$(INTDIR)\IntersectionHelper.obj" \
	"$(INTDIR)\ProMoBlockModel.obj" \
	"$(INTDIR)\ProMoBlockView.obj" \
	"$(INTDIR)\ProMoClipboardHandler.obj" \
	"$(INTDIR)\ProMoControlFactory.obj" \
	"$(INTDIR)\ProMoEdgeModel.obj" \
	"$(INTDIR)\ProMoEdgeView.obj" \
	"$(INTDIR)\ProMoEditor.obj" \
	"$(INTDIR)\ProMoEntityContainer.obj" \
	"$(INTDIR)\ProMoLabel.obj" \
	"$(INTDIR)\ProMoModel.obj" \
	"$(INTDIR)\ProMoNameFactory.obj" \
	"$(INTDIR)\ProMoProperty.obj" \
	"$(INTDIR)\ProMoRenderer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tokenizer.obj" \
	"$(INTDIR)\UndoItem.obj" \
	"$(INTDIR)\VariantWrapper.obj" \
	"$(INTDIR)\WinProMo.obj" \
	"$(INTDIR)\WinProMo.res"

"..\..\Release\WinProMo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

ALL : "..\..\Debug\WinProMo.dll" "$(OUTDIR)\WinProMo.bsc"

CLEAN : 
	-@erase "$(INTDIR)\DiagramClipboardHandler.obj"
	-@erase "$(INTDIR)\DiagramClipboardHandler.sbr"
	-@erase "$(INTDIR)\DiagramEditor.obj"
	-@erase "$(INTDIR)\DiagramEditor.sbr"
	-@erase "$(INTDIR)\DiagramEntity.obj"
	-@erase "$(INTDIR)\DiagramEntity.sbr"
	-@erase "$(INTDIR)\DiagramEntityContainer.obj"
	-@erase "$(INTDIR)\DiagramEntityContainer.sbr"
	-@erase "$(INTDIR)\DiagramLine.obj"
	-@erase "$(INTDIR)\DiagramLine.sbr"
	-@erase "$(INTDIR)\DiagramMenu.obj"
	-@erase "$(INTDIR)\DiagramMenu.sbr"
	-@erase "$(INTDIR)\DiagramPropertyDlg.obj"
	-@erase "$(INTDIR)\DiagramPropertyDlg.sbr"
	-@erase "$(INTDIR)\DibHelper.obj"
	-@erase "$(INTDIR)\DibHelper.sbr"
	-@erase "$(INTDIR)\DoublePoint.obj"
	-@erase "$(INTDIR)\DoublePoint.sbr"
	-@erase "$(INTDIR)\DoubleRect.obj"
	-@erase "$(INTDIR)\DoubleRect.sbr"
	-@erase "$(INTDIR)\FileParser.obj"
	-@erase "$(INTDIR)\FileParser.sbr"
	-@erase "$(INTDIR)\FileSerializer.obj"
	-@erase "$(INTDIR)\FileSerializer.sbr"
	-@erase "$(INTDIR)\GeometryHelper.obj"
	-@erase "$(INTDIR)\GeometryHelper.sbr"
	-@erase "$(INTDIR)\GroupFactory.obj"
	-@erase "$(INTDIR)\GroupFactory.sbr"
	-@erase "$(INTDIR)\IntersectionHelper.obj"
	-@erase "$(INTDIR)\IntersectionHelper.sbr"
	-@erase "$(INTDIR)\ProMoBlockModel.obj"
	-@erase "$(INTDIR)\ProMoBlockModel.sbr"
	-@erase "$(INTDIR)\ProMoBlockView.obj"
	-@erase "$(INTDIR)\ProMoBlockView.sbr"
	-@erase "$(INTDIR)\ProMoClipboardHandler.obj"
	-@erase "$(INTDIR)\ProMoClipboardHandler.sbr"
	-@erase "$(INTDIR)\ProMoControlFactory.obj"
	-@erase "$(INTDIR)\ProMoControlFactory.sbr"
	-@erase "$(INTDIR)\ProMoEdgeModel.obj"
	-@erase "$(INTDIR)\ProMoEdgeModel.sbr"
	-@erase "$(INTDIR)\ProMoEdgeView.obj"
	-@erase "$(INTDIR)\ProMoEdgeView.sbr"
	-@erase "$(INTDIR)\ProMoEditor.obj"
	-@erase "$(INTDIR)\ProMoEditor.sbr"
	-@erase "$(INTDIR)\ProMoEntityContainer.obj"
	-@erase "$(INTDIR)\ProMoEntityContainer.sbr"
	-@erase "$(INTDIR)\ProMoLabel.obj"
	-@erase "$(INTDIR)\ProMoLabel.sbr"
	-@erase "$(INTDIR)\ProMoModel.obj"
	-@erase "$(INTDIR)\ProMoModel.sbr"
	-@erase "$(INTDIR)\ProMoNameFactory.obj"
	-@erase "$(INTDIR)\ProMoNameFactory.sbr"
	-@erase "$(INTDIR)\ProMoProperty.obj"
	-@erase "$(INTDIR)\ProMoProperty.sbr"
	-@erase "$(INTDIR)\ProMoRenderer.obj"
	-@erase "$(INTDIR)\ProMoRenderer.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Tokenizer.obj"
	-@erase "$(INTDIR)\Tokenizer.sbr"
	-@erase "$(INTDIR)\UndoItem.obj"
	-@erase "$(INTDIR)\UndoItem.sbr"
	-@erase "$(INTDIR)\VariantWrapper.obj"
	-@erase "$(INTDIR)\VariantWrapper.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WinProMo.obj"
	-@erase "$(INTDIR)\WinProMo.pch"
	-@erase "$(INTDIR)\WinProMo.res"
	-@erase "$(INTDIR)\WinProMo.sbr"
	-@erase "$(OUTDIR)\WinProMo.bsc"
	-@erase "$(OUTDIR)\WinProMo.exp"
	-@erase "$(OUTDIR)\WinProMo.lib"
	-@erase "$(OUTDIR)\WinProMo.pdb"
	-@erase "..\..\Debug\WinProMo.dll"
	-@erase "..\..\Debug\WinProMo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D WINPROMO_EXPORTS=1 /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D\
 WINPROMO_EXPORTS=1 /FR"$(INTDIR)/" /Fp"$(INTDIR)/WinProMo.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
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
	"$(INTDIR)\DiagramClipboardHandler.sbr" \
	"$(INTDIR)\DiagramEditor.sbr" \
	"$(INTDIR)\DiagramEntity.sbr" \
	"$(INTDIR)\DiagramEntityContainer.sbr" \
	"$(INTDIR)\DiagramLine.sbr" \
	"$(INTDIR)\DiagramMenu.sbr" \
	"$(INTDIR)\DiagramPropertyDlg.sbr" \
	"$(INTDIR)\DibHelper.sbr" \
	"$(INTDIR)\DoublePoint.sbr" \
	"$(INTDIR)\DoubleRect.sbr" \
	"$(INTDIR)\FileParser.sbr" \
	"$(INTDIR)\FileSerializer.sbr" \
	"$(INTDIR)\GeometryHelper.sbr" \
	"$(INTDIR)\GroupFactory.sbr" \
	"$(INTDIR)\IntersectionHelper.sbr" \
	"$(INTDIR)\ProMoBlockModel.sbr" \
	"$(INTDIR)\ProMoBlockView.sbr" \
	"$(INTDIR)\ProMoClipboardHandler.sbr" \
	"$(INTDIR)\ProMoControlFactory.sbr" \
	"$(INTDIR)\ProMoEdgeModel.sbr" \
	"$(INTDIR)\ProMoEdgeView.sbr" \
	"$(INTDIR)\ProMoEditor.sbr" \
	"$(INTDIR)\ProMoEntityContainer.sbr" \
	"$(INTDIR)\ProMoLabel.sbr" \
	"$(INTDIR)\ProMoModel.sbr" \
	"$(INTDIR)\ProMoNameFactory.sbr" \
	"$(INTDIR)\ProMoProperty.sbr" \
	"$(INTDIR)\ProMoRenderer.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Tokenizer.sbr" \
	"$(INTDIR)\UndoItem.sbr" \
	"$(INTDIR)\VariantWrapper.sbr" \
	"$(INTDIR)\WinProMo.sbr"

"$(OUTDIR)\WinProMo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /base:0x10000000 /subsystem:windows /dll /debug /machine:I386 /out:"../../Debug/WinProMo.dll"
LINK32_FLAGS=/nologo /base:0x10000000 /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/WinProMo.pdb" /debug /machine:I386 /def:".\WinProMo.def"\
 /out:"../../Debug/WinProMo.dll" /implib:"$(OUTDIR)/WinProMo.lib" 
DEF_FILE= \
	".\WinProMo.def"
LINK32_OBJS= \
	"$(INTDIR)\DiagramClipboardHandler.obj" \
	"$(INTDIR)\DiagramEditor.obj" \
	"$(INTDIR)\DiagramEntity.obj" \
	"$(INTDIR)\DiagramEntityContainer.obj" \
	"$(INTDIR)\DiagramLine.obj" \
	"$(INTDIR)\DiagramMenu.obj" \
	"$(INTDIR)\DiagramPropertyDlg.obj" \
	"$(INTDIR)\DibHelper.obj" \
	"$(INTDIR)\DoublePoint.obj" \
	"$(INTDIR)\DoubleRect.obj" \
	"$(INTDIR)\FileParser.obj" \
	"$(INTDIR)\FileSerializer.obj" \
	"$(INTDIR)\GeometryHelper.obj" \
	"$(INTDIR)\GroupFactory.obj" \
	"$(INTDIR)\IntersectionHelper.obj" \
	"$(INTDIR)\ProMoBlockModel.obj" \
	"$(INTDIR)\ProMoBlockView.obj" \
	"$(INTDIR)\ProMoClipboardHandler.obj" \
	"$(INTDIR)\ProMoControlFactory.obj" \
	"$(INTDIR)\ProMoEdgeModel.obj" \
	"$(INTDIR)\ProMoEdgeView.obj" \
	"$(INTDIR)\ProMoEditor.obj" \
	"$(INTDIR)\ProMoEntityContainer.obj" \
	"$(INTDIR)\ProMoLabel.obj" \
	"$(INTDIR)\ProMoModel.obj" \
	"$(INTDIR)\ProMoNameFactory.obj" \
	"$(INTDIR)\ProMoProperty.obj" \
	"$(INTDIR)\ProMoRenderer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tokenizer.obj" \
	"$(INTDIR)\UndoItem.obj" \
	"$(INTDIR)\VariantWrapper.obj" \
	"$(INTDIR)\WinProMo.obj" \
	"$(INTDIR)\WinProMo.res"

"..\..\Debug\WinProMo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\WinProMo.obj" : $(SOURCE) $(DEP_CPP_WINPR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


"$(INTDIR)\WinProMo.obj" : $(SOURCE) $(DEP_CPP_WINPR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"

"$(INTDIR)\WinProMo.sbr" : $(SOURCE) $(DEP_CPP_WINPR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"


!ENDIF 

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
 WINPROMO_EXPORTS=1 /FR"$(INTDIR)/" /Fp"$(INTDIR)/WinProMo.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\UndoItem.obj" : $(SOURCE) $(DEP_CPP_UNDOI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\UndoItem.obj" : $(SOURCE) $(DEP_CPP_UNDOI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\UndoItem.sbr" : $(SOURCE) $(DEP_CPP_UNDOI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DiagramEditor.obj" : $(SOURCE) $(DEP_CPP_DIAGR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DiagramEditor.obj" : $(SOURCE) $(DEP_CPP_DIAGR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DiagramEditor.sbr" : $(SOURCE) $(DEP_CPP_DIAGR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\FileUtils\FileParser.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRA=\
	".\DiagramEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DiagramEntity.obj" : $(SOURCE) $(DEP_CPP_DIAGRA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DiagramEntity.obj" : $(SOURCE) $(DEP_CPP_DIAGRA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DiagramEntity.sbr" : $(SOURCE) $(DEP_CPP_DIAGRA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DiagramEntityContainer.obj" : $(SOURCE) $(DEP_CPP_DIAGRAM)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DiagramEntityContainer.obj" : $(SOURCE) $(DEP_CPP_DIAGRAM)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DiagramEntityContainer.sbr" : $(SOURCE) $(DEP_CPP_DIAGRAM)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DiagramLine.obj" : $(SOURCE) $(DEP_CPP_DIAGRAML) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DiagramLine.obj" : $(SOURCE) $(DEP_CPP_DIAGRAML) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DiagramLine.sbr" : $(SOURCE) $(DEP_CPP_DIAGRAML) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\DiagramMenu.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_DIAGRAMM=\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRAMM=\
	".\DiagramEditor\stdafx.h"\
	

"$(INTDIR)\DiagramMenu.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

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
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DiagramMenu.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DiagramMenu.sbr" : $(SOURCE) $(DEP_CPP_DIAGRAMM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DiagramPropertyDlg.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DiagramPropertyDlg.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DiagramPropertyDlg.sbr" : $(SOURCE) $(DEP_CPP_DIAGRAMP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\GroupFactory.cpp
DEP_CPP_GROUP=\
	".\DiagramEditor\GroupFactory.h"\
	
NODEP_CPP_GROUP=\
	".\DiagramEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\GroupFactory.obj" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\GroupFactory.obj" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\GroupFactory.sbr" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\Tokenizer.cpp
DEP_CPP_TOKEN=\
	".\DiagramEditor\Tokenizer.h"\
	
NODEP_CPP_TOKEN=\
	".\DiagramEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\Tokenizer.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Tokenizer.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\Tokenizer.sbr" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DiagramClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMC)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DiagramClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMC)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DiagramClipboardHandler.sbr" : $(SOURCE) $(DEP_CPP_DIAGRAMC)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\GeometryUtils\GeometryHelper.h"\
	".\GeometryUtils\IntersectionHelper.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMO=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoBlockView.obj" : $(SOURCE) $(DEP_CPP_PROMO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoBlockView.obj" : $(SOURCE) $(DEP_CPP_PROMO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoBlockView.sbr" : $(SOURCE) $(DEP_CPP_PROMO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoClipboardHandler.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOC=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_PROMOC) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_PROMOC) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoClipboardHandler.sbr" : $(SOURCE) $(DEP_CPP_PROMOC) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOCO=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoControlFactory.obj" : $(SOURCE) $(DEP_CPP_PROMOCO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoControlFactory.obj" : $(SOURCE) $(DEP_CPP_PROMOCO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoControlFactory.sbr" : $(SOURCE) $(DEP_CPP_PROMOCO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\DiagramEditor\Tokenizer.h"\
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOE=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoEdgeModel.obj" : $(SOURCE) $(DEP_CPP_PROMOE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEdgeModel.obj" : $(SOURCE) $(DEP_CPP_PROMOE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEdgeModel.sbr" : $(SOURCE) $(DEP_CPP_PROMOE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOED=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoEdgeView.obj" : $(SOURCE) $(DEP_CPP_PROMOED) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEdgeView.obj" : $(SOURCE) $(DEP_CPP_PROMOED) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEdgeView.sbr" : $(SOURCE) $(DEP_CPP_PROMOED) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\GeometryUtils\GeometryHelper.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEditor.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOEDI=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoEditor.obj" : $(SOURCE) $(DEP_CPP_PROMOEDI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEditor.obj" : $(SOURCE) $(DEP_CPP_PROMOEDI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEditor.sbr" : $(SOURCE) $(DEP_CPP_PROMOEDI) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoClipboardHandler.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOEN=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoEntityContainer.obj" : $(SOURCE) $(DEP_CPP_PROMOEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEntityContainer.obj" : $(SOURCE) $(DEP_CPP_PROMOEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEntityContainer.sbr" : $(SOURCE) $(DEP_CPP_PROMOEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoModel.cpp
DEP_CPP_PROMOM=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOM=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoModel.obj" : $(SOURCE) $(DEP_CPP_PROMOM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoModel.obj" : $(SOURCE) $(DEP_CPP_PROMOM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoModel.sbr" : $(SOURCE) $(DEP_CPP_PROMOM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoNameFactory.cpp
DEP_CPP_PROMON=\
	".\ProMoEditor\ProMoNameFactory.h"\
	
NODEP_CPP_PROMON=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoNameFactory.obj" : $(SOURCE) $(DEP_CPP_PROMON) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoNameFactory.obj" : $(SOURCE) $(DEP_CPP_PROMON) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoNameFactory.sbr" : $(SOURCE) $(DEP_CPP_PROMON) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

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
	".\DiagramEditor\Tokenizer.h"\
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOB=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoBlockModel.obj" : $(SOURCE) $(DEP_CPP_PROMOB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoBlockModel.obj" : $(SOURCE) $(DEP_CPP_PROMOB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoBlockModel.sbr" : $(SOURCE) $(DEP_CPP_PROMOB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FileUtils\FileParser.cpp
DEP_CPP_FILEP=\
	".\DiagramEditor\Tokenizer.h"\
	".\FileUtils\FileParser.h"\
	
NODEP_CPP_FILEP=\
	".\FileUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\FileParser.obj" : $(SOURCE) $(DEP_CPP_FILEP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\FileParser.obj" : $(SOURCE) $(DEP_CPP_FILEP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\FileParser.sbr" : $(SOURCE) $(DEP_CPP_FILEP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FileUtils\FileSerializer.cpp
DEP_CPP_FILES=\
	".\FileUtils\FileSerializer.h"\
	
NODEP_CPP_FILES=\
	".\FileUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\FileSerializer.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\FileSerializer.obj" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\FileSerializer.sbr" : $(SOURCE) $(DEP_CPP_FILES) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeometryUtils\IntersectionHelper.cpp
DEP_CPP_INTER=\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\GeometryUtils\GeometryHelper.h"\
	".\GeometryUtils\IntersectionHelper.h"\
	
NODEP_CPP_INTER=\
	".\GeometryUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\IntersectionHelper.obj" : $(SOURCE) $(DEP_CPP_INTER) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\IntersectionHelper.obj" : $(SOURCE) $(DEP_CPP_INTER) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\IntersectionHelper.sbr" : $(SOURCE) $(DEP_CPP_INTER) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeometryUtils\DoubleRect.cpp
DEP_CPP_DOUBL=\
	".\GeometryUtils\DoubleRect.h"\
	
NODEP_CPP_DOUBL=\
	".\GeometryUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DoubleRect.obj" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DoubleRect.obj" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DoubleRect.sbr" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeometryUtils\GeometryHelper.cpp
DEP_CPP_GEOME=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\GeometryUtils\GeometryHelper.h"\
	".\StdAfx.h"\
	
NODEP_CPP_GEOME=\
	".\GeometryUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\GeometryHelper.obj" : $(SOURCE) $(DEP_CPP_GEOME) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\GeometryHelper.obj" : $(SOURCE) $(DEP_CPP_GEOME) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\GeometryHelper.sbr" : $(SOURCE) $(DEP_CPP_GEOME) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GeometryUtils\DoublePoint.cpp
DEP_CPP_DOUBLE=\
	".\GeometryUtils\DoublePoint.h"\
	
NODEP_CPP_DOUBLE=\
	".\GeometryUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DoublePoint.obj" : $(SOURCE) $(DEP_CPP_DOUBLE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DoublePoint.obj" : $(SOURCE) $(DEP_CPP_DOUBLE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DoublePoint.sbr" : $(SOURCE) $(DEP_CPP_DOUBLE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FileUtils\VariantWrapper.cpp
DEP_CPP_VARIA=\
	".\FileUtils\VariantWrapper.h"\
	".\StdAfx.h"\
	
NODEP_CPP_VARIA=\
	".\FileUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\VariantWrapper.obj" : $(SOURCE) $(DEP_CPP_VARIA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\VariantWrapper.obj" : $(SOURCE) $(DEP_CPP_VARIA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\VariantWrapper.sbr" : $(SOURCE) $(DEP_CPP_VARIA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoProperty.cpp
DEP_CPP_PROMOP=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOP=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoProperty.obj" : $(SOURCE) $(DEP_CPP_PROMOP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoProperty.obj" : $(SOURCE) $(DEP_CPP_PROMOP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoProperty.sbr" : $(SOURCE) $(DEP_CPP_PROMOP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoLabel.cpp
DEP_CPP_PROMOL=\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOL=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoLabel.obj" : $(SOURCE) $(DEP_CPP_PROMOL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoLabel.obj" : $(SOURCE) $(DEP_CPP_PROMOL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoLabel.sbr" : $(SOURCE) $(DEP_CPP_PROMOL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FileUtils\DibHelper.cpp
DEP_CPP_DIBHE=\
	".\FileUtils\DibHelper.h"\
	
NODEP_CPP_DIBHE=\
	".\FileUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DibHelper.obj" : $(SOURCE) $(DEP_CPP_DIBHE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DibHelper.obj" : $(SOURCE) $(DEP_CPP_DIBHE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\DibHelper.sbr" : $(SOURCE) $(DEP_CPP_DIBHE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProMoEditor\ProMoRenderer.cpp
DEP_CPP_PROMOR=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\FileUtils\DibHelper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoEntityContainer.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoModel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOR=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoRenderer.obj" : $(SOURCE) $(DEP_CPP_PROMOR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoRenderer.obj" : $(SOURCE) $(DEP_CPP_PROMOR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoRenderer.sbr" : $(SOURCE) $(DEP_CPP_PROMOR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
