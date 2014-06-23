# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=clonemsg - Win32 Direct
!MESSAGE No configuration specified.  Defaulting to clonemsg - Win32 Direct.
!ENDIF 

!IF "$(CFG)" != "clonemsg - Win32 Direct" && "$(CFG)" !=\
 "clonemsg - Win32 ExtDict SoftPointer" && "$(CFG)" !=\
 "clonemsg - Win32 ExtDict HardPointer" && "$(CFG)" !=\
 "clonemsg - Win32 NOD SoftPointer" && "$(CFG)" !=\
 "clonemsg - Win32 NOD HardPointer"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CMSGVC4X.MAK" CFG="clonemsg - Win32 Direct"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "clonemsg - Win32 Direct" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 ExtDict SoftPointer" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 ExtDict HardPointer" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 NOD SoftPointer" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "clonemsg - Win32 NOD HardPointer" (based on\
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
# PROP Target_Last_Scanned "clonemsg - Win32 NOD HardPointer"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "clonemsg - Win32 Direct"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Direct"
# PROP Intermediate_Dir "Direct"
OUTDIR=.\Direct
INTDIR=.\Direct

ALL : "$(OUTDIR)\clonemsg.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxutils.obj"
	-@erase "$(INTDIR)\edreact.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\MkrEnti.obj"
	-@erase "$(INTDIR)\MKROBJE.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\clonemsg.arx"
	-@erase "$(OUTDIR)\clonemsg.exp"
	-@erase "$(OUTDIR)\clonemsg.ilk"
	-@erase "$(OUTDIR)\clonemsg.lib"
	-@erase "$(OUTDIR)\clonemsg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "DIRECT" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "DIRECT" /Fp"$(INTDIR)/CMSGVC4X.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Direct/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CMSGVC4X.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"Direct/clonemsg.arx"
# SUBTRACT LINK32 /nodefaultlib /force
LINK32_FLAGS=..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib\
 ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/clonemsg.pdb" /debug\
 /machine:I386 /def:".\clonemsg.def" /out:"$(OUTDIR)/clonemsg.arx"\
 /implib:"$(OUTDIR)/clonemsg.lib" 
DEF_FILE= \
	".\clonemsg.def"
LINK32_OBJS= \
	"$(INTDIR)\arxutils.obj" \
	"$(INTDIR)\edreact.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MkrEnti.obj" \
	"$(INTDIR)\MKROBJE.obj"

"$(OUTDIR)\clonemsg.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Dictiona"
# PROP BASE Intermediate_Dir "Dictiona"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ExtDSoft"
# PROP Intermediate_Dir "ExtDSoft"
OUTDIR=.\ExtDSoft
INTDIR=.\ExtDSoft

ALL : "$(OUTDIR)\clonemsg.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxutils.obj"
	-@erase "$(INTDIR)\edreact.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\MkrEnti.obj"
	-@erase "$(INTDIR)\MKROBJE.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\clonemsg.arx"
	-@erase "$(OUTDIR)\clonemsg.exp"
	-@erase "$(OUTDIR)\clonemsg.ilk"
	-@erase "$(OUTDIR)\clonemsg.lib"
	-@erase "$(OUTDIR)\clonemsg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /Fp"$(INTDIR)/CMSGVC4X.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\ExtDSoft/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CMSGVC4X.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 ..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"ExtDSoft/clonemsg.arx"
# SUBTRACT LINK32 /nodefaultlib /force
LINK32_FLAGS=..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib\
 ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/clonemsg.pdb" /debug\
 /machine:I386 /def:".\clonemsg.def" /out:"$(OUTDIR)/clonemsg.arx"\
 /implib:"$(OUTDIR)/clonemsg.lib" 
DEF_FILE= \
	".\clonemsg.def"
LINK32_OBJS= \
	"$(INTDIR)\arxutils.obj" \
	"$(INTDIR)\edreact.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MkrEnti.obj" \
	"$(INTDIR)\MKROBJE.obj"

"$(OUTDIR)\clonemsg.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Extensio"
# PROP BASE Intermediate_Dir "Extensio"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ExtDHard"
# PROP Intermediate_Dir "ExtDHard"
OUTDIR=.\ExtDHard
INTDIR=.\ExtDHard

ALL : "$(OUTDIR)\clonemsg.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxutils.obj"
	-@erase "$(INTDIR)\edreact.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\MkrEnti.obj"
	-@erase "$(INTDIR)\MKROBJE.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\clonemsg.arx"
	-@erase "$(OUTDIR)\clonemsg.exp"
	-@erase "$(OUTDIR)\clonemsg.ilk"
	-@erase "$(OUTDIR)\clonemsg.lib"
	-@erase "$(OUTDIR)\clonemsg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "HARDPOINTER" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "HARDPOINTER"\
 /Fp"$(INTDIR)/CMSGVC4X.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\ExtDHard/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CMSGVC4X.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 ..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"ExtDHard/clonemsg.arx"
# SUBTRACT LINK32 /nodefaultlib /force
LINK32_FLAGS=..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib\
 ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/clonemsg.pdb" /debug\
 /machine:I386 /def:".\clonemsg.def" /out:"$(OUTDIR)/clonemsg.arx"\
 /implib:"$(OUTDIR)/clonemsg.lib" 
DEF_FILE= \
	".\clonemsg.def"
LINK32_OBJS= \
	"$(INTDIR)\arxutils.obj" \
	"$(INTDIR)\edreact.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MkrEnti.obj" \
	"$(INTDIR)\MKROBJE.obj"

"$(OUTDIR)\clonemsg.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Namedobj"
# PROP BASE Intermediate_Dir "Namedobj"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "NoDSoft"
# PROP Intermediate_Dir "NoDSoft"
OUTDIR=.\NoDSoft
INTDIR=.\NoDSoft

ALL : "$(OUTDIR)\clonemsg.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxutils.obj"
	-@erase "$(INTDIR)\edreact.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\MkrEnti.obj"
	-@erase "$(INTDIR)\MKROBJE.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\clonemsg.arx"
	-@erase "$(OUTDIR)\clonemsg.exp"
	-@erase "$(OUTDIR)\clonemsg.ilk"
	-@erase "$(OUTDIR)\clonemsg.lib"
	-@erase "$(OUTDIR)\clonemsg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD"\
 /Fp"$(INTDIR)/CMSGVC4X.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\NoDSoft/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CMSGVC4X.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 ..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"NoDSoft/clonemsg.arx"
# SUBTRACT LINK32 /nodefaultlib /force
LINK32_FLAGS=..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib\
 ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/clonemsg.pdb" /debug\
 /machine:I386 /def:".\clonemsg.def" /out:"$(OUTDIR)/clonemsg.arx"\
 /implib:"$(OUTDIR)/clonemsg.lib" 
DEF_FILE= \
	".\clonemsg.def"
LINK32_OBJS= \
	"$(INTDIR)\arxutils.obj" \
	"$(INTDIR)\edreact.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MkrEnti.obj" \
	"$(INTDIR)\MKROBJE.obj"

"$(OUTDIR)\clonemsg.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Namedob0"
# PROP BASE Intermediate_Dir "Namedob0"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "NoDHard"
# PROP Intermediate_Dir "NoDHard"
OUTDIR=.\NoDHard
INTDIR=.\NoDHard

ALL : "$(OUTDIR)\clonemsg.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxutils.obj"
	-@erase "$(INTDIR)\edreact.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\MkrEnti.obj"
	-@erase "$(INTDIR)\MKROBJE.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\clonemsg.arx"
	-@erase "$(OUTDIR)\clonemsg.exp"
	-@erase "$(OUTDIR)\clonemsg.ilk"
	-@erase "$(OUTDIR)\clonemsg.lib"
	-@erase "$(OUTDIR)\clonemsg.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /D "HARDPOINTER" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "_DEBUG" /D "WIN32"\
 /D "_WINDOWS" /D "ACRXAPP" /D "WIN" /D "XLATE" /D "NOD" /D "HARDPOINTER"\
 /Fp"$(INTDIR)/CMSGVC4X.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\NoDHard/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CMSGVC4X.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 rxapi.lib acad.lib acedapi.lib libacge.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /force /out:"WinDebug/clonemsg.arx"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 ..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:"NoDHard/clonemsg.arx"
# SUBTRACT LINK32 /nodefaultlib /force
LINK32_FLAGS=..\..\lib\rxapi.lib ..\..\lib\acad.lib ..\..\lib\acedapi.lib\
 ..\..\lib\libacge.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/clonemsg.pdb" /debug\
 /machine:I386 /def:".\clonemsg.def" /out:"$(OUTDIR)/clonemsg.arx"\
 /implib:"$(OUTDIR)/clonemsg.lib" 
DEF_FILE= \
	".\clonemsg.def"
LINK32_OBJS= \
	"$(INTDIR)\arxutils.obj" \
	"$(INTDIR)\edreact.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\MkrEnti.obj" \
	"$(INTDIR)\MKROBJE.obj"

"$(OUTDIR)\clonemsg.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "clonemsg - Win32 Direct"
# Name "clonemsg - Win32 ExtDict SoftPointer"
# Name "clonemsg - Win32 ExtDict HardPointer"
# Name "clonemsg - Win32 NOD SoftPointer"
# Name "clonemsg - Win32 NOD HardPointer"

!IF  "$(CFG)" == "clonemsg - Win32 Direct"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\clonemsg.def

!IF  "$(CFG)" == "clonemsg - Win32 Direct"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"

!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\main.cpp
DEP_CPP_MAIN_=\
	".\arxutils.h"\
	".\edreact.h"\
	".\main.h"\
	".\MkrEnti.h"\
	".\MKROBJE.h"\
	

!IF  "$(CFG)" == "clonemsg - Win32 Direct"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"


"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\arxutils.cpp
DEP_CPP_ARXUT=\
	".\arxutils.h"\
	

!IF  "$(CFG)" == "clonemsg - Win32 Direct"


"$(INTDIR)\arxutils.obj" : $(SOURCE) $(DEP_CPP_ARXUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"


"$(INTDIR)\arxutils.obj" : $(SOURCE) $(DEP_CPP_ARXUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"


"$(INTDIR)\arxutils.obj" : $(SOURCE) $(DEP_CPP_ARXUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"


"$(INTDIR)\arxutils.obj" : $(SOURCE) $(DEP_CPP_ARXUT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"


"$(INTDIR)\arxutils.obj" : $(SOURCE) $(DEP_CPP_ARXUT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MKROBJE.cpp
DEP_CPP_MKROB=\
	".\MKROBJE.h"\
	

!IF  "$(CFG)" == "clonemsg - Win32 Direct"


"$(INTDIR)\MKROBJE.obj" : $(SOURCE) $(DEP_CPP_MKROB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"


"$(INTDIR)\MKROBJE.obj" : $(SOURCE) $(DEP_CPP_MKROB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"


"$(INTDIR)\MKROBJE.obj" : $(SOURCE) $(DEP_CPP_MKROB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"


"$(INTDIR)\MKROBJE.obj" : $(SOURCE) $(DEP_CPP_MKROB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"


"$(INTDIR)\MKROBJE.obj" : $(SOURCE) $(DEP_CPP_MKROB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\edreact.cpp
DEP_CPP_EDREA=\
	".\arxutils.h"\
	".\edreact.h"\
	".\MkrEnti.h"\
	

!IF  "$(CFG)" == "clonemsg - Win32 Direct"


"$(INTDIR)\edreact.obj" : $(SOURCE) $(DEP_CPP_EDREA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"


"$(INTDIR)\edreact.obj" : $(SOURCE) $(DEP_CPP_EDREA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"


"$(INTDIR)\edreact.obj" : $(SOURCE) $(DEP_CPP_EDREA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"


"$(INTDIR)\edreact.obj" : $(SOURCE) $(DEP_CPP_EDREA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"


"$(INTDIR)\edreact.obj" : $(SOURCE) $(DEP_CPP_EDREA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MkrEnti.cpp
DEP_CPP_MKREN=\
	".\MkrEnti.h"\
	

!IF  "$(CFG)" == "clonemsg - Win32 Direct"


"$(INTDIR)\MkrEnti.obj" : $(SOURCE) $(DEP_CPP_MKREN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict SoftPointer"


"$(INTDIR)\MkrEnti.obj" : $(SOURCE) $(DEP_CPP_MKREN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 ExtDict HardPointer"


"$(INTDIR)\MkrEnti.obj" : $(SOURCE) $(DEP_CPP_MKREN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD SoftPointer"


"$(INTDIR)\MkrEnti.obj" : $(SOURCE) $(DEP_CPP_MKREN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "clonemsg - Win32 NOD HardPointer"


"$(INTDIR)\MkrEnti.obj" : $(SOURCE) $(DEP_CPP_MKREN) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
