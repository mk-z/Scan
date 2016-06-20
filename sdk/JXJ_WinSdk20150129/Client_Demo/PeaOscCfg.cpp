// PeaOscCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "PeaOscCfg.h"
#include "Pub_Data.h"
#include "PeaJointAction.h"


// CPeaOscCfg 对话框

IMPLEMENT_DYNAMIC(CPeaOscCfg, CDialog)

CPeaOscCfg::CPeaOscCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CPeaOscCfg::IDD, pParent)
{

}

CPeaOscCfg::~CPeaOscCfg()
{
	DestroyWindow();
}

void CPeaOscCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_StartPeaOsc, m_EnablePeaOsc);
	DDX_Control(pDX, IDC_COMBO_SceneType, m_SceneType);
	DDX_Control(pDX, IDC_COMBO_TargetLever, m_TarGetLever);
	DDX_Control(pDX, IDC_StartTime1, m_EnableTime1);
	DDX_Control(pDX, IDC_StartTime2, m_EnableTime2);
	DDX_Control(pDX, IDC_StartTime3, m_EnableTime3);
	DDX_Control(pDX, IDC_StartTime4, m_EnableTime4);
	DDX_Control(pDX, IDC_STIME1, m_StartTime1);
	DDX_Control(pDX, IDC_STIME2, m_StartTime2);
	DDX_Control(pDX, IDC_STIME3, m_StartTime3);
	DDX_Control(pDX, IDC_STIME4, m_StartTime4);
	DDX_Control(pDX, IDC_ETIME1, m_EndTime1);
	DDX_Control(pDX, IDC_ETIME2, m_EndTime2);
	DDX_Control(pDX, IDC_ETIME3, m_EndTime3);
	DDX_Control(pDX, IDC_ETIME4, m_EndTime4);
	DDX_Control(pDX, IDC_COMBO_RULEID, m_RuleId);
	DDX_Control(pDX, IDC_EDIT_RULENAME, m_RuleName);
	DDX_Control(pDX, IDC_COMBO_RULELEVER, m_RuleLever);
	DDX_Control(pDX, IDC_COMBO_RULEID2, m_RuleParam);
	DDX_Control(pDX, IDC_COMBO_Cross, m_cross);
	DDX_Control(pDX, IDC_CHECK_STARTRULE, m_StartRule);
	DDX_Control(pDX, IDC_COMBO_ZJMODE, m_ZjMode);
	DDX_Control(pDX, IDC_CHECK_UPLOADALARM, m_UpLoadAlarm);
}


BEGIN_MESSAGE_MAP(CPeaOscCfg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPeaOscCfg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CPeaOscCfg::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_StartTime1, &CPeaOscCfg::OnBnClickedStarttime1)
	ON_BN_CLICKED(IDC_StartTime2, &CPeaOscCfg::OnBnClickedStarttime2)
	ON_BN_CLICKED(IDC_StartTime3, &CPeaOscCfg::OnBnClickedStarttime3)
	ON_BN_CLICKED(IDC_StartTime4, &CPeaOscCfg::OnBnClickedStarttime4)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_RULEID, &CPeaOscCfg::OnCbnSelchangeComboRuleid)
	ON_CBN_SELCHANGE(IDC_COMBO_RULEID2, &CPeaOscCfg::OnCbnSelchangeComboRuleid2)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CPeaOscCfg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTONJOINTACTION, &CPeaOscCfg::OnBnClickedButtonjointaction)
END_MESSAGE_MAP()


