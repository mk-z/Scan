# Microsoft Developer Studio Project File - Name="IVS_VDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=IVS_VDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "IVS_VDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IVS_VDemo.mak" CFG="IVS_VDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IVS_VDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IVS_VDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "IVS_VDemo - Win32 Release pdb" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IVS_VDemo - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dhnetsdk.lib dhconfigsdk.lib /nologo /subsystem:windows /machine:I386 /libpath:"include"

!ELSEIF  "$(CFG)" == "IVS_VDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "D:\VxWork\Trunk\NetSDK_Chn_Bin\¿âÎÄ¼þ"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"include"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "IVS_VDemo - Win32 Release pdb"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "IVS_VDemo___Win32_Release_pdb"
# PROP BASE Intermediate_Dir "IVS_VDemo___Win32_Release_pdb"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 dhnetsdk.lib dhconfigsdk.lib /nologo /subsystem:windows /machine:I386 /libpath:"include"
# ADD LINK32 dhnetsdk.lib dhconfigsdk.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"include"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "IVS_VDemo - Win32 Release"
# Name "IVS_VDemo - Win32 Debug"
# Name "IVS_VDemo - Win32 Release pdb"
# Begin Group "DeviceDlg"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DeviceListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceListDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DeviceTree.BMP
# End Source File
# Begin Source File

SOURCE=.\res\IVS_VDemo.ico
# End Source File
# Begin Source File

SOURCE=.\IVS_VDemo.rc
# End Source File
# Begin Source File

SOURCE=.\res\IVS_VDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\control\virtTree.cpp
# End Source File
# Begin Source File

SOURCE=.\control\virtTree.h
# End Source File
# End Group
# Begin Group "ConfigDlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GlobalCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalCfg.h
# End Source File
# Begin Source File

SOURCE=.\ProfileCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileCfg.h
# End Source File
# Begin Source File

SOURCE=.\ProjectCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProjectCfg.h
# End Source File
# Begin Source File

SOURCE=.\TaskCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\TaskCfg.h
# End Source File
# End Group
# Begin Group "Login"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# End Group
# Begin Group "MainDlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IVS_VDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\IVS_VDemo.h
# End Source File
# Begin Source File

SOURCE=.\IVS_VDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IVS_VDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListenDiagnosisRes.cpp
# End Source File
# Begin Source File

SOURCE=.\ListenDiagnosisRes.h
# End Source File
# Begin Source File

SOURCE=.\QueryDiagnosisRes.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDiagnosisRes.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "ProfileInfo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ProfileInfo1.cpp
# End Source File
# Begin Source File

SOURCE=.\ProfileInfo1.h
# End Source File
# End Group
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SdkCallback.cpp
# End Source File
# Begin Source File

SOURCE=.\SdkCallback.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
