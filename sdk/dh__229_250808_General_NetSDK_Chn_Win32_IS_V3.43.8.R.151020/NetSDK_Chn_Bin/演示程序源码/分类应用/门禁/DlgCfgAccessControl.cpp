// DlgCfgAccessControl.cpp : implementation file
//

#include "stdafx.h"
#include "accesscontrol.h"
#include "DlgCfgAccessControl.h"
#include "SubDlgCfgDoorOpenTimeSection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgAccessControl dialog


CDlgCfgAccessControl::CDlgCfgAccessControl(CWnd* pParent /* = NULL */, LLONG lLoginID /* = 0 */)
	: CDialog(CDlgCfgAccessControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgAccessControl)
	//}}AFX_DATA_INIT
	m_lLoginID = lLoginID;
	memset(&m_stuInfo, 0, sizeof(m_stuInfo));
}


void CDlgCfgAccessControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgAccessControl)
	DDX_Control(pDX, IDC_ACCESSCONTROL_CHK_FIRSTENTER_REMOTECHECK, m_chkRemoteCheck);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CHK_FIRSTENTER_ENABLE, m_chkFirstEnterEnable);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CMB_FIRSTENTER_STATUS, m_cbFirstEnterStatus);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CMB_CHANNEL, m_cmbChannel);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CMB_OPENTIMEINDEX, m_cmbOpenTimeIndex);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CMB_OPENMETHOD, m_cmbOpenMethod);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CHK_SENSOR, m_chkSensor);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CHK_REPEATENTERALARM, m_chkRepeatEnterAlarm);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CHK_DURESSALARM, m_chkDuressAlarm);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CHK_DOORNOTCLOSEALARM, m_chkDoorNotCloseAlarm);
	DDX_Control(pDX, IDC_ACCESSCONTROL_CHK_BREAKINALARM, m_chkBreakAlarm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgAccessControl, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgAccessControl)
	ON_BN_CLICKED(IDC_ACCESSCONTROL_BTN_TIMESECTION, OnAccessControlBtnTimeSection)
	ON_BN_CLICKED(IDC_ACCESSCONTROL_BTN_GET, OnAccessControlBtnGet)
	ON_BN_CLICKED(IDC_ACCESSCONTROL_BTN_SET, OnAccessControlBtnSet)
	ON_CBN_SELCHANGE(IDC_ACCESSCONTROL_CMB_CHANNEL, OnSelchangeAccesscontrolCmbChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgAccessControl private method

void CDlgCfgAccessControl::InitDlg()
{
	int i = 0;

	// channel
	m_cmbChannel.ResetContent();
	for (i = 0; i < 4; i++)
	{
		CString csInfo;
		csInfo.Format("%s%d", ConvertString("Channel", DLG_CFG_ACCESS_CONTROL), i + 1);
		m_cmbChannel.InsertString(-1, csInfo);
	}
	m_cmbChannel.SetCurSel(0);

	// door open method
	m_cmbOpenMethod.ResetContent();
	for (i = 0; i < sizeof(stuDemoOpenMethod)/sizeof(stuDemoOpenMethod[0]); i++)
	{
		m_cmbOpenMethod.InsertString(-1, ConvertString(stuDemoOpenMethod[i].szName));
	}
	m_cmbOpenMethod.SetCurSel(-1);
    m_cmbOpenMethod.SetDroppedWidth(160);
	m_stuInfo.abDoorOpenMethod = true;

	// door unlock hold time
	m_stuInfo.abUnlockHoldInterval = true;

	// door close timeout
	m_stuInfo.abCloseTimeout = true;

	// open time index in config of AccessTimeSchedule, start from 0
	m_cmbOpenTimeIndex.ResetContent();
	for (i = 0; i < 128; i++)
	{
		CString csInfo;
		csInfo.Format("%02d", i);
		m_cmbOpenTimeIndex.InsertString(-1, csInfo);
	}

	// first enter status
	m_cbFirstEnterStatus.ResetContent();
	static const char* szFirstEnterStat[] = 
	{	"Unknown", 
		"KeepOpen", 
		"Normal"
	};
	for (i=0; i<3; i++)
	{
		m_cbFirstEnterStatus.InsertString(-1, ConvertString(szFirstEnterStat[i], DLG_CFG_ACCESS_CONTROL));
	}
	m_cbFirstEnterStatus.SetCurSel((int)m_stuInfo.stuFirstEnterInfo.emStatus);

	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_FIRSTENTER_TIMERINDEX, 0);

	m_cmbOpenTimeIndex.SetCurSel(-1);
	m_stuInfo.abOpenAlwaysTimeIndex = true;

	// holiday record set recNo
	m_stuInfo.abHolidayTimeIndex = true;

	// break in alarm enable
	//m_stuInfo.abBreakInAlarmEnable = true;
	m_chkBreakAlarm.SetCheck(BST_UNCHECKED);

	// repeat enter alarm enable
	//m_stuInfo.abRepeatEnterAlarmEnable = true;
	m_chkRepeatEnterAlarm.SetCheck(BST_UNCHECKED);

	// door not close enable
	//m_stuInfo.abDoorNotClosedAlarmEnable = true;
	m_chkDoorNotCloseAlarm.SetCheck(BST_UNCHECKED);

	// duress alarm enable
	//m_stuInfo.abDuressAlarmEnable = true;
	m_chkDuressAlarm.SetCheck(BST_UNCHECKED);

	// sensor alarm enable
	//m_stuInfo.abSensorEnable = true;
	m_chkSensor.SetCheck(BST_UNCHECKED);

	// first enter
	//m_stuInfo.abFirstEnterEnable = true;
	m_chkFirstEnterEnable.SetCheck(BST_UNCHECKED);

    // remote check
    //m_stuInfo.abRemoteCheck = true;
    m_chkRemoteCheck.SetCheck(BST_UNCHECKED);
}

