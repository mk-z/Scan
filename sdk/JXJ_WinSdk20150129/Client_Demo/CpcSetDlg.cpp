// CpcSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "CpcSetDlg.h"
#include "Pub_Data.h"

// CCpcSetDlg 对话框

CCpcSetDlg	*gCpcSetDlg = NULL;

IMPLEMENT_DYNAMIC(CCpcSetDlg, CDialog)

CCpcSetDlg::CCpcSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCpcSetDlg::IDD, pParent)
{
	gCpcSetDlg = this;
}

CCpcSetDlg::~CCpcSetDlg()
{
}

void CCpcSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_StartTime1, m_EnableTime1);
	DDX_Control(pDX, IDC_StartTime2, m_EnableTime2);
	DDX_Control(pDX, IDC_StartTime3, m_EnableTime3);
	DDX_Control(pDX, IDC_StartTime4, m_EnableTime4);
	DDX_Control(pDX, IDC_STIME1, m_startTime1);
	DDX_Control(pDX, IDC_STIME2, m_startTime2);
	DDX_Control(pDX, IDC_STIME3, m_startTime3);
	DDX_Control(pDX, IDC_STIME4, m_startTime4);
	DDX_Control(pDX, IDC_ETIME1, m_endTime1);
	DDX_Control(pDX, IDC_ETIME2, m_endTime2);
	DDX_Control(pDX, IDC_ETIME3, m_endTime3);
	DDX_Control(pDX, IDC_ETIME4, m_endTime4);
	DDX_Control(pDX, IDC_COMBO1, m_sensitivity);
	DDX_Control(pDX, IDC_COMBO2, m_maxCount);
	DDX_Control(pDX, IDC_EDIT2, m_minSize);
	DDX_Control(pDX, IDC_EDIT3, m_maxSize);
	DDX_Control(pDX, IDC_CHECK2, m_enabelRule);
	DDX_Control(pDX, IDC_COMBO3, m_ruleID);
	DDX_Control(pDX, IDC_CHECK_ENABLECPC, m_EnableCpc);
	DDX_Control(pDX, IDC_COMBO4, m_combo_res);
}


BEGIN_MESSAGE_MAP(CCpcSetDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CCpcSetDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CCpcSetDlg::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_StartTime1, &CCpcSetDlg::OnBnClickedStarttime1)
	ON_BN_CLICKED(IDC_StartTime2, &CCpcSetDlg::OnBnClickedStarttime2)
	ON_BN_CLICKED(IDC_StartTime3, &CCpcSetDlg::OnBnClickedStarttime3)
	ON_BN_CLICKED(IDC_StartTime4, &CCpcSetDlg::OnBnClickedStarttime4)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCpcSetDlg::OnBnClickedButtonClear)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CCpcSetDlg::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CCpcSetDlg 消息处理程序
BOOL CCpcSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cpcScreen.Create(IDD_DIALOG_CPC_SCREEN, this);
	m_cpcScreen.MoveWindow(30,60,520,300,TRUE);
	m_cpcScreen.ShowWindow(SW_SHOW);


	m_ruleID.SetCurSel(0);

	m_sensitivity.AddString(_T("未知"));
	m_sensitivity.AddString(_T("1"));
	m_sensitivity.AddString(_T("2"));
	m_sensitivity.AddString(_T("3"));
	m_sensitivity.AddString(_T("4"));
	m_sensitivity.AddString(_T("5"));

	m_combo_res.AddString(_T("176x144"));	// QCIF
	m_combo_res.AddString(_T("352x288"));	// CIF

	CString str;
	for (int i = 1; i <= 15; i++)
	{
		str.Format(_T("%d"), i);
		m_maxCount.AddString(str);
	}


	m_startTime1.EnableWindow(FALSE);
	m_endTime1.EnableWindow(FALSE);

	m_startTime2.EnableWindow(FALSE);
	m_endTime2.EnableWindow(FALSE);

	m_startTime3.EnableWindow(FALSE);
	m_endTime3.EnableWindow(FALSE);

	m_startTime4.EnableWindow(FALSE);
	m_endTime4.EnableWindow(FALSE);

	return TRUE;
}

void CCpcSetDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码

