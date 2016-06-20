// VideoPlan.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "VideoPlan.h"
#include "Pub_Data.h"


// CVideoPlan 对话框



IMPLEMENT_DYNAMIC(CVideoPlan, CDialog)

CVideoPlan::CVideoPlan(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoPlan::IDD, pParent)
{

	m_DiskNo = -1;
}

CVideoPlan::~CVideoPlan()
{
	DestroyWindow();
}

void CVideoPlan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_Channel);
	DDX_Control(pDX, IDC_LIST_DISK, m_ListDisk);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, m_StramType);
	DDX_Control(pDX, IDC_EDIT_SECOND, m_Yl);
	DDX_Control(pDX, IDC_CHECK_AUTOCOVER, m_AutoCover);
	DDX_Control(pDX, IDC_PROGRESS_FORMAT, m_FormatProgress);
}


BEGIN_MESSAGE_MAP(CVideoPlan, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CVideoPlan::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CVideoPlan::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_TIMESET, &CVideoPlan::OnBnClickedButtonTimeset)
	ON_BN_CLICKED(IDC_BUTTON_FORMATTING, &CVideoPlan::OnBnClickedButtonFormatting)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DISK, &CVideoPlan::OnNMClickListDisk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CVideoPlan 消息处理程序

BOOL CVideoPlan::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_Channel.AddString(_T("0"));
	m_Channel.SetCurSel(0);


	m_ListDisk.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE);

	//添加标题栏，列头信息
	if(g_PubData.g_iLanguageFlag == 0)
	{
		CString			strText;
		strText.Format(_T("磁盘号"));
		m_ListDisk.InsertColumn(0,strText,0,50);
		strText.Format(_T("总容量MB"));
		m_ListDisk.InsertColumn(1,strText,0,80);
		strText.Format(_T("剩余容量MB"));
		m_ListDisk.InsertColumn(2,strText,0,80);
		strText.Format(_T("备份盘"));
		m_ListDisk.InsertColumn(3,strText,0,50);
		strText.Format(_T("状态"));
		m_ListDisk.InsertColumn(4,strText,0,50);
		strText.Format(_T("磁盘类型"));
		m_ListDisk.InsertColumn(5,strText,0,80);
		strText.Format(_T("文件类型"));
		m_ListDisk.InsertColumn(6,strText,0,80);


		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 1)
		{
			m_StramType.AddString(_T("主码流"));
		}
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 2)
		{
			m_StramType.AddString(_T("次码流"));
		}
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 3)
		{
			m_StramType.AddString(_T("三码流"));
		}

	}
	else
	{
		CString			strText;
		strText.Format(_T("Disk ID"));
		m_ListDisk.InsertColumn(0,strText,0,50);
		strText.Format(_T("Total tankage(MB)"));
		m_ListDisk.InsertColumn(1,strText,0,80);
		strText.Format(_T("Residual capacity(MB)"));
		m_ListDisk.InsertColumn(2,strText,0,80);
		strText.Format(_T("Duplicate record"));
		m_ListDisk.InsertColumn(3,strText,0,50);
		strText.Format(_T("State"));
		m_ListDisk.InsertColumn(4,strText,0,50);
		strText.Format(_T("Disk type"));
		m_ListDisk.InsertColumn(5,strText,0,80);
		strText.Format(_T("File type"));
		m_ListDisk.InsertColumn(6,strText,0,80);


		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 1)
		{
			m_StramType.AddString(_T("main stream"));
		}
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 2)
		{
			m_StramType.AddString(_T("secone stream"));
		}
		if(g_PubData.g_jDevCap[g_PubData.g_iAttributeIng].chn_cap.stream_count  >= 3)
		{
			m_StramType.AddString(_T("third stream"));
		}

	}
	
	
	m_StramType.SetCurSel(g_PubData.g_iStreamType[g_PubData.g_iAttributeIng]);

	m_FormatProgress.SetRange(0,100);
	m_FormatProgress.ShowWindow(SW_HIDE);
