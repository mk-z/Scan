// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "ConfigDlg.h"
#include "RuleCfgdlg.h"
#include "SenceCfgdlg.h"
#include "ModuleCfgdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	//}}AFX_DATA_INIT
	m_lLogHandle = 0;
	m_nChannelNum = 0;
	m_nSelectChannel = -1;
	m_lRealPlayHandle = 0;
	m_nSelectTab = 0;
	m_pRuleDlg = NULL;
	m_pSceneDlg = NULL;
	m_pModuleDlg = NULL;
	InitializeCriticalSection(&m_csSelectTab);
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_TAB_CONFIG, m_ctlMainTab);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONFIG, OnSelchangeTabConfig)
	ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	InitTabControl();

	return TRUE;
}

void CConfigDlg::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_pModuleDlg)
	{
		if (m_pModuleDlg->GetSafeHwnd())
		{
			m_pModuleDlg->DestroyWindow();
		}
		delete m_pModuleDlg;
	}

	if (m_pRuleDlg)
	{
		if (m_pRuleDlg->GetSafeHwnd())
		{
			m_pRuleDlg->DestroyWindow();
		}
		delete m_pRuleDlg;
	}

	if (m_pSceneDlg)
	{
		if (m_pSceneDlg->GetSafeHwnd())
		{
			m_pSceneDlg->DestroyWindow();
		}
		delete m_pSceneDlg;
	}

	LeaveCriticalSection(&m_csSelectTab);
}

void CConfigDlg::Init(LLONG lLogHandle)
{
	m_lLogHandle = lLogHandle;
}
void CConfigDlg::SetChannelNum(int nChannel)
{
	m_nChannelNum = nChannel;

	char szBuf[16] = {0};
	int nIndex = 0;
	m_cbChannel.ResetContent();
	for (int i = 0; i < m_nChannelNum; i++)
	{
		CString strName = ConvertString("channel") + itoa(i, szBuf, 10);
		nIndex = m_cbChannel.AddString(strName);
		m_cbChannel.SetItemData(nIndex, i);
	}
		m_cbChannel.SetCurSel(0);
}

void CConfigDlg::InitTabControl()
{
	CRect childRect;
	m_ctlMainTab.GetClientRect(&childRect);
	childRect.top += 20;
	childRect.bottom -= 4;
	childRect.left += 4;
	childRect.right -= 4;
	
	m_pSceneDlg = new CSenceCfgdlg;
	if(m_pSceneDlg)
	{
		m_pSceneDlg->Create(IDD_DIALOG_CFG_SCENCE, &m_ctlMainTab);
		m_pSceneDlg->MoveWindow(childRect);
	}
	m_pRuleDlg = new CRuleCfgdlg;
	if (m_pRuleDlg)
	{
		m_pRuleDlg->Create(IDD_DIALOG_CFG_RULE, &m_ctlMainTab);
		m_pRuleDlg->MoveWindow(childRect);
	}
	m_pModuleDlg = new CModuleCfgdlg;
	if (m_pModuleDlg)
	{
		m_pModuleDlg->Create(IDD_DIALOG_CFG_MODULE, &m_ctlMainTab);
		m_pModuleDlg->MoveWindow(childRect);
	}
	
	m_ctlMainTab.InsertItem(0, ConvertString("Scene Configuration"));
	m_ctlMainTab.InsertItem(1, ConvertString("Module Configuration"));
	m_ctlMainTab.InsertItem(2, ConvertString("Rule Configuration"));

	
	m_ctlMainTab.SetCurSel(0);
	DoTab(0);
	m_nSelectTab = 0;
}

void CConfigDlg::DoTab(int nTab)
{
	//Check nTab value is within the threshold
	if(nTab>2)
	{
		nTab=2;
	}
	if(nTab<0)
	{
		nTab=0;
	}
	
	BOOL bTab[3];
	bTab[0]=bTab[1]=bTab[2]=FALSE;
	bTab[nTab]=TRUE;
	
	//Display or hide dialogue box 
	if (m_pSceneDlg)
	{
		SetDlgState(m_pSceneDlg,bTab[0]);
		m_pSceneDlg->SetPlayParam(bTab[0]);
	}
	if (m_pRuleDlg)
	{
		SetDlgState(m_pRuleDlg,bTab[2]);
	}
	if (m_pModuleDlg)
	{
		SetDlgState(m_pModuleDlg,bTab[1]);
		m_pModuleDlg->ShowPreview(1, 1);
	}

}

void CConfigDlg::SetDlgState(CWnd *pWnd, BOOL bShow)
{
	if (pWnd == NULL)
	{
		return;
	}
	
	if(bShow)
	{
		pWnd->ShowWindow(SW_SHOW);
	}
	else
	{
		pWnd->ShowWindow(SW_HIDE);
	}
}

