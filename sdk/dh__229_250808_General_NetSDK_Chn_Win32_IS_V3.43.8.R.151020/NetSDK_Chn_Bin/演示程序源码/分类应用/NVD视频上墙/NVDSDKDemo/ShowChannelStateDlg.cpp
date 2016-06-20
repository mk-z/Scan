// ShowChannelStateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "ShowChannelStateDlg.h"
#include "dhnetsdk.h"
#include "NVDSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowChannelStateDlg dialog


CShowChannelStateDlg::CShowChannelStateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowChannelStateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowChannelStateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_nDecChannel = 0;
}


void CShowChannelStateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowChannelStateDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowChannelStateDlg, CDialog)
	//{{AFX_MSG_MAP(CShowChannelStateDlg)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowChannelStateDlg message handlers

void CShowChannelStateDlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnRefreshInfo();
	CDialog::OnTimer(nIDEvent);
}

void CShowChannelStateDlg::SetDlgParam(int nDecChannel)
{
 	m_nDecChannel = nDecChannel;
}

//刷新显示当前解码器的信息
void CShowChannelStateDlg::OnRefreshInfo() 
{
	CString str = "";
	
	for (int i = 0; i < m_nDecChannel; i++)
	{
		DEV_DECCHANNEL_STATE stChannelState = {0};
		
		CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
		if (pParentDlg != NULL)
		{
			int nRet = pParentDlg->GetChannelState(i, &stChannelState);
			if (nRet <= 0)
			{
				continue;
			}
		}
		
		if (stChannelState.byEncoderID >= 0)
		{
			if(stChannelState.byChnState == 0)
			{
				str.Format("  %s", ConvertString("Idle"));
			}
			else if(stChannelState.byChnState == 1)
			{
				str.Format("  %s       %s           %d           %d           %d", ConvertString("Monitor"), stChannelState.szResolution, stChannelState.byFrame, stChannelState.nChannelFLux, stChannelState.nDecodeFlux);
			}
			else if(stChannelState.byChnState == 2)
			{
				str.Format("  %s       %s           %d           %d           %d", ConvertString("PlayBack"), stChannelState.szResolution, stChannelState.byFrame, stChannelState.nChannelFLux, stChannelState.nDecodeFlux );
			}
			else if(stChannelState.byChnState == 3)
			{
				str.Format("  %s       %s           %d           %d           %d", ConvertString("DecoderTour"), stChannelState.szResolution, stChannelState.byFrame, stChannelState.nChannelFLux, stChannelState.nDecodeFlux );
			}
			
			GetDlgItem(IDC_SPLIT_INFO1 + stChannelState.byEncoderID)->SetWindowText(str);
		}	
	}
	
}

void CShowChannelStateDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer((int)this);
	CDialog::OnClose();
}

BOOL CShowChannelStateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	g_SetWndStaticText(this);

	OnRefreshInfo();
	
	// TODO: Add extra initialization here
	SetTimer((UINT)this, 2000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
