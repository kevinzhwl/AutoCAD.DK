# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=AsdkBodyApp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to AsdkBodyApp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AsdkBodyApp - Win32 Release" && "$(CFG)" !=\
 "AsdkBodyApp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Asdkbodyvc4x.mak" CFG="AsdkBodyApp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsdkBodyApp - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AsdkBodyApp - Win32 Debug" (based on\
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
# PROP Target_Last_Scanned "AsdkBodyApp - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "AsdkBodyApp - Win32 Release"

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

ALL : "$(OUTDIR)\AsdkBodyApp.arx"

CLEAN : 
	-@erase "$(INTDIR)\AsdkBody.obj"
	-@erase "$(INTDIR)\AsdkBodyApp.obj"
	-@erase "$(INTDIR)\ERRORMSG.OBJ"
	-@erase "$(OUTDIR)\AsdkBodyApp.arx"
	-@erase "$(OUTDIR)\AsdkBodyApp.exp"
	-@erase "$(OUTDIR)\AsdkBodyApp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /YX"stdarx.h" /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK"\
 /Fp"$(INTDIR)/Asdkbodyvc4x.pch" /YX"stdarx.h" /Fo"$(INTDIR)/" /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Asdkbodyvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\lib\amodeler.lib ..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:"Release/AsdkBodyApp.arx"
LINK32_FLAGS=..\..\lib\amodeler.lib ..\..\..\..\lib\rxapi.lib\
 ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib\
 ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/AsdkBodyApp.pdb" /machine:I386 /def:".\AsdkBodyApp.DEF"\
 /out:"$(OUTDIR)/AsdkBodyApp.arx" /implib:"$(OUTDIR)/AsdkBodyApp.lib" 
DEF_FILE= \
	".\AsdkBodyApp.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AsdkBody.obj" \
	"$(INTDIR)\AsdkBodyApp.obj" \
	"$(INTDIR)\ERRORMSG.OBJ"

"$(OUTDIR)\AsdkBodyApp.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AsdkBodyApp - Win32 Debug"

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

ALL : "$(OUTDIR)\AsdkBodyApp.arx" "$(OUTDIR)\Asdkbodyvc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\AsdkBody.obj"
	-@erase "$(INTDIR)\AsdkBody.sbr"
	-@erase "$(INTDIR)\AsdkBodyApp.obj"
	-@erase "$(INTDIR)\AsdkBodyApp.sbr"
	-@erase "$(INTDIR)\ERRORMSG.OBJ"
	-@erase "$(INTDIR)\ERRORMSG.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\AsdkBodyApp.arx"
	-@erase "$(OUTDIR)\AsdkBodyApp.exp"
	-@erase "$(OUTDIR)\AsdkBodyApp.ilk"
	-@erase "$(OUTDIR)\AsdkBodyApp.lib"
	-@erase "$(OUTDIR)\AsdkBodyApp.pdb"
	-@erase "$(OUTDIR)\Asdkbodyvc4x.bsc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /FR /YX"stdarx.h" /c
# SUBTRACT CPP /WX
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Asdkbodyvc4x.pch" /YX"stdarx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
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
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Asdkbodyvc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AsdkBody.sbr" \
	"$(INTDIR)\AsdkBodyApp.sbr" \
	"$(INTDIR)\ERRORMSG.SBR"

"$(OUTDIR)\Asdkbodyvc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\lib\amodeler.lib ..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"Debug/AsdkBodyApp.arx"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib ..\..\lib\amodeler.lib ..\..\..\..\lib\rxapi.lib\
 ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\libacge.lib\
 ..\..\..\..\lib\acad.lib ..\..\..\..\lib\acgiapi.lib /nologo\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/AsdkBodyApp.pdb" /debug /machine:I386 /def:".\AsdkBodyApp.DEF"\
 /out:"$(OUTDIR)/AsdkBodyApp.arx" /implib:"$(OUTDIR)/AsdkBodyApp.lib" 
DEF_FILE= \
	".\AsdkBodyApp.DEF"
LINK32_OBJS= \
	"$(INTDIR)\AsdkBody.obj" \
	"$(INTDIR)\AsdkBodyApp.obj" \
	"$(INTDIR)\ERRORMSG.OBJ"

"$(OUTDIR)\AsdkBodyApp.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "AsdkBodyApp - Win32 Release"
# Name "AsdkBodyApp - Win32 Debug"

!IF  "$(CFG)" == "AsdkBodyApp - Win32 Release"

!ELSEIF  "$(CFG)" == "AsdkBodyApp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\AsdkBody.CPP

!IF  "$(CFG)" == "AsdkBodyApp - Win32 Release"

DEP_CPP_ASDKB=\
	".\Asdkbody.H"\
	".\stdarx.h"\
	

"$(INTDIR)\AsdkBody.obj" : $(SOURCE) $(DEP_CPP_ASDKB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AsdkBodyApp - Win32 Debug"

DEP_CPP_ASDKB=\
	".\Asdkbody.H"\
	".\stdarx.h"\
	

"$(INTDIR)\AsdkBody.obj" : $(SOURCE) $(DEP_CPP_ASDKB) "$(INTDIR)"

"$(INTDIR)\AsdkBody.sbr" : $(SOURCE) $(DEP_CPP_ASDKB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AsdkBodyApp.CPP
DEP_CPP_ASDKBO=\
	".\Asdkbody.H"\
	".\AsdkBodyApp.H"\
	".\ERRORMSG.H"\
	".\stdarx.h"\
	

!IF  "$(CFG)" == "AsdkBodyApp - Win32 Release"


"$(INTDIR)\AsdkBodyApp.obj" : $(SOURCE) $(DEP_CPP_ASDKBO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AsdkBodyApp - Win32 Debug"


"$(INTDIR)\AsdkBodyApp.obj" : $(SOURCE) $(DEP_CPP_ASDKBO) "$(INTDIR)"

"$(INTDIR)\AsdkBodyApp.sbr" : $(SOURCE) $(DEP_CPP_ASDKBO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ERRORMSG.CPP
DEP_CPP_ERROR=\
	".\ERRORMSG.H"\
	".\stdarx.h"\
	

!IF  "$(CFG)" == "AsdkBodyApp - Win32 Release"


"$(INTDIR)\ERRORMSG.OBJ" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "AsdkBodyApp - Win32 Debug"


"$(INTDIR)\ERRORMSG.OBJ" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"

"$(INTDIR)\ERRORMSG.SBR" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AsdkBodyApp.DEF

!IF  "$(CFG)" == "AsdkBodyApp - Win32 Release"

!ELSEIF  "$(CFG)" == "AsdkBodyApp - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
