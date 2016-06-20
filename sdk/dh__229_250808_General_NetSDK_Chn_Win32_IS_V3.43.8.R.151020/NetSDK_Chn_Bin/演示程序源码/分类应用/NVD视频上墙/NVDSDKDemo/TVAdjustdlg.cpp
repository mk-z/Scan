// TVAdjustdlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "TVAdjustdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTVAdjustdlg dialog


CTVAdjustdlg::CTVAdjustdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTVAdjustdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTVAdjustdlg)
	m_hCurLoginID = 0;
	m_nDecChannel = 0;
	m_nCurTvID = 0;
	//memset(&m_stuTvAdjustInfo, 0, 4*sizeof(DHDEV_TVADJUST_CFG));
	m_stuTvAdjustInfo = NULL;
	//}}AFX_DATA_INIT
}


void CTVAdjustdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTVAdjustdlg)
	DDX_Control(pDX, IDC_COMBO1, m_ctlDecTV);
	DDX_Control(pDX, IDC_SLIDER_BOTTON, m_slider_botton);
	DDX_Control(pDX, IDC_SLIDER_RIGHT, m_slider_right);
	DDX_Control(pDX, IDC_SLIDER_LEFT, m_slider_left);
	DDX_Control(pDX, IDC_SLIDER_TOP, m_slider_top);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTVAdjustdlg, CDialog)
	//{{AFX_MSG_MAP(CTVAdjustdlg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_TOP, OnReleasedcaptureSliderTop)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_LEFT, OnReleasedcaptureSliderLeft)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RIGHT, OnReleasedcaptureSliderRight)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BOTTON, OnReleasedcaptureSliderBotton)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTVAdjustdlg message handlers

BOOL CTVAdjustdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here

	m_slider_top.SetRange(0, 100);
	m_slider_botton.SetRange(0, 100);
	m_slider_left.SetRange(0, 100);
	m_slider_right.SetRange(0, 100);

	CString strText = "";
	int nIndex = 0;
	for (int i = 0; i < m_nDecChannel; i++)
	{
		strText.Format("TV %d", i);
		nIndex = m_ctlDecTV.AddString(strText);
		m_ctlDecTV.SetItemData(nIndex, i);
	}
	m_ctlDecTV.SetCurSel(0);
	OnSelchangeCombo1();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTVAdjustdlg::OnReleasedcaptureSliderTop(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_stuTvAdjustInfo[m_nCurTvID].nTop = m_slider_top.GetPos();

	CString str;
	str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nTop);
	((CStatic *)GetDlgItem(IDC_INT_TOP))->SetWindowText(str);
	
	*pResult = 0;
}

void CTVAdjustdlg::OnReleasedcaptureSliderLeft(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_stuTvAdjustInfo[m_nCurTvID].nLeft = m_slider_left.GetPos();
	CString str;
	str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nLeft);
	((CStatic *)GetDlgItem(IDC_INT_LEFT))->SetWindowText(str);
	*pResult = 0;
}

void CTVAdjustdlg::OnReleasedcaptureSliderRight(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_stuTvAdjustInfo[m_nCurTvID].nRight = m_slider_right.GetPos();
	CString str;
	str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nRight);
	((CStatic *)GetDlgItem(IDC_INT_RIGHT))->SetWindowText(str);
	*pResult = 0;
}

void CTVAdjustdlg::OnReleasedcaptureSliderBotton(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_stuTvAdjustInfo[m_nCurTvID].nBotton = m_slider_botton.GetPos();
	CString str;
	str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nBotton);
	((CStatic *)GetDlgItem(IDC_INT_BOTTON))->SetWindowText(str);
	*pResult = 0;
}

void CTVAdjustdlg::SetDlgParam(LLONG lLoginID, int nDevChannel)
{
	m_hCurLoginID = lLoginID;
	m_nDecChannel = nDevChannel;
	if (nDevChannel > 0)
	{
		m_stuTvAdjustInfo = new DHDEV_TVADJUST_CFG[m_nDecChannel];
	}
	
}

