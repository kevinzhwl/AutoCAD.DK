# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=packngo - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to packngo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "packngo - Win32 Release" && "$(CFG)" !=\
 "packngo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "packngovc4x.mak" CFG="packngo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "packngo - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "packngo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "packngo - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "packngo - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\"
# PROP Intermediate_Dir ".\release"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\release

ALL : "$(OUTDIR)\packngo.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\pack.res"
	-@erase "$(INTDIR)\packcore.obj"
	-@erase "$(INTDIR)\packdlg.obj"
	-@erase "$(INTDIR)\packutil.obj"
	-@erase "$(INTDIR)\pathdlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\packngo.arx"
	-@erase "$(OUTDIR)\packngo.exp"
	-@erase "$(OUTDIR)\packngo.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/packngovc4x.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\.\release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/pack.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/packngovc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib ..\..\lib\rxapi.lib ..\..\lib\libacge.lib ..\..\lib\ism.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /machine:I386 /out:".\packngo.arx"
LINK32_FLAGS=..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib\
 ..\..\lib\rxapi.lib ..\..\lib\libacge.lib ..\..\lib\ism.lib /nologo\
 /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)/packngo.pdb" /machine:I386 /def:".\pack.def"\
 /out:"$(OUTDIR)/packngo.arx" /implib:"$(OUTDIR)/packngo.lib" 
DEF_FILE= \
	".\pack.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\pack.res" \
	"$(INTDIR)\packcore.obj" \
	"$(INTDIR)\packdlg.obj" \
	"$(INTDIR)\packutil.obj" \
	"$(INTDIR)\pathdlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\packngo.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "packngo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\"
# PROP Intermediate_Dir ".\debug"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\debug

ALL : "$(OUTDIR)\packngo.arx"

CLEAN : 
	-@erase "$(INTDIR)\arxmfctmpl.obj"
	-@erase "$(INTDIR)\pack.res"
	-@erase "$(INTDIR)\packcore.obj"
	-@erase "$(INTDIR)\packdlg.obj"
	-@erase "$(INTDIR)\packutil.obj"
	-@erase "$(INTDIR)\pathdlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\packngo.arx"
	-@erase "$(OUTDIR)\packngo.exp"
	-@erase "$(OUTDIR)\packngo.ilk"
	-@erase "$(OUTDIR)\packngo.lib"
	-@erase "$(OUTDIR)\packngo.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\inc" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/packngovc4x.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\.\debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/pack.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/packngovc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib ..\..\lib\rxapi.lib ..\..\lib\libacge.lib ..\..\lib\ism.lib mfc42.lib mfcs42.lib MSVCRT.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib advapi32.lib shell32.lib comctl32.lib uuid.lib oledlg.lib ole32.lib olepro32.lib oleaut32.lib OLDNAMES.lib /nologo /base:0x1c000000 /entry:"DllEntryPoint@12" /subsystem:windows /dll /debug /machine:I386 /nodefaultlib /out:".\packngo.arx"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=..\..\lib\acad.lib ..\..\lib\acedapi.lib ..\..\lib\acgiapi.lib\
 ..\..\lib\rxapi.lib ..\..\lib\libacge.lib ..\..\lib\ism.lib mfc42.lib\
 mfcs42.lib MSVCRT.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib\
 winspool.lib advapi32.lib shell32.lib comctl32.lib uuid.lib oledlg.lib\
 ole32.lib olepro32.lib oleaut32.lib OLDNAMES.lib /nologo /base:0x1c000000\
 /entry:"DllEntryPoint@12" /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/packngo.pdb" /debug /machine:I386 /nodefaultlib\
 /def:".\pack.def" /out:"$(OUTDIR)/packngo.arx" /implib:"$(OUTDIR)/packngo.lib" 
DEF_FILE= \
	".\pack.def"
LINK32_OBJS= \
	"$(INTDIR)\arxmfctmpl.obj" \
	"$(INTDIR)\pack.res" \
	"$(INTDIR)\packcore.obj" \
	"$(INTDIR)\packdlg.obj" \
	"$(INTDIR)\packutil.obj" \
	"$(INTDIR)\pathdlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\packngo.arx" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "packngo - Win32 Release"
# Name "packngo - Win32 Debug"

!IF  "$(CFG)" == "packngo - Win32 Release"

!ELSEIF  "$(CFG)" == "packngo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\pack.def

