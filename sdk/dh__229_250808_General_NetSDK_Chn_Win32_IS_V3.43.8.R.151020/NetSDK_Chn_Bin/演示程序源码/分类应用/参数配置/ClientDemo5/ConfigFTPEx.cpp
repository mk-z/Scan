// ConfigFTPEx.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo5.h"
#include "ConfigFTPEx.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigFTPEx dialog


CConfigFTPEx::CConfigFTPEx(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigFTPEx::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigFTPEx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_pstuNasInfoEx = NULL;
}


void CConfigFTPEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigFTPEx)
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_ctlEnable);
	DDX_Control(pDX, IDC_LIST_FTPEX, m_ctlFtpEx);
	DDX_Control(pDX, IDC_COMBO_PORTOCOL, m_ctlPortocol);
	DDX_Control(pDX, IDC_COMBO_ENCODING, m_ctlEncoding);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigFTPEx, CDialog)
	//{{AFX_MSG_MAP(CConfigFTPEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnButtonModify)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FTPEX, OnItemchangedListFtpex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigFTPEx message handlers
BOOL CConfigFTPEx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	InitListView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CConfigFTPEx::InitDlgInfo()
{
	
	m_pstuNasInfoEx = new CFG_NAS_INFO_EX;
	if(NULL == m_pstuNasInfoEx)
	{
		return;
	}
	memset(m_pstuNasInfoEx, 0, sizeof(CFG_NAS_INFO_EX));
	
	int nIndex = 0;
	m_ctlEncoding.ResetContent();
	nIndex = m_ctlEncoding.AddString("UTF8");
	m_ctlEncoding.SetItemData(nIndex,0);

	nIndex = m_ctlEncoding.AddString("GB2312");
	m_ctlEncoding.SetItemData(nIndex,1);


	m_ctlPortocol.ResetContent();
	nIndex = m_ctlPortocol.AddString("FTP");
	m_ctlPortocol.SetItemData(nIndex,0);

	nIndex = m_ctlPortocol.AddString("SMB");
	m_ctlPortocol.SetItemData(nIndex,1);

	nIndex = m_ctlPortocol.AddString("ISCSI");
	m_ctlPortocol.SetItemData(nIndex,2);
	
    nIndex = m_ctlPortocol.AddString("NFS");
	m_ctlPortocol.SetItemData(nIndex,3);
	OnButtonRead();

}
void CConfigFTPEx::InitListView()
{
	m_ctlFtpEx.SetExtendedStyle(m_ctlFtpEx.GetExtendedStyle() | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlFtpEx.InsertColumn(0, ConvertString("Index"),LVCFMT_LEFT,60,-1);
	m_ctlFtpEx.InsertColumn(1, ConvertString("Enable"),LVCFMT_LEFT,60,0);
	m_ctlFtpEx.InsertColumn(2, ConvertString("Name"),LVCFMT_LEFT,90,1);
	m_ctlFtpEx.InsertColumn(3, ConvertString("Portocol"),LVCFMT_LEFT,90,2);
	m_ctlFtpEx.InsertColumn(4, ConvertString("Address"),LVCFMT_LEFT,90,3);
	m_ctlFtpEx.InsertColumn(5, ConvertString("Port"),LVCFMT_LEFT,90,4);
	m_ctlFtpEx.InsertColumn(6, ConvertString("User"),LVCFMT_LEFT,80,5);
	m_ctlFtpEx.InsertColumn(7, ConvertString("Password"),LVCFMT_LEFT,80,6);
	m_ctlFtpEx.InsertColumn(8, ConvertString("Directory"),LVCFMT_LEFT,80,7);
	m_ctlFtpEx.InsertColumn(9, ConvertString("CharEncoding"),LVCFMT_LEFT,80,8);
}
void CConfigFTPEx::InsertListView(CString strIndex, CString strEnable, CString strName, CString strPortocol, CString strAddress,
		CString strPort, CString strUser, CString strPassword, CString strDirectory, CString strEncoding)
{
	int nIndex = m_ctlFtpEx.GetItemCount();
	m_ctlFtpEx.InsertItem(LVIF_TEXT|LVIF_STATE,nIndex,strIndex,0,LVIS_SELECTED,0,0);
	
	m_ctlFtpEx.SetItemText(nIndex,1,strEnable);
	m_ctlFtpEx.SetItemText(nIndex,2,strName);
	m_ctlFtpEx.SetItemText(nIndex,3,strPortocol);
	m_ctlFtpEx.SetItemText(nIndex,4,strAddress);
	m_ctlFtpEx.SetItemText(nIndex,5,strPort);
	m_ctlFtpEx.SetItemText(nIndex,6,strUser);
	m_ctlFtpEx.SetItemText(nIndex,7,strPassword);
	m_ctlFtpEx.SetItemText(nIndex,8,strDirectory);
	m_ctlFtpEx.SetItemText(nIndex,9,strEncoding);
}

void CConfigFTPEx::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	SaveFtpExInfo(m_pstuNasInfoEx);
	
	((CClientDemo5Dlg*)AfxGetMainWnd())->SetFTPEXConfigInfo(m_pstuNasInfoEx,0);	
}
void CConfigFTPEx::SaveFtpExInfo(CFG_NAS_INFO_EX *m_pstuNasInfo)
{
	if(NULL == m_pstuNasInfo)
	{
		return;
	}
	int nCount = m_ctlFtpEx.GetItemCount();	
	nCount = nCount > MAX_NAS_NUM ? MAX_NAS_NUM:nCount;
	
	int i = 0;
	for(i = 0; i < nCount; i ++)
	{
		CFG_NAS_INFO_NEW* pNasInfo = &m_pstuNasInfoEx->stuNasGroup.stuNasInfo[i];
		
		CString Tmp;
		Tmp = m_ctlFtpEx.GetItemText(i,1);
		
		if(Tmp == "True")
		{
			pNasInfo->bEnable = TRUE;
		}
		else
		{
			pNasInfo->bEnable = FALSE;
		}

		Tmp = m_ctlFtpEx.GetItemText(i,2);
		memcpy(pNasInfo->szName, (LPSTR)(LPCTSTR)Tmp, MAX_NAME_LEN);
		
		Tmp = m_ctlFtpEx.GetItemText(i,3);
		if(Tmp == "FTP")
		{
			pNasInfo->nPortocol = 0;
		}
		else if(Tmp == "SMB")
		{
			pNasInfo->nPortocol = 1;
		}
        else if(Tmp == "ISCSI")
        {
            pNasInfo->nPortocol = 2;
        }
        else if(Tmp == "NFS")
        {
            pNasInfo->nPortocol = 3;
		}
		Tmp = m_ctlFtpEx.GetItemText(i,4);
		memcpy(pNasInfo->szAddress, (LPSTR)(LPCTSTR)Tmp, MAX_ADDRESS_LEN);
		
		Tmp = m_ctlFtpEx.GetItemText(i,5);
		pNasInfo->nPort = atol(Tmp);

		
		Tmp = m_ctlFtpEx.GetItemText(i,6);
		memcpy(pNasInfo->szUser, (LPSTR)(LPCTSTR)Tmp, MAX_USERNAME_LEN);

		Tmp = m_ctlFtpEx.GetItemText(i,7);
		memcpy(pNasInfo->szPassword, (LPSTR)(LPCTSTR)Tmp, MAX_PASSWORD_LEN);

		Tmp = m_ctlFtpEx.GetItemText(i,8);
		memcpy(pNasInfo->szDirectory, (LPSTR)(LPCTSTR)Tmp, MAX_NAME_LEN);
		
		Tmp = m_ctlFtpEx.GetItemText(i,9);
		if(Tmp == "UTF8")
		{
			pNasInfo->nCharEncoding = 0;
		}
		else if(Tmp == "GB2312")
		{
			pNasInfo->nCharEncoding = 1;
		}

	}
}
void CConfigFTPEx::OnButtonRead() 
{
	// TODO: Add your control notification handler code here
	CleanAll();

	m_pstuNasInfoEx = new CFG_NAS_INFO_EX;
	if(NULL == m_pstuNasInfoEx)
	{
		return ;
	}
	
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetFTPEXConfigInfo(m_pstuNasInfoEx,0);

	ShowFtpEx(m_pstuNasInfoEx);
}