void CTVAdjustdlg::OnSelchangeCombo1() 
{
	int nIndex = m_ctlDecTV.GetCurSel();
	if (nIndex != -1)
	{
		int nTVId = m_ctlDecTV.GetItemData(nIndex);
		m_nCurTvID = nTVId;
		DWORD dwRetLen = 0;
		BOOL bRet = CLIENT_GetDevConfig(m_hCurLoginID, DH_DEV_TV_ADJUST_CFG, nTVId, &m_stuTvAdjustInfo[nTVId], sizeof(DHDEV_TVADJUST_CFG), &dwRetLen, 2000);
		if (bRet && dwRetLen == sizeof(DHDEV_TVADJUST_CFG))
		{
			m_slider_top.SetPos(m_stuTvAdjustInfo[nTVId].nTop);
			m_slider_botton.SetPos(m_stuTvAdjustInfo[nTVId].nBotton);
			m_slider_left.SetPos(m_stuTvAdjustInfo[nTVId].nLeft);
			m_slider_right.SetPos(m_stuTvAdjustInfo[nTVId].nRight);	

			CString str;
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nRight);
			((CStatic *)GetDlgItem(IDC_INT_RIGHT))->SetWindowText(str);
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nBotton);
			((CStatic *)GetDlgItem(IDC_INT_BOTTON))->SetWindowText(str);
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nLeft);
			((CStatic *)GetDlgItem(IDC_INT_LEFT))->SetWindowText(str);
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nTop);
			((CStatic *)GetDlgItem(IDC_INT_TOP))->SetWindowText(str);
			
		}
		else
		{
			MessageBox(ConvertString("Failed to query!"), ConvertString("Prompt"));
		}
	}	

	UpdateData(FALSE);
}



void CTVAdjustdlg::OnOK() 
{
	int nRet = 0;
	DWORD dwRetLen = 0;
	nRet = CLIENT_SetDevConfig(m_hCurLoginID, DH_DEV_TV_ADJUST_CFG, m_nCurTvID, &m_stuTvAdjustInfo[m_nCurTvID], sizeof(DHDEV_TVADJUST_CFG), 2000);
	if (nRet) 
	{
		nRet = CLIENT_GetDevConfig(m_hCurLoginID, DH_DEV_TV_ADJUST_CFG, m_nCurTvID, &m_stuTvAdjustInfo[m_nCurTvID], sizeof(DHDEV_TVADJUST_CFG), &dwRetLen, 2000);
		if (nRet && dwRetLen == sizeof(DHDEV_TVADJUST_CFG))
		{
			m_slider_top.SetPos(m_stuTvAdjustInfo[m_nCurTvID].nTop);
			m_slider_botton.SetPos(m_stuTvAdjustInfo[m_nCurTvID].nBotton);
			m_slider_left.SetPos(m_stuTvAdjustInfo[m_nCurTvID].nLeft);
			m_slider_right.SetPos(m_stuTvAdjustInfo[m_nCurTvID].nRight);

			CString str;
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nRight);
			((CStatic *)GetDlgItem(IDC_INT_RIGHT))->SetWindowText(str);
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nBotton);
			((CStatic *)GetDlgItem(IDC_INT_BOTTON))->SetWindowText(str);
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nLeft);
			((CStatic *)GetDlgItem(IDC_INT_LEFT))->SetWindowText(str);
			str.Format("[%d]", m_stuTvAdjustInfo[m_nCurTvID].nTop);
			((CStatic *)GetDlgItem(IDC_INT_TOP))->SetWindowText(str);

		}
		else
		{
			MessageBox(ConvertString("Failed to query!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Failed to set!"), ConvertString("Prompt"));

	}
	
	UpdateData(FALSE);
}

void CTVAdjustdlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (m_stuTvAdjustInfo)
	{
		delete[] m_stuTvAdjustInfo;
		m_stuTvAdjustInfo = NULL;
	}
	CDialog::OnCancel();
}
