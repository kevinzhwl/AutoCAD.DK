# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=loadApp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to loadApp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "loadApp - Win32 Release" && "$(CFG)" !=\
 "loadApp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "loadappvc4x.mak" CFG="loadApp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "loadApp - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "loadApp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "loadApp - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "loadApp - Win32 Release"

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

ALL : ".\loadApp.arx"

CLEAN : 
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\LaMfcToolbar.obj"
	-@erase "$(INTDIR)\lispReactor.obj"
	-@erase "$(INTDIR)\loadApp.obj"
	-@erase "$(INTDIR)\loadApp.res"
	-@erase "$(INTDIR)\loadApp_main.obj"
	-@erase "$(INTDIR)\LoadAppDia.obj"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\TBHandler.obj"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(OUTDIR)\loadApp.exp"
	-@erase "$(OUTDIR)\loadApp.lib"
	-@erase ".\loadApp.arx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "_WINDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "_AFXDLL" /D\
 "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "_WINDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/loadappvc4x.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/loadApp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/loadappvc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\lib\Rxapi.lib ..\..\..\lib\Acedapi.lib ..\..\..\lib\Acad.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:".\loadApp.arx"
# SUBTRACT LINK32 /map /debug /force
LINK32_FLAGS=..\..\..\lib\Rxapi.lib ..\..\..\lib\Acedapi.lib\
 ..\..\..\lib\Acad.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/loadApp.pdb"\
 /machine:I386 /def:".\loadApp.def" /out:".\loadApp.arx"\
 /implib:"$(OUTDIR)/loadApp.lib" 
DEF_FILE= \
	".\loadApp.def"
LINK32_OBJS= \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\LaMfcToolbar.obj" \
	"$(INTDIR)\lispReactor.obj" \
	"$(INTDIR)\loadApp.obj" \
	"$(INTDIR)\loadApp.res" \
	"$(INTDIR)\loadApp_main.obj" \
	"$(INTDIR)\LoadAppDia.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\TBHandler.obj" \
	"$(INTDIR)\utils.obj"

".\loadApp.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"

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

ALL : ".\loadApp.arx" "$(OUTDIR)\loadappvc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\IniFile.sbr"
	-@erase "$(INTDIR)\LaMfcToolbar.obj"
	-@erase "$(INTDIR)\LaMfcToolbar.sbr"
	-@erase "$(INTDIR)\lispReactor.obj"
	-@erase "$(INTDIR)\lispReactor.sbr"
	-@erase "$(INTDIR)\loadApp.obj"
	-@erase "$(INTDIR)\loadApp.res"
	-@erase "$(INTDIR)\loadApp.sbr"
	-@erase "$(INTDIR)\loadApp_main.obj"
	-@erase "$(INTDIR)\loadApp_main.sbr"
	-@erase "$(INTDIR)\LoadAppDia.obj"
	-@erase "$(INTDIR)\LoadAppDia.sbr"
	-@erase "$(INTDIR)\Stdafx.obj"
	-@erase "$(INTDIR)\Stdafx.sbr"
	-@erase "$(INTDIR)\TBHandler.obj"
	-@erase "$(INTDIR)\TBHandler.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\loadApp.exp"
	-@erase "$(OUTDIR)\loadApp.lib"
	-@erase "$(OUTDIR)\loadApp.pdb"
	-@erase "$(OUTDIR)\loadappvc4x.bsc"
	-@erase ".\loadApp.arx"
	-@erase ".\loadApp.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# SUBTRACT CPP /u
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "_WINDLL" /D "_AFXDLL" /D\
 "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/loadappvc4x.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/loadApp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/loadappvc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\IniFile.sbr" \
	"$(INTDIR)\LaMfcToolbar.sbr" \
	"$(INTDIR)\lispReactor.sbr" \
	"$(INTDIR)\loadApp.sbr" \
	"$(INTDIR)\loadApp_main.sbr" \
	"$(INTDIR)\LoadAppDia.sbr" \
	"$(INTDIR)\Stdafx.sbr" \
	"$(INTDIR)\TBHandler.sbr" \
	"$(INTDIR)\utils.sbr"

"$(OUTDIR)\loadappvc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\..\lib\Rxapi.lib ..\..\..\lib\Acedapi.lib ..\..\..\lib\Acad.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /out:".\loadApp.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\..\lib\Rxapi.lib ..\..\..\lib\Acedapi.lib\
 ..\..\..\lib\Acad.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12"\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/loadApp.pdb" /debug\
 /machine:I386 /def:".\loadApp.def" /out:".\loadApp.arx"\
 /implib:"$(OUTDIR)/loadApp.lib" 
DEF_FILE= \
	".\loadApp.def"