int CConfigDlg:: GetSelectTabPlayPort(void)
{
	int nPort = 0;
	EnterCriticalSection(&m_csSelectTab);
	if (m_nSelectTab == 0)
	{
		nPort = m_pSceneDlg->GetPlayPort();
	}
	else if (m_nSelectTab == 1)
	{
		nPort = m_pModuleDlg->GetPlayPort();
	}
	LeaveCriticalSection(&m_csSelectTab);

	return nPort; 
}

void CConfigDlg::OnSelchangeTabConfig(NMHDR* pNMHDR, LRESULT* pResult) 
{
	EnterCriticalSection(&m_csSelectTab);
	m_nSelectTab = m_ctlMainTab.GetCurSel();
	LeaveCriticalSection(&m_csSelectTab);

	if(m_nSelectTab>=0)
	{
		DoTab(m_nSelectTab);
	}
	
	*pResult = 0;
}

void CConfigDlg::OnButtonSave() 
{
	int nIndex = m_cbChannel.GetCurSel();
	int nChannelID = m_cbChannel.GetItemData(nIndex);

	int nBufLen = 1024 * 32;
	char* pJsonBuf = new char[nBufLen];
	if (pJsonBuf == NULL)
	{
		// 缓冲不足
		MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
		return;
	}
	int nError = 0;
	int nRestart = 0;

	/* save rule info */
	CFG_ANALYSERULES_INFO stRule = {0};
	stRule.nRuleCount = 1;
	stRule.nRuleLen = sizeof(CFG_FACERECOGNITION_INFO) + sizeof(CFG_RULE_INFO);
	stRule.pRuleBuf = new char[stRule.nRuleLen];
	if (stRule.pRuleBuf == NULL)
	{
		// 缓冲不足
		MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
		return;
	}

	CFG_RULE_INFO* pRuleInfo = (CFG_RULE_INFO*)stRule.pRuleBuf;
	pRuleInfo->dwRuleType = EVENT_IVS_FACERECOGNITION;
	pRuleInfo->nRuleSize = sizeof(CFG_FACERECOGNITION_INFO);
	CFG_FACERECOGNITION_INFO* pFaceRecognitionRule = (CFG_FACERECOGNITION_INFO*)(stRule.pRuleBuf + sizeof(CFG_RULE_INFO));
	if (m_pRuleDlg && pFaceRecognitionRule)
	{
		m_pRuleDlg->SaveRuleInfo(pFaceRecognitionRule);
	}

	memset(pJsonBuf, 0, nBufLen);
	BOOL bRet = CLIENT_PacketData(CFG_CMD_ANALYSERULE, &stRule, sizeof(stRule), pJsonBuf, nBufLen);
	if (bRet)
	{
		bRet = CLIENT_SetNewDevConfig(m_lLogHandle, CFG_CMD_ANALYSERULE, nChannelID, pJsonBuf, nBufLen, &nError, &nRestart, 2000);
		if (bRet)
		{
			// 保存成功
			MessageBox(ConvertString("Save rule info success!"),ConvertString("Prompt"));
		}
		else
		{
			// 保存失败
			MessageBox(ConvertString("Save rule info failed!"),ConvertString("Prompt"));
		}
	}
	else
	{
		// 打包失败
		MessageBox(ConvertString("packet rule info failed!"),ConvertString("Prompt"));
	}
	if (stRule.pRuleBuf != NULL)
	{
		delete []stRule.pRuleBuf;
	}

	/* save sence info */
	CFG_ANALYSEGLOBAL_INFO* pSenceInfo = new CFG_ANALYSEGLOBAL_INFO;
	if (pSenceInfo == NULL)
	{
		// 缓冲不足
		MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
		return;
	}
	memset(pSenceInfo, 0, sizeof(CFG_ANALYSEGLOBAL_INFO));
	if (m_pSceneDlg)
	{
		bRet = m_pSceneDlg->SaveSceneInfo(pSenceInfo);
		if (bRet)
		{
			memset(pJsonBuf, 0, nBufLen);
			bRet = CLIENT_PacketData(CFG_CMD_ANALYSEGLOBAL, pSenceInfo, sizeof(CFG_ANALYSEGLOBAL_INFO), pJsonBuf, nBufLen);
			if (bRet)
			{
				bRet = CLIENT_SetNewDevConfig(m_lLogHandle, CFG_CMD_ANALYSEGLOBAL, nChannelID, pJsonBuf, nBufLen, &nError, &nRestart, 2000);
				if (bRet)
				{
					// 保存成功
					MessageBox(ConvertString("Save scene info success!"),ConvertString("Prompt"));
				}
				else
				{
					// 保存失败
					MessageBox(ConvertString("Save scene info failed!"),ConvertString("Prompt"));
				}
			}
			else
			{
				// 打包失败
				MessageBox(ConvertString("packet scene info failed!"),ConvertString("Prompt"));
			}
		}
		else
		{
			// 保存失败
			MessageBox(ConvertString("Save scene info failed!"),ConvertString("Prompt"));
		}

		if (pSenceInfo)
		{
			delete pSenceInfo;
		}
	}
	/* save module info */
	CFG_ANALYSEMODULES_INFO* pModuleInfo = new CFG_ANALYSEMODULES_INFO;
	if (pModuleInfo == NULL)
	{
		// 缓冲不足
		MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
		return;
	}
	memset(pModuleInfo, 0, sizeof(CFG_ANALYSEMODULES_INFO));
	if (m_pModuleDlg)
	{
		m_pModuleDlg->SaveModuleInfo(pModuleInfo, nChannelID);
	}
	
	memset(pJsonBuf, 0, nBufLen);
	bRet = CLIENT_PacketData(CFG_CMD_ANALYSEMODULE, pModuleInfo, sizeof(CFG_ANALYSEMODULES_INFO), pJsonBuf, nBufLen);
	if (bRet)
	{
		bRet = CLIENT_SetNewDevConfig(m_lLogHandle, CFG_CMD_ANALYSEMODULE, nChannelID, pJsonBuf, nBufLen, &nError, &nRestart, 2000);
		if (bRet)
		{
			// 保存成功
			MessageBox(ConvertString("Save module info success!"),ConvertString("Prompt"));
		}
		else
		{
			// 保存失败
			MessageBox(ConvertString("Save module info failed!"),ConvertString("Prompt"));
		}
	}
	else
	{
		// 打包失败
		MessageBox(ConvertString("packet module info failed!"),ConvertString("Prompt"));
	}
	
	if (pModuleInfo)
	{
		delete pModuleInfo;
	}
	
	if (pJsonBuf)
	{
		delete []pJsonBuf;
	}
}