//	OnBnClickedButtonFlash();

	return TRUE;
}
void CVideoPlan::OnBnClickedButtonFlash()
{
	// TODO: 在此添加控件通知处理程序代码

	int iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_DISK_INFO, (char *)&m_diskInfo, sizeof(m_diskInfo),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}

	iRet = -1;
	iRet = JNetGetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_RECORD_INFO, (char *)&m_recordConfig, sizeof(m_recordConfig),NULL, NULL );
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strGetMessage);
		return;
	}

	ReFreshDisk();
	ReFreshRegin();
}

void CVideoPlan::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代
	m_recordConfig.level = m_StramType.GetCurSel();

	CString strText(_T(""));
	m_Yl.GetWindowText(strText);
	m_recordConfig.pre_record = _ttoi(strText);

	m_recordConfig.auto_cover = m_AutoCover.GetCheck();

	int iRet = -1;
	iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_RECORD_INFO, (char *)&m_recordConfig, sizeof(m_recordConfig), TRUE);
	if( iRet != 0)
	{
		AfxMessageBox( g_PubData.g_strSetMessage);
		return;
	}

}

void CVideoPlan::OnBnClickedButtonTimeset()
{
	// TODO: 在此添加控件通知处理程序代码
	g_PubData.g_iShowTimeDlgFlag = 1;
	int id = m_cVideoTime.DoModal();
	if(id == IDOK)
	{
		int i = m_cVideoTime.m_iSelIndex;
		m_recordConfig.week.days[i].seg[0].enable = m_cVideoTime.m_iVideoTime1;
		m_recordConfig.week.days[i].seg[1].enable = m_cVideoTime.m_iVideoTime2;
		m_recordConfig.week.days[i].seg[2].enable = m_cVideoTime.m_iVideoTime3;
		m_recordConfig.week.days[i].seg[3].enable = m_cVideoTime.m_iVideoTime4;
		if(m_recordConfig.week.days[i].seg[0].enable == 1)
		{
			m_recordConfig.week.days[i].seg[0].time_start.hour = m_cVideoTime.m_STime1.GetHour();
			m_recordConfig.week.days[i].seg[0].time_start.minute = m_cVideoTime.m_STime1.GetMinute();
			m_recordConfig.week.days[i].seg[0].time_start.second = m_cVideoTime.m_STime1.GetSecond();

			m_recordConfig.week.days[i].seg[0].time_end.hour = m_cVideoTime.m_ETime1.GetHour();
			m_recordConfig.week.days[i].seg[0].time_end.minute = m_cVideoTime.m_ETime1.GetMinute();
			m_recordConfig.week.days[i].seg[0].time_end.second = m_cVideoTime.m_ETime1.GetSecond();
		}

		if(m_recordConfig.week.days[i].seg[1].enable == 1)
		{
			m_recordConfig.week.days[i].seg[1].time_start.hour = m_cVideoTime.m_STime2.GetHour();
			m_recordConfig.week.days[i].seg[1].time_start.minute = m_cVideoTime.m_STime2.GetMinute();
			m_recordConfig.week.days[i].seg[1].time_start.second = m_cVideoTime.m_STime2.GetSecond();

			m_recordConfig.week.days[i].seg[1].time_end.hour = m_cVideoTime.m_ETime2.GetHour();
			m_recordConfig.week.days[i].seg[1].time_end.minute = m_cVideoTime.m_ETime2.GetMinute();
			m_recordConfig.week.days[i].seg[1].time_end.second = m_cVideoTime.m_ETime2.GetSecond();
		}

		if(m_recordConfig.week.days[i].seg[2].enable == 1)
		{
			m_recordConfig.week.days[i].seg[2].time_start.hour = m_cVideoTime.m_STime3.GetHour();
			m_recordConfig.week.days[i].seg[2].time_start.minute = m_cVideoTime.m_STime3.GetMinute();
			m_recordConfig.week.days[i].seg[2].time_start.second = m_cVideoTime.m_STime3.GetSecond();

			m_recordConfig.week.days[i].seg[2].time_end.hour = m_cVideoTime.m_ETime3.GetHour();
			m_recordConfig.week.days[i].seg[2].time_end.minute = m_cVideoTime.m_ETime3.GetMinute();
			m_recordConfig.week.days[i].seg[2].time_end.second = m_cVideoTime.m_ETime3.GetSecond();
		}

		if(m_recordConfig.week.days[i].seg[3].enable == 1)
		{
			m_recordConfig.week.days[i].seg[3].time_start.hour = m_cVideoTime.m_STime4.GetHour();
			m_recordConfig.week.days[i].seg[3].time_start.minute = m_cVideoTime.m_STime4.GetMinute();
			m_recordConfig.week.days[i].seg[3].time_start.second = m_cVideoTime.m_STime4.GetSecond();

			m_recordConfig.week.days[i].seg[3].time_end.hour = m_cVideoTime.m_ETime4.GetHour();
			m_recordConfig.week.days[i].seg[3].time_end.minute = m_cVideoTime.m_ETime4.GetMinute();
			m_recordConfig.week.days[i].seg[3].time_end.second = m_cVideoTime.m_ETime4.GetSecond();
		}

		OnBnClickedButtonSave();
	}

}

