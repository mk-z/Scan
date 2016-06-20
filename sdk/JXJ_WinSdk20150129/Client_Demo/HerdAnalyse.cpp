// HerdAnalyse.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "HerdAnalyse.h"
#include "Pub_Data.h"



#define  DRAWCOLOR RGB(255,0,0)
// CHerdAnalyse 对话框
CHerdAnalyse *gHerdAnalyseDlg = NULL;
JHerdAnalyse  gHerdAnalyse;
IMPLEMENT_DYNAMIC(CHerdAnalyse, CDialog)

CHerdAnalyse::CHerdAnalyse(CWnd* pParent /*=NULL*/)
	: CDialog(CHerdAnalyse::IDD, pParent)
{
	gHerdAnalyseDlg = this;
}

CHerdAnalyse::~CHerdAnalyse()
{
}

void CHerdAnalyse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLE, m_enable);
	DDX_Control(pDX, IDC_COMBO_UPLOAD, m_upInterval);
	DDX_Control(pDX, IDC_COMBO_QUADR, m_quadr);
	DDX_Control(pDX, IDC_EDIT1, m_quadrID);
	DDX_Control(pDX, IDC_EDIT2, m_quadrName);
	DDX_Control(pDX, IDC_EDIT3, m_inner_percent);
	DDX_Control(pDX, IDC_EDIT4, m_outer_percent);
	DDX_Control(pDX, IDC_SLIDER7, m_edge);
	DDX_Control(pDX, IDC_SLIDER1, m_binary);
	DDX_Control(pDX, IDC_SLIDER2, m_blur);
	DDX_Control(pDX, IDC_SLIDER3, m_contour);
	DDX_Control(pDX, IDC_SLIDER4, m_dilate);
	DDX_Control(pDX, IDC_SLIDER5, m_erode);
	DDX_Control(pDX, IDC_SLIDER6, m_hierarchy);
	DDX_Control(pDX, IDC_SLIDER8, m_mask);
}


BEGIN_MESSAGE_MAP(CHerdAnalyse, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHerdAnalyse::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CHerdAnalyse::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_TIMESET, &CHerdAnalyse::OnBnClickedButtonTimeset)
	ON_CBN_SELCHANGE(IDC_COMBO_QUADR, &CHerdAnalyse::OnCbnSelchangeComboQuadr)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CHerdAnalyse::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CHerdAnalyse 消息处理程序
BOOL CHerdAnalyse::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_herdAnalyseScreen.Create(IDD_DIALOG_HerdAnalyseScreen, this);
	m_herdAnalyseScreen.MoveWindow(30,60,520,300,TRUE);
	m_herdAnalyseScreen.ShowWindow(SW_SHOW);


	for(int i=0;i < 11; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		m_upInterval.AddString(str);
	}

	for(int i = 0; i < MAX_TROUGH_SIZE; i++)
	{
		CString strId;
		strId.Format(_T("%d"), i);
		m_quadr.AddString(strId);
	}
	m_quadr.SetCurSel(0);

	m_edge.SetRange(0,255);
	m_binary.SetRange(0,255);
	m_blur.SetRange(0,255);
	m_contour.SetRange(0,255);
	m_dilate.SetRange(0,255);
	m_erode.SetRange(0,255);
	m_hierarchy.SetRange(0,255);
	m_mask.SetRange(0,255);

	return TRUE;
}


void CHerdAnalyse::SliderCtrlSetPos()
{
	CString strShow = _T("");
	strShow.Format(_T("%d"),  m_edge.GetPos());
	GetDlgItem(IDC_STATIC_TEXT1)->SetWindowText(strShow);

	strShow.Format(_T("%d"),  m_binary.GetPos());
	GetDlgItem(IDC_STATIC_TEXT2)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_blur.GetPos());
	GetDlgItem(IDC_STATIC_TEXT3)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_contour.GetPos());
	GetDlgItem(IDC_STATIC_TEXT4)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_dilate.GetPos());
	GetDlgItem(IDC_STATIC_TEXT5)->SetWindowText(strShow);

	strShow.Format(_T("%d"),  m_erode.GetPos());
	GetDlgItem(IDC_STATIC_TEXT6)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_hierarchy.GetPos());
	GetDlgItem(IDC_STATIC_TEXT7)->SetWindowText(strShow);

	strShow.Format(_T("%d"), m_mask.GetPos());
	GetDlgItem(IDC_STATIC_TEXT8)->SetWindowText(strShow);

}

