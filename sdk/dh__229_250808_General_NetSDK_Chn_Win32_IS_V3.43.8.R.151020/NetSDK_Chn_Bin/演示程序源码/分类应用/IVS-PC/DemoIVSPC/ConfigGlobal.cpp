// ConfigGlobal.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "ConfigGlobal.h"
#include "DemoIVSPCDlg.h"
#include "IvsGlobalPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CConfigGlobal::CConfigGlobal(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigGlobal::IDD, pParent)
	, m_pIvsGlobalPreview(NULL)
{
	m_colorPen = RGB(0, 0, 255);
}


void CConfigGlobal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigGlobal)
	DDX_Control(pDX, IDC_CFGGLO_EDT_CHANNELNAME, m_edtChnName);
	DDX_Control(pDX, IDC_CFGGLO_CMB_SCENE, m_cmbScene);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigGlobal, CDialog)
	//{{AFX_MSG_MAP(CConfigGlobal)
	ON_CBN_SELCHANGE(IDC_CFGGLO_CMB_SCENE, OnSelchangeCfggloCmbScene)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CFGGLO_BTN_GET, OnCfggloBtnGet)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_SET, OnCfggloBtnSet)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CFGGLO_BTN_REDRAW, CConfigGlobal::OnBnClickedCfggloBtnRedraw)
	ON_BN_CLICKED(IDC_CFGGLO_BTN_RESET, CConfigGlobal::OnBnClickedCfggloBtnReset)
	ON_BN_CLICKED(IDC_BTN_HOR_LINE, CConfigGlobal::OnBnClickedBtnHorLine)
END_MESSAGE_MAP()


BOOL CConfigGlobal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	CRect rt;
	GetDlgItem(IDC_CFGGLO_STATIC_PREVIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);

	m_pIvsGlobalPreview = new CIvsGlobalPreview;
	m_pIvsGlobalPreview->Create(NULL, NULL, WS_CHILD, CRect(0, 0, 0, 0), this, 5000);
	m_pIvsGlobalPreview->MoveWindow(&rt);
	m_pIvsGlobalPreview->ShowWindow(SW_SHOW);

	return TRUE; 
}

void CConfigGlobal::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pIvsGlobalPreview)
	{
		if (m_pIvsGlobalPreview->GetSafeHwnd())
		{
			m_pIvsGlobalPreview->DestroyWindow();
		}
		
		delete m_pIvsGlobalPreview;
		m_pIvsGlobalPreview = NULL;
	}

	UninitGlobalDlg();
}

/*
 *	
 */
void CConfigGlobal::InitGlobalDlg(int nChannel)
{
	if (nChannel == -1)
	{
		UninitGlobalDlg();
		return;
	}

	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}	

	TCHAR szChnName[32] = {0};
	_sntprintf(szChnName, _countof(szChnName)*sizeof(TCHAR), _T("%s%02d"), ConvertString(_T("Channel")), nChannel + 1);
	SetDlgItemText(IDC_CFGGLO_EDT_CHANNELNAME, szChnName);

	int nChnID = 0;
	CFG_CAP_ANALYSE_INFO* pDevCapInfo = pMainDlg->GetCapAnalyseInfo(nChannel);
	int i = 0;
	CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobal = pMainDlg->GetAnalyseGlobalInfo(nChannel);
	if (pDevCapInfo && pAnalyseGlobal)
	{
		GTNODEAREA* pNodeArea = NULL;
		GTNODESTAFF* pNodeStaff = NULL;
		HTREEITEM hItem = 0;

		m_cmbScene.AddString(ConvertString(pAnalyseGlobal->szSceneType));
		if (m_cmbScene.GetCount() > 0)
		{
			m_cmbScene.SetCurSel(0);
		}
		
		CString str;
		str.Format("%0.1f", pAnalyseGlobal->CameraHeight);
		GetDlgItem(IDC_EDIT_CANMERA_HEIGHT)->SetWindowText(str);
		str.Format("%0.1f", pAnalyseGlobal->CameraDistance);
		GetDlgItem(IDC_EDIT_DISTANCE)->SetWindowText(str);
		str.Format("%0.1f", pAnalyseGlobal->CameraAngle);
		GetDlgItem(IDC_EDIT_ANGLE)->SetWindowText(str);
	}
}
/*
 *	
 */
void CConfigGlobal::UninitGlobalDlg()
{
	int nCount = m_cmbScene.GetCount();

	for (int i = 0; i < m_cmbScene.GetCount(); i++)
	{
		CFG_ANALYSEGLOBAL_INFO* pGloInfo = (CFG_ANALYSEGLOBAL_INFO*)m_cmbScene.GetItemData(i);
		if (pGloInfo)
		{
			delete pGloInfo;
			pGloInfo = NULL;
		}
	}
	m_cmbScene.ResetContent();
}

