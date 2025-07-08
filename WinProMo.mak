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
CPP=cl.exe
RSC=rc.exe

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
	-@erase "..\Release\WinProMo.dll"
	-@erase ".\Release\BoolPropertyItem.obj"
	-@erase ".\Release\CustomPropertyItem.obj"
	-@erase ".\Release\DiagramClipboardHandler.obj"
	-@erase ".\Release\DiagramEditor.obj"
	-@erase ".\Release\DiagramEntity.obj"
	-@erase ".\Release\DiagramEntityContainer.obj"
	-@erase ".\Release\DiagramLine.obj"
	-@erase ".\Release\DiagramMenu.obj"
	-@erase ".\Release\DiagramPropertyDlg.obj"
	-@erase ".\Release\DoublePropertyItem.obj"
	-@erase ".\Release\GroupFactory.obj"
	-@erase ".\Release\IntPropertyItem.obj"
	-@erase ".\Release\ProMoBlockModel.obj"
	-@erase ".\Release\ProMoBlockView.obj"
	-@erase ".\Release\ProMoClipboardHandler.obj"
	-@erase ".\Release\ProMoControlFactory.obj"
	-@erase ".\Release\ProMoEdgeModel.obj"
	-@erase ".\Release\ProMoEdgeView.obj"
	-@erase ".\Release\ProMoEditor.obj"
	-@erase ".\Release\ProMoEntityContainer.obj"
	-@erase ".\Release\ProMoModel.obj"
	-@erase ".\Release\ProMoNameFactory.obj"
	-@erase ".\Release\PropertyDialog.obj"
	-@erase ".\Release\PropertyItem.obj"
	-@erase ".\Release\PropertyWrappers.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\StringPropertyItem.obj"
	-@erase ".\Release\Tokenizer.obj"
	-@erase ".\Release\UndoItem.obj"
	-@erase ".\Release\WinProMo.exp"
	-@erase ".\Release\WinProMo.lib"
	-@erase ".\Release\WinProMo.obj"
	-@erase ".\Release\WinProMo.pch"
	-@erase ".\Release\WinProMo.res"
	-@erase ".\Release\WinProMoDoc.obj"
	-@erase ".\Release\WinProMoDocTemplate.obj"
	-@erase ".\Release\WinProMoView.obj"

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
	".\Release\BoolPropertyItem.obj" \
	".\Release\CustomPropertyItem.obj" \
	".\Release\DiagramClipboardHandler.obj" \
	".\Release\DiagramEditor.obj" \
	".\Release\DiagramEntity.obj" \
	".\Release\DiagramEntityContainer.obj" \
	".\Release\DiagramLine.obj" \
	".\Release\DiagramMenu.obj" \
	".\Release\DiagramPropertyDlg.obj" \
	".\Release\DoublePropertyItem.obj" \
	".\Release\GroupFactory.obj" \
	".\Release\IntPropertyItem.obj" \
	".\Release\ProMoBlockModel.obj" \
	".\Release\ProMoBlockView.obj" \
	".\Release\ProMoClipboardHandler.obj" \
	".\Release\ProMoControlFactory.obj" \
	".\Release\ProMoEdgeModel.obj" \
	".\Release\ProMoEdgeView.obj" \
	".\Release\ProMoEditor.obj" \
	".\Release\ProMoEntityContainer.obj" \
	".\Release\ProMoModel.obj" \
	".\Release\ProMoNameFactory.obj" \
	".\Release\PropertyDialog.obj" \
	".\Release\PropertyItem.obj" \
	".\Release\PropertyWrappers.obj" \
	".\Release\StdAfx.obj" \
	".\Release\StringPropertyItem.obj" \
	".\Release\Tokenizer.obj" \
	".\Release\UndoItem.obj" \
	".\Release\WinProMo.obj" \
	".\Release\WinProMo.res" \
	".\Release\WinProMoDoc.obj" \
	".\Release\WinProMoDocTemplate.obj" \
	".\Release\WinProMoView.obj"

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
	-@erase "..\Debug\WinProMo.dll"
	-@erase "..\Debug\WinProMo.ilk"
	-@erase ".\Debug\BoolPropertyItem.obj"
	-@erase ".\Debug\CustomPropertyItem.obj"
	-@erase ".\Debug\DiagramClipboardHandler.obj"
	-@erase ".\Debug\DiagramEditor.obj"
	-@erase ".\Debug\DiagramEntity.obj"
	-@erase ".\Debug\DiagramEntityContainer.obj"
	-@erase ".\Debug\DiagramLine.obj"
	-@erase ".\Debug\DiagramMenu.obj"
	-@erase ".\Debug\DiagramPropertyDlg.obj"
	-@erase ".\Debug\DoublePropertyItem.obj"
	-@erase ".\Debug\GroupFactory.obj"
	-@erase ".\Debug\IntPropertyItem.obj"
	-@erase ".\Debug\ProMoBlockModel.obj"
	-@erase ".\Debug\ProMoBlockView.obj"
	-@erase ".\Debug\ProMoClipboardHandler.obj"
	-@erase ".\Debug\ProMoControlFactory.obj"
	-@erase ".\Debug\ProMoEdgeModel.obj"
	-@erase ".\Debug\ProMoEdgeView.obj"
	-@erase ".\Debug\ProMoEditor.obj"
	-@erase ".\Debug\ProMoEntityContainer.obj"
	-@erase ".\Debug\ProMoModel.obj"
	-@erase ".\Debug\ProMoNameFactory.obj"
	-@erase ".\Debug\PropertyDialog.obj"
	-@erase ".\Debug\PropertyItem.obj"
	-@erase ".\Debug\PropertyWrappers.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\StringPropertyItem.obj"
	-@erase ".\Debug\Tokenizer.obj"
	-@erase ".\Debug\UndoItem.obj"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\WinProMo.exp"
	-@erase ".\Debug\WinProMo.lib"
	-@erase ".\Debug\WinProMo.obj"
	-@erase ".\Debug\WinProMo.pch"
	-@erase ".\Debug\WinProMo.pdb"
	-@erase ".\Debug\WinProMo.res"
	-@erase ".\Debug\WinProMoDoc.obj"
	-@erase ".\Debug\WinProMoDocTemplate.obj"
	-@erase ".\Debug\WinProMoView.obj"

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
	".\Debug\BoolPropertyItem.obj" \
	".\Debug\CustomPropertyItem.obj" \
	".\Debug\DiagramClipboardHandler.obj" \
	".\Debug\DiagramEditor.obj" \
	".\Debug\DiagramEntity.obj" \
	".\Debug\DiagramEntityContainer.obj" \
	".\Debug\DiagramLine.obj" \
	".\Debug\DiagramMenu.obj" \
	".\Debug\DiagramPropertyDlg.obj" \
	".\Debug\DoublePropertyItem.obj" \
	".\Debug\GroupFactory.obj" \
	".\Debug\IntPropertyItem.obj" \
	".\Debug\ProMoBlockModel.obj" \
	".\Debug\ProMoBlockView.obj" \
	".\Debug\ProMoClipboardHandler.obj" \
	".\Debug\ProMoControlFactory.obj" \
	".\Debug\ProMoEdgeModel.obj" \
	".\Debug\ProMoEdgeView.obj" \
	".\Debug\ProMoEditor.obj" \
	".\Debug\ProMoEntityContainer.obj" \
	".\Debug\ProMoModel.obj" \
	".\Debug\ProMoNameFactory.obj" \
	".\Debug\PropertyDialog.obj" \
	".\Debug\PropertyItem.obj" \
	".\Debug\PropertyWrappers.obj" \
	".\Debug\StdAfx.obj" \
	".\Debug\StringPropertyItem.obj" \
	".\Debug\Tokenizer.obj" \
	".\Debug\UndoItem.obj" \
	".\Debug\WinProMo.obj" \
	".\Debug\WinProMo.res" \
	".\Debug\WinProMoDoc.obj" \
	".\Debug\WinProMoDocTemplate.obj" \
	".\Debug\WinProMoView.obj"

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\WinProMo.obj" : $(SOURCE) $(DEP_CPP_WINPR) "$(INTDIR)"\
 ".\Release\WinProMo.pch"


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\WinProMo.obj" : $(SOURCE) $(DEP_CPP_WINPR) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"


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
	

