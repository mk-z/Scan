// ModuleCfgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "ModuleCfgdlg.h"
#include "TargetFilterPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModuleCfgdlg dialog


CModuleCfgdlg::CModuleCfgdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModuleCfgdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModuleCfgdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pPreview = NULL;
	m_dwChannel = 0;
	m_pModuleCfgInfo= NULL;
	m_llRealPlayHandle = NULL;
	m_nPort = 2;
	InitializeCriticalSection(&m_csModule);
}


void CModuleCfgdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModuleCfgdlg)
	DDX_Control(pDX, IDC_SLIDER_ACCURACY, m_ctrlSliderAccuracy);
	DDX_Control(pDX, IDC_SLIDER_SENSITIVITY, m_ctrlSliderSensitivity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModuleCfgdlg, CDialog)
	//{{AFX_MSG_MAP(CModuleCfgdlg)
	ON_BN_CLICKED(IDC_BTN_ZONE_DRAW, OnBtnZoneDraw)
	ON_BN_CLICKED(IDC_BTN_ZONE_CLEAR, OnBtnZoneClear)
	ON_BN_CLICKED(IDC_BTN_WIDTH_DRAW, OnBtnWidthDraw)
	ON_BN_CLICKED(IDC_BTN_WIDTH_CLEAR, OnBtnWidthClear)
	ON_WM_HSCROLL()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModuleCfgdlg message handlers

BOOL CModuleCfgdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	m_ctrlSliderAccuracy.SetRange(1, 10);
	m_ctrlSliderSensitivity.SetRange(1, 10);

	g_PlayAPI.PLAY_OpenStream(m_nPort, 0, 0, 1024 * 900);

	CRect rt;
	GetDlgItem(IDC_STATIC_MODULE)->GetWindowRect(&rt);
	ScreenToClient(&rt);

	m_pPreview = new CTargetFilterPreview;
	if (m_pPreview)
	{
		m_pPreview->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 5555);

		m_pPreview->MoveWindow(&rt);
		m_pPreview->ShowWindow(TRUE);
	}

	m_pModuleCfgInfo = new CFG_ANALYSEMODULES_INFO;
	if (m_pModuleCfgInfo)
	{
		ZeroMemory(m_pModuleCfgInfo, sizeof(CFG_ANALYSEMODULES_INFO));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModuleCfgdlg::OnBtnZoneDraw() 
{
	// TODO: Add your control notification handler code here
	m_pPreview->m_bDrawDetectRegion = TRUE;
	
	GetDlgItem(IDC_BTN_ZONE_DRAW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_ZONE_CLEAR)->EnableWindow(TRUE);
}

void CModuleCfgdlg::OnBtnZoneClear() 
{
	// TODO: Add your control notification handler code here
	EnterCriticalSection(&m_csModule);

	m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].nDetectRegionPoint = 0;
	ZeroMemory(m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].stuDetectRegion, sizeof(CFG_POLYGON) * 4);

	LeaveCriticalSection(&m_csModule);

	SetNewPosition(m_pModuleCfgInfo);
	GetDlgItem(IDC_BTN_ZONE_DRAW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_ZONE_CLEAR)->EnableWindow(FALSE);
}

void CModuleCfgdlg::OnBtnWidthDraw() 
{
	// TODO: Add your control notification handler code here
	m_pPreview->m_bDrawFilter = TRUE;

	GetDlgItem(IDC_BTN_WIDTH_DRAW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_WIDTH_CLEAR)->EnableWindow(TRUE);
	
}

void CModuleCfgdlg::OnBtnWidthClear() 
{
	// TODO: Add your control notification handler code here
	EnterCriticalSection(&m_csModule);

	m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].nCalibrateBoxNum = 0;
	ZeroMemory(m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].stuCalibrateBoxs,
			   sizeof(CFG_CALIBRATEBOX_INFO) * MAX_CALIBRATEBOX_NUM);

	ZeroMemory(&m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].stuFilterMaxSize, sizeof(CFG_SIZE));
	ZeroMemory(&m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].stuFilterMinSize, sizeof(CFG_SIZE));

	LeaveCriticalSection(&m_csModule);

	GetDlgItem(IDC_BTN_WIDTH_DRAW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_WIDTH_CLEAR)->EnableWindow(FALSE);
}