void CConfigGlobal::ShowPreview(LONG lLoginHanlde, int nChannel)
{
	if (!lLoginHanlde || nChannel < 0)
	{
		return;
	}
	
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->GetLoginHandle())
		{
			if (pMainDlg->GetRealPlayHandle())
			{
				::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
				g_PlayAPI.PLAY_Stop(g_nPlayPort);
				g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				pMainDlg->SetRealPlayHandel(0);
			}
			
			CFG_ANALYSEGLOBAL_INFO* pGlobalInfo = pMainDlg->GetAnalyseGlobalInfo(pMainDlg->GetCurrentChannel());
			if (!pGlobalInfo)
			{
				return;
			}

			long m_lPlayID = 0;
			HWND hWnd = m_pIvsGlobalPreview->GetSafeHwnd();
			NET_DEVICEINFO* pDevInfo = pMainDlg->GetDevInfo();
			int nChnCount = 0;
			if (pDevInfo)
			{
				nChnCount = pDevInfo->byChanNum;
			}
			
			//Enable stream
			BOOL bOpenRet = g_PlayAPI.PLAY_OpenStream(g_nPlayPort, 0, 0, 1024 * 900);
			if(bOpenRet)
			{
				// 从码流中提取智能分析信息
				BOOL bRet = FALSE;

				m_pIvsGlobalPreview->setGlobalInfo(pGlobalInfo, FALSE);
				bRet = g_PlayAPI.PLAY_RigisterDrawFun(g_nPlayPort, CIvsGlobalPreview::DrawIvsGlobalCfgProc, 
												(DWORD)m_pIvsGlobalPreview);
				if (!bRet)
				{
					MessageBox(ConvertString("PLAY_RigisterDrawFun failed!"), ConvertString("Prompt"));
				}
				//Begin play 
				BOOL bPlayRet = g_PlayAPI.PLAY_Play(g_nPlayPort, hWnd);
				if(bPlayRet)
				{
					//Real-time play 
					m_lPlayID = CLIENT_RealPlay(pMainDlg->GetLoginHandle(), nChannel, 0);
					if(0 != m_lPlayID)
					{
						pMainDlg->SetRealPlayHandel(m_lPlayID);
						//Callback monitor data and then save 
						CLIENT_SetRealDataCallBackEx(m_lPlayID, RealDataCallBackEx, (LDWORD)this, 0x1f);
					}
					else
					{
						g_PlayAPI.PLAY_Stop(g_nPlayPort);
						g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
						int x = ::CLIENT_GetLastError();
						MessageBox(ConvertString("Fail to play!"), ConvertString("Prompt"));
					}
				}
				else
				{
					g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
				}
			}
		}
	}
}

void CConfigGlobal::ClosePreview(LONG lRealPlayHandle)
{
	if (!lRealPlayHandle)
	{
		return;
	}
	
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		if (pMainDlg->GetRealPlayHandle())
		{
			::CLIENT_StopRealPlay(pMainDlg->GetRealPlayHandle());
			g_PlayAPI.PLAY_Stop(g_nPlayPort);
			g_PlayAPI.PLAY_CloseStream(g_nPlayPort);
			GetDlgItem(IDC_CFGGLO_STATIC_PREVIEW)->Invalidate(FALSE);
			pMainDlg->SetRealPlayHandel(0);
		}
	}
}

/*
 *	选择场景，选择的变化还将影响到模块配置和规则配置的内容
 */
void CConfigGlobal::OnSelchangeCfggloCmbScene() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	CFG_CAP_ANALYSE_INFO* pCapInfo
		= pMainDlg->GetCapAnalyseInfo(pMainDlg->GetCurrentChannel());
	CFG_ANALYSEGLOBAL_INFO* pAnalyseGlobal 
		= pMainDlg->GetAnalyseGlobalInfo(pMainDlg->GetCurrentChannel());

	CString strScenType;
	m_cmbScene.GetLBText(m_cmbScene.GetCurSel(), strScenType);
	if (strcmp(strScenType.GetBuffer(0), pAnalyseGlobal->szSceneType) == 0)
	{
		return;
	}

	int nSel = m_cmbScene.GetItemData(m_cmbScene.GetCurSel());
	if (!nSel)
	{
		return;
	}
}

/*
 *	重新从设备获取全局配置信息，并更新到界面
 */