int CVideoPlan::ReFreshDisk()
{
	m_ListDisk.DeleteAllItems();

	int iCount = m_diskInfo.disk_num;
	CString str;
	for(int i = 0; i < iCount; i++)
	{
		str.Format(_T("%d"),m_diskInfo.disk[i].disk_no);
		m_ListDisk.InsertItem(i,str);
		str.Format(_T("%d"),m_diskInfo.disk[i].total_size);
		m_ListDisk.SetItemText(i,1,str);
		str.Format(_T("%d"),m_diskInfo.disk[i].free_size);
		m_ListDisk.SetItemText(i,2,str);

		if(m_diskInfo.disk[i].is_backup == 0)
		{
			str.Format(_T("%s"),_T("否"));
		}
		else if(m_diskInfo.disk[i].is_backup == 1)
		{
			str.Format(_T("%s"),_T("是"));
		}
		m_ListDisk.SetItemText(i,3,str);

		if(m_diskInfo.disk[i].status == 0)
		{
			str = _T("正在使用");
		}
		else if(m_diskInfo.disk[i].status == 1)
		{
			str = _T("装上");
		}
		else if(m_diskInfo.disk[i].status == 2)
		{
			str = _T("卸载");
		}
		m_ListDisk.SetItemText(i,4,str);

		if(m_diskInfo.disk[i].disk_type == 0)
		{
			str = _T("SATA");
		}
		else if(m_diskInfo.disk[i].disk_type == 1)
		{
			str = _T("USB");
		}
		else if(m_diskInfo.disk[i].disk_type == 2)
		{
			str = _T("ISCSI");
		}
		else if(m_diskInfo.disk[i].disk_type == 3)
		{
			str = _T("NFS");
		}
		else if(m_diskInfo.disk[i].disk_type == 4)
		{
			str = _T("SD");
		}
		m_ListDisk.SetItemText(i,5,str);


		if(m_diskInfo.disk[i].sys_file_type == 0)
		{
			str = _T("FAT 16");
		}
		else if(m_diskInfo.disk[i].sys_file_type == 1)
		{
			str = _T("FAT 32");
		}
		else if(m_diskInfo.disk[i].sys_file_type == 2)
		{
			str = _T("NTFS");
		}
		else if(m_diskInfo.disk[i].sys_file_type == 3)
		{
			str = _T("EXT");
		}
		else if(m_diskInfo.disk[i].sys_file_type == 4)
		{
			str = _T("EXT2");
		}
		else if(m_diskInfo.disk[i].sys_file_type == 5)
		{
			str = _T("EXT3");
		}

		m_ListDisk.SetItemText(i,6,str);
	}
	
	return 0;
}

