# Microsoft Developer Studio Project File - Name="ClientDemo5" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ClientDemo5 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo5.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo5.mak" CFG="ClientDemo5 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientDemo5 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo5 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientDemo5 - Win32 Release"

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

!ELSEIF  "$(CFG)" == "ClientDemo5 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dhnetsdk.lib dhconfigsdk.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/ClientDemo5D.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ClientDemo5 - Win32 Release"
# Name "ClientDemo5 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlarmInputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmShelter.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmVLostDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Common.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionArea.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionAreaBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigChannelEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigCover.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigFTP.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigFTPEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigFTPMain.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigNetworkMulticastAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigStrategy.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigVideoIn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\SRC\dhconfigsdk\dhconfigsdk.h
# End Source File
# Begin Source File

SOURCE=.\DlgChn.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDVR.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPC.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMsgHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\DriveRecordChn.cpp
# End Source File
# Begin Source File

SOURCE=.\IPFileterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MacFilteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StrategyDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\StrategyEncryption.cpp
# End Source File
# Begin Source File

SOURCE=.\StrategyTrans.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlarmInputDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmMotion.h
# End Source File
# Begin Source File

SOURCE=.\AlarmShelter.h
# End Source File
# Begin Source File

SOURCE=.\AlarmVLostDlg.h
# End Source File
# Begin Source File

SOURCE=.\AreaDraw.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ComConstants.h
# End Source File
# Begin Source File

SOURCE=.\Common.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionArea.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionAreaBlock.h
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.h
# End Source File
# Begin Source File

SOURCE=.\ConfigChannelEx.h
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigCover.h
# End Source File
# Begin Source File

SOURCE=.\ConfigFile.h
# End Source File
# Begin Source File

SOURCE=.\ConfigFTP.h
# End Source File
# Begin Source File

SOURCE=.\ConfigFTPEx.h
# End Source File
# Begin Source File

SOURCE=.\ConfigFTPMain.h
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.h
# End Source File
# Begin Source File

SOURCE=.\ConfigNetworkMulticastAdd.h
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.h
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.h
# End Source File
# Begin Source File

SOURCE=.\ConfigStrategy.h
# End Source File
# Begin Source File

SOURCE=.\ConfigVideoIn.h
# End Source File
# Begin Source File

SOURCE=.\dhassistant.h
# End Source File
# Begin Source File

SOURCE=.\dhconfigsdk.h
# End Source File
# Begin Source File

SOURCE=.\dhnetsdk.h
# End Source File
# Begin Source File

SOURCE=.\DlgChn.h
# End Source File
# Begin Source File

SOURCE=.\DlgDVR.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPC.h
# End Source File
# Begin Source File

SOURCE=.\DlgMsgHandle.h
# End Source File
# Begin Source File

SOURCE=.\DriveRecordChn.h
# End Source File
# Begin Source File

SOURCE=.\IPFileterDlg.h
# End Source File
# Begin Source File

SOURCE=.\MacFilteDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StrategyDownload.h
# End Source File
# Begin Source File

SOURCE=.\StrategyEncryption.h
# End Source File
# Begin Source File

SOURCE=.\StrategyTrans.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ClientDemo5.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo5.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\langchn.ini
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