void CConfigGlobal::OnCfggloBtnGet() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	int nChannel = pMainDlg->GetCurrentChannel();
	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo
		= (CFG_ANALYSEGLOBAL_INFO*)pMainDlg->GetAnalyseGlobalInfo(nChannel);
	if (nChannel < 0 || !pGlobalInfo)
	{
		return;
	}
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// get global info
	BOOL bSuccess = CLIENT_GetNewDevConfig(pMainDlg->GetLoginHandle(), CFG_CMD_ANALYSEGLOBAL
											, nChannel, szOutBuffer, _countof(szOutBuffer), &nErr);
	if (bSuccess)
	{
		int nRetLen = 0;
		BOOL bRet = CLIENT_ParseData(CFG_CMD_ANALYSEGLOBAL, szOutBuffer, (char*)pGlobalInfo, 
						   				sizeof(CFG_ANALYSEGLOBAL_INFO), &nRetLen);
		if (bRet == FALSE)
		{
			MessageBox(ConvertString("Parser data error!"), ConvertString("Prompt"));
			return;
		}
	}
	else
	{
		MessageBox(ConvertString("Get GlobalInfo failed!"), ConvertString("Prompt"));
		return;
	}

	ClosePreview(pMainDlg->GetRealPlayHandle());
	UninitGlobalDlg();

	InitGlobalDlg(nChannel);
	m_pIvsGlobalPreview->setGlobalInfo(NULL, TRUE);
	m_pIvsGlobalPreview->Invalidate(FALSE);
	ShowPreview(pMainDlg->GetLoginHandle(), nChannel);
}

/*
 *	将界面上的配置信息打包上传到设备
 */
void CConfigGlobal::OnCfggloBtnSet() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	
	int nChannel = pMainDlg->GetCurrentChannel();
	CFG_ANALYSEGLOBAL_INFO* pGlobalInfo
		= (CFG_ANALYSEGLOBAL_INFO*)pMainDlg->GetAnalyseGlobalInfo(nChannel);
	if (nChannel < 0 || !pGlobalInfo)
	{
		return;
	}

	CString str;
	GetDlgItem(IDC_EDIT_CANMERA_HEIGHT)->GetWindowText(str);
	pGlobalInfo->CameraHeight = atof(str.GetBuffer(0));
	GetDlgItem(IDC_EDIT_DISTANCE)->GetWindowText(str);
	pGlobalInfo->CameraDistance = atof(str.GetBuffer(0));
	GetDlgItem(IDC_EDIT_ANGLE)->GetWindowText(str); 
	pGlobalInfo->CameraAngle = atof(str.GetBuffer(0));	
	
	int nErr = 0;
	char szOutBuffer[32 * 1024] = {0};
	
	// set global info
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ANALYSEGLOBAL, (LPVOID)pGlobalInfo,sizeof(CFG_ANALYSEGLOBAL_INFO)
									, szOutBuffer, _countof(szOutBuffer));
	if (!bRet)
	{
		MessageBox(ConvertString(_T("Packet data error!")), ConvertString("Prompt"));
		return;
	}
	
	int nRetLen = 0;
	bRet = CLIENT_SetNewDevConfig(pMainDlg->GetLoginHandle(), CFG_CMD_ANALYSEGLOBAL 
								  , nChannel, szOutBuffer, _countof(szOutBuffer), &nErr, &nRetLen);
	if (bRet)
	{
		MessageBox(ConvertString(_T("Set GlobalInfo Successfully!")), ConvertString("Prompt"));
	}
	else
	{
		MessageBox(ConvertString(_T("Set GlobalInfo Failed!")), ConvertString("Prompt"));
	}
}

void CConfigGlobal::OnBnClickedCfggloBtnRedraw()
{
	// TODO: 在此添加控件通知处理程序代码
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	NET_IN_SETMODULESTATE inState = {0};
	inState.dwSize = sizeof(inState);
	NET_OUT_SETMODULESTATE outState = {0};
	outState.dwSize = sizeof(outState);
	BOOL bRet = CLIENT_OperateVideoAnalyseDevice(pMainDlg->GetLoginHandle(), pMainDlg->GetCurrentChannel()
													, NET_SET_MODULESTATE, &inState, &outState);
	if (bRet)
	{
		MessageBox(ConvertString("Set success!"), ConvertString("Prompt"));
	}
}

void CConfigGlobal::OnBnClickedCfggloBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	CDemoIVSPCDlg* pMainDlg = (CDemoIVSPCDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	NET_IN_RESETINTERNAL_OPTION inState = {0};
	inState.dwSize = sizeof(inState);
	NET_OUT_RESETINTERNAL_OPTION outState = {0};
	outState.dwSize = sizeof(outState);
	BOOL bRet = CLIENT_OperateVideoAnalyseDevice(pMainDlg->GetLoginHandle(), pMainDlg->GetCurrentChannel()
														, NET_RESET_INTERNALOPTIONS, &inState, &outState);
	if (bRet)
	{
		MessageBox(ConvertString("Reset Parameter Succeed!"), ConvertString("Prompt"));
		OnCfggloBtnGet();
	}
}

void CConfigGlobal::OnBnClickedBtnHorLine()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pIvsGlobalPreview->EnableDrawLine(true);
}