// 	g_cpcCfg.enable = m_EnableCpc.GetCheck();
// 	SaveTime();
// 
// 	g_cpcCfg.rule_cfg.enable = m_enabelRule.GetCheck();
// 
// 	g_cpcCfg.rule_cfg.sensitivity = m_sensitivity.GetCurSel();
// 	g_cpcCfg.rule_cfg.count_max = m_maxCount.GetCurSel() + 1;
// 	CString strText = _T("");
// 	m_maxSize.GetWindowText(strText);
// 	g_cpcCfg.rule_cfg.size_max = _ttoi(strText);
// 
// 	m_minSize.GetWindowText(strText);
// 	g_cpcCfg.rule_cfg.size_min = _ttoi(strText);
// 
// 	CRect cRect;
// 	m_cpcScreen.GetWindowRect(cRect);
// 	int index = m_ruleID.GetCurSel();
// 	g_cpcCfg.rule_cfg.rules[index].enable = m_enabelRule.GetCheck();
// 	for(int i = 0; i < J_SDK_MAX_CPC_RULE_POINT; i++ )
// 	{
// 		g_cpcCfg.rule_cfg.rules[index].rule_point[i].x = (int)(m_cpcScreen.m_cpcPoint[i].x * g_cpcCfg.rule_max_width / cRect.Width());
// 		g_cpcCfg.rule_cfg.rules[index].rule_point[i].y = (int)(m_cpcScreen.m_cpcPoint[i].y * g_cpcCfg.rule_max_height / cRect.Height());
// 	}
// 
// 	//drawVo and ivsSize=========================================
// 	g_cpcCfg.res[0] = 1;	//DrawVo
// 	//g_cpcCfg.res[1] = 1;	//IvsSize: 0-QCIF	1-CIF
// 	//===========================================================
// 	g_cpcCfg.res[1] = m_combo_res.GetCurSel();	//IvsSize: 0-QCIF	1-CIF
// 
// 	int iRet = -1;
// 	jcu_notify_cb_t notify;
// 	notify.callback = SetCpcCallBack;
// 	notify.is_sync = JCU_OP_ASYNC;
// 	notify.user_arg = NULL;
// 
// 	iRet = jcu_net_cfg_set(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_CPC_INFO,(char *)&g_cpcCfg, sizeof(g_cpcCfg), &notify );
// 	if( iRet != 0)
// 	{
// 		AfxMessageBox(_T("Set"), g_PubData.g_strSetMessage);
// 		return ;
// 	}
}

void CCpcSetDlg::SaveTime()
{
	COleDateTime timeStart1;
	COleDateTime timeEnd1;
	m_startTime1.GetTime(timeStart1);
	m_endTime1.GetTime(timeEnd1);

	COleDateTime timeStart2;
	COleDateTime timeEnd2;
	m_startTime2.GetTime(timeStart2);
	m_endTime2.GetTime(timeEnd2);

	COleDateTime timeStart3;
	COleDateTime timeEnd3;
	m_startTime3.GetTime(timeStart3);
	m_endTime3.GetTime(timeEnd3);

	COleDateTime timeStart4;
	COleDateTime timeEnd4;
	m_startTime4.GetTime(timeStart4);
	m_endTime4.GetTime(timeEnd4);

// 	g_cpcCfg.segment[0].open = m_EnableTime1.GetCheck();
// 	g_cpcCfg.segment[1].open = m_EnableTime2.GetCheck();
// 	g_cpcCfg.segment[2].open = m_EnableTime3.GetCheck();
// 	g_cpcCfg.segment[3].open = m_EnableTime4.GetCheck();
// 
// 	g_cpcCfg.segment[0].begin_sec = timeStart1.GetHour()*3600 + timeStart1.GetMinute()*60 + timeStart1.GetSecond();
// 	g_cpcCfg.segment[1].begin_sec = timeStart2.GetHour()*3600 + timeStart2.GetMinute()*60 + timeStart2.GetSecond();
// 	g_cpcCfg.segment[2].begin_sec = timeStart3.GetHour()*3600 + timeStart3.GetMinute()*60 + timeStart3.GetSecond();
// 	g_cpcCfg.segment[3].begin_sec = timeStart4.GetHour()*3600 + timeStart4.GetMinute()*60 + timeStart4.GetSecond();
// 
// 	g_cpcCfg.segment[0].end_sec = timeEnd1.GetHour()*3600 + timeEnd1.GetMinute()*60 + timeEnd1.GetSecond();
// 	g_cpcCfg.segment[1].end_sec = timeEnd2.GetHour()*3600 + timeEnd2.GetMinute()*60 + timeEnd2.GetSecond();
// 	g_cpcCfg.segment[2].end_sec = timeEnd3.GetHour()*3600 + timeEnd3.GetMinute()*60 + timeEnd3.GetSecond();
// 	g_cpcCfg.segment[3].end_sec = timeEnd4.GetHour()*3600 + timeEnd4.GetMinute()*60 + timeEnd4.GetSecond();

}