void CHerdAnalyse::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

	gHerdAnalyse.smart.ucEdgeParam = gHerdAnalyseDlg->m_edge.GetPos();
	gHerdAnalyse.smart.ucBinaryParam = gHerdAnalyseDlg->m_binary.GetPos();
	gHerdAnalyse.smart.ucBlurParam = gHerdAnalyseDlg->m_blur.GetPos();
	gHerdAnalyse.smart.ucContourParam = gHerdAnalyseDlg->m_contour.GetPos();
	gHerdAnalyse.smart.ucDilateParam = gHerdAnalyseDlg->m_dilate.GetPos();
	gHerdAnalyse.smart.ucErodeParam = gHerdAnalyseDlg->m_erode.GetPos();
	gHerdAnalyse.smart.ucHierarchyParam = gHerdAnalyseDlg->m_hierarchy.GetPos();
	gHerdAnalyse.smart.ucMaskParam = gHerdAnalyseDlg->m_mask.GetPos();

	gHerdAnalyse.fodder_eable = m_enable.GetCheck();
	gHerdAnalyse.report_intv = m_upInterval.GetCurSel();
	
	int nIndex = m_quadr.GetCurSel();

	CString strText = _T("");
	m_quadrID.GetWindowText(strText);
	int nId = _ttoi(strText);
	if(nId < 0 || nId >65535)
	{
		AfxMessageBox(_T("槽的ID在0到65535之间"));
		return;
	}
	gHerdAnalyse.field.trough[nIndex].id = nId;

	m_quadrName.GetWindowText(strText);
	memset(gHerdAnalyse.field.trough[nIndex].name, 0, J_SDK_MAX_NAME_LEN);
	memcpy(gHerdAnalyse.field.trough[nIndex].name, strText.GetBuffer(), strText.GetLength());
	strText.ReleaseBuffer();

	m_inner_percent.GetWindowText(strText);
	gHerdAnalyse.field.trough[nIndex].inner_percent = _ttoi(strText);

	m_outer_percent.GetWindowText(strText);
	gHerdAnalyse.field.trough[nIndex].outer_percent = _ttoi(strText);
	


	CRect cRect;
	m_herdAnalyseScreen.GetWindowRect(cRect);
	int iDeviceWidth;
	int iDeviceHeight;
	iDeviceWidth = gHerdAnalyse.max_width;
	iDeviceHeight = gHerdAnalyse.max_height;

	for(int i = 0; i < 4; i++)
	{
		gHerdAnalyse.field.trough[nIndex].inner_quadr.angle[i].x = (int)((m_herdAnalyseScreen.m_innerPoint[i].x * iDeviceWidth)/cRect.Width());
		gHerdAnalyse.field.trough[nIndex].inner_quadr.angle[i].y = (int)((m_herdAnalyseScreen.m_innerPoint[i].y * iDeviceHeight) /cRect.Height());
	}

	for(int i = 0; i < 4; i++)
	{
		gHerdAnalyse.field.trough[nIndex].outer_quadr.angle[i].x = (int)((m_herdAnalyseScreen.m_outerPoint[i].x * iDeviceWidth)/cRect.Width());
		gHerdAnalyse.field.trough[nIndex].outer_quadr.angle[i].y = (int)((m_herdAnalyseScreen.m_outerPoint[i].y * iDeviceHeight) /cRect.Height());
	}