void CConfigDlg::OnButtonRead() 
{
	GetConfigInfo();
}

void CConfigDlg::GetConfigInfo()
{
	int nIndex = m_cbChannel.GetCurSel();
	int nChannelID = m_cbChannel.GetItemData(nIndex);

	int nBufLen = 1024 * 32;
	char* pJsonBuf = new char[nBufLen];
	if (pJsonBuf == NULL)
	{
		// 缓冲不足
		MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
		return;
	}
	int nError = 0;

	/* show rule info */
	memset(pJsonBuf, 0, nBufLen);
	BOOL bRet = CLIENT_GetNewDevConfig(m_lLogHandle, CFG_CMD_ANALYSERULE, nChannelID, pJsonBuf, nBufLen, &nError, 2000);
	if (bRet)
	{
		CFG_ANALYSERULES_INFO stRule = {0};
		stRule.nRuleLen = (sizeof(CFG_FACERECOGNITION_INFO) + sizeof(CFG_RULE_INFO)) *10;
		stRule.pRuleBuf = new char[stRule.nRuleLen];
		if (stRule.pRuleBuf == NULL)
		{
			// 缓冲不足
			MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
			return;
		}
		memset(stRule.pRuleBuf , 0, stRule.nRuleLen);
		bRet = CLIENT_ParseData(CFG_CMD_ANALYSERULE, pJsonBuf, &stRule, sizeof(stRule), NULL);
		if (!bRet)
		{
			// 解析失败
			MessageBox(ConvertString("Parse rule data failed!"),ConvertString("Prompt"));
		}

		int nReadLen = 0;
		for (int i = 0; i < stRule.nRuleCount; i++)
		{
			CFG_RULE_INFO* pRuleInfo = (CFG_RULE_INFO*)(stRule.pRuleBuf + nReadLen);
			nReadLen += sizeof(CFG_RULE_INFO);
			if (pRuleInfo->dwRuleType == EVENT_IVS_FACERECOGNITION)
			{
				CFG_FACERECOGNITION_INFO* pFaceRecognitonInfo = (CFG_FACERECOGNITION_INFO*)(stRule.pRuleBuf + nReadLen);
				if (m_pRuleDlg)
				{
					m_pRuleDlg->ShowRuleInfo(pFaceRecognitonInfo);
				}
				
				break;
			}
			nReadLen += pRuleInfo->nRuleSize;
		}

		if (stRule.pRuleBuf == NULL)
		{
			delete []stRule.pRuleBuf;
		}
	}
	else
	{
		// 获取规则信息失败
		MessageBox(ConvertString("Get rule info failed!"),ConvertString("Prompt"));
	}

	/* save  sence info */
	memset(pJsonBuf, 0, nBufLen);
	nError = 0;
	bRet = CLIENT_GetNewDevConfig(m_lLogHandle, CFG_CMD_ANALYSEGLOBAL, nChannelID, pJsonBuf, nBufLen, &nError, 2000);
	if (bRet)
	{
		CFG_ANALYSEGLOBAL_INFO* pSceneInfo = new CFG_ANALYSEGLOBAL_INFO;
		if (pSceneInfo == NULL)
		{
			// 缓冲不足
			MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
			return;
		}
		memset(pSceneInfo, 0, sizeof(CFG_ANALYSEGLOBAL_INFO));

		bRet = CLIENT_ParseData(CFG_CMD_ANALYSEGLOBAL, pJsonBuf, pSceneInfo, sizeof(CFG_ANALYSEGLOBAL_INFO), NULL);
		if (bRet)
		{
			if (m_pSceneDlg)
			{
				m_pSceneDlg->ShowSceneInfo(pSceneInfo);
			}
		}
		else
		{
			//解析失败
			MessageBox(ConvertString("Parse scene data failed!"),ConvertString("Prompt"));

		}

		if (pSceneInfo)
		{
			delete pSceneInfo;
		}
	}
	else
	{
		// 获取失败
		MessageBox(ConvertString("Get scene info failed!"),ConvertString("Prompt"));
	}

	memset(pJsonBuf, 0, nBufLen);
	nError = 0;
	bRet = CLIENT_GetNewDevConfig(m_lLogHandle, CFG_CMD_ANALYSEMODULE, nChannelID, pJsonBuf, nBufLen, &nError, 2000);
	if (bRet)
	{
		CFG_ANALYSEMODULES_INFO* pModuleInfo = new CFG_ANALYSEMODULES_INFO;
		if (pModuleInfo == NULL)
		{
			// 缓冲不足
			MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
			return;
		}
		memset(pModuleInfo, 0, sizeof(CFG_ANALYSEMODULES_INFO));
		
		bRet = CLIENT_ParseData(CFG_CMD_ANALYSEMODULE, pJsonBuf, pModuleInfo, sizeof(CFG_ANALYSEMODULES_INFO), NULL);
		if (bRet)
		{
			if (m_pModuleDlg)
			{
				m_pModuleDlg->ShowModuleInfo(pModuleInfo, nChannelID);
			}
		}
		else
		{
			//解析失败
			MessageBox(ConvertString("Parse module data failed!"),ConvertString("Prompt"));
			
		}
		
		if (pModuleInfo)
		{
			delete pModuleInfo;
		}
	}
	else
	{
		// 获取失败
		MessageBox(ConvertString("Get module info failed!"),ConvertString("Prompt"));
	}
	if (pJsonBuf)
	{
		delete []pJsonBuf;
	}
}

