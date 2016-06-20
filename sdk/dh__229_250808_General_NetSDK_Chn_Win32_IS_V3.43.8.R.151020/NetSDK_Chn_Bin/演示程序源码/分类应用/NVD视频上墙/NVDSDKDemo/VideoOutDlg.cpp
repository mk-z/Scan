// VideoOutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "nvdsdkdemo.h"
#include "VideoOutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoOutDlg dialog


CVideoOutDlg::CVideoOutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoOutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoOutDlg)
	m_hCurLoginID = 0;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVideoOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoOutDlg)
	DDX_Control(pDX, IDC_COMBO_RESOLUTION,  m_ctlResolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoOutDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoOutDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoOutDlg message handlers

void GetMaskedIndex(BYTE *des, BYTE src, DWORD dwMask)
{
	if (!des || src < 0)
	{
		return;
	}
	char idx = -1;
	for (int i = 0; i< 32; i++)
	{
		if ((dwMask&(0x01<<i))) 
		{
			idx++;
		}

		if (idx >= 0 && i >= src)
		{
			break;
		}
	}
	*des = (idx >= 0)?idx:0;
}

void GetOrigIndex(BYTE *des, BYTE src, DWORD dwMask)
{
	if (!des || src < 0)
	{
		return;
	}
	char idx = -1;
	int i = 0;
	for (i = 0; i< 32; i++)
	{
		if ((dwMask&(0x01<<i))) 
		{
			idx++;
		}

		if (idx >= 0 && idx >= src)
		{
			break;
		}
	}
	*des = (idx >= 0)?i:0;
}


void CVideoOutDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CVideoOutDlg::SetDlgParam(LLONG lLoginID)
{
	m_hCurLoginID = lLoginID;
}

BOOL CVideoOutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here

	while(m_ctlResolution.GetCount() > 0)
	{
		m_ctlResolution.DeleteString(0);
	}


	BOOL bRet = FALSE;
	DWORD retlen = 0;
	memset(&m_stVideoOut, 0, sizeof(DEV_VIDEOOUT_INFO));
	if (m_hCurLoginID != 0)
	{
		bRet = CLIENT_GetDevConfig(m_hCurLoginID, DH_DEV_VIDEOOUT_CFG, 0, &m_stVideoOut, sizeof(DEV_VIDEOOUT_INFO), &retlen, 1000);
		if (!bRet || retlen != sizeof(DEV_VIDEOOUT_INFO)) 
		{
			MessageBox(ConvertString("Fail to get configuration"), ConvertString("Prompt"));
			return 0;
		}

		char *rsName[20] = {"D1", "HD1", "BCIF", "CIF", "QCIF", "VGA", "QVGA", "SVCD","QQVGA", "SVGA", "XVGA",
							"WXGA", "SXGA", "WSXGA", "UXGA", "WUXGA", "LTF", "720P", "1080P", "1.3M"};
		int rsIdx = 0;
		for (int i = 0; i < 20; i++)
		{
			if (m_stVideoOut.dwImageSizeMask & (0x01<<i))
			{
				m_ctlResolution.InsertString(rsIdx, ConvertString(rsName[i]));
				rsIdx++;
			}
		}
		BYTE byrsIdx = 0;
		GetMaskedIndex(&byrsIdx, m_stVideoOut.nImageSize, m_stVideoOut.dwImageSizeMask);		
		m_ctlResolution.SetCurSel(byrsIdx);
	}
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVideoOutDlg::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(TRUE);

	int nResolutionIndex = m_ctlResolution.GetCurSel();
	if (nResolutionIndex < 0)
	{
		return;
	}

	if (m_hCurLoginID != 0)
	{
		BYTE rsOIdx = 0;
		GetOrigIndex(&rsOIdx, nResolutionIndex, m_stVideoOut.dwImageSizeMask);
		m_stVideoOut.nImageSize = rsOIdx;
		
		BOOL bRet = CLIENT_SetDevConfig(m_hCurLoginID, DH_DEV_VIDEOOUT_CFG, 0, &m_stVideoOut, sizeof(DEV_VIDEOOUT_INFO), 1000);
		if (!bRet ) 
		{
			MessageBox(ConvertString("Fail to set configuration"), ConvertString("Prompt"));		
		}
	}
	
	CDialog::OnOK();
}

void CVideoOutDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