// 	int iRet = -1;
// 	jcu_notify_cb_t notify;
// 	notify.callback = SetHerdAnalyseCallBack;
// 	notify.is_sync = JCU_OP_ASYNC;
// 	notify.user_arg = NULL;
// 
// 	iRet = jcu_net_cfg_set(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_HERD_ANALYSE,(char *)&gHerdAnalyse, sizeof(JHerdAnalyse), &notify );
// 	if( iRet != 0)
// 	{
// 		AfxMessageBox(_T("Set"), g_PubData.g_strSetMessage);
// 		return ;
// 	}
}

void CHerdAnalyse::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	if(g_PubData.g_iPlayWndFlag != 9 )
	{
		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL, m_herdAnalyseScreen.GetSafeHwnd(),NULL,NULL);
	}

// 	int iRet = -1;
// 	jcu_notify_cb_t notify;
// 	notify.callback =HerdAnalyseCallBack;
// 	notify.is_sync = JCU_OP_ASYNC;
// 	notify.user_arg = NULL;
// 
// 
// 	iRet = jcu_net_cfg_get(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_HERD_ANALYSE,NULL, sizeof(JHerdAnalyse), &notify );
// 	if( iRet != 0)
// 	{
// 		AfxMessageBox(_T("Get"), g_PubData.g_strGetMessage);
// 		return ;
// 	}

//	m_herdAnalyseScreen.RegDrawCallBack();
}


// int CHerdAnalyse::HerdAnalyseCallBack(struct _jcu_notify_cb_s *handle, jcu_cb_parm_t *parm)
// {
// 	
// 	ZeroMemory(&gHerdAnalyse,sizeof(JHerdAnalyse));
// 	int copy_size = parm->size;
// 	if(copy_size > sizeof(gHerdAnalyse))
// 	{
// 		copy_size = sizeof(gHerdAnalyse);
// 	}
// 	memcpy(&gHerdAnalyse, parm->data, copy_size);
// 	
// 	gHerdAnalyseDlg->m_enable.SetCheck(gHerdAnalyse.fodder_eable);
// 	gHerdAnalyseDlg->m_upInterval.SetCurSel(gHerdAnalyse.report_intv);
// 
// 	gHerdAnalyseDlg->m_edge.SetPos(gHerdAnalyse.smart.ucEdgeParam);
// 	gHerdAnalyseDlg->m_binary.SetPos(gHerdAnalyse.smart.ucBinaryParam);
// 	gHerdAnalyseDlg->m_blur.SetPos(gHerdAnalyse.smart.ucBlurParam);
// 	gHerdAnalyseDlg->m_contour.SetPos(gHerdAnalyse.smart.ucContourParam);
// 	gHerdAnalyseDlg->m_dilate.SetPos(gHerdAnalyse.smart.ucDilateParam);
// 	gHerdAnalyseDlg->m_erode.SetPos(gHerdAnalyse.smart.ucErodeParam);
// 	gHerdAnalyseDlg->m_hierarchy.SetPos(gHerdAnalyse.smart.ucHierarchyParam);
// 	gHerdAnalyseDlg->m_mask.SetPos(gHerdAnalyse.smart.ucMaskParam);
// 
// 
// 	gHerdAnalyseDlg->m_herdAnalyseScreen.RegDrawCallBack();
// 
// 	gHerdAnalyseDlg->OnCbnSelchangeComboQuadr();
// 
// 	gHerdAnalyseDlg->SliderCtrlSetPos();
// 
// 	
// 	return 0;
// }


