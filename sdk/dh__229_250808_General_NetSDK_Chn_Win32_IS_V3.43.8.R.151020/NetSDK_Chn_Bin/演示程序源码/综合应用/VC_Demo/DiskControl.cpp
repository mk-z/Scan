// DiskControl.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "DiskControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiskControl dialog


CDiskControl::CDiskControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDiskControl::IDD, pParent)
{
	memset(&m_devWorkState, 0, sizeof(NET_DEV_WORKSTATE));
	//{{AFX_DATA_INIT(CDiskControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDiskControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiskControl)
	DDX_Control(pDX, IDC_DISKSEL_COMBO, m_disksel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiskControl, CDialog)
	//{{AFX_MSG_MAP(CDiskControl)
	ON_CBN_SELCHANGE(IDC_DISKSEL_COMBO, OnSelchangeDiskselCombo)
	/*
	ON_BN_CLICKED(IDC_CLEAR_DATA, OnClearData)
	ON_BN_CLICKED(IDC_SET_READ_WRITE, OnSetReadWrite)
	ON_BN_CLICKED(IDC_SET_READ_ONLY, OnSetReadOnly)
	ON_BN_CLICKED(IDC_SET_REDUNDANT, OnSetRedundant)
	ON_BN_CLICKED(IDC_ERROR_RECOVERY, OnErrorRecovery)
	*/
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiskControl message handlers

BOOL CDiskControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	BOOL bRet = CLIENT_GetDEVWorkState(m_dev->LoginID, &m_devWorkState);
	if (bRet)
	{/*
		CString str;
		//show disk num
		str.Format("%d", m_devWorkState.ideInfo.ide_num);
		GetDlgItem(IDC_DISK_NUM)->SetWindowText(str);

		//show ide port num
		str.Format("%d", m_devWorkState.ideInfo.ide_port);
		GetDlgItem(IDC_IDE_PORT)->SetWindowText(str);
		
		//show ide mask
		str.Format("0x%04x", m_devWorkState.ideInfo.ide_msk);
		GetDlgItem(IDC_IDE_MASK)->SetWindowText(str);

		//show bad disk mask
		str.Format("0x%04x", m_devWorkState.ideInfo.ide_bad);
		GetDlgItem(IDC_BAD_MASK)->SetWindowText(str);
		
		//show disk sizes
		for (int i = 0; i < m_devWorkState.ideInfo.ide_num; i++)
		{
			str.Format("Disk %d", i+1);
			m_disksel.InsertString(i, str.GetBuffer(0));
			m_disksel.SetItemData(i, m_devWorkState.ideInfo.ide_cap[i]);
		}
		if (m_disksel.GetCount() > 0)
		{
			m_disksel.SetCurSel(0);
			OnSelchangeDiskselCombo();
		}
		*/
	}	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDiskControl::OnSelchangeDiskselCombo() 
{/*
	int n = m_disksel.GetCurSel();
	CString str;
	NET_DRIVER_INFO *info = &m_devWorkState.driverInfo[n];
	str.Format(" Driver type: %d, Driver index: %d\n size: %d, Remain: %d, Record sections: %d\n\n Record section 1:\n %d-%02d-%02d %02d:%02d:%02d ~ %d-%02d-%02d %02d:%02d:%02d\n\n Record section 2:\n %d-%02d-%02d %02d:%02d:%02d ~ %d-%02d-%02d %02d:%02d:%02d\n\n",
		
				info->driver_type, info->index, info->total_space, info->remain_space, info->section_count,

				info->start_time1.dwYear, info->start_time1.dwMonth, info->start_time1.dwDay,
				info->start_time1.dwHour, info->start_time1.dwMinute, info->start_time1.dwSecond,
				info->end_time1.dwYear, info->end_time1.dwMonth, info->end_time1.dwDay,
				info->end_time1.dwHour, info->end_time1.dwMinute, info->end_time1.dwSecond,

				info->start_time2.dwYear, info->start_time2.dwMonth, info->start_time2.dwDay,
				info->start_time2.dwHour, info->start_time2.dwMinute, info->start_time2.dwSecond,
				info->end_time2.dwYear, info->end_time2.dwMonth, info->end_time2.dwDay,
				info->end_time2.dwHour, info->end_time2.dwMinute, info->end_time2.dwSecond
				);
	CString strWrk;
	if (info->is_current)
	{
		strWrk.Format(" Is working: Yes");
	}
	else
	{
		strWrk.Format(" Is working: No");
	}

	str += strWrk;
	 
	GetDlgItem(IDC_DISK_INFO)->SetWindowText(str.GetBuffer(0));
	*/
}

void CDiskControl::SetDeviceId(DeviceNode *dev)
{
	m_dev = dev;
}
/*
void CDiskControl::OnClearData() 
{
	DISKCTRL_PARAM diskParam;
	diskParam.dwSize = sizeof(DISKCTRL_PARAM);
	diskParam.nIndex = m_disksel.GetCurSel();		//Ó²ÅÌºÅ
	diskParam.ctrlType = 0;		// 0 - clear data
	CLIENT_ControlDevice(m_dev->LoginID, CTRL_DISK, &diskParam);
}

void CDiskControl::OnSetReadWrite() 
{
	DISKCTRL_PARAM diskParam;
	diskParam.dwSize = sizeof(DISKCTRL_PARAM);
	diskParam.nIndex = m_disksel.GetCurSel();		//Ó²ÅÌºÅ
	diskParam.ctrlType = 1;		// 1 - set as read-write
	CLIENT_ControlDevice(m_dev->LoginID, CTRL_DISK, &diskParam);
}

void CDiskControl::OnSetReadOnly() 
{
	DISKCTRL_PARAM diskParam;
	diskParam.dwSize = sizeof(DISKCTRL_PARAM);
	diskParam.nIndex = m_disksel.GetCurSel();		//Ó²ÅÌºÅ
	diskParam.ctrlType = 2;		// 2 - set as read-only
	CLIENT_ControlDevice(m_dev->LoginID, CTRL_DISK, &diskParam);
}

void CDiskControl::OnSetRedundant() 
{
	DISKCTRL_PARAM diskParam;
	diskParam.dwSize = sizeof(DISKCTRL_PARAM);
	diskParam.nIndex = m_disksel.GetCurSel();		//Ó²ÅÌºÅ
	diskParam.ctrlType = 3;		// 2 - set as redundant
	CLIENT_ControlDevice(m_dev->LoginID, CTRL_DISK, &diskParam);
}

void CDiskControl::OnErrorRecovery() 
{
	DISKCTRL_PARAM diskParam;
	diskParam.dwSize = sizeof(DISKCTRL_PARAM);
	diskParam.nIndex = m_disksel.GetCurSel();		//Ó²ÅÌºÅ
	diskParam.ctrlType = 4;		// 4 - error recovery
	CLIENT_ControlDevice(m_dev->LoginID, CTRL_DISK, &diskParam);
}
*/
