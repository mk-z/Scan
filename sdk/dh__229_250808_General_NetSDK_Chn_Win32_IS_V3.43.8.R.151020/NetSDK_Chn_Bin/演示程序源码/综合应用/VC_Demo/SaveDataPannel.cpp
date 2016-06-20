// SaveDataPannel.cpp : implementation file
//

#include "StdAfx.h"
#include "netsdkdemo.h"
#include "SaveDataPannel.h"
#include "NetSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveDataPannel dialog


CSaveDataPannel::CSaveDataPannel(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveDataPannel::IDD, pParent)
{
	m_myBrush.CreateSolidBrush(RGB(195,195,195));
	//{{AFX_DATA_INIT(CSaveDataPannel)
	//}}AFX_DATA_INIT
}


void CSaveDataPannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveDataPannel)
	DDX_Control(pDX, IDC_SAVECBDATARAW, m_IsSaveDataRaw);
	DDX_Control(pDX, IDC_SAVECBDATAYUV, m_IsSaveDataYuv);
	DDX_Control(pDX, IDC_SAVECBDATASTD, m_IsSaveDataStd);
	DDX_Control(pDX, IDC_SAVECBDATAPCM, m_IsSaveDataPcm);
	DDX_Control(pDX, IDC_SAVE_REALDATA, m_IsSaveRealData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveDataPannel, CDialog)
	//{{AFX_MSG_MAP(CSaveDataPannel)
	ON_BN_CLICKED(IDC_SAVE_REALDATA, OnSaveRealdata)
	ON_BN_CLICKED(IDC_SAVECBDATASTD, OnSavecbdatastd)
	ON_BN_CLICKED(IDC_SAVECBDATAYUV, OnSavecbdatayuv)
	ON_BN_CLICKED(IDC_SAVECBDATAPCM, OnSavecbdatapcm)
	ON_BN_CLICKED(IDC_SAVECBDATARAW, OnSavecbdataraw)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveDataPannel message handlers

BOOL CSaveDataPannel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	g_SetWndStaticText(this);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveDataPannel::OnSaveRealdata() 
{
	int nCheck = m_IsSaveRealData.GetCheck();
	((CNetSDKDemoDlg *)GetParent())->SaveRealdata(nCheck);
}

void CSaveDataPannel::OnSavecbdatastd() 
{
	int nCheck = m_IsSaveDataStd.GetCheck();
	((CNetSDKDemoDlg *)GetParent())->SavecbdataStd(nCheck);
}

void CSaveDataPannel::OnSavecbdatayuv() 
{
	int nCheck = m_IsSaveDataYuv.GetCheck();
	((CNetSDKDemoDlg *)GetParent())->Savecbdatayuv(nCheck);
}

void CSaveDataPannel::OnSavecbdatapcm() 
{
	int nCheck = m_IsSaveDataPcm.GetCheck();
	((CNetSDKDemoDlg *)GetParent())->Savecbdatapcm(nCheck);
}

void CSaveDataPannel::OnSavecbdataraw() 
{
	int nCheck = m_IsSaveDataRaw.GetCheck();
	((CNetSDKDemoDlg *)GetParent())->SavecbdataRaw(nCheck);
}

void CSaveDataPannel::SetCheckReal(int nCheck)
{
	m_IsSaveRealData.SetCheck(nCheck);
}

void CSaveDataPannel::SetCheckRaw(int nCheck)
{
	m_IsSaveDataRaw.SetCheck(nCheck);
}

void CSaveDataPannel::SetCheckStd(int nCheck)
{
	m_IsSaveDataStd.SetCheck(nCheck);
}

void CSaveDataPannel::SetCheckPcm(int nCheck)
{
	m_IsSaveDataPcm.SetCheck(nCheck);
}

void CSaveDataPannel::SetCheckYuv(int nCheck)
{
	m_IsSaveDataYuv.SetCheck(nCheck);
}


HBRUSH CSaveDataPannel::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetBkMode(TRANSPARENT);
	
	return m_myBrush;
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


BOOL CSaveDataPannel::PreTranslateMessage(MSG* pMsg) 
{
	if (WM_KEYDOWN == pMsg->message && 
		(VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam))
	{
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