".\Release\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Release\WinProMo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D\
 WINPROMO_EXPORTS=1 /Fp"$(INTDIR)/WinProMo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

".\Debug\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

".\Debug\WinProMo.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMo.rc
DEP_RSC_WINPRO=\
	".\res\DiagramEditorDemo.ico"\
	".\res\DiagramEditorDemo.rc2"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\WinProMo.res" : $(SOURCE) $(DEP_RSC_WINPRO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\WinProMo.res" : $(SOURCE) $(DEP_RSC_WINPRO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DiagramEditor\UndoItem.cpp
DEP_CPP_UNDOI=\
	".\DiagramEditor\UndoItem.h"\
	
NODEP_CPP_UNDOI=\
	".\DiagramEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\UndoItem.obj" : $(SOURCE) $(DEP_CPP_UNDOI) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\UndoItem.obj" : $(SOURCE) $(DEP_CPP_UNDOI) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\DiagramEditor.obj" : $(SOURCE) $(DEP_CPP_DIAGR) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DiagramEditor.obj" : $(SOURCE) $(DEP_CPP_DIAGR) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	".\StdAfx.h"\
	
NODEP_CPP_DIAGRA=\
	".\DiagramEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\DiagramEntity.obj" : $(SOURCE) $(DEP_CPP_DIAGRA) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DiagramEntity.obj" : $(SOURCE) $(DEP_CPP_DIAGRA) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\DiagramEntityContainer.obj" : $(SOURCE) $(DEP_CPP_DIAGRAM)\
 "$(INTDIR)" ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DiagramEntityContainer.obj" : $(SOURCE) $(DEP_CPP_DIAGRAM) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\DiagramLine.obj" : $(SOURCE) $(DEP_CPP_DIAGRAML) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DiagramLine.obj" : $(SOURCE) $(DEP_CPP_DIAGRAML) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\DiagramMenu.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMM) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DiagramMenu.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMM) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\DiagramPropertyDlg.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMP) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DiagramPropertyDlg.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMP) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\GroupFactory.obj" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\GroupFactory.obj" : $(SOURCE) $(DEP_CPP_GROUP) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\Tokenizer.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\Tokenizer.obj" : $(SOURCE) $(DEP_CPP_TOKEN) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\DiagramClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMC)\
 "$(INTDIR)" ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DiagramClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMC)\
 "$(INTDIR)" ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\PropertyDialog.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\PropertyDialog.obj" : $(SOURCE) $(DEP_CPP_PROPE) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoBlockView.obj" : $(SOURCE) $(DEP_CPP_PROMO) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoBlockView.obj" : $(SOURCE) $(DEP_CPP_PROMO) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_PROMOC) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoClipboardHandler.obj" : $(SOURCE) $(DEP_CPP_PROMOC) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoControlFactory.obj" : $(SOURCE) $(DEP_CPP_PROMOCO) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoControlFactory.obj" : $(SOURCE) $(DEP_CPP_PROMOCO) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoEdgeModel.obj" : $(SOURCE) $(DEP_CPP_PROMOE) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoEdgeModel.obj" : $(SOURCE) $(DEP_CPP_PROMOE) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoEdgeView.obj" : $(SOURCE) $(DEP_CPP_PROMOED) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoEdgeView.obj" : $(SOURCE) $(DEP_CPP_PROMOED) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	".\PropertyItem\StringPropertyItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_PROMOEDI=\
	".\ProMoEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoEditor.obj" : $(SOURCE) $(DEP_CPP_PROMOEDI) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoEditor.obj" : $(SOURCE) $(DEP_CPP_PROMOEDI) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoEntityContainer.obj" : $(SOURCE) $(DEP_CPP_PROMOEN) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoEntityContainer.obj" : $(SOURCE) $(DEP_CPP_PROMOEN) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoModel.obj" : $(SOURCE) $(DEP_CPP_PROMOM) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoModel.obj" : $(SOURCE) $(DEP_CPP_PROMOM) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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


