
// testFindDevicesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "testFindDevices.h"
#include "testFindDevicesDlg.h"
#include "afxdialogex.h"

# include <stdlib.h>
#include "DiZhiPuVideoServer/netsdk.h"
#include "DiZhiPuVideoServer/H264Play.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "netsdk.lib")

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestFindDevicesDlg 对话框



CtestFindDevicesDlg::CtestFindDevicesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestFindDevicesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestFindDevicesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_wndList);
}

BEGIN_MESSAGE_MAP(CtestFindDevicesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestFindDevicesDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestFindDevicesDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtestFindDevicesDlg 消息处理程序

BOOL CtestFindDevicesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_wndList.DeleteAllItems(); 
	m_wndList.InsertColumn(0, _T(""));
	m_wndList.InsertColumn(1, _T("设备编号"));
	m_wndList.InsertColumn(2, _T("IP"));
	m_wndList.InsertColumn(3, _T("协议"));
	m_wndList.InsertColumn(4, _T("PORT"));
	m_wndList.InsertColumn(5, _T("MAC"));
	m_wndList.InsertColumn(6, _T("SN"));
	m_wndList.SetColumnWidth(0, 20);
	m_wndList.SetColumnWidth(1, 150);
	m_wndList.SetColumnWidth(2, 150);
	m_wndList.SetColumnWidth(3, 50);
	m_wndList.SetColumnWidth(4, 50);
	m_wndList.SetColumnWidth(5, 150);
	m_wndList.SetColumnWidth(6, 150);
	
	



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtestFindDevicesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestFindDevicesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtestFindDevicesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestFindDevicesDlg::OnBnClickedButton1()
{
	
}


void CtestFindDevicesDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	int  nInit = 0;
	int nRetLength = 0;

	nInit = H264_DVR_Init(NULL, NULL);
	int j = m_wndList.GetItemCount();
	while(j < 0)
	{
		m_wndList.DeleteItem(j);
		j--;
	}
	
	SDK_CONFIG_NET_COMMON_V2 m_Device[100] = { 0 };
	memset(&m_Device, 0, sizeof(SDK_CONFIG_NET_COMMON_V2)* 100);
	bool bRet = H264_DVR_SearchDevice((char*)m_Device, sizeof(SDK_CONFIG_NET_COMMON_V2)* 100, &nRetLength, 3000);
	
	if (bRet)
	{		
		m_wndList.SetRedraw(FALSE);
		int nTotalIndex = m_wndList.GetItemCount();
		int i=0, ncount = nRetLength / sizeof(SDK_CONFIG_NET_COMMON_V2);
		for (i = 0; i < ncount; i++)		
		{
			char sTmp[20] = { 0 };
			sprintf_s(sTmp, "%d", i+1);
			int nIndex = m_wndList.InsertItem(nTotalIndex + i, sTmp);
			
			m_wndList.SetItemText(nIndex, 1, m_Device[i].HostName);
			struct in_addr in;
			in.s_addr = m_Device[i].HostIP.l;			
			m_wndList.SetItemText(nIndex, 2, inet_ntoa(in));

			m_wndList.SetItemText(nIndex, 6, m_Device[i].sSn);
				
		}
		
		
		m_wndList.SetRedraw(TRUE);
	}
	
}
