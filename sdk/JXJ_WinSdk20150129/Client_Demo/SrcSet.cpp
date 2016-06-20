// SrcSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "SrcSet.h"
#include "IniFile.h"
#include "direct.h"     //mkdir 头文件
#include "Pub_Data.h"

// CSrcSet 对话框

IMPLEMENT_DYNAMIC(CSrcSet, CDialog)

CSrcSet::CSrcSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSrcSet::IDD, pParent)
{
	m_iMode = -1;
	m_strPort = _T("");
	m_strSPort = _T("");
}

CSrcSet::~CSrcSet()
{

}

void CSrcSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TAKEAPICTURESRC, m_TakeAPictureSrc);
	DDX_Control(pDX, IDC_EDIT_RECODESRC, m_RecodeSrc);
	DDX_Control(pDX, IDC_CHECK_SERVER, m_ServerCheck);
	DDX_Control(pDX, IDC_CHECK_CLIENT, m_ClientCheck);
	DDX_Control(pDX, IDC_EDIT_PORT, m_EPort);
	DDX_Control(pDX, IDC_EDIT_SPORT, m_eSport);
	DDX_Control(pDX, IDC_EDIT_DOWNLOAD, m_downLoadSrc);
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_language);
}


BEGIN_MESSAGE_MAP(CSrcSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_TAKEAPICTURE, &CSrcSet::OnBnClickedButtonTakeapicture)
	ON_BN_CLICKED(IDC_BUTTON_RECODESRC, &CSrcSet::OnBnClickedButtonRecodesrc)
	ON_BN_CLICKED(IDOK, &CSrcSet::OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_SERVER, &CSrcSet::OnBnClickedCheckServer)
	ON_BN_CLICKED(IDC_CHECK_CLIENT, &CSrcSet::OnBnClickedCheckClient)
	ON_BN_CLICKED(IDC_BUTTON_DOWNSRC, &CSrcSet::OnBnClickedButtonDownsrc)
END_MESSAGE_MAP()


// CSrcSet 消息处理程序
BOOL CSrcSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_TakeAPictureSrc.EnableWindow(FALSE);
	m_RecodeSrc.EnableWindow(FALSE);
	m_downLoadSrc.EnableWindow(FALSE);


	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_language.AddString(_T("简体中文"));
		m_language.AddString(_T("英语(美国)"));
	}
	else
	{
		m_language.AddString(_T("Simplified Chinese"));
		m_language.AddString(_T("English(USA)"));
	}
	
	InitWnd();
	m_ServerCheck.EnableWindow(FALSE);


	


	return TRUE;
}

void CSrcSet::InitWnd()
{

 	CStringArray strArrKey;
 	CStringArray strArrKeyValue;	
 
 
 	CStringArray strArraySetion;
 	int iLen = g_PubData.g_iniFile.GetAllSections(strArraySetion);
 	if(strArraySetion.GetAt(0) == _T(""))
 	{
 		return;
 	}
 
 	g_PubData.g_iniFile.GetAllKeysAndValues(strArraySetion.GetAt(0),strArrKey,strArrKeyValue);
 
 	m_TakeAPictureSrc.SetWindowText(strArrKeyValue.GetAt(0));
 	m_RecodeSrc.SetWindowText(strArrKeyValue.GetAt(1));
	m_downLoadSrc.SetWindowText(strArrKeyValue.GetAt(2));
 	m_strTakeApictureSrc = strArrKeyValue.GetAt(0);
 	m_strRecodeSrc = strArrKeyValue.GetAt(1);
	m_strDownLoadSrc = strArrKeyValue.GetAt(2);

	CStringArray modeKey;
	CStringArray modeValue;
	CString strTemp = strArraySetion.GetAt(1);

	g_PubData.g_iniFile.GetAllKeysAndValues(strTemp,modeKey,modeValue);
	m_iMode = _ttoi(modeValue.GetAt(0));
	m_strPort = modeValue.GetAt(1);
	m_strSPort = modeValue.GetAt(2);
	CString strLanguage = modeValue.GetAt(3);
	if(m_iMode == 0)
	{
		m_ClientCheck.SetCheck(1);
	}
	else
	{
		m_ServerCheck.SetCheck(1);
	}
	
	m_EPort.SetWindowText(m_strPort);
	m_eSport.SetWindowText(m_strSPort);
	int iSel = _ttoi(strLanguage);
	m_language.SetCurSel(iSel);
	OnBnClickedCheckServer();
	OnBnClickedCheckClient();

}

void CSrcSet::OnBnClickedButtonTakeapicture()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strTakeApictureSrc = OpenFileSrc();
	if(m_strTakeApictureSrc == _T(""))
	{
		return;
	}
	m_TakeAPictureSrc.SetWindowText(m_strTakeApictureSrc);

}

void CSrcSet::OnBnClickedButtonRecodesrc()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strRecodeSrc = OpenFileSrc();
	if(m_strRecodeSrc == _T(""))
	{
		return;
	}
	m_RecodeSrc.SetWindowText(m_strRecodeSrc);
}

CString CSrcSet::OpenFileSrc()
{
	UpdateData(TRUE);

	CString strSrc = _T("");
	char szDir[MAX_PATH];

	BROWSEINFO bi;

	ITEMIDLIST *pidl;

	bi.hwndOwner = this->m_hWnd;

	bi.pidlRoot = NULL;

	bi.pszDisplayName = szDir;

	bi.lpszTitle = "请选择目录";

	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;

	bi.lpfn = NULL;

	bi.lParam = 0;

	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi);

	if(pidl == NULL)
	{
		return _T("");
	}

	if(!SHGetPathFromIDList(pidl, szDir)) 
	{
		return _T("");
	}
	else
	{
		strSrc.Format(_T("%s"),szDir);
	}

	return strSrc;
	//UpdateData(FALSE);    
}
void CSrcSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		if(m_ClientCheck.GetCheck() == 1)
		{
			m_iMode = 0;
		}
		else
		{
			m_iMode = 1;
		}
		m_EPort.GetWindowText(m_strPort);
		m_eSport.GetWindowText(m_strSPort);
		m_iLanguageFlag = m_language.GetCurSel();
		

		OnOK();
	}
	catch(...)
	{
		//AfxMessageBox(_T("catch"));
	}
}

void CSrcSet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	try
	{
		CDialog::OnClose();
	}
	catch(...)
	{
		//AfxMessageBox(_T("catch"));
	}

}	

void CSrcSet::OnBnClickedCheckServer()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ServerCheck.GetCheck() == 1)
	{
		m_ClientCheck.SetCheck(0);
		m_EPort.EnableWindow(TRUE);
		m_eSport.EnableWindow(TRUE);
	}
	else
	{
		m_ClientCheck.SetCheck(1);
		m_EPort.EnableWindow(FALSE);
		m_eSport.EnableWindow(FALSE);
	}
}

void CSrcSet::OnBnClickedCheckClient()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_ClientCheck.GetCheck() == 1)
	{
		m_ServerCheck.SetCheck(0);
	}
	else
	{
		m_ServerCheck.SetCheck(1);
	}
}

void CSrcSet::OnBnClickedButtonDownsrc()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strDownLoadSrc = OpenFileSrc();
	if(m_strDownLoadSrc == _T(""))
	{
		return;
	}
	m_downLoadSrc.SetWindowText(m_strDownLoadSrc);
}
