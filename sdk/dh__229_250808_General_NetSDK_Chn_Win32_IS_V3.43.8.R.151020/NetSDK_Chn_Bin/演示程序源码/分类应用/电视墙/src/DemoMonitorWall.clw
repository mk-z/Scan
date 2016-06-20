; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVideoWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demomonitorwall.h"
LastPage=0

ClassCount=11
Class1=CCollectionDlg
Class2=CDemoMonitorWallApp
Class3=CDemoMonitorWallDlg
Class4=CLoginDlg
Class5=CMonitorWallWnd
Class6=CPowerDlg
Class7=CSpliceScreenConfigDlg
Class8=CStaticEx
Class9=CToolBarEx
Class10=CVideoScreen
Class11=CVideoWnd

ResourceCount=7
Resource1=IDD_DIALOG_SPLICESCREEN
Resource2=IDD_DIALOG_POWER
Resource3=IDD_DIALOG_COLLECTION
Resource4=IDR_TOOLBAR1
Resource5=IDD_DEMOMONITORWALL_DIALOG
Resource6=IDD_DIALOG_LOGIN
Resource7=IDR_TOOLBAR2

[CLS:CCollectionDlg]
Type=0
BaseClass=CDialog
HeaderFile=CollectionDlg.h
ImplementationFile=CollectionDlg.cpp
LastObject=CCollectionDlg
Filter=D
VirtualFilter=dWC

[CLS:CDemoMonitorWallApp]
Type=0
BaseClass=CWinApp
HeaderFile=DemoMonitorWall.h
ImplementationFile=DemoMonitorWall.cpp

[CLS:CDemoMonitorWallDlg]
Type=0
BaseClass=CDialog
HeaderFile=DemoMonitorWallDlg.h
ImplementationFile=DemoMonitorWallDlg.cpp

[CLS:CLoginDlg]
Type=0
BaseClass=CDialog
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp

[CLS:CMonitorWallWnd]
Type=0
BaseClass=CWnd
HeaderFile=MonitorWallWnd.h
ImplementationFile=MonitorWallWnd.cpp

[CLS:CPowerDlg]
Type=0
BaseClass=CDialog
HeaderFile=PowerDlg.h
ImplementationFile=PowerDlg.cpp

[CLS:CSpliceScreenConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=SpliceScreenConfigDlg.h
ImplementationFile=SpliceScreenConfigDlg.cpp

[CLS:CStaticEx]
Type=0
BaseClass=CStatic
HeaderFile=StaticEx.h
ImplementationFile=StaticEx.cpp

[CLS:CToolBarEx]
Type=0
BaseClass=CToolBar
HeaderFile=ToolBarEx.h
ImplementationFile=ToolBarEx.cpp

[CLS:CVideoScreen]
Type=0
BaseClass=CWnd
HeaderFile=VideoScreen.h
ImplementationFile=VideoScreen.cpp

[CLS:CVideoWnd]
Type=0
BaseClass=CWnd
HeaderFile=VideoWnd.h
ImplementationFile=VideoWnd.cpp
Filter=W
VirtualFilter=WC
LastObject=CVideoWnd

[DLG:IDD_DIALOG_COLLECTION]
Type=1
Class=CCollectionDlg
ControlCount=7
Control1=IDC_LIST_COLLECTION,listbox,1352728835
Control2=IDC_EDIT_COLLECTION_NAME,edit,1350631552
Control3=IDC_BTN_LOAD,button,1342242816
Control4=IDC_BTN_SAVE,button,1342242816
Control5=IDC_COMBO_MONITORWALL,combobox,1344339971
Control6=IDC_EDIT_COLLECTION_NEW_NAME,edit,1350631552
Control7=IDC_BTN_RENAME,button,1342242816

[DLG:IDD_DEMOMONITORWALL_DIALOG]
Type=1
Class=CDemoMonitorWallDlg
ControlCount=3
Control1=IDC_TREE_DEVICE,SysTreeView32,1350635559
Control2=IDC_BTN_REMOVE_DEVICE,button,1342242816
Control3=IDC_BTN_ADD_DEVICE,button,1342242816

[DLG:IDD_DIALOG_LOGIN]
Type=1
Class=CLoginDlg
ControlCount=15
Control1=IDC_EDIT_ADDRESS,edit,1216413824
Control2=IDC_COMBO_ADDRESS,combobox,1344339970
Control3=IDC_EDIT_PORT,edit,1350631552
Control4=IDC_EDIT_USER,edit,1350631552
Control5=IDC_EDIT_PWD,edit,1350631584
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_DEV_CLASS,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_DEV_TYPE,edit,1350631552
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_POWER]
Type=1
Class=CPowerDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_MONITORWALL,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_BLOCK,combobox,1344339971
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMBO_OUTPUT,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_COMBO_POWER,combobox,1344339971