// CPeaOscCfg 消息处理程序
BOOL CPeaOscCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(g_PubData.g_iLanguageFlag == 0)
	{
		m_SceneType.AddString(_T("暂不支持"));
		m_SceneType.AddString(_T("室内场景"));
		m_SceneType.AddString(_T("室外场景"));
		m_SceneType.SetCurSel(0);

		m_TarGetLever.AddString(_T("高"));
		m_TarGetLever.AddString(_T("中"));
		m_TarGetLever.AddString(_T("低"));

		for(int i = 0; i < 8; i++)
		{
			CString strId;
			strId.Format(_T("%d"), i);
			m_RuleId.AddString(strId);
		}
		m_RuleId.SetCurSel(0);

		m_RuleLever.AddString(_T("暂不支持"));
		m_RuleLever.AddString(_T("无警戒"));
		m_RuleLever.AddString(_T("低级警戒"));
		m_RuleLever.AddString(_T("中级警戒"));
		m_RuleLever.AddString(_T("高级警戒"));
		m_RuleLever.SetCurSel(0);

		m_cross.AddString(_T("双向"));
		m_cross.AddString(_T("左到右"));
		m_cross.AddString(_T("右到左"));
		m_cross.EnableWindow(FALSE);

		m_ZjMode.AddString(_T("入侵"));
		m_ZjMode.AddString(_T("进入"));
		m_ZjMode.AddString(_T("离开"));
		m_ZjMode.EnableWindow(FALSE);
		m_ZjMode.SetCurSel(0);

		//J_TRIPWIRE_RULE_TYPE        = 101,       //单绊线-->	JTripWireRuleS
		//J_PERI_METER_RULE_TYPE      = 103,       //警戒区-->	JPerimeterRuleS
		//J_OBJECT_LOOK_RULE_TYPE     = 105,       //物品看护--> JLeftTakeRuleS


		m_SceneType.EnableWindow(FALSE);  //暂不支持
		m_RuleLever.EnableWindow(FALSE);  //暂不支持

		m_RuleParam.AddString(_T("单绊线"));
		m_RuleParam.AddString(_T("警戒区"));
		m_RuleParam.AddString(_T("物品遗留"));
		m_RuleParam.AddString(_T("物品丢失"));
		m_RuleParam.SetCurSel(0);

	}
	else
	{
		m_SceneType.AddString(_T("nonsupport"));
		m_SceneType.AddString(_T("室内场景"));
		m_SceneType.AddString(_T("室外场景"));
		m_SceneType.SetCurSel(0);

		m_TarGetLever.AddString(_T("High"));
		m_TarGetLever.AddString(_T("Middle"));
		m_TarGetLever.AddString(_T("Low"));

		for(int i = 0; i < 8; i++)
		{
			CString strId;
			strId.Format(_T("%d"), i);
			m_RuleId.AddString(strId);
		}
		m_RuleId.SetCurSel(0);

		m_RuleLever.AddString(_T("nonsupport"));
		m_RuleLever.AddString(_T("无警戒"));
		m_RuleLever.AddString(_T("低级警戒"));
		m_RuleLever.AddString(_T("中级警戒"));
		m_RuleLever.AddString(_T("高级警戒"));
		m_RuleLever.SetCurSel(0);

		m_cross.AddString(_T("two-way"));
		m_cross.AddString(_T("Left to right"));
		m_cross.AddString(_T("Right to left"));
		m_cross.EnableWindow(FALSE);

		m_ZjMode.AddString(_T("Intrude"));
		m_ZjMode.AddString(_T("Enter"));
		m_ZjMode.AddString(_T("Leave"));
		m_ZjMode.EnableWindow(FALSE);
		m_ZjMode.SetCurSel(0);

		//J_TRIPWIRE_RULE_TYPE        = 101,       //单绊线-->	JTripWireRuleS
		//J_PERI_METER_RULE_TYPE      = 103,       //警戒区-->	JPerimeterRuleS
		//J_OBJECT_LOOK_RULE_TYPE     = 105,       //物品看护--> JLeftTakeRuleS


		m_SceneType.EnableWindow(FALSE);  //暂不支持
		m_RuleLever.EnableWindow(FALSE);  //暂不支持

		m_RuleParam.AddString(_T("Single trip line "));
		m_RuleParam.AddString(_T("Alert area"));
		m_RuleParam.AddString(_T("Left"));
		m_RuleParam.AddString(_T("Take"));
		m_RuleParam.SetCurSel(0);

	}
	
	m_StartTime1.EnableWindow(FALSE);
	m_StartTime2.EnableWindow(FALSE);
	m_StartTime3.EnableWindow(FALSE);
	m_StartTime4.EnableWindow(FALSE);

	m_EndTime1.EnableWindow(FALSE);
	m_EndTime2.EnableWindow(FALSE);
	m_EndTime3.EnableWindow(FALSE);
	m_EndTime4.EnableWindow(FALSE);

	m_peaoscScreen.Create(IDD_DIALOG_PeaOscScreen, this);
	m_peaoscScreen.MoveWindow(30,60,520,300,TRUE);
	m_peaoscScreen.ShowWindow(SW_SHOW);

	return TRUE;
}
void CPeaOscCfg::OnBnClickedButtonFlash()
{

}