void CConfigFTPEx::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	int nCount = m_ctlFtpEx.GetItemCount();

	if(nCount >= MAX_NAS_NUM)
	{
		MessageBox(ConvertString("More than  Maxn 16!"), ConvertString("Prompt"));
		return;
	}

	int nTmp = 0;
	int nIndex = 0;

	CString strIndex;
	strIndex.Format("%d" , nCount + 1);

	CString strEnable;
	if(m_ctlEnable.GetCheck())
	{
		strEnable.Format("True");
	}
	else 
	{
		strEnable.Format("False");
	}

	char strTmpName[MAX_NAME_LEN] = {0};
	GetDlgItemText(IDC_EDIT_NAME, strTmpName,MAX_NAME_LEN);
	CString strName;
	strName.Format("%s",strTmpName);

	
	CString strPortocol;
	nIndex = m_ctlPortocol.GetCurSel();
	if(nIndex == 0)
	{
		strPortocol.Format("FTP");
	}
	else if(nIndex == 1)
	{
		strPortocol.Format("SMB");
	}
	else if(nIndex == 2)
	{
		strPortocol.Format("ISCSI");
	}
    else if(nIndex == 3)
    {
        strPortocol.Format("NFS");
	}
	else
	{
		return;
	}
	
	char strTmpAddress[MAX_ADDRESS_LEN] = {0};
	GetDlgItemText(IDC_EDIT_SERVERIP, strTmpAddress, MAX_ADDRESS_LEN);
	CString strAddress;
	strAddress.Format("%s",strTmpAddress);

	
	CString strPort;
	nTmp = GetDlgItemInt(IDC_EDIT_PORT);
	if(nTmp < 0)
	{
		return;
	}
	strPort.Format("%d",nTmp);


	char strTmpUser[MAX_USERNAME_LEN] = {0};
	GetDlgItemText(IDC_EDIT_USERNAME, strTmpUser, MAX_USERNAME_LEN);
	CString strUser;
	strUser.Format("%s", strTmpUser);


	char strTmpPassword[MAX_PASSWORD_LEN] = {0};
	GetDlgItemText(IDC_EDIT_PASSWORD, strTmpPassword, MAX_PASSWORD_LEN);
	CString strPassword;
	strPassword.Format("%s",strTmpPassword);

	char strTmpDirectory[MAX_NAME_LEN] = {0};
	GetDlgItemText(IDC_EDIT_DIRECTORY, strTmpDirectory, MAX_NAME_LEN);
	CString strDirectory;
	strDirectory.Format("%s", strTmpDirectory);
	
	CString strEncoding;
	nIndex = m_ctlEncoding.GetCurSel();
	if(nIndex == 0)
	{
		strEncoding.Format("UTF8");
	}
	else if(nIndex == 1)
	{
		strEncoding.Format("GB2312");
	}	
	else 
	{
		return;
	}
	
	InsertListView(strIndex, strEnable, strName, strPortocol, strAddress, strPort, strUser, strPassword, strDirectory, strEncoding);
}

