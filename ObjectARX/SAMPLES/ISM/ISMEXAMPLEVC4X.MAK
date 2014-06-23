# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=ism - Win32 Release
!MESSAGE No configuration specified.  Defaulting to ism - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "ism - Win32 Debug" && "$(CFG)" != "ism - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "IsmExamplevc4x.mak" CFG="ism - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ism - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ism - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "ism - Win32 Release"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ism - Win32 Debug"

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

ALL : ".\IsmExample.arx" "$(OUTDIR)\ismtest.bsc"

CLEAN : 
	-@erase "$(INTDIR)\access.obj"
	-@erase "$(INTDIR)\access.sbr"
	-@erase "$(INTDIR)\CustomApplication.obj"
	-@erase "$(INTDIR)\CustomApplication.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\IsmExample.exp"
	-@erase "$(OUTDIR)\IsmExample.lib"
	-@erase "$(OUTDIR)\IsmExample.pdb"
	-@erase "$(OUTDIR)\ismtest.bsc"
	-@erase ".\IsmExample.arx"
	-@erase ".\IsmExample.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/IsmExamplevc4x.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug/ismtest.bsc"
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ismtest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\access.sbr" \
	"$(INTDIR)\CustomApplication.sbr"

"$(OUTDIR)\ismtest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib ..\..\lib\libacge.lib ..\..\lib\rxapi.lib ..\..\lib\ism.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"msvcrtd.lib" /out:"IsmExample.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib\
 ..\..\lib\libacge.lib ..\..\lib\rxapi.lib ..\..\lib\ism.lib /nologo\
 /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/IsmExample.pdb" /debug /machine:I386\
 /nodefaultlib:"libc.lib" /nodefaultlib:"msvcrtd.lib" /out:"IsmExample.arx"\
 /implib:"$(OUTDIR)/IsmExample.lib" 
LINK32_OBJS= \
	"$(INTDIR)\access.obj" \
	"$(INTDIR)\CustomApplication.obj"

".\IsmExample.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ism - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\IsmExample.arx" ".\Debug\ismtest.bsc"

CLEAN : 
	-@erase "$(INTDIR)\access.obj"
	-@erase "$(INTDIR)\access.sbr"
	-@erase "$(INTDIR)\CustomApplication.obj"
	-@erase "$(INTDIR)\CustomApplication.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\IsmExample.exp"
	-@erase "$(OUTDIR)\IsmExample.lib"
	-@erase "$(OUTDIR)\IsmExample.pdb"
	-@erase ".\Debug\ismtest.bsc"
	-@erase ".\IsmExample.arx"
	-@erase ".\IsmExample.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "NDEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/IsmExamplevc4x.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o"Debug/ismtest.bsc"
# ADD BSC32 /nologo /o"Debug/ismtest.bsc"
BSC32_FLAGS=/nologo /o"Debug/ismtest.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\access.sbr" \
	"$(INTDIR)\CustomApplication.sbr"

".\Debug\ismtest.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib ..\..\lib\libacge.lib ..\..\lib\rxapi.lib ..\..\lib\ism.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libc.lib" /out:"IsmExample.arx"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib ..\..\lib\libacge.lib ..\..\lib\rxapi.lib ..\..\lib\ism.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"IsmExample.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib\
 ..\..\lib\libacge.lib ..\..\lib\rxapi.lib ..\..\lib\ism.lib /nologo\
 /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/IsmExample.pdb" /debug /machine:I386\
 /out:"IsmExample.arx" /implib:"$(OUTDIR)/IsmExample.lib" 
LINK32_OBJS= \
	"$(INTDIR)\access.obj" \
	"$(INTDIR)\CustomApplication.obj"

".\IsmExample.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

MTL_PROJ=/nologo /D "_DEBUG" /win32 

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

# Name "ism - Win32 Debug"
# Name "ism - Win32 Release"

!IF  "$(CFG)" == "ism - Win32 Debug"

!ELSEIF  "$(CFG)" == "ism - Win32 Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\CustomApplication.cpp

"$(INTDIR)\CustomApplication.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\CustomApplication.sbr" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\access.cpp

"$(INTDIR)\access.obj" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\access.sbr" : $(SOURCE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
