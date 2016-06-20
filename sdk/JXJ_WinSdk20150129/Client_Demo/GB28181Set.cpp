// GB28181Set.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "GB28181Set.h"
#include "Pub_Data.h"


// CGB28181Set 对话框


IMPLEMENT_DYNAMIC(CGB28181Set, CDialog)

CGB28181Set::CGB28181Set(CWnd* pParent /*=NULL*/)
	: CDialog(CGB28181Set::IDD, pParent)
	, m_cstrItemTextEdit(_T(""))
{

	ZeroMemory(&m_gb28181, sizeof(m_gb28181));
	ZeroMemory(&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg));
	m_iSelChannel = 0;
}

CGB28181Set::~CGB28181Set()
{
	DestroyWindow();
}

void CGB28181Set::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DEVICEID, m_DEVid);
	DDX_Control(pDX, IDC_EDIT_DEVICEPASS, m_DEVpass);
	DDX_Control(pDX, IDC_EDITSERVERID, m_SERVERid);
	DDX_Control(pDX, IDC_EDITSERVERIP, m_SERVERip);
	DDX_Control(pDX, IDC_EDITSERVERPORT, m_SERVERport);
	DDX_Control(pDX, IDC_EDITSERVERMSG, m_SERVERmsg);
	DDX_Control(pDX, IDC_EDIT_CHANNELID, m_channelID);
	DDX_Control(pDX, IDC_COMBO_CHANNELNO, m_channelNo);
	DDX_Control(pDX, IDC_LIST_CHANNELID, m_channelIDlist);
	DDX_Control(pDX, IDC_EDIT_EDITCHANNEL, m_SubItemEdit);
	DDX_Text(pDX, IDC_EDIT_EDITCHANNEL, m_cstrItemTextEdit);
}


BEGIN_MESSAGE_MAP(CGB28181Set, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CGB28181Set::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CGB28181Set::OnBnClickedButtonFlash)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNELNO, &CGB28181Set::OnCbnSelchangeComboChannelno)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CHANNELID, &CGB28181Set::OnNMDblclkListChannelid)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST_CHANNELID, &CGB28181Set::OnNMKillfocusListChannelid)
	ON_EN_KILLFOCUS(IDC_EDIT_EDITCHANNEL, &CGB28181Set::OnEnKillfocusEditEditchannel)
END_MESSAGE_MAP()


// CGB28181Set 消息处理程序

BOOL CGB28181Set::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_channelID.ShowWindow(SW_HIDE);
	m_channelNo.ShowWindow(SW_HIDE);
	m_SubItemEdit.ShowWindow(SW_HIDE);

	m_channelIDlist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
	CRect rc;
	m_channelIDlist.GetWindowRect(&rc);
	int nWidth = rc.Width() / 5;
	m_channelIDlist.InsertColumn(0 , _T("通道号"), 2, nWidth-5, -1);
	m_channelIDlist.InsertColumn(1 , _T("通道ID"), 2, nWidth*4-5,-1);

	
	return TRUE;
}


void CGB28181Set::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strText = _T("");
	m_DEVid.GetWindowText(strText);
	memset(m_gb28181.device_id, '\0', sizeof(m_gb28181.device_id));
	memcpy(m_gb28181.device_id, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_DEVpass.GetWindowText(strText);
	memset(m_gb28181.device_pwd, '\0', sizeof(m_gb28181.device_pwd));
	memcpy(m_gb28181.device_pwd, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_SERVERid.GetWindowText(strText);
	memset(m_gb28181.server_id, '\0', sizeof(m_gb28181.server_id));
	memcpy(m_gb28181.server_id, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	m_SERVERip.GetWindowText(strText);
	memset(m_gb28181.server_ip, '\0', sizeof(m_gb28181.server_ip));
	memcpy(m_gb28181.server_ip, strText.GetBuffer(0), strText.GetLength());
	strText.ReleaseBuffer();

	

	m_SERVERport.GetWindowText(strText);
	m_gb28181.server_port = _ttoi(strText);

	m_SERVERmsg.GetWindowText(strText);
	m_gb28181.msg_port = _ttoi(strText);

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_CFG, (char *)&m_gb28181, sizeof(m_gb28181), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
	

	CString strID;
	for(int i = 0; i < m_channelIDlist.GetItemCount(); i++)
	{
		strID = m_channelIDlist.GetItemText(i, 1);
		memset(m_gb28181ChannelCfg.channel_id[i], '\0', sizeof(m_gb28181ChannelCfg.channel_id[i]));
		memcpy(m_gb28181ChannelCfg.channel_id[i], strID.GetBuffer(0), strID.GetLength());
	}
	strID.ReleaseBuffer();


	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_NVR_CH_CFG, (char *)&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strSetMessage);
		return ;
	}
}

void CGB28181Set::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strID;
	if(m_channelNo.GetCurSel() < 0 )
	{
		for(int i = 0; i< g_PubData.g_iChannelNo; i++)
		{
			CString str = _T("");
			str.Format(_T("%d"), i);
			m_channelNo.AddString(str);

			strID.Format(_T("%d"), i+1);
			m_channelIDlist.InsertItem(i,strID);
			m_channelIDlist.SetItemText(i,1, "");
		}
		m_channelNo.SetCurSel(0);
		m_iSelChannel = 0;
	}

	m_iSelChannel = m_channelNo.GetCurSel();
	int iRet = -1;

	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_CFG, (char *)&m_gb28181, sizeof(m_gb28181),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}

	
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_GB28181_PROTO_NVR_CH_CFG, (char *)&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshWindow();
	ReFreshChannelCfgWindow();
}


