

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "ConfigAtmScene.h"
#include "Video Analyse ConfigurationDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigAtmScene dialog


CConfigAtmScene::CConfigAtmScene(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigAtmScene::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigAtmScene)
	//}}AFX_DATA_INIT

	m_lLoginId = 0;
	m_nChannelCount = 0;
	m_nCurrentChannel = -1;

	for (int i=0;i<MAX_CHANNEL_NUM; i++)
	{
		m_stuAnalysSceneInfo[i] = new CFG_ANALYSEGLOBAL_INFO;
		memset((void*)m_stuAnalysSceneInfo[i],0x0,sizeof(CFG_ANALYSEGLOBAL_INFO));
	}
}


void CConfigAtmScene::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigAtmScene)
	DDX_Control(pDX, IDC_COMBO_CHANNEL_T, m_cbChannel);
	DDX_Control(pDX, IDC_COMBO_SCENE_T, m_cbScene);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigAtmScene, CDialog)
	//{{AFX_MSG_MAP(CConfigAtmScene)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_T, OnButtonSaveT)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_T, OnButtonRefreshT)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_T, OnSelchangeComboChannelT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigAtmScene message handlers

void CConfigAtmScene::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CConfigAtmScene::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CConfigAtmScene::Init(int nChannelCount)
{
 	Clear();
	
	m_nChannelCount = nChannelCount;
	
	int nIndex = 0;
	char szBuffer[32] = {0};
	m_cbChannel.ResetContent();
	for(int i = 0; i < m_nChannelCount; i++)
	{
		CString str;
		str = ConvertString("channel") + itoa(i, szBuffer, 10);
		nIndex = m_cbChannel.AddString(str);
		m_cbChannel.SetItemData(nIndex, i);
	}
	
	m_cbChannel.SetCurSel(0);
	m_nCurrentChannel = 0;

 	// get supported object type
 	GetCannelObjTypes();
 	// show scene info
 	ShowTrafficSceneInfo();
}

void CConfigAtmScene::OnButtonSaveT() 
{
	// TODO: Add your control notification handler code here
	if(-1 != m_cbChannel.GetCurSel())
	{
		BOOL bRet = SaveChannelScene(m_nCurrentChannel);
		if (!bRet)
		{
			return;
		}
		//Call father window to save data
		((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->SetTrafficScene(m_nCurrentChannel, 
			*m_stuAnalysSceneInfo[m_nCurrentChannel]);
	}
	else
	{
		MessageBox(ConvertString("please select the channel!"), ConvertString("Prompt"));
	}
}

void CConfigAtmScene::OnButtonRefreshT() 
{
	// TODO: Add your control notification handler code here
	ShowTrafficSceneInfo();
}

BOOL CConfigAtmScene::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);
	
	//memset(m_stuAnalysSceneInfo, 0, sizeof(CFG_ANALYSEGLOBAL_INFO) * MAX_CHANNEL_NUM);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CConfigAtmScene::Clear()
{
	UpdateData(FALSE);
	
	m_cbScene.ResetContent();
	m_cbChannel.ResetContent();
}

void CConfigAtmScene::GetCannelObjTypes()
{
	int nChannelId = m_cbChannel.GetCurSel();
	CFG_CAP_ANALYSE_INFO* pDeviceCap = NULL;
	if (-1 == nChannelId)
	{
		MessageBox(ConvertString("Please check one channel!"),ConvertString("Prompt"));
		return;
	}
	
	pDeviceCap = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetChannelCapInfo(nChannelId);
	
	if (pDeviceCap != NULL)
	{
		m_nSupportedSceneNum = pDeviceCap->nSupportedSceneNum;
		memcpy(m_gSceneName, pDeviceCap->szSceneName, MAX_SCENE_LIST_SIZE * MAX_NAME_LEN * sizeof(char));
	}
	
	m_cbScene.ResetContent();
	for(int i = 0; i < m_nSupportedSceneNum; i++)
	{
		nChannelId = m_cbScene.AddString(ConvertString(m_gSceneName[i]));
		m_cbScene.SetItemData(nChannelId, i);
	}
	
	m_lLoginId = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetLoginID();
}

void CConfigAtmScene::ShowChannelScene(int nChannelId)
{
	// get info
	BOOL bSuccess = ((CVideoAnalyseConfigurationDlg*)AfxGetMainWnd())->GetTrafficScene(nChannelId, 
		*m_stuAnalysSceneInfo[nChannelId]);
	if (!bSuccess)
	{
		return;
	}
	
	// show info
	int i;
	for(i = 0; i < m_nSupportedSceneNum; i++)
	{
		if (strcmp(m_stuAnalysSceneInfo[nChannelId]->szSceneType, m_gSceneName[i]) == 0)
		{
			m_cbScene.SetCurSel(i);
			break;
		}
	}
	
	nChannelId = 0;
	
	UpdateData(FALSE);
}
void CConfigAtmScene::ShowTrafficSceneInfo()
{	
	//Call father window to read data 
	ShowChannelScene(m_nCurrentChannel);
}



BOOL CConfigAtmScene::SaveChannelScene(int nChannelId)
{
	BOOL bRet = UpdateData(TRUE);
	if (!bRet)
	{
		return FALSE;
	}
	// save info
	memset(m_stuAnalysSceneInfo[nChannelId]->szSceneType, 0, MAX_NAME_LEN* sizeof(char));
	nChannelId = m_cbScene.GetCurSel();
	if (nChannelId != -1)
	{
		memcpy(m_stuAnalysSceneInfo[nChannelId]->szSceneType, m_gSceneName[nChannelId], MAX_NAME_LEN* sizeof(char));
	}
		
	return TRUE;
}

void CConfigAtmScene::OnSelchangeComboChannelT() 
{
	// TODO: Add your control notification handler code here
	// save
	SaveChannelScene(m_nCurrentChannel);
	
	m_nCurrentChannel = m_cbChannel.GetCurSel();
	
	// show
	GetCannelObjTypes();
	ShowChannelScene(m_nCurrentChannel);
}
