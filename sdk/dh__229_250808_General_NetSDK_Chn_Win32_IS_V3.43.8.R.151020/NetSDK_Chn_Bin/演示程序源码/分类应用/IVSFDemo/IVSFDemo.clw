; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CModuleCfgdlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IVSFDemo.h"

ClassCount=13
Class1=CIVSFDemoApp
Class2=CIVSFDemoDlg
Class3=CAboutDlg

ResourceCount=11
Resource1=IDD_DIALOG_ALARMON
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_CFG_RULE
Resource4=IDD_ABOUTBOX
Resource5=IDD_DIALOG_CFG_SCENCE
Class4=CLogDlg
Class5=CLoginDlg
Class6=CPreviewDlg
Class7=CEventDlg
Resource6=IDD_DIALOG_CONFIG
Class8=CAlarmOnDlg
Class9=CAlarmShow
Resource7=IDD_IVSFDEMO_DIALOG
Resource8=IDD_DIALOG_ALARMSHOW
Resource9=IDD_DIALOG_DEVLOGIN
Class10=CConfigDlg
Resource10=IDD_DIALOG_PREVIEW
Class11=CSenceCfgdlg
Class12=CRuleCfgdlg
Class13=CModuleCfgdlg
Resource11=IDD_DIALOG_CFG_MODULE

[CLS:CIVSFDemoApp]
Type=0
HeaderFile=IVSFDemo.h
ImplementationFile=IVSFDemo.cpp
Filter=N

[CLS:CIVSFDemoDlg]
Type=0
HeaderFile=IVSFDemoDlg.h
ImplementationFile=IVSFDemoDlg.cpp
Filter=D
LastObject=CIVSFDemoDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=IVSFDemoDlg.h
ImplementationFile=IVSFDemoDlg.cpp
Filter=D
LastObject=IDOK

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IVSFDEMO_DIALOG]
Type=1
Class=CIVSFDemoDlg
ControlCount=6
Control1=IDC_BUTTON_PREVIWE,button,1476460544
Control2=IDC_BUTTON_CONFIG,button,1476460544
Control3=IDC_BUTTON_LOG,button,1342242816
Control4=IDC_STATIC,static,1342177287
Control5=IDC_STATIC_BACKGROUND,static,1342177284
Control6=IDC_BUTTON_ALARMON,button,1476460544

[DLG:IDD_DIALOG_PREVIEW]
Type=1
Class=CPreviewDlg
ControlCount=8
Control1=IDC_STATIC_PREVIEW,static,1342177285
Control2=IDC_COMBO_CHANNEL,combobox,1344274690
Control3=IDC_BUTTON_STARTVIEW,button,1342242816
Control4=IDC_BUTTON_STOPVIEW,button,1476460544
Control5=IDC_STATIC,static,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_LIST_EVENT,SysListView32,1350631425
Control8=IDC_STATIC_ALARMVIEW,static,1342177287

[CLS:CLogDlg]
Type=0
HeaderFile=LogDlg.h
ImplementationFile=LogDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLogDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_DEVLOGIN]
Type=1
Class=CLoginDlg
ControlCount=10
Control1=IDC_BUTTON_LOGIN,button,1342242816
Control2=IDC_BUTTON_LOGOUT,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_IP,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_PORT,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_USERNAME,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_PASSWORD,edit,1350631584

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoginDlg
VirtualFilter=dWC

[CLS:CPreviewDlg]
Type=0
HeaderFile=PreviewDlg.h
ImplementationFile=PreviewDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_CHANNEL
VirtualFilter=dWC

[CLS:CEventDlg]
Type=0
HeaderFile=EventDlg.h
ImplementationFile=EventDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CEventDlg

[DLG:IDD_DIALOG_ALARMON]
Type=1
Class=CAlarmOnDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_BUTTON_SELALL,button,1342242816
Control3=IDC_BUTTON_ANTISEL,button,1342242816
Control4=IDC_LIST_CHANNEL,SysListView32,1350631427
Control5=IDC_BUTTON_STOP,button,1342242816

[CLS:CAlarmOnDlg]
Type=0
HeaderFile=AlarmOnDlg.h
ImplementationFile=AlarmOnDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST_CHANNEL
VirtualFilter=dWC

