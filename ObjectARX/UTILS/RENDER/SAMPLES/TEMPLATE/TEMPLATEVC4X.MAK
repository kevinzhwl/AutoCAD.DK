# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=template - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to template - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "template - Win32 Release" && "$(CFG)" !=\
 "template - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "templatevc4x.mak" CFG="template - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "template - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "template - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "template - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "template - Win32 Release"

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

ALL : "$(OUTDIR)\template.arx" "$(OUTDIR)\templatevc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\template.obj"
	-@erase "$(INTDIR)\template.sbr"
	-@erase "$(OUTDIR)\template.arx"
	-@erase "$(OUTDIR)\template.exp"
	-@erase "$(OUTDIR)\template.lib"
	-@erase "$(OUTDIR)\templatevc4x.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /O2 /I "r:\rx\api" /I "t:\avlib\inc" /I "r:\ads" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "ACRXAPP" /D "RADPACK" /FR /YX /c
# ADD CPP /nologo /MD /W4 /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "ACRXAPP" /D "RADPACK" /FR /YX /c
CPP_PROJ=/nologo /MD /W4 /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_X86_" /D "ACRXAPP" /D "RADPACK" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/templatevc4x.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/templatevc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\template.sbr"

"$(OUTDIR)\templatevc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 olecli32.lib olesvr32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c00000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:IX86 /def:"t:\avlib\sample\template.def"
# ADD LINK32 ..\..\lib\avlib.lib ..\..\..\..\lib\acad.lib ..\..\..\..\lib\rxapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c00000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:IX86 /nodefaultlib:"libc" /def:"template.def" /out:"Release/template.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\lib\avlib.lib ..\..\..\..\lib\acad.lib\
 ..\..\..\..\lib\rxapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c00000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/template.pdb"\
 /machine:IX86 /nodefaultlib:"libc" /def:"template.def"\
 /out:"$(OUTDIR)/template.arx" /implib:"$(OUTDIR)/template.lib" 
LINK32_OBJS= \
	"$(INTDIR)\template.obj"

"$(OUTDIR)\template.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "template - Win32 Debug"

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

ALL : "$(OUTDIR)\template.arx" "$(OUTDIR)\templatevc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\template.obj"
	-@erase "$(INTDIR)\template.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\template.arx"
	-@erase "$(OUTDIR)\template.exp"
	-@erase "$(OUTDIR)\template.ilk"
	-@erase "$(OUTDIR)\template.lib"
	-@erase "$(OUTDIR)\template.pdb"
	-@erase "$(OUTDIR)\templatevc4x.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /I "r:\rx\api" /I "t:\avlib\inc" /I "r:\ads" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "ACRXAPP" /D "RADPACK" /FR /YX /c
# ADD CPP /nologo /MD /W4 /Gm /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "ACRXAPP" /D "RADPACK" /FR /YX /c
CPP_PROJ=/nologo /MD /W4 /Gm /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_X86_" /D "ACRXAPP" /D "RADPACK"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/templatevc4x.pch" /YX /Fo"$(INTDIR)/"\
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/templatevc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\template.sbr"

"$(OUTDIR)\templatevc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 olecli32.lib olesvr32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c00000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:IX86 /def:"t:\avlib\sample\template.def"
# ADD LINK32 ..\..\lib\avlib.lib ..\..\..\..\lib\acad.lib ..\..\..\..\lib\rxapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c00000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:IX86 /nodefaultlib:"libcd" /def:"template.def" /out:"Debug/template.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\lib\avlib.lib ..\..\..\..\lib\acad.lib\
 ..\..\..\..\lib\rxapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c00000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/template.pdb" /debug\
 /machine:IX86 /nodefaultlib:"libcd" /def:"template.def"\
 /out:"$(OUTDIR)/template.arx" /implib:"$(OUTDIR)/template.lib" 
LINK32_OBJS= \
	"$(INTDIR)\template.obj"

"$(OUTDIR)\template.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "template - Win32 Release"
# Name "template - Win32 Debug"

!IF  "$(CFG)" == "template - Win32 Release"

!ELSEIF  "$(CFG)" == "template - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\template.cpp

!IF  "$(CFG)" == "template - Win32 Release"

DEP_CPP_TEMPL=\
	"..\..\inc\averror.h"\
	"..\..\inc\avlib.h"\
	
NODEP_CPP_TEMPL=\
	"..\..\inc\adscodes.h"\
	"..\..\inc\adslib.h"\
	

"$(INTDIR)\template.obj" : $(SOURCE) $(DEP_CPP_TEMPL) "$(INTDIR)"

"$(INTDIR)\template.sbr" : $(SOURCE) $(DEP_CPP_TEMPL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "template - Win32 Debug"

DEP_CPP_TEMPL=\
	"..\..\inc\averror.h"\
	"..\..\inc\avlib.h"\
	
NODEP_CPP_TEMPL=\
	"..\..\inc\adscodes.h"\
	"..\..\inc\adslib.h"\
	

"$(INTDIR)\template.obj" : $(SOURCE) $(DEP_CPP_TEMPL) "$(INTDIR)"

"$(INTDIR)\template.sbr" : $(SOURCE) $(DEP_CPP_TEMPL) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