[DLG:IDD_DIALOG_SPLICESCREEN]
Type=1
Class=CSpliceScreenConfigDlg
ControlCount=28
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_OUTPUT_COUNT,button,1342177287
Control4=IDC_STATIC_OUTPUT_COUNT2,button,1342177287
Control5=IDC_RADIO_LAYOUT_1x1,button,1342308361
Control6=IDC_RADIO_LAYOUT_2x2,button,1342177289
Control7=IDC_RADIO_LAYOUT_3x3,button,1342177289
Control8=IDC_RADIO_LAYOUT_4x4,button,1342177289
Control9=IDC_RADIO_LAYOUT_nxn,button,1342177289
Control10=IDC_COMBO_OUTPUT_LAYOUT_ROW,combobox,1344339971
Control11=IDC_COMBO_OUTPUT_LAYOUT_COLUMN,combobox,1344339971
Control12=IDC_STATIC,static,1342308352
Control13=IDC_RADIO_SIZE_1x1,button,1342308361
Control14=IDC_RADIO_SIZE_2x2,button,1342177289
Control15=IDC_RADIO_SIZE_3x3,button,1342177289
Control16=IDC_RADIO_SIZE_4x4,button,1342177289
Control17=IDC_RADIO_SIZE_nxn,button,1342177289
Control18=IDC_COMBO_OUTPUT_SIZE_ROW,combobox,1344339971
Control19=IDC_COMBO_OUTPUT_SIZE_COLUMN,combobox,1344339971
Control20=IDC_STATIC,static,1342308352
Control21=IDC_BTN_ADD,button,1342242816
Control22=IDC_BTN_DELETE,button,1342242816
Control23=IDC_BTN_CLEAR,button,1342242816
Control24=IDC_LIST_BLOCK_OUTPUTS,listbox,1352730961
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EDIT_SPLICE_NAME,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EDIT_SPLICE_ID,edit,1350631552

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=ID_TOOLBAR_LOGIN
Command2=ID_TOOLBAR_LOGOUT
Command3=ID_TOOLBAR_SPLICE
Command4=IDCANCEL
CommandCount=4

[TB:IDR_TOOLBAR2]
Type=1
Class=?
Command1=ID_TOOLBAR_TV_OUT
Command2=ID_TOOLBAR_SPLIT1
Command3=ID_TOOLBAR_SPLIT4
Command4=ID_TOOLBAR_SPLIT8
Command5=ID_TOOLBAR_SPLIT9
Command6=ID_TOOLBAR_SPLIT16
Command7=ID_TOOLBAR_SPLIT25
Command8=ID_TOOLBAR_SPLIT36
Command9=ID_TOOLBAR_SPLIT_FREE
Command10=ID_TOOLBAR_OPEN_WINDOW
Command11=ID_TOOLBAR_CLOSE_WINDOW
Command12=ID_TOOLBAR_SET_LEVEL
Command13=ID_TOOLBAR_POWER
Command14=ID_TOOLBAR_COLLECTION
CommandCount=14