// 实时监视数据回调函数原形
void __stdcall RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser)
{
	CConfigDlg *pDlg = (CConfigDlg*)dwUser;
	if (pDlg != NULL)
	{
		int nPort = pDlg->GetSelectTabPlayPort();
		g_PlayAPI.PLAY_InputData(nPort, pBuffer, dwBufSize);
	}
}

void CConfigDlg::CloseStream()
{
	if (m_lRealPlayHandle != 0)
	{
		CLIENT_StopRealPlay(m_lRealPlayHandle);
	}
	m_nSelectChannel = -1;
}

void CConfigDlg::OpenChannelStream()
{
	int nIndex = m_cbChannel.GetCurSel();
	int nChannelId = m_cbChannel.GetItemData(nIndex);
	if (m_nSelectChannel == nChannelId && m_lRealPlayHandle != 0)
	{
		return;
	}

	if (m_lRealPlayHandle != 0)
	{
		CLIENT_StopRealPlay(m_lRealPlayHandle);
	}

	m_lRealPlayHandle = CLIENT_RealPlay(m_lLogHandle, nChannelId, 0);
	if (m_lRealPlayHandle )
	{
		CLIENT_SetRealDataCallBack(m_lRealPlayHandle, RealDataCallBack, (LDWORD)this);
	}
	else
	{
		// 打开视频失败
		MessageBox(ConvertString("open stream failed!"),ConvertString("Prompt"));
	}

	m_nSelectChannel = nChannelId;
}

void CConfigDlg::OnSelchangeComboChannel() 
{
	OpenChannelStream();
}
