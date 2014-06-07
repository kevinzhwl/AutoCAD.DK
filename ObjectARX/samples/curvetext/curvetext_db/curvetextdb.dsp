# Microsoft Developer Studio Project File - Name="curveText DB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=curveText DB - Win32 DBX Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "curveTextDB.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "curveTextDB.mak" CFG="curveText DB - Win32 DBX Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "curveText DB - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "curveText DB - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "curveText DB - Win32 DBX Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "curveText DB - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Output\Release"
# PROP Intermediate_Dir "intermediate\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\inc" /D "NDEBUG" /D "ACRXAPP" /D "RADPACK" /D "CURVETEXTDBX" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 acdb15.lib rxapi.lib acgiapi.lib acge15.lib acrx15.lib acutil15.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /machine:I386 /out:"..\Curvetext.dbx" /libpath:"..\..\..\lib"

!ELSEIF  "$(CFG)" == "curveText DB - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Output\Debug"
# PROP Intermediate_Dir "intermediate\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /D "_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "ACRXAPP" /D "CURVETEXTDBX" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 acdb15.lib rxapi.lib acgiapi.lib acge15.lib acrx15.lib acutil15.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /out:"..\Curvetext.dbx" /pdbtype:sept /libpath:"..\..\..\lib"
# SUBTRACT LINK32 /map /nodefaultlib

!ELSEIF  "$(CFG)" == "curveText DB - Win32 DBX Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "curveText_DB___Win32_DBX_Debug"
# PROP BASE Intermediate_Dir "curveText_DB___Win32_DBX_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DBX_Debug"
# PROP Intermediate_Dir "DBX_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "..\..\..\inc" /D "_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "ACRXAPP" /D "CURVETEXTDBX" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "D:\ObjectDBX\inc" /D "_DEBUG" /D "_WINDLL" /D "_AFXDLL" /D "ACRXAPP" /D "CURVETEXTDBX" /D "WIN32" /D "_WINDOWS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 acad.lib acdb15.lib rxapi.lib acgiapi.lib acge15.lib acrx15.lib acutil15.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /out:"D:\Program Files\AutoCAD T\\Curvetext.dbx" /pdbtype:sept /libpath:"..\..\..\lib"
# SUBTRACT BASE LINK32 /map /nodefaultlib
# ADD LINK32 acdb15.lib rxapi.lib acgiapi.lib acge15.lib acrx15.lib acutil15.lib /nologo /base:"0x1c000000" /subsystem:windows /dll /debug /machine:I386 /out:"D:\ObjectDBX\Release\Curvetext.dbx" /pdbtype:sept /libpath:"D:\ObjectDBX\lib"
# SUBTRACT LINK32 /map /nodefaultlib

!ENDIF 

# Begin Target

# Name "curveText DB - Win32 Release"
# Name "curveText DB - Win32 Debug"
# Name "curveText DB - Win32 DBX Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp def"
# Begin Source File

SOURCE=.\curveText.cpp
# End Source File
# Begin Source File

SOURCE=.\CurveTextDB.def
# End Source File
# Begin Source File

SOURCE=.\curvetextIterator.cpp

!IF  "$(CFG)" == "curveText DB - Win32 Release"

!ELSEIF  "$(CFG)" == "curveText DB - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "curveText DB - Win32 DBX Debug"

# ADD BASE CPP /Yu
# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAIN.CPP

!IF  "$(CFG)" == "curveText DB - Win32 Release"

!ELSEIF  "$(CFG)" == "curveText DB - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "curveText DB - Win32 DBX Debug"

# ADD BASE CPP /Yu
# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp

!IF  "$(CFG)" == "curveText DB - Win32 Release"

!ELSEIF  "$(CFG)" == "curveText DB - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "curveText DB - Win32 DBX Debug"

# ADD BASE CPP /Yu
# ADD CPP /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CurveText.h
# End Source File
# Begin Source File

SOURCE=.\curvetextIterator.h
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\Utils.h
# End Source File
# End Group
# End Target
# End Project
