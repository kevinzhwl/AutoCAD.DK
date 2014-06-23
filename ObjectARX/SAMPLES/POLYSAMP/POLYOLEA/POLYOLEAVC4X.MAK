# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=polyolea - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to polyolea - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "polyolea - Win32 Release" && "$(CFG)" !=\
 "polyolea - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "polyoleavc4x.mak" CFG="polyolea - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "polyolea - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "polyolea - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "polyolea - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "polyolea - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\"
# PROP Intermediate_Dir ".\release"
OUTDIR=.
INTDIR=.\release

ALL : "$(OUTDIR)\polyolea.dll" "$(OUTDIR)\polyolea.tlb"

CLEAN : 
	-@erase "$(INTDIR)\cpoly.obj"
	-@erase "$(INTDIR)\cpolyapp.obj"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\server.obj"
	-@erase "$(OUTDIR)\polyolea.dll"
	-@erase "$(OUTDIR)\polyolea.exp"
	-@erase "$(OUTDIR)\polyolea.lib"
	-@erase ".\polyolea.h"
	-@erase ".\polyolea.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS"\
 /Fp"$(INTDIR)/polyoleavc4x.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\.\release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/polyoleavc4x.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /machine:I386
# ADD LINK32 ..\polysamp.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acad.lib ..\..\..\lib\libacge.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\acgiapi.lib /nologo /base:0x1c000000 /subsystem:windows /dll /machine:I386 /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib" /out:".\polyolea.dll"
LINK32_FLAGS=..\polysamp.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acad.lib\
 ..\..\..\lib\libacge.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\acgiapi.lib\
 /nologo /base:0x1c000000 /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/polyolea.pdb" /machine:I386 /nodefaultlib:"libcmtd.lib"\
 /nodefaultlib:"msvcrtd.lib" /def:".\polyolea.def" /out:"$(OUTDIR)/polyolea.dll"\
 /implib:"$(OUTDIR)/polyolea.lib" 
DEF_FILE= \
	".\polyolea.def"
LINK32_OBJS= \
	"$(INTDIR)\cpoly.obj" \
	"$(INTDIR)\cpolyapp.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\server.obj"

"$(OUTDIR)\polyolea.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\"
# PROP Intermediate_Dir ".\debug"
OUTDIR=.
INTDIR=.\debug

ALL : "$(OUTDIR)\polyolea.dll" "$(OUTDIR)\polyolea.tlb"\
 "$(OUTDIR)\polyoleavc4x.bsc"

CLEAN : 
	-@erase "$(INTDIR)\cpoly.obj"
	-@erase "$(INTDIR)\cpoly.sbr"
	-@erase "$(INTDIR)\cpolyapp.obj"
	-@erase "$(INTDIR)\cpolyapp.sbr"
	-@erase "$(INTDIR)\guid.obj"
	-@erase "$(INTDIR)\guid.sbr"
	-@erase "$(INTDIR)\server.obj"
	-@erase "$(INTDIR)\server.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\polyolea.dll"
	-@erase "$(OUTDIR)\polyolea.exp"
	-@erase "$(OUTDIR)\polyolea.ilk"
	-@erase "$(OUTDIR)\polyolea.lib"
	-@erase "$(OUTDIR)\polyolea.pdb"
	-@erase "$(OUTDIR)\polyoleavc4x.bsc"
	-@erase ".\polyolea.h"
	-@erase ".\polyolea.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "POLYSAMP" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Fr /YX /c
CPP_PROJ=/nologo /MD /W3 /Gm /GX /Zi /Od /I "..\..\..\inc" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "ACRXAPP" /D "RADPACK" /D "POLYSAMP" /D "_WINDLL" /D\
 "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/polyoleavc4x.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\.\debug/
CPP_SBRS=.\.\debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/polyoleavc4x.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cpoly.sbr" \
	"$(INTDIR)\cpolyapp.sbr" \
	"$(INTDIR)\guid.sbr" \
	"$(INTDIR)\server.sbr"