void CModuleCfgdlg::ShowModuleInfo(CFG_ANALYSEMODULES_INFO* pModule, DWORD dwChannel)
{
	if (!pModule || dwChannel < 0)
	{
		return;
	}

	EnterCriticalSection(&m_csModule);

	memcpy(m_pModuleCfgInfo, pModule, sizeof(CFG_ANALYSEMODULES_INFO));

	if (m_pPreview)
	{
		m_pPreview->SetModuleInfo(m_pModuleCfgInfo, dwChannel);
	}
	
	m_dwChannel = dwChannel;

	char szLeftTop[16] = {0};
	sprintf(szLeftTop, "X%d, Y%d",
			pModule->stuModuleInfo[dwChannel].stuDetectRegion[0].nX,
			pModule->stuModuleInfo[dwChannel].stuDetectRegion[0].nY);
	SetDlgItemText(IDC_EDT_ZONE_LEFTTOP, szLeftTop);

	char szRightBottom[16] = {0};
	sprintf(szRightBottom, "X%d, Y%d",
			pModule->stuModuleInfo[dwChannel].stuDetectRegion[2].nX,
			pModule->stuModuleInfo[dwChannel].stuDetectRegion[2].nY);
	SetDlgItemText(IDC_EDT_ZONE_RIGHTBOTTOM, szRightBottom);

	if (pModule->stuModuleInfo[dwChannel].nDetectRegionPoint)
	{
		m_pModuleCfgInfo->stuModuleInfo[dwChannel].nDetectRegionPoint = 4;
		memcpy(m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuDetectRegion,
			   pModule->stuModuleInfo[dwChannel].stuDetectRegion,
			   sizeof(CFG_POLYGON) * 4);
		GetDlgItem(IDC_BTN_ZONE_DRAW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ZONE_CLEAR)->EnableWindow(TRUE);
	} 
	else
	{
		m_pModuleCfgInfo->stuModuleInfo[dwChannel].nDetectRegionPoint = 0;
		ZeroMemory(m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuDetectRegion,
				   sizeof(CFG_POLYGON) * MAX_POLYGON_NUM);
		GetDlgItem(IDC_BTN_ZONE_DRAW)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ZONE_CLEAR)->EnableWindow(FALSE);
	}

	if (pModule->stuModuleInfo[dwChannel].nCalibrateBoxNum)
	{
		m_pModuleCfgInfo->stuModuleInfo[dwChannel].nAreaCalibrateBoxNum = 1;
		memcpy(m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuCalibrateBoxs,
			   pModule->stuModuleInfo[dwChannel].stuCalibrateBoxs,
			   sizeof(CFG_CALIBRATEBOX_INFO));

		SetDlgItemInt(IDC_EDT_WIDTHMAX, m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuFilterMaxSize.nWidth < 0 ? 0 : m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuFilterMaxSize.nWidth, FALSE);
		SetDlgItemInt(IDC_EDT_WIDTHMIN, m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuFilterMinSize.nWidth < 0 ? 0 : m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuFilterMinSize.nWidth, FALSE);
		GetDlgItem(IDC_BTN_WIDTH_DRAW)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_WIDTH_CLEAR)->EnableWindow(TRUE);
	} 
	else
	{
		m_pModuleCfgInfo->stuModuleInfo[dwChannel].nAreaCalibrateBoxNum = 0;
		ZeroMemory(m_pModuleCfgInfo->stuModuleInfo[dwChannel].stuCalibrateBoxs,
			sizeof(CFG_CALIBRATEBOX_INFO));
		SetDlgItemInt(IDC_EDT_WIDTHMAX, 0, FALSE);
		SetDlgItemInt(IDC_EDT_WIDTHMIN, 0, FALSE);
		GetDlgItem(IDC_BTN_WIDTH_DRAW)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_WIDTH_CLEAR)->EnableWindow(FALSE);
	}

	LeaveCriticalSection(&m_csModule);

	if (pModule->stuModuleInfo[dwChannel].bAccuracy)
	{
		m_ctrlSliderAccuracy.SetPos(pModule->stuModuleInfo[dwChannel].byAccuracy);
	} 
	
	m_ctrlSliderSensitivity.SetPos(pModule->stuModuleInfo[dwChannel].bSensitivity);
}