int CVideoPlan::ReFreshRegin()
{
	
	m_StramType.SetCurSel(m_recordConfig.level);

	CString strText(_T(""));
	strText.Format("%d", m_recordConfig.pre_record);
	m_Yl.SetWindowText(strText);

	m_AutoCover.SetCheck(m_recordConfig.auto_cover);

	return 0;
}

void CVideoPlan::ShowVideoTime(int iIndex)
{
	g_PubData.g_iVideoTime1 = m_recordConfig.week.days[iIndex].seg[0].enable;
	g_PubData.g_iVideoTime2 = m_recordConfig.week.days[iIndex].seg[1].enable;
	g_PubData.g_iVideoTime3 = m_recordConfig.week.days[iIndex].seg[2].enable;
	g_PubData.g_iVideoTime4 = m_recordConfig.week.days[iIndex].seg[3].enable;
	if(m_recordConfig.week.days[iIndex].seg[0].enable == 1)
	{
		int iY = m_recordConfig.week.days[iIndex].seg[0].time_start.hour;
		int iM = m_recordConfig.week.days[iIndex].seg[0].time_start.minute;
		int iD = m_recordConfig.week.days[iIndex].seg[0].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime1 = Stime;

		iY = m_recordConfig.week.days[iIndex].seg[0].time_end.hour;
		iM = m_recordConfig.week.days[iIndex].seg[0].time_end.minute;
		iD = m_recordConfig.week.days[iIndex].seg[0].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime1 = Etime;

	}
	if(m_recordConfig.week.days[iIndex].seg[1].enable == 1)
	{
		int iY = m_recordConfig.week.days[iIndex].seg[1].time_start.hour;
		int iM = m_recordConfig.week.days[iIndex].seg[1].time_start.minute;
		int iD = m_recordConfig.week.days[iIndex].seg[1].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime2 = Stime;

		iY = m_recordConfig.week.days[iIndex].seg[1].time_end.hour;
		iM = m_recordConfig.week.days[iIndex].seg[1].time_end.minute;
		iD = m_recordConfig.week.days[iIndex].seg[1].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime2 = Etime;
	}
	if(m_recordConfig.week.days[iIndex].seg[2].enable == 1)
	{
		int iY = m_recordConfig.week.days[iIndex].seg[2].time_start.hour;
		int iM = m_recordConfig.week.days[iIndex].seg[2].time_start.minute;
		int iD = m_recordConfig.week.days[iIndex].seg[2].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime3 = Stime;

		iY = m_recordConfig.week.days[iIndex].seg[2].time_end.hour;
		iM = m_recordConfig.week.days[iIndex].seg[2].time_end.minute;
		iD = m_recordConfig.week.days[iIndex].seg[2].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime3 = Etime;
	}
	if(m_recordConfig.week.days[iIndex].seg[3].enable == 1)
	{
		int iY = m_recordConfig.week.days[iIndex].seg[3].time_start.hour;
		int iM = m_recordConfig.week.days[iIndex].seg[3].time_start.minute;
		int iD = m_recordConfig.week.days[iIndex].seg[3].time_start.second;

		COleDateTime cTime;
		cTime = COleDateTime::GetCurrentTime();	
		COleDateTime Stime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_STime4 = Stime;

		iY = m_recordConfig.week.days[iIndex].seg[3].time_end.hour;
		iM = m_recordConfig.week.days[iIndex].seg[3].time_end.minute;
		iD = m_recordConfig.week.days[iIndex].seg[3].time_end.second;

		COleDateTime Etime(cTime.GetYear(),cTime.GetMonth(), cTime.GetDay(),iY, iM, iD);
		g_PubData.g_ETime4 = Etime;
	}
}