[DLG:IDD_DIALOG_ALARMSHOW]
Type=1
Class=CAlarmShow
ControlCount=0

[CLS:CAlarmShow]
Type=0
HeaderFile=AlarmShow.h
ImplementationFile=AlarmShow.cpp
BaseClass=CDialog
Filter=D
LastObject=CAlarmShow

[DLG:IDD_DIALOG_CONFIG]
Type=1
Class=CConfigDlg
ControlCount=5
Control1=IDC_TAB_CONFIG,SysTabControl32,1342177280
Control2=IDC_BUTTON_SAVE,button,1342242816
Control3=IDC_BUTTON_READ,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMBO_CHANNEL,combobox,1344340226

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_CHANNEL
VirtualFilter=dWC

[DLG:IDD_DIALOG_CFG_SCENCE]
Type=1
Class=CSenceCfgdlg
ControlCount=24
Control1=IDC_STATIC,static,1342308354
Control2=IDC_EDIT_CAMERAHEIGHT,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308354
Control6=IDC_EDIT_FACEANGLE_DOWN,edit,1350631552
Control7=IDC_EDIT_FACEANGLEUP,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308354
Control12=IDC_EDIT_FACEANGLE_LEFT,edit,1350631552
Control13=IDC_EDIT_FACEANGLE_RIGHT,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC_FACEUD,static,1350569998
Control18=IDC_STATIC_FACERL,static,1350569998
Control19=IDC_STATIC_SCENEVIEW,static,1342177284
Control20=IDC_STATIC,static,1342308354
Control21=IDC_EDIT_MAINDIR_1,edit,1350631552
Control22=IDC_EDIT_MAINDIR_2,edit,1350631552
Control23=IDC_BUTTON_DRAW,button,1342242816
Control24=IDC_BUTTON_DELETE,button,1342242816

[CLS:CSenceCfgdlg]
Type=0
HeaderFile=SenceCfgdlg.h
ImplementationFile=SenceCfgdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSenceCfgdlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_CFG_RULE]
Type=1
Class=CRuleCfgdlg
ControlCount=22
Control1=IDC_STATIC,static,1342308354
Control2=IDC_EDIT_RULENAME,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_COMBO_MODE,combobox,1344339970
Control5=IDC_CHECK_EYEBROW,button,1476460547
Control6=IDC_CHECK_EYE,button,1476460547
Control7=IDC_CHECK_NOSE,button,1476460547
Control8=IDC_CHECK_MOUTH,button,1476460547
Control9=IDC_CHECK_FACE,button,1476460547
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308354
Control16=IDC_EDIT_SIMILARITY,edit,1350631552
Control17=IDC_EDIT_IMPORTANTRANK,edit,1350631552
Control18=IDC_EDIT_ACCURACY,edit,1350631552
Control19=IDC_STATIC,static,1342308354
Control20=IDC_EDIT_MAXCANDIDATE,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_CFG_MODULE]
Type=1
Class=CModuleCfgdlg
ControlCount=23
Control1=IDC_STATIC_MODULE,static,1342177284
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_EDT_ZONE_LEFTTOP,edit,1350631552
Control5=IDC_EDT_ZONE_RIGHTBOTTOM,edit,1350631552
Control6=IDC_BTN_ZONE_DRAW,button,1342242816
Control7=IDC_BTN_ZONE_CLEAR,button,1342242816
Control8=IDC_EDT_WIDTHMAX,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDT_WIDTHMIN,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_BTN_WIDTH_DRAW,button,1342242816
Control15=IDC_BTN_WIDTH_CLEAR,button,1342242816
Control16=IDC_SLIDER_ACCURACY,msctls_trackbar32,1342242816
Control17=IDC_STATIC,static,1342308354
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_SLIDER_SENSITIVITY,msctls_trackbar32,1342242816
Control21=IDC_STATIC,static,1342308354
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352

[CLS:CRuleCfgdlg]
Type=0
HeaderFile=RuleCfgdlg.h
ImplementationFile=RuleCfgdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO_MODE

[CLS:CModuleCfgdlg]
Type=0
HeaderFile=ModuleCfgdlg.h
ImplementationFile=ModuleCfgdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDT_WIDTHMIN