void CPeaOscCfg::OnBnClickedButtonSave()
{
// 	TODO: 在此添加控件通知处理程序代码
// 		gPeaOscCfg.enable = m_EnablePeaOsc.GetCheck();
// 		gPeaOscCfg.scene_type = m_SceneType.GetCurSel();
// 		gPeaOscCfg.target_level = m_TarGetLever.GetCurSel();
// 	
// 		CRect cRect;
// 		m_peaoscScreen.GetWindowRect(cRect);
// 	
// 		SaveTime();   //保存时间段设置
// 	
// 		int i = m_RuleId.GetCurSel();
// 		gPeaOscCfg.rules[i].check_enable = m_StartRule.GetCheck();
// 		gPeaOscCfg.rules[i].stRuleExpHdl.report_alarm = m_UpLoadAlarm.GetCheck();
// 		CString strRuleName = _T("");
// 		m_RuleName.GetWindowText(strRuleName);
// 		memset(gPeaOscCfg.rules[i].rule_name, 0, sizeof(gPeaOscCfg.rules[i].rule_name));
// 		memcpy(gPeaOscCfg.rules[i].rule_name, strRuleName.GetBuffer(0), strRuleName.GetLength());
// 		strRuleName.ReleaseBuffer();
// 		
// 		gPeaOscCfg.rules[i].check_level = m_RuleLever.GetCurSel();
// 	
// 		int iRuleType = m_RuleParam.GetCurSel();
// 		if(iRuleType == 0) //单绊线
// 		{
// 			if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_TRIP_WIRE_CAP)
// 			{
// 				gPeaOscCfg.rules[i].stRulePara.u8RuleType = J_TRIPWIRE_RULE_TYPE;
// 				gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.u32CrossDir = m_cross.GetCurSel();
// 				gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.start_point.x = (int)(m_peaoscScreen.m_lineStartPoint.x * gPeaOscCfg.rule_max_width / cRect.Width());
// 				gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.start_point.y = (int)(m_peaoscScreen.m_lineStartPoint.y * gPeaOscCfg.rule_max_height / cRect.Height());
// 				gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.end_point.x = (int)(m_peaoscScreen.m_lineEndPoint.x * gPeaOscCfg.rule_max_width / cRect.Width());
// 				gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.end_point.y = (int)(m_peaoscScreen.m_lineEndPoint.y * gPeaOscCfg.rule_max_height / cRect.Height());
// 			}
// 			else
// 			{
// 				if(g_PubData.g_iLanguageFlag == 0)
// 					AfxMessageBox(_T("设备不支持单绊线"));
// 				else
// 					AfxMessageBox(_T("Peaosc"), _T("The device does not support single lines!"));
// 				return;
// 			}
// 			
// 		}	
// 		else if(iRuleType == 1)// 警戒区
// 		{
// 			if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_PERI_METER_CAP)
// 			{
// 				gPeaOscCfg.rules[i].stRulePara.u8RuleType = J_PERI_METER_RULE_TYPE;
// 				gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.u32Mode = m_ZjMode.GetCurSel();
// 				if(m_peaoscScreen.m_iCountKeepWatchPoints == 0)
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.stPolygon.point_num = 0;
// 				}
// 				else
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.stPolygon.point_num = m_peaoscScreen.m_iCountKeepWatchPoints;
// 				}
// 				
// 				for(int j = 0; j < m_peaoscScreen.m_iCountKeepWatchPoints; j++)
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.stPolygon.points[j].x = (int)(m_peaoscScreen.m_KeepWatchPoints[j].x * gPeaOscCfg.rule_max_width / cRect.Width());
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.stPolygon.points[j].y = (int)(m_peaoscScreen.m_KeepWatchPoints[j].y * gPeaOscCfg.rule_max_height / cRect.Height());
// 				}
// 	
// 			}
// 			else
// 			{
// 				if(g_PubData.g_iLanguageFlag == 0)
// 					AfxMessageBox(_T("设备不支持警戒区"));
// 				else
// 					AfxMessageBox(_T("Peaosc"), _T("The device does not support the alert zone!"));
// 				
// 				return;
// 			}	
// 	
// 		}
// 		else if(iRuleType == 2) //物品遗留
// 		{
// 			if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_LEFT_CAP)
// 			{
// 				gPeaOscCfg.rules[i].stRulePara.u8RuleType = J_LEFT_RULE_TYPE;
// 				if(m_peaoscScreen.m_iCountLeftPoints == 0)
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stLeft.stPolygon.point_num = 0;
// 				}
// 				else
// 				{		
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stLeft.stPolygon.point_num = m_peaoscScreen.m_iCountLeftPoints;
// 				}	
// 				
// 				for(int j = 0; j < m_peaoscScreen.m_iCountLeftPoints; j++)
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stLeft.stPolygon.points[j].x = (int)(m_peaoscScreen.m_LeftPoints[j].x * gPeaOscCfg.rule_max_width / cRect.Width());
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stLeft.stPolygon.points[j].y = (int)(m_peaoscScreen.m_LeftPoints[j].y * gPeaOscCfg.rule_max_height / cRect.Height());
// 				}
// 			}
// 			else
// 			{
// 				if(g_PubData.g_iLanguageFlag == 0)
// 					AfxMessageBox(_T("设备不支持物品遗留"));
// 				else
// 					AfxMessageBox(_T("Peaosc"), _T("The device does not support left!"));
// 	
// 				//AfxMessageBox(_T("The device does not support left"));
// 				return;
// 			}
// 			
// 		}
// 		else if(iRuleType == 3) //物品丢失
// 		{
// 			if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].ivs_cap & IVS_TAKE_CAP)
// 			{
// 				gPeaOscCfg.rules[i].stRulePara.u8RuleType = J_TAKE_RULE_TYPE;
// 				if(m_peaoscScreen.m_iCountTakePoints == 0)
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTake.stPolygon.point_num = 0;
// 				}
// 				else
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTake.stPolygon.point_num = m_peaoscScreen.m_iCountTakePoints;
// 				}
// 				
// 				for(int j = 0; j < m_peaoscScreen.m_iCountTakePoints; j++)
// 				{
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTake.stPolygon.points[j].x = (int)(m_peaoscScreen.m_TakePoints[j].x * gPeaOscCfg.rule_max_width / cRect.Width());
// 					gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTake.stPolygon.points[j].y = (int)(m_peaoscScreen.m_TakePoints[j].y * gPeaOscCfg.rule_max_height / cRect.Height());
// 				}
// 			}
// 			else
// 			{
// 				if(g_PubData.g_iLanguageFlag == 0)
// 					AfxMessageBox(_T("设备不支持物品丢失"));
// 				else
// 					AfxMessageBox(_T("Peaosc"), _T("The device does not support loss!"));
// 				//AfxMessageBox(_T("The device does not support loss"));
// 				return;
// 			}
// 			
// 		}
// 	
// 		int iRet = -1;
// 		jcu_notify_cb_t notify;
// 		notify.callback = SetPeaOscCallBack;
// 		notify.is_sync = JCU_OP_ASYNC;
// 		notify.user_arg = NULL;
// 	
// 		iRet = jcu_set_req_ttl(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng], 5);
// 		if(iRet != 0)
// 		{
// 			AfxMessageBox(_T("Peaosc"), _T("Save Failed!"));
// 			return;
// 		}
// 	
// 		iRet = jcu_net_cfg_set(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_PEA_OSC_INFO,(char *)&gPeaOscCfg, sizeof(gPeaOscCfg), &notify );
// 		if( iRet != 0)
// 		{
// 			AfxMessageBox(_T("Peaosc"), _T("Save Failed!"));
// 			return ;
// 		}
// 		
}


