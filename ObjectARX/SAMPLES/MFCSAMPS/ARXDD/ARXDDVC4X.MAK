# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=arxdragdrop - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to arxdragdrop - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "arxdragdrop - Win32 Release" && "$(CFG)" !=\
 "arxdragdrop - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "arxddvc4x.mak" CFG="arxdragdrop - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "arxdragdrop - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "arxdragdrop - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "arxdragdrop - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"

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

ALL : ".\arxdragdrop.arx" "$(OUTDIR)\arxddvc4x.pch"

CLEAN : 
	-@erase "$(INTDIR)\arxddvc4x.pch"
	-@erase "$(INTDIR)\arxdragdrop.obj"
	-@erase "$(INTDIR)\arxdraw.res"
	-@erase "$(INTDIR)\arxdrawView.obj"
	-@erase "$(INTDIR)\ArxSliderVw.obj"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dropsource.obj"
	-@erase "$(INTDIR)\droptarget.obj"
	-@erase "$(INTDIR)\IENUMFE.OBJ"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\rxtemplt.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\arxdragdrop.exp"
	-@erase "$(OUTDIR)\arxdragdrop.lib"
	-@erase ".\arxdragdrop.arx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /YX"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/arxddvc4x.pch"\
 /YX"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/arxdraw.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/arxddvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:".\arxdragdrop.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/arxdragdrop.pdb" /machine:I386 /def:".\arxdragdrop.def"\
 /out:".\arxdragdrop.arx" /implib:"$(OUTDIR)/arxdragdrop.lib" 
DEF_FILE= \
	".\arxdragdrop.def"
LINK32_OBJS= \
	"$(INTDIR)\arxdragdrop.obj" \
	"$(INTDIR)\arxdraw.res" \
	"$(INTDIR)\arxdrawView.obj" \
	"$(INTDIR)\ArxSliderVw.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\dropsource.obj" \
	"$(INTDIR)\droptarget.obj" \
	"$(INTDIR)\IENUMFE.OBJ" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\rxtemplt.obj" \
	"$(INTDIR)\StdAfx.obj"

".\arxdragdrop.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"

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

ALL : ".\arxdragdrop.arx" "$(OUTDIR)\arxddvc4x.bsc" "$(OUTDIR)\arxddvc4x.pch"

CLEAN : 
	-@erase "$(INTDIR)\arxddvc4x.pch"
	-@erase "$(INTDIR)\arxdragdrop.obj"
	-@erase "$(INTDIR)\arxdragdrop.sbr"
	-@erase "$(INTDIR)\arxdraw.res"
	-@erase "$(INTDIR)\arxdrawView.obj"
	-@erase "$(INTDIR)\arxdrawView.sbr"
	-@erase "$(INTDIR)\ArxSliderVw.obj"
	-@erase "$(INTDIR)\ArxSliderVw.sbr"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dataobj.sbr"
	-@erase "$(INTDIR)\dropsource.obj"
	-@erase "$(INTDIR)\dropsource.sbr"
	-@erase "$(INTDIR)\droptarget.obj"
	-@erase "$(INTDIR)\droptarget.sbr"
	-@erase "$(INTDIR)\IENUMFE.OBJ"
	-@erase "$(INTDIR)\IENUMFE.SBR"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\rxtemplt.obj"
	-@erase "$(INTDIR)\rxtemplt.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\arxddvc4x.bsc"
	-@erase "$(OUTDIR)\arxdragdrop.exp"
	-@erase "$(OUTDIR)\arxdragdrop.lib"
	-@erase "$(OUTDIR)\arxdragdrop.pdb"
	-@erase ".\arxdragdrop.arx"
	-@erase ".\arxdragdrop.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /FR /YX"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/arxddvc4x.pch" /YX"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/arxdraw.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/arxddvc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\arxdragdrop.sbr" \
	"$(INTDIR)\arxdrawView.sbr" \
	"$(INTDIR)\ArxSliderVw.sbr" \
	"$(INTDIR)\dataobj.sbr" \
	"$(INTDIR)\dropsource.sbr" \
	"$(INTDIR)\droptarget.sbr" \
	"$(INTDIR)\IENUMFE.SBR" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\rxtemplt.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\arxddvc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:".\arxdragdrop.arx"
# SUBTRACT LINK32 /pdb:none /force
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/arxdragdrop.pdb" /debug /machine:I386 /def:".\arxdragdrop.def"\
 /out:".\arxdragdrop.arx" /implib:"$(OUTDIR)/arxdragdrop.lib" 
DEF_FILE= \
	".\arxdragdrop.def"
