// SenceCfgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "SenceCfgdlg.h"
#include "IvsSceneDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSenceCfgdlg dialog


CSenceCfgdlg::CSenceCfgdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSenceCfgdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSenceCfgdlg)
	m_dbCameraHight = 0;
	m_nFaceAngleDown = 0;
	m_nFaceAngleLeft = 0;
	m_nFaceAngleRight = 0;
	m_nFaceAngleUp = 0;
	m_strMaindirection1 = _T("");
	m_strMaindirection2 = _T("");
	//}}AFX_DATA_INIT
	m_nPort = 1;
	m_pIvsSceneDraw = NULL;
}

void CSenceCfgdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSenceCfgdlg)
	DDX_Text(pDX, IDC_EDIT_CAMERAHEIGHT, m_dbCameraHight);
	DDV_MinMaxDouble(pDX, m_dbCameraHight, 0., 30000.);
	DDX_Text(pDX, IDC_EDIT_FACEANGLE_DOWN, m_nFaceAngleDown);
	DDX_Text(pDX, IDC_EDIT_FACEANGLE_LEFT, m_nFaceAngleLeft);
	DDX_Text(pDX, IDC_EDIT_FACEANGLE_RIGHT, m_nFaceAngleRight);
	DDX_Text(pDX, IDC_EDIT_FACEANGLEUP, m_nFaceAngleUp);
	DDX_Text(pDX, IDC_EDIT_MAINDIR_1, m_strMaindirection1);
	DDX_Text(pDX, IDC_EDIT_MAINDIR_2, m_strMaindirection2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSenceCfgdlg, CDialog)
	//{{AFX_MSG_MAP(CSenceCfgdlg)
	ON_MESSAGE(WM_ZONEDONE, OnZoneDone)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, OnButtonDraw)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSenceCfgdlg message handlers

BOOL CSenceCfgdlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	BOOL bOpenRet = g_PlayAPI.PLAY_OpenStream(m_nPort, 0, 0, 1024 * 900);
	if (!bOpenRet)
	{
		MessageBox(ConvertString("PLAY_OpenStream failed!"), ConvertString("Prompt"));
	}

	m_pIvsSceneDraw = new CIvsSceneDraw;
	if (m_pIvsSceneDraw == NULL)
	{
		MessageBox(ConvertString("system memory not enough!"),ConvertString("Prompt"));
	}
	CRect rt;
	GetDlgItem(IDC_STATIC_SCENEVIEW)->GetWindowRect(&rt);
	ScreenToClient(&rt);
	m_pIvsSceneDraw->Create(NULL,
								NULL,
								WS_CHILD,
								CRect(0, 0, 0, 0),
								this,
								5000);
	m_pIvsSceneDraw->MoveWindow(&rt);
	m_pIvsSceneDraw->ShowWindow(SW_SHOW);

	return TRUE;
}

void CSenceCfgdlg::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_pIvsSceneDraw)
	{
		if (m_pIvsSceneDraw->GetSafeHwnd())
		{
			m_pIvsSceneDraw->DestroyWindow();
		}
		delete m_pIvsSceneDraw;
	}

	g_PlayAPI.PLAY_Stop(m_nPort);
	g_PlayAPI.PLAY_CloseStream(m_nPort);
}

void CSenceCfgdlg::SetPlayParam(BOOL bStart)
{
	if (!bStart)
	{
		g_PlayAPI.PLAY_Stop(m_nPort);
	}
	else if (m_pIvsSceneDraw)
	{
		HWND hWnd = m_pIvsSceneDraw->GetSafeHwnd();
		BOOL bRet = g_PlayAPI.PLAY_RigisterDrawFun(m_nPort, 
			CIvsSceneDraw::drawIvsSceneCfgProc, 
			(DWORD)m_pIvsSceneDraw);
		if (!bRet)
		{
			MessageBox(ConvertString("PLAY_RigisterDrawFun failed!"), ConvertString("Prompt"));
		}
		//Begin play 
		BOOL bPlayRet = g_PlayAPI.PLAY_Play(m_nPort, hWnd);
	}
}

void CSenceCfgdlg::OnButtonDraw() 
{
	m_pIvsSceneDraw->setMainDirection(NULL, TRUE);
	m_pIvsSceneDraw->beginDraw(true);
}

void CSenceCfgdlg::OnButtonDelete() 
{
	m_pIvsSceneDraw->setMainDirection(NULL, TRUE);
}

