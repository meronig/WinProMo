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

ALL : "..\..\Release\WinProMo.dll" "..\..\Release\WinProMo.tlb"

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
	-@erase "$(INTDIR)\ProMoAppAutoAbs.obj"
	-@erase "$(INTDIR)\ProMoAppChildAuto.obj"
	-@erase "$(INTDIR)\ProMoBlockAuto.obj"
	-@erase "$(INTDIR)\ProMoBlockChildAuto.obj"
	-@erase "$(INTDIR)\ProMoBlockModel.obj"
	-@erase "$(INTDIR)\ProMoBlockView.obj"
	-@erase "$(INTDIR)\ProMoBoundaryBlocksAuto.obj"
	-@erase "$(INTDIR)\ProMoClipboardHandler.obj"
	-@erase "$(INTDIR)\ProMoControlFactory.obj"
	-@erase "$(INTDIR)\ProMoDiagramAutoAbs.obj"
	-@erase "$(INTDIR)\ProMoDiagramChildAuto.obj"
	-@erase "$(INTDIR)\ProMoDiagramsAutoAbs.obj"
	-@erase "$(INTDIR)\ProMoEdgeAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeChildAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeModel.obj"
	-@erase "$(INTDIR)\ProMoEdgeSegmentAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeSegmentsAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeView.obj"
	-@erase "$(INTDIR)\ProMoEditor.obj"
	-@erase "$(INTDIR)\ProMoElementAuto.obj"
	-@erase "$(INTDIR)\ProMoElementChildAuto.obj"
	-@erase "$(INTDIR)\ProMoElementsAuto.obj"
	-@erase "$(INTDIR)\ProMoEntityContainer.obj"
	-@erase "$(INTDIR)\ProMoIncomingEdgesAuto.obj"
	-@erase "$(INTDIR)\ProMoLabel.obj"
	-@erase "$(INTDIR)\ProMoLabelAuto.obj"
	-@erase "$(INTDIR)\ProMoLabelsAuto.obj"
	-@erase "$(INTDIR)\ProMoModel.obj"
	-@erase "$(INTDIR)\ProMoNameFactory.obj"
	-@erase "$(INTDIR)\ProMoOutgoingEdgesAuto.obj"
	-@erase "$(INTDIR)\ProMoPropertiesAuto.obj"
	-@erase "$(INTDIR)\ProMoProperty.obj"
	-@erase "$(INTDIR)\ProMoPropertyAuto.obj"
	-@erase "$(INTDIR)\ProMoRenderer.obj"
	-@erase "$(INTDIR)\ProMoSubBlocksAuto.obj"
	-@erase "$(INTDIR)\SafeArrayWrapper.obj"
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
	-@erase "..\..\Release\WinProMo.tlb"

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
	"$(INTDIR)\ProMoAppAutoAbs.obj" \
	"$(INTDIR)\ProMoAppChildAuto.obj" \
	"$(INTDIR)\ProMoBlockAuto.obj" \
	"$(INTDIR)\ProMoBlockChildAuto.obj" \
	"$(INTDIR)\ProMoBlockModel.obj" \
	"$(INTDIR)\ProMoBlockView.obj" \
	"$(INTDIR)\ProMoBoundaryBlocksAuto.obj" \
	"$(INTDIR)\ProMoClipboardHandler.obj" \
	"$(INTDIR)\ProMoControlFactory.obj" \
	"$(INTDIR)\ProMoDiagramAutoAbs.obj" \
	"$(INTDIR)\ProMoDiagramChildAuto.obj" \
	"$(INTDIR)\ProMoDiagramsAutoAbs.obj" \
	"$(INTDIR)\ProMoEdgeAuto.obj" \
	"$(INTDIR)\ProMoEdgeChildAuto.obj" \
	"$(INTDIR)\ProMoEdgeModel.obj" \
	"$(INTDIR)\ProMoEdgeSegmentAuto.obj" \
	"$(INTDIR)\ProMoEdgeSegmentsAuto.obj" \
	"$(INTDIR)\ProMoEdgeView.obj" \
	"$(INTDIR)\ProMoEditor.obj" \
	"$(INTDIR)\ProMoElementAuto.obj" \
	"$(INTDIR)\ProMoElementChildAuto.obj" \
	"$(INTDIR)\ProMoElementsAuto.obj" \
	"$(INTDIR)\ProMoEntityContainer.obj" \
	"$(INTDIR)\ProMoIncomingEdgesAuto.obj" \
	"$(INTDIR)\ProMoLabel.obj" \
	"$(INTDIR)\ProMoLabelAuto.obj" \
	"$(INTDIR)\ProMoLabelsAuto.obj" \
	"$(INTDIR)\ProMoModel.obj" \
	"$(INTDIR)\ProMoNameFactory.obj" \
	"$(INTDIR)\ProMoOutgoingEdgesAuto.obj" \
	"$(INTDIR)\ProMoPropertiesAuto.obj" \
	"$(INTDIR)\ProMoProperty.obj" \
	"$(INTDIR)\ProMoPropertyAuto.obj" \
	"$(INTDIR)\ProMoRenderer.obj" \
	"$(INTDIR)\ProMoSubBlocksAuto.obj" \
	"$(INTDIR)\SafeArrayWrapper.obj" \
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