".\Release\ProMoNameFactory.obj" : $(SOURCE) $(DEP_CPP_PROMON) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoNameFactory.obj" : $(SOURCE) $(DEP_CPP_PROMON) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\ProMoBlockModel.obj" : $(SOURCE) $(DEP_CPP_PROMOB) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\ProMoBlockModel.obj" : $(SOURCE) $(DEP_CPP_PROMOB) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\WinProMoView.obj" : $(SOURCE) $(DEP_CPP_WINPROM) "$(INTDIR)"\
 ".\Release\WinProMo.pch"


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\WinProMoView.obj" : $(SOURCE) $(DEP_CPP_WINPROM) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\WinProMoDocTemplate.obj" : $(SOURCE) $(DEP_CPP_WINPROMO) "$(INTDIR)"\
 ".\Release\WinProMo.pch"


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\WinProMoDocTemplate.obj" : $(SOURCE) $(DEP_CPP_WINPROMO) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\WinProMoDoc.obj" : $(SOURCE) $(DEP_CPP_WINPROMOD) "$(INTDIR)"\
 ".\Release\WinProMo.pch"


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\WinProMoDoc.obj" : $(SOURCE) $(DEP_CPP_WINPROMOD) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropertyItem\StringPropertyItem.cpp
DEP_CPP_STRIN=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\PropertyItem\PropertyItem.h"\
	".\PropertyItem\StringPropertyItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_STRIN=\
	".\PropertyItem\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\StringPropertyItem.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\StringPropertyItem.obj" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\CustomPropertyItem.obj" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\CustomPropertyItem.obj" : $(SOURCE) $(DEP_CPP_CUSTO) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropertyItem\DoublePropertyItem.cpp
