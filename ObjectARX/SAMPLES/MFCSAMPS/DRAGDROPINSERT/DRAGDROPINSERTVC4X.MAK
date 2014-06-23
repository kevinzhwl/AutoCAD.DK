# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=dndInsert - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to dndInsert - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "dndInsert - Win32 Release" && "$(CFG)" !=\
 "dndInsert - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "dragdropinsertvc4x.mak" CFG="dndInsert - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dndInsert - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dndInsert - Win32 Debug" (based on\
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
# PROP Target_Last_Scanned "dndInsert - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dndInsert - Win32 Release"

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

ALL : ".\dndInsert.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxdragdrop.obj"
	-@erase "$(INTDIR)\arxdraw.res"
	-@erase "$(INTDIR)\arxdrawView.obj"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dragdropinsertvc4x.pch"
	-@erase "$(INTDIR)\dropsource.obj"
	-@erase "$(INTDIR)\droptarget.obj"
	-@erase "$(INTDIR)\IENUMFE.OBJ"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\rxtemplt.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\dndInsert.exp"
	-@erase "$(OUTDIR)\dndInsert.lib"
	-@erase ".\dndInsert.arx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL"\
 /Fp"$(INTDIR)/dragdropinsertvc4x.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
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
# SUBTRACT BSC32 /nologo
BSC32_FLAGS=/o"$(OUTDIR)/dragdropinsertvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /nodefaultlib:"LIBC" /force /out:".\dndInsert.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/dndInsert.pdb" /machine:I386 /nodefaultlib:"LIBC"\
 /def:".\arxdragdrop.def" /force /out:".\dndInsert.arx"\
 /implib:"$(OUTDIR)/dndInsert.lib" 
DEF_FILE= \
	".\arxdragdrop.def"
LINK32_OBJS= \
	"$(INTDIR)\arxdragdrop.obj" \
	"$(INTDIR)\arxdraw.res" \
	"$(INTDIR)\arxdrawView.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\dropsource.obj" \
	"$(INTDIR)\droptarget.obj" \
	"$(INTDIR)\IENUMFE.OBJ" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\rxtemplt.obj" \
	"$(INTDIR)\StdAfx.obj"

".\dndInsert.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"

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

ALL : ".\dndInsert.arx" "$(OUTDIR)\dragdropinsertvc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\arxdragdrop.obj"
	-@erase "$(INTDIR)\arxdragdrop.sbr"
	-@erase "$(INTDIR)\arxdraw.res"
	-@erase "$(INTDIR)\arxdrawView.obj"
	-@erase "$(INTDIR)\arxdrawView.sbr"
	-@erase "$(INTDIR)\dataobj.obj"
	-@erase "$(INTDIR)\dataobj.sbr"
	-@erase "$(INTDIR)\dragdropinsertvc4x.pch"
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
	-@erase "$(OUTDIR)\dndInsert.exp"
	-@erase "$(OUTDIR)\dndInsert.lib"
	-@erase "$(OUTDIR)\dndInsert.pdb"
	-@erase "$(OUTDIR)\dragdropinsertvc4x.bsc"
	-@erase ".\dndInsert.arx"
	-@erase ".\dndInsert.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "s:\rx\rxmfc" /I "..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "s:\rx\rxmfc" /I "..\..\..\inc" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/dragdropinsertvc4x.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
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
# SUBTRACT BSC32 /nologo
BSC32_FLAGS=/o"$(OUTDIR)/dragdropinsertvc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\arxdragdrop.sbr" \
	"$(INTDIR)\arxdrawView.sbr" \
	"$(INTDIR)\dataobj.sbr" \
	"$(INTDIR)\dropsource.sbr" \
	"$(INTDIR)\droptarget.sbr" \
	"$(INTDIR)\IENUMFE.SBR" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\rxtemplt.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\dragdropinsertvc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"LIBC" /out:".\dndInsert.arx"
# SUBTRACT LINK32 /pdb:none /force
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib ..\..\..\lib\libacge.lib /nologo /base:0x1c000000\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/dndInsert.pdb" /debug /machine:I386 /nodefaultlib:"LIBC"\
 /def:".\arxdragdrop.def" /out:".\dndInsert.arx"\
 /implib:"$(OUTDIR)/dndInsert.lib" 
DEF_FILE= \
	".\arxdragdrop.def"
