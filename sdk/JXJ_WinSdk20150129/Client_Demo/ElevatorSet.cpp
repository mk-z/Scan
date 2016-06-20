// ElevatorSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "ElevatorSet.h"
#include "Pub_Data.h"

// CElevatorSet 对话框



IMPLEMENT_DYNAMIC(CElevatorSet, CDialog)

CElevatorSet::CElevatorSet(CWnd* pParent /*=NULL*/)
	: CDialog(CElevatorSet::IDD, pParent)
	, m_cstrItemTextEdit(_T(""))
{
	ZeroMemory(&m_elevatorCfg, sizeof(m_elevatorCfg));
}

CElevatorSet::~CElevatorSet()
{
}

void CElevatorSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_THETOP, m_editTop);
	DDX_Control(pDX, IDC_EDIT2, m_editCurrent);
	DDX_Control(pDX, IDC_LIST_FLOOR, m_floorList);
	DDX_Control(pDX, IDC_EDIT_LISTEDIT, m_SubItemEdit);
	DDX_Text(pDX, IDC_EDIT_LISTEDIT, m_cstrItemTextEdit);
	DDX_Control(pDX, IDC_EDIT_ADD, m_loopAdd);
	DDX_Control(pDX, IDC_EDIT_TEXTX, m_showTextX);
	DDX_Control(pDX, IDC_EDIT_TEXTY, m_showTextY);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_showTextColor);
}


BEGIN_MESSAGE_MAP(CElevatorSet, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SETTOP, &CElevatorSet::OnBnClickedButtonSettop)
	ON_BN_CLICKED(IDC_BUTTON_SETCURRENT, &CElevatorSet::OnBnClickedButtonSetcurrent)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CElevatorSet::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CElevatorSet::OnBnClickedButtonSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FLOOR, &CElevatorSet::OnNMDblclkListFloor)
	ON_EN_KILLFOCUS(IDC_EDIT_LISTEDIT, &CElevatorSet::OnEnKillfocusEditListedit)
	ON_BN_CLICKED(IDC_BUTTON_SETLOOPADD, &CElevatorSet::OnBnClickedButtonSetloopadd)
END_MESSAGE_MAP()


// CElevatorSet 消息处理程序
BOOL CElevatorSet::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_SubItemEdit.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_SETCURRENT)->ShowWindow(SW_HIDE);

	m_floorList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);
	CRect rc;
	m_floorList.GetWindowRect(&rc);
	int nWidth = rc.Width() / 2;
	

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_floorList.InsertColumn(0 , _T("楼层ID"), 2, 100, -1);
		m_floorList.InsertColumn(1 , _T("楼层别名"), 2, 100,-1);

		m_showTextColor.EnableAutomaticButton(_T("默认值"), RGB(0, 0, 0)); 
		m_showTextColor.EnableOtherButton(_T("其余颜色")); 
		m_showTextColor.SetColor((COLORREF)-1); 
		m_showTextColor.SetColumnsNumber(10);     
	}
	else
	{
		m_floorList.InsertColumn(0 , _T("Floor ID "), 2, 100, -1);
		m_floorList.InsertColumn(1 , _T("Floor alias"), 2, 100,-1);

		m_showTextColor.EnableAutomaticButton(_T("Windows default"), RGB(0, 0, 0)); 
		m_showTextColor.EnableOtherButton(_T("Other colors ")); 
		m_showTextColor.SetColor((COLORREF)-1); 
		m_showTextColor.SetColumnsNumber(10);     
	}

	return TRUE;
}

void CElevatorSet::OnBnClickedButtonSettop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_floorList.DeleteAllItems();

	CString strCount;
	m_editTop.GetWindowText(strCount);
	int iCount = _ttoi(strCount);
	m_elevatorCfg.thetop = iCount;
	CString strID = _T("");
	CString strText = _T("");
	for(int i = 0; i < iCount; i ++)
	{
		strID.Format(_T("%d"), i+1);
		m_floorList.InsertItem(i,strID);
		strText.Format(_T("%s"), m_elevatorCfg.layername[i]);
		m_floorList.SetItemText(i,1, strText);
	}
}

void CElevatorSet::OnBnClickedButtonSetcurrent()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CElevatorSet::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ELEVATOR_CFG, (char *)&m_elevatorCfg, sizeof(m_elevatorCfg),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox(g_PubData.g_strGetMessage);
		return ;
	}
}

