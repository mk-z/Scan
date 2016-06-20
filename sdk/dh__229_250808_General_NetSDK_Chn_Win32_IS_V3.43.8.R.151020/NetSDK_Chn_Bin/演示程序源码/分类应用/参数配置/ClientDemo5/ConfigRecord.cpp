// ConfigRecord.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigRecord.h"
#include "ClientDemo5Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigRecord dialog


CConfigRecord::CConfigRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigRecord)
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
	//}}AFX_DATA_INIT
	m_nChannelCount = 0;
	m_nCurChannel = -1;
	m_nCurWeek = -1;
	m_nProtoVer = 4;
	m_bNewProtocol = FALSE;
	m_pRecordInfo = NULL;

}

void CConfigRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigRecord)
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_ctlRecordType);
	DDX_Control(pDX, IDC_CHECK_ALM1, m_ctlALM1);
	DDX_Control(pDX, IDC_CHECK_ALM2, m_ctlALM2);
	DDX_Control(pDX, IDC_CHECK_ALM3, m_ctlALM3);
	DDX_Control(pDX, IDC_CHECK_ALM4, m_ctlALM4);
	DDX_Control(pDX, IDC_CHECK_ALM5, m_ctlALM5);
	DDX_Control(pDX, IDC_CHECK_ALM6, m_ctlALM6);
	DDX_Control(pDX, IDC_CHECK_DTT1, m_ctlDTT1);
	DDX_Control(pDX, IDC_CHECK_DTT2, m_ctlDTT2);
	DDX_Control(pDX, IDC_CHECK_DTT3, m_ctlDTT3);
	DDX_Control(pDX, IDC_CHECK_DTT4, m_ctlDTT4);
	DDX_Control(pDX, IDC_CHECK_DTT5, m_ctlDTT5);
	DDX_Control(pDX, IDC_CHECK_DTT6, m_ctlDTT6);
	DDX_Control(pDX, IDC_CHECK_PRD6, m_ctlPRD6);
	DDX_Control(pDX, IDC_CHECK_PRD5, m_ctlPRD5);
	DDX_Control(pDX, IDC_CHECK_PRD4, m_ctlPRD4);
	DDX_Control(pDX, IDC_CHECK_PRD3, m_ctlPRD3);
	DDX_Control(pDX, IDC_CHECK_PRD2, m_ctlPRD2);
	DDX_Control(pDX, IDC_CHECK_PRD1, m_ctlPRD1);
	DDX_Control(pDX, IDC_CHECK_MA6, m_ctlMA6);
	DDX_Control(pDX, IDC_CHECK_MA5, m_ctlMA5);
	DDX_Control(pDX, IDC_CHECK_MA4, m_ctlMA4);
	DDX_Control(pDX, IDC_CHECK_MA3, m_ctlMA3);
	DDX_Control(pDX, IDC_CHECK_MA2, m_ctlMA2);
	DDX_Control(pDX, IDC_CHECK_MA1, m_ctlMA1);
	DDX_Control(pDX, IDC_COMBO_RECORDWEEK, m_ctlRecordWeek);
	DDX_Control(pDX, IDC_CHECK_REDUNDANCY, m_ctlRedundancy);
	DDX_Control(pDX, IDC_COMBO_CHANNO, m_ctlChannel);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigRecord, CDialog)
	//{{AFX_MSG_MAP(CConfigRecord)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_READALL, OnButtonReadall)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNO, OnSelchangeComboChanno)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORDWEEK, OnSelchangeComboRecordweek)
	ON_BN_CLICKED(IDC_CHECK_MA1, OnClickMA1)
	ON_BN_CLICKED(IDC_CHECK_MA2, OnClickMA2)
	ON_BN_CLICKED(IDC_CHECK_MA3, OnClickMA3)
	ON_BN_CLICKED(IDC_CHECK_MA4, OnClickMA4)
	ON_BN_CLICKED(IDC_CHECK_MA5, OnClickMA5)
	ON_BN_CLICKED(IDC_CHECK_MA6, OnClickMA6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigRecord message handlers

bool CConfigRecord::IsWeekDataValid()
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
//Save
void CConfigRecord::OnButtonApply() 
{
	// TODO: Add your control notification handler code here
	if(-1 != m_ctlChannel.GetCurSel())
	{
		bool bRet = IsWeekDataValid();
		if (!bRet)
		{
			MessageBox(ConvertString("Save config info failed!"), ConvertString("Prompt"));
		}
		else
		{	
			BOOL bValid = SaveChannelInfo(m_nCurChannel);
			if(bValid)
			{
				if (NULL == m_pRecordInfo)
				{
					return;
				}
				if (m_bNewProtocol == FALSE)
				{
					//Call father window to save data 
					((CClientDemo5Dlg*)AfxGetMainWnd())->SetRecordConfigInfo(m_pRecordInfo,m_nChannelCount);
				}
				else
				{
					((CClientDemo5Dlg*)AfxGetMainWnd())->SetOneRecordConfigInfo(m_pRecordInfo + m_nCurChannel, m_nCurChannel);
				}		
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Input error!"), ConvertString("Prompt"));
	}
}

//Read and get 
void CConfigRecord::OnButtonReadall() 
{
	// TODO: Add your control notification handler code here
	
	//First clear 
	CleanAll();
	InitRecordInfo();
	//Call father window to read data 
	((CClientDemo5Dlg*)AfxGetMainWnd())->GetRecordConfigInfo();
	
}

/*
 *	Function£ºDisplay record configuration information
 *	Input parameter£º
 *	pRecordInfo£ºrecord configuration structure array
 *	nChannelCount£ºarray amount, e,g channel amount
 */
void CConfigRecord::InitDlgInfo(DHDEV_RECORD_CFG *pRecordInfo, int nChannelCount, int nProtoVer, BOOL bNewProtocol)
{
	m_nProtoVer = nProtoVer;
	m_nChannelCount = nChannelCount;
	m_bNewProtocol = bNewProtocol;
	m_ctlChannel.ResetContent();

	//Save channel video information 
	if (m_pRecordInfo)
	{
		memset(m_pRecordInfo, 0, CHANNEL_NUM_LIMIT * sizeof(DHDEV_RECORD_CFG));
		memcpy(m_pRecordInfo, pRecordInfo, m_nChannelCount * sizeof(DHDEV_RECORD_CFG));
	}

	CString str;
	int nIndex = 0;
	int i = 0;
	//Channel dropdown menu setup 
	for(i=0;i<m_nChannelCount;i++)
	{
		str.Format("%d",i+1);
		nIndex = m_ctlChannel.AddString(str);
		m_ctlChannel.SetItemData(nIndex,i);
		//Save channel video information 
		//m_RecordInfo[i] = pRecordInfo[i];
	}
	//Select channel 0
	if(0 < m_ctlChannel.GetCount())
	{
		m_ctlChannel.SetCurSel(0);
		OnSelchangeComboChanno();
	}
}

//Channel switch 
void CConfigRecord::OnSelchangeComboChanno() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if(CB_ERR != nIndex && NULL != m_pRecordInfo)
	{
		int nNum = (int)m_ctlChannel.GetItemData(nIndex);
		
		//First save channel information 
		SaveChannelInfo(m_nCurChannel);
		
		if (m_bNewProtocol == TRUE)
		{
			((CClientDemo5Dlg*)AfxGetMainWnd())->GetOneRecordConfigInfo(m_pRecordInfo + nNum, nNum);
		}

		//Display channel corresponding information 
		SetDlgItemInt(IDC_EDIT_PRERECLEN, m_pRecordInfo[nNum].byPreRecordLen);
		m_ctlRedundancy.SetCheck((m_pRecordInfo[nNum].byRedundancyEn)?1:0);
		//Week 
		if (m_ctlRecordWeek.GetCount() > 0)
		{
			m_ctlRecordWeek.SetCurSel(0);
		}

		m_ctlRecordType.SetCurSel(m_pRecordInfo[nNum].byRecordType);
		OnSelchangeComboRecordweek();
		
		m_nCurChannel = nNum;
	}
}

//Week switch 
void CConfigRecord::OnSelchangeComboRecordweek() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ctlChannel.GetCurSel();
	if(CB_ERR != nIndex && NULL != m_pRecordInfo)
	{
		int nNum = m_ctlChannel.GetItemData(nIndex);
		nIndex = m_ctlRecordWeek.GetCurSel();
		if(CB_ERR != nIndex)
		{
			//First save week period information 
			SaveWeekInfo(m_nCurChannel,m_nCurWeek);
			//Display week period information 
			for(int i=0;i<6;i++)
			{
				DH_TSECT periodInfo = m_pRecordInfo[nNum].stSect[nIndex][i];
				ShowPeriodInfo(&periodInfo,i+1);
			}

			m_nCurWeek = nIndex;
		}
	}
}

void CConfigRecord::OnClickMA1() 
{
	BOOL bMAEnable = m_ctlMA1.GetCheck();
	if (bMAEnable)
	{
		m_ctlALM1.SetCheck(FALSE);
		m_ctlDTT1.SetCheck(FALSE);
		m_ctlALM1.EnableWindow(FALSE);
		m_ctlDTT1.EnableWindow(FALSE);
	}
	else
	{
		m_ctlALM1.EnableWindow(TRUE);
		m_ctlDTT1.EnableWindow(TRUE);
	}
}

void CConfigRecord::OnClickMA2() 
{
	BOOL bMAEnable = m_ctlMA2.GetCheck();
	if (bMAEnable)
	{
		m_ctlALM2.SetCheck(FALSE);
		m_ctlDTT2.SetCheck(FALSE);
		m_ctlALM2.EnableWindow(FALSE);
		m_ctlDTT2.EnableWindow(FALSE);
	}
	else
	{
		m_ctlALM2.EnableWindow(TRUE);
		m_ctlDTT2.EnableWindow(TRUE);
	}
}

void CConfigRecord::OnClickMA3() 
{
	BOOL bMAEnable = m_ctlMA3.GetCheck();
	if (bMAEnable)
	{
		m_ctlALM3.SetCheck(FALSE);
		m_ctlDTT3.SetCheck(FALSE);
		m_ctlALM3.EnableWindow(FALSE);
		m_ctlDTT3.EnableWindow(FALSE);
	}
	else
	{
		m_ctlALM3.EnableWindow(TRUE);
		m_ctlDTT3.EnableWindow(TRUE);
	}
}

void CConfigRecord::OnClickMA4() 
{
	BOOL bMAEnable = m_ctlMA4.GetCheck();
	if (bMAEnable)
	{
		m_ctlALM4.SetCheck(FALSE);
		m_ctlDTT4.SetCheck(FALSE);
		m_ctlALM4.EnableWindow(FALSE);
		m_ctlDTT4.EnableWindow(FALSE);
	}
	else
	{
		m_ctlALM4.EnableWindow(TRUE);
		m_ctlDTT4.EnableWindow(TRUE);
	}
}

void CConfigRecord::OnClickMA5() 
{
	BOOL bMAEnable = m_ctlMA5.GetCheck();
	if (bMAEnable)
	{
		m_ctlALM5.SetCheck(FALSE);
		m_ctlDTT5.SetCheck(FALSE);
		m_ctlALM5.EnableWindow(FALSE);
		m_ctlDTT5.EnableWindow(FALSE);
	}
	else
	{
		m_ctlALM5.EnableWindow(TRUE);
		m_ctlDTT5.EnableWindow(TRUE);
	}
}

void CConfigRecord::OnClickMA6() 
{
	BOOL bMAEnable = m_ctlMA6.GetCheck();
	if (bMAEnable)
	{
		m_ctlALM6.SetCheck(FALSE);
		m_ctlDTT6.SetCheck(FALSE);
		m_ctlALM6.EnableWindow(FALSE);
		m_ctlDTT6.EnableWindow(FALSE);
	}
	else
	{
		m_ctlALM6.EnableWindow(TRUE);
		m_ctlDTT6.EnableWindow(TRUE);
 	}
}

BOOL CConfigRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	ConvertComboBox(m_ctlRecordWeek);
	int nIndex = m_ctlRecordType.AddString("Main Data stream");
	m_ctlRecordType.SetItemData(nIndex, 0);
	nIndex = m_ctlRecordType.AddString("Substream_1");
	m_ctlRecordType.SetItemData(nIndex, 1);
	nIndex = m_ctlRecordType.AddString("Substream_2");
	m_ctlRecordType.SetItemData(nIndex, 2);
	nIndex = m_ctlRecordType.AddString("Substream_3");
	m_ctlRecordType.SetItemData(nIndex, 3);
	ConvertComboBox(m_ctlRecordType);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//Save channel informaiton 
BOOL CConfigRecord::SaveChannelInfo(int nNum)
{
	BOOL bValid = TRUE;
	if(-1 < nNum && -1 < m_nCurWeek && NULL != m_pRecordInfo)
	{
		DHDEV_RECORD_CFG *pInfo = m_pRecordInfo + nNum;
		if(NULL != pInfo)
		{
			pInfo->byRedundancyEn = m_ctlRedundancy.GetCheck();
			pInfo->byPreRecordLen = GetDlgItemInt(IDC_EDIT_PRERECLEN);
			//add by Nick
			int nIndex = m_ctlRecordType.GetCurSel();
			if(nIndex == CB_ERR)
			{
				MessageBox(ConvertString("Please select a record type"));
				return FALSE;
			}
			pInfo->byRecordType = (BYTE)m_ctlRecordType.GetItemData(nIndex);
			//end add
			//Save week period information 
			bValid = SaveWeekInfo(nNum,m_nCurWeek);
		}
	}
	return bValid;
}

//Save week period information 
BOOL CConfigRecord::SaveWeekInfo(int nNum, int nWeek)
{
	BOOL bValid = TRUE;
	if(-1 < nNum && -1 < nWeek && NULL != m_pRecordInfo)
	{
		if(UpdateData(TRUE))
		{
			DH_TSECT *pPeriodInfo = &(m_pRecordInfo[nNum].stSect[nWeek][0]);
			pPeriodInfo->bEnable = m_ctlDTT1.GetCheck() ? (pPeriodInfo->bEnable | 0x01) : (pPeriodInfo->bEnable & 0xFFFFFFFE);
			if (m_nProtoVer >= 5)
			{
				pPeriodInfo->bEnable = m_ctlALM1.GetCheck() ? (pPeriodInfo->bEnable | 0x02) : (pPeriodInfo->bEnable & 0xFFFFFFFD);
				pPeriodInfo->bEnable = m_ctlPRD1.GetCheck() ? (pPeriodInfo->bEnable | 0x04) : (pPeriodInfo->bEnable & 0xFFFFFFFB);
				pPeriodInfo->bEnable = m_ctlMA1.GetCheck() ? (pPeriodInfo->bEnable | 0x08) : (pPeriodInfo->bEnable & 0xFFFFFFF7);
			}
			pPeriodInfo->iBeginHour = m_prd1StartHour;
			pPeriodInfo->iBeginMin = m_prd1StartMinute;
			pPeriodInfo->iBeginSec = m_prd1StartSecond;
			pPeriodInfo->iEndHour = m_prd1EndHour;
			pPeriodInfo->iEndMin = m_prd1EndMinute;
			pPeriodInfo->iEndSec = m_prd1EndSecond;

			pPeriodInfo = &(m_pRecordInfo[nNum].stSect[nWeek][1]);
			pPeriodInfo->bEnable = m_ctlDTT2.GetCheck() ? (pPeriodInfo->bEnable | 0x01) : (pPeriodInfo->bEnable & 0xFFFFFFFE);
			if (m_nProtoVer >= 5)
			{
				pPeriodInfo->bEnable = m_ctlALM2.GetCheck() ? (pPeriodInfo->bEnable | 0x02) : (pPeriodInfo->bEnable & 0xFFFFFFFD);
				pPeriodInfo->bEnable = m_ctlPRD2.GetCheck() ? (pPeriodInfo->bEnable | 0x04) : (pPeriodInfo->bEnable & 0xFFFFFFFB);
				pPeriodInfo->bEnable = m_ctlMA2.GetCheck() ? (pPeriodInfo->bEnable | 0x08) : (pPeriodInfo->bEnable & 0xFFFFFFF7);
			}
			pPeriodInfo->iBeginHour = m_prd2StartHour;
			pPeriodInfo->iBeginMin = m_prd2StartMinute;
			pPeriodInfo->iBeginSec = m_prd2StartSecond;
			pPeriodInfo->iEndHour = m_prd2EndHour;
			pPeriodInfo->iEndMin = m_prd2EndMinute;
			pPeriodInfo->iEndSec = m_prd2EndSecond;

			pPeriodInfo = &(m_pRecordInfo[nNum].stSect[nWeek][2]);
			pPeriodInfo->bEnable = m_ctlDTT3.GetCheck() ? (pPeriodInfo->bEnable | 0x01) : (pPeriodInfo->bEnable & 0xFFFFFFFE);
			if (m_nProtoVer >= 5)
			{
				pPeriodInfo->bEnable = m_ctlALM3.GetCheck() ? (pPeriodInfo->bEnable | 0x02) : (pPeriodInfo->bEnable & 0xFFFFFFFD);
				pPeriodInfo->bEnable = m_ctlPRD3.GetCheck() ? (pPeriodInfo->bEnable | 0x04) : (pPeriodInfo->bEnable & 0xFFFFFFFB);
				pPeriodInfo->bEnable = m_ctlMA3.GetCheck() ? (pPeriodInfo->bEnable | 0x08) : (pPeriodInfo->bEnable & 0xFFFFFFF7);
			}
			pPeriodInfo->iBeginHour = m_prd3StartHour;
			pPeriodInfo->iBeginMin = m_prd3StartMinute;
			pPeriodInfo->iBeginSec = m_prd3StartSecond;
			pPeriodInfo->iEndHour = m_prd3EndHour;
			pPeriodInfo->iEndMin = m_prd3EndMinute;
			pPeriodInfo->iEndSec = m_prd3EndSecond;

			pPeriodInfo = &(m_pRecordInfo[nNum].stSect[nWeek][3]);
			pPeriodInfo->bEnable = m_ctlDTT4.GetCheck() ? (pPeriodInfo->bEnable | 0x01) : (pPeriodInfo->bEnable & 0xFFFFFFFE);
			if (m_nProtoVer >= 5)
			{
				pPeriodInfo->bEnable = m_ctlALM4.GetCheck() ? (pPeriodInfo->bEnable | 0x02) : (pPeriodInfo->bEnable & 0xFFFFFFFD);
				pPeriodInfo->bEnable = m_ctlPRD4.GetCheck() ? (pPeriodInfo->bEnable | 0x04) : (pPeriodInfo->bEnable & 0xFFFFFFFB);
				pPeriodInfo->bEnable = m_ctlMA4.GetCheck() ? (pPeriodInfo->bEnable | 0x08) : (pPeriodInfo->bEnable & 0xFFFFFFF7);
			}
			pPeriodInfo->iBeginHour = m_prd4StartHour;
			pPeriodInfo->iBeginMin = m_prd4StartMinute;
			pPeriodInfo->iBeginSec = m_prd4StartSecond;
			pPeriodInfo->iEndHour = m_prd4EndHour;
			pPeriodInfo->iEndMin = m_prd4EndMinute;
			pPeriodInfo->iEndSec = m_prd4EndSecond;

			pPeriodInfo = &(m_pRecordInfo[nNum].stSect[nWeek][4]);
			pPeriodInfo->bEnable = m_ctlDTT5.GetCheck() ? (pPeriodInfo->bEnable | 0x01) : (pPeriodInfo->bEnable & 0xFFFFFFFE);
			if (m_nProtoVer >= 5)
			{
				pPeriodInfo->bEnable = m_ctlALM5.GetCheck() ? (pPeriodInfo->bEnable | 0x02) : (pPeriodInfo->bEnable & 0xFFFFFFFD);
				pPeriodInfo->bEnable = m_ctlPRD5.GetCheck() ? (pPeriodInfo->bEnable | 0x04) : (pPeriodInfo->bEnable & 0xFFFFFFFB);
				pPeriodInfo->bEnable = m_ctlMA5.GetCheck() ? (pPeriodInfo->bEnable | 0x08) : (pPeriodInfo->bEnable & 0xFFFFFFF7);
			}
			pPeriodInfo->iBeginHour = m_prd5StartHour;
			pPeriodInfo->iBeginMin = m_prd5StartMinute;
			pPeriodInfo->iBeginSec = m_prd5StartSecond;
			pPeriodInfo->iEndHour = m_prd5EndHour;
			pPeriodInfo->iEndMin = m_prd5EndMinute;
			pPeriodInfo->iEndSec = m_prd5EndSecond;

			pPeriodInfo = &(m_pRecordInfo[nNum].stSect[nWeek][5]);
			pPeriodInfo->bEnable = m_ctlDTT6.GetCheck() ? (pPeriodInfo->bEnable | 0x01) : (pPeriodInfo->bEnable & 0xFFFFFFFE);
			if (m_nProtoVer >= 5)
			{
				pPeriodInfo->bEnable = m_ctlALM6.GetCheck() ? (pPeriodInfo->bEnable | 0x02) : (pPeriodInfo->bEnable & 0xFFFFFFFD);
				pPeriodInfo->bEnable = m_ctlPRD6.GetCheck() ? (pPeriodInfo->bEnable | 0x04) : (pPeriodInfo->bEnable & 0xFFFFFFFB);
				pPeriodInfo->bEnable = m_ctlMA6.GetCheck() ? (pPeriodInfo->bEnable | 0x08) : (pPeriodInfo->bEnable & 0xFFFFFFF7);
			}
			pPeriodInfo->iBeginHour = m_prd6StartHour;
			pPeriodInfo->iBeginMin = m_prd6StartMinute;
			pPeriodInfo->iBeginSec = m_prd6StartSecond;
			pPeriodInfo->iEndHour = m_prd6EndHour;
			pPeriodInfo->iEndMin = m_prd6EndMinute;
			pPeriodInfo->iEndSec = m_prd6EndSecond;
		}
		else
		{
			bValid = FALSE;
		}
	}
	return bValid;
}

//Display period information 
void CConfigRecord::ShowPeriodInfo(DH_TSECT *pTSect, BYTE nNum)
{
	switch(nNum) {
	case 1:
		m_ctlPRD1.SetCheck((pTSect->bEnable & 0x04)?1:0);
		if (m_nProtoVer >= 5)
		{
			if (pTSect->bEnable & 0x08)
			{
				m_ctlMA1.SetCheck(TRUE);
				
				m_ctlALM1.SetCheck(FALSE);
				m_ctlDTT1.SetCheck(FALSE);
				m_ctlALM1.EnableWindow(FALSE);
				m_ctlDTT1.EnableWindow(FALSE);
			}
			else
			{
				m_ctlMA1.SetCheck(FALSE);
				m_ctlALM1.EnableWindow(TRUE);
				m_ctlDTT1.EnableWindow(TRUE);
				m_ctlALM1.SetCheck((pTSect->bEnable & 0x02)?1:0);
				m_ctlDTT1.SetCheck((pTSect->bEnable & 0x01)?1:0);
			}
		
		}
		m_prd1StartHour = pTSect->iBeginHour;
		m_prd1StartMinute = pTSect->iBeginMin;
		m_prd1StartSecond = pTSect->iBeginSec;
		m_prd1EndHour = pTSect->iEndHour;
		m_prd1EndMinute = pTSect->iEndMin;
		m_prd1EndSecond = pTSect->iEndSec;
		break;
	case 2:
		m_ctlPRD2.SetCheck((pTSect->bEnable & 0x04)?1:0);
		if (m_nProtoVer >= 5)
		{
			if (pTSect->bEnable & 0x08)
			{
				m_ctlMA2.SetCheck(TRUE);
				
				m_ctlALM2.SetCheck(FALSE);
				m_ctlDTT2.SetCheck(FALSE);
				m_ctlALM2.EnableWindow(FALSE);
				m_ctlDTT2.EnableWindow(FALSE);
			}
			else
			{
				m_ctlMA2.SetCheck(FALSE);
				m_ctlALM2.EnableWindow(TRUE);
				m_ctlDTT2.EnableWindow(TRUE);
				m_ctlALM2.SetCheck((pTSect->bEnable & 0x02)?1:0);
				m_ctlDTT2.SetCheck((pTSect->bEnable & 0x01)?1:0);	
			}
		}
		m_prd2StartHour = pTSect->iBeginHour;
		m_prd2StartMinute = pTSect->iBeginMin;
		m_prd2StartSecond = pTSect->iBeginSec;
		m_prd2EndHour = pTSect->iEndHour;
		m_prd2EndMinute = pTSect->iEndMin;
		m_prd2EndSecond = pTSect->iEndSec;
		break;
	case 3:
		m_ctlPRD3.SetCheck((pTSect->bEnable & 0x04)?1:0);
		if (m_nProtoVer >= 5)
		{
			if (pTSect->bEnable & 0x08)
			{
				m_ctlMA3.SetCheck(TRUE);
				
				m_ctlALM3.SetCheck(FALSE);
				m_ctlDTT3.SetCheck(FALSE);
				m_ctlALM3.EnableWindow(FALSE);
				m_ctlDTT3.EnableWindow(FALSE);
			}
			else
			{
				m_ctlMA3.SetCheck(FALSE);
				m_ctlALM3.EnableWindow(TRUE);
				m_ctlDTT3.EnableWindow(TRUE);
				m_ctlALM3.SetCheck((pTSect->bEnable & 0x02)?1:0);
				m_ctlDTT3.SetCheck((pTSect->bEnable & 0x01)?1:0);
			}
		}
		m_prd3StartHour = pTSect->iBeginHour;
		m_prd3StartMinute = pTSect->iBeginMin;
		m_prd3StartSecond = pTSect->iBeginSec;
		m_prd3EndHour = pTSect->iEndHour;
		m_prd3EndMinute = pTSect->iEndMin;
		m_prd3EndSecond = pTSect->iEndSec;
		break;
	case 4:
		m_ctlPRD4.SetCheck((pTSect->bEnable & 0x04)?1:0);
		if (m_nProtoVer >= 5)
		{
			if (pTSect->bEnable & 0x08)
			{
				m_ctlMA4.SetCheck(TRUE);
				
				m_ctlALM4.SetCheck(FALSE);
				m_ctlDTT4.SetCheck(FALSE);
				m_ctlALM4.EnableWindow(FALSE);
				m_ctlDTT4.EnableWindow(FALSE);
			}
			else
			{
				m_ctlMA4.SetCheck(FALSE);
				m_ctlALM4.EnableWindow(TRUE);
				m_ctlDTT4.EnableWindow(TRUE);
				m_ctlALM4.SetCheck((pTSect->bEnable & 0x02)?1:0);
				m_ctlDTT4.SetCheck((pTSect->bEnable & 0x01)?1:0);
			}
		}
		m_prd4StartHour = pTSect->iBeginHour;
		m_prd4StartMinute = pTSect->iBeginMin;
		m_prd4StartSecond = pTSect->iBeginSec;
		m_prd4EndHour = pTSect->iEndHour;
		m_prd4EndMinute = pTSect->iEndMin;
		m_prd4EndSecond = pTSect->iEndSec;
		break;
	case 5:
		m_ctlPRD5.SetCheck((pTSect->bEnable & 0x04)?1:0);
		if (m_nProtoVer >= 5)
		{
			if (pTSect->bEnable & 0x08)
			{
				m_ctlMA5.SetCheck(TRUE);
				
				m_ctlALM5.SetCheck(FALSE);
				m_ctlDTT5.SetCheck(FALSE);
				m_ctlALM5.EnableWindow(FALSE);
				m_ctlDTT5.EnableWindow(FALSE);
			}
			else
			{
				m_ctlMA5.SetCheck(FALSE);
				m_ctlALM5.EnableWindow(TRUE);
				m_ctlDTT5.EnableWindow(TRUE);
				m_ctlALM5.SetCheck((pTSect->bEnable & 0x02)?1:0);
				m_ctlDTT5.SetCheck((pTSect->bEnable & 0x01)?1:0);
			}
		}
		m_prd5StartHour = pTSect->iBeginHour;
		m_prd5StartMinute = pTSect->iBeginMin;
		m_prd5StartSecond = pTSect->iBeginSec;
		m_prd5EndHour = pTSect->iEndHour;
		m_prd5EndMinute = pTSect->iEndMin;
		m_prd5EndSecond = pTSect->iEndSec;
		break;
	case 6:
		m_ctlPRD6.SetCheck((pTSect->bEnable & 0x04)?1:0);
		if (m_nProtoVer >= 5)
		{
			if (pTSect->bEnable & 0x08)
			{
				m_ctlMA6.SetCheck(TRUE);
				
				m_ctlALM6.SetCheck(FALSE);
				m_ctlDTT6.SetCheck(FALSE);
				m_ctlALM6.EnableWindow(FALSE);
				m_ctlDTT6.EnableWindow(FALSE);
			}
			else
			{
				m_ctlMA6.SetCheck(FALSE);
				m_ctlALM6.EnableWindow(TRUE);
				m_ctlDTT6.EnableWindow(TRUE);
				m_ctlALM6.SetCheck((pTSect->bEnable & 0x02)?1:0);
				m_ctlDTT6.SetCheck((pTSect->bEnable & 0x01)?1:0);
			}
		}
		m_prd6StartHour = pTSect->iBeginHour;
		m_prd6StartMinute = pTSect->iBeginMin;
		m_prd6StartSecond = pTSect->iBeginSec;
		m_prd6EndHour = pTSect->iEndHour;
		m_prd6EndMinute = pTSect->iEndMin;
		m_prd6EndSecond = pTSect->iEndSec;
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}

//Clear 
void CConfigRecord::CleanAll(bool bCleanRecodinfo)
{
	m_ctlChannel.ResetContent();
	SetDlgItemText(IDC_EDIT_PRERECLEN, "");
	m_ctlRedundancy.SetCheck(0);
	m_ctlRecordWeek.SetCurSel(-1);

	m_ctlPRD1.SetCheck(0);
	m_ctlPRD2.SetCheck(0);
	m_ctlPRD3.SetCheck(0);
	m_ctlPRD4.SetCheck(0);
	m_ctlPRD5.SetCheck(0);
	m_ctlPRD6.SetCheck(0);
	m_ctlDTT1.SetCheck(0);
	m_ctlDTT2.SetCheck(0);
	m_ctlDTT3.SetCheck(0);
	m_ctlDTT4.SetCheck(0);
	m_ctlDTT5.SetCheck(0);
	m_ctlDTT6.SetCheck(0);
	m_ctlALM1.SetCheck(0);
	m_ctlALM2.SetCheck(0);
	m_ctlALM3.SetCheck(0);
	m_ctlALM4.SetCheck(0);
	m_ctlALM5.SetCheck(0);
	m_ctlALM6.SetCheck(0);
	m_ctlMA1.SetCheck(0);
	m_ctlMA2.SetCheck(0);
	m_ctlMA3.SetCheck(0);
	m_ctlMA4.SetCheck(0);
	m_ctlMA5.SetCheck(0);
	m_ctlMA6.SetCheck(0);

	m_ctlALM1.EnableWindow(TRUE);
	m_ctlDTT1.EnableWindow(TRUE);
	m_ctlMA1.EnableWindow(TRUE);
	m_ctlALM2.EnableWindow(TRUE);
	m_ctlDTT2.EnableWindow(TRUE);
	m_ctlMA2.EnableWindow(TRUE);
	m_ctlALM3.EnableWindow(TRUE);
	m_ctlDTT3.EnableWindow(TRUE);
	m_ctlMA3.EnableWindow(TRUE);
	m_ctlALM4.EnableWindow(TRUE);
	m_ctlDTT4.EnableWindow(TRUE);
	m_ctlMA4.EnableWindow(TRUE);
	m_ctlALM5.EnableWindow(TRUE);
	m_ctlDTT5.EnableWindow(TRUE);
	m_ctlMA5.EnableWindow(TRUE);
	m_ctlALM6.EnableWindow(TRUE);
	m_ctlDTT6.EnableWindow(TRUE);
    m_ctlMA6.EnableWindow(TRUE);

	for(int i=0;i<6;i++)
	{
		DH_TSECT periodInfo = {0};
		periodInfo.iEndHour = 24;
		ShowPeriodInfo(&periodInfo,i+1);
	}

	m_nChannelCount = 0;
	m_nCurChannel = -1;
	m_nCurWeek = -1;

	if (bCleanRecodinfo && NULL != m_pRecordInfo)
	{
		delete[] m_pRecordInfo;
		m_pRecordInfo = NULL;
	}
}

// init record info,called after login succeed
BOOL CConfigRecord::InitRecordInfo()
{
	if (NULL == m_pRecordInfo)
	{
		m_pRecordInfo = new DHDEV_RECORD_CFG[CHANNEL_NUM_LIMIT];
		if (NULL == m_pRecordInfo)
		{
			return FALSE;
		}
	}
	return TRUE;

}