void CSenceCfgdlg::ShowSceneInfo(CFG_ANALYSEGLOBAL_INFO* pSenceInfo)
{
	if (pSenceInfo == NULL)
	{
		return;
	}

	if (pSenceInfo->bFaceRecognition)
	{
		m_dbCameraHight = pSenceInfo->stuFaceRecognitionScene.dbCameraHeight;
		m_nFaceAngleDown = pSenceInfo->stuFaceRecognitionScene.byFaceAngleDown;
		m_nFaceAngleLeft = pSenceInfo->stuFaceRecognitionScene.byFaceAngleLeft;
		m_nFaceAngleUp = pSenceInfo->stuFaceRecognitionScene.byFaceAngleUp;
		m_nFaceAngleRight = pSenceInfo->stuFaceRecognitionScene.byFaceAngleRight;
		char szTempBuf[64] = {0};
		sprintf(szTempBuf, "X%d, Y%d", pSenceInfo->stuFaceRecognitionScene.stuMainDirection[0].nX, pSenceInfo->stuFaceRecognitionScene.stuMainDirection[0].nY);
		m_strMaindirection1 = szTempBuf;
		memset(szTempBuf, 0, sizeof(szTempBuf));
		sprintf(szTempBuf, "X%d, Y%d", pSenceInfo->stuFaceRecognitionScene.stuMainDirection[1].nX, pSenceInfo->stuFaceRecognitionScene.stuMainDirection[1].nY);
		m_strMaindirection2 = szTempBuf;

		m_pIvsSceneDraw->setMainDirection(pSenceInfo->stuFaceRecognitionScene.stuMainDirection, FALSE);
	}

	UpdateData(FALSE);
}

BOOL CSenceCfgdlg::SaveSceneInfo(CFG_ANALYSEGLOBAL_INFO* pSenceInfo)
{
	if(!UpdateData(TRUE))
	{
		return FALSE;
	}

	if (pSenceInfo == NULL)
	{
		return FALSE;
	}

	pSenceInfo->bFaceRecognition = TRUE;
	strncpy(pSenceInfo->szSceneType, "FaceRecognition", MAX_NAME_LEN);
	pSenceInfo->stuFaceRecognitionScene.dbCameraHeight = m_dbCameraHight;
	pSenceInfo->stuFaceRecognitionScene.byFaceAngleDown = m_nFaceAngleDown;
	pSenceInfo->stuFaceRecognitionScene.byFaceAngleUp = m_nFaceAngleUp;
	pSenceInfo->stuFaceRecognitionScene.byFaceAngleLeft = m_nFaceAngleLeft;
	pSenceInfo->stuFaceRecognitionScene.byFaceAngleRight = m_nFaceAngleRight;
	pSenceInfo->stuFaceRecognitionScene.nMainDirection = 2;
	sscanf((LPSTR)(LPCSTR)m_strMaindirection1, "X%d, Y%d", &(pSenceInfo->stuFaceRecognitionScene.stuMainDirection[0].nX), 
		&(pSenceInfo->stuFaceRecognitionScene.stuMainDirection[0].nY));
	sscanf((LPSTR)(LPCSTR)m_strMaindirection2, "X%d, Y%d", &(pSenceInfo->stuFaceRecognitionScene.stuMainDirection[1].nX), 
		&(pSenceInfo->stuFaceRecognitionScene.stuMainDirection[1].nY));

	return TRUE;
}

LRESULT CSenceCfgdlg::OnZoneDone(WPARAM wParam, LPARAM lParam)
{
	CFG_POLYGON* pMainDirection = (CFG_POLYGON*)wParam;
	int  nPointNum = (int)lParam;

	if (pMainDirection != NULL && nPointNum >= 2)
	{
		char szTempBuf[64] = {0};
		sprintf(szTempBuf, "X%d, Y%d", pMainDirection[0].nX, pMainDirection[0].nY);
		GetDlgItem(IDC_EDIT_MAINDIR_1)->SetWindowText(szTempBuf);
		m_strMaindirection1 = szTempBuf;
		memset(szTempBuf, 0, sizeof(szTempBuf));
		sprintf(szTempBuf, "X%d, Y%d", pMainDirection[1].nX, pMainDirection[1].nY);
		GetDlgItem(IDC_EDIT_MAINDIR_2)->SetWindowText(szTempBuf);
		m_strMaindirection2 = szTempBuf;

	}
	return TRUE;

}