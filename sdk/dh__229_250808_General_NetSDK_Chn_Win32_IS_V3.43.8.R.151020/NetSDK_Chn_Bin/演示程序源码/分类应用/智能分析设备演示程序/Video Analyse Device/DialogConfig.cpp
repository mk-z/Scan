// DialogConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Real Load Picture.h"
#include "DialogConfig.h"
#include "Utility.h"
#include <string>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogConfig dialog


CDialogConfig::CDialogConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogConfig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogConfig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogConfig, CDialog)
	//{{AFX_MSG_MAP(CDialogConfig)
	ON_BN_CLICKED(IDC_BUTTON_CHOSE_FILE, OnButtonChoseFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogConfig message handlers


BOOL CDialogConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();

	g_SetWndStaticText(this);

	//读取数据文件夹的位置
	string strCfgFilePath;
	string strCfgDefaultFolder;
	GetModulePath("dhnetsdk.dll", strCfgFilePath);
	strCfgDefaultFolder = strCfgFilePath;
	strCfgFilePath.append(CFG_CFG_FILE_NAME);
	strCfgDefaultFolder.append(PC_DATA_STORE_FOLDER);
	
		char szFolder[1024] = {0};
	::GetPrivateProfileString(CFG_SECTION_CFG, CFG_KEY_DATA_PATH, strCfgDefaultFolder.c_str(), szFolder, 1024, strCfgFilePath.c_str());

	GetDlgItem(IDC_EDIT_DATA_PATH)->SetWindowText(szFolder);



	return true;
}
void CDialogConfig::OnOK() 
{
	string strCfgFilePath;

	GetModulePath("dhnetsdk.dll", strCfgFilePath);
	strCfgFilePath.append(CFG_CFG_FILE_NAME);
	
	char szFolder[1024] = {0};
	GetDlgItem(IDC_EDIT_DATA_PATH)->GetWindowText(szFolder, 1024);
	::WritePrivateProfileString(CFG_SECTION_CFG, CFG_KEY_DATA_PATH, szFolder, strCfgFilePath.c_str());

	CDialog::OnOK();
}

void CDialogConfig::OnButtonChoseFile() 
{
	CString m_FileSrc;         
	//将选择的文件夹路径保存在此变量中
	TCHAR Buffer[MAX_PATH];
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = NULL;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;    
	//要求返回文件系统的目录
	bi.pszDisplayName = Buffer;    
	//此参数如为NULL则不能显示对话框
	bi.lpszTitle = _T("请选择文件夹");
	bi.lpfn = NULL;
	bi.iImage=IDR_MAINFRAME; 
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	//调用显示选择对话框
	if(pIDList){   
		SHGetPathFromIDList(pIDList, Buffer);   
		//取得文件夹路径到Buffer里 
		m_FileSrc = Buffer;
		//将文件夹路径保存在一个CString对象里
	}

	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) 
	{
		return;
	}
	//释放内存
	lpMalloc->Free(pIDList);
	lpMalloc->Release();

	if (m_FileSrc.GetLength() != 0)
	{
		if (m_FileSrc.GetAt(m_FileSrc.GetLength()-1) != '\\')
		{
			m_FileSrc += "\\";
		}
		GetDlgItem(IDC_EDIT_DATA_PATH)->SetWindowText(m_FileSrc);
	}
}
