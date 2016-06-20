// AlarmInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "AlarmInputDlg.h"
#include "ClientDemo5Dlg.h"
#include "DriveRecordChn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmInputDlg dialog


CAlarmInputDlg::CAlarmInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmInputDlg::IDD, pParent)
	, m_vecAlarmName(NULL)
{
	//{{AFX_DATA_INIT(CAlarmInputDlg)
	m_prd1EndHour = 24;
	m_prd1StartHour = 0;
	m_prd1EndMinute = 0;
	m_prd1StartMinute = 0;
	m_prd1EndSecond = 0;
	m_prd1StartSecond = 0;
	m_prd2EndHour = 24;
	m_prd2StartHour = 0;
	m_prd2StartMinute = 0;
	m_prd2EndSecond = 0;
	m_prd3EndHour = 24;
	m_prd3EndMinute = 0;
	m_prd3StartMinute = 0;
	m_prd3EndSecond = 0;
	m_prd3StartSecond = 0;
	m_prd4EndHour = 24;
	m_prd4StartHour = 0;
	m_prd4EndMinute = 0;
	m_prd4StartMinute = 0;
	m_prd4EndSecond = 0;
	m_prd4StartSecond = 0;
	m_prd2EndMinute = 0;
	m_prd5EndHour = 24;
	m_prd5StartHour = 0;
	m_prd5EndMinute = 0;
	m_prd5StartMinute = 0;
	m_prd5EndSecond = 0;
	m_prd5StartSecond = 0;
	m_prd6EndHour = 24;
	m_prd6StartHour = 0;
	m_prd6EndMinute = 0;
	m_prd6StartMinute = 0;
	m_prd6EndSecond = 0;
	m_prd6StartSecond = 0;
	m_prd2StartSecond = 0;
	m_prd3StartHour = 0;
	m_dwMatrixMask = 0;
	m_dwAmount = 0;
	m_bMatrixEn = FALSE;
	m_bLog = FALSE;
	//}}AFX_DATA_INIT
	m_nCurAlarmChannel = -1;
	m_nCurWeek = -1;
	m_nAlarmOut = 0;
	m_nChannel = 0;
//	m_bNewProtocol = FALSE;
	m_pstAlarminInfo = NULL;
}


void CAlarmInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmInputDlg)
	DDX_Control(pDX, IDC_EDIT_ALARMNAME, m_editAlarmName);
	DDX_Control(pDX, IDC_CHECK_PRD6, m_ctlPRD6);
	DDX_Control(pDX, IDC_CHECK_PRD5, m_ctlPRD5);
	DDX_Control(pDX, IDC_CHECK_PRD4, m_ctlPRD4);
	DDX_Control(pDX, IDC_CHECK_PRD3, m_ctlPRD3);
	DDX_Control(pDX, IDC_CHECK_PRD2, m_ctlPRD2);
	DDX_Control(pDX, IDC_CHECK_PRD1, m_ctlPRD1);
	DDX_Control(pDX, IDC_CHECK_ALARMENABLE, m_ctlAlarmEn);
	DDX_Control(pDX, IDC_CHECK_UPLOAD, m_chkUpload);
	DDX_Control(pDX, IDC_CHECK_SENDMAIL, m_chkSendMail);
	DDX_Control(pDX, IDC_CHECK_RECORD, m_chkRecord);
	DDX_Control(pDX, IDC_CHECK_OUTPUT, m_chkOutPut);
	DDX_Control(pDX, IDC_CHECK_LOCALTOUR, m_chkLocalTour);
	DDX_Control(pDX, IDC_CHECK_LOCALTIP, m_chkLocalIP);
	DDX_Control(pDX, IDC_COMBO_ALARMWEEK, m_ctlAlarmWeek);
	DDX_Control(pDX, IDC_COMBO_ALARMTYPE, m_ctlAlarmType);
	DDX_Control(pDX, IDC_COMBO_ALARMIN, m_ctlAlarmIn);
	DDX_Text(pDX, IDC_EDIT_PRD1_E_HOUR, m_prd1EndHour);
	DDV_MinMaxUInt(pDX, m_prd1EndHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD1_S_HOUR, m_prd1StartHour);
	DDV_MinMaxUInt(pDX, m_prd1StartHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD1_E_MINUTE, m_prd1EndMinute);
	DDV_MinMaxUInt(pDX, m_prd1EndMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD1_S_MINUTE, m_prd1StartMinute);
	DDV_MinMaxUInt(pDX, m_prd1StartMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD1_E_SEC, m_prd1EndSecond);
	DDV_MinMaxUInt(pDX, m_prd1EndSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD1_S_SEC, m_prd1StartSecond);
	DDV_MinMaxUInt(pDX, m_prd1StartSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD2_E_HOUR, m_prd2EndHour);
	DDV_MinMaxUInt(pDX, m_prd2EndHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD2_S_HOUR, m_prd2StartHour);
	DDV_MinMaxUInt(pDX, m_prd2StartHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD2_S_MINUTE, m_prd2StartMinute);
	DDV_MinMaxUInt(pDX, m_prd2StartMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD2_E_SEC, m_prd2EndSecond);
	DDV_MinMaxUInt(pDX, m_prd2EndSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD3_E_HOUR, m_prd3EndHour);
	DDV_MinMaxUInt(pDX, m_prd3EndHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD3_E_MINUTE, m_prd3EndMinute);
	DDV_MinMaxUInt(pDX, m_prd3EndMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD3_S_MINUTE, m_prd3StartMinute);
	DDV_MinMaxUInt(pDX, m_prd3StartMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD3_E_SEC, m_prd3EndSecond);
	DDV_MinMaxUInt(pDX, m_prd3EndSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD3_S_SEC, m_prd3StartSecond);
	DDV_MinMaxUInt(pDX, m_prd3StartSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD4_E_HOUR, m_prd4EndHour);
	DDV_MinMaxUInt(pDX, m_prd4EndHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD4_S_HOUR, m_prd4StartHour);
	DDV_MinMaxUInt(pDX, m_prd4StartHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD4_E_MINUTE, m_prd4EndMinute);
	DDV_MinMaxUInt(pDX, m_prd4EndMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD4_S_MINUTE, m_prd4StartMinute);
	DDV_MinMaxUInt(pDX, m_prd4StartMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD4_E_SEC, m_prd4EndSecond);
	DDV_MinMaxUInt(pDX, m_prd4EndSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD4_S_SEC, m_prd4StartSecond);
	DDV_MinMaxUInt(pDX, m_prd4StartSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD2_E_MINUTE, m_prd2EndMinute);
	DDV_MinMaxUInt(pDX, m_prd2EndMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD5_E_HOUR, m_prd5EndHour);
	DDV_MinMaxUInt(pDX, m_prd5EndHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD5_S_HOUR, m_prd5StartHour);
	DDV_MinMaxUInt(pDX, m_prd5StartHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD5_E_MINUTE, m_prd5EndMinute);
	DDV_MinMaxUInt(pDX, m_prd5EndMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD5_S_MINUTE, m_prd5StartMinute);
	DDV_MinMaxUInt(pDX, m_prd5StartMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD5_E_SEC, m_prd5EndSecond);
	DDV_MinMaxUInt(pDX, m_prd5EndSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD5_S_SEC, m_prd5StartSecond);
	DDV_MinMaxUInt(pDX, m_prd5StartSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD6_E_HOUR, m_prd6EndHour);
	DDV_MinMaxUInt(pDX, m_prd6EndHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD6_S_HOUR, m_prd6StartHour);
	DDV_MinMaxUInt(pDX, m_prd6StartHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_PRD6_E_MINUTE, m_prd6EndMinute);
	DDV_MinMaxUInt(pDX, m_prd6EndMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD6_S_MINUTE, m_prd6StartMinute);
	DDV_MinMaxUInt(pDX, m_prd6StartMinute, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD6_E_SEC, m_prd6EndSecond);
	DDV_MinMaxUInt(pDX, m_prd6EndSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD6_S_SEC, m_prd6StartSecond);
	DDV_MinMaxUInt(pDX, m_prd6StartSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD2_S_SEC, m_prd2StartSecond);
	DDV_MinMaxUInt(pDX, m_prd2StartSecond, 0, 59);
	DDX_Text(pDX, IDC_EDIT_PRD3_S_HOUR, m_prd3StartHour);
	DDV_MinMaxUInt(pDX, m_prd3StartHour, 0, 24);
	DDX_Text(pDX, IDC_EDIT_MATRIX_MASK, m_dwMatrixMask);
	DDV_MinMaxUInt(pDX, m_dwMatrixMask, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_dwAmount);
	DDV_MinMaxUInt(pDX, m_dwAmount, 0, 255);
	DDX_Check(pDX, IDC_CHECK_MATRIX_EN, m_bMatrixEn);
	DDX_Check(pDX, IDC_CHECK_BLOG, m_bLog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmInputDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmInputDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN, OnSelchangeComboAlarmin)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMWEEK, OnSelchangeComboAlarmweek)
	ON_WM_CANCELMODE()
	ON_EN_CHANGE(IDC_EDIT_ALARMNAME, OnChangeEditAlarmname)
	ON_BN_CLICKED(IDC_BTN_DRIVE_RECORD, OnBtnDriveRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAlarmInputDlg::InitDlgInfo(DHDEV_ALARM_SCHEDULE_EX *pAlarmInfo, BYTE nAlarmIn, BYTE nAlarmOut, int nChannel, vector<string>& vecAlarmName)
{
	if(pAlarmInfo != NULL)
	{
		m_pstAlarminInfo = new CFG_ALARMIN_INFO[nAlarmIn/*DH_MAX_ALARM_IN_NUM_EX*/];
		if(NULL == m_pstAlarminInfo)
		{
			return;
		}
		memset(m_pstAlarminInfo, 0, nAlarmIn/*DH_MAX_ALARM_IN_NUM_EX*/*sizeof(CFG_ALARMIN_INFO));


		m_vecAlarmName  = &vecAlarmName;
		int i = 0;
		m_nAlarmOut     = nAlarmOut;
		m_nChannel      = nChannel;
		
		//Set alarm input dropdown menu 
		m_ctlAlarmIn.ResetContent();
		CString strAlarmIn;
		int nIndex = 0;
		for (i = 0; i < nAlarmIn; i++)
		{
			strAlarmIn.Format(ConvertString("Alarm Input %d"), i+1);
			nIndex = m_ctlAlarmIn.AddString(strAlarmIn);
			m_ctlAlarmIn.SetItemData(nIndex,i);
		}
		
		//Alarm output 
		BYTE byRelInitVal[32] = {0};
		m_chnAlarmOut.SetChnState(byRelInitVal,nAlarmOut);
		
		if (m_ctlAlarmIn.GetCount() > 0)
		{
			m_ctlAlarmIn.SetCurSel(0);	
			OnSelchangeComboAlarmin();		
		}
	}
}


void CAlarmInputDlg::RefreshAlarmName()
{
	g_RefreshAlarmName(m_vecAlarmName, m_nCurAlarmChannel, m_editAlarmName);
};

//Clear
void CAlarmInputDlg::CleanAll()
{
	m_ctlAlarmIn.ResetContent();
	m_ctlAlarmEn.SetCheck(0);
	m_ctlAlarmType.SetCurSel(-1);
	m_chkUpload.SetCheck(0);
	m_chkLocalIP.SetCheck(0);
	m_chkLocalTour.SetCheck(0);
	m_chkSendMail.SetCheck(0);
	m_chkRecord.SetCheck(0);
	m_chkOutPut.SetCheck(0);

	BYTE byRelInitVal[32] = {0};
	m_chnAlarmOut.SetChnState(byRelInitVal,32);
	int i=0;
	m_ctlAlarmWeek.SetCurSel(-1);
	for(i=0;i<6;i++)
	{
		CFG_TIME_SECTION periodInfo = {0};
		periodInfo.nEndHour = 24;
		ShowPeriodInfo(&periodInfo,i+1);
	}

	m_nCurAlarmChannel = -1;
	m_nCurWeek = -1;
	m_nAlarmOut = 0;
	m_nChannel = 0;

	m_vecAlarmName = NULL;
	m_editAlarmName.EnableWindow(FALSE);
	m_editAlarmName.SetWindowText("");

	
	if(NULL != m_pstAlarminInfo)
	{
		delete[] m_pstAlarminInfo;
		m_pstAlarminInfo = NULL;
	}
}

//Save
BOOL CAlarmInputDlg::SaveAll()
{
	BOOL bSuccess = FALSE;
	if(-1 != m_ctlAlarmIn.GetCurSel())
	{
		bSuccess = SaveAlarmChannelInfo(m_nCurAlarmChannel);
	}
	return bSuccess;//bSuccess;
}

//Alarm input option switch 
void CAlarmInputDlg::OnSelchangeComboAlarmin() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlAlarmIn.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = (int)m_ctlAlarmIn.GetItemData(nIndex);
		
		//First save alarm input channel information
		SaveAlarmChannelInfo(m_nCurAlarmChannel);


		((CClientDemo5Dlg*)AfxGetMainWnd())->GetAlarmInConfigInfo(&m_pstAlarminInfo[nNum], nIndex);

	
		//Display alarm input channel corresponding information 

		m_ctlAlarmEn.SetCheck(m_pstAlarminInfo[nNum].bEnable?1:0);
		m_ctlAlarmType.SetCurSel(m_pstAlarminInfo[nNum].nAlarmType);
		
		if(m_pstAlarminInfo[nNum].stuEventHandler.abMessageEnable)
		{
			GetDlgItem(IDC_CHECK_UPLOAD)->EnableWindow(TRUE);
			m_chkUpload.SetCheck(m_pstAlarminInfo[nNum].stuEventHandler.bMessageEnable ?TRUE:FALSE);
		}
		else
		{	
			m_chkUpload.SetCheck(FALSE);
			GetDlgItem(IDC_CHECK_UPLOAD)->EnableWindow(FALSE);
		}
		
		if(m_pstAlarminInfo[nNum].stuEventHandler.abTipEnable)
		{	
			GetDlgItem(IDC_CHECK_LOCALTIP)->EnableWindow(TRUE);
			m_chkLocalIP.SetCheck(m_pstAlarminInfo[nNum].stuEventHandler.bTipEnable ?TRUE:FALSE);
		}
		else
		{
			GetDlgItem(IDC_CHECK_LOCALTIP)->EnableWindow(FALSE);
			m_chkLocalIP.SetCheck(FALSE);
		}

		if(m_pstAlarminInfo[nNum].stuEventHandler.abTourEnable)
		{
			GetDlgItem(IDC_CHECK_LOCALTOUR)->EnableWindow(TRUE);
			m_chkLocalTour.SetCheck(m_pstAlarminInfo[nNum].stuEventHandler.bTourEnable ?TRUE:FALSE);
		}
		else
		{
			GetDlgItem(IDC_CHECK_LOCALTOUR)->EnableWindow(FALSE);
			m_chkLocalTour.SetCheck(FALSE);
		}

		if(m_pstAlarminInfo[nNum].stuEventHandler.abMailEnable)
		{
			GetDlgItem(IDC_CHECK_SENDMAIL)->EnableWindow(TRUE);
			m_chkSendMail.SetCheck(m_pstAlarminInfo[nNum].stuEventHandler.bMailEnable?TRUE:FALSE);
		}
		else
		{
			GetDlgItem(IDC_CHECK_SENDMAIL)->EnableWindow(FALSE);
			m_chkSendMail.SetCheck(FALSE);
		}

		if(m_pstAlarminInfo[nNum].stuEventHandler.abRecordEnable 
			&&m_pstAlarminInfo[nNum].stuEventHandler.bRecordEnable)
		{
			m_chkRecord.SetCheck(TRUE);	
		}
		else
		{
			m_chkRecord.SetCheck(FALSE);
		}

		if(m_pstAlarminInfo[nNum].stuEventHandler.abAlarmOutEn
			&&m_pstAlarminInfo[nNum].stuEventHandler.bAlarmOutEn)
		{
			m_chkOutPut.SetCheck(TRUE);	
		}
		else
		{
			m_chkOutPut.SetCheck(FALSE);
		}
		m_chnAlarmOut.SetChnState(m_pstAlarminInfo[nNum].stuEventHandler.dwAlarmOutMask[0],m_nAlarmOut);

		//Time period
		if (m_ctlAlarmWeek.GetCount() > 0)
		{
			m_ctlAlarmWeek.SetCurSel(0);
			OnSelchangeComboAlarmweek(); 
		}	

		m_dwMatrixMask = (unsigned short)m_pstAlarminInfo[nNum].stuEventHandler.dwMatrixMask[0];
		m_dwAmount     = m_pstAlarminInfo[nNum].stuEventHandler.nSnapshotTimes;
		m_bLog		   = m_pstAlarminInfo[nNum].stuEventHandler.bLogEnable;
		m_bMatrixEn    = m_pstAlarminInfo[nNum].stuEventHandler.bMatrixEnable;

		UpdateData(FALSE);
		
		m_nCurAlarmChannel = nNum;

		RefreshAlarmName();
	}
}