void CPeaOscCfg::SaveTime()
{
// 	COleDateTime timeStart1;
// 	COleDateTime timeEnd1;
// 	m_StartTime1.GetTime(timeStart1);
// 	m_EndTime1.GetTime(timeEnd1);
// 
// 	COleDateTime timeStart2;
// 	COleDateTime timeEnd2;
// 	m_StartTime2.GetTime(timeStart2);
// 	m_EndTime2.GetTime(timeEnd2);
// 
// 	COleDateTime timeStart3;
// 	COleDateTime timeEnd3;
// 	m_StartTime3.GetTime(timeStart3);
// 	m_EndTime3.GetTime(timeEnd3);
// 
// 	COleDateTime timeStart4;
// 	COleDateTime timeEnd4;
// 	m_StartTime4.GetTime(timeStart4);
// 	m_EndTime4.GetTime(timeEnd4);
// 
// 	gPeaOscCfg.sched_time[0].open = m_EnableTime1.GetCheck();
// 	gPeaOscCfg.sched_time[1].open = m_EnableTime2.GetCheck();
// 	gPeaOscCfg.sched_time[2].open = m_EnableTime3.GetCheck();
// 	gPeaOscCfg.sched_time[3].open = m_EnableTime4.GetCheck();
// 
// 	gPeaOscCfg.sched_time[0].begin_sec = timeStart1.GetHour()*3600 + timeStart1.GetMinute()*60 + timeStart1.GetSecond();
// 	gPeaOscCfg.sched_time[1].begin_sec = timeStart2.GetHour()*3600 + timeStart2.GetMinute()*60 + timeStart2.GetSecond();
// 	gPeaOscCfg.sched_time[2].begin_sec = timeStart3.GetHour()*3600 + timeStart3.GetMinute()*60 + timeStart3.GetSecond();
// 	gPeaOscCfg.sched_time[3].begin_sec = timeStart4.GetHour()*3600 + timeStart4.GetMinute()*60 + timeStart4.GetSecond();
// 
// 	gPeaOscCfg.sched_time[0].end_sec = timeEnd1.GetHour()*3600 + timeEnd1.GetMinute()*60 + timeEnd1.GetSecond();
// 	gPeaOscCfg.sched_time[1].end_sec = timeEnd2.GetHour()*3600 + timeEnd2.GetMinute()*60 + timeEnd2.GetSecond();
// 	gPeaOscCfg.sched_time[2].end_sec = timeEnd3.GetHour()*3600 + timeEnd3.GetMinute()*60 + timeEnd3.GetSecond();
// 	gPeaOscCfg.sched_time[3].end_sec = timeEnd4.GetHour()*3600 + timeEnd4.GetMinute()*60 + timeEnd4.GetSecond();
// 
// }
// void CPeaOscCfg::OnBnClickedButtonFlash()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if(g_PubData.g_iPlayWndFlag != 7 )
// 	{
// 		AVP_AddPlayWnd(g_PubData.g_iChancel[g_PubData.g_iAttributeIng],NULL, m_peaoscScreen.GetSafeHwnd(),NULL,NULL);
// 	}
// 
// 	int iRet = -1;
// 	jcu_notify_cb_t notify;
// 	notify.callback =PeaOscCallBack;
// 	notify.is_sync = JCU_OP_ASYNC;
// 	notify.user_arg = NULL;
// 
// 	iRet = jcu_set_req_ttl(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng], 5);
// 	if(iRet != 0)
// 	{
// 		AfxMessageBox(_T("Peaosc"), _T("Save Failed!"));
// 		return;
// 	}
// 	iRet = jcu_net_cfg_get(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_PEA_OSC_INFO,NULL, sizeof(JPeaOscCfg), &notify );
// 	if( iRet != 0)
// 	{
// 		AfxMessageBox(_T("Peaosc"), _T("Save Failed!"));
// 		return ;
// 	}

}
int CPeaOscCfg::ReFreshWindow()
{
// 	if (parm->args != JCU_NOTIFY_ERR_0)
// 	{
// 		AfxMessageBox(_T("Peaosc"), _T("Failed to get!"));
// 		return -1;
// 	}
// 
// 	if(!::IsWindow(gCpeaOsc->m_hWnd))
// 	{
// 		return -1;
// 	}
// 	ZeroMemory(&gPeaOscCfg,sizeof(JPeaOscCfg));
// 	int copy_size = parm->size;
// 	if(copy_size > sizeof(JPeaOscCfg))
// 	{
// 		copy_size = sizeof(JPeaOscCfg);
// 	}
// 	memcpy(&gPeaOscCfg, parm->data, copy_size);
// 	gCpeaOsc->m_EnablePeaOsc.SetCheck(gPeaOscCfg.enable);
// 	gCpeaOsc->m_SceneType.SetCurSel(gPeaOscCfg.scene_type);
// 	gCpeaOsc->m_TarGetLever.SetCurSel(gPeaOscCfg.target_level);
// 	
// 	gCpeaOsc->m_EnableTime1.SetCheck(gPeaOscCfg.sched_time[0].open);
// 	gCpeaOsc->m_EnableTime2.SetCheck(gPeaOscCfg.sched_time[1].open);
// 	gCpeaOsc->m_EnableTime3.SetCheck(gPeaOscCfg.sched_time[2].open);
// 	gCpeaOsc->m_EnableTime4.SetCheck(gPeaOscCfg.sched_time[3].open);
// 	gCpeaOsc->OnBnClickedStarttime1();
// 	gCpeaOsc->OnBnClickedStarttime2();
// 	gCpeaOsc->OnBnClickedStarttime3();
// 	gCpeaOsc->OnBnClickedStarttime4();
// 
// 	int iTimeS1 =  gPeaOscCfg.sched_time[0].begin_sec;
// 	int iTimeS2 =  gPeaOscCfg.sched_time[1].begin_sec;
// 	int iTimeS3 =  gPeaOscCfg.sched_time[2].begin_sec;
// 	int iTimeS4 =  gPeaOscCfg.sched_time[3].begin_sec;
// 
// 	int iTimeE1 = gPeaOscCfg.sched_time[0].end_sec;
// 	int iTimeE2 = gPeaOscCfg.sched_time[1].end_sec;
// 	int iTimeE3 = gPeaOscCfg.sched_time[2].end_sec;
// 	int iTimeE4 = gPeaOscCfg.sched_time[3].end_sec;
// 
// 	COleDateTime cTime;
// 	cTime = COleDateTime::GetCurrentTime();																	// 小时		//分钟			//秒
// 	COleDateTime startTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS1/3600, (iTimeS1%3600)/60, (iTimeS1%3600)%60);
// 	COleDateTime startTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS2/3600, (iTimeS2%3600)/60, (iTimeS2%3600)%60);
// 	COleDateTime startTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS3/3600, (iTimeS3%3600)/60, (iTimeS3%3600)%60);
// 	COleDateTime startTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeS4/3600, (iTimeS4%3600)/60, (iTimeS4%3600)%60);
// 	gCpeaOsc->m_StartTime1.SetTime(startTime1);
// 	gCpeaOsc->m_StartTime2.SetTime(startTime2);
// 	gCpeaOsc->m_StartTime3.SetTime(startTime3);
// 	gCpeaOsc->m_StartTime4.SetTime(startTime4);
// 
// 	COleDateTime endTime1(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE1/3600, (iTimeE1%3600)/60, (iTimeE1%3600)%60);
// 	COleDateTime endTime2(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE2/3600, (iTimeE2%3600)/60, (iTimeE2%3600)%60);
// 	COleDateTime endTime3(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE3/3600, (iTimeE3%3600)/60, (iTimeE3%3600)%60);
// 	COleDateTime endTime4(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iTimeE4/3600, (iTimeE4%3600)/60, (iTimeE4%3600)%60);
// 	gCpeaOsc->m_EndTime1.SetTime(endTime1);
// 	gCpeaOsc->m_EndTime2.SetTime(endTime2);
// 	gCpeaOsc->m_EndTime3.SetTime(endTime3);
// 	gCpeaOsc->m_EndTime4.SetTime(endTime4);
// 
// 	gCpeaOsc->OnCbnSelchangeComboRuleid();
 	return 0;
}