ALL : "..\..\Debug\WinProMo.dll" "..\..\Debug\WinProMo.tlb"\
 "$(OUTDIR)\WinProMo.bsc"

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
	-@erase "$(INTDIR)\ProMoAppAutoAbs.obj"
	-@erase "$(INTDIR)\ProMoAppAutoAbs.sbr"
	-@erase "$(INTDIR)\ProMoAppChildAuto.obj"
	-@erase "$(INTDIR)\ProMoAppChildAuto.sbr"
	-@erase "$(INTDIR)\ProMoBlockAuto.obj"
	-@erase "$(INTDIR)\ProMoBlockAuto.sbr"
	-@erase "$(INTDIR)\ProMoBlockChildAuto.obj"
	-@erase "$(INTDIR)\ProMoBlockChildAuto.sbr"
	-@erase "$(INTDIR)\ProMoBlockModel.obj"
	-@erase "$(INTDIR)\ProMoBlockModel.sbr"
	-@erase "$(INTDIR)\ProMoBlockView.obj"
	-@erase "$(INTDIR)\ProMoBlockView.sbr"
	-@erase "$(INTDIR)\ProMoBoundaryBlocksAuto.obj"
	-@erase "$(INTDIR)\ProMoBoundaryBlocksAuto.sbr"
	-@erase "$(INTDIR)\ProMoClipboardHandler.obj"
	-@erase "$(INTDIR)\ProMoClipboardHandler.sbr"
	-@erase "$(INTDIR)\ProMoControlFactory.obj"
	-@erase "$(INTDIR)\ProMoControlFactory.sbr"
	-@erase "$(INTDIR)\ProMoDiagramAutoAbs.obj"
	-@erase "$(INTDIR)\ProMoDiagramAutoAbs.sbr"
	-@erase "$(INTDIR)\ProMoDiagramChildAuto.obj"
	-@erase "$(INTDIR)\ProMoDiagramChildAuto.sbr"
	-@erase "$(INTDIR)\ProMoDiagramsAutoAbs.obj"
	-@erase "$(INTDIR)\ProMoDiagramsAutoAbs.sbr"
	-@erase "$(INTDIR)\ProMoEdgeAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeAuto.sbr"
	-@erase "$(INTDIR)\ProMoEdgeChildAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeChildAuto.sbr"
	-@erase "$(INTDIR)\ProMoEdgeModel.obj"
	-@erase "$(INTDIR)\ProMoEdgeModel.sbr"
	-@erase "$(INTDIR)\ProMoEdgeSegmentAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeSegmentAuto.sbr"
	-@erase "$(INTDIR)\ProMoEdgeSegmentsAuto.obj"
	-@erase "$(INTDIR)\ProMoEdgeSegmentsAuto.sbr"
	-@erase "$(INTDIR)\ProMoEdgeView.obj"
	-@erase "$(INTDIR)\ProMoEdgeView.sbr"
	-@erase "$(INTDIR)\ProMoEditor.obj"
	-@erase "$(INTDIR)\ProMoEditor.sbr"
	-@erase "$(INTDIR)\ProMoElementAuto.obj"
	-@erase "$(INTDIR)\ProMoElementAuto.sbr"
	-@erase "$(INTDIR)\ProMoElementChildAuto.obj"
	-@erase "$(INTDIR)\ProMoElementChildAuto.sbr"
	-@erase "$(INTDIR)\ProMoElementsAuto.obj"
	-@erase "$(INTDIR)\ProMoElementsAuto.sbr"
	-@erase "$(INTDIR)\ProMoEntityContainer.obj"
	-@erase "$(INTDIR)\ProMoEntityContainer.sbr"
	-@erase "$(INTDIR)\ProMoIncomingEdgesAuto.obj"
	-@erase "$(INTDIR)\ProMoIncomingEdgesAuto.sbr"
	-@erase "$(INTDIR)\ProMoLabel.obj"
	-@erase "$(INTDIR)\ProMoLabel.sbr"
	-@erase "$(INTDIR)\ProMoLabelAuto.obj"
	-@erase "$(INTDIR)\ProMoLabelAuto.sbr"
	-@erase "$(INTDIR)\ProMoLabelsAuto.obj"
	-@erase "$(INTDIR)\ProMoLabelsAuto.sbr"
	-@erase "$(INTDIR)\ProMoModel.obj"
	-@erase "$(INTDIR)\ProMoModel.sbr"
	-@erase "$(INTDIR)\ProMoNameFactory.obj"
	-@erase "$(INTDIR)\ProMoNameFactory.sbr"
	-@erase "$(INTDIR)\ProMoOutgoingEdgesAuto.obj"
	-@erase "$(INTDIR)\ProMoOutgoingEdgesAuto.sbr"
	-@erase "$(INTDIR)\ProMoPropertiesAuto.obj"
	-@erase "$(INTDIR)\ProMoPropertiesAuto.sbr"
	-@erase "$(INTDIR)\ProMoProperty.obj"
	-@erase "$(INTDIR)\ProMoProperty.sbr"
	-@erase "$(INTDIR)\ProMoPropertyAuto.obj"
	-@erase "$(INTDIR)\ProMoPropertyAuto.sbr"
	-@erase "$(INTDIR)\ProMoRenderer.obj"
	-@erase "$(INTDIR)\ProMoRenderer.sbr"
	-@erase "$(INTDIR)\ProMoSubBlocksAuto.obj"
	-@erase "$(INTDIR)\ProMoSubBlocksAuto.sbr"
	-@erase "$(INTDIR)\SafeArrayWrapper.obj"
	-@erase "$(INTDIR)\SafeArrayWrapper.sbr"
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
	-@erase "..\..\Debug\WinProMo.tlb"

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
	"$(INTDIR)\ProMoAppAutoAbs.sbr" \
	"$(INTDIR)\ProMoAppChildAuto.sbr" \
	"$(INTDIR)\ProMoBlockAuto.sbr" \
	"$(INTDIR)\ProMoBlockChildAuto.sbr" \
	"$(INTDIR)\ProMoBlockModel.sbr" \
	"$(INTDIR)\ProMoBlockView.sbr" \
	"$(INTDIR)\ProMoBoundaryBlocksAuto.sbr" \
	"$(INTDIR)\ProMoClipboardHandler.sbr" \
	"$(INTDIR)\ProMoControlFactory.sbr" \
	"$(INTDIR)\ProMoDiagramAutoAbs.sbr" \
	"$(INTDIR)\ProMoDiagramChildAuto.sbr" \
	"$(INTDIR)\ProMoDiagramsAutoAbs.sbr" \
	"$(INTDIR)\ProMoEdgeAuto.sbr" \
	"$(INTDIR)\ProMoEdgeChildAuto.sbr" \
	"$(INTDIR)\ProMoEdgeModel.sbr" \
	"$(INTDIR)\ProMoEdgeSegmentAuto.sbr" \
	"$(INTDIR)\ProMoEdgeSegmentsAuto.sbr" \
	"$(INTDIR)\ProMoEdgeView.sbr" \
	"$(INTDIR)\ProMoEditor.sbr" \
	"$(INTDIR)\ProMoElementAuto.sbr" \
	"$(INTDIR)\ProMoElementChildAuto.sbr" \
	"$(INTDIR)\ProMoElementsAuto.sbr" \
	"$(INTDIR)\ProMoEntityContainer.sbr" \
	"$(INTDIR)\ProMoIncomingEdgesAuto.sbr" \
	"$(INTDIR)\ProMoLabel.sbr" \
	"$(INTDIR)\ProMoLabelAuto.sbr" \
	"$(INTDIR)\ProMoLabelsAuto.sbr" \
	"$(INTDIR)\ProMoModel.sbr" \
	"$(INTDIR)\ProMoNameFactory.sbr" \
	"$(INTDIR)\ProMoOutgoingEdgesAuto.sbr" \
	"$(INTDIR)\ProMoPropertiesAuto.sbr" \
	"$(INTDIR)\ProMoProperty.sbr" \
	"$(INTDIR)\ProMoPropertyAuto.sbr" \
	"$(INTDIR)\ProMoRenderer.sbr" \
	"$(INTDIR)\ProMoSubBlocksAuto.sbr" \
	"$(INTDIR)\SafeArrayWrapper.sbr" \
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
	"$(INTDIR)\ProMoAppAutoAbs.obj" \
	"$(INTDIR)\ProMoAppChildAuto.obj" \
	"$(INTDIR)\ProMoBlockAuto.obj" \
	"$(INTDIR)\ProMoBlockChildAuto.obj" \
	"$(INTDIR)\ProMoBlockModel.obj" \
	"$(INTDIR)\ProMoBlockView.obj" \
	"$(INTDIR)\ProMoBoundaryBlocksAuto.obj" \
	"$(INTDIR)\ProMoClipboardHandler.obj" \
	"$(INTDIR)\ProMoControlFactory.obj" \
	"$(INTDIR)\ProMoDiagramAutoAbs.obj" \
	"$(INTDIR)\ProMoDiagramChildAuto.obj" \
	"$(INTDIR)\ProMoDiagramsAutoAbs.obj" \
	"$(INTDIR)\ProMoEdgeAuto.obj" \
	"$(INTDIR)\ProMoEdgeChildAuto.obj" \
	"$(INTDIR)\ProMoEdgeModel.obj" \
	"$(INTDIR)\ProMoEdgeSegmentAuto.obj" \
	"$(INTDIR)\ProMoEdgeSegmentsAuto.obj" \
	"$(INTDIR)\ProMoEdgeView.obj" \
	"$(INTDIR)\ProMoEditor.obj" \
	"$(INTDIR)\ProMoElementAuto.obj" \
	"$(INTDIR)\ProMoElementChildAuto.obj" \
	"$(INTDIR)\ProMoElementsAuto.obj" \
	"$(INTDIR)\ProMoEntityContainer.obj" \
	"$(INTDIR)\ProMoIncomingEdgesAuto.obj" \
	"$(INTDIR)\ProMoLabel.obj" \
	"$(INTDIR)\ProMoLabelAuto.obj" \
	"$(INTDIR)\ProMoLabelsAuto.obj" \
	"$(INTDIR)\ProMoModel.obj" \
	"$(INTDIR)\ProMoNameFactory.obj" \
	"$(INTDIR)\ProMoOutgoingEdgesAuto.obj" \
	"$(INTDIR)\ProMoPropertiesAuto.obj" \
	"$(INTDIR)\ProMoProperty.obj" \
	"$(INTDIR)\ProMoPropertyAuto.obj" \
	"$(INTDIR)\ProMoRenderer.obj" \
	"$(INTDIR)\ProMoSubBlocksAuto.obj" \
	"$(INTDIR)\SafeArrayWrapper.obj" \
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
	".\Automation\..\stdafx.h"\
	

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
	".\Automation\..\stdafx.h"\
	

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
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\WinProMo.res" : $(SOURCE) $(DEP_RSC_WINPRO) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WinProMo.res" /i "Release" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


