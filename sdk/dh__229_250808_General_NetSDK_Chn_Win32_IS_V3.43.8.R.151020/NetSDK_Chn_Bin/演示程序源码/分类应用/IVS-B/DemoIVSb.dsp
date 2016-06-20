# Microsoft Developer Studio Project File - Name="DemoIVSb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DemoIVSb - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DemoIVSb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DemoIVSb.mak" CFG="DemoIVSb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DemoIVSb - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DemoIVSb - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DemoIVSb - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /stack:0x400000 /subsystem:windows /machine:I386
# SUBTRACT LINK32 /verbose /pdb:none /incremental:yes /map /debug

!ELSEIF  "$(CFG)" == "DemoIVSb - Win32 Debug"

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
# ADD LINK32 /nologo /stack:0x400000 /subsystem:windows /incremental:no /machine:I386
# SUBTRACT LINK32 /pdb:none /debug

!ENDIF 

# Begin Target

# Name "DemoIVSb - Win32 Release"
# Name "DemoIVSb - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "rulesDlg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RuleCrossFence.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleCrossFence.h
# End Source File
# Begin Source File

SOURCE=.\RuleCrossLine.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleCrossLine.h
# End Source File
# Begin Source File

SOURCE=.\RuleCrossRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleCrossRegion.h
# End Source File
# Begin Source File

SOURCE=.\RuleLeft.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleLeft.h
# End Source File
# Begin Source File

SOURCE=.\RuleMove.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleMove.h
# End Source File
# Begin Source File

SOURCE=.\RuleParking.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleParking.h
# End Source File
# Begin Source File

SOURCE=.\RulePreservation.cpp
# End Source File
# Begin Source File

SOURCE=.\RulePreservation.h
# End Source File
# Begin Source File

SOURCE=.\RuleRetrogradation.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleRetrogradation.h
# End Source File
# Begin Source File

SOURCE=.\RuleStay.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleStay.h
# End Source File
# Begin Source File

SOURCE=.\RuleTakenAway.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleTakenAway.h
# End Source File
# Begin Source File

SOURCE=.\RuleVideoAbnormal.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleVideoAbnormal.h
# End Source File
# Begin Source File

SOURCE=.\RuleWander.cpp
# End Source File
# Begin Source File

SOURCE=.\RuleWander.h
# End Source File
# End Group
# Begin Group "tool"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IvsGlobalPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\IvsGlobalPreview.h
# End Source File
# Begin Source File

SOURCE=.\IvsModulePreview.cpp
# End Source File
# Begin Source File

SOURCE=.\IvsModulePreview.h
# End Source File
# Begin Source File

SOURCE=.\IvsRulePreview.cpp
# End Source File
# Begin Source File

SOURCE=.\IvsRulePreview.h
# End Source File
# Begin Source File

SOURCE=.\TargetFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\TargetFilter.h
# End Source File
# Begin Source File

SOURCE=.\TargetFilterPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\TargetFilterPreview.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Alarm.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigGlobal.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigModule.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigRules.cpp
# End Source File
# Begin Source File

SOURCE=.\DemoIVSb.cpp
# End Source File
# Begin Source File

SOURCE=.\DemoIVSb.rc
# End Source File
# Begin Source File

SOURCE=.\DemoIVSbDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Login.cpp
# End Source File
# Begin Source File

SOURCE=.\Logo.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayApi.cpp
# End Source File
# Begin Source File

SOURCE=.\Preview.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Switch.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Alarm.h
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\ConfigGlobal.h
# End Source File
# Begin Source File

SOURCE=.\ConfigModule.h
# End Source File
# Begin Source File

SOURCE=.\ConfigRules.h
# End Source File
# Begin Source File

SOURCE=.\DemoIVSb.h
# End Source File
# Begin Source File

SOURCE=.\DemoIVSbDlg.h
# End Source File
# Begin Source File

SOURCE=.\Login.h
# End Source File
# Begin Source File

SOURCE=.\Logo.h
# End Source File
# Begin Source File

SOURCE=.\PlayApi.h
# End Source File
# Begin Source File

SOURCE=.\Preview.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Switch.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DemoIVSb.ico
# End Source File
# Begin Source File

SOURCE=.\res\DemoIVSb.rc2
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
