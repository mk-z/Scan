# Microsoft Developer Studio Project File - Name="AccessControl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AccessControl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AccessControl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AccessControl.mak" CFG="AccessControl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AccessControl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AccessControl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AccessControl - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "AccessControl - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Bin/AccessControl_d.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AccessControl - Win32 Release"
# Name "AccessControl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccessControl.cpp
# End Source File
# Begin Source File

SOURCE=.\AccessControl.rc
# End Source File
# Begin Source File

SOURCE=.\AccessControlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmSubscribe.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCapability.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDoorControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQueryLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordSetControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSubDlgInfoAccessRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSubDlgInfoHoliday.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSubDlgInfoPassword.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserManage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\Include\mdump.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordSetFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SubDlgCfgDoorOpenTimeSection.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgInfoCard.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgSensorInfoDescription.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccessControl.h
# End Source File
# Begin Source File

SOURCE=.\AccessControlDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmSubscribe.h
# End Source File
# Begin Source File

SOURCE=.\DlgCapability.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceTime.h
# End Source File
# Begin Source File

SOURCE=.\DlgDoorControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgQueryLog.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordSetControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgSubDlgInfoAccessRecord.h
# End Source File
# Begin Source File

SOURCE=.\DlgSubDlgInfoHoliday.h
# End Source File
# Begin Source File

SOURCE=.\DlgSubDlgInfoPassword.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserManage.h
# End Source File
# Begin Source File

SOURCE=.\DlgVersion.h
# End Source File
# Begin Source File

SOURCE=.\Include\mdump.h
# End Source File
# Begin Source File

SOURCE=.\RecordSetFinder.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgCfgDoorOpenTimeSection.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgInfoCard.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgSensorInfoDescription.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AccessControl.ico
# End Source File
# Begin Source File

SOURCE=.\res\AccessControl.rc2
# End Source File
# End Group
# Begin Group "Config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgCfgAccessControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAccessControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAccessControlGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAccessControlGeneral.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNetwork.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNTP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgNTP.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgTimeSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgTimeSchedule.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
