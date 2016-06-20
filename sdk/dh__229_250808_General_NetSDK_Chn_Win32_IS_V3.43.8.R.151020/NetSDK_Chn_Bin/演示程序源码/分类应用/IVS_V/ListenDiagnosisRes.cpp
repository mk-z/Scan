// ListenDiagnosisRes.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "ListenDiagnosisRes.h"
#include "ProjectCfg.h"
#include "IVS_VDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListenDiagnosisRes dialog

static const int g_nResultOfPage = 20;

const std::string g_szFailType[] = {
	"Diagnosis succ"		,
	"Disconnect"			,
	"Ch Not Exist"			,	 
	"Login Over Time"		,
	"No Video"				,
	"No Right"				,
	"PlatformLoginFailed"	,
	"PlatformDisconnect"    ,
	"GetStreamOverTime"		,
	"Unknow "				,
};

const std::string g_szResultType[] = {
	"Rotation" , 
	"Real" , 
	"Unknow Type" ,
};

const std::string g_szDiagnosisState[] = 
{
	"Fail"	  ,
	"Success" ,
};



CListenDiagnosisRes::CListenDiagnosisRes(CWnd* pParent /*=NULL*/)
	: CDialog(CListenDiagnosisRes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListenDiagnosisRes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CListenDiagnosisRes::CListenDiagnosisRes(CDialog* pProject, CWnd* pParent /*= NULL*/)
: CDialog(CListenDiagnosisRes::IDD, pParent),m_pProject(reinterpret_cast<CProjectCfg*>(pProject))
,m_hDiagnosisHandle(0)
{
	
}

CListenDiagnosisRes::~CListenDiagnosisRes()
{
	if( 0 != m_hDiagnosisHandle )
	{
		CLIENT_StopVideoDiagnosis(m_hDiagnosisHandle);
		m_hDiagnosisHandle = 0 ;
	}
};

void CListenDiagnosisRes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListenDiagnosisRes)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LISTEN_LIST_RESULT, m_lstResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListenDiagnosisRes, CDialog)
	//{{AFX_MSG_MAP(CListenDiagnosisRes)
	ON_BN_CLICKED(IDC_BTN_STOP_LISTEN, OnBtnStopListen)
	ON_BN_CLICKED(IDC_BTN_START_LISTEN, OnBtnStartListen)
	ON_BN_CLICKED(IDC_LISTEN_BTN_FIRSTPAGE, OnListenBtnFirstPage)
	ON_BN_CLICKED(IDC_LISTEN_BTN_PREPAGE, OnListenBtnPrePage)
	ON_BN_CLICKED(IDC_LISTEN_BTN_NEXTPAGE, OnListenBtnNextPage)
	ON_BN_CLICKED(IDC_LISTEN_BTN_ENDPAGE, OnListenBtnEndPage)
	ON_BN_CLICKED(IDC_LISTEN_BTN_GOPAGE, OnListenBtnGoPage)
	ON_BN_CLICKED(IDC_RADIO_LISTEN_ALL_DEVICES, OnRadioListenAllDevices)
	ON_BN_CLICKED(IDC_RADIO_LISTEN_ONE_DEVICE, OnRadioListenOneDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CListenDiagnosisRes::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstResult.ModifyStyleEx(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	m_lstResult.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	char *szListTitle[]={"NO.", "CameraName", "Dither", "Stration", "Loss",
		"Cover", "Frozen", "Brightness", "Contrast", "Unbalance",
		"Noise", "Blur", "SceneChange"};
	for (int i=0; i< sizeof(szListTitle)/sizeof(szListTitle[0]); i++)
	{
		m_lstResult.InsertColumn(i, ConvertString(szListTitle[i]), LVCFMT_CENTER, 60);
	}

	CButton *pBtn = reinterpret_cast<CButton *>(GetDlgItem(IDC_RADIO_LISTEN_ALL_DEVICES));
	pBtn->SetCheck(BST_CHECKED);
	OnRadioListenAllDevices();

	SetDlgItemInt(IDC_LISTEN_EDIT_WAITTIME ,1000);
	GetDlgItem(IDC_BTN_START_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_LISTEN_BTN_FIRSTPAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LISTEN_BTN_PREPAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LISTEN_BTN_NEXTPAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LISTEN_BTN_ENDPAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LISTEN_BTN_GOPAGE)->EnableWindow(FALSE);

	GetDlgItem(IDC_FAILED_CAUSE)->SetWindowText("No Msg");
	GetDlgItem(IDC_RESULT_TYPE)->SetWindowText(("No Msg"));
	GetDlgItem(IDC_COLLECTIVITY_STATE)->SetWindowText("No Msg");

	SetDlgItemText(IDC_STATIC_RESULT,ConvertString("E: Error, -: Normal, W: Warning, A: Abnormal"));
	g_SetWndStaticText(this);
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CListenDiagnosisRes message handlers


void CListenDiagnosisRes::OnBtnStopListen() 
{
	if( 0!= m_hDiagnosisHandle)
	{
		CLIENT_StopVideoDiagnosis(m_hDiagnosisHandle);
		m_hDiagnosisHandle = 0;

		GetDlgItem(IDC_BTN_START_LISTEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_STOP_LISTEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_LISTEN_BTN_FIRSTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LISTEN_BTN_PREPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LISTEN_BTN_NEXTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LISTEN_BTN_ENDPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_LISTEN_BTN_GOPAGE)->EnableWindow(FALSE);

		
		GetDlgItem(IDC_FAILED_CAUSE)->SetWindowText("No Msg");
		GetDlgItem(IDC_RESULT_TYPE)->SetWindowText(("No Msg"));
		GetDlgItem(IDC_COLLECTIVITY_STATE)->SetWindowText("No Msg");
	}
	
}

int CALLBACK RealVideoDiagnosis(LLONG lDiagnosisHandle, NET_REAL_DIAGNOSIS_RESULT* pDiagnosisInfo, void* pBuf, int nBufLen, LDWORD dwUser)
{
	if( (lDiagnosisHandle == 0) || ( pDiagnosisInfo == NULL ) ||
		(pBuf == NULL ) || (nBufLen == 0 ) || (dwUser == 0 ) )
	{
		return 0;
	}

	CListenDiagnosisRes * pListenDiagnosisRes = (CListenDiagnosisRes *)dwUser;
	NET_VIDEODIAGNOSIS_COMMON_INFO * pstVideoCommInfo = pDiagnosisInfo->pstDiagnosisCommonInfo;
	
	pListenDiagnosisRes->m_hDiagnosisHandle = lDiagnosisHandle;

	pListenDiagnosisRes->GetDlgItem(IDC_FAILED_CAUSE)
		->SetWindowText(g_szFailType[pstVideoCommInfo->emFailedCause].c_str());

	pListenDiagnosisRes->GetDlgItem(IDC_RESULT_TYPE)
		->SetWindowText(g_szResultType[pstVideoCommInfo->emResultType].c_str() );

	pListenDiagnosisRes->GetDlgItem(IDC_COLLECTIVITY_STATE)
		->SetWindowText(g_szDiagnosisState[pstVideoCommInfo->bCollectivityState].c_str());

	//int nSumPage = 

	return 0;
}

void CListenDiagnosisRes::OnBtnStartListen() 
{
	char szDebugMsg[MAX_PATH] = {0};

	CIVS_VDemoDlg *pParent = reinterpret_cast<CIVS_VDemoDlg *>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();

	if( lLoginID <= 0 )
	{
		//return;
	}

	NET_IN_VIDEODIAGNOSIS stIn = {0};
	NET_OUT_VIDEODIAGNOSIS stOut = {0};

	//Init NET_IN_VIDEODIAGNOSIS
	stIn.dwSize = sizeof( NET_IN_VIDEODIAGNOSIS );
	stIn.nDiagnosisID = 0;
	stIn.dwWaitTime = GetDlgItemInt(IDC_LISTEN_EDIT_WAITTIME);
	stIn.dwUser = (DWORD)this;

	if (0 == stIn.dwWaitTime)
	{
		AfxMessageBox(ConvertString("Wait time can not be zero !"));
		return;
	}
	stIn.cbVideoDiagnosis = RealVideoDiagnosis;

	//Init NET_OUT_VIDEODIAGNOSIS
	stOut.dwSize = sizeof( NET_OUT_VIDEODIAGNOSIS );

	BOOL bRet = CLIENT_StartVideoDiagnosis(lLoginID, &stIn, &stOut);
	sprintf(szDebugMsg, 
		ConvertString("(0x%x) CLIENT_StartVideoDiagnosis return %s LastError:0x%x item!"),
		stOut.lDiagnosisHandle,
		bRet==TRUE?ConvertString("successfully"):ConvertString("failure"),
		CLIENT_GetLastError());

	if(  TRUE == bRet )
	{
		m_hDiagnosisHandle = stOut.lDiagnosisHandle;

		GetDlgItem(IDC_BTN_START_LISTEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STOP_LISTEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_LISTEN_BTN_FIRSTPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_LISTEN_BTN_PREPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_LISTEN_BTN_NEXTPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_LISTEN_BTN_ENDPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_LISTEN_BTN_GOPAGE)->EnableWindow(TRUE);
	}
	else
	{
		AfxMessageBox(szDebugMsg);
	}
}

void CListenDiagnosisRes::OnListenBtnFirstPage() 
{
	int nSumPage = GetDlgItemInt(IDC_LISTEN_EDIT_PAGESUM);
	if (nSumPage < 1)
	{
		return;
	}

	int nIndexPage = 1;
	SetDlgItemInt(IDC_EDIT_PAGEINDEX,nIndexPage);
	m_lstResult.DeleteAllItems();
	
	GetDlgItem(IDC_LISTEN_BTN_PREPAGE)->EnableWindow(FALSE);	
	GetDlgItem(IDC_LISTEN_BTN_FIRSTPAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_LISTEN_BTN_NEXTPAGE)->EnableWindow(FALSE);	
	GetDlgItem(IDC_LISTEN_BTN_ENDPAGE)->EnableWindow(FALSE);
	if (nSumPage>1)
	{
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(TRUE);	
		GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(TRUE);
	}
	
	/*
	// 申请内存
	NET_OUT_DIAGNOSIS_INFO *pstDoOut = NULL;
	if (FALSE == InitOutDiagnosisInfo(&pstDoOut))
		return;
	// 查询第一页
	BOOL bRet = QueryPage(m_lFindHandle, nIndexPage-1, pstDoOut);
	if (bRet)
	{
		// 更新界面
		UpDateDataToDlg(pstDoOut);
	}
	// 删除内存
	DeleteOutDiagnosisInfo(pstDoOut);
	*/
}

void CListenDiagnosisRes::OnListenBtnPrePage() 
{
	// TODO: Add your control notification handler code here
	
}

void CListenDiagnosisRes::OnListenBtnNextPage() 
{
	// TODO: Add your control notification handler code here
	
}

void CListenDiagnosisRes::OnListenBtnEndPage() 
{
	// TODO: Add your control notification handler code here
	
}

void CListenDiagnosisRes::OnListenBtnGoPage() 
{
	// TODO: Add your control notification handler code here
	
}

void CListenDiagnosisRes::OnRadioListenAllDevices() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_LISTEN_IPADDRESS)->EnableWindow(FALSE);
	
}

void CListenDiagnosisRes::OnRadioListenOneDevice() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_LISTEN_IPADDRESS)->EnableWindow(TRUE);	
}