BOOL CDlgCfgAccessControl::SetConfigToDevice()
{
	int nChn = m_cmbChannel.GetCurSel();
	if (-1 == nChn)
	{
		return FALSE;
	}

	char szJsonBuf[1024 * 40] = {0};
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ACCESS_EVENT, &m_stuInfo, sizeof(m_stuInfo), szJsonBuf, sizeof(szJsonBuf));
	if (!bRet)
	{
		MessageBox(ConvertString(CString("packet AccessControl error..."), DLG_CFG_ACCESS_CONTROL), ConvertString("Prompt"));
		return FALSE;
	} 
	else
	{		
		int nerror = 0;
		int nrestart = 0;
		
		bRet = CLIENT_SetNewDevConfig((LLONG)m_lLoginID, CFG_CMD_ACCESS_EVENT, nChn, szJsonBuf, 1024*40, &nerror, &nrestart, 5000);
		if (!bRet)
		{
			CString csErr;
			csErr.Format("%s 0x%08x...", ConvertString("SetupConfig AccessControl failed:", DLG_CFG_ACCESS_CONTROL), CLIENT_GetLastError());
			MessageBox(csErr, ConvertString("Prompt"));
			return FALSE;
		}
		else
		{
			MessageBox(ConvertString(CString("SetConfig AccessControl ok!"), DLG_CFG_ACCESS_CONTROL), ConvertString("Prompt"));
		}
	}
	return TRUE;
}

