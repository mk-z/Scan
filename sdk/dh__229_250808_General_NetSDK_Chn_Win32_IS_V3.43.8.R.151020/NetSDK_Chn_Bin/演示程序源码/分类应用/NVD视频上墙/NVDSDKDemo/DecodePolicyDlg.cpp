// DecodePolicyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "DecodePolicyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DecodePolicyDlg dialog


DecodePolicyDlg::DecodePolicyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DecodePolicyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DecodePolicyDlg)
	m_strTimeRegion = _T("");
	m_nDecodeTime = 0;
	//}}AFX_DATA_INIT
}


void DecodePolicyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DecodePolicyDlg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cbChannelID);
	DDX_Text(pDX, IDC_STATIC_REGION, m_strTimeRegion);
	DDX_Text(pDX, IDC_EDIT_TIME, m_nDecodeTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DecodePolicyDlg, CDialog)
	//{{AFX_MSG_MAP(DecodePolicyDlg)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DecodePolicyDlg message handlers

BOOL DecodePolicyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);


	DEV_DECODER_INFO devDecoderInfo = {0};
	BOOL bRet = CLIENT_QueryDecoderInfo(m_lLoginID, &devDecoderInfo, 3000);
	if(bRet == FALSE)
	{
		AfxMessageBox(ConvertString("Query decoder information failed!"));
		return FALSE;
	}
	
	CString strChannel;
	for(int nNum = 0; nNum < devDecoderInfo.nEncoderNum; nNum++)
	{
		strChannel.Format(ConvertString("Channel") + "%d", nNum);
		m_cbChannelID.AddString(strChannel);
	}
	m_cbChannelID.SetCurSel(0);

	OnButtonRefresh();
	return TRUE;
}

void DecodePolicyDlg::SetDlgParam(LONG lLoginID)
{
	m_lLoginID = lLoginID;
}

void DecodePolicyDlg::OnButtonSave() 
{
	UpdateData(TRUE);
	int nChannelId = m_cbChannelID.GetCurSel();

	if (m_nDecodeTime >= m_stuDecodePolicy.nMinTime 
		&& m_nDecodeTime <= m_stuDecodePolicy.nMaxTime)
	{
		m_stuDecodePolicy.nDeocdeBufTime = m_nDecodeTime;
		BOOL bRet = CLIENT_SetDevConfig(m_lLoginID, DH_DEV_DECODE_POLICY_CFG, nChannelId, &m_stuDecodePolicy, 
			sizeof(DHDEV_DECODEPOLICY_CFG));
		
		if (!bRet)
		{
			MessageBox(ConvertString("Save failed!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Save failed! Wrong value!"), ConvertString("Prompt"));
	}
}

void DecodePolicyDlg::OnButtonRefresh() 
{
	int nChannelId = m_cbChannelID.GetCurSel();

	BOOL bRet = FALSE;
	unsigned long lRet = 0;
	memset(&m_stuDecodePolicy, 0, sizeof(DHDEV_DECODEPOLICY_CFG));
	bRet = CLIENT_GetDevConfig(m_lLoginID, DH_DEV_DECODE_POLICY_CFG, nChannelId,
		&m_stuDecodePolicy, sizeof(DHDEV_DECODEPOLICY_CFG), &lRet);
	if(!bRet)
	{
		MessageBox(ConvertString("Refresh failed!"), ConvertString("Prompt"));
	}
	else
	{
		m_nDecodeTime = m_stuDecodePolicy.nDeocdeBufTime;
		m_strTimeRegion.Format("%d~%d ms", m_stuDecodePolicy.nMinTime, m_stuDecodePolicy.nMaxTime);
		UpdateData(FALSE);
	}
}

void DecodePolicyDlg::OnSelchangeComboChannel() 
{
	OnButtonRefresh();
}