"$(OUTDIR)\polyoleavc4x.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ..\polysamp.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acad.lib ..\..\..\lib\libacge.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\acgiapi.lib /nologo /base:0x1c000000 /subsystem:windows /dll /debug /machine:I386 /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib" /out:".\polyolea.dll"
LINK32_FLAGS=..\polysamp.lib ..\..\..\lib\rxapi.lib ..\..\..\lib\acad.lib\
 ..\..\..\lib\libacge.lib ..\..\..\lib\acedapi.lib ..\..\..\lib\acgiapi.lib\
 /nologo /base:0x1c000000 /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/polyolea.pdb" /debug /machine:I386 /nodefaultlib:"libcmtd.lib"\
 /nodefaultlib:"msvcrtd.lib" /def:".\polyolea.def" /out:"$(OUTDIR)/polyolea.dll"\
 /implib:"$(OUTDIR)/polyolea.lib" 
DEF_FILE= \
	".\polyolea.def"
LINK32_OBJS= \
	"$(INTDIR)\cpoly.obj" \
	"$(INTDIR)\cpolyapp.obj" \
	"$(INTDIR)\guid.obj" \
	"$(INTDIR)\server.obj"

"$(OUTDIR)\polyolea.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "polyolea - Win32 Release"
# Name "polyolea - Win32 Debug"

!IF  "$(CFG)" == "polyolea - Win32 Release"

!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\polyolea.def

!IF  "$(CFG)" == "polyolea - Win32 Release"

!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\guid.cpp
DEP_CPP_GUID_=\
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
	"..\..\..\inc\entclsid.h"\
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
	"..\..\..\inc\interfac.h"\
	"..\..\..\inc\intermac.h"\
	"..\..\..\inc\iretapp.h"\
	"..\..\..\inc\oapinit.h"\
	"..\..\..\inc\oleaprot.h"\
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
	".\cpoly.h"\
	".\cpolyapp.h"\
	".\polyolea.h"\
	
NODEP_CPP_GUID_=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "polyolea - Win32 Release"


"$(INTDIR)\guid.obj" : $(SOURCE) $(DEP_CPP_GUID_) "$(INTDIR)" ".\polyolea.h"


!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"


"$(INTDIR)\guid.obj" : $(SOURCE) $(DEP_CPP_GUID_) "$(INTDIR)" ".\polyolea.h"

"$(INTDIR)\guid.sbr" : $(SOURCE) $(DEP_CPP_GUID_) "$(INTDIR)" ".\polyolea.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cpoly.cpp
DEP_CPP_CPOLY=\
	"..\..\..\inc\accmd.h"\
	"..\..\..\inc\acdb.h"\
	"..\..\..\inc\aced.h"\
	"..\..\..\inc\acestext.h"\
	"..\..\..\inc\adesk.h"\
	"..\..\..\inc\ads.h"\
	"..\..\..\inc\adsdef.h"\
	"..\..\..\inc\comsys.h"\
	"..\..\..\inc\dbaudita.h"\
	"..\..\..\inc\dbboiler.h"\
	"..\..\..\inc\dbcurve.h"\
	"..\..\..\inc\dbdate.h"\
	"..\..\..\inc\dbdict.h"\
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
	"..\..\..\inc\dbsymtb.h"\
	"..\..\..\inc\entclsid.h"\
	"..\..\..\inc\geassign.h"\
	"..\..\..\inc\gecurv3d.h"\
	"..\..\..\inc\gedblar.h"\
	"..\..\..\inc\gedll.h"\
	"..\..\..\inc\geent2d.h"\
	"..\..\..\inc\geent3d.h"\
	"..\..\..\inc\gegbl.h"\
	"..\..\..\inc\gegblabb.h"\
	"..\..\..\inc\geintrvl.h"\
	"..\..\..\inc\gelent3d.h"\
	"..\..\..\inc\gelibver.h"\
	"..\..\..\inc\geline3d.h"\
	"..\..\..\inc\gepent3d.h"\
	"..\..\..\inc\geplanar.h"\
	"..\..\..\inc\geplane.h"\
	"..\..\..\inc\gepnt2d.h"\
	"..\..\..\inc\gepnt3d.h"\
	"..\..\..\inc\geponc3d.h"\
	"..\..\..\inc\gept3dar.h"\
	"..\..\..\inc\gescl3d.h"\
	"..\..\..\inc\gesurf.h"\
	"..\..\..\inc\getol.h"\
	"..\..\..\inc\gevec2d.h"\
	"..\..\..\inc\gevec3d.h"\
	"..\..\..\inc\interfac.h"\
	"..\..\..\inc\intermac.h"\
	"..\..\..\inc\iretapp.h"\
	"..\..\..\inc\oleaprot.h"\
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
	"..\poly.h"\
	".\cpoly.h"\
	".\polyolea.h"\
	