//Period switch 
void CAlarmInputDlg::OnSelchangeComboAlarmweek() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlAlarmIn.GetCurSel();
	if(CB_ERR != nIndex)
	{
		int nNum = m_ctlAlarmIn.GetItemData(nIndex);
		nIndex = m_ctlAlarmWeek.GetCurSel();
		if(CB_ERR != nIndex)
		{
			//First save week period information
			SaveWeekInfo(m_nCurAlarmChannel,m_nCurWeek);
			//Display week period information
			for(int i=0;i<6;i++)
			{
		//		DH_TSECT periodInfo = m_AlarmInInfo[nNum].stSect[nIndex][i];
		//		ShowPeriodInfo(&periodInfo,i+1);
				CFG_TIME_SECTION periodInfo = m_pstAlarminInfo[nNum].stuTimeSection[nIndex][i];
				ShowPeriodInfo(&periodInfo,i+1);
			
			}
			
			m_nCurWeek = nIndex;
		}
	}
}
bool CAlarmInputDlg::IsWeekDataValid()
{
	UpdateData(TRUE);
	
	ValidWeekData(1);
	ValidWeekData(2);
	ValidWeekData(3);
	ValidWeekData(4);
	ValidWeekData(5);
	ValidWeekData(6);
	
	return true;
}
//Save alarm channel information 
BOOL CAlarmInputDlg::SaveAlarmChannelInfo(int nNum)
{
	BOOL bValid = TRUE;
	if(-1 < nNum && -1 < m_nCurWeek)
	{
		bool bRet = IsWeekDataValid();
		if (!bRet)
		{
			//MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
			return FALSE;
		}	
//---p3
		CFG_ALARMIN_INFO *pInfo = &m_pstAlarminInfo[nNum];
		if(NULL != pInfo)
		{
			pInfo->bEnable    = m_ctlAlarmEn.GetCheck();
			pInfo->nAlarmType = m_ctlAlarmType.GetCurSel();
        
			pInfo->stuEventHandler.bMessageEnable = m_chkUpload.GetCheck();

			pInfo->stuEventHandler.bTipEnable = m_chkLocalIP.GetCheck();

			pInfo->stuEventHandler.bTourEnable = m_chkLocalTour.GetCheck();

			pInfo->stuEventHandler.bMailEnable = m_chkSendMail.GetCheck();

			pInfo->stuEventHandler.bRecordEnable = m_chkRecord.GetCheck();

			pInfo->stuEventHandler.bAlarmOutEn = m_chkOutPut.GetCheck();

			pInfo->stuEventHandler.dwAlarmOutMask[0] = 0;
			m_chnAlarmOut.GetChnState(pInfo->stuEventHandler.dwAlarmOutMask, m_nAlarmOut);
            // 如果报警输出通道有勾选，需要将使能置为ture，后续结构体转为josn时判断依据
			if (0 != pInfo->stuEventHandler.dwAlarmOutMask[0])
            {
				pInfo->stuEventHandler.abAlarmOutMask = true;
            }

			UpdateData(TRUE);
			pInfo->stuEventHandler.dwMatrixMask[0] = m_dwMatrixMask;
			pInfo->stuEventHandler.nSnapshotTimes  = m_dwAmount;
			pInfo->stuEventHandler.bLogEnable      = m_bLog;
			pInfo->stuEventHandler.bMatrixEnable   = m_bMatrixEn;
			bValid = SaveWeekInfo(nNum,m_nCurWeek);
		}
//---p3
	}
	return bValid;
}