void CPeaOscCfg::OnBnClickedStarttime1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_EnableTime1.GetCheck() == 1)
	{
		m_StartTime1.EnableWindow(TRUE);
		m_EndTime1.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime1.EnableWindow(FALSE);
		m_EndTime1.EnableWindow(FALSE);
	}
}

void CPeaOscCfg::OnBnClickedStarttime2()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_EnableTime2.GetCheck() == 1)
	{
		m_StartTime2.EnableWindow(TRUE);
		m_EndTime2.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime2.EnableWindow(FALSE);
		m_EndTime2.EnableWindow(FALSE);
	}
}

void CPeaOscCfg::OnBnClickedStarttime3()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_EnableTime3.GetCheck() == 1)
	{
		m_StartTime3.EnableWindow(TRUE);
		m_EndTime3.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime3.EnableWindow(FALSE);
		m_EndTime3.EnableWindow(FALSE);
	}
}

void CPeaOscCfg::OnBnClickedStarttime4()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_EnableTime4.GetCheck() == 1)
	{
		m_StartTime4.EnableWindow(TRUE);
		m_EndTime4.EnableWindow(TRUE);
	}
	else
	{
		m_StartTime4.EnableWindow(FALSE);
		m_EndTime4.EnableWindow(FALSE);
	}
}

