# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=arxmdi - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to arxmdi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "arxmdi - Win32 Release" && "$(CFG)" != "arxmdi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "arxmdivc4x.mak" CFG="arxmdi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "arxmdi - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "arxmdi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "arxmdi - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "arxmdi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\arxmdi.arx"

CLEAN : 
	-@erase "$(INTDIR)\bounce.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\mdi.obj"
	-@erase "$(INTDIR)\mdi.res"
	-@erase "$(INTDIR)\rxtemplt.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(OUTDIR)\arxmdi.exp"
	-@erase "$(OUTDIR)\arxmdi.lib"
	-@erase ".\arxmdi.arx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/arxmdivc4x.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/mdi.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/arxmdivc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /nodefaultlib:"MSVCRTD.LIB" /out:".\arxmdi.arx"
# SUBTRACT LINK32 /incremental:yes
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/arxmdi.pdb"\
 /machine:I386 /nodefaultlib:"MSVCRTD.LIB" /def:".\rxtemplt.def"\
 /out:".\arxmdi.arx" /implib:"$(OUTDIR)/arxmdi.lib" 
DEF_FILE= \
	".\rxtemplt.def"
LINK32_OBJS= \
	"$(INTDIR)\bounce.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\mdi.obj" \
	"$(INTDIR)\mdi.res" \
	"$(INTDIR)\rxtemplt.obj" \
	"$(INTDIR)\stdafx.obj"

".\arxmdi.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "arxmdi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\arxmdi.arx"

CLEAN : 
	-@erase "$(INTDIR)\bounce.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\mdi.obj"
	-@erase "$(INTDIR)\mdi.res"
	-@erase "$(INTDIR)\rxtemplt.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\arxmdi.exp"
	-@erase "$(OUTDIR)\arxmdi.lib"
	-@erase "$(OUTDIR)\arxmdi.pdb"
	-@erase ".\arxmdi.arx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/arxmdivc4x.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/mdi.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/arxmdivc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:no /debug /machine:I386 /nodefaultlib:"LIBC" /out:".\arxmdi.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/arxmdi.pdb" /debug\
 /machine:I386 /nodefaultlib:"LIBC" /def:".\rxtemplt.def" /out:".\arxmdi.arx"\
 /implib:"$(OUTDIR)/arxmdi.lib" 
DEF_FILE= \
	".\rxtemplt.def"
LINK32_OBJS= \
	"$(INTDIR)\bounce.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\mdi.obj" \
	"$(INTDIR)\mdi.res" \
	"$(INTDIR)\rxtemplt.obj" \
	"$(INTDIR)\stdafx.obj"

".\arxmdi.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "arxmdi - Win32 Release"
# Name "arxmdi - Win32 Debug"

!IF  "$(CFG)" == "arxmdi - Win32 Release"

!ELSEIF  "$(CFG)" == "arxmdi - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\bounce.h"\
	".\mainfrm.h"\
	".\mdi.h"\
	".\stdafx.h"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


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
	".\bounce.h"\
	".\mainfrm.h"\
	".\mdi.h"\
	".\stdafx.h"\
	
NODEP_CPP_RXTEM=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

"$(INTDIR)\rxtemplt.obj" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mdi.rc
DEP_RSC_MDI_R=\
	".\MDI.ICO"\
	

"$(INTDIR)\mdi.res" : $(SOURCE) $(DEP_RSC_MDI_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mdi.cpp
DEP_CPP_MDI_C=\
	".\bounce.h"\
	".\mainfrm.h"\
	".\mdi.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mdi.obj" : $(SOURCE) $(DEP_CPP_MDI_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\bounce.h"\
	".\mainfrm.h"\
	".\mdi.h"\
	".\stdafx.h"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bounce.cpp
DEP_CPP_BOUNC=\
	".\bounce.h"\
	".\mainfrm.h"\
	".\mdi.h"\
	".\stdafx.h"\
	

"$(INTDIR)\bounce.obj" : $(SOURCE) $(DEP_CPP_BOUNC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\rxtemplt.def

!IF  "$(CFG)" == "arxmdi - Win32 Release"

!ELSEIF  "$(CFG)" == "arxmdi - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