BOOL CDlgCfgAccessControl::GetConfigFromDevice()
{
	int nChn = m_cmbChannel.GetCurSel();
	if (-1 == nChn)
	{
		return FALSE;
	}

	char szJsonBuf[1024 * 40] = {0};
	int nerror = 0;
	BOOL bRet = CLIENT_GetNewDevConfig((LLONG)m_lLoginID, CFG_CMD_ACCESS_EVENT, nChn, szJsonBuf, 1024*40, &nerror, 5000);
	
	if (bRet)
	{
		DWORD dwRetLen = 0;
		bRet = CLIENT_ParseData(CFG_CMD_ACCESS_EVENT, szJsonBuf, (void*)&m_stuInfo, sizeof(m_stuInfo), &dwRetLen);
		if (!bRet)
		{
			MessageBox(ConvertString(CString("parse AccessControl error..."), DLG_CFG_ACCESS_CONTROL), ConvertString("Prompt"));
			return FALSE;
		}
	}
	else
	{			
		CString csErr;
		csErr.Format("%s 0x%08x...\r\n\r\n%s", ConvertString("QueryConfig AccessControl error:", DLG_CFG_ACCESS_CONTROL),
			CLIENT_GetLastError(), szJsonBuf);
		MessageBox(csErr, ConvertString("Prompt"));
		return FALSE;
	}
	return TRUE;
}

void CDlgCfgAccessControl::DlgToStu()
{
	// door open method
    int nMethodIndex = m_cmbOpenMethod.GetCurSel();
    if (nMethodIndex >= 0 && nMethodIndex < sizeof(stuDemoOpenMethod)/sizeof(stuDemoOpenMethod[0]))
    {
        m_stuInfo.emDoorOpenMethod = (CFG_DOOR_OPEN_METHOD)stuDemoOpenMethod[nMethodIndex].emOpenMethod;
    }
    else
    {
        m_stuInfo.emDoorOpenMethod = CFG_DOOR_OPEN_METHOD_UNKNOWN;
    }
	
	// door unlock hold time
	m_stuInfo.nUnlockHoldInterval = GetDlgItemInt(IDC_ACCESSCONTROL_EDT_UNLOCKHOLD, NULL, TRUE);
	
	// door close timeout
	m_stuInfo.nCloseTimeout = GetDlgItemInt(IDC_ACCESSCONTROL_EDT_CLOSETIMEOUT, NULL, TRUE);
	
	// open time index in config of AccessTimeSchedule, start from 0
	m_stuInfo.nOpenAlwaysTimeIndex = m_cmbOpenTimeIndex.GetCurSel();
	
	// holiday record set recNo
	m_stuInfo.nHolidayTimeRecoNo = GetDlgItemInt(IDC_ACCESSCONTROL_EDT_HOLIDAYTIMERECNO, NULL, TRUE);

	// first enter status
	m_stuInfo.stuFirstEnterInfo.emStatus = static_cast<CFG_ACCESS_FIRSTENTER_STATUS>(m_cbFirstEnterStatus.GetCurSel());

	// first enter time index
	m_stuInfo.stuFirstEnterInfo.nTimeIndex = GetDlgItemInt(IDC_ACCESSCONTROL_EDT_FIRSTENTER_TIMERINDEX);
	
	// break in alarm enable
	if (m_chkBreakAlarm.GetCheck())
	{
        m_stuInfo.abBreakInAlarmEnable = true;
		m_stuInfo.bBreakInAlarmEnable = TRUE;
	}
	else
	{
		m_stuInfo.bBreakInAlarmEnable = FALSE;
	}
	
	// repeat enter alarm enable
	if (m_chkRepeatEnterAlarm.GetCheck())
	{
        m_stuInfo.abRepeatEnterAlarmEnable = true;
		m_stuInfo.bRepeatEnterAlarm = TRUE;
	}
	else
	{
		m_stuInfo.bRepeatEnterAlarm = FALSE;
	}
	
	// door not close enable
	if (m_chkDoorNotCloseAlarm.GetCheck())
	{
        m_stuInfo.abDoorNotClosedAlarmEnable = true;
		m_stuInfo.bDoorNotClosedAlarmEnable = TRUE;
	}
	else
	{
		m_stuInfo.bDoorNotClosedAlarmEnable = FALSE;
	}
	
	// duress alarm enable
	if (m_chkDuressAlarm.GetCheck())
	{
        m_stuInfo.abDuressAlarmEnable = true;
		m_stuInfo.bDuressAlarmEnable = TRUE;
	}
	else
	{
		m_stuInfo.bDuressAlarmEnable = FALSE;
	}
	
	// sensor alarm enable
	if (m_chkSensor.GetCheck())
	{
        m_stuInfo.abSensorEnable = true;
		m_stuInfo.bSensorEnable = TRUE;
	}
	else
	{
		m_stuInfo.bSensorEnable = FALSE;
	}

	// time section...

	// first enter enable
	if (m_chkFirstEnterEnable.GetCheck())
	{
        m_stuInfo.abFirstEnterEnable = true;
		m_stuInfo.stuFirstEnterInfo.bEnable = TRUE;
	}
	else
	{
		m_stuInfo.stuFirstEnterInfo.bEnable = FALSE;
	}

    // remote check
    if (m_chkRemoteCheck.GetCheck())
    {
        m_stuInfo.abRemoteCheck = true;
        m_stuInfo.bRemoteCheck = TRUE;
    }
    else
    {
        m_stuInfo.bRemoteCheck = FALSE;
    }
}