"$(INTDIR)\WinProMo.res" : $(SOURCE) $(DEP_RSC_WINPRO) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/WinProMo.res" /i "Debug" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


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
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	
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
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\FileUtils\FileParser.h"\
	
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
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\GroupFactory.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	
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
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	
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
DEP_CPP_DIAGRAMM=\
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEditor.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramMenu.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\UndoItem.h"\
	
NODEP_CPP_DIAGRAMM=\
	".\DiagramEditor\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\DiagramMenu.obj" : $(SOURCE) $(DEP_CPP_DIAGRAMM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


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
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	
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
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\GroupFactory.h"\
	".\DiagramEditor\UndoItem.h"\
	
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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMO=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMO=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoBlockView.obj" : $(SOURCE) $(DEP_CPP_PROMO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMO=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\GeometryUtils\GeometryHelper.h"\
	".\GeometryUtils\IntersectionHelper.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMO=\
	".\ProMoEditor\stdafx.h"\
	

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
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
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
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
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
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOE=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOE=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeModel.obj" : $(SOURCE) $(DEP_CPP_PROMOE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOE=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\FileUtils\FileParser.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOE=\
	".\ProMoEditor\stdafx.h"\
	

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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOED=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOED=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeView.obj" : $(SOURCE) $(DEP_CPP_PROMOED) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOED=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\FileUtils\FileParser.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOED=\
	".\ProMoEditor\stdafx.h"\
	

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
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOEN=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\Automation\ProMoElementsAuto.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEN=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoEntityContainer.obj" : $(SOURCE) $(DEP_CPP_PROMOEN) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOEN=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\Automation\ProMoElementsAuto.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEN=\
	".\ProMoEditor\stdafx.h"\
	

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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOM=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOM=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoModel.obj" : $(SOURCE) $(DEP_CPP_PROMOM) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOM=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOM=\
	".\ProMoEditor\stdafx.h"\
	

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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOB=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOB=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoBlockModel.obj" : $(SOURCE) $(DEP_CPP_PROMOB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOB=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
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
	".\FileUtils\FileParser.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOB=\
	".\ProMoEditor\stdafx.h"\
	

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
	".\GeometryUtils\DoublePoint.h"\
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
	".\Automation\..\stdafx.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\GeometryUtils\GeometryHelper.h"\
	
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
	".\Automation\..\stdafx.h"\
	".\FileUtils\VariantWrapper.h"\
	
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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOP=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOP=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoProperty.obj" : $(SOURCE) $(DEP_CPP_PROMOP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOP=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
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
	".\FileUtils\FileParser.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOP=\
	".\ProMoEditor\stdafx.h"\
	

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

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOL=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOL=\
	".\ProMoEditor\stdafx.h"\
	

"$(INTDIR)\ProMoLabel.obj" : $(SOURCE) $(DEP_CPP_PROMOL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOL=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
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
	".\FileUtils\FileParser.h"\
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
	".\ProMoEditor\ProMoNameFactory.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOL=\
	".\ProMoEditor\stdafx.h"\
	

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
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
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
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoElementsAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOEL=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\Automation\ProMoElementsAuto.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEL=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoElementsAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOEL=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\Automation\ProMoElementsAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEL=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoElementsAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoElementsAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOEL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoAppChildAuto.cpp
DEP_CPP_PROMOA=\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	
NODEP_CPP_PROMOA=\
	".\Automation\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoAppChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoAppChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoAppChildAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoDiagramAutoAbs.cpp
DEP_CPP_PROMOD=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelsAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOD=\
	".\Automation\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoDiagramAutoAbs.obj" : $(SOURCE) $(DEP_CPP_PROMOD) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoDiagramAutoAbs.obj" : $(SOURCE) $(DEP_CPP_PROMOD) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoDiagramAutoAbs.sbr" : $(SOURCE) $(DEP_CPP_PROMOD) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoDiagramChildAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMODI=\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	
NODEP_CPP_PROMODI=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoDiagramChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMODI)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMODI=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\FileUtils\DibHelper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMODI=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoDiagramChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMODI)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoDiagramChildAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMODI)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoDiagramsAutoAbs.cpp
DEP_CPP_PROMODIA=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramsAutoAbs.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\FileUtils\DibHelper.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMODIA=\
	".\Automation\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoDiagramsAutoAbs.obj" : $(SOURCE) $(DEP_CPP_PROMODIA)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoDiagramsAutoAbs.obj" : $(SOURCE) $(DEP_CPP_PROMODIA)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoDiagramsAutoAbs.sbr" : $(SOURCE) $(DEP_CPP_PROMODIA)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoElementAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOELE=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelsAuto.h"\
	".\automation\ProMoPropertiesAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOELE=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoElementAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOELE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOELE=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelsAuto.h"\
	".\automation\ProMoPropertiesAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOELE=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoElementAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOELE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoElementAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOELE) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoAppAutoAbs.cpp