void CPeaOscCfg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CPeaOscCfg::OnCbnSelchangeComboRuleid()
{
	// TODO: 在此添加控件通知处理程序代码
// 	int iRuleId = m_RuleId.GetCurSel();
// 
// 	m_StartRule.SetCheck(gPeaOscCfg.rules[iRuleId].check_enable);
// 	CString strRuleName;
// 	strRuleName.Format(_T("%s"), gPeaOscCfg.rules[iRuleId].rule_name);
// 	m_RuleName.SetWindowText(strRuleName);
// 	m_RuleLever.SetCurSel(gPeaOscCfg.rules[iRuleId].check_level);
// 	m_UpLoadAlarm.SetCheck(gPeaOscCfg.rules[iRuleId].stRuleExpHdl.report_alarm);
// 
// 	if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TRIPWIRE_RULE_TYPE)
// 	{
// 		m_RuleParam.SetCurSel(0);
// 	}
// 	else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_PERI_METER_RULE_TYPE)
// 	{
// 		m_RuleParam.SetCurSel(1);
// 	}
// 	else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_LEFT_RULE_TYPE)
// 	{
// 		m_RuleParam.SetCurSel(2);
// 	}
// 	else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TAKE_RULE_TYPE)
// 	{
// 		m_RuleParam.SetCurSel(3);
// 	}
// 	
// 	m_cross.SetCurSel(gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTripWire.u32CrossDir);
// 	CRect cRect;
// 	m_peaoscScreen.GetWindowRect(cRect);
// 	int iW = cRect.Width();
// 	int iH=  cRect.Height();
// 	if(m_RuleParam.GetCurSel() == 0)
// 	{
// 		int sx = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTripWire.stLine.start_point.x;
// 		int sy = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTripWire.stLine.start_point.y;
// 		int ex= gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTripWire.stLine.end_point.x;
// 		int ey= gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTripWire.stLine.end_point.y;
// 		m_peaoscScreen.m_lineStartPoint.x =  (sx * iW)/gPeaOscCfg.rule_max_width;
// 		m_peaoscScreen.m_lineStartPoint.y = (sy * iH)/gPeaOscCfg.rule_max_height;
// 		m_peaoscScreen.m_lineEndPoint.x = (ex * iW)/gPeaOscCfg.rule_max_width;
// 		m_peaoscScreen.m_lineEndPoint.y = (ey * iH)/gPeaOscCfg.rule_max_height;
// 	}
// 	else if(m_RuleParam.GetCurSel() == 1)
// 	{
// 		for(int i = 0; i < J_SDK_MAX_POLYGON_POINT; i++)
// 		{
// 			int px = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stPerimeter.stPolygon.points[i].x;
// 			int py = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stPerimeter.stPolygon.points[i].y;
// 			m_peaoscScreen.m_KeepWatchPoints[i].x = (px * iW)/gPeaOscCfg.rule_max_width;
// 			m_peaoscScreen.m_KeepWatchPoints[i].y = (py * iH)/gPeaOscCfg.rule_max_height;
// 		}
// 		if(gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stPerimeter.stPolygon.point_num  > 0)
// 		{
// 			m_peaoscScreen.m_iCountKeepWatchPoints = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stPerimeter.stPolygon.point_num - 1;
// 		}
// 		else
// 		{
// 			m_peaoscScreen.m_iCountKeepWatchPoints = 0;
// 		}
// 		m_peaoscScreen.m_bDBlbuttonDown = TRUE;
// 	}
// 	else if(m_RuleParam.GetCurSel() == 2)
// 	{
// 		for(int i = 0; i < J_SDK_MAX_POLYGON_POINT; i++)
// 		{
// 			int px = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stLeft.stPolygon.points[i].x;
// 			int py = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stLeft.stPolygon.points[i].y;
// 			m_peaoscScreen.m_LeftPoints[i].x = (px * iW)/gPeaOscCfg.rule_max_width;
// 			m_peaoscScreen.m_LeftPoints[i].y = (py * iH)/gPeaOscCfg.rule_max_height;
// 		}
// 		if(gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stLeft.stPolygon.point_num > 0)
// 		{
// 			m_peaoscScreen.m_iCountLeftPoints = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stLeft.stPolygon.point_num - 1;
// 		}
// 		else
// 		{
// 			m_peaoscScreen.m_iCountLeftPoints = 0;
// 		}
// 		m_peaoscScreen.m_bDBlbuttonDown = TRUE;
// 	}
// 	else if(m_RuleParam.GetCurSel() == 3)
// 	{
// 		for(int i = 0; i < J_SDK_MAX_POLYGON_POINT; i++)
// 		{
// 			int px = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTake.stPolygon.points[i].x;
// 			int py = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTake.stPolygon.points[i].y;
// 			m_peaoscScreen.m_TakePoints[i].x = (px * iW)/gPeaOscCfg.rule_max_width;
// 			m_peaoscScreen.m_TakePoints[i].y = (py * iH)/gPeaOscCfg.rule_max_height;
// 		}
// 		if(gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTake.stPolygon.point_num > 0)
// 		{
// 			m_peaoscScreen.m_iCountTakePoints = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTake.stPolygon.point_num - 1;
// 		}
// 		else
// 		{
// 			m_peaoscScreen.m_iCountTakePoints = 0;
// 		}
// 		m_peaoscScreen.m_bDBlbuttonDown = TRUE;
// 	}
// 	OnCbnSelchangeComboRuleid2();
// 	m_peaoscScreen.m_ruleID = iRuleId;
// 	m_peaoscScreen.RegDrawCallBack();
	
}