NODEP_CPP_CPOLY=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "polyolea - Win32 Release"


"$(INTDIR)\cpoly.obj" : $(SOURCE) $(DEP_CPP_CPOLY) "$(INTDIR)" ".\polyolea.h"


!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"


"$(INTDIR)\cpoly.obj" : $(SOURCE) $(DEP_CPP_CPOLY) "$(INTDIR)" ".\polyolea.h"

"$(INTDIR)\cpoly.sbr" : $(SOURCE) $(DEP_CPP_CPOLY) "$(INTDIR)" ".\polyolea.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\polyolea.odl
DEP_MTL_POLYO=\
	".\polyenu.h"\
	

!IF  "$(CFG)" == "polyolea - Win32 Release"

# ADD MTL /h ".\polyolea.h"

BuildCmds= \
	$(MTL) /nologo /D "NDEBUG" /tlb "$(OUTDIR)/polyolea.tlb" /h ".\polyolea.h"\
 /win32 $(SOURCE) \
	

"$(OUTDIR)\polyolea.tlb" : $(SOURCE) $(DEP_MTL_POLYO) "$(OUTDIR)"
   $(BuildCmds)

"$(OUTDIR)\polyolea.h" : $(SOURCE) $(DEP_MTL_POLYO) "$(OUTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"

# ADD MTL /h ".\polyolea.h"

BuildCmds= \
	$(MTL) /nologo /D "_DEBUG" /tlb "$(OUTDIR)/polyolea.tlb" /h ".\polyolea.h"\
 /win32 $(SOURCE) \
	

"$(OUTDIR)\polyolea.tlb" : $(SOURCE) $(DEP_MTL_POLYO) "$(OUTDIR)"
   $(BuildCmds)

"$(OUTDIR)\polyolea.h" : $(SOURCE) $(DEP_MTL_POLYO) "$(OUTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\server.cpp
DEP_CPP_SERVE=\
	"..\..\..\inc\accmd.h"\
	"..\..\..\inc\acdb.h"\
	"..\..\..\inc\aced.h"\
	"..\..\..\inc\acestext.h"\
	"..\..\..\inc\adesk.h"\
	"..\..\..\inc\ads.h"\
	"..\..\..\inc\adsdef.h"\
	"..\..\..\inc\comsys.h"\
	"..\..\..\inc\dbaudita.h"\
	"..\..\..\inc\dbboiler.h"\
	"..\..\..\inc\dbcurve.h"\
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
	"..\..\..\inc\entclsid.h"\
	"..\..\..\inc\geassign.h"\
	"..\..\..\inc\gecurv3d.h"\
	"..\..\..\inc\gedblar.h"\
	"..\..\..\inc\gedll.h"\
	"..\..\..\inc\geent2d.h"\
	"..\..\..\inc\geent3d.h"\
	"..\..\..\inc\gegbl.h"\
	"..\..\..\inc\gegblabb.h"\
	"..\..\..\inc\geintrvl.h"\
	"..\..\..\inc\gelent3d.h"\
	"..\..\..\inc\gelibver.h"\
	"..\..\..\inc\geline3d.h"\
	"..\..\..\inc\gepent3d.h"\
	"..\..\..\inc\geplanar.h"\
	"..\..\..\inc\geplane.h"\
	"..\..\..\inc\gepnt2d.h"\
	"..\..\..\inc\gepnt3d.h"\
	"..\..\..\inc\geponc3d.h"\
	"..\..\..\inc\gept3dar.h"\
	"..\..\..\inc\gescl3d.h"\
	"..\..\..\inc\gesurf.h"\
	"..\..\..\inc\getol.h"\
	"..\..\..\inc\gevec2d.h"\
	"..\..\..\inc\gevec3d.h"\
	"..\..\..\inc\interfac.h"\
	"..\..\..\inc\intermac.h"\
	"..\..\..\inc\iretapp.h"\
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
	"..\..\..\inc\rxregsvc.h"\
	"..\..\..\inc\rxsrvice.h"\
	"..\..\..\inc\rxsys.h"\
	"..\poly.h"\
	".\cpoly.h"\
	".\cpolyapp.h"\
	".\polyolea.h"\
	