DEP_CPP_PROMOAP=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramsAutoAbs.h"\
	".\DiagramEditor\DiagramClipboardHandler.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramEntityContainer.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\Tokenizer.h"\
	".\DiagramEditor\UndoItem.h"\
	".\FileUtils\DibHelper.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOAP=\
	".\Automation\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\ProMoAppAutoAbs.obj" : $(SOURCE) $(DEP_CPP_PROMOAP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoAppAutoAbs.obj" : $(SOURCE) $(DEP_CPP_PROMOAP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoAppAutoAbs.sbr" : $(SOURCE) $(DEP_CPP_PROMOAP) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FileUtils\SafeArrayWrapper.cpp
DEP_CPP_SAFEA=\
	".\Automation\..\stdafx.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	
NODEP_CPP_SAFEA=\
	".\FileUtils\stdafx.h"\
	

!IF  "$(CFG)" == "WinProMo - Win32 Release"


"$(INTDIR)\SafeArrayWrapper.obj" : $(SOURCE) $(DEP_CPP_SAFEA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\SafeArrayWrapper.obj" : $(SOURCE) $(DEP_CPP_SAFEA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\SafeArrayWrapper.sbr" : $(SOURCE) $(DEP_CPP_SAFEA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoBlockAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOBL=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\automation\ProMoBoundaryBlocksAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoIncomingEdgesAuto.h"\
	".\Automation\ProMoOutgoingEdgesAuto.h"\
	".\automation\ProMoSubBlocksAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\GeometryUtils\GeometryHelper.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOBL=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoBlockAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOBL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOBL=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\automation\ProMoBoundaryBlocksAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoIncomingEdgesAuto.h"\
	".\Automation\ProMoOutgoingEdgesAuto.h"\
	".\automation\ProMoSubBlocksAuto.h"\
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
	".\GeometryUtils\GeometryHelper.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOBL=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoBlockAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOBL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoBlockAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOBL) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoEdgeAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOEDG=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentsAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDG=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDG) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOEDG=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentsAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDG=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEdgeAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDG) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEdgeAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOEDG) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoIncomingEdgesAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOI=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoIncomingEdgesAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOI=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoIncomingEdgesAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOI)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOI=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoIncomingEdgesAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
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
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOI=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoIncomingEdgesAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOI)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoIncomingEdgesAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOI)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoSubBlocksAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOS=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoSubBlocksAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOS=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoSubBlocksAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOS) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOS=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoSubBlocksAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOS=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoSubBlocksAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOS) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoSubBlocksAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOS) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoBoundaryBlocksAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOBO=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\automation\ProMoBoundaryBlocksAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOBO=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoBoundaryBlocksAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOBO)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOBO=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockAuto.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\automation\ProMoBoundaryBlocksAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOBO=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoBoundaryBlocksAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOBO)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoBoundaryBlocksAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOBO)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoLabelsAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOLA=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
	".\automation\ProMoLabelsAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOLA=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoLabelsAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOLA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOLA=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
	".\automation\ProMoLabelsAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOLA=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoLabelsAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOLA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoLabelsAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOLA) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoPropertiesAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOPR=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoPropertiesAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOPR=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoPropertiesAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOPR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOPR=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoPropertiesAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOPR=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoPropertiesAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOPR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoPropertiesAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOPR) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoPropertyAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOPRO=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOPRO=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoPropertyAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOPRO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOPRO=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoControlFactory.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOPRO=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoPropertyAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOPRO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoPropertyAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOPRO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoLabelAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOLAB=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOLAB=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoLabelAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOLAB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOLAB=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\automation\ProMoLabelAuto.h"\
	".\automation\ProMoPropertyAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOLAB=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoLabelAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOLAB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoLabelAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOLAB) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoEdgeSegmentsAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOEDGE=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentAuto.h"\
	".\Automation\ProMoEdgeSegmentsAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDGE=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeSegmentsAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDGE)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOEDGE=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentAuto.h"\
	".\Automation\ProMoEdgeSegmentsAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDGE=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEdgeSegmentsAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDGE)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEdgeSegmentsAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOEDGE)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoEdgeSegmentAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOEDGES=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDGES=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeSegmentAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDGES)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOEDGES=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoEdgeSegmentAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDGES=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEdgeSegmentAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDGES)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEdgeSegmentAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOEDGES)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoElementChildAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOELEM=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOELEM=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoElementChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOELEM)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOELEM=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOELEM=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoElementChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOELEM)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoElementChildAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOELEM)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoEdgeChildAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOEDGEC=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDGEC=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoEdgeChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDGEC)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOEDGEC=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOEDGEC=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoEdgeChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOEDGEC)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoEdgeChildAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOEDGEC)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoBlockChildAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOBLO=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOBLO=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoBlockChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOBLO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOBLO=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
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
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOBLO=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoBlockChildAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOBLO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoBlockChildAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOBLO) "$(INTDIR)"\
 "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Automation\ProMoOutgoingEdgesAuto.cpp