void CModuleCfgdlg::SaveModuleInfo(CFG_ANALYSEMODULES_INFO* pModule, DWORD dwChannel)
{
	if (!pModule || dwChannel < 0)
	{
		return;
	}

	EnterCriticalSection(&m_csModule);

	memcpy(pModule, m_pModuleCfgInfo, sizeof(CFG_ANALYSEMODULES_INFO));

	LeaveCriticalSection(&m_csModule);
}


void CModuleCfgdlg::ShowPreview(LLONG llLoginHandle, DWORD dwChannel)
{
	if (!llLoginHandle || dwChannel < 0)
	{
		return;
	}
	
	if (m_pPreview)
	{
		BOOL bRet = g_PlayAPI.PLAY_RigisterDrawFun(m_nPort, CTargetFilterPreview::DrawTargetFilterCfgProc, (DWORD)m_pPreview);
		if (!bRet)
		{
			MessageBox(ConvertString("PLAY_RigisterDrawFun failed!"), ConvertString("Prompt"));
		}
		//Begin play 
		BOOL bPlayRet = g_PlayAPI.PLAY_Play(m_nPort, m_pPreview->GetSafeHwnd());
	}
}

void CModuleCfgdlg::ClosePreview(LLONG llLoginHandle, DWORD dwChannel)
{
	if (!llLoginHandle || dwChannel < 0)
	{
		return;
	}

	g_PlayAPI.PLAY_Stop(m_nPort);
}

void CModuleCfgdlg::SetNewPosition(CFG_ANALYSEMODULES_INFO* pModule)
{
	if (!pModule)
	{
		return;
	}

	char szLeftTop[16] = {0};
	sprintf(szLeftTop, "X%d, Y%d",
			pModule->stuModuleInfo[m_dwChannel].stuDetectRegion[0].nX,
			pModule->stuModuleInfo[m_dwChannel].stuDetectRegion[0].nY);
	SetDlgItemText(IDC_EDT_ZONE_LEFTTOP, szLeftTop);
	
	char szRightBottom[16] = {0};
	sprintf(szRightBottom, "X%d, Y%d",
			pModule->stuModuleInfo[m_dwChannel].stuDetectRegion[2].nX,
			pModule->stuModuleInfo[m_dwChannel].stuDetectRegion[2].nY);
	SetDlgItemText(IDC_EDT_ZONE_RIGHTBOTTOM, szRightBottom);

	SetDlgItemInt(IDC_EDT_WIDTHMAX, pModule->stuModuleInfo[m_dwChannel].stuFilterMaxSize.nWidth, FALSE);
	SetDlgItemInt(IDC_EDT_WIDTHMIN, pModule->stuModuleInfo[m_dwChannel].stuFilterMinSize.nWidth, FALSE);
}

BOOL CModuleCfgdlg::DestroyWindow() 
{
	if (m_pPreview)
	{
		g_PlayAPI.PLAY_Stop(m_nPort);
		g_PlayAPI.PLAY_CloseStream(m_nPort);

		if (m_pPreview->GetSafeHwnd())
		{
			m_pPreview->DestroyWindow();
		}

		delete m_pPreview;
		m_pPreview = NULL;
	}

	DeleteCriticalSection(&m_csModule);

	if (m_pModuleCfgInfo)
	{
		delete m_pModuleCfgInfo;
		m_pModuleCfgInfo = NULL;
	}

	return CDialog::DestroyWindow();
}

void CModuleCfgdlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_ACCURACY)
	{
		CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
		if (pSlider && m_pModuleCfgInfo)
		{
			m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].bAccuracy = true;
			m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].byAccuracy = pSlider->GetPos();
		}
	} 
	else if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_SENSITIVITY)
	{
		CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
		if (pSlider && m_pModuleCfgInfo)
		{
			m_pModuleCfgInfo->stuModuleInfo[m_dwChannel].bSensitivity = pSlider->GetPos();
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CModuleCfgdlg::OnDestroy() 
{
	CDialog::OnDestroy();

	if (m_pPreview)
	{
		g_PlayAPI.PLAY_Stop(m_nPort);
		g_PlayAPI.PLAY_CloseStream(m_nPort);
		
		if (m_pPreview->GetSafeHwnd())
		{
			m_pPreview->DestroyWindow();
		}
		
		delete m_pPreview;
		m_pPreview = NULL;
	}

	DeleteCriticalSection(&m_csModule);

	if (m_pModuleCfgInfo)
	{
		delete m_pModuleCfgInfo;
		m_pModuleCfgInfo = NULL;
	}
}
