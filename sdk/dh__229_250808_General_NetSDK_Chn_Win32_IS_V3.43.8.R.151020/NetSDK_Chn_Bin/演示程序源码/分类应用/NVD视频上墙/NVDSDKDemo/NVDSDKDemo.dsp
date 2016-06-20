# Microsoft Developer Studio Project File - Name="NVDSDKDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NVDSDKDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NVDSDKDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NVDSDKDemo.mak" CFG="NVDSDKDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NVDSDKDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NVDSDKDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NVDSDKDemo - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dhnetsdk.lib Ws2_32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "NVDSDKDemo - Win32 Debug"

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
# ADD LINK32 dhnetsdk.lib Ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NVDSDKDemo - Win32 Release"
# Name "NVDSDKDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddDecoderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddDeviceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioTalkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DecodePolicyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DecoderInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DecTourDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DevByFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DevByTimeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ExSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\NVDSDKDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\NVDSDKDemo.rc
# End Source File
# Begin Source File

SOURCE=.\NVDSDKDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PannelDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\PannelEncoder.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayBackProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadWriteMutex.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchTVDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowChannelStateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TourCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\TVAdjustdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoOutDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddDecoderDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddDeviceDlg.h
# End Source File
# Begin Source File

SOURCE=.\AudioTalkDlg.h
# End Source File
# Begin Source File

SOURCE=.\DecodePolicyDlg.h
# End Source File
# Begin Source File

SOURCE=.\DecoderInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\DecTourDlg.h
# End Source File
# Begin Source File

SOURCE=.\DevByFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\DevByTimeDlg.h
# End Source File
# Begin Source File

SOURCE=.\dhnetsdk.h
# End Source File
# Begin Source File

SOURCE=.\ExSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\NVDSDKDemo.h
# End Source File
# Begin Source File

SOURCE=.\NVDSDKDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\PannelDecoder.h
# End Source File
# Begin Source File

SOURCE=.\PannelEncoder.h
# End Source File
# Begin Source File

SOURCE=.\PlayBackProcess.h
# End Source File
# Begin Source File

SOURCE=.\ReadWriteMutex.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchTVDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShowChannelStateDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TourCfg.h
# End Source File
# Begin Source File

SOURCE=.\TVAdjustdlg.h
# End Source File
# Begin Source File

SOURCE=.\VideoOutDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\NVDSDKDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\NVDSDKDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\playback2.bmp
# End Source File
# End Group
# Begin Group "VideoWindow"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\MonitorWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\include\MonitorWnd.h
# End Source File
# Begin Source File

SOURCE=.\include\PlayWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\include\PlayWnd.h
# End Source File
# Begin Source File

SOURCE=.\include\VideoWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\include\VideoWindow.h
# End Source File
# Begin Source File

SOURCE=.\include\WndContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\include\WndContainer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
