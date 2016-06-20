# Microsoft Developer Studio Project File - Name="Video Analyse Configuration" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Video Analyse Configuration - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Video Analyse Configuration.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Video Analyse Configuration.mak" CFG="Video Analyse Configuration - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Video Analyse Configuration - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Video Analyse Configuration - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Video Analyse Configuration - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dhnetsdk.lib dhconfigsdk.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Video Analyse Configuration - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /pdb:"..\..\bin\Debug/Video Analyse Configuration.pdb" /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Video Analyse Configuration - Win32 Release"
# Name "Video Analyse Configuration - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ConfigAtmScene.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigCrossLineRule.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigCrossRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigFaceRule.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigModule.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigPasteRule.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigRioterRule.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigRules.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigTraffic.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigTrafficGateRule.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigWanderRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawObject.cpp
# End Source File
# Begin Source File

SOURCE=.\PictrueDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SceneShow.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=".\Video Analyse Configuration.cpp"
# End Source File
# Begin Source File

SOURCE=".\Video Analyse Configuration.rc"
# End Source File
# Begin Source File

SOURCE=".\Video Analyse ConfigurationDlg.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Common.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAtmScene.h
# End Source File
# Begin Source File

SOURCE=.\ConfigCrossLineRule.h
# End Source File
# Begin Source File

SOURCE=.\ConfigCrossRegion.h
# End Source File
# Begin Source File

SOURCE=.\ConfigFaceRule.h
# End Source File
# Begin Source File

SOURCE=.\ConfigModule.h
# End Source File
# Begin Source File

SOURCE=.\ConfigPasteRule.h
# End Source File
# Begin Source File

SOURCE=.\ConfigRioterRule.h
# End Source File
# Begin Source File

SOURCE=.\ConfigRules.h
# End Source File
# Begin Source File

SOURCE=.\ConfigTraffic.h
# End Source File
# Begin Source File

SOURCE=.\ConfigTrafficGateRule.h
# End Source File
# Begin Source File

SOURCE=.\ConfigWanderRule.h
# End Source File
# Begin Source File

SOURCE=.\DrawObject.h
# End Source File
# Begin Source File

SOURCE=.\PictrueDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SceneShow.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=".\Video Analyse Configuration.h"
# End Source File
# Begin Source File

SOURCE=".\Video Analyse ConfigurationDlg.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=".\res\Video Analyse Configuration.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Video Analyse Configuration.rc2"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\dhconfigsdk.lib
# End Source File
# Begin Source File

SOURCE=.\dhnetsdk.lib
# End Source File
# End Target
# End Project