LINK32_OBJS= \
	"$(INTDIR)\arxdragdrop.obj" \
	"$(INTDIR)\arxdraw.res" \
	"$(INTDIR)\arxdrawView.obj" \
	"$(INTDIR)\dataobj.obj" \
	"$(INTDIR)\dropsource.obj" \
	"$(INTDIR)\droptarget.obj" \
	"$(INTDIR)\IENUMFE.OBJ" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\rxtemplt.obj" \
	"$(INTDIR)\StdAfx.obj"

".\dndInsert.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "dndInsert - Win32 Release"
# Name "dndInsert - Win32 Debug"

!IF  "$(CFG)" == "dndInsert - Win32 Release"

!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\arxdragdrop.cpp
DEP_CPP_ARXDR=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dndInsert - Win32 Release"


"$(INTDIR)\arxdragdrop.obj" : $(SOURCE) $(DEP_CPP_ARXDR) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"


"$(INTDIR)\arxdragdrop.obj" : $(SOURCE) $(DEP_CPP_ARXDR) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\arxdragdrop.sbr" : $(SOURCE) $(DEP_CPP_ARXDR) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	"..\..\..\inc\rxmfcapi.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dndInsert - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL"\
 /Fp"$(INTDIR)/dragdropinsertvc4x.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\dragdropinsertvc4x.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /Gm /GX /Zi /Od /I "s:\rx\rxmfc" /I "..\..\..\inc" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/dragdropinsertvc4x.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\dragdropinsertvc4x.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawView.h"\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dndInsert - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IENUMFE.CPP
DEP_CPP_IENUM=\
	"..\..\..\inc\rxmfcapi.h"\
	".\IENUMFE.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dndInsert - Win32 Release"


"$(INTDIR)\IENUMFE.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"


"$(INTDIR)\IENUMFE.OBJ" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\IENUMFE.SBR" : $(SOURCE) $(DEP_CPP_IENUM) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\droptarget.cpp

!IF  "$(CFG)" == "dndInsert - Win32 Release"

DEP_CPP_DROPT=\
	".\arxdrawView.h"\
	".\dataobj.h"\
	".\droptarget.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\droptarget.obj" : $(SOURCE) $(DEP_CPP_DROPT) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"

DEP_CPP_DROPT=\
	".\arxdrawView.h"\
	".\dataobj.h"\
	".\droptarget.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\droptarget.obj" : $(SOURCE) $(DEP_CPP_DROPT) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\droptarget.sbr" : $(SOURCE) $(DEP_CPP_DROPT) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dropsource.cpp
DEP_CPP_DROPS=\
	"..\..\..\inc\rxmfcapi.h"\
	".\dropsource.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dndInsert - Win32 Release"


"$(INTDIR)\dropsource.obj" : $(SOURCE) $(DEP_CPP_DROPS) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"


"$(INTDIR)\dropsource.obj" : $(SOURCE) $(DEP_CPP_DROPS) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\dropsource.sbr" : $(SOURCE) $(DEP_CPP_DROPS) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\dataobj.cpp
DEP_CPP_DATAO=\
	"..\..\..\inc\rxmfcapi.h"\
	".\dataobj.h"\
	".\IENUMFE.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dndInsert - Win32 Release"


"$(INTDIR)\dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"


"$(INTDIR)\dataobj.obj" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\dataobj.sbr" : $(SOURCE) $(DEP_CPP_DATAO) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\arxdrawView.cpp
DEP_CPP_ARXDRA=\
	"..\..\..\inc\rxmfcapi.h"\
	".\arxdragdrop.h"\
	".\arxdrawView.h"\
	".\dataobj.h"\
	".\dropsource.h"\
	".\droptarget.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "dndInsert - Win32 Release"


"$(INTDIR)\arxdrawView.obj" : $(SOURCE) $(DEP_CPP_ARXDRA) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"


"$(INTDIR)\arxdrawView.obj" : $(SOURCE) $(DEP_CPP_ARXDRA) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\arxdrawView.sbr" : $(SOURCE) $(DEP_CPP_ARXDRA) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rxtemplt.cpp

!IF  "$(CFG)" == "dndInsert - Win32 Release"

DEP_CPP_RXTEM=\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\rxtemplt.obj" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"

DEP_CPP_RXTEM=\
	".\MainFrm.h"\
	".\StdAfx.h"\
	

"$(INTDIR)\rxtemplt.obj" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"

"$(INTDIR)\rxtemplt.sbr" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"\
 "$(INTDIR)\dragdropinsertvc4x.pch"


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

SOURCE=.\arxdragdrop.def

!IF  "$(CFG)" == "dndInsert - Win32 Release"

!ELSEIF  "$(CFG)" == "dndInsert - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