//Save week period information 
BOOL CAlarmInputDlg::SaveWeekInfo(int nNum, int nWeek)
{
	BOOL bValid = TRUE;
	if(-1 < nNum && -1 < nWeek)
	{
		if(UpdateData(TRUE))
		{		
			//p3;
			CFG_TIME_SECTION *pPeriodInfo = &(m_pstAlarminInfo[nNum].stuTimeSection[nWeek][0]);
			
			pPeriodInfo->dwRecordMask = m_ctlPRD1.GetCheck();
 			pPeriodInfo->nBeginHour   = m_prd1StartHour;
			pPeriodInfo->nBeginMin    = m_prd1StartMinute;
 			pPeriodInfo->nBeginSec    = m_prd1StartSecond;
			pPeriodInfo->nEndHour     = m_prd1EndHour;
			pPeriodInfo->nEndMin      = m_prd1EndMinute;
			pPeriodInfo->nEndSec      = m_prd1EndSecond;

			pPeriodInfo = &(m_pstAlarminInfo[nNum].stuTimeSection[nWeek][1]);
			pPeriodInfo->dwRecordMask = m_ctlPRD2.GetCheck();
			pPeriodInfo->nBeginHour   = m_prd2StartHour;
			pPeriodInfo->nBeginMin    = m_prd2StartMinute;
			pPeriodInfo->nBeginSec    = m_prd2StartSecond;
			pPeriodInfo->nEndHour     = m_prd2EndHour;
			pPeriodInfo->nEndMin      = m_prd2EndMinute;
			pPeriodInfo->nEndSec      = m_prd2EndSecond;


			pPeriodInfo = &(m_pstAlarminInfo[nNum].stuTimeSection[nWeek][2]);
			pPeriodInfo->dwRecordMask = m_ctlPRD3.GetCheck();
			pPeriodInfo->nBeginHour   = m_prd3StartHour;
			pPeriodInfo->nBeginMin    = m_prd3StartMinute;
			pPeriodInfo->nBeginSec    = m_prd3StartSecond;
			pPeriodInfo->nEndHour     = m_prd3EndHour;
			pPeriodInfo->nEndMin      = m_prd3EndMinute;
			pPeriodInfo->nEndSec      = m_prd3EndSecond;


			pPeriodInfo = &(m_pstAlarminInfo[nNum].stuTimeSection[nWeek][3]);
			pPeriodInfo->dwRecordMask = m_ctlPRD4.GetCheck();
			pPeriodInfo->nBeginHour   = m_prd4StartHour;
			pPeriodInfo->nBeginMin    = m_prd4StartMinute;
			pPeriodInfo->nBeginSec    = m_prd4StartSecond;
			pPeriodInfo->nEndHour     = m_prd4EndHour;
			pPeriodInfo->nEndMin      = m_prd4EndMinute;
			pPeriodInfo->nEndSec      = m_prd4EndSecond;


			pPeriodInfo = &(m_pstAlarminInfo[nNum].stuTimeSection[nWeek][4]);
			pPeriodInfo->dwRecordMask = m_ctlPRD5.GetCheck();
			pPeriodInfo->nBeginHour   = m_prd5StartHour;
			pPeriodInfo->nBeginMin    = m_prd5StartMinute;
			pPeriodInfo->nBeginSec    = m_prd5StartSecond;
			pPeriodInfo->nEndHour     = m_prd5EndHour;
			pPeriodInfo->nEndMin      = m_prd5EndMinute;
			pPeriodInfo->nEndSec      = m_prd5EndSecond;
			

			pPeriodInfo = &(m_pstAlarminInfo[nNum].stuTimeSection[nWeek][5]);
			pPeriodInfo->dwRecordMask = m_ctlPRD6.GetCheck();
			pPeriodInfo->nBeginHour   = m_prd6StartHour;
			pPeriodInfo->nBeginMin    = m_prd6StartMinute;
			pPeriodInfo->nBeginSec    = m_prd6StartSecond;
			pPeriodInfo->nEndHour     = m_prd6EndHour;
			pPeriodInfo->nEndMin      = m_prd6EndMinute;
			pPeriodInfo->nEndSec      = m_prd6EndSecond;
		}
		else
		{
			bValid = FALSE;
		}
	}
	return bValid;
}

