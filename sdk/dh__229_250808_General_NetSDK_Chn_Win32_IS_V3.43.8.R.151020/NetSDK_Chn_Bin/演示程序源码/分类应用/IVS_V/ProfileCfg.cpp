// Profile.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "ProfileCfg.h"
#include "ProfileInfo1.h"
#include "IVS_VDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileCfg dialog


CProfileCfg::CProfileCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CProfileCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProfileCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pProfileInfo1 = new CProfileInfo1(this);

	m_pstProfile = NULL;

	memset(&m_stTreeData, 0x0, sizeof(STtreeData) );
	m_stTreeData.strName = ConvertString("Detection");

	m_bSavePage = true;
	m_hSelectTreeItem = 0;
}

CProfileCfg::~CProfileCfg()
{
	SAFE_DELETE(m_pProfileInfo1);
	UnInitProfile(&m_pstProfile);
	
	m_TreeProfile.DeleteAllItems();
	m_TreeProfile.DeleteAllData(&m_stTreeData.pChild);
	m_TreeProfile.DeleteAllData(&m_stTreeData.pBrother);
}

void CProfileCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProfileCfg)
	DDX_Control(pDX, IDC_TREE_PROFILE, m_TreeProfile);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProfileCfg, CDialog)
	//{{AFX_MSG_MAP(CProfileCfg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROFILE, OnTvnSelchangedTreeProject)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGetConfig)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSetConfig)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAddProfile)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDeleteProfile)
	ON_BN_CLICKED(IDC_BTN_SAVEPAGE,OnBtnSavePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileCfg message handlers

STtreeData* CProfileCfg::InitTreeLink(char *szName, DWORD dwProfile, BOOL bFirstChild /*= FALSE*/)
{
	char* szProfileName[] = {NET_DIAGNOSIS_DITHER,
		NET_DIAGNOSIS_STRIATION,
		NET_DIAGNOSIS_LOSS,
		NET_DIAGNOSIS_COVER,
		NET_DIAGNOSIS_FROZEN,

		NET_DIAGNOSIS_BRIGHTNESS,		
		NET_DIAGNOSIS_CONTRAST,
		NET_DIAGNOSIS_UNBALANCE,
		NET_DIAGNOSIS_NOISE,
		NET_DIAGNOSIS_BLUR,

		NET_DIAGNOSIS_SCENECHANGE
	};

	DWORD dwMaskControl[] = { CProfileInfo1::EN_MASK_CONTROLS_NAME,
		VideoDitherDetection,
		VideoStriationDetection,
		VideoLossDetection,
		VideoCoverDetection,
		VideoFrozenDetection,

		VideoBrightnessDetection,
		VideoContrastDetection,
		VideoUnbalanceDetection,
		VideoNoiseDetection,
		VideoBlurDetection,

		VideoSceneChangeDetection,
	};


	STtreeData* pRoot = NULL;
	if (bFirstChild)
	{
		pRoot = m_TreeProfile.AddNodeNext(m_stTreeData, szName, m_pProfileInfo1, dwMaskControl[0], dwProfile, 0, 0, FALSE, CVirtTree::EN_NODE_TYPE_CHILD);
	}
	else
	{
		pRoot = m_stTreeData.pChild;
		while (pRoot->pBrother) pRoot = pRoot->pBrother;
		pRoot = m_TreeProfile.AddNodeNext(*pRoot, szName, m_pProfileInfo1, dwMaskControl[0], dwProfile, 0, 0, FALSE, CVirtTree::EN_NODE_TYPE_BROTHER);
	}

	STtreeData* pDetection = pRoot;
	for (int i=0; i<sizeof(szProfileName)/sizeof(szProfileName[0]); i++)
	{
		CVirtTree::EN_NODE_TYPE enNodeType = CVirtTree::EN_NODE_TYPE_CHILD;
		if (0 == i)
		{
			enNodeType = CVirtTree::EN_NODE_TYPE_CHILD;
		}
		else
		{
			enNodeType = CVirtTree::EN_NODE_TYPE_BROTHER;
		}
		pDetection = m_TreeProfile.AddNodeNext(*pDetection, ConvertString(szProfileName[i]).GetBuffer(0), m_pProfileInfo1, dwMaskControl[i+1], dwProfile, 0, 0, FALSE, enNodeType);
	}

	if (bFirstChild)
	{
		pRoot = &m_stTreeData;
	}
	return pRoot;
}

void CProfileCfg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CProfileCfg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL CProfileCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (NULL != m_pProfileInfo1)
	{
		m_pProfileInfo1->Create(IDD_DLG_PROFILE_INFO1,this);
		CRect rc;
		GetDlgItem(IDC_CONFIG_AREA)->GetClientRect(&rc);
		rc.DeflateRect(20,40);
		GetDlgItem(IDC_CONFIG_AREA)->ClientToScreen(&rc);
		m_pProfileInfo1->MoveWindow(&rc);
		m_pProfileInfo1->EnableControls(m_stTreeData.dwMaskControls);
		m_pProfileInfo1->ShowWindow(SW_SHOW);
	}

	g_SetWndStaticText(this);

	return TRUE;
}