void CHerdAnalyse::SetWndData()
{
	
	CRect cRect;
	m_herdAnalyseScreen.GetWindowRect(cRect);
	int iW = cRect.Width();
	int iH=  cRect.Height();
	int nIndex = m_quadr.GetCurSel();
	int innerFlag = 0;
	int outerFlag = 0;
	if(gHerdAnalyse.max_width <= 0 || gHerdAnalyse.max_height <= 0)
	{
		AfxMessageBox(_T("获取到的设备信息错误！"));
		return;
	}
	for(int i = 0; i < 4; i++)
	{
		m_herdAnalyseScreen.m_innerPoint[i].x = (gHerdAnalyse.field.trough[nIndex].inner_quadr.angle[i].x*iW)/gHerdAnalyse.max_width;
		m_herdAnalyseScreen.m_innerPoint[i].y = (gHerdAnalyse.field.trough[nIndex].inner_quadr.angle[i].y*iH)/gHerdAnalyse.max_height;
		if(m_herdAnalyseScreen.m_innerPoint[i].x > 0 || m_herdAnalyseScreen.m_innerPoint[i].y > 0)
		{
			innerFlag = 1;
		}
		m_herdAnalyseScreen.m_outerPoint[i].x = (gHerdAnalyse.field.trough[nIndex].outer_quadr.angle[i].x*iW)/gHerdAnalyse.max_width;
		m_herdAnalyseScreen.m_outerPoint[i].y = (gHerdAnalyse.field.trough[nIndex].outer_quadr.angle[i].y*iH)/gHerdAnalyse.max_height;
		if(m_herdAnalyseScreen.m_outerPoint[i].x > 0 || m_herdAnalyseScreen.m_outerPoint[i].y > 0)
		{
			outerFlag = 1;
		}
	}

	

	if(innerFlag)
		m_herdAnalyseScreen.m_nInnerNum = 4;
	if(outerFlag)
		m_herdAnalyseScreen.m_nOuterNum = 4;

	

}

void CHerdAnalyse::ShowVideoTime(int iIndex)
{

	g_PubData.g_iVideoTime1 = gHerdAnalyse.week.days[iIndex].seg[0].enable;
	g_PubData.g_iVideoTime2 = gHerdAnalyse.week.days[iIndex].seg[1].enable;
	g_PubData.g_iVideoTime3 = gHerdAnalyse.week.days[iIndex].seg[2].enable;
	g_PubData.g_iVideoTime4 = gHerdAnalyse.week.days[iIndex].seg[3].enable;
	if(gHerdAnalyse.week.days[iIndex].seg[0].enable == 1)
	{
		int iY = gHerdAnalyse.week.days[iIndex].seg[0].time_start.hour;
		int iM = gHerdAnalyse.week.days[iIndex].seg[0].time_start.minute;
		int iD = gHerdAnalyse.week.days[iIndex].seg[0].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime1 = Stime;

		iY = gHerdAnalyse.week.days[iIndex].seg[0].time_end.hour;
		iM = gHerdAnalyse.week.days[iIndex].seg[0].time_end.minute;
		iD = gHerdAnalyse.week.days[iIndex].seg[0].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime1 = Etime;

	}
	if(gHerdAnalyse.week.days[iIndex].seg[1].enable == 1)
	{
		int iY = gHerdAnalyse.week.days[iIndex].seg[1].time_start.hour;
		int iM = gHerdAnalyse.week.days[iIndex].seg[1].time_start.minute;
		int iD = gHerdAnalyse.week.days[iIndex].seg[1].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime2 = Stime;

		iY = gHerdAnalyse.week.days[iIndex].seg[1].time_end.hour;
		iM = gHerdAnalyse.week.days[iIndex].seg[1].time_end.minute;
		iD = gHerdAnalyse.week.days[iIndex].seg[1].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime2 = Etime;
	}
	if(gHerdAnalyse.week.days[iIndex].seg[2].enable == 1)
	{
		int iY = gHerdAnalyse.week.days[iIndex].seg[2].time_start.hour;
		int iM = gHerdAnalyse.week.days[iIndex].seg[2].time_start.minute;
		int iD = gHerdAnalyse.week.days[iIndex].seg[2].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime3 = Stime;

		iY = gHerdAnalyse.week.days[iIndex].seg[2].time_end.hour;
		iM = gHerdAnalyse.week.days[iIndex].seg[2].time_end.minute;
		iD = gHerdAnalyse.week.days[iIndex].seg[2].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime3 = Etime;
	}
	if(gHerdAnalyse.week.days[iIndex].seg[3].enable == 1)
	{
		int iY = gHerdAnalyse.week.days[iIndex].seg[3].time_start.hour;
		int iM = gHerdAnalyse.week.days[iIndex].seg[3].time_start.minute;
		int iD = gHerdAnalyse.week.days[iIndex].seg[3].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime4 = Stime;

		iY = gHerdAnalyse.week.days[iIndex].seg[3].time_end.hour;
		iM = gHerdAnalyse.week.days[iIndex].seg[3].time_end.minute;
		iD = gHerdAnalyse.week.days[iIndex].seg[3].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime4 = Etime;
	}
}


