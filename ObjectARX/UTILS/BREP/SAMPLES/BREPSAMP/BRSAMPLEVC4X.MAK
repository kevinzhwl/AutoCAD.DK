# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=brsample - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to brsample - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "brsample - Win32 Release" && "$(CFG)" !=\
 "brsample - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "brsamplevc4x.mak" CFG="brsample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "brsample - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "brsample - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "brsample - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "brsample - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\"
# PROP Intermediate_Dir ".\"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\brsample.arx"

CLEAN : 
	-@erase "$(INTDIR)\brbblock.obj"
	-@erase "$(INTDIR)\brbdump.obj"
	-@erase "$(INTDIR)\brdbutl.obj"
	-@erase "$(INTDIR)\brdump.obj"
	-@erase "$(INTDIR)\bredump.obj"
	-@erase "$(INTDIR)\brfdump.obj"
	-@erase "$(INTDIR)\brgeutl.obj"
	-@erase "$(INTDIR)\brlncnt.obj"
	-@erase "$(INTDIR)\brptcnt.obj"
	-@erase "$(INTDIR)\brreport.obj"
	-@erase "$(INTDIR)\brsample.obj"
	-@erase "$(INTDIR)\brtrmsrf.obj"
	-@erase "$(INTDIR)\brvdump.obj"
	-@erase "$(OUTDIR)\brsample.arx"
	-@erase "$(OUTDIR)\brsample.exp"
	-@erase "$(OUTDIR)\brsample.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "RADPACK" /D "ACRXAPP" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\inc" /I "..\..\..\..\inc" /D\
 "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "RADPACK" /D "ACRXAPP"\
 /Fp"$(INTDIR)/brsamplevc4x.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\.\ 
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/brsamplevc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\libacge.lib ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\acad.lib ..\..\lib\libacgex.lib ..\..\lib\libacbr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:".\brsample.arx"
LINK32_FLAGS=..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\libacge.lib\
 ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\acad.lib ..\..\lib\libacgex.lib\
 ..\..\lib\libacbr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/brsample.pdb"\
 /machine:I386 /def:".\brsample.def" /out:"$(OUTDIR)/brsample.arx"\
 /implib:"$(OUTDIR)/brsample.lib" 
DEF_FILE= \
	".\brsample.def"
LINK32_OBJS= \
	"$(INTDIR)\brbblock.obj" \
	"$(INTDIR)\brbdump.obj" \
	"$(INTDIR)\brdbutl.obj" \
	"$(INTDIR)\brdump.obj" \
	"$(INTDIR)\bredump.obj" \
	"$(INTDIR)\brfdump.obj" \
	"$(INTDIR)\brgeutl.obj" \
	"$(INTDIR)\brlncnt.obj" \
	"$(INTDIR)\brptcnt.obj" \
	"$(INTDIR)\brreport.obj" \
	"$(INTDIR)\brsample.obj" \
	"$(INTDIR)\brtrmsrf.obj" \
	"$(INTDIR)\brvdump.obj"

"$(OUTDIR)\brsample.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "brsample - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\"
# PROP Intermediate_Dir ".\"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.

ALL : "$(OUTDIR)\brsample.arx"

CLEAN : 
	-@erase "$(INTDIR)\brbblock.obj"
	-@erase "$(INTDIR)\brbdump.obj"
	-@erase "$(INTDIR)\brdbutl.obj"
	-@erase "$(INTDIR)\brdump.obj"
	-@erase "$(INTDIR)\bredump.obj"
	-@erase "$(INTDIR)\brfdump.obj"
	-@erase "$(INTDIR)\brgeutl.obj"
	-@erase "$(INTDIR)\brlncnt.obj"
	-@erase "$(INTDIR)\brptcnt.obj"
	-@erase "$(INTDIR)\brreport.obj"
	-@erase "$(INTDIR)\brsample.obj"
	-@erase "$(INTDIR)\brtrmsrf.obj"
	-@erase "$(INTDIR)\brvdump.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\brsample.arx"
	-@erase "$(OUTDIR)\brsample.exp"
	-@erase "$(OUTDIR)\brsample.ilk"
	-@erase "$(OUTDIR)\brsample.lib"
	-@erase "$(OUTDIR)\brsample.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "RADPACK" /D "ACRXAPP" /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /I "..\..\..\..\inc" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "RADPACK" /D "ACRXAPP"\
 /Fp"$(INTDIR)/brsamplevc4x.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\.\ 
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/brsamplevc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\libacge.lib ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\acad.lib ..\..\lib\libacgex.lib ..\..\lib\libacbr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:".\brsample.arx"
LINK32_FLAGS=..\..\..\..\lib\rxapi.lib ..\..\..\..\lib\libacge.lib\
 ..\..\..\..\lib\acedapi.lib ..\..\..\..\lib\acad.lib ..\..\lib\libacgex.lib\
 ..\..\lib\libacbr.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/brsample.pdb" /debug\
 /machine:I386 /def:".\brsample.def" /out:"$(OUTDIR)/brsample.arx"\
 /implib:"$(OUTDIR)/brsample.lib" 
DEF_FILE= \
	".\brsample.def"