void CConfigFTPEx::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_ctlFtpEx.GetItemCount())
	{
		if(0 < m_ctlFtpEx.GetSelectedCount())
		{
			int nIndex = m_ctlFtpEx.GetSelectionMark();
			if(-1 != nIndex)
			{
				m_ctlFtpEx.DeleteItem(nIndex);
			}
		}
	}
}

void CConfigFTPEx::OnButtonModify() 
{
	// TODO: Add your control notification handler code here
	if(0 !=	m_ctlFtpEx.GetItemCount())
	{
		if(0 < m_ctlFtpEx.GetSelectedCount())
		{
			int nIndex = m_ctlFtpEx.GetSelectionMark();
			if(-1 != nIndex)
			{
				int nTmp = 0;
				int nTmpIndex = 0;
				CString strEnable;
				if(m_ctlEnable.GetCheck())
				{
					strEnable.Format("True");
				}
				else 
				{
					strEnable.Format("False");
				}
				
				char strTmpName[MAX_NAME_LEN] = {0};
				GetDlgItemText(IDC_EDIT_NAME, strTmpName,MAX_NAME_LEN);
				CString strName;
				strName.Format("%s",strTmpName);
				
				
				CString strPortocol;
				nTmpIndex = m_ctlPortocol.GetCurSel();
				if(nTmpIndex == 0)
				{
					strPortocol.Format("FTP");
				}
				else if(nTmpIndex == 1)
				{
					strPortocol.Format("SMB");
				}
                else if(nTmpIndex == 2)
                {
                    strPortocol.Format("ISCSI");
                }
                else if(nTmpIndex == 3)
                {
                    strPortocol.Format("NFS");
				}
				else
				{
					return;
				}
				
				char strTmpAddress[MAX_ADDRESS_LEN] = {0};
				GetDlgItemText(IDC_EDIT_SERVERIP, strTmpAddress, MAX_ADDRESS_LEN);
				CString strAddress;
				strAddress.Format("%s",strTmpAddress);
				
				
				CString strPort;
				nTmp = GetDlgItemInt(IDC_EDIT_PORT);
				if(nTmp < 0)
				{
					return;
				}
				strPort.Format("%d",nTmp);
				
				
				char strTmpUser[MAX_USERNAME_LEN] = {0};
				GetDlgItemText(IDC_EDIT_USERNAME, strTmpUser, MAX_USERNAME_LEN);
				CString strUser;
				strUser.Format("%s", strTmpUser);
				
				
				char strTmpPassword[MAX_PASSWORD_LEN] = {0};
				GetDlgItemText(IDC_EDIT_PASSWORD, strTmpPassword, MAX_PASSWORD_LEN);
				CString strPassword;
				strPassword.Format("%s",strTmpPassword);
				
				char strTmpDirectory[MAX_NAME_LEN] = {0};
				GetDlgItemText(IDC_EDIT_DIRECTORY, strTmpDirectory, MAX_NAME_LEN);
				CString strDirectory;
				strDirectory.Format("%s", strTmpDirectory);
				
				CString strEncoding;
				nTmpIndex = m_ctlEncoding.GetCurSel();
				if(nTmpIndex == 0)
				{
					strEncoding.Format("UTF8");
				}
				else if(nTmpIndex == 1)
				{
					strEncoding.Format("GB2312");
				}	
				else 
				{
					return;
				}
				m_ctlFtpEx.SetItemText(nIndex, 1, strEnable);
				m_ctlFtpEx.SetItemText(nIndex, 2, strName);
				m_ctlFtpEx.SetItemText(nIndex, 3, strPortocol);
				m_ctlFtpEx.SetItemText(nIndex, 4, strAddress);
				m_ctlFtpEx.SetItemText(nIndex, 5, strPort);
				m_ctlFtpEx.SetItemText(nIndex, 6, strUser);
				m_ctlFtpEx.SetItemText(nIndex, 7, strPassword);
				m_ctlFtpEx.SetItemText(nIndex, 8, strDirectory);
				m_ctlFtpEx.SetItemText(nIndex, 9, strEncoding);
			}
		}
	}
}
void CConfigFTPEx::CleanAll()
{
	m_ctlEncoding.SetCurSel(-1);
	m_ctlPortocol.SetCurSel(-1);
	m_ctlFtpEx.DeleteAllItems();

	SetDlgItemText(IDC_EDIT_SERVERIP,"");
	SetDlgItemText(IDC_EDIT_PORT,"");
	SetDlgItemText(IDC_EDIT_USERNAME,"");
	SetDlgItemText(IDC_EDIT_PASSWORD,"");
	SetDlgItemText(IDC_EDIT_DIRECTORY,"");
	SetDlgItemText(IDC_EDIT_NAME,"");
	
	m_ctlEnable.SetCheck(FALSE);
		
	if(m_pstuNasInfoEx != NULL)
	{
		delete m_pstuNasInfoEx;
		m_pstuNasInfoEx = NULL;
	}
}