LINK32_OBJS= \
	"$(INTDIR)\arxdragdrop.obj" \
	"$(INTDIR)\arxdraw.res" \
	"$(INTDIR)\arxdrawView.obj" \
	"$(INTDIR)\ArxSliderVw.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\dropsource.obj" \
	"$(INTDIR)\droptarget.obj" \
	"$(INTDIR)\IENUMFE.OBJ" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\rxtemplt.obj" \
	"$(INTDIR)\StdAfx.obj"

".\arxdragdrop.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "arxdragdrop - Win32 Release"
# Name "arxdragdrop - Win32 Debug"

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"

!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\arxdragdrop.cpp
DEP_CPP_ARXDR=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\arxdragdrop.obj" : $(SOURCE) $(DEP_CPP_ARXDR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\arxdragdrop.obj" : $(SOURCE) $(DEP_CPP_ARXDR) "$(INTDIR)"

"$(INTDIR)\arxdragdrop.sbr" : $(SOURCE) $(DEP_CPP_ARXDR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\..\..\inc\rxmfcapi.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)/arxddvc4x.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\arxddvc4x.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/arxddvc4x.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\arxddvc4x.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IENUMFE.CPP
DEP_CPP_IENUM=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\IENUMFE.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\IENUMFE.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"

"$(INTDIR)\IENUMFE.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\droptarget.cpp
DEP_CPP_DROPT=\
	"..\..\..\inc\acdb.h"\
	"..\..\..\inc\adesk.h"\
	"..\..\..\inc\ads.h"\
	"..\..\..\inc\adscodes.h"\
	"..\..\..\inc\adsdef.h"\
	"..\..\..\inc\adslib.h"\
	"..\..\..\inc\comsys.h"\
	"..\..\..\inc\dbaudita.h"\
	"..\..\..\inc\dbboiler.h"\
	"..\..\..\inc\dbcurve.h"\
	"..\..\..\inc\dbdate.h"\
	"..\..\..\inc\dbdict.h"\
	"..\..\..\inc\dbents.h"\
	"..\..\..\inc\dbfiler.h"\
	"..\..\..\inc\dbhandle.h"\
	"..\..\..\inc\dbid.h"\
	"..\..\..\inc\dbid_ops.h"\
	"..\..\..\inc\dbidapps.h"\
	"..\..\..\inc\dbidar.h"\
	"..\..\..\inc\dbintar.h"\
	"..\..\..\inc\dbmain.h"\
	"..\..\..\inc\dbmtext.h"\
	"..\..\..\inc\dbptrar.h"\
	"..\..\..\inc\dbsubeid.h"\
	"..\..\..\inc\dbsymtb.h"\
	"..\..\..\inc\gecurv3d.h"\
	"..\..\..\inc\gedblar.h"\
	"..\..\..\inc\gedll.h"\
	"..\..\..\inc\geent2d.h"\
	"..\..\..\inc\geent3d.h"\
	"..\..\..\inc\gegbl.h"\
	"..\..\..\inc\geintrvl.h"\
	"..\..\..\inc\gelent3d.h"\
	"..\..\..\inc\gelibver.h"\
	"..\..\..\inc\geline3d.h"\
	"..\..\..\inc\gepent3d.h"\
	"..\..\..\inc\geplanar.h"\
	"..\..\..\inc\geplane.h"\
	"..\..\..\inc\gepnt2d.h"\
	"..\..\..\inc\gepnt3d.h"\
	"..\..\..\inc\geponc3d.h"\
	"..\..\..\inc\gept3dar.h"\
	"..\..\..\inc\gescl3d.h"\
	"..\..\..\inc\gesurf.h"\
	"..\..\..\inc\getol.h"\
	"..\..\..\inc\gevec2d.h"\
	"..\..\..\inc\gevec3d.h"\
	"..\..\..\inc\rxboiler.h"\
	"..\..\..\inc\rxclass.h"\
	"..\..\..\inc\rxcom.h"\
	"..\..\..\inc\rxdefs.h"\
	"..\..\..\inc\rxdict.h"\
	"..\..\..\inc\rxditer.h"\
	"..\..\..\inc\rxdlinkr.h"\
	"..\..\..\inc\rxiter.h"\
	"..\..\..\inc\rxmfcapi.h"\
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxregsvc.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DROPT=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\droptarget.obj" : $(SOURCE) $(DEP_CPP_DROPT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\droptarget.obj" : $(SOURCE) $(DEP_CPP_DROPT) "$(INTDIR)"