void CProfileCfg::OnTvnSelchangedTreeProject(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if (0 == hItem)
	{
		return;
	}
	if (!m_bSavePage)
	{
		OnBtnSavePage();
	}
	m_bSavePage = false;

#ifdef _DEBUG
	char szTmp[MAX_PATH]={0};
	sprintf(szTmp, "m_bSavePage: %d", m_bSavePage);
	OutputDebugString(szTmp);
#endif // _DEBUG
	
	// 保存此树当前选中项
	m_hSelectTreeItem = hItem;
	m_TreeProfile.Select(m_hSelectTreeItem, TVGN_CARET);
	m_TreeProfile.Select(m_hSelectTreeItem, TVGN_DROPHILITE);

	UpdateData(true);
	m_pProfileInfo1->ShowWindow(SW_HIDE);
	STtreeData* pData = reinterpret_cast<STtreeData*>(m_TreeProfile.GetItemData(hItem));
	if (NULL != pData && NULL != pData->pData && NULL != pData->dwProfile)
	{
		CProfileInfo1* pWnd = reinterpret_cast<CProfileInfo1*>(pData->pData);
		pWnd->EnableControls(pData->dwMaskControls);
		CString s = m_TreeProfile.GetItemText(hItem);
		if (pData->dwMaskControls == CProfileInfo1::EN_MASK_CONTROLS_NAME)
		{
			pWnd->UpdateDataToDlg(s.GetBuffer(0), NULL);
		}
		else if (pData->dwMaskControls > CProfileInfo1::EN_MASK_CONTROLS_NAME)
		{
			HTREEITEM hParent = m_TreeProfile.GetParentItem(hItem);
			CString sParent = m_TreeProfile.GetItemText(hParent);
			CFG_VIDEO_DIAGNOSIS_PROFILE* pProfileInfo= reinterpret_cast<CFG_VIDEO_DIAGNOSIS_PROFILE*>(pData->dwProfile);
			if (0 == sParent.Compare(pProfileInfo->szName))
			{
				pWnd->UpdateDataToDlg(sParent.GetBuffer(0), NULL);
				pWnd->UpdateDataToDlg(s.GetBuffer(0), pProfileInfo);
			}
			else
			{
				CString s;
				s.Format(ConvertString("OnTvnSelchangedTreeProject error, ['%s'] of tree item don't same as Memory data ['%s'] !"),
					sParent.GetBuffer(0), pProfileInfo->szName);
				OutputDebugString(s);
				AfxMessageBox(s);
			}
		}

		pWnd->ShowWindow(SW_SHOW);
	}	
}

void CProfileCfg::UnInitProfile(CFG_VIDEODIAGNOSIS_PROFILE ** pstProfile)
{
	if (NULL != pstProfile && NULL != (*pstProfile))
	{
		for (int i=0; i<(*pstProfile)->nTotalProfileNum; i++)
		{
			CFG_VIDEO_DIAGNOSIS_PROFILE & p = (*pstProfile)->pstProfiles[i];
			SAFE_DELETE(p.pstBlur);
			SAFE_DELETE(p.pstBrightness);
			SAFE_DELETE(p.pstContrast);
			SAFE_DELETE(p.pstCover);
			SAFE_DELETE(p.pstDither);
			
			SAFE_DELETE(p.pstFrozen);
			SAFE_DELETE(p.pstLoss);
			SAFE_DELETE(p.pstNoise);
			SAFE_DELETE(p.pstSceneChange);
			SAFE_DELETE(p.pstStriation);
			
			SAFE_DELETE(p.pstUnbalance);
		}
		SAFE_DELETE_A((*pstProfile)->pstProfiles);
		SAFE_DELETE((*pstProfile));
	}
}