NODEP_CPP_SERVE=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "polyolea - Win32 Release"


"$(INTDIR)\server.obj" : $(SOURCE) $(DEP_CPP_SERVE) "$(INTDIR)" ".\polyolea.h"


!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"


"$(INTDIR)\server.obj" : $(SOURCE) $(DEP_CPP_SERVE) "$(INTDIR)" ".\polyolea.h"

"$(INTDIR)\server.sbr" : $(SOURCE) $(DEP_CPP_SERVE) "$(INTDIR)" ".\polyolea.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\cpolyapp.cpp
DEP_CPP_CPOLYA=\
	"..\..\..\inc\accmd.h"\
	"..\..\..\inc\acdb.h"\
	"..\..\..\inc\aced.h"\
	"..\..\..\inc\acestext.h"\
	"..\..\..\inc\adesk.h"\
	"..\..\..\inc\ads.h"\
	"..\..\..\inc\adsdef.h"\
	"..\..\..\inc\comsys.h"\
	"..\..\..\inc\dbaudita.h"\
	"..\..\..\inc\dbboiler.h"\
	"..\..\..\inc\dbcurve.h"\
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
	"..\..\..\inc\entclsid.h"\
	"..\..\..\inc\geassign.h"\
	"..\..\..\inc\gecurv3d.h"\
	"..\..\..\inc\gedblar.h"\
	"..\..\..\inc\gedll.h"\
	"..\..\..\inc\geent2d.h"\
	"..\..\..\inc\geent3d.h"\
	"..\..\..\inc\gegbl.h"\
	"..\..\..\inc\gegblabb.h"\
	"..\..\..\inc\geintrvl.h"\
	"..\..\..\inc\gelent3d.h"\
	"..\..\..\inc\gelibver.h"\
	"..\..\..\inc\geline3d.h"\
	"..\..\..\inc\gepent3d.h"\
	"..\..\..\inc\geplanar.h"\
	"..\..\..\inc\geplane.h"\
	"..\..\..\inc\gepnt2d.h"\
	"..\..\..\inc\gepnt3d.h"\
	"..\..\..\inc\geponc3d.h"\
	"..\..\..\inc\gept3dar.h"\
	"..\..\..\inc\gescl3d.h"\
	"..\..\..\inc\gesurf.h"\
	"..\..\..\inc\getol.h"\
	"..\..\..\inc\gevec2d.h"\
	"..\..\..\inc\gevec3d.h"\
	"..\..\..\inc\interfac.h"\
	"..\..\..\inc\intermac.h"\
	"..\..\..\inc\iretapp.h"\
	"..\..\..\inc\oleaprot.h"\
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
	"..\command.h"\
	"..\poly.h"\
	".\cpoly.h"\
	".\cpolyapp.h"\
	".\polyolea.h"\
	
NODEP_CPP_CPOLYA=\
	"..\..\..\inc\dbidinln.h"\
	"..\..\..\inc\heapagnt.h"\
	

!IF  "$(CFG)" == "polyolea - Win32 Release"


"$(INTDIR)\cpolyapp.obj" : $(SOURCE) $(DEP_CPP_CPOLYA) "$(INTDIR)"\
 ".\polyolea.h"


!ELSEIF  "$(CFG)" == "polyolea - Win32 Debug"


"$(INTDIR)\cpolyapp.obj" : $(SOURCE) $(DEP_CPP_CPOLYA) "$(INTDIR)"\
 ".\polyolea.h"

"$(INTDIR)\cpolyapp.sbr" : $(SOURCE) $(DEP_CPP_CPOLYA) "$(INTDIR)"\
 ".\polyolea.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