DWORD CVideoPlan::ThreadFun(LPVOID lpThreadParameter)
{
	CVideoPlan *pDlg = (CVideoPlan *)lpThreadParameter;
	while(g_PubData.g_iFormatProgress != 100)
	{
		Sleep(500);
		if( g_PubData.g_iFormatProgress < 0)
		{
			return 0;
		}
		pDlg->m_FormatProgress.SetPos(g_PubData.g_iFormatProgress);	
	}	
	if (g_PubData.g_iFormatProgress == 100)
	{
		pDlg->m_FormatProgress.SetPos(g_PubData.g_iFormatProgress);
		g_PubData.g_iFormatProgress = -1;
		pDlg->GetDlgItem(IDC_BUTTON_FORMATTING)->EnableWindow(TRUE);
		pDlg->m_FormatProgress.ShowWindow(SW_HIDE);
		if(g_PubData.g_iLanguageFlag == 0)
			AfxMessageBox(_T("格式化成功"));
		else
			AfxMessageBox(_T("Format successful!"));
		return 0;
	}

	return 0;
}

void CVideoPlan::OnBnClickedButtonFormatting()
{
	// TODO: 在此添加控件通知处理程序代码
	/*PARAM_FORMAT_DISK 
	格式磁盘,对应的结构体__FormatDisk 
	*/
	if(m_DiskNo < 0)
	{
		if(g_PubData.g_iLanguageFlag == 0)
			AfxMessageBox(_T("选择需要格式化的磁盘"));
		else
			AfxMessageBox( _T("Choose to format the disk!"));
		return;
	}
	int iRet = -1;
	if(g_PubData.g_iLanguageFlag == 0)
		iRet = ::MessageBox(NULL,_T("确定格式化磁盘?"),_T("是否格式化"),MB_YESNO|MB_ICONQUESTION); 
	else
		iRet =  AfxMessageBox( _T("Determining disk formatting?")); 
	if(iRet == IDNO || iRet < 0)
	{
		return;
	}
	 JFormatDisk formatDisk;
	 formatDisk.disk_no = m_DiskNo;
	 formatDisk.progress = 0;
	 iRet = -1;
	 iRet = JNetSetParam(g_PubData.g_vLoginHandle[g_PubData.g_iAttributeIng],0,PARAM_FORMAT_DISK, (char *)&formatDisk, sizeof(formatDisk), TRUE);
	 if( iRet != 0)
	 {
		 AfxMessageBox(_T("格式化失败"));
		 return ;
	 }
	 m_FormatProgress.ShowWindow(SW_SHOW);
	 GetDlgItem(IDC_BUTTON_FORMATTING)->EnableWindow(FALSE);
	 g_PubData.g_iFormatProgress = 0;
	 HANDLE hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFun,this,0,0);
	 CloseHandle(hThread);
	
}

// int CVideoPlan::ForMattCallBack(struct _jcu_notify_cb_s *handle, jcu_cb_parm_t *parm)
// {
// 	if (parm->args != JCU_NOTIFY_ERR_0)
// 	{
// 		//AfxMessageBox(_T("格式化磁盘失败"));
// 		gVideoPlan->m_FormatProgress.ShowWindow(SW_HIDE);
// 		g_PubData.g_iFormatProgress = -1;
// 		return -1;
// 	}
// 	int iRet = *(int *)parm->data;
// 	if(iRet != JCU_NOTIFY_ERR_0)
// 	{
// 		AfxMessageBox(_T("Set"), g_PubData.g_strSetMessage);
// 		gVideoPlan->m_FormatProgress.ShowWindow(SW_HIDE);
// 		g_PubData.g_iFormatProgress = -1;
// 		return -1;
// 	}
// 	return 0;
// }

void CVideoPlan::OnNMClickListDisk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = pNMItemActivate->iItem;
	CString strNo = _T("");
	strNo = m_ListDisk.GetItemText(iIndex, 0);
	m_DiskNo = _ttoi(strNo);
	*pResult = 0;
}

void CVideoPlan::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}