void CPeaOscCfg::OnCbnSelchangeComboRuleid2()
{
	// TODO: 在此添加控件通知处理程序代码

// 	int iRuleId = m_RuleId.GetCurSel();
// 	int iRuleParam = m_RuleParam.GetCurSel();
// 	CString strMsg;
// 	if(g_PubData.g_iLanguageFlag == 0)
// 	{
// 		strMsg = _T("请先清空原有规则");
// 	}
// 	else
// 	{
// 		strMsg = _T("Please clear the original rules! ");
// 	}
// 	 
// 
// 	if(m_RuleParam.GetCurSel() == 0)
// 	{
// 		if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType != J_TRIPWIRE_RULE_TYPE && (gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTripWire.stLine.start_point.x > 0
// 			|| gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTripWire.stLine.start_point.y > 0 ) )
// 		{
// 			if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TRIPWIRE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(0);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_PERI_METER_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(1);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_LEFT_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(2);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TAKE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(3);
// 			}
// 			AfxMessageBox(_T("Peaosc"), strMsg);
// 			return ;
// 		}
// 	}
// 	else if(m_RuleParam.GetCurSel() == 1)
// 	{
// 		int pointNum = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stPerimeter.stPolygon.point_num;
// 		if( pointNum > J_SDK_MAX_POLYGON_POINT  || (gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType != J_PERI_METER_RULE_TYPE && pointNum > 0))
// 		{	
// 			if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TRIPWIRE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(0);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_PERI_METER_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(1);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_LEFT_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(2);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TAKE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(3);
// 			}
// 			AfxMessageBox(_T("peaosc"), strMsg);
// 			return ;
// 		}
// 		
// 		m_peaoscScreen.m_bDBlbuttonDown = TRUE;
// 	}
// 	else if(m_RuleParam.GetCurSel() == 2)
// 	{
// 		int pointNum = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stLeft.stPolygon.point_num;
// 		if(pointNum > J_SDK_MAX_POLYGON_POINT || (gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType != J_LEFT_RULE_TYPE && pointNum > 0))
// 		{	
// 			if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TRIPWIRE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(0);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_PERI_METER_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(1);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_LEFT_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(2);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TAKE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(3);
// 			}
// 			AfxMessageBox(_T("peaosc"), strMsg);
// 			return ;
// 		}
// 		m_peaoscScreen.m_bDBlbuttonDown = TRUE;
// 	}
// 	else if(m_RuleParam.GetCurSel() == 3)
// 	{
// 		int pointNum = gPeaOscCfg.rules[iRuleId].stRulePara.uRuleDefine.stTake.stPolygon.point_num;
// 		if(pointNum > J_SDK_MAX_POLYGON_POINT || (gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType != J_TAKE_RULE_TYPE && pointNum > 0))
// 		{	
// 			if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TRIPWIRE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(0);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_PERI_METER_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(1);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_LEFT_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(2);
// 			}
// 			else if(gPeaOscCfg.rules[iRuleId].stRulePara.u8RuleType == J_TAKE_RULE_TYPE)
// 			{
// 				m_RuleParam.SetCurSel(3);
// 			}
// 			AfxMessageBox(_T("peaosc"), strMsg);
// 			return ;
// 			m_peaoscScreen.m_bDBlbuttonDown = TRUE;
// 		}
// 	}
// 
// 	if(iRuleParam == 0)
// 	{
// 		m_cross.EnableWindow(TRUE);
// 	}
// 	else
// 	{
// 		m_cross.EnableWindow(FALSE);
// 	}
// 
// 	if(iRuleParam == 1)
// 	{
// 		m_ZjMode.EnableWindow(TRUE);
// 	}
// 	else
// 	{
// 		m_ZjMode.EnableWindow(FALSE);
// 	}
// 
// 	m_peaoscScreen.m_ruleParam = iRuleParam;
// 	
}