void CProfileCfg::InitOneProfile(CFG_VIDEO_DIAGNOSIS_PROFILE& p)
{
	p.pstBlur = new CFG_VIDEO_BLUR_DETECTION;
	memset(p.pstBlur, 0x0, sizeof(CFG_VIDEO_BLUR_DETECTION));
	
	p.pstBrightness = new CFG_VIDEO_BRIGHTNESS_DETECTION;
	memset(p.pstBrightness, 0x0, sizeof(*p.pstBrightness));
	
	p.pstContrast = new CFG_VIDEO_CONTRAST_DETECTION;
	memset(p.pstContrast, 0x0, sizeof(*p.pstContrast));
	
	p.pstCover = new CFG_VIDEO_COVER_DETECTION;
	memset(p.pstCover, 0x0, sizeof(*p.pstCover));
	
	p.pstDither = new CFG_VIDEO_DITHER_DETECTION;
	memset(p.pstDither, 0x0, sizeof(*p.pstDither));
	
	p.pstFrozen = new CFG_VIDEO_FROZEN_DETECTION;
	memset(p.pstFrozen, 0x0, sizeof(*p.pstFrozen));
	
	p.pstLoss = new CFG_VIDEO_LOSS_DETECTION;
	memset(p.pstLoss, 0x0, sizeof(*p.pstLoss));
	
	p.pstNoise = new CFG_VIDEO_NOISE_DETECTION;
	memset(p.pstNoise, 0x0, sizeof(*p.pstNoise));
	
	p.pstSceneChange = new CFG_VIDEO_SCENECHANGE_DETECTION;
	memset(p.pstSceneChange, 0x0, sizeof(*p.pstSceneChange));
	
	p.pstStriation = new CFG_VIDEO_STRIATION_DETECTION;
	memset(p.pstStriation, 0x0, sizeof(*p.pstStriation));
	
	p.pstUnbalance = new CFG_VIDEO_UNBALANCE_DETECTION;
	memset(p.pstUnbalance, 0x0, sizeof(*p.pstUnbalance));
	
	memset(p.szName,0x0, sizeof(p.szName));
}
void CProfileCfg::InitProfileCfg(CFG_VIDEODIAGNOSIS_PROFILE** pProfile)
{
	UnInitProfile(pProfile);

	// 重新分配
	(*pProfile) = new CFG_VIDEODIAGNOSIS_PROFILE;
	memset((*pProfile), 0x0, sizeof((*pProfile)));
	
	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	(*pProfile)->nTotalProfileNum = pParent->GetMaxProfiles();
	(*pProfile)->pstProfiles = new CFG_VIDEO_DIAGNOSIS_PROFILE[(*pProfile)->nTotalProfileNum];
	memset((*pProfile)->pstProfiles, 0x0, sizeof((*pProfile)->pstProfiles));
	
	for (int i=0; i<(*pProfile)->nTotalProfileNum; i++)
	{
		InitOneProfile((*pProfile)->pstProfiles[i]);
	}
}
void CProfileCfg::OnBtnGetConfig()
{
	CString sDebugMsg;

	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}

	int nErr = 0;
	int nLenOut = sizeof(CFG_VIDEODIAGNOSIS_PROFILE);

	InitProfileCfg(&m_pstProfile);

	int nJsonLen = 1024*1024;
	char * szJson = new char[nJsonLen+1];
	memset(szJson, 0x0, nJsonLen+1);
	char szCmd[] = CFG_CMD_VIDEODIAGNOSIS_PROFILE;

	BOOL bSuccess = CLIENT_GetNewDevConfig(lLoginID, szCmd, 0, szJson, nJsonLen, &nErr, 3000);
	sDebugMsg.Format(ConvertString("(0x%x) CLIENT_GetNewDevConfig %s return %s LastError:0x%x !"),
		lLoginID, szCmd, bSuccess == TRUE ? ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError());
	OutputDebugString(sDebugMsg);
	if (bSuccess)
	{
		int nRet = 0;
		BOOL bRet = CLIENT_ParseData(szCmd,szJson,m_pstProfile,nLenOut,&nRet);
		sDebugMsg.Format(ConvertString("CLIENT_ParseData %s return %s !"),szCmd,bRet==TRUE? ConvertString("successfully"):ConvertString("failure"));
		OutputDebugString(sDebugMsg);
		if (bRet)
		{
			// 刷新数据到界面上
			UpdateDataToDlg();
		}
		else
		{
			AfxMessageBox(sDebugMsg);
		}
	}
	else
	{
		AfxMessageBox(sDebugMsg);
	}
	SAFE_DELETE_A(szJson);
	m_TreeProfile.ResetTree(m_stTreeData);

	m_hSelectTreeItem = 0;
}