//Display period information
void CAlarmInputDlg::ShowPeriodInfo(CFG_TIME_SECTION *pTSect, BYTE nNum)
{
	switch(nNum) {
	case 1:
		m_ctlPRD1.SetCheck((pTSect->dwRecordMask)?1:0);
		m_prd1StartHour   = pTSect->nBeginHour;
		m_prd1StartMinute = pTSect->nBeginMin;
		m_prd1StartSecond = pTSect->nBeginSec;
		m_prd1EndHour     = pTSect->nEndHour;
		m_prd1EndMinute   = pTSect->nEndMin;
		m_prd1EndSecond   = pTSect->nEndSec;
		break;
	case 2:
		m_ctlPRD2.SetCheck((pTSect->dwRecordMask)?1:0);
		m_prd2StartHour   = pTSect->nBeginHour;
		m_prd2StartMinute = pTSect->nBeginMin;
		m_prd2StartSecond = pTSect->nBeginSec;
		m_prd2EndHour     = pTSect->nEndHour;
		m_prd2EndMinute   = pTSect->nEndMin;
		m_prd2EndSecond   = pTSect->nEndSec;
		break;
	case 3:
		m_ctlPRD3.SetCheck((pTSect->dwRecordMask)?1:0);
		m_prd3StartHour   = pTSect->nBeginHour;
		m_prd3StartMinute = pTSect->nBeginMin;
		m_prd3StartSecond = pTSect->nBeginSec;
		m_prd3EndHour     = pTSect->nEndHour;
		m_prd3EndMinute   = pTSect->nEndMin;
		m_prd3EndSecond   = pTSect->nEndSec;
		break;
	case 4:
		m_ctlPRD4.SetCheck((pTSect->dwRecordMask)?1:0);
		m_prd4StartHour   = pTSect->nBeginHour;
		m_prd4StartMinute = pTSect->nBeginMin;
		m_prd4StartSecond = pTSect->nBeginSec;
		m_prd4EndHour     = pTSect->nEndHour;
		m_prd4EndMinute   = pTSect->nEndMin;
		m_prd4EndSecond   = pTSect->nEndSec;
		break;
	case 5:
		m_ctlPRD5.SetCheck((pTSect->dwRecordMask)?1:0);
		m_prd5StartHour   = pTSect->nBeginHour;
		m_prd5StartMinute = pTSect->nBeginMin;
		m_prd5StartSecond = pTSect->nBeginSec;
		m_prd5EndHour     = pTSect->nEndHour;
		m_prd5EndMinute   = pTSect->nEndMin;
		m_prd5EndSecond   = pTSect->nEndSec;
		break;
	case 6:
		m_ctlPRD6.SetCheck((pTSect->dwRecordMask)?1:0);
		m_prd6StartHour   = pTSect->nBeginHour;
		m_prd6StartMinute = pTSect->nBeginMin;
		m_prd6StartSecond = pTSect->nBeginSec;
		m_prd6EndHour     = pTSect->nEndHour;
		m_prd6EndMinute   = pTSect->nEndMin;
		m_prd6EndSecond   = pTSect->nEndSec;
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}

BOOL CAlarmInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	ConvertComboBox(m_ctlAlarmWeek);
	ConvertComboBox(m_ctlAlarmType);

	m_chnAlarmOut.Create(IDD_DIALOG_CHN, this);
	m_chnAlarmOut.Attach(IDC_STATIC_ALARMOUT, this);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAlarmInputDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}