void CPeaOscCfg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
// 	int i = m_RuleId.GetCurSel();
// 	
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.u32CrossDir = m_cross.GetCurSel();
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.start_point.x = 0;
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.start_point.y = 0;
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.end_point.x = 0;
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTripWire.stLine.end_point.y = 0;
// 	m_peaoscScreen.m_lineStartPoint.x = 0;
// 	m_peaoscScreen.m_lineStartPoint.y = 0;
// 	m_peaoscScreen.m_lineEndPoint.x = 0;
// 	m_peaoscScreen.m_lineEndPoint.y = 0;
// 
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.u32Mode = m_ZjMode.GetCurSel();
// 
// 	for(int j = 0; j < J_SDK_MAX_POLYGON_POINT; j++)
// 	{
// 		m_peaoscScreen.m_KeepWatchPoints[j].x = 0;
// 		m_peaoscScreen.m_KeepWatchPoints[j].y = 0;
// 		gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.stPolygon.points[j].x = 0;
// 		gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.stPolygon.points[j].y = 0;
// 	}
// 	m_peaoscScreen.m_iCountKeepWatchPoints = 0;
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stPerimeter.stPolygon.point_num = 0;
// 
// 	for(int j = 0; j < J_SDK_MAX_POLYGON_POINT; j++)
// 	{
// 		m_peaoscScreen.m_LeftPoints[j].x = 0;
// 		m_peaoscScreen.m_LeftPoints[j].y = 0;
// 		gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stLeft.stPolygon.points[j].x = 0;
// 		gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stLeft.stPolygon.points[j].y = 0;
// 	}
// 	m_peaoscScreen.m_iCountLeftPoints = 0;
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stLeft.stPolygon.point_num = 0;
// 
// 	for(int j = 0; j < J_SDK_MAX_POLYGON_POINT; j++)
// 	{
// 		m_peaoscScreen.m_LeftPoints[j].x = 0;
// 		m_peaoscScreen.m_LeftPoints[j].y = 0;
// 		gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTake.stPolygon.points[j].x = 0;
// 		gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTake.stPolygon.points[j].y = 0;
// 	}
// 	m_peaoscScreen.m_iCountTakePoints = 0;
// 	gPeaOscCfg.rules[i].stRulePara.uRuleDefine.stTake.stPolygon.point_num = 0;
// 
// 	int iRet = -1;
// 	jcu_notify_cb_t notify;
// 	notify.callback = SetPeaOscCallBack;
// 	notify.is_sync = JCU_OP_ASYNC;
// 	notify.user_arg = NULL;
// 
// 	iRet = jcu_net_cfg_set(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0, g_PubData.g_iStreamType[g_PubData.g_iAttributeIng] ,PARAM_PEA_OSC_INFO,(char *)&gPeaOscCfg, sizeof(gPeaOscCfg), &notify );
// 	if( iRet != 0)
// 	{
// 		AfxMessageBox(_T("Peaosc"), _T("Save Failed!"));
// 		return ;
// 	}
}

void CPeaOscCfg::OnBnClickedButtonjointaction()
{
	// TODO: 在此添加控件通知处理程序代码
// 	CPeaJointAction jointAction;
// 	int i = m_RuleId.GetCurSel();
// 
// 	g_PubData.m_iJointActionChannel = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_record_enable_channel;
// 	g_PubData.m_iJointRecTime = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_record_second;
// 	g_PubData.m_iJointOut = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_output_enable_channel;
// 	g_PubData.m_iJointOutTime = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_output_times;
// 	g_PubData.m_iJointTakePicChannel = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_snap_enable_channel;
// 	g_PubData.m_iJoinTakePicLever = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_snap_interval;
// 
// 	if(gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.process.joint_post_process[0] & JOINT_SNAP_FTP)
// 	{	
// 		 g_PubData.m_iTakePicFtpUp = 1;
// 	}
// 	else
// 	{
// 		 g_PubData.m_iTakePicFtpUp = 0;
// 	}
// 
// 	g_PubData.m_iTakePicCount = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_snap_times;
// 	g_PubData.m_iJointVoice = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_beep_enable;
// 	g_PubData.m_iJointVoiceTime = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_beep_second;
// 	g_PubData.m_iJointEmail = gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_email_enable;
// 	
// 	int iRet  = jointAction.DoModal();
// 	if(iRet == IDOK)
// 	{
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.alarm_type = J_SDK_PEA_OSC_ALARM;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_record_enable_channel = g_PubData.m_iJointActionChannel;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_record_second = g_PubData.m_iJointRecTime;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_output_enable_channel = g_PubData.m_iJointOut;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_output_times = g_PubData.m_iJointOutTime;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_snap_enable_channel = g_PubData.m_iJointTakePicChannel;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_snap_interval = g_PubData.m_iJoinTakePicLever;
// 
// 		if(g_PubData.m_iTakePicFtpUp == 1)
// 		{	
// 			
// 			gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.process.joint_post_process[0] = JOINT_SNAP_FTP;
// 		}
// 		else
// 		{
// 			gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.process.joint_post_process[0] = 0;
// 		}
// 
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_snap_times = g_PubData.m_iTakePicCount;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_beep_enable = g_PubData.m_iJointVoice;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_beep_second = g_PubData.m_iJointVoiceTime;
// 		gPeaOscCfg.rules[i].stRuleExpHdl.joint_action.joint.joint_email_enable = g_PubData.m_iJointEmail;
// 	}
}
