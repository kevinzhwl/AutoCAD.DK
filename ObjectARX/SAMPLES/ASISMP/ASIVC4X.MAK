# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=asismp - Win32 Release
!MESSAGE No configuration specified.  Defaulting to asismp - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "asismp - Win32 Debug" && "$(CFG)" != "asismp - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "asivc4x.mak" CFG="asismp - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "asismp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "asismp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "asismp - Win32 Release"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "asismp - Win32 Debug"

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

ALL : "$(OUTDIR)\ASISMP.arx" "$(OUTDIR)\asivc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\asismp.obj"
	-@erase "$(INTDIR)\asismp.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ASISMP.arx"
	-@erase "$(OUTDIR)\ASISMP.exp"
	-@erase "$(OUTDIR)\ASISMP.ilk"
	-@erase "$(OUTDIR)\ASISMP.lib"
	-@erase "$(OUTDIR)\ASISMP.pdb"
	-@erase "$(OUTDIR)\asivc4x.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /O2 /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_MBCS" /D "RADPACK" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /O2 /I "..\..\inc" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_MBCS"\
 /D "RADPACK" /FR"$(INTDIR)/" /Fp"$(INTDIR)/asivc4x.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/asivc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\asismp.sbr"

"$(OUTDIR)\asivc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib  ..\..\lib\libacge.lib ..\..\lib\rxapi.lib ..\..\lib\asertvc4.lib ..\..\lib\asiatvc4.lib  user32.lib kernel32.lib advapi32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:IX86 /out:"Debug/ASISMP.arx"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=..\..\lib\acad.lib ..\..\lib\acedapi.lib  ..\..\lib\libacge.lib\
 ..\..\lib\rxapi.lib ..\..\lib\asertvc4.lib ..\..\lib\asiatvc4.lib  user32.lib\
 kernel32.lib advapi32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/ASISMP.pdb" /debug\
 /machine:IX86 /def:".\asismp.def" /out:"$(OUTDIR)/ASISMP.arx"\
 /implib:"$(OUTDIR)/ASISMP.lib" 
DEF_FILE= \
	".\asismp.def"
LINK32_OBJS= \
	"$(INTDIR)\asismp.obj"

"$(OUTDIR)\ASISMP.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "asismp - Win32 Release"

# PROP BASE Use_MFC 2
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

ALL : "$(OUTDIR)\ASISMP.arx" "$(OUTDIR)\asivc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\asismp.obj"
	-@erase "$(INTDIR)\asismp.sbr"
	-@erase "$(OUTDIR)\ASISMP.arx"
	-@erase "$(OUTDIR)\ASISMP.exp"
	-@erase "$(OUTDIR)\ASISMP.ilk"
	-@erase "$(OUTDIR)\ASISMP.lib"
	-@erase "$(OUTDIR)\asivc4x.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /Od /I "..\..\inc" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_MBCS" /D "RADPACK" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "_WINDOWS" /D\
 "ACRXAPP" /D "_USRDLL" /D "CS_USEDLL" /D "CS_APP" /D "_MBCS" /D "RADPACK"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/asivc4x.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /win32
# ADD MTL /nologo /win32
MTL_PROJ=/nologo /win32 
# ADD BASE RSC /l 0x409 /d "_AFXDLL"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/asivc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\asismp.sbr"

"$(OUTDIR)\asivc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib ..\..\lib\libacge.lib ..\..\lib\rxapi.lib libc.lib user32.lib msvcrt.lib oldnames.lib kernel32.lib advapi32.lib /nologo /base:0x35000000 /entry:"DllEntryPoint@12" /machine:IX86 /subsystem:
# SUBTRACT BASE LINK32 /pdb:none /map
# ADD LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\libacge.lib ..\..\lib\rxapi.lib ..\..\lib\asertvc4.lib ..\..\lib\asiatvc4.lib user32.lib kernel32.lib advapi32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:yes /machine:IX86 /out:"Release/ASISMP.arx"
# SUBTRACT LINK32 /pdb:none /map /debug /nodefaultlib
LINK32_FLAGS=..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\libacge.lib\
 ..\..\lib\rxapi.lib ..\..\lib\asertvc4.lib ..\..\lib\asiatvc4.lib user32.lib\
 kernel32.lib advapi32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/ASISMP.pdb"\
 /machine:IX86 /def:".\asismp.def" /out:"$(OUTDIR)/ASISMP.arx"\
 /implib:"$(OUTDIR)/ASISMP.lib" 
DEF_FILE= \
	".\asismp.def"
LINK32_OBJS= \
	"$(INTDIR)\asismp.obj"

"$(OUTDIR)\ASISMP.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "asismp - Win32 Debug"
# Name "asismp - Win32 Release"

!IF  "$(CFG)" == "asismp - Win32 Debug"

!ELSEIF  "$(CFG)" == "asismp - Win32 Release"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\asismp.def

!IF  "$(CFG)" == "asismp - Win32 Debug"

!ELSEIF  "$(CFG)" == "asismp - Win32 Release"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\asismp.cpp
DEP_CPP_ASISM=\
	

"$(INTDIR)\asismp.obj" : $(SOURCE) $(DEP_CPP_ASISM) "$(INTDIR)"

"$(INTDIR)\asismp.sbr" : $(SOURCE) $(DEP_CPP_ASISM) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