!IF  "$(CFG)" == "packngo - Win32 Release"

!ELSEIF  "$(CFG)" == "packngo - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\pack.rc
DEP_RSC_PACK_=\
	".\pack.bmp"\
	".\resource.hm"\
	

"$(INTDIR)\pack.res" : $(SOURCE) $(DEP_RSC_PACK_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\packcore.cpp
DEP_CPP_PACKC=\
	"..\..\inc\accmd.h"\
	"..\..\inc\acdb.h"\
	"..\..\inc\aced.h"\
	"..\..\inc\acgi.h"\
	"..\..\inc\actrans.h"\
	"..\..\inc\adesk.h"\
	"..\..\inc\adeskabb.h"\
	"..\..\inc\ads.h"\
	"..\..\inc\adscodes.h"\
	"..\..\inc\adsdef.h"\
	"..\..\inc\adslib.h"\
	"..\..\inc\comsys.h"\
	"..\..\inc\dbaudita.h"\
	"..\..\inc\dbboiler.h"\
	"..\..\inc\dbcurve.h"\
	"..\..\inc\dbdate.h"\
	"..\..\inc\dbdict.h"\
	"..\..\inc\dbelipse.h"\
	"..\..\inc\dbents.h"\
	"..\..\inc\dbfiler.h"\
	"..\..\inc\dbhandle.h"\
	"..\..\inc\dbid.h"\
	"..\..\inc\dbid_ops.h"\
	"..\..\inc\dbidapps.h"\
	"..\..\inc\dbidar.h"\
	"..\..\inc\dbimage.h"\
	"..\..\inc\dbintar.h"\
	"..\..\inc\dbjig.h"\
	"..\..\inc\dbmain.h"\
	"..\..\inc\dbmtext.h"\
	"..\..\inc\dbpl.h"\
	"..\..\inc\dbproxy.h"\
	"..\..\inc\dbptrar.h"\
	"..\..\inc\dbsubeid.h"\
	"..\..\inc\dbsymtb.h"\
	"..\..\inc\gearc2d.h"\
	"..\..\inc\gearc3d.h"\
	"..\..\inc\gebndpln.h"\
	"..\..\inc\gecurv2d.h"\
	"..\..\inc\gecurv3d.h"\
	"..\..\inc\gedblar.h"\
	"..\..\inc\gedll.h"\
	"..\..\inc\geent2d.h"\
	"..\..\inc\geent3d.h"\
	"..\..\inc\gegbl.h"\
	"..\..\inc\geintrvl.h"\
	"..\..\inc\gekvec.h"\
	"..\..\inc\gelent2d.h"\
	"..\..\inc\gelent3d.h"\
	"..\..\inc\gelibver.h"\
	"..\..\inc\geline2d.h"\
	"..\..\inc\geline3d.h"\
	"..\..\inc\gelnsg2d.h"\
	"..\..\inc\gelnsg3d.h"\
	"..\..\inc\gemat2d.h"\
	"..\..\inc\gemat3d.h"\
	"..\..\inc\gepent2d.h"\
	"..\..\inc\gepent3d.h"\
	"..\..\inc\geplanar.h"\
	"..\..\inc\geplane.h"\
	"..\..\inc\geplin2d.h"\
	"..\..\inc\gepnt2d.h"\
	"..\..\inc\gepnt3d.h"\
	"..\..\inc\geponc2d.h"\
	"..\..\inc\geponc3d.h"\
	"..\..\inc\gept2dar.h"\
	"..\..\inc\gept3dar.h"\
	"..\..\inc\gescl3d.h"\
	"..\..\inc\gesent2d.h"\
	"..\..\inc\gesurf.h"\
	"..\..\inc\getol.h"\
	"..\..\inc\gevec2d.h"\
	"..\..\inc\gevec3d.h"\
	"..\..\inc\graph.h"\
	"..\..\inc\imgdef.h"\
	"..\..\inc\imgdefim.h"\
	"..\..\inc\imgent.h"\
	"..\..\inc\imgentim.h"\
	"..\..\inc\imgvars.h"\
	"..\..\inc\rxboiler.h"\
	"..\..\inc\rxclass.h"\
	"..\..\inc\rxcom.h"\
	"..\..\inc\rxdefs.h"\
	"..\..\inc\rxdict.h"\
	"..\..\inc\rxditer.h"\
	"..\..\inc\rxdlinkr.h"\
	"..\..\inc\rxiter.h"\
	"..\..\inc\rxnames.h"\
	"..\..\inc\rxobject.h"\
	"..\..\inc\rxsrvice.h"\
	"..\..\inc\rxsys.h"\
	"..\..\inc\xgraph.h"\
	".\packcore.h"\
	".\PackDlg.h"\
	".\packutil.h"\
	".\stdafx.h"\
	
NODEP_CPP_PACKC=\
	"..\..\inc\dbidinln.h"\
	"..\..\inc\heapagnt.h"\
	

"$(INTDIR)\packcore.obj" : $(SOURCE) $(DEP_CPP_PACKC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\packdlg.cpp
DEP_CPP_PACKD=\
	"..\..\inc\accmd.h"\
	"..\..\inc\acdb.h"\
	"..\..\inc\aced.h"\
	"..\..\inc\acgi.h"\
	"..\..\inc\actrans.h"\
	"..\..\inc\adesk.h"\
	"..\..\inc\adeskabb.h"\
	"..\..\inc\ads.h"\
	"..\..\inc\adscodes.h"\
	"..\..\inc\adsdef.h"\
	"..\..\inc\adslib.h"\
	"..\..\inc\comsys.h"\
	"..\..\inc\dbaudita.h"\
	"..\..\inc\dbboiler.h"\
	"..\..\inc\dbcurve.h"\
	"..\..\inc\dbdate.h"\
	"..\..\inc\dbdict.h"\
	"..\..\inc\dbelipse.h"\
	"..\..\inc\dbents.h"\
	"..\..\inc\dbfiler.h"\
	"..\..\inc\dbhandle.h"\
	"..\..\inc\dbid.h"\
	"..\..\inc\dbid_ops.h"\
	"..\..\inc\dbidapps.h"\
	"..\..\inc\dbidar.h"\
	"..\..\inc\dbimage.h"\
	"..\..\inc\dbintar.h"\
	"..\..\inc\dbjig.h"\
	"..\..\inc\dbmain.h"\
	"..\..\inc\dbmtext.h"\
	"..\..\inc\dbpl.h"\
	"..\..\inc\dbproxy.h"\
	"..\..\inc\dbptrar.h"\
	"..\..\inc\dbsubeid.h"\
	"..\..\inc\dbsymtb.h"\
	"..\..\inc\gearc2d.h"\
	"..\..\inc\gearc3d.h"\
	"..\..\inc\gebndpln.h"\
	"..\..\inc\gecurv2d.h"\
	"..\..\inc\gecurv3d.h"\
	"..\..\inc\gedblar.h"\
	"..\..\inc\gedll.h"\
	"..\..\inc\geent2d.h"\
	"..\..\inc\geent3d.h"\
	"..\..\inc\gegbl.h"\
	"..\..\inc\geintrvl.h"\
	"..\..\inc\gekvec.h"\
	"..\..\inc\gelent2d.h"\
	"..\..\inc\gelent3d.h"\
	"..\..\inc\gelibver.h"\
	"..\..\inc\geline2d.h"\
	"..\..\inc\geline3d.h"\
	"..\..\inc\gelnsg2d.h"\
	"..\..\inc\gelnsg3d.h"\
	"..\..\inc\gemat2d.h"\
	"..\..\inc\gemat3d.h"\
	"..\..\inc\gepent2d.h"\
	"..\..\inc\gepent3d.h"\
	"..\..\inc\geplanar.h"\
	"..\..\inc\geplane.h"\
	"..\..\inc\geplin2d.h"\
	"..\..\inc\gepnt2d.h"\
	"..\..\inc\gepnt3d.h"\
	"..\..\inc\geponc2d.h"\
	"..\..\inc\geponc3d.h"\
	"..\..\inc\gept2dar.h"\
	"..\..\inc\gept3dar.h"\
	"..\..\inc\gescl3d.h"\
	"..\..\inc\gesent2d.h"\
	"..\..\inc\gesurf.h"\
	"..\..\inc\getol.h"\
	"..\..\inc\gevec2d.h"\
	"..\..\inc\gevec3d.h"\
	"..\..\inc\graph.h"\
	"..\..\inc\imgdef.h"\
	"..\..\inc\imgdefim.h"\
	"..\..\inc\imgent.h"\
	"..\..\inc\imgentim.h"\
	"..\..\inc\imgvars.h"\
	"..\..\inc\rxboiler.h"\
	"..\..\inc\rxclass.h"\
	"..\..\inc\rxcom.h"\
	"..\..\inc\rxdefs.h"\
	"..\..\inc\rxdict.h"\
	"..\..\inc\rxditer.h"\
	"..\..\inc\rxdlinkr.h"\
	"..\..\inc\rxiter.h"\
	"..\..\inc\rxnames.h"\
	"..\..\inc\rxobject.h"\
	"..\..\inc\rxsrvice.h"\
	"..\..\inc\rxsys.h"\
	"..\..\inc\xgraph.h"\
	".\packcore.h"\
	".\PackDlg.h"\
	".\packutil.h"\
	".\pathdlg.h"\
	".\resource.hm"\
	".\resourcehelper.h"\
	".\stdafx.h"\
	
NODEP_CPP_PACKD=\
	"..\..\inc\dbidinln.h"\
	"..\..\inc\heapagnt.h"\
	

"$(INTDIR)\packdlg.obj" : $(SOURCE) $(DEP_CPP_PACKD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\packutil.cpp
DEP_CPP_PACKU=\
	".\packcore.h"\
	".\packutil.h"\
	".\stdafx.h"\
	

"$(INTDIR)\packutil.obj" : $(SOURCE) $(DEP_CPP_PACKU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\pathdlg.cpp
DEP_CPP_PATHD=\
	".\pathdlg.h"\
	".\stdafx.h"\
	

"$(INTDIR)\pathdlg.obj" : $(SOURCE) $(DEP_CPP_PATHD) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\arxmfctmpl.cpp
DEP_CPP_ARXMF=\
	"..\..\inc\accmd.h"\
	"..\..\inc\acdb.h"\
	"..\..\inc\aced.h"\
	"..\..\inc\adesk.h"\
	"..\..\inc\ads.h"\
	"..\..\inc\adsdef.h"\
	"..\..\inc\comsys.h"\
	"..\..\inc\dbaudita.h"\
	"..\..\inc\dbboiler.h"\
	"..\..\inc\dbfiler.h"\
	"..\..\inc\dbhandle.h"\
	"..\..\inc\dbid.h"\
	"..\..\inc\dbid_ops.h"\
	"..\..\inc\dbidapps.h"\
	"..\..\inc\dbidar.h"\
	"..\..\inc\dbintar.h"\
	"..\..\inc\dbjig.h"\
	"..\..\inc\dbmain.h"\
	"..\..\inc\dbptrar.h"\
	"..\..\inc\dbsubeid.h"\
	"..\..\inc\gecurv3d.h"\
	"..\..\inc\gedblar.h"\
	"..\..\inc\gedll.h"\
	"..\..\inc\geent2d.h"\
	"..\..\inc\geent3d.h"\
	"..\..\inc\gegbl.h"\
	"..\..\inc\geintrvl.h"\
	"..\..\inc\gelent3d.h"\
	"..\..\inc\gelibver.h"\
	"..\..\inc\geline3d.h"\
	"..\..\inc\gepent3d.h"\
	"..\..\inc\gepnt2d.h"\
	"..\..\inc\gepnt3d.h"\
	"..\..\inc\geponc3d.h"\
	"..\..\inc\gept3dar.h"\
	"..\..\inc\gescl3d.h"\
	"..\..\inc\getol.h"\
	"..\..\inc\gevec2d.h"\
	"..\..\inc\gevec3d.h"\
	"..\..\inc\rxboiler.h"\
	"..\..\inc\rxclass.h"\
	"..\..\inc\rxcom.h"\
	"..\..\inc\rxdefs.h"\
	"..\..\inc\rxdict.h"\
	"..\..\inc\rxditer.h"\
	"..\..\inc\rxdlinkr.h"\
	"..\..\inc\rxiter.h"\
	"..\..\inc\rxnames.h"\
	"..\..\inc\rxobject.h"\
	"..\..\inc\rxsrvice.h"\
	"..\..\inc\rxsys.h"\
	".\resourcehelper.h"\
	".\stdafx.h"\
	
NODEP_CPP_ARXMF=\
	"..\..\inc\dbidinln.h"\
	"..\..\inc\heapagnt.h"\
	

"$(INTDIR)\arxmfctmpl.obj" : $(SOURCE) $(DEP_CPP_ARXMF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