void CAlarmInputDlg::OnChangeEditAlarmname() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
    int nIndex = m_ctlAlarmIn.GetCurSel();
    int nNum = (int)m_ctlAlarmIn.GetItemData(nIndex);
    m_nCurAlarmChannel = nNum;
    // 修改 m_vecAlarmName
	g_OnChangeEditAlarmname(m_vecAlarmName, m_nCurAlarmChannel, m_editAlarmName);

    // 修改 m_pstAlarminInfo[m_nCurAlarmChannel]
    if (m_nCurAlarmChannel >= 0)
    {
        CString str;
        m_editAlarmName.GetWindowText(str);
        strncpy(m_pstAlarminInfo[m_nCurAlarmChannel].szChnName, str.GetLength() > 32 ? str.Left(32) : str.GetBuffer(0), sizeof(m_pstAlarminInfo[m_nCurAlarmChannel].szChnName) -1);
        m_pstAlarminInfo[m_nCurAlarmChannel].szChnName[MAX_CHANNELNAME_LEN-1] = 0;
    }
}

void CAlarmInputDlg::OnBtnDriveRecord() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlAlarmIn.GetCurSel();
	if (CB_ERR == nIndex)
	{
		MessageBox(ConvertString("Please select channel!"), ConvertString("Prompt"));
		return;
	}
	if (NULL == m_pstAlarminInfo)
	{	
		return;
	}
	int nNum = m_ctlAlarmIn.GetItemData(nIndex);
	DriveRecordChn recordChnDlg;
	// save markinfo to dlgchannel
	BOOL bRet = recordChnDlg.SetRecordMark(m_pstAlarminInfo[nNum].stuEventHandler.dwRecordMask, m_nChannel);
	if (!bRet)
	{
		return;
	}
	if (IDOK == recordChnDlg.DoModal())
	{
		memcpy(m_pstAlarminInfo[nNum].stuEventHandler.dwRecordMask, 
			recordChnDlg.GetRecordMark(), MAX_CHANNEL_COUNT*sizeof(DWORD));
        for (int i = 0; i < MAX_CHANNEL_COUNT; i++)
        {
			if (0 != m_pstAlarminInfo[nNum].stuEventHandler.dwRecordMask[i])
			{
				m_pstAlarminInfo[nNum].stuEventHandler.abRecordMask = true;
				break;
			}
        }
	}
}