void CConfigFTPEx::OnItemchangedListFtpex(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	if (pNMListView ==NULL)
	{
		return;
	}
	
	if (pNMListView->uNewState == 3/* && pNMListView->uOldState == 0*/)
	{
		int nIndex = pNMListView->iItem;
		if(-1 != nIndex)
		{
			CString strTmp;
			strTmp = m_ctlFtpEx.GetItemText(nIndex, 1);

			if(strTmp == "True")
			{
				m_ctlEnable.SetCheck(TRUE);
			}
			else
			{
				m_ctlEnable.SetCheck(FALSE);
			}
			
			strTmp = m_ctlFtpEx.GetItemText(nIndex,2);
			SetDlgItemText(IDC_EDIT_NAME,strTmp);

			strTmp = m_ctlFtpEx.GetItemText(nIndex,3);
			if(strTmp == "FTP")
			{
				m_ctlPortocol.SetCurSel(0);
			}
			else if(strTmp == "SMB")
			{
				m_ctlPortocol.SetCurSel(1);
			}
			else if(strTmp == "ISCSI")
			{
				m_ctlPortocol.SetCurSel(2);
			}
            else if(strTmp == "NFS")
            {
                m_ctlPortocol.SetCurSel(3);
			}


			strTmp = m_ctlFtpEx.GetItemText(nIndex,4);
			SetDlgItemText(IDC_EDIT_SERVERIP,strTmp);


			strTmp = m_ctlFtpEx.GetItemText(nIndex,5);
			SetDlgItemText(IDC_EDIT_PORT,strTmp);


			strTmp = m_ctlFtpEx.GetItemText(nIndex,6);
			SetDlgItemText(IDC_EDIT_USERNAME, strTmp);

			strTmp = m_ctlFtpEx.GetItemText(nIndex,7);
			SetDlgItemText(IDC_EDIT_PASSWORD, strTmp);

			strTmp = m_ctlFtpEx.GetItemText(nIndex,8);
			SetDlgItemText(IDC_EDIT_DIRECTORY, strTmp);

			
			strTmp = m_ctlFtpEx.GetItemText(nIndex,9);
			if(strTmp == "UTF8")
			{
				m_ctlEncoding.SetCurSel(0);
			}
			else if(strTmp == "GB2312")
			{
				m_ctlEncoding.SetCurSel(1);
			}
		
		}
	}
}
void CConfigFTPEx::ShowFtpEx(CFG_NAS_INFO_EX *m_pstuNasInfo)
{
	if(NULL == m_pstuNasInfo)
	{
		return;
	}
	int i = 0;
	if(m_pstuNasInfoEx->nVersion == 1)
	{
		for(i = 0; i < m_pstuNasInfoEx->stuNasGroup.nNasNum; i ++)
		{
			CFG_NAS_INFO_NEW *pNasNew = &m_pstuNasInfo->stuNasGroup.stuNasInfo[i];
			
			CString strIndex;
			strIndex.Format("%d",i+1);

			CString strEnable;
			if(pNasNew->bEnable == TRUE)
			{
				strEnable.Format("True");
			}
			else
			{
				strEnable.Format("False");
			}
			CString strszName;
			strszName.Format("%s",pNasNew->szName);

			CString strPortocol;
			if(pNasNew->nPortocol == 0)
			{
				strPortocol.Format("FTP");
			}
			else if(pNasNew->nPortocol == 1)
			{
				strPortocol.Format("SMB");
			}
			else if(pNasNew->nPortocol == 2)
			{
				strPortocol.Format("ISCSI");
			}
            else if(pNasNew->nPortocol == 3)
            {
                strPortocol.Format("NFS");
			}
			CString strAddress;
			strAddress.Format("%s",pNasNew->szAddress);

			CString strPort;
			strPort.Format("%d",pNasNew->nPort);

			CString strUser;
			strUser.Format("%s",pNasNew->szUser);
			
			CString strPassword;
			strPassword.Format("%s",pNasNew->szPassword);

			CString strDirectory;
			strDirectory.Format("%s",pNasNew->szDirectory);

			CString strEncoding;
			if(pNasNew->nCharEncoding == 0)
			{
				strEncoding.Format("UTF8");
			}
			else if(pNasNew->nCharEncoding == 1)
			{
				strEncoding.Format("GB2312");
			}
			InsertListView(strIndex, strEnable, strszName, strPortocol, strAddress, strPort, strUser, strPassword, strDirectory, strEncoding);
		}
	}
}