"$(INTDIR)\droptarget.sbr" : $(SOURCE) $(DEP_CPP_DROPT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dropsource.cpp
DEP_CPP_DROPS=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\dropsource.obj" : $(SOURCE) $(DEP_CPP_DROPS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\dropsource.obj" : $(SOURCE) $(DEP_CPP_DROPS) "$(INTDIR)"

"$(INTDIR)\dropsource.sbr" : $(SOURCE) $(DEP_CPP_DROPS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dataobj.cpp
DEP_CPP_DATAO=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"

"$(INTDIR)\dataobj.sbr" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\arxdrawView.cpp
DEP_CPP_ARXDRA=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\arxdrawView.obj" : $(SOURCE) $(DEP_CPP_ARXDRA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\arxdrawView.obj" : $(SOURCE) $(DEP_CPP_ARXDRA) "$(INTDIR)"

"$(INTDIR)\arxdrawView.sbr" : $(SOURCE) $(DEP_CPP_ARXDRA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rxtemplt.cpp
DEP_CPP_RXTEM=\
	"..\..\..\inc\accmd.h"\
	"..\..\..\inc\acdb.h"\
	"..\..\..\inc\aced.h"\
	"..\..\..\inc\adesk.h"\
	"..\..\..\inc\ads.h"\
	"..\..\..\inc\adscodes.h"\
	"..\..\..\inc\adsdef.h"\
	"..\..\..\inc\adslib.h"\
	"..\..\..\inc\comsys.h"\
	"..\..\..\inc\dbaudita.h"\
	"..\..\..\inc\dbboiler.h"\
	"..\..\..\inc\dbfiler.h"\
	"..\..\..\inc\dbhandle.h"\
	"..\..\..\inc\dbid.h"\
	"..\..\..\inc\dbid_ops.h"\
	"..\..\..\inc\dbidapps.h"\
	"..\..\..\inc\dbidar.h"\
	"..\..\..\inc\dbintar.h"\
	"..\..\..\inc\dbjig.h"\
	"..\..\..\inc\dbmain.h"\
	"..\..\..\inc\dbptrar.h"\
	"..\..\..\inc\dbsubeid.h"\
	"..\..\..\inc\gecurv3d.h"\
	"..\..\..\inc\gedblar.h"\
	"..\..\..\inc\gedll.h"\
	"..\..\..\inc\geent2d.h"\
	"..\..\..\inc\geent3d.h"\
	"..\..\..\inc\gegbl.h"\
	"..\..\..\inc\geintrvl.h"\
	"..\..\..\inc\gelent3d.h"\
	"..\..\..\inc\gelibver.h"\
	"..\..\..\inc\geline3d.h"\
	"..\..\..\inc\gepent3d.h"\
	"..\..\..\inc\gepnt2d.h"\
	"..\..\..\inc\gepnt3d.h"\
	"..\..\..\inc\geponc3d.h"\
	"..\..\..\inc\gept3dar.h"\
	"..\..\..\inc\gescl3d.h"\
	"..\..\..\inc\getol.h"\
	"..\..\..\inc\gevec2d.h"\
	"..\..\..\inc\gevec3d.h"\
	"..\..\..\inc\rxboiler.h"\
	"..\..\..\inc\rxclass.h"\
	"..\..\..\inc\rxcom.h"\
	"..\..\..\inc\rxdefs.h"\
	"..\..\..\inc\rxdict.h"\
	"..\..\..\inc\rxditer.h"\
	"..\..\..\inc\rxdlinkr.h"\
	"..\..\..\inc\rxiter.h"\
	"..\..\..\inc\rxmfcapi.h"\
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	
NODEP_CPP_RXTEM=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\rxtemplt.obj" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\rxtemplt.obj" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"

"$(INTDIR)\rxtemplt.sbr" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\arxdraw.rc
DEP_RSC_ARXDRAW=\
	".\res\arxdraw.ico"\
	".\res\arxdraw.rc2"\
	".\res\arxdrawDoc.ico"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\arxdraw.res" : $(SOURCE) $(DEP_RSC_ARXDRAW) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ArxSliderVw.cpp
DEP_CPP_ARXSL=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawview.h"\
	".\ArxSliderVw.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\Droptarget.h"\
	".\IENUMFE.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"


"$(INTDIR)\ArxSliderVw.obj" : $(SOURCE) $(DEP_CPP_ARXSL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"


"$(INTDIR)\ArxSliderVw.obj" : $(SOURCE) $(DEP_CPP_ARXSL) "$(INTDIR)"

"$(INTDIR)\ArxSliderVw.sbr" : $(SOURCE) $(DEP_CPP_ARXSL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\arxdragdrop.def

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"

!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