void CProfileCfg::OnBtnSetConfig()
{
	if (!m_bSavePage)
	{
		OnBtnSavePage();
	}
#ifdef _DEBUG
	char szTmp[MAX_PATH]={0};
	sprintf(szTmp, "m_bSavePage: %d", m_bSavePage);
	OutputDebugString(szTmp);
#endif // _DEBUG
	CString sDebugMsg;

	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}

	// 获取界面数据
	//GetDlgData();
	
	// 封装并设置数据
	void * pStInfo = NULL;
	CopyAllProfile((CFG_VIDEODIAGNOSIS_PROFILE**)&pStInfo, m_pstProfile);
	
	char szCmd[] = CFG_CMD_VIDEODIAGNOSIS_PROFILE;
	int nJsonLen = 1024*1024;
	char * szJson = new char[nJsonLen+1];
	memset(szJson, 0x0, nJsonLen+1);

	BOOL bRet = CLIENT_PacketData(szCmd, pStInfo, sizeof(CFG_VIDEODIAGNOSIS_PROFILE), szJson, nJsonLen);
	UnInitProfile((CFG_VIDEODIAGNOSIS_PROFILE **)&pStInfo);

	sDebugMsg.Format(ConvertString("(0x%x) CLIENT_PacketData %s return %s !"),lLoginID, szCmd, bRet == TRUE ? ConvertString("successfully"):ConvertString("failure"));
	OutputDebugString(sDebugMsg);
	if (bRet == TRUE)
	{
		int nErr = 0;
		int nrestart = 0;
		BOOL bSuccess = CLIENT_SetNewDevConfig(lLoginID, szCmd, 0, szJson, nJsonLen, &nErr, &nrestart, 3000);		
		sDebugMsg.Format(ConvertString("(0x%x) CLIENT_SetNewDevConfig %s return %s LastError:0x%x !"),
			lLoginID, szCmd, bSuccess == TRUE ? ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError());
		OutputDebugString(sDebugMsg);
		if (bSuccess == TRUE)
		{
		}
		else
			AfxMessageBox(sDebugMsg);;
	}
	else
		AfxMessageBox(sDebugMsg);;
}
void CProfileCfg::CopyAllProfile(CFG_VIDEODIAGNOSIS_PROFILE**pDest, CFG_VIDEODIAGNOSIS_PROFILE* pSrc)
{
	if (NULL == pDest)
	{
		return;
	}

	InitProfileCfg(pDest);

	if (NULL != pSrc)
	{
		(*pDest)->nTotalProfileNum = pSrc->nTotalProfileNum;
		int j = 0;
		for (int i=0; i<pSrc->nTotalProfileNum; i++)
		{
			CFG_VIDEO_DIAGNOSIS_PROFILE& stProfile = pSrc->pstProfiles[i];
			if (0 != strlen(stProfile.szName))
			{
				CopyProfile(stProfile, (*pDest)->pstProfiles[j++]);
			}
		}
	}
}
void CProfileCfg::GetOneProfileData(CFG_VIDEO_DIAGNOSIS_PROFILE* pInfo, HTREEITEM hDetect)
{
	if (NULL == pInfo || 0 == hDetect)
	{
		return;
	}

	CString sName = m_TreeProfile.GetItemText(hDetect);
	int nNameLen = __min(sizeof(pInfo->szName), sName.GetLength());
	strncpy(pInfo->szName, sName.GetBuffer(0), nNameLen);

	HTREEITEM hItem = m_TreeProfile.GetChildItem(hDetect);
	while(0 != hItem)
	{
		CString s = m_TreeProfile.GetItemText(hItem);
		
		CProfileInfo1* pWnd = NULL;
		STtreeData* pData = reinterpret_cast<STtreeData*>(m_TreeProfile.GetItemData(hItem));
		if (NULL != pData && NULL != pData->pData)
		{
			pWnd = reinterpret_cast<CProfileInfo1*>(pData->pData);
			pWnd->GetDlgData(s.GetBuffer(0), pInfo);
		}

		hItem = m_TreeProfile.GetNextSiblingItem(hItem);
	}
}