!IF  "$(CFG)" == "WinProMo - Win32 Release"

DEP_CPP_PROMOO=\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\Automation\ProMoOutgoingEdgesAuto.h"\
	".\DiagramEditor\DiagramEntity.h"\
	".\DiagramEditor\DiagramLine.h"\
	".\DiagramEditor\DiagramPropertyDlg.h"\
	".\DiagramEditor\HitParams.h"\
	".\DiagramEditor\HitParamsRect.h"\
	".\FileUtils\SafeArrayWrapper.h"\
	".\FileUtils\VariantWrapper.h"\
	".\GeometryUtils\DoublePoint.h"\
	".\GeometryUtils\DoubleRect.h"\
	".\ProMoEditor\ProMoBlockModel.h"\
	".\ProMoEditor\ProMoBlockView.h"\
	".\ProMoEditor\ProMoEdgeModel.h"\
	".\ProMoEditor\ProMoEdgeView.h"\
	".\ProMoEditor\ProMoEntity.h"\
	".\ProMoEditor\ProMoLabel.h"\
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOO=\
	".\Automation\stdafx.h"\
	

"$(INTDIR)\ProMoOutgoingEdgesAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOO)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

DEP_CPP_PROMOO=\
	".\Automation\..\ProMoEditor\ProMoEntityContainer.h"\
	".\Automation\..\ProMoEditor\ProMoModel.h"\
	".\Automation\..\stdafx.h"\
	".\Automation\ProMoAppAutoAbs.h"\
	".\Automation\ProMoAppChildAuto.h"\
	".\Automation\ProMoAutomationHost.h"\
	".\automation\ProMoBlockChildAuto.h"\
	".\Automation\ProMoDiagramAutoAbs.h"\
	".\Automation\ProMoDiagramChildAuto.h"\
	".\automation\ProMoEdgeAuto.h"\
	".\Automation\ProMoElementAuto.h"\
	".\automation\ProMoElementChildAuto.h"\
	".\Automation\ProMoOutgoingEdgesAuto.h"\
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
	".\FileUtils\SafeArrayWrapper.h"\
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
	".\ProMoEditor\ProMoProperty.h"\
	".\ProMoEditor\ProMoPropertyOwner.h"\
	".\ProMoEditor\ProMoRenderer.h"\
	".\ProMoEditor\ProMoView.h"\
	
NODEP_CPP_PROMOO=\
	".\Automation\stdafx.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\ProMoOutgoingEdgesAuto.obj" : $(SOURCE) $(DEP_CPP_PROMOO)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

"$(INTDIR)\ProMoOutgoingEdgesAuto.sbr" : $(SOURCE) $(DEP_CPP_PROMOO)\
 "$(INTDIR)" "$(INTDIR)\WinProMo.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinProMo.odl

!IF  "$(CFG)" == "WinProMo - Win32 Release"

# ADD MTL /tlb "../../Release/WinProMo.tlb"

"..\..\Release\WinProMo.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "NDEBUG" /tlb "../../Release/WinProMo.tlb" /win32\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "WinProMo - Win32 Debug"

# ADD MTL /tlb "../../Debug/WinProMo.tlb"

"..\..\Debug\WinProMo.tlb" : $(SOURCE) "$(OUTDIR)"
   $(MTL) /nologo /D "_DEBUG" /tlb "../../Debug/WinProMo.tlb" /win32 $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