void CDlgCfgAccessControl::StuToDlg()
{
	// door open method
    BOOL bMethodFound = FALSE;
    for (int i = 0; i < sizeof(stuDemoOpenMethod)/sizeof(stuDemoOpenMethod[0]); i++)
    {
        if (m_stuInfo.emDoorOpenMethod == stuDemoOpenMethod[i].emOpenMethod)
        {
            bMethodFound = TRUE;
            m_cmbOpenMethod.SetCurSel(i);
            break;
        }
    }
    if (!bMethodFound)
    {
        m_cmbOpenMethod.SetCurSel(-1);
    }

	// door unlock hold time
	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_UNLOCKHOLD, m_stuInfo.nUnlockHoldInterval);
	
	// door close timeout
	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_CLOSETIMEOUT, m_stuInfo.nCloseTimeout);
	
	// open time index in config of AccessTimeSchedule, start from 0
	m_cmbOpenTimeIndex.SetCurSel(m_stuInfo.nOpenAlwaysTimeIndex);
	
	// holiday record set recNo
	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_HOLIDAYTIMERECNO, m_stuInfo.nHolidayTimeRecoNo);

	// first enter time index
	SetDlgItemInt(IDC_ACCESSCONTROL_EDT_FIRSTENTER_TIMERINDEX, m_stuInfo.stuFirstEnterInfo.nTimeIndex);

	// first enter status
	m_cbFirstEnterStatus.SetCurSel((int)m_stuInfo.stuFirstEnterInfo.emStatus);

	
	// break in alarm enable
    if (m_stuInfo.abBreakInAlarmEnable)
    {
        if (m_stuInfo.bBreakInAlarmEnable)
        {
            m_chkBreakAlarm.SetCheck(BST_CHECKED);
        }
        else
        {
            m_chkBreakAlarm.SetCheck(BST_UNCHECKED);
        }
    }
    else
    {
        m_chkBreakAlarm.SetCheck(BST_UNCHECKED);
    }
	
	// repeat enter alarm enable
    if (m_stuInfo.abRepeatEnterAlarmEnable)
    {
        if (m_stuInfo.bRepeatEnterAlarm)
        {
            m_chkRepeatEnterAlarm.SetCheck(BST_CHECKED);
        }
        else
        {
            m_chkRepeatEnterAlarm.SetCheck(BST_UNCHECKED);
        }
    }
    else
    {
        m_chkRepeatEnterAlarm.SetCheck(BST_UNCHECKED);
    }
	
	// door not close enable
    if (m_stuInfo.abDoorNotClosedAlarmEnable)
    {
        if (m_stuInfo.bDoorNotClosedAlarmEnable)
        {
            m_chkDoorNotCloseAlarm.SetCheck(BST_CHECKED);
        }
        else
        {
            m_chkDoorNotCloseAlarm.SetCheck(BST_UNCHECKED);
        }
    } 
    else
    {
        m_chkDoorNotCloseAlarm.SetCheck(BST_UNCHECKED);
    }
	
	// duress alarm enable
    if (m_stuInfo.abDuressAlarmEnable)
    {
        if (m_stuInfo.bDuressAlarmEnable)
        {
            m_chkDuressAlarm.SetCheck(BST_CHECKED);
        }
        else
        {
            m_chkDuressAlarm.SetCheck(BST_UNCHECKED);
        }
    } 
    else
    {
        m_chkDuressAlarm.SetCheck(BST_UNCHECKED);
    }
	
	// sensor alarm enable
    if (m_stuInfo.abSensorEnable)
    {
        if (m_stuInfo.bSensorEnable)
        {
            m_chkSensor.SetCheck(BST_CHECKED);
        }
        else
        {
            m_chkSensor.SetCheck(BST_UNCHECKED);
        }
    }
    else
    {
        m_chkSensor.SetCheck(BST_UNCHECKED);
    }
	
	// time section...

	//first enter enable
    if (m_stuInfo.abFirstEnterEnable)
    {
        if (m_stuInfo.stuFirstEnterInfo.bEnable)
        {
            m_chkFirstEnterEnable.SetCheck(BST_CHECKED);
        }
        else
        {
            m_chkFirstEnterEnable.SetCheck(BST_UNCHECKED);
        }
    }
    else
    {
        m_chkFirstEnterEnable.SetCheck(BST_UNCHECKED);
    }

    // remote check
    if (m_stuInfo.abRemoteCheck)
    {
        if (m_stuInfo.bRemoteCheck)
        {
            m_chkRemoteCheck.SetCheck(BST_CHECKED);
        }
        else
        {
            m_chkRemoteCheck.SetCheck(BST_UNCHECKED);
        }
    }
    else
    {
        m_chkRemoteCheck.SetCheck(BST_UNCHECKED);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgAccessControl message handlers

BOOL CDlgCfgAccessControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this, DLG_CFG_ACCESS_CONTROL);
	// TODO: Add extra initialization here
	InitDlg();
	if (GetConfigFromDevice())
	{
		StuToDlg();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgAccessControl::OnAccessControlBtnTimeSection() 
{
	// TODO: Add your control notification handler code here
	CSubDlgCfgDoorOpenTimeSection dlg(this);
	dlg.SetTimeSection(&m_stuInfo.stuDoorTimeSection[0][0]);
	if (IDOK == dlg.DoModal())
	{
		for (int i = 0; i < WEEK_DAY_NUM; i++)
		{
			for (int j = 0; j < MAX_DOOR_TIME_SECTION; j++)
			{
				const CFG_DOOROPEN_TIMESECTION_INFO* pstuTimeSection = dlg.GetTimeSection(i, j);
				if (pstuTimeSection)
				{
					memcpy(&m_stuInfo.stuDoorTimeSection[i][j], pstuTimeSection, sizeof(CFG_DOOROPEN_TIMESECTION_INFO));
				}
			}
		}
	}
}

void CDlgCfgAccessControl::OnAccessControlBtnGet() 
{
	// TODO: Add your control notification handler code here
	if (GetConfigFromDevice())
	{
		StuToDlg();
	}
}

void CDlgCfgAccessControl::OnAccessControlBtnSet() 
{
	// TODO: Add your control notification handler code here
	DlgToStu();
	SetConfigToDevice();
}

void CDlgCfgAccessControl::OnSelchangeAccesscontrolCmbChannel() 
{
	// TODO: Add your control notification handler code here
	OnAccessControlBtnGet();
}