int CGB28181Set::ReFreshWindow()
{
	CString strText = _T("");
	strText.Format(_T("%s"), m_gb28181.device_id);
	
	m_DEVid.SetWindowText(strText);

	strText.Format(_T("%s"), m_gb28181.device_pwd);
	m_DEVpass.SetWindowText(strText);

	strText.Format(_T("%s"), m_gb28181.server_id);
	m_SERVERid.SetWindowText(strText);

	strText.Format(_T("%s"), m_gb28181.server_ip);
	m_SERVERip.SetWindowText(strText);

	strText.Format(_T("%d"), m_gb28181.server_port);
	m_SERVERport.SetWindowText(strText);

	strText.Format(_T("%d"), m_gb28181.msg_port);
	m_SERVERmsg.SetWindowText(strText);

	return 0;
}



int CGB28181Set::ReFreshChannelCfgWindow()
{
	
	CString strText = _T("");
	for(int i= 0; i < g_PubData.g_iChannelNo; i++)
	{	
		strText.Format(_T("%s"), m_gb28181ChannelCfg.channel_id[i]);
		//gGb28181Set->m_channelID.SetWindowText(strText);

		m_channelIDlist.SetItemText(i, 1, strText);
	}	
	
	return 0;
}


void CGB28181Set::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CGB28181Set::OnCbnSelchangeComboChannelno()
{
	// TODO: 在此添加控件通知处理程序代码

	m_iSelChannel = m_channelNo.GetCurSel();
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],m_iSelChannel,PARAM_GB28181_PROTO_CFG, (char *)&m_gb28181, sizeof(m_gb28181),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}


	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],m_iSelChannel,PARAM_GB28181_PROTO_NVR_CH_CFG, (char *)&m_gb28181ChannelCfg, sizeof(m_gb28181ChannelCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}
	ReFreshWindow();
	ReFreshChannelCfgWindow();
}

void CGB28181Set::OnNMDblclkListChannelid(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;

	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;  
	if(pNMListCtrl->iSubItem == 0)
		return;
	if(pNMListCtrl->iItem != -1)  
	{  
		CRect rect,dlgRect;  
		//获得当前列的宽度以适应如果用户调整宽度   
		//此处不用获得的子项rect矩形框来设置宽度   
		//是因第一列时返回的宽度是整行的宽度，我也不知道为啥   
		int width = m_channelIDlist.GetColumnWidth(pNMListCtrl->iSubItem);  
		m_channelIDlist.GetSubItemRect(pNMListCtrl->iItem,pNMListCtrl->iSubItem,LVIR_BOUNDS,rect);  
		//保存选择的列表项索引   
		//这个因为我是用了两个列表控件一个CEdit   
		//所以需要保存列表的索引   
		//以及子项相对应的行列号索引   
		m_listSelFlag[0] = 1;//列表1   
		m_listSelFlag[1] = pNMListCtrl->iItem;  
		m_listSelFlag[2] = pNMListCtrl->iSubItem;  

		//获得listctrl矩形框   
		//获得父对话框的位置以调整CEdit的显示位置，具体见下面代码   
		m_channelIDlist.GetWindowRect(&dlgRect);  
		//调整与父窗口对应   
		ScreenToClient(&dlgRect);  
		int height = rect.Height();  
		rect.top += (dlgRect.top+1);  
		rect.left += (dlgRect.left+1);  
		rect.bottom = rect.top+height+2;  
		rect.right = rect.left+width+2;  
		m_SubItemEdit.MoveWindow(&rect);  
		m_SubItemEdit.ShowWindow(SW_SHOW);  
		m_SubItemEdit.SetFocus();  
	}  





}


void CGB28181Set::SetListItemText(void)  
{  
	UpdateData(TRUE);  
	//AfxMessageBox(cstrItemTextEdit);   
	// 	if(m_listSelFlag[0] == 2)//出售列表   
	// 	{  
	// 		//此处的m_cstrItemTextEdit是CEdit控件的字符串关联变量   
	// 		m_ListCtrlNotSell.SetItemText(m_listSelFlag[1],m_listSelFlag[2],m_cstrItemTextEdit);  
	// 		//重置编辑框文本   
	// 		m_SubItemEdit.SetWindowText("");  
	// 		//隐藏编辑框   
	// 		m_SubItemEdit.ShowWindow(SW_HIDE);  
	// 	}  
	if(m_listSelFlag[0] == 1)//购买列表   
	{  
		m_channelIDlist.SetItemText(m_listSelFlag[1],m_listSelFlag[2],m_cstrItemTextEdit);  
		m_SubItemEdit.SetWindowText("");  
		m_SubItemEdit.ShowWindow(SW_HIDE);  
	}  
	//强制刷新列表控件（否则视觉上有感觉有点不爽，可以试试^_^）   
	//m_ListCtrlNotSell.Invalidate();  
}  
void CGB28181Set::OnNMKillfocusListChannelid(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	
}


BOOL CGB28181Set::PreTranslateMessage(MSG* pMsg)  
{  
	// TODO: 在此添加专用代码和/或调用基类   
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )   
	{     
		if( GetFocus()->GetDlgCtrlID() == IDC_EDIT_EDITCHANNEL)  
		{  
			if(m_listSelFlag[0] == 1)  
				m_channelIDlist.SetFocus();//使列表控件获得焦点，则CEdit会自动失去焦点，触发EN_KILLFOCUS消息   
			// 			if(m_cstrItemTextEdit[0] == 2)  
			// 				m_ListCtrlNotSell.SetFocus();  
		}  
		return TRUE;  
	}  
	return CDialog::PreTranslateMessage(pMsg);  
}  
void CGB28181Set::OnEnKillfocusEditEditchannel()
{
	// TODO: 在此添加控件通知处理程序代码
	SetListItemText();
}
