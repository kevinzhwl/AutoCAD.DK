# Microsoft Developer Studio Project File - Name="AsdkBodyUi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AsdkBodyUi - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AsdkBodyUi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AsdkBodyUi.mak" CFG="AsdkBodyUi - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AsdkBodyUi - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AsdkBodyUi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AsdkBodyUi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX $(USRCFLAGS) /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Oy- /I "..\..\..\inc" /I "..\..\..\..\..\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /YX"stdarx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rxapi.lib ..\asdkbodyobj\release\asdkbodyobj.lib acutil15.lib acedapi.lib acad.lib acrx15.lib acge15.lib acdb15.lib asdkAmodeler.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\AsdkBodyUi.arx" /libpath:"..\..\..\lib" /libpath:"..\..\..\..\..\lib"

!ELSEIF  "$(CFG)" == "AsdkBodyUi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX $(USRCFLAGS) /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /I "..\..\..\..\..\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /YX"stdarx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 rxapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\asdkbodyobj\debug\asdkbodyobj.lib acutil15.lib acedapi.lib acad.lib acrx15.lib acge15.lib acdb15.lib asdkAmodeler.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\AsdkBodyUi.arx" /libpath:"..\..\..\lib" /libpath:"..\..\..\..\..\lib"

!ENDIF 

# Begin Target

# Name "AsdkBodyUi - Win32 Release"
# Name "AsdkBodyUi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AsdkBodyUi.CPP
# End Source File
# Begin Source File

SOURCE=.\AsdkBodyUi.DEF
# End Source File
# Begin Source File

SOURCE=.\ERRORMSG.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AsdkBodyUi.H
# End Source File
# Begin Source File

SOURCE=.\ERRORMSG.H
# End Source File
# Begin Source File

SOURCE=.\stdarx.h
# End Source File
# End Group
# End Target
# End Project
