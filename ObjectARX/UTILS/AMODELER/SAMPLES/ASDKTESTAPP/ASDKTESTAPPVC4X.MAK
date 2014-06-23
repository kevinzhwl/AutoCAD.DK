# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=AsdkTestApp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to AsdkTestApp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AsdkTestApp - Win32 Release" && "$(CFG)" !=\
 "AsdkTestApp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsdkTestAppvc4x.mak" CFG="AsdkTestApp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsdkTestApp - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AsdkTestApp - Win32 Debug" (based on\
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
# PROP Target_Last_Scanned "AsdkTestApp - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "AsdkTestApp - Win32 Release"

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

ALL : "$(OUTDIR)\AsdkTestApp.arx"

CLEAN : 
	-@erase "$(INTDIR)\AsdkTestApp.obj"
	-@erase "$(INTDIR)\SAMPLE.OBJ"
	-@erase "$(OUTDIR)\AsdkTestApp.arx"
	-@erase "$(OUTDIR)\AsdkTestApp.exp"
	-@erase "$(OUTDIR)\AsdkTestApp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /YX"stdarx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK"\
 /Fp"$(INTDIR)/AsdkTestAppvc4x.pch" /YX"stdarx.h" /Fo"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AsdkTestAppvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\lib\Amodeler.lib ..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:"Release/AsdkTestApp.arx"
LINK32_FLAGS=..\..\lib\Amodeler.lib ..\..\..\..\lib\rxapi.lib\
 ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib\
 ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/AsdkTestApp.pdb" /machine:I386 /def:".\AsdkTestApp.DEF"\
 /out:"$(OUTDIR)/AsdkTestApp.arx" /implib:"$(OUTDIR)/AsdkTestApp.lib" 
DEF_FILE= \
	".\AsdkTestApp.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AsdkTestApp.obj" \
	"$(INTDIR)\SAMPLE.OBJ"

"$(OUTDIR)\AsdkTestApp.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AsdkTestApp - Win32 Debug"

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

ALL : "$(OUTDIR)\AsdkTestApp.arx" "$(OUTDIR)\AsdkTestAppvc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\AsdkTestApp.obj"
	-@erase "$(INTDIR)\AsdkTestApp.sbr"
	-@erase "$(INTDIR)\SAMPLE.OBJ"
	-@erase "$(INTDIR)\SAMPLE.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\AsdkTestApp.arx"
	-@erase "$(OUTDIR)\AsdkTestApp.exp"
	-@erase "$(OUTDIR)\AsdkTestApp.ilk"
	-@erase "$(OUTDIR)\AsdkTestApp.lib"
	-@erase "$(OUTDIR)\AsdkTestApp.pdb"
	-@erase "$(OUTDIR)\AsdkTestAppvc4x.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /FR /YX"stdarx.h" /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/AsdkTestAppvc4x.pch" /YX"stdarx.h" /Fo"$(INTDIR)/"\
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AsdkTestAppvc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AsdkTestApp.sbr" \
	"$(INTDIR)\SAMPLE.SBR"

"$(OUTDIR)\AsdkTestAppvc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\lib\Amodeler.lib ..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"Debug/AsdkTestApp.arx"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\lib\Amodeler.lib ..\..\..\..\lib\rxapi.lib\
 ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib\
 ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/AsdkTestApp.pdb" /debug /machine:I386 /def:".\AsdkTestApp.DEF"\
 /out:"$(OUTDIR)/AsdkTestApp.arx" /implib:"$(OUTDIR)/AsdkTestApp.lib" 
DEF_FILE= \
	".\AsdkTestApp.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AsdkTestApp.obj" \
	"$(INTDIR)\SAMPLE.OBJ"

"$(OUTDIR)\AsdkTestApp.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "AsdkTestApp - Win32 Release"
# Name "AsdkTestApp - Win32 Debug"

!IF  "$(CFG)" == "AsdkTestApp - Win32 Release"

!ELSEIF  "$(CFG)" == "AsdkTestApp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\AsdkTestApp.CPP

!IF  "$(CFG)" == "AsdkTestApp - Win32 Release"

DEP_CPP_ASDKT=\
	".\AsdkTestApp.H"\
	".\stdarx.h"\
	

"$(INTDIR)\AsdkTestApp.obj" : $(SOURCE) $(DEP_CPP_ASDKT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AsdkTestApp - Win32 Debug"

DEP_CPP_ASDKT=\
	".\AsdkTestApp.H"\
	".\stdarx.h"\
	

"$(INTDIR)\AsdkTestApp.obj" : $(SOURCE) $(DEP_CPP_ASDKT) "$(INTDIR)"

"$(INTDIR)\AsdkTestApp.sbr" : $(SOURCE) $(DEP_CPP_ASDKT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AsdkTestApp.DEF

!IF  "$(CFG)" == "AsdkTestApp - Win32 Release"

!ELSEIF  "$(CFG)" == "AsdkTestApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SAMPLE.CPP

!IF  "$(CFG)" == "AsdkTestApp - Win32 Release"

DEP_CPP_SAMPL=\
	".\stdarx.h"\
	

"$(INTDIR)\SAMPLE.OBJ" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AsdkTestApp - Win32 Debug"

DEP_CPP_SAMPL=\
	".\stdarx.h"\
	

"$(INTDIR)\SAMPLE.OBJ" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"

"$(INTDIR)\SAMPLE.SBR" : $(SOURCE) $(DEP_CPP_SAMPL) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