void CHerdAnalyse::OnBnClickedButtonTimeset()
{
	// TODO: 在此添加控件通知处理程序代码
	g_PubData.g_iShowTimeDlgFlag = 6;
	int id = m_cVideoTime.DoModal();
	if(id == IDOK)
	{
		int i = m_cVideoTime.m_iSelIndex;
		gHerdAnalyse.week.days[i].seg[0].enable = m_cVideoTime.m_iVideoTime1;
		gHerdAnalyse.week.days[i].seg[1].enable = m_cVideoTime.m_iVideoTime2;
		gHerdAnalyse.week.days[i].seg[2].enable = m_cVideoTime.m_iVideoTime3;
		gHerdAnalyse.week.days[i].seg[3].enable = m_cVideoTime.m_iVideoTime4;
		if(gHerdAnalyse.week.days[i].seg[0].enable == 1)
		{
			gHerdAnalyse.week.days[i].seg[0].time_start.hour = m_cVideoTime.m_STime1.GetHour();
			gHerdAnalyse.week.days[i].seg[0].time_start.minute = m_cVideoTime.m_STime1.GetMinute();
			gHerdAnalyse.week.days[i].seg[0].time_start.second = m_cVideoTime.m_STime1.GetSecond();

			gHerdAnalyse.week.days[i].seg[0].time_end.hour = m_cVideoTime.m_ETime1.GetHour();
			gHerdAnalyse.week.days[i].seg[0].time_end.minute = m_cVideoTime.m_ETime1.GetMinute();
			gHerdAnalyse.week.days[i].seg[0].time_end.second = m_cVideoTime.m_ETime1.GetSecond();
		}

		if(gHerdAnalyse.week.days[i].seg[1].enable == 1)
		{
			gHerdAnalyse.week.days[i].seg[1].time_start.hour = m_cVideoTime.m_STime2.GetHour();
			gHerdAnalyse.week.days[i].seg[1].time_start.minute = m_cVideoTime.m_STime2.GetMinute();
			gHerdAnalyse.week.days[i].seg[1].time_start.second = m_cVideoTime.m_STime2.GetSecond();

			gHerdAnalyse.week.days[i].seg[1].time_end.hour = m_cVideoTime.m_ETime2.GetHour();
			gHerdAnalyse.week.days[i].seg[1].time_end.minute = m_cVideoTime.m_ETime2.GetMinute();
			gHerdAnalyse.week.days[i].seg[1].time_end.second = m_cVideoTime.m_ETime2.GetSecond();
		}

		if(gHerdAnalyse.week.days[i].seg[2].enable == 1)
		{
			gHerdAnalyse.week.days[i].seg[2].time_start.hour = m_cVideoTime.m_STime3.GetHour();
			gHerdAnalyse.week.days[i].seg[2].time_start.minute = m_cVideoTime.m_STime3.GetMinute();
			gHerdAnalyse.week.days[i].seg[2].time_start.second = m_cVideoTime.m_STime3.GetSecond();

			gHerdAnalyse.week.days[i].seg[2].time_end.hour = m_cVideoTime.m_ETime3.GetHour();
			gHerdAnalyse.week.days[i].seg[2].time_end.minute = m_cVideoTime.m_ETime3.GetMinute();
			gHerdAnalyse.week.days[i].seg[2].time_end.second = m_cVideoTime.m_ETime3.GetSecond();
		}

		if(gHerdAnalyse.week.days[i].seg[3].enable == 1)
		{
			gHerdAnalyse.week.days[i].seg[3].time_start.hour = m_cVideoTime.m_STime4.GetHour();
			gHerdAnalyse.week.days[i].seg[3].time_start.minute = m_cVideoTime.m_STime4.GetMinute();
			gHerdAnalyse.week.days[i].seg[3].time_start.second = m_cVideoTime.m_STime4.GetSecond();

			gHerdAnalyse.week.days[i].seg[3].time_end.hour = m_cVideoTime.m_ETime4.GetHour();
			gHerdAnalyse.week.days[i].seg[3].time_end.minute = m_cVideoTime.m_ETime4.GetMinute();
			gHerdAnalyse.week.days[i].seg[3].time_end.second = m_cVideoTime.m_ETime4.GetSecond();
		}
		OnBnClickedButtonSave();
	}
}

