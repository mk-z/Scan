# Microsoft Developer Studio Project File - Name="AlarmDevice" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AlarmDevice - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AlarmDevice.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AlarmDevice.mak" CFG="AlarmDevice - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AlarmDevice - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AlarmDevice - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AlarmDevice - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Bin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ELSEIF  "$(CFG)" == "AlarmDevice - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Bin/Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Bin"
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
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Bin/AlarmDevice_d.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AlarmDevice - Win32 Release"
# Name "AlarmDevice - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Control&Query"

# PROP Default_Filter ""
# End Group
# Begin Group "Config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgCfgAirCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmCenter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmChassisIntrusion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmExAlarmBox.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmOut.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmPowerFault.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmSlotBond.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmSubSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmUrgency.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAnalogAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAutoMaintain.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgBatteryLowPower.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgExAlarmInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgExAlarmOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgGuard.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgIPConflict.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgLocales.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgMacConflict.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgMobile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetAbort.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNTP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPhoneNotify.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPSTNAlarmServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPSTNBreakLine.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgRCEmergencyCall.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSensorInfoOfVW.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSensorSampling.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSerial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSnapLinkage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSTP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgWireless.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AddUserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\AirConditionOperate.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmDevice.rc
# End Source File
# Begin Source File

SOURCE=.\AlarmDeviceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmSubscribe.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioBoardcastDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BSWndContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\DHPtzMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgActivatedDefenceArea.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmBell.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOutSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmSubSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAnalogAlarmChannels.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAnalogAlarmData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBypassCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCapability.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmBell.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExAlarmChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExAlarmEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExAlarmHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgExtendedBypass.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalBypass.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLowRateWPAN.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptPlaysound.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQueryLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecoverConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRestoreCfgNew.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetArmMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetBypass.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetNetWorkParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStateBattery.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserManage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\ExButton.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\mdump.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyPwd.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyUserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayApi.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\PtzScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SubDlgCfgEventHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgCfgTimeSection.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgSensorInfoDescription.cpp
# End Source File
# Begin Source File

SOURCE=.\TabUserManageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoNodeInfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddUserInfo.h
# End Source File
# Begin Source File

SOURCE=.\AirConditionOperate.h
# End Source File
# Begin Source File

SOURCE=.\AlarmDevice.h
# End Source File
# Begin Source File

SOURCE=.\AlarmDeviceDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmSubscribe.h
# End Source File
# Begin Source File

SOURCE=.\AudioBoardcastDlg.h
# End Source File
# Begin Source File

SOURCE=.\BSWndContainer.h
# End Source File
# Begin Source File

SOURCE=.\DHPtzMenu.h
# End Source File
# Begin Source File

SOURCE=.\DlgAccess.h
# End Source File
# Begin Source File

SOURCE=.\DlgActivatedDefenceArea.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmBell.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmChannel.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOutSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmState.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmSubSystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgAnalogAlarmChannels.h
# End Source File
# Begin Source File

SOURCE=.\DlgAnalogAlarmData.h
# End Source File
# Begin Source File

SOURCE=.\DlgBypassCtl.h
# End Source File
# Begin Source File

SOURCE=.\DlgCapability.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAirCondition.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmBell.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmCenter.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmChassisIntrusion.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmExAlarmBox.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmKeyboard.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmOut.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmPowerFault.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmSlotBond.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmSubSystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAlarmUrgency.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAnalogAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAutoMaintain.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgBatteryLowPower.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgExAlarmInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgExAlarmOutput.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgGuard.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgIPConflict.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgLocales.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgMacConflict.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgMobile.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetAbort.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetCollection.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetwork.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNTP.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPhoneNotify.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPSTNAlarmServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPSTNBreakLine.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgRCEmergencyCall.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSensorInfoOfVW.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSensorSampling.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSerial.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSnapLinkage.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSTP.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgWireless.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceTime.h
# End Source File
# Begin Source File

SOURCE=.\DlgExAlarmChannel.h
# End Source File
# Begin Source File

SOURCE=.\DlgExAlarmEventHandler.h
# End Source File
# Begin Source File

SOURCE=.\DlgExAlarmHandler.h
# End Source File
# Begin Source File

SOURCE=.\DlgExtendedBypass.h
# End Source File
# Begin Source File

SOURCE=.\DlgFileList.h
# End Source File
# Begin Source File

SOURCE=.\DlgFileManager.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalBypass.h
# End Source File
# Begin Source File

SOURCE=.\DlgLowRateWPAN.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptAccess.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptPlaysound.h
# End Source File
# Begin Source File

SOURCE=.\DlgQueryLog.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecoverConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgRestoreCfgNew.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetArmMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetBypass.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetNetWorkParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgStateBattery.h
# End Source File
# Begin Source File

SOURCE=.\DlgTalk.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserManage.h
# End Source File
# Begin Source File

SOURCE=.\DlgVersion.h
# End Source File
# Begin Source File

SOURCE=.\ExButton.h
# End Source File
# Begin Source File

SOURCE=.\FlashLabel.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\mdump.h
# End Source File
# Begin Source File

SOURCE=.\ModifyPwd.h
# End Source File
# Begin Source File

SOURCE=.\ModifyUserInfo.h
# End Source File
# Begin Source File

SOURCE=.\MultiPlay.h
# End Source File
# Begin Source File

SOURCE=.\PlayApi.h
# End Source File
# Begin Source File

SOURCE=.\PlayWnd.h
# End Source File
# Begin Source File

SOURCE=.\PtzScreen.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgCfgEventHandler.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgCfgTimeSection.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgSensorInfoDescription.h
# End Source File
# Begin Source File

SOURCE=.\TabUserManageDlg.h
# End Source File
# Begin Source File

SOURCE=.\VideoNodeInfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AlarmDevice.ico
# End Source File
# Begin Source File

SOURCE=.\res\AlarmDevice.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
