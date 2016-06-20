# Microsoft Developer Studio Project File - Name="ClientDemo3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ClientDemo3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo3.mak" CFG="ClientDemo3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientDemo3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientDemo3 - Win32 Release"

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
# ADD LINK32 dhnetsdk.lib dhplay.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ClientDemo3 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dhnetsdk.lib dhplay.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/ClientDemo.exe" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=regsvr32 /u /s DayTimePickSDK.ocx & regsvr32 /s DayTimePickSDK.ocx
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ClientDemo3 - Win32 Release"
# Name "ClientDemo3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChannelOneDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo3.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo3.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDemo3Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\daytimepicksdk.cpp
# End Source File
# Begin Source File

SOURCE=.\ExSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FourChannelsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaybackByFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaybackByTime.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaybackMulty.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChannelOneDialog.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo3.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo3Dlg.h
# End Source File
# Begin Source File

SOURCE=.\daytimepicksdk.h
# End Source File
# Begin Source File

SOURCE=.\ExSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FourChannelsDialog.h
# End Source File
# Begin Source File

SOURCE=.\PlaybackByFile.h
# End Source File
# Begin Source File

SOURCE=.\PlaybackByTime.h
# End Source File
# Begin Source File

SOURCE=.\PlaybackMulty.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ClientDemo3.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo3.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ClientDemo3 : {57CBF30F-3574-4DAF-89DA-E61510E0D91C}
# 	2:5:Class:CDayTimePick
# 	2:10:HeaderFile:daytimepick.h
# 	2:8:ImplFile:daytimepick.cpp
# End Section
# Section ClientDemo3 : {239852BA-EDB9-4A43-9DAC-43A585E1A130}
# 	2:21:DefaultSinkHeaderFile:daytimepicksdk.h
# 	2:16:DefaultSinkClass:CDayTimePickSDK
# End Section
# Section ClientDemo3 : {46C8CED7-C59E-430B-843C-92B2E803F296}
# 	2:5:Class:CDayTimePickSDK
# 	2:10:HeaderFile:daytimepicksdk.h
# 	2:8:ImplFile:daytimepicksdk.cpp
# End Section
# Section ClientDemo3 : {CD2D4B6A-F5BE-45AD-93BE-AC72FB797B00}
# 	2:21:DefaultSinkHeaderFile:daytimepick.h
# 	2:16:DefaultSinkClass:CDayTimePick
# End Section