LINK32_OBJS= \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\LaMfcToolbar.obj" \
	"$(INTDIR)\lispReactor.obj" \
	"$(INTDIR)\loadApp.obj" \
	"$(INTDIR)\loadApp.res" \
	"$(INTDIR)\loadApp_main.obj" \
	"$(INTDIR)\LoadAppDia.obj" \
	"$(INTDIR)\Stdafx.obj" \
	"$(INTDIR)\TBHandler.obj" \
	"$(INTDIR)\utils.obj"

".\loadApp.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "loadApp - Win32 Release"
# Name "loadApp - Win32 Debug"

!IF  "$(CFG)" == "loadApp - Win32 Release"

!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\utils.cpp
DEP_CPP_UTILS=\
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
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_UTILS=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\utils.obj" : $(SOURCE) $(DEP_CPP_UTILS) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\utils.obj" : $(SOURCE) $(DEP_CPP_UTILS) "$(INTDIR)"

"$(INTDIR)\utils.sbr" : $(SOURCE) $(DEP_CPP_UTILS) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\loadApp.cpp
DEP_CPP_LOADA=\
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
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_LOADA=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\loadApp.obj" : $(SOURCE) $(DEP_CPP_LOADA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\loadApp.obj" : $(SOURCE) $(DEP_CPP_LOADA) "$(INTDIR)"

"$(INTDIR)\loadApp.sbr" : $(SOURCE) $(DEP_CPP_LOADA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\loadApp.rc
DEP_RSC_LOADAP=\
	".\latoolba.bmp"\
	".\RES\MFCTEMPL.RC2"\
	

"$(INTDIR)\loadApp.res" : $(SOURCE) $(DEP_RSC_LOADAP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LoadAppDia.cpp
DEP_CPP_LOADAPP=\
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
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_LOADAPP=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\LoadAppDia.obj" : $(SOURCE) $(DEP_CPP_LOADAPP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\LoadAppDia.obj" : $(SOURCE) $(DEP_CPP_LOADAPP) "$(INTDIR)"

"$(INTDIR)\LoadAppDia.sbr" : $(SOURCE) $(DEP_CPP_LOADAPP) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "loadApp - Win32 Release"

!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Stdafx.cpp
DEP_CPP_STDAF=\
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
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_STDAF=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"

"$(INTDIR)\Stdafx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IniFile.cpp
DEP_CPP_INIFI=\
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
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_INIFI=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\IniFile.obj" : $(SOURCE) $(DEP_CPP_INIFI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\IniFile.obj" : $(SOURCE) $(DEP_CPP_INIFI) "$(INTDIR)"

"$(INTDIR)\IniFile.sbr" : $(SOURCE) $(DEP_CPP_INIFI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\loadApp.def

!IF  "$(CFG)" == "loadApp - Win32 Release"

!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LaMfcToolbar.cpp
DEP_CPP_LAMFC=\
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
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_LAMFC=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\LaMfcToolbar.obj" : $(SOURCE) $(DEP_CPP_LAMFC) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\LaMfcToolbar.obj" : $(SOURCE) $(DEP_CPP_LAMFC) "$(INTDIR)"

"$(INTDIR)\LaMfcToolbar.sbr" : $(SOURCE) $(DEP_CPP_LAMFC) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\loadApp_main.cpp
DEP_CPP_LOADAPP_=\
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
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\RXREGSVC.H"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_LOADAPP_=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\loadApp_main.obj" : $(SOURCE) $(DEP_CPP_LOADAPP_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\loadApp_main.obj" : $(SOURCE) $(DEP_CPP_LOADAPP_) "$(INTDIR)"

"$(INTDIR)\loadApp_main.sbr" : $(SOURCE) $(DEP_CPP_LOADAPP_) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TBHandler.cpp
DEP_CPP_TBHAN=\
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
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_TBHAN=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\TBHandler.obj" : $(SOURCE) $(DEP_CPP_TBHAN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\TBHandler.obj" : $(SOURCE) $(DEP_CPP_TBHAN) "$(INTDIR)"

"$(INTDIR)\TBHandler.sbr" : $(SOURCE) $(DEP_CPP_TBHAN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\lispReactor.cpp
DEP_CPP_LISPR=\
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
	"..\..\..\inc\rxnames.h"\
	"..\..\..\inc\rxobject.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	".\inifile.h"\
	".\lamfctoolbar.h"\
	".\lispreactor.h"\
	".\loadapp.h"\
	".\loadappdia.h"\
	".\stdafx.h"\
	".\tbhandler.h"\
	".\utils.h"\
	
NODEP_CPP_LISPR=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "loadApp - Win32 Release"


"$(INTDIR)\lispReactor.obj" : $(SOURCE) $(DEP_CPP_LISPR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "loadApp - Win32 Debug"


"$(INTDIR)\lispReactor.obj" : $(SOURCE) $(DEP_CPP_LISPR) "$(INTDIR)"

"$(INTDIR)\lispReactor.sbr" : $(SOURCE) $(DEP_CPP_LISPR) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