void CElevatorSet::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码


	CString strText = _T("");

	m_editTop.GetWindowText(strText);
	m_elevatorCfg.thetop = _ttoi(strText);

	
	m_editCurrent.GetWindowText(strText);
	m_elevatorCfg.thecurrent = _ttoi(strText) - 1;


	m_showTextX.GetWindowText(strText);
	m_elevatorCfg.osd_display_x = _ttoi(strText);

	m_showTextY.GetWindowText(strText);
	m_elevatorCfg.osd_display_y =  _ttoi(strText);

	if(m_elevatorCfg.osd_display_x > 704 || m_elevatorCfg.osd_display_y > 576 ||
	   m_elevatorCfg.osd_display_x < 0 || m_elevatorCfg.osd_display_y < 0)
	{
		AfxMessageBox(_T("设置坐标错误!"));
		return;
	}
	

	m_elevatorCfg.osd_display_color = m_showTextColor.GetColor();

	for(int i = 0; i < m_elevatorCfg.thetop; i ++)
	{
		strText = m_floorList.GetItemText(i,1);
		if(strText.GetLength() >= 20)
		{
			CString strText;
			strText.Format(_T("第 %d 层楼层别名设置过长！"), i+1);
			AfxMessageBox(strText);
			return;

		}
		memset(m_elevatorCfg.layername[i], 0, 20);
		memcpy(m_elevatorCfg.layername[i], strText, strText.GetLength());
	}
	strText.ReleaseBuffer();
	
	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_ELEVATOR_CFG, (char *)&m_elevatorCfg, sizeof(m_elevatorCfg), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return ;
	}
}



int CElevatorSet::RedrawWindow()
{

	CString strText = _T("");
	strText.Format(_T("%d"), m_elevatorCfg.thetop);
	m_editTop.SetWindowText(strText);

	strText.Format(_T("%d"),m_elevatorCfg.thecurrent+1);
	m_editCurrent.SetWindowText(strText);
	
	m_showTextColor.SetColor(m_elevatorCfg.osd_display_color);

	strText.Format(_T("%d"), m_elevatorCfg.osd_display_x);
	m_showTextX.SetWindowText(strText);

	strText.Format(_T("%d"), m_elevatorCfg.osd_display_y);
	m_showTextY.SetWindowText(strText);

	strText.ReleaseBuffer();

	OnBnClickedButtonSettop();

	return 0;
}



void CElevatorSet::OnNMDblclkListFloor(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW *pNMListCtrl = (NM_LISTVIEW *)pNMHDR;  
	if(pNMListCtrl->iSubItem == 0)
		return;
	if(pNMListCtrl->iItem != -1)  
	{  
		CRect rect,dlgRect;  
		//获得当前列的宽度以适应如果用户调整宽度   
		//此处不用获得的子项rect矩形框来设置宽度   
		//是因第一列时返回的宽度是整行的宽度，我也不知道为啥   
		int width = m_floorList.GetColumnWidth(pNMListCtrl->iSubItem);  
		m_floorList.GetSubItemRect(pNMListCtrl->iItem,pNMListCtrl->iSubItem,LVIR_BOUNDS,rect);  
		//保存选择的列表项索引   
		//这个因为我是用了两个列表控件一个CEdit   
		//所以需要保存列表的索引   
		//以及子项相对应的行列号索引   
		m_listSelFlag[0] = 1;//列表1   
		m_listSelFlag[1] = pNMListCtrl->iItem;  
		m_listSelFlag[2] = pNMListCtrl->iSubItem;  
	
		//获得listctrl矩形框   
		//获得父对话框的位置以调整CEdit的显示位置，具体见下面代码   
		m_floorList.GetWindowRect(&dlgRect);  
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


	//*pResult = 0;
}


void CElevatorSet::SetListItemText(void)  
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
		m_floorList.SetItemText(m_listSelFlag[1],m_listSelFlag[2],m_cstrItemTextEdit);  
		m_SubItemEdit.SetWindowText("");  
		m_SubItemEdit.ShowWindow(SW_HIDE);  
	}  
	//强制刷新列表控件（否则视觉上有感觉有点不爽，可以试试^_^）   
	//m_ListCtrlNotSell.Invalidate();  
}  

void CElevatorSet::OnEnKillfocusEditListedit()
{
	// TODO: 在此添加控件通知处理程序代码
	SetListItemText();  
}


BOOL CElevatorSet::PreTranslateMessage(MSG* pMsg)  
{  
	// TODO: 在此添加专用代码和/或调用基类   
	if ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN )   
	{     
		if( GetFocus()->GetDlgCtrlID() == IDC_EDIT2)  
		{  
			if(m_cstrItemTextEdit[0] == 1)  
				m_floorList.SetFocus();//使列表控件获得焦点，则CEdit会自动失去焦点，触发EN_KILLFOCUS消息   
// 			if(m_cstrItemTextEdit[0] == 2)  
// 				m_ListCtrlNotSell.SetFocus();  
		}  
		return TRUE;  
	}  
	return CDialog::PreTranslateMessage(pMsg);  
}  

void CElevatorSet::OnBnClickedButtonSetloopadd()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString strText = _T("");
	m_loopAdd.GetWindowText(strText);
	int nIndex = _ttoi(strText);
	if(nIndex < 1)
	{
		AfxMessageBox(_T("输入有误！"));
		return;
	}

	CString strIndex = m_floorList.GetItemText(nIndex-1, 1);
	int iValue = _ttoi(strIndex);
	int j = 0;

	for(int i = nIndex-1; i < m_elevatorCfg.thetop; i++)
	{
		strText.Format(_T("%d"), iValue+j);
		m_floorList.SetItemText(i, 1, strText);
		j++;
	}

}