void CHerdAnalyse::OnCbnSelchangeComboQuadr()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_quadr.GetCurSel();
	
	CString strID, strName, strIn, strOut;
	strID.Format(_T("%d"),	 gHerdAnalyse.field.trough[nIndex].id);
	strName.Format(_T("%s"), gHerdAnalyse.field.trough[nIndex].name);
	strIn.Format(_T("%d"),   gHerdAnalyse.field.trough[nIndex].inner_percent);
	strOut.Format(_T("%d"),  gHerdAnalyse.field.trough[nIndex].outer_percent);

	m_quadrID.SetWindowText(strID);
	m_quadrName.SetWindowText(strName);
	m_inner_percent.SetWindowText(strIn);
	m_outer_percent.SetWindowText(strOut);

	SetWndData();

}

void CHerdAnalyse::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	for(int i = 0; i < 4; i++)
	{
		m_herdAnalyseScreen.m_innerPoint[i].x = 0;
		m_herdAnalyseScreen.m_innerPoint[i].y = 0;

		m_herdAnalyseScreen.m_outerPoint[i].x = 0;
		m_herdAnalyseScreen.m_outerPoint[i].y = 0;
	}
	m_herdAnalyseScreen.m_nInnerNum = 0;;
	m_herdAnalyseScreen.m_nOuterNum = 0;
	OnBnClickedButtonSave();
}



BOOL CHerdAnalyse::PreTranslateMessage(MSG* pMsg) 
{

	int buID;
	buID= GetWindowLong(pMsg->hwnd,GWL_ID);//由窗口句柄获得ID号，GetWindowLong为获得窗口的ID号。
	if(pMsg->message==WM_LBUTTONDOWN)   //按下 
	{	

	}
	if(pMsg->message==WM_LBUTTONUP)  //松开
	{  
		if( buID == IDC_SLIDER1 ||
			buID == IDC_SLIDER2 ||
			buID == IDC_SLIDER3 ||
			buID == IDC_SLIDER4 ||
			buID == IDC_SLIDER5 ||
			buID == IDC_SLIDER6 ||
			buID == IDC_SLIDER7 ||
			buID == IDC_SLIDER8 
			)
		{
			OnBnClickedButtonSave();
			SliderCtrlSetPos();
		}
	}

	if(pMsg->message == WM_KEYUP && (pMsg->wParam == VK_RIGHT  || pMsg->wParam == VK_LEFT) )
	{

		if( buID == IDC_SLIDER1 ||
			buID == IDC_SLIDER2 ||
			buID == IDC_SLIDER3 ||
			buID == IDC_SLIDER4 ||
			buID == IDC_SLIDER5 ||
			buID == IDC_SLIDER6 ||
			buID == IDC_SLIDER7 ||
			buID == IDC_SLIDER8 
			)
		{
			OnBnClickedButtonSave();
			SliderCtrlSetPos();

		}
		return FALSE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
