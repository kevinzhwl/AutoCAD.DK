# Microsoft Developer Studio Project File - Name="arxdragdrop" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=arxdragdrop - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "arxdd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "arxdd.mak" CFG="arxdragdrop - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "arxdragdrop - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "arxdragdrop - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "arxdragdrop - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /D "ACRXAPP" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rxapi.lib acad.lib acedapi.lib acge15.lib acdb15.lib acutil15.lib acrx15.lib /nologo /subsystem:windows /dll /machine:I386 /out:".\arxdragdrop.arx" /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "arxdragdrop - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_AFXDLL" /D "ACRXAPP" /FR /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 rxapi.lib acad.lib acedapi.lib acge15.lib acdb15.lib acutil15.lib acrx15.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\arxdragdrop.arx" /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /pdb:none /force

!ENDIF 

# Begin Target

# Name "arxdragdrop - Win32 Release"
# Name "arxdragdrop - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\arxdragdrop.cpp
# End Source File
# Begin Source File

SOURCE=.\arxdragdrop.def
# End Source File
# Begin Source File

SOURCE=.\arxdraw.rc
# End Source File
# Begin Source File

SOURCE=.\arxdrawView.cpp
# End Source File
# Begin Source File

SOURCE=.\ArxSliderVw.cpp
# End Source File
# Begin Source File

SOURCE=.\dropsource.cpp
# End Source File
# Begin Source File

SOURCE=.\droptarget.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\arxdragdrop.h
# End Source File
# Begin Source File

SOURCE=.\arxdrawview.h
# End Source File
# Begin Source File

SOURCE=.\ArxSliderVw.h
# End Source File
# Begin Source File

SOURCE=.\dataobj.h
# End Source File
# Begin Source File

SOURCE=.\dropsource.h
# End Source File
# Begin Source File

SOURCE=.\Droptarget.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\arxdraw.ico
# End Source File
# Begin Source File

SOURCE=.\res\arxdraw.rc2
# End Source File
# Begin Source File

SOURCE=.\res\arxdrawDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