void CCpcSetDlg::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码
// 	if(g_PubData.g_iPlayWndFlag != 8 )
// 	{
// 		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL, m_cpcScreen.GetSafeHwnd(),NULL,NULL);
// 	}
// 
// 	int iRet = -1;
// 	jcu_notify_cb_t notify;
// 	notify.callback =CpcCallBack;
// 	notify.is_sync = JCU_OP_ASYNC;
// 	notify.user_arg = NULL;
// 
// 
// 	iRet = jcu_net_cfg_get(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_CPC_INFO,NULL, sizeof(JCpcCfg), &notify );
// 	if( iRet != 0)
// 	{
// 		AfxMessageBox(_T("Get"), g_PubData.g_strGetMessage);
// 		return ;
// 	}
// 
// 	m_cpcScreen.RegDrawCallBack();
}

// int CCpcSetDlg::CpcCallBack(struct _jcu_notify_cb_s *handle, jcu_cb_parm_t *parm)
// {
// 	if (parm->args != JCU_NOTIFY_ERR_0)
// 	{
// 		AfxMessageBox(_T("Get"), g_PubData.g_strGetMessage);
// 		return -1;
// 	}
// 
// 	if(!::IsWindow(gCpcSetDlg->m_hWnd))
// 	{
// 		return -1;
// 	}
// 	ZeroMemory(&g_cpcCfg,sizeof(JCpcCfg));
// 	int copy_size = parm->size;
// 	if(copy_size > sizeof(JCpcCfg))
// 	{
// 		copy_size = sizeof(JCpcCfg);
// 	}
// 	memcpy(&g_cpcCfg, parm->data, copy_size);
// 	
// 
// 	gCpcSetDlg->m_EnableCpc.SetCheck(g_cpcCfg.enable);
// 
// 	gCpcSetDlg->m_EnableTime1.SetCheck(g_cpcCfg.segment[0].open);
// 	gCpcSetDlg->m_EnableTime2.SetCheck(g_cpcCfg.segment[1].open);
// 	gCpcSetDlg->m_EnableTime3.SetCheck(g_cpcCfg.segment[2].open);
// 	gCpcSetDlg->m_EnableTime4.SetCheck(g_cpcCfg.segment[3].open);
// 	gCpcSetDlg->OnBnClickedStarttime1();
// 	gCpcSetDlg->OnBnClickedStarttime2();
// 	gCpcSetDlg->OnBnClickedStarttime3();
// 	gCpcSetDlg->OnBnClickedStarttime4();
// 
// 	int iTimeS1 =  g_cpcCfg.segment[0].begin_sec;
// 	int iTimeS2 =  g_cpcCfg.segment[1].begin_sec;
// 	int iTimeS3 =  g_cpcCfg.segment[2].begin_sec;
// 	int iTimeS4 =  g_cpcCfg.segment[3].begin_sec;
// 
// 	int iTimeE1 = g_cpcCfg.segment[0].end_sec;
// 	int iTimeE2 = g_cpcCfg.segment[1].end_sec;
// 	int iTimeE3 = g_cpcCfg.segment[2].end_sec;
// 	int iTimeE4 = g_cpcCfg.segment[3].end_sec;
// 
// 
// 	COleDateTime cTime;
// 	cTime = COleDateTime::GetCurrentTime();																	// 小时		//分钟			//秒
// 	COleDateTime startTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS1/3600, (iTimeS1%3600)/60, (iTimeS1%3600)%60);
// 	COleDateTime startTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS2/3600, (iTimeS2%3600)/60, (iTimeS2%3600)%60);
// 	COleDateTime startTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS3/3600, (iTimeS3%3600)/60, (iTimeS3%3600)%60);
// 	COleDateTime startTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS4/3600, (iTimeS4%3600)/60, (iTimeS4%3600)%60);
// 	gCpcSetDlg->m_startTime1.SetTime(startTime1);
// 	gCpcSetDlg->m_startTime2.SetTime(startTime2);
// 	gCpcSetDlg->m_startTime3.SetTime(startTime3);
// 	gCpcSetDlg->m_startTime4.SetTime(startTime4);
// 
// 	COleDateTime endTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE1/3600, (iTimeE1%3600)/60, (iTimeE1%3600)%60);
// 	COleDateTime endTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE2/3600, (iTimeE2%3600)/60, (iTimeE2%3600)%60);
// 	COleDateTime endTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE3/3600, (iTimeE3%3600)/60, (iTimeE3%3600)%60);
// 	COleDateTime endTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE4/3600, (iTimeE4%3600)/60, (iTimeE4%3600)%60);
// 	gCpcSetDlg->m_endTime1.SetTime(endTime1);
// 	gCpcSetDlg->m_endTime2.SetTime(endTime2);
// 	gCpcSetDlg->m_endTime3.SetTime(endTime3);
// 	gCpcSetDlg->m_endTime4.SetTime(endTime4);
// 
// 	gCpcSetDlg->m_ruleID.SetCurSel(g_cpcCfg.rule_cfg.enable);
// 	gCpcSetDlg->m_sensitivity.SetCurSel(g_cpcCfg.rule_cfg.sensitivity);
// 	gCpcSetDlg->m_maxCount.SetCurSel(g_cpcCfg.rule_cfg.count_max - 1);
// 	CString strText;
// 	strText.Format(_T("%d"), g_cpcCfg.rule_cfg.size_max);
// 	gCpcSetDlg->m_maxSize.SetWindowText(strText);
// 
// 	strText.Format(_T("%d"), g_cpcCfg.rule_cfg.size_min);
// 	gCpcSetDlg->m_minSize.SetWindowText(strText);
// 	gCpcSetDlg->OnCbnSelchangeCombo3();
// 
// 	gCpcSetDlg->m_combo_res.SetCurSel(g_cpcCfg.res[1]);
// 	return 0;
// }



