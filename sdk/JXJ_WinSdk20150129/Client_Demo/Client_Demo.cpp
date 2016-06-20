
// Client_Demo.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "Client_DemoDlg.h"
#include "FullUpDlg.h"
#include "Pub_Data.h"
#include "BorderDlg.h"
#include "direct.h"     //mkdir 头文件

#include "Winnls.h"
#include "Windows.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClient_DemoApp

BEGIN_MESSAGE_MAP(CClient_DemoApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClient_DemoApp 构造

CClient_DemoApp::CClient_DemoApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CClient_DemoApp 对象

CClient_DemoApp theApp;
CFullUpDlg g_cFullUpDlg[GET_MAX_DEV_NUM];
CPub_Data g_PubData;

// CClient_DemoApp 初始化

BOOL CClient_DemoApp::InitInstance()
{
	
	AfxOleInit();
	
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//=======================================================

	CStringArray strArrKey;
	CStringArray strArrKeyValue;	
	CStringArray strArraySetion;
	CStringArray strArrallSecons;

	//g_PubData.g_iniFile.m_strPath = _T(".\\sdk.ini");
	g_PubData.g_iniFile.SetIniPath(_T(""), _T("sdk.ini"));
	g_PubData.g_iniFile.GetAllSections(strArrallSecons);
	int iCount = strArrallSecons.GetCount();
	if(strArrallSecons.GetAt(0) == _T(""))
	{
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("抓拍路径"),_T("D:\\PICTURE_SRC"));
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("录像路径"),_T("D:\\VIDEO_SRC"));	
		g_PubData.g_iniFile.SetKeyValue(_T("src"),_T("下载路径"),_T("D:\\DOWNLOAD_SRC"));
		if(!PathFileExists(_T("D:\\PICTURE_SRC")))
		{
			::_mkdir(_T("D:\\PICTURE_SRC")); 
		}
		if(!PathFileExists(_T("D:\\VIDEO_SRC")))
		{
			::_mkdir(_T("D:\\VIDEO_SRC")); 
		}
		if(!PathFileExists(_T("D:\\DOWNLOAD_SRC")))
		{
			::_mkdir(_T("D:\\DOWNLOAD_SRC")); 
		}

	}
	if(iCount< 2)
	{
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("模式"),_T("0"));     //0 客户端  1 服务端;
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("信令端口"),_T("5556"));
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("流端口"),_T("6666"));
		g_PubData.g_iniFile.SetKeyValue(_T("mode"),_T("语言"),_T("0"));
	}


	g_PubData.g_iniFile.GetAllSections(strArraySetion);
	g_PubData.g_iniFile.GetAllKeysAndValues(strArraySetion.GetAt(1),strArrKey,strArrKeyValue);
	g_PubData.g_iLanguageFlag = _ttoi(strArrKeyValue.GetAt(3));
	//==============================================================
	LCID lcidThread = 0;
	if(g_PubData.g_iLanguageFlag == 0)
	{
		lcidThread = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED),SORT_DEFAULT);
		SetThreadLocale(lcidThread);  

	}
	else
	{
		lcidThread = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),SORT_DEFAULT);
		SetThreadUILanguage(lcidThread);
	}


	//SetThreadUILanguage(lcidThread);


	if(g_PubData.g_iLanguageFlag == 0)
	{
		g_PubData.g_strTalkS = _T("对讲");
		g_PubData.g_strTalkE = _T("停止");

		g_PubData.g_strRecordS = _T("录像");
		g_PubData.g_strRecordE = _T("停止");

		g_PubData.g_strListenS = _T("监听");
		g_PubData.g_strListemE = _T("关闭");

		g_PubData.g_strSetMessage = _T("设置失败！");
		g_PubData.g_strGetMessage = _T("获取失败！");

	}
	else
	{
		g_PubData.g_strTalkS = _T("Talk");
		g_PubData.g_strTalkE = _T("Stop");

		g_PubData.g_strRecordS = _T("Record");
		g_PubData.g_strRecordE = _T("Stop");

		g_PubData.g_strListenS = _T("Listen");
		g_PubData.g_strListemE = _T("Close");

		g_PubData.g_strSetMessage = _T("Set Failed！");
		g_PubData.g_strGetMessage = _T("Get Failed！");

	}











	
	CClient_DemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。

	
	return FALSE;
}
