// AlarmOnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "AlarmOnDlg.h"
#include "IVSFDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmOnDlg dialog


CAlarmOnDlg::CAlarmOnDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmOnDlg::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CAlarmOnDlg)
	//}}AFX_DATA_INIT

	m_pIVSDemoDlg = NULL;
	m_nChannelCount = 0;
	memset(m_gChannelSel, 0, sizeof(m_gChannelSel));
}


void CAlarmOnDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CAlarmOnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmOnDlg)
	DDX_Control(pDX, IDC_LIST_CHANNEL, m_lsChannels);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmOnDlg, CDialog)
	//{{AFX_MSG_MAP(CAlarmOnDlg)
	ON_BN_CLICKED(IDC_BUTTON_SELALL, OnButtonSelall)
	ON_BN_CLICKED(IDC_BUTTON_ANTISEL, OnButtonAntisel)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAlarmOnDlg, CDialog)
	//{{AFX_DISPATCH_MAP(CAlarmOnDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAlarmOnDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {E49341FF-237B-4208-A0BC-9D6E615F3054}
static const IID IID_IAlarmOnDlg =
{ 0xe49341ff, 0x237b, 0x4208, { 0xa0, 0xbc, 0x9d, 0x6e, 0x61, 0x5f, 0x30, 0x54 } };

BEGIN_INTERFACE_MAP(CAlarmOnDlg, CDialog)
	INTERFACE_PART(CAlarmOnDlg, IID_IAlarmOnDlg, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmOnDlg message handlers

BOOL CAlarmOnDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	m_lsChannels.DeleteAllItems();
	char szBuf[16]={0};
	BOOL bSatrt = FALSE;
	m_lsChannels.SetExtendedStyle(m_lsChannels.GetExtendedStyle() | 
		LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_lsChannels.InsertColumn(0, ConvertString("ObjectType"), LVCFMT_LEFT, 80, -1);
	for (int i = 0; i < m_nChannelCount; i++)
	{
		CString  strChName = ConvertString("channel") + itoa(i, szBuf, 10);
		m_lsChannels.InsertItem(LVIF_TEXT|LVIF_STATE,i,strChName,0,LVIS_SELECTED,0,0);
		if (m_gChannelSel[i] != 0)
		{
			m_lsChannels.SetCheck(i,TRUE);
			bSatrt = TRUE;
		}
	}
	
	if (bSatrt)
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_CHANNEL)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_BUTTON_SELALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANTISEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_CHANNEL)->EnableWindow(TRUE);
		
		GetDlgItem(IDC_BUTTON_SELALL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ANTISEL)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	}
	
	return TRUE;
}

void CAlarmOnDlg::Init(int nChannelCount, CIVSFDemoDlg* pIVSFDemoDlg, LLONG* pChannelHandle)
{
	m_nChannelCount = nChannelCount;
	m_pIVSDemoDlg = pIVSFDemoDlg;

	for (int i = 0; i < nChannelCount; i++)
	{
		if (pChannelHandle[i] != 0)
		{
			m_gChannelSel[i] = 1;
		}
	}
	return;
}

void CAlarmOnDlg::OnOK() 
{
	for (int i = 0; i < m_nChannelCount; i++)
	{
		m_gChannelSel[i] = m_lsChannels.GetCheck(i);
	}

	m_pIVSDemoDlg->AlarmLoad(m_gChannelSel, TRUE);

	CDialog::OnOK();
}

void CAlarmOnDlg::OnButtonSelall() 
{
	for(int i = 0; i < m_nChannelCount; i++)
	{
		m_lsChannels.SetCheck(i, 1);
	}

}

void CAlarmOnDlg::OnButtonAntisel() 
{
	for(int i = 0; i < m_nChannelCount; i++)
	{
		if (m_lsChannels.GetCheck(i) == 1)
		{
			m_lsChannels.SetCheck(i, 0);
		}
		else
		{
			m_lsChannels.SetCheck(i, 1);
		}
	}

}

void CAlarmOnDlg::OnButtonStop() 
{
	for (int i = 0; i < m_nChannelCount; i++)
	{
		m_gChannelSel[i] = m_lsChannels.GetCheck(i);
	}
	
	m_pIVSDemoDlg->AlarmLoad(m_gChannelSel, FALSE);

	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_CHANNEL)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_BUTTON_SELALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ANTISEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
}
