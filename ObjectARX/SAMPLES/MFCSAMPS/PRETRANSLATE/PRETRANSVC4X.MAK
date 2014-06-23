# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=pretranslate - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to pretranslate - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "pretranslate - Win32 Release" && "$(CFG)" !=\
 "pretranslate - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "pretransvc4x.mak" CFG="pretranslate - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pretranslate - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pretranslate - Win32 Debug" (based on\
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
# PROP Target_Last_Scanned "pretranslate - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pretranslate - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\pretranslate.arx"

CLEAN : 
	-@erase "$(INTDIR)\rxtemplt.obj"
	-@erase "$(OUTDIR)\pretranslate.exp"
	-@erase "$(OUTDIR)\pretranslate.lib"
	-@erase ".\pretranslate.arx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)/pretransvc4x.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pretransvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /nodefaultlib:"MSVCRTD" /out:".\pretranslate.arx"
# SUBTRACT LINK32 /force
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/pretranslate.pdb"\
 /machine:I386 /nodefaultlib:"MSVCRTD" /def:".\rxtemplt.def"\
 /out:".\pretranslate.arx" /implib:"$(OUTDIR)/pretranslate.lib" 
DEF_FILE= \
	".\rxtemplt.def"
LINK32_OBJS= \
	"$(INTDIR)\rxtemplt.obj"

".\pretranslate.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pretranslate - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\pretranslate.arx" "$(OUTDIR)\pretransvc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\rxtemplt.obj"
	-@erase "$(INTDIR)\rxtemplt.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\pretranslate.exp"
	-@erase "$(OUTDIR)\pretranslate.lib"
	-@erase "$(OUTDIR)\pretranslate.pdb"
	-@erase "$(OUTDIR)\pretransvc4x.bsc"
	-@erase ".\pretranslate.arx"
	-@erase ".\pretranslate.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/pretransvc4x.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/pretransvc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\rxtemplt.sbr"

"$(OUTDIR)\pretransvc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"MSVCRTD" /out:".\pretranslate.arx"
# SUBTRACT LINK32 /pdb:none /force
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/pretranslate.pdb"\
 /debug /machine:I386 /nodefaultlib:"MSVCRTD" /def:".\rxtemplt.def"\
 /out:".\pretranslate.arx" /implib:"$(OUTDIR)/pretranslate.lib" 
DEF_FILE= \
	".\rxtemplt.def"
LINK32_OBJS= \
	"$(INTDIR)\rxtemplt.obj"

".\pretranslate.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "pretranslate - Win32 Release"
# Name "pretranslate - Win32 Debug"

!IF  "$(CFG)" == "pretranslate - Win32 Release"

!ELSEIF  "$(CFG)" == "pretranslate - Win32 Debug"

!ENDIF 

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
	
NODEP_CPP_RXTEM=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "pretranslate - Win32 Release"


"$(INTDIR)\rxtemplt.obj" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "pretranslate - Win32 Debug"


"$(INTDIR)\rxtemplt.obj" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"

"$(INTDIR)\rxtemplt.sbr" : $(SOURCE) $(DEP_CPP_RXTEM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rxtemplt.def

!IF  "$(CFG)" == "pretranslate - Win32 Release"

!ELSEIF  "$(CFG)" == "pretranslate - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
