# Microsoft Developer Studio Project File - Name="NetSDKDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NetSDKDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NetSDKDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NetSDKDemo.mak" CFG="NetSDKDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NetSDKDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NetSDKDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NetSDKDemo - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /pdb:none /debug /machine:I386

!ELSEIF  "$(CFG)" == "NetSDKDemo - Win32 Debug"

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
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NetSDKDemo - Win32 Release"
# Name "NetSDKDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddDeviceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvanceBtnPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmCtrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioBroadcastDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoMaintenance.cpp
# End Source File
# Begin Source File

SOURCE=.\BSWndContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientState.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmBlind.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmDisk.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionArea.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionAreaBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmVlost.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigMainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.cpp
# End Source File
# Begin Source File

SOURCE=.\CycleChild.cpp
# End Source File
# Begin Source File

SOURCE=.\CycleMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\DDNS_QueryIP.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceWorkState.cpp
# End Source File
# Begin Source File

SOURCE=.\DevMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\DiskControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DownloadByTime.cpp
# End Source File
# Begin Source File

SOURCE=.\ExButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ExSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtPtzCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\NetSDKDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\NetSDKDemo.rc
# End Source File
# Begin Source File

SOURCE=.\NetSDKDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NetUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\NormalBtnPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayBackByTime.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayCtrlPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\PreviewParmsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PtzMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\PTZPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordCtrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RuntimeMsgPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveDataPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectPannel.cpp
# End Source File
# Begin Source File

SOURCE=.\setdeviceconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\SplitInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\TransCom.cpp
# End Source File
# Begin Source File

SOURCE=.\User_AddGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\User_AddUser.cpp
# End Source File
# Begin Source File

SOURCE=.\User_ModifyGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\User_ModifyPsw.cpp
# End Source File
# Begin Source File

SOURCE=.\User_ModifyUser.cpp
# End Source File
# Begin Source File

SOURCE=.\UserManage.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddDeviceDlg.h
# End Source File
# Begin Source File

SOURCE=.\AdvanceBtnPannel.h
# End Source File
# Begin Source File

SOURCE=.\AlarmCtrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\AudioBroadcastDlg.h
# End Source File
# Begin Source File

SOURCE=.\AutoMaintenance.h
# End Source File
# Begin Source File

SOURCE=.\BSWndContainer.h
# End Source File
# Begin Source File

SOURCE=.\ClientState.h
# End Source File
# Begin Source File

SOURCE=.\ColorPannel.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmAlarm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmBlind.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmDisk.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotion.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionArea.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmMotionAreaBlock.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarmVlost.h
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.h
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigMainDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.h
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.h
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.h
# End Source File
# Begin Source File

SOURCE=.\CycleChild.h
# End Source File
# Begin Source File

SOURCE=.\CycleMonitor.h
# End Source File
# Begin Source File

SOURCE=.\DDNS_QueryIP.h
# End Source File
# Begin Source File

SOURCE=.\DeviceWorkState.h
# End Source File
# Begin Source File

SOURCE=.\DevMgr.h
# End Source File
# Begin Source File

SOURCE=.\Depend\dhassistant.h
# End Source File
# Begin Source File

SOURCE=.\Depend\dhnetsdk.h
# End Source File
# Begin Source File

SOURCE=.\DiskControl.h
# End Source File
# Begin Source File

SOURCE=.\DownloadByTime.h
# End Source File
# Begin Source File

SOURCE=.\ExButton.h
# End Source File
# Begin Source File

SOURCE=.\ExSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ExtPtzCtrl.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\MessageText.h
# End Source File
# Begin Source File

SOURCE=.\MessageText_eng.h
# End Source File
# Begin Source File

SOURCE=.\NetSDKDemo.h
# End Source File
# Begin Source File

SOURCE=.\NetSDKDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\NetUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\NormalBtnPannel.h
# End Source File
# Begin Source File

SOURCE=.\PlayBackByTime.h
# End Source File
# Begin Source File

SOURCE=.\PlayCtrlPannel.h
# End Source File
# Begin Source File

SOURCE=.\PlayWnd.h
# End Source File
# Begin Source File

SOURCE=.\PreviewParmsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PtzMenu.h
# End Source File
# Begin Source File

SOURCE=.\PTZPannel.h
# End Source File
# Begin Source File

SOURCE=.\RanderManager.h
# End Source File
# Begin Source File

SOURCE=.\RecordCtrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RuntimeMsgPannel.h
# End Source File
# Begin Source File

SOURCE=.\SaveDataPannel.h
# End Source File
# Begin Source File

SOURCE=.\ScreenPannel.h
# End Source File
# Begin Source File

SOURCE=.\SearchRecord.h
# End Source File
# Begin Source File

SOURCE=.\SelectPannel.h
# End Source File
# Begin Source File

SOURCE=.\setdeviceconfig.h
# End Source File
# Begin Source File

SOURCE=.\SplitInfoDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemConfig.h
# End Source File
# Begin Source File

SOURCE=.\TransCom.h
# End Source File
# Begin Source File

SOURCE=.\User_AddGroup.h
# End Source File
# Begin Source File

SOURCE=.\User_AddUser.h
# End Source File
# Begin Source File

SOURCE=.\User_ModifyGroup.h
# End Source File
# Begin Source File

SOURCE=.\User_ModifyPsw.h
# End Source File
# Begin Source File

SOURCE=.\User_ModifyUser.h
# End Source File
# Begin Source File

SOURCE=.\UserManage.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\NetSDKDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\NetSDKDemo.rc2
# End Source File
# End Group
# Begin Group "sdklib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Depend\dhnetsdk.lib
# End Source File
# Begin Source File

SOURCE=.\Depend\dhconfigsdk.lib
# End Source File
# End Group
# End Target
# End Project
# Section NetSDKDemo : {55A0FD0C-E3F1-4647-8F67-5AC8B8EB0BF8}
# 	2:21:DefaultSinkHeaderFile:dhocxsystemset.h
# 	2:16:DefaultSinkClass:CDHOCXSYSTEMSET
# End Section
# Section NetSDKDemo : {AAA74029-3456-40ED-B7A5-DABEE636FB26}
# 	2:21:DefaultSinkHeaderFile:setdeviceconfig.h
# 	2:16:DefaultSinkClass:CSetDeviceConfig
# End Section
# Section NetSDKDemo : {34CE288C-B851-4F13-85B8-E878111D29D8}
# 	2:5:Class:CSetDeviceConfig
# 	2:10:HeaderFile:setdeviceconfig.h
# 	2:8:ImplFile:setdeviceconfig.cpp
# End Section
