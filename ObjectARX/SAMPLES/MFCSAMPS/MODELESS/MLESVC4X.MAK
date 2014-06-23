# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=modeless - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to modeless - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "modeless - Win32 Release" && "$(CFG)" !=\
 "modeless - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "mlesvc4x.mak" CFG="modeless - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modeless - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "modeless - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "modeless - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modeless - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : ".\modeless.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\modeless.obj"
	-@erase "$(INTDIR)\modeless.res"
	-@erase "$(OUTDIR)\modeless.exp"
	-@erase "$(OUTDIR)\modeless.lib"
	-@erase "$(OUTDIR)\modeless.pdb"
	-@erase ".\modeless.arx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /Od /I "..\..\..\inc" /D "NDEBUG" /D "ACRXAPP" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /Od /I "..\..\..\inc" /D "NDEBUG" /D "ACRXAPP" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/mlesvc4x.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/modeless.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mlesvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /force /out:".\modeless.arx"
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/modeless.pdb" /debug\
 /machine:I386 /def:".\modeless.def" /force /out:".\modeless.arx"\
 /implib:"$(OUTDIR)/modeless.lib" 
DEF_FILE= \
	".\modeless.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\modeless.obj" \
	"$(INTDIR)\modeless.res"

".\modeless.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "modeless - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : ".\modeless.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\modeless.obj"
	-@erase "$(INTDIR)\modeless.res"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\modeless.exp"
	-@erase "$(OUTDIR)\modeless.lib"
	-@erase "$(OUTDIR)\modeless.pdb"
	-@erase ".\modeless.arx"
	-@erase ".\modeless.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/mlesvc4x.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/modeless.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/mlesvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:".\modeless.arx"
# SUBTRACT LINK32 /force
LINK32_FLAGS=..\..\..\lib\acad.lib ..\..\..\lib\rxapi.lib\
 ..\..\..\lib\acedapi.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/modeless.pdb" /debug\
 /machine:I386 /def:".\modeless.def" /out:".\modeless.arx"\
 /implib:"$(OUTDIR)/modeless.lib" 
DEF_FILE= \
	".\modeless.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\modeless.obj" \
	"$(INTDIR)\modeless.res"

".\modeless.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "modeless - Win32 Release"
# Name "modeless - Win32 Debug"

!IF  "$(CFG)" == "modeless - Win32 Release"

!ELSEIF  "$(CFG)" == "modeless - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\modeless.rc

"$(INTDIR)\modeless.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\modeless.cpp
DEP_CPP_MODEL=\
	"..\..\..\inc\accmd.h"\
	"..\..\..\inc\acdb.h"\
	"..\..\..\inc\aced.h"\
	"..\..\..\inc\adesk.h"\
	"..\..\..\inc\adeskabb.h"\
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
	".\chello.h"\
	".\dbmr.h"\
	".\modeless.h"\
	".\resourcehelper.h"\
	".\stdafx.h"\
	
NODEP_CPP_MODEL=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

"$(INTDIR)\modeless.obj" : $(SOURCE) $(DEP_CPP_MODEL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\modeless.def

!IF  "$(CFG)" == "modeless - Win32 Release"

!ELSEIF  "$(CFG)" == "modeless - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\arxmfctmpl.cpp
DEP_CPP_ARXMF=\
	"..\..\..\inc\accmd.h"\
	"..\..\..\inc\acdb.h"\
	"..\..\..\inc\aced.h"\
	"..\..\..\inc\adesk.h"\
	"..\..\..\inc\ads.h"\
	"..\..\..\inc\adsdef.h"\
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
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\resourcehelper.h"\
	".\stdafx.h"\
	
NODEP_CPP_ARXMF=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

"$(INTDIR)\arxmfctmpl.obj" : $(SOURCE) $(DEP_CPP_ARXMF) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