LINK32_OBJS= \
	"$(INTDIR)\brbblock.obj" \
	"$(INTDIR)\brbdump.obj" \
	"$(INTDIR)\brdbutl.obj" \
	"$(INTDIR)\brdump.obj" \
	"$(INTDIR)\bredump.obj" \
	"$(INTDIR)\brfdump.obj" \
	"$(INTDIR)\brgeutl.obj" \
	"$(INTDIR)\brlncnt.obj" \
	"$(INTDIR)\brptcnt.obj" \
	"$(INTDIR)\brreport.obj" \
	"$(INTDIR)\brsample.obj" \
	"$(INTDIR)\brtrmsrf.obj" \
	"$(INTDIR)\brvdump.obj"

"$(OUTDIR)\brsample.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "brsample - Win32 Release"
# Name "brsample - Win32 Debug"

!IF  "$(CFG)" == "brsample - Win32 Release"

!ELSEIF  "$(CFG)" == "brsample - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\brbblock.cpp
DEP_CPP_BRBBL=\
	".\brbblock.h"\
	".\brdbutl.h"\
	".\brreport.h"\
	

"$(INTDIR)\brbblock.obj" : $(SOURCE) $(DEP_CPP_BRBBL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brvdump.cpp
DEP_CPP_BRVDU=\
	".\brreport.h"\
	".\brvdump.h"\
	

"$(INTDIR)\brvdump.obj" : $(SOURCE) $(DEP_CPP_BRVDU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brdbutl.cpp
DEP_CPP_BRDBU=\
	".\brdbutl.h"\
	

"$(INTDIR)\brdbutl.obj" : $(SOURCE) $(DEP_CPP_BRDBU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brdump.cpp
DEP_CPP_BRDUM=\
	".\brbdump.h"\
	".\brdbutl.h"\
	".\brdump.h"\
	".\bredump.h"\
	".\brfdump.h"\
	".\brreport.h"\
	".\brvdump.h"\
	

"$(INTDIR)\brdump.obj" : $(SOURCE) $(DEP_CPP_BRDUM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bredump.cpp
DEP_CPP_BREDU=\
	".\bredump.h"\
	".\brgeutl.h"\
	".\brreport.h"\
	".\brvdump.h"\
	

"$(INTDIR)\bredump.obj" : $(SOURCE) $(DEP_CPP_BREDU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brfdump.cpp
DEP_CPP_BRFDU=\
	".\brfdump.h"\
	".\brgeutl.h"\
	".\brreport.h"\
	

"$(INTDIR)\brfdump.obj" : $(SOURCE) $(DEP_CPP_BRFDU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brgeutl.cpp

!IF  "$(CFG)" == "brsample - Win32 Release"

DEP_CPP_BRGEU=\
	".\brgeutl.h"\
	".\brreport.h"\
	

"$(INTDIR)\brgeutl.obj" : $(SOURCE) $(DEP_CPP_BRGEU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "brsample - Win32 Debug"

DEP_CPP_BRGEU=\
	".\brgeutl.h"\
	".\brreport.h"\
	

"$(INTDIR)\brgeutl.obj" : $(SOURCE) $(DEP_CPP_BRGEU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\brlncnt.cpp
DEP_CPP_BRLNC=\
	".\brdbutl.h"\
	".\brlncnt.h"\
	".\brreport.h"\
	

"$(INTDIR)\brlncnt.obj" : $(SOURCE) $(DEP_CPP_BRLNC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brptcnt.cpp
DEP_CPP_BRPTC=\
	".\brdbutl.h"\
	".\brptcnt.h"\
	".\brreport.h"\
	

"$(INTDIR)\brptcnt.obj" : $(SOURCE) $(DEP_CPP_BRPTC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brreport.cpp
DEP_CPP_BRREP=\
	".\brreport.h"\
	

"$(INTDIR)\brreport.obj" : $(SOURCE) $(DEP_CPP_BRREP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brsample.cpp
DEP_CPP_BRSAM=\
	".\brbblock.h"\
	".\brdump.h"\
	".\brlncnt.h"\
	".\brptcnt.h"\
	".\brtrmsrf.h"\
	

"$(INTDIR)\brsample.obj" : $(SOURCE) $(DEP_CPP_BRSAM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\brtrmsrf.cpp

!IF  "$(CFG)" == "brsample - Win32 Release"

DEP_CPP_BRTRM=\
	".\brdbutl.h"\
	".\brgeutl.h"\
	".\brreport.h"\
	".\brtrmsrf.h"\
	

"$(INTDIR)\brtrmsrf.obj" : $(SOURCE) $(DEP_CPP_BRTRM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "brsample - Win32 Debug"

DEP_CPP_BRTRM=\
	".\brdbutl.h"\
	".\brgeutl.h"\
	".\brreport.h"\
	".\brtrmsrf.h"\
	

"$(INTDIR)\brtrmsrf.obj" : $(SOURCE) $(DEP_CPP_BRTRM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\brbdump.cpp

!IF  "$(CFG)" == "brsample - Win32 Release"

DEP_CPP_BRBDU=\
	".\brbdump.h"\
	".\brgeutl.h"\
	".\brreport.h"\
	".\brvdump.h"\
	

"$(INTDIR)\brbdump.obj" : $(SOURCE) $(DEP_CPP_BRBDU) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "brsample - Win32 Debug"

DEP_CPP_BRBDU=\
	".\brbdump.h"\
	".\brgeutl.h"\
	".\brreport.h"\
	".\brvdump.h"\
	

"$(INTDIR)\brbdump.obj" : $(SOURCE) $(DEP_CPP_BRBDU) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\brsample.def

!IF  "$(CFG)" == "brsample - Win32 Release"

!ELSEIF  "$(CFG)" == "brsample - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