DEP_CPP_DOUBL=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\PropertyItem\DoublePropertyItem.h"\
	".\PropertyItem\PropertyItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DOUBL=\
	".\PropertyItem\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\DoublePropertyItem.obj" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\DoublePropertyItem.obj" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropertyItem\IntPropertyItem.cpp
DEP_CPP_INTPR=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\PropertyItem\IntPropertyItem.h"\
	".\PropertyItem\PropertyItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_INTPR=\
	".\PropertyItem\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\IntPropertyItem.obj" : $(SOURCE) $(DEP_CPP_INTPR) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\IntPropertyItem.obj" : $(SOURCE) $(DEP_CPP_INTPR) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\PropertyItem.obj" : $(SOURCE) $(DEP_CPP_PROPER) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\PropertyItem.obj" : $(SOURCE) $(DEP_CPP_PROPER) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\PropertyWrappers.obj" : $(SOURCE) $(DEP_CPP_PROPERT) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\PropertyWrappers.obj" : $(SOURCE) $(DEP_CPP_PROPERT) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropertyItem\BoolPropertyItem.cpp
DEP_CPP_BOOLP=\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	".\PropertyItem\BoolPropertyItem.h"\
	".\PropertyItem\PropertyItem.h"\
	".\StdAfx.h"\
	
NODEP_CPP_BOOLP=\
	".\PropertyItem\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


".\Release\BoolPropertyItem.obj" : $(SOURCE) $(DEP_CPP_BOOLP) "$(INTDIR)"\
 ".\Release\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


".\Debug\BoolPropertyItem.obj" : $(SOURCE) $(DEP_CPP_BOOLP) "$(INTDIR)"\
 ".\Debug\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