void CCpcSetDlg::OnBnClickedStarttime1()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_EnableTime1.GetCheck() == 1)
	{
		m_startTime1.EnableWindow(TRUE);
		m_endTime1.EnableWindow(TRUE);
	}
	else
	{
		m_startTime1.EnableWindow(FALSE);
		m_endTime1.EnableWindow(FALSE);
	}
}

void CCpcSetDlg::OnBnClickedStarttime2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_EnableTime2.GetCheck() == 1)
	{
		m_startTime2.EnableWindow(TRUE);
		m_endTime2.EnableWindow(TRUE);
	}
	else
	{
		m_startTime2.EnableWindow(FALSE);
		m_endTime2.EnableWindow(FALSE);
	}
}

void CCpcSetDlg::OnBnClickedStarttime3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_EnableTime3.GetCheck() == 1)
	{
		m_startTime3.EnableWindow(TRUE);
		m_endTime3.EnableWindow(TRUE);
	}
	else
	{
		m_startTime3.EnableWindow(FALSE);
		m_endTime3.EnableWindow(FALSE);
	}
}

void CCpcSetDlg::OnBnClickedStarttime4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_EnableTime4.GetCheck() == 1)
	{
		m_startTime4.EnableWindow(TRUE);
		m_endTime4.EnableWindow(TRUE);
	}
	else
	{
		m_startTime4.EnableWindow(FALSE);
		m_endTime4.EnableWindow(FALSE);
	}
}

void CCpcSetDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
// 	int index = m_ruleID.GetCurSel();
// 
// 	for(int i = 0; i < J_SDK_MAX_CPC_RULE_POINT; i++ )
// 	{
// 		g_cpcCfg.rule_cfg.rules[index].rule_point[i].x = 0;
// 		g_cpcCfg.rule_cfg.rules[index].rule_point[i].y = 0;
// 		m_cpcScreen.m_cpcPoint[i] = 0;
// 	}
// 
// 	m_cpcScreen.m_iCountPoint = 0;
// 
// 	int iRet = -1;
// 	jcu_notify_cb_t notify;
// 	notify.callback = SetCpcCallBack;
// 	notify.is_sync = JCU_OP_ASYNC;
// 	notify.user_arg = NULL;
// 
// 	iRet = jcu_net_cfg_set(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_CPC_INFO,(char *)&g_cpcCfg, sizeof(g_cpcCfg), &notify );
// 	if( iRet != 0)
// 	{
// 		AfxMessageBox(_T("Set"), g_PubData.g_strSetMessage);
// 		return ;
// 	}
}

void CCpcSetDlg::OnCbnSelchangeCombo3()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_ruleID.GetCurSel();
	CRect cRect;
	m_cpcScreen.GetWindowRect(cRect);
	int iW = cRect.Width();
	int iH=  cRect.Height();

// 	m_enabelRule.SetCheck( g_cpcCfg.rule_cfg.rules[i].enable);
// 	m_cpcScreen.m_iCountPoint =  4;
// 
// 	if(g_cpcCfg.rule_max_width == 0 || g_cpcCfg.rule_max_height == 0)
// 	{
// 		return;
// 	}
// 	for(int j = 0 ;j < J_SDK_MAX_CPC_RULE_POINT; j++)
// 	{
// 		int x = g_cpcCfg.rule_cfg.rules[i].rule_point[j].x;
// 		int y = g_cpcCfg.rule_cfg.rules[i].rule_point[j].y;
// 		m_cpcScreen.m_cpcPoint[j].x  = (x * iW) / g_cpcCfg.rule_max_width;
// 		m_cpcScreen.m_cpcPoint[j].y  = (y * iH) / g_cpcCfg.rule_max_height;
//  	}
// 	

}