void CProfileCfg::GetDlgData()
{
	HTREEITEM hRoot= m_TreeProfile.GetRootItem();
	HTREEITEM hDetect = m_TreeProfile.GetChildItem(hRoot);
	for (int i=0; i<m_pstProfile->nTotalProfileNum && hDetect; i++)
	{
		CFG_VIDEO_DIAGNOSIS_PROFILE* pInfo= &m_pstProfile->pstProfiles[i];

		GetOneProfileData(pInfo, hDetect);

		hDetect = m_TreeProfile.GetNextSiblingItem(hDetect);
	}

}

void CProfileCfg::UpdateDataToDlg()
{
	// 删除树结构
	m_TreeProfile.DeleteAllItems();
	m_TreeProfile.DeleteAllData(&m_stTreeData.pChild);
	m_TreeProfile.DeleteAllData(&m_stTreeData.pBrother);

	// 重建树结构
	for (int i=0; i<m_pstProfile->nReturnProfileNum && NULL != m_pstProfile->pstProfiles; i++)
	{
		CFG_VIDEO_DIAGNOSIS_PROFILE &st = m_pstProfile->pstProfiles[i];
		if (0 == i)
		{
			InitTreeLink(st.szName, (DWORD)&st, TRUE);
		}
		else
		{
			InitTreeLink(st.szName, (DWORD)&st);
		}
	}
}

void CProfileCfg::GetData()
{
	OnBtnGetConfig();
}

void CProfileCfg::OnBtnAddProfile()
{
	if (NULL == m_pstProfile)
		return;
	
	if (m_pstProfile->nReturnProfileNum >= m_pstProfile->nTotalProfileNum
		|| 0 == m_pstProfile->nTotalProfileNum)
	{
		char szDebug[MAX_PATH] = {0};
		sprintf(szDebug, ConvertString("The count of profile form is already maximized !"));
		OutputDebugString(szDebug);
		AfxMessageBox(szDebug);;
		return;
	}

	STtreeData* pData = NULL;
	HTREEITEM hRoot= m_TreeProfile.GetRootItem();
	if (0 == hRoot)
	{
		m_pstProfile->nReturnProfileNum++;
		memcpy(m_pstProfile->pstProfiles[0].szName, ConvertString("ProfileName_0"), sizeof(m_pstProfile->pstProfiles[0].szName));
		pData = InitTreeLink(m_pstProfile->pstProfiles[0].szName, (DWORD)&m_pstProfile->pstProfiles[0], TRUE);
	}
	else
	{
		HTREEITEM hItem = hRoot;
		HTREEITEM hDetect = m_TreeProfile.GetChildItem(hRoot);
		while(0 != hDetect)
		{
			hItem = hDetect;
			hDetect = m_TreeProfile.GetNextSiblingItem(hDetect);
		}

		CFG_VIDEO_DIAGNOSIS_PROFILE* pstProfile = NULL;
		for (int i=0; i<m_pstProfile->nTotalProfileNum; i++)
		{
			if (0 == strlen(m_pstProfile->pstProfiles[i].szName))
			{
				pstProfile = &m_pstProfile->pstProfiles[i];
				break;
			}
		}

		if (NULL != pstProfile)
		{
			sprintf(pstProfile->szName, ConvertString("ProfileName_%d"),hItem);
			m_pstProfile->nReturnProfileNum++;
			pData = InitTreeLink(pstProfile->szName, (DWORD)pstProfile);
		}
	}

	m_TreeProfile.AddProfile(pData);
}

void CProfileCfg::CopyProfile(CFG_VIDEO_DIAGNOSIS_PROFILE & stFrom, CFG_VIDEO_DIAGNOSIS_PROFILE& stDest)
{
	memcpy(stDest.szName, stFrom.szName, sizeof(stDest.szName));
	*stDest.pstDither = *stFrom.pstDither;
	*stDest.pstStriation = *stFrom.pstStriation;
	*stDest.pstLoss = *stFrom.pstLoss;
	*stDest.pstCover = *stFrom.pstCover;
	*stDest.pstFrozen = *stFrom.pstFrozen;

	*stDest.pstBrightness = *stFrom.pstBrightness;
	*stDest.pstContrast = *stFrom.pstContrast;
	*stDest.pstUnbalance = *stFrom.pstUnbalance;
	*stDest.pstNoise = *stFrom.pstNoise;
	*stDest.pstBlur = *stFrom.pstBlur;

	*stDest.pstSceneChange = *stFrom.pstSceneChange;
}
void CProfileCfg::OnBtnDeleteProfile()
{
	HTREEITEM hSelect = m_TreeProfile.GetSelectedItem();
	HTREEITEM hParent = m_TreeProfile.GetParentItem(hSelect);
	if (0 != hParent)
	{
		if (hParent != m_TreeProfile.GetRootItem())
		{
			hSelect = hParent;
		}

		STtreeData* pData = reinterpret_cast<STtreeData*>(m_TreeProfile.GetItemData(hSelect));
		if (NULL == pData || NULL == pData->pData || NULL == pData->dwProfile)
		{
			return;
		}

		CFG_VIDEO_DIAGNOSIS_PROFILE* pProfileInfo= reinterpret_cast<CFG_VIDEO_DIAGNOSIS_PROFILE*>(pData->dwProfile);
		//memset(pProfileInfo->szName, 0x0, sizeof(pProfileInfo->szName));
		InitOneProfile(*pProfileInfo);

		m_pstProfile->nReturnProfileNum--;

		m_TreeProfile.DeleteItem(hSelect);

	}
}

void CProfileCfg::OnBtnSavePage()
{
	if (true == m_bSavePage)
	{
		return;
	}
	m_bSavePage = true;

	if (NULL == m_pstProfile)
	{
		InitProfileCfg(&m_pstProfile);
	}
#ifdef _DEBUG
	char szTmp[MAX_PATH]={0};
	sprintf(szTmp, "m_bSavePage: %d", m_bSavePage);
	OutputDebugString(szTmp);
#endif // _DEBUG
	HTREEITEM hSelect = m_hSelectTreeItem;
	HTREEITEM hParent = m_TreeProfile.GetParentItem(hSelect);
	
	UpdateData(FALSE);
	// profile name
	if ( hParent == m_TreeProfile.GetRootItem() 
		&& TRUE == m_TreeProfile.ItemHasChildren(hSelect))
	{
		STtreeData* pData = reinterpret_cast<STtreeData*>(m_TreeProfile.GetItemData(hSelect));
		if (NULL != pData && NULL != pData->pData && NULL != pData->dwProfile)
		{
			CFG_VIDEO_DIAGNOSIS_PROFILE* pProfileInfo= reinterpret_cast<CFG_VIDEO_DIAGNOSIS_PROFILE*>(pData->dwProfile);
			CProfileInfo1* pWnd = reinterpret_cast<CProfileInfo1*>(pData->pData);
			
			char szName[MAX_PATH] = {0};
			pWnd->GetDlgItemText(IDC_EDIT_PROFILE_NAME, szName, sizeof(szName));
			memcpy(pProfileInfo->szName, szName, sizeof(pProfileInfo->szName));
			m_TreeProfile.SetItemText(hSelect,szName);
		}
	}
	else if (hParent != m_TreeProfile.GetRootItem()
		&& FALSE == m_TreeProfile.ItemHasChildren(hSelect))
	{
		STtreeData* pData = reinterpret_cast<STtreeData*>(m_TreeProfile.GetItemData(hSelect));
		if (NULL != pData && NULL != pData->pData && NULL != pData->dwProfile)
		{
			CFG_VIDEO_DIAGNOSIS_PROFILE* pProfileInfo= reinterpret_cast<CFG_VIDEO_DIAGNOSIS_PROFILE*>(pData->dwProfile);
			CProfileInfo1* pWnd = reinterpret_cast<CProfileInfo1*>(pData->pData);
			char szName[MAX_PATH] = {0};
			pWnd->GetDlgItemText(IDC_EDIT_PROFILE_NAME, szName, sizeof(szName));
			if (0 == _stricmp(pProfileInfo->szName, szName))
			{
				CString stype = m_TreeProfile.GetItemText(hSelect);
				pWnd->GetDlgData(stype.GetBuffer(0), pProfileInfo);
			}
			else
			{
				CString s;
				s.Format(ConvertString("save page data error, Profile name ['%s'] of tree item don't same as Memory data ['%s'] !"),
					szName, pProfileInfo->szName);
				OutputDebugString(s);
				AfxMessageBox(s);
			}
		}
	}

	UpdateData(TRUE);

}
