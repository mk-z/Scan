// QueryDiagnosisRes.cpp : implementation file
//

#include "stdafx.h"
#include "IVS_VDemo.h"
#include "QueryDiagnosisRes.h"
#include "ProjectCfg.h"
#include "IVS_VDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryDiagnosisRes dialog

const int g_nResultOfPage = 20;

CQueryDiagnosisRes::CQueryDiagnosisRes(CWnd* pParent /*=NULL*/)
	: CDialog(CQueryDiagnosisRes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQueryDiagnosisRes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pProject = NULL;
}

CQueryDiagnosisRes::CQueryDiagnosisRes(CDialog* pProject, CWnd* pParent /*= NULL*/)
: CDialog(CQueryDiagnosisRes::IDD, pParent),m_pProject(reinterpret_cast<CProjectCfg*>(pProject))
,m_lFindHandle(0)
{

}

CQueryDiagnosisRes::~CQueryDiagnosisRes()
{
	if (0 != m_lFindHandle)
	{
		CLIENT_StopFindDiagnosis(m_lFindHandle);
		m_lFindHandle = 0;
	}
}

void CQueryDiagnosisRes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQueryDiagnosisRes)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_DATE, m_startDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_TIME, m_startTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_DATE, m_endDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_TIME, m_endTime);
	DDX_Control(pDX, IDC_LIST_RESULT, m_lstResult);
	//DDX_Control(pDX, IDC_COMBO_TYPE, m_comboType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQueryDiagnosisRes, CDialog)
	//{{AFX_MSG_MAP(CQueryDiagnosisRes)
	ON_BN_CLICKED(IDC_BTN_QUERY,OnBtnQuery)
	ON_BN_CLICKED(IDC_BTN_STOP_QUERY,OnBtnStopQuery)
	ON_BN_CLICKED(IDC_BTN_FIRSTPAGE,OnBtnFirstPage)
	ON_BN_CLICKED(IDC_BTN_PREPAGE,OnBtnPrePage)
	ON_BN_CLICKED(IDC_BTN_NEXTPAGE,OnBtnNextPage)
	ON_BN_CLICKED(IDC_BTN_ENDPAGE,OnBtnEndPage)
	ON_BN_CLICKED(IDC_BTN_GOPAGE,OnBtnGoPage)
	ON_BN_CLICKED(IDC_RADIO_ALL_DEVICES, OnRadioAllDevices)
	ON_BN_CLICKED(IDC_RADIO_ONE_DEVICE, OnRadioOneDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryDiagnosisRes message handlers

void CQueryDiagnosisRes::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CQueryDiagnosisRes::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL CQueryDiagnosisRes::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_startDate.ModifyStyleEx(0, DTS_SHORTDATEFORMAT);
	m_startTime.ModifyStyleEx(0, DTS_TIMEFORMAT);
	m_endDate.ModifyStyleEx(0, DTS_SHORTDATEFORMAT );
	m_endTime.ModifyStyleEx(0, DTS_TIMEFORMAT);
	
	m_lstResult.ModifyStyleEx(0, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL);
	m_lstResult.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	char *szListTitle[]={"NO.", "CameraName", "Dither", "Stration", "Loss",
	"Cover", "Frozen", "Brightness", "Contrast", "Unbalance",
	"Noise", "Blur", "SceneChange"};
	for (int i=0; i< sizeof(szListTitle)/sizeof(szListTitle[0]); i++)
	{
		m_lstResult.InsertColumn(i, ConvertString(szListTitle[i]), LVCFMT_CENTER, 60);
	}

	CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_RADIO_ALL_DEVICES));
	pBtn->SetCheck(BST_CHECKED);
	OnRadioAllDevices();

	SetDlgItemInt(IDC_EDIT_WAITTIME,3000);

#if 0
	{
		char *szListType[]={"All", "Dither", "Stration", "Loss",
			"Cover", "Frozen", "Brightness", "Contrast", "Unbalance",
			"Noise", "Blur", "SceneChange"};
		for (int i=0; i< sizeof(szListType)/sizeof(szListType[0]); i++)
		{
			m_comboType.InsertString(i,szListType[i]);
		}
		m_comboType.SetCurSel(0);
	}
#endif

	{
		GetDlgItem(IDC_BTN_QUERY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_STOP_QUERY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_GOPAGE)->EnableWindow(FALSE);
	}

	SetDlgItemText(IDC_STATIC_RESULT,ConvertString("E: Error, -: Normal, W: Warning, A: Abnormal"));
	g_SetWndStaticText(this);

	return TRUE;
}

void CQueryDiagnosisRes::OnBtnQuery()
{
	char szDebugMsg[MAX_PATH]={0};

	CIVS_VDemoDlg* pParent =  reinterpret_cast<CIVS_VDemoDlg*>(GetOwner());
	DWORD lLoginID = pParent->GetLoginID();
	if (lLoginID <= 0)
	{
		return;
	}

	NET_IN_FIND_DIAGNOSIS stIn = {0};
	stIn.dwWaitTime = GetDlgItemInt(IDC_EDIT_WAITTIME);
	if (0 == stIn.dwWaitTime)
	{
		AfxMessageBox(ConvertString("Wait time can not be zero !"));
		return;
	}
	// 目前只能用通道0的实例查询
	stIn.nDiagnosisID = 0;
	
	// type
	stIn.nTypeCount = 1;
	stIn.pstDiagnosisTypes = new NET_ARRAY[stIn.nTypeCount];
	for (int i=0; i< stIn.nTypeCount; i++)
	{
		NET_ARRAY &stType = stIn.pstDiagnosisTypes[i];
		stType.dwSize = sizeof(NET_ARRAY);
		stType.dwArrayLen = MAX_PATH;
// 		stType.pArray = new char[stType.dwArrayLen];
// 		if (NULL != stType.pArray)
// 		{
// 			memset(stType.pArray,0x0,stType.dwArrayLen);
// 		}
		stType.pArray = NULL;
	}
	
	// device
	CButton* pBtn = reinterpret_cast<CButton*>(GetDlgItem(IDC_RADIO_ALL_DEVICES));
	if ( BST_CHECKED == pBtn->GetCheck())
	{
		stIn.stuDeviceID.pArray = NULL;
	}
	else
	{
		stIn.stuDeviceID.pArray = new char[stIn.stuDeviceID.dwArrayLen];
		if (NULL != stIn.stuDeviceID.pArray)
		{
			stIn.stuDeviceID.dwArrayLen = MAX_PATH;
			memset(stIn.stuDeviceID.pArray,0x0,stIn.stuDeviceID.dwArrayLen);
			GetDlgItemText(IDC_IPADDRESS1, stIn.stuDeviceID.pArray, MAX_PATH-1);
		}
	}
	
	// time
	SYSTEMTIME st = {0};
	m_startDate.GetTime(&st);
	stIn.stuStartTime.dwYear = st.wYear;
	stIn.stuStartTime.dwMonth = st.wMonth;
	stIn.stuStartTime.dwDay = st.wDay;
	m_startTime.GetTime(&st);
	stIn.stuStartTime.dwHour = st.wHour;
	stIn.stuStartTime.dwMinute = st.wMinute;
	stIn.stuStartTime.dwSecond = st.wSecond;

	SYSTEMTIME stEnd = {0};
	m_endDate.GetTime(&stEnd);
	stIn.stuEndTime.dwYear = stEnd.wYear;
	stIn.stuEndTime.dwMonth = stEnd.wMonth;
	stIn.stuEndTime.dwDay = stEnd.wDay;
	m_endTime.GetTime(&stEnd);
	stIn.stuEndTime.dwHour = stEnd.wHour;
	stIn.stuEndTime.dwMinute = stEnd.wMinute;
	stIn.stuEndTime.dwSecond = stEnd.wSecond;

	stIn.nVideoChannel = -1;
	
	stIn.stuDeviceID.dwSize = sizeof(NET_ARRAY) ;
	stIn.dwSize = sizeof (NET_IN_FIND_DIAGNOSIS);
	
	NET_OUT_FIND_DIAGNOSIS stOut = {0};
	stOut.dwSize = sizeof (NET_OUT_FIND_DIAGNOSIS);
	
	BOOL bRet = CLIENT_StartFindDiagnosisResult(lLoginID,&stIn,&stOut);
	sprintf(szDebugMsg, ConvertString("(0x%x) CLIENT_StartFindDiagnosisResult return %s LastError:0x%x dwTotalCount:%d item!"),
		stOut.lFindHandle,bRet==TRUE?ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError(),stOut.dwTotalCount);
	if (bRet == TRUE)
	{
		m_lFindHandle = stOut.lFindHandle;
		// 更新界面总页数
		int nSumPage = stOut.dwTotalCount/ g_nResultOfPage;
		if (stOut.dwTotalCount % g_nResultOfPage)
		{
			nSumPage++;
		}

		SetDlgItemInt(IDC_EDIT_PAGESUM, nSumPage);
		if (nSumPage)
		{						
			// 界面状态
			if (nSumPage > 1)
			{
				GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_GOPAGE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_QUERY)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_STOP_QUERY)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BTN_GOPAGE)->EnableWindow(FALSE);
			}

			OnBtnFirstPage();
		}
		else
		{
			m_lstResult.DeleteAllItems();
			// 界面状态
			GetDlgItem(IDC_BTN_QUERY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_STOP_QUERY)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_GOPAGE)->EnableWindow(FALSE);

			OnBtnStopQuery();
		}
	}
	else
	AfxMessageBox(szDebugMsg);

	// 清理申请内存
	if (NULL != stIn.pstDiagnosisTypes)
	{
		for (int i=0; i< stIn.nTypeCount; i++)
		{
			NET_ARRAY &stType = stIn.pstDiagnosisTypes[i];
			if (NULL != stType.pArray)
			{
				delete []stType.pArray;
				stType.pArray = NULL;
			}
		}

		if (NULL != stIn.stuDeviceID.pArray)
		{
			delete []stIn.stuDeviceID.pArray;
			stIn.stuDeviceID.pArray = NULL;
		}

		delete [] stIn.pstDiagnosisTypes;
	}
}

void CQueryDiagnosisRes::OnBtnStopQuery()
{
	if (0 != m_lFindHandle)
	{
		CLIENT_StopFindDiagnosis(m_lFindHandle);
		m_lFindHandle = 0;

		GetDlgItem(IDC_BTN_QUERY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_STOP_QUERY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_GOPAGE)->EnableWindow(FALSE);
	}
}

BOOL CQueryDiagnosisRes::UpDateDataToDlg(NET_OUT_DIAGNOSIS_INFO *pstDoOut)
{

#define DISP_STATE(A,P,J){\
	if (NULL != A)\
	{\
		int nS = P->emState;\
		if ( nS < nState && nS > 0 )\
		{\
			m_lstResult.SetItemText(i,J, ConvertString(szState[nS]));\
		}\
	}\
}

	if (NULL == pstDoOut)
	{
		return FALSE;
	}

	if ( pstDoOut->nInputNum < pstDoOut->nReturnNum)
	{
		return FALSE;
	}

	//const char *szState[] = {"Error","Normal","Warning","Abnormal"};
	const char *szState[] = {"Err","-","W","A"};
	int nState = sizeof(szState)/sizeof(szState[0]);

	for (int i=0; i< pstDoOut->nReturnNum; i++)
	{
		NET_VIDEODIAGNOSIS_RESULT_INFO &stResult = pstDoOut->pstDiagnosisResult[i];

		char szTmp[MAX_PATH] = {0};
		sprintf(szTmp, "%d",i+1);
		m_lstResult.InsertItem(i, szTmp);

		int j = 1;
		m_lstResult.SetItemText(i, j++, stResult.pstDiagnosisCommonInfo->stDeviceID.pArray);

		DISP_STATE(stResult.abDither, stResult.pstDither, j++);
		DISP_STATE(stResult.abStration, stResult.pstStration, j++);
		DISP_STATE(stResult.abLoss, stResult.pstLoss, j++);
		DISP_STATE(stResult.abCover, stResult.pstCover, j++);
		DISP_STATE(stResult.abFrozen, stResult.pstFrozen, j++);

		DISP_STATE(stResult.abBrightness, stResult.pstBrightness, j++);
		DISP_STATE(stResult.abContrast, stResult.pstContrast, j++);
		DISP_STATE(stResult.abUnbalance, stResult.pstUnbalance, j++);
		DISP_STATE(stResult.abNoise, stResult.pstNoise, j++);
		DISP_STATE(stResult.abBlur, stResult.pstBlur, j++);

		DISP_STATE(stResult.abSceneChange, stResult.pstSceneChange, j++);
	}

	return TRUE;
}

void CQueryDiagnosisRes::OnBtnFirstPage()
{
	int nSumPage = GetDlgItemInt(IDC_EDIT_PAGESUM);
	if (nSumPage < 1)
	{
		return;
	}
	int nIndexPage = 1;
	SetDlgItemInt(IDC_EDIT_PAGEINDEX,nIndexPage);
	m_lstResult.DeleteAllItems();

	GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);
	if (nSumPage>1)
	{
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(TRUE);	
		GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(TRUE);
	}

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
}
void CQueryDiagnosisRes::OnBtnPrePage()
{
	int nIndexPage = GetDlgItemInt(IDC_EDIT_PAGEINDEX);
	int nSumPage = GetDlgItemInt(IDC_EDIT_PAGESUM);
	if (nIndexPage-1 > 0 && nSumPage > 0)
	{
		if (nIndexPage == nSumPage)
		{
			GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(TRUE);
		}
		SetDlgItemInt(IDC_EDIT_PAGEINDEX,--nIndexPage);
		m_lstResult.DeleteAllItems();
		if (1 == nIndexPage)
		{
			GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(FALSE);
		}
	}
	else
	{
		return;
	}
	
	// 申请内存
	NET_OUT_DIAGNOSIS_INFO *pstDoOut = NULL;
	if (FALSE == InitOutDiagnosisInfo(&pstDoOut))
		return;
	
	// 查询上一页
	BOOL bRet = QueryPage(m_lFindHandle, nIndexPage-1, pstDoOut);
	if (bRet)
	{
		// 更新界面
		UpDateDataToDlg(pstDoOut);
	}
	
	// 删除内存
	DeleteOutDiagnosisInfo(pstDoOut);

}
void CQueryDiagnosisRes::OnBtnNextPage()
{
	int nIndexPage = GetDlgItemInt(IDC_EDIT_PAGEINDEX);
	int nSumPage = GetDlgItemInt(IDC_EDIT_PAGESUM);
	if (nSumPage-nIndexPage >= 1 && nSumPage > 0)
	{
		if (1 == nIndexPage)
		{
			GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(TRUE);
		}
		SetDlgItemInt(IDC_EDIT_PAGEINDEX,++nIndexPage);
		m_lstResult.DeleteAllItems();
		if (nIndexPage == nSumPage)
		{
			GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);
		}
	}
	else
	{
		return;
	}
	
	// 申请内存
	NET_OUT_DIAGNOSIS_INFO *pstDoOut = NULL;
	if (FALSE == InitOutDiagnosisInfo(&pstDoOut))
		return;
	
	// 查询上一页
	BOOL bRet = QueryPage(m_lFindHandle, nIndexPage-1, pstDoOut);
	if (bRet)
	{
		// 更新界面
		UpDateDataToDlg(pstDoOut);
	}
	// 删除内存
	DeleteOutDiagnosisInfo(pstDoOut);
}
void CQueryDiagnosisRes::OnBtnEndPage()
{
	int nSumPage = GetDlgItemInt(IDC_EDIT_PAGESUM);
	if (nSumPage <= 0)
	{
		return;
	}
	m_lstResult.DeleteAllItems();
	SetDlgItemInt(IDC_EDIT_PAGEINDEX,nSumPage);

	GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(TRUE);	
	GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);	
	// 申请内存
	NET_OUT_DIAGNOSIS_INFO *pstDoOut = NULL;
	if (FALSE == InitOutDiagnosisInfo(&pstDoOut))
		return;
	
	// 查询上一页
	BOOL bRet = QueryPage(m_lFindHandle, nSumPage-1, pstDoOut);
	if (bRet)
	{
		// 更新界面
		UpDateDataToDlg(pstDoOut);
	}
	// 删除内存
	DeleteOutDiagnosisInfo(pstDoOut);
}
void CQueryDiagnosisRes::OnBtnGoPage()
{
	int nIndexPage = GetDlgItemInt(IDC_EDIT_GOPAGE);
	int nSumPage = GetDlgItemInt(IDC_EDIT_PAGESUM);
	if (nSumPage <= 0)
	{
		return;
	}
	if (nIndexPage > nSumPage || nIndexPage <1)
	{
		return;
	}

	m_lstResult.DeleteAllItems();
	if (1 == nIndexPage)
	{
		GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(TRUE);
	}
	else if (nSumPage == nIndexPage)
	{
		GetDlgItem(IDC_BTN_PREPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_FIRSTPAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_NEXTPAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ENDPAGE)->EnableWindow(FALSE);
	}	
	// 申请内存
	NET_OUT_DIAGNOSIS_INFO *pstDoOut = NULL;
	if (FALSE == InitOutDiagnosisInfo(&pstDoOut))
		return;
	
	// 查询上一页
	BOOL bRet = QueryPage(m_lFindHandle, nIndexPage-1, pstDoOut);
	if (bRet)
	{
		// 更新界面
		UpDateDataToDlg(pstDoOut);
		SetDlgItemInt(IDC_EDIT_PAGEINDEX,nIndexPage);		
	}
	// 删除内存
	DeleteOutDiagnosisInfo(pstDoOut);	
}

BOOL CQueryDiagnosisRes::InitOutDiagnosisInfo(NET_OUT_DIAGNOSIS_INFO **pstDoOut)
{
#define NET_ARR_INIT(OBJ,LEN){\
	OBJ.pArray = new char[(LEN)];\
	if (NULL != OBJ.pArray){\
	OBJ.dwSize = sizeof(NET_ARRAY);\
	OBJ.dwArrayLen = LEN;\
	}\
}
	int i = 0;
	if (NULL == pstDoOut)
	{
		return FALSE;
	}
	
	if (NULL != *pstDoOut)
	{
		DeleteOutDiagnosisInfo(*pstDoOut);
	}

	*pstDoOut = new NET_OUT_DIAGNOSIS_INFO;
	if (NULL == *pstDoOut)
	{
		return FALSE;
	}
	memset(*pstDoOut, 0, sizeof(NET_OUT_DIAGNOSIS_INFO));

	NET_OUT_DIAGNOSIS_INFO &stDoOut = **pstDoOut;
	stDoOut.dwSize = sizeof(NET_OUT_DIAGNOSIS_INFO);
	stDoOut.nInputNum = g_nResultOfPage;
	stDoOut.pstDiagnosisResult = new NET_VIDEODIAGNOSIS_RESULT_INFO[stDoOut.nInputNum];
	if (stDoOut.pstDiagnosisResult == NULL)
	{
		goto _clear;
	}
	for (i=0;i<stDoOut.nInputNum;i++)
	{
		NET_VIDEODIAGNOSIS_RESULT_INFO* pInfo = &stDoOut.pstDiagnosisResult[i];
		
		if (NULL != pInfo)
		{
			memset(pInfo, 0, sizeof(NET_VIDEODIAGNOSIS_RESULT_INFO));
			pInfo->dwSize = sizeof(NET_VIDEODIAGNOSIS_RESULT_INFO);

			pInfo->pstDiagnosisCommonInfo = new NET_VIDEODIAGNOSIS_COMMON_INFO;
			if (NULL == pInfo->pstDiagnosisCommonInfo)
			{
				goto _clear;
			}

			NET_VIDEODIAGNOSIS_COMMON_INFO* pCmn = pInfo->pstDiagnosisCommonInfo;
			NET_ARR_INIT(pCmn->stProject,MAX_PATH);
			NET_ARR_INIT(pCmn->stProfile,MAX_PATH);
			NET_ARR_INIT(pCmn->stTask,MAX_PATH);
			NET_ARR_INIT(pCmn->stDeviceID,MAX_PATH);
			
			pInfo->pstBlur = new NET_VIDEO_BLUR_DETECTIONRESULT;
			pInfo->pstBrightness = new NET_VIDEO_BRIGHTNESS_DETECTIONRESULT;
			pInfo->pstContrast = new NET_VIDEO_CONTRAST_DETECTIONRESULT;
			pInfo->pstCover = new NET_VIDEO_COVER_DETECTIONRESULT;
			pInfo->pstDither = new NET_VIDEO_DITHER_DETECTIONRESULT;
			pInfo->pstFrozen = new NET_VIDEO_FROZEN_DETECTIONRESULT;
			pInfo->pstLoss = new NET_VIDEO_LOSS_DETECTIONRESULT;
			pInfo->pstNoise = new NET_VIDEO_NOISE_DETECTIONRESULT;
			pInfo->pstSceneChange = new NET_VIDEO_SCENECHANGE_DETECTIONRESULT;
			pInfo->pstStration = new NET_VIDEO_STRIATION_DETECTIONRESULT;
			pInfo->pstUnbalance = new NET_VIDEO_UNBALANCE_DETECTIONRESULT;
		}
	}

	return TRUE;

_clear:
	DeleteOutDiagnosisInfo(*pstDoOut);
	return FALSE;
}

void CQueryDiagnosisRes::DeleteOutDiagnosisInfo(NET_OUT_DIAGNOSIS_INFO *pstDoOut)
{
	if (NULL != pstDoOut)
	{
		for (int i=0; i<pstDoOut->nInputNum; i++)
		{
			NET_VIDEODIAGNOSIS_RESULT_INFO& stDiagnosisResult = pstDoOut->pstDiagnosisResult[i];
			SAFE_DELETE(stDiagnosisResult.pstDiagnosisCommonInfo->stDeviceID.pArray);
			SAFE_DELETE(stDiagnosisResult.pstDiagnosisCommonInfo->stProject.pArray);
			SAFE_DELETE(stDiagnosisResult.pstDiagnosisCommonInfo->stProfile.pArray);
			SAFE_DELETE(stDiagnosisResult.pstDiagnosisCommonInfo->stTask.pArray);
			SAFE_DELETE(stDiagnosisResult.pstDiagnosisCommonInfo);

			SAFE_DELETE(stDiagnosisResult.pstDither);
			SAFE_DELETE(stDiagnosisResult.pstStration);
			SAFE_DELETE(stDiagnosisResult.pstLoss);
			SAFE_DELETE(stDiagnosisResult.pstCover);
			SAFE_DELETE(stDiagnosisResult.pstFrozen);

			SAFE_DELETE(stDiagnosisResult.pstBrightness);
			SAFE_DELETE(stDiagnosisResult.pstContrast);
			SAFE_DELETE(stDiagnosisResult.pstUnbalance);
			SAFE_DELETE(stDiagnosisResult.pstNoise);
			SAFE_DELETE(stDiagnosisResult.pstBlur);

			SAFE_DELETE(stDiagnosisResult.pstSceneChange);
		}
		SAFE_DELETE_A(pstDoOut->pstDiagnosisResult);
		SAFE_DELETE(pstDoOut);
	}
}

BOOL CQueryDiagnosisRes::QueryPage(LLONG lFindHandle, int nPage, NET_OUT_DIAGNOSIS_INFO * pstDoOut)
{
	if (NULL == pstDoOut || 0 == lFindHandle)
	{
		return FALSE;
	}

	NET_IN_DIAGNOSIS_INFO stDoIn = {0};
	stDoIn.dwSize = sizeof(NET_IN_DIAGNOSIS_INFO);
	stDoIn.nDiagnosisID = 0;
	stDoIn.nFindCount = g_nResultOfPage;
	stDoIn.nBeginNumber = nPage*g_nResultOfPage;
	stDoIn.dwWaitTime = GetDlgItemInt(IDC_EDIT_WAITTIME);
	pstDoOut->nReturnNum = 0;
	
	char szTmp[MAX_PATH] = {0};
	BOOL bRetDo = CLIENT_DoFindDiagnosisResult(lFindHandle, &stDoIn, pstDoOut);
	sprintf(szTmp, ConvertString("(0x%x) CLIENT_DoFindDiagnosisResult(nBeginNumber:%d,nFindCount:%d) return %s LastError:0x%x !"),
		lFindHandle,stDoIn.nBeginNumber,stDoIn.nFindCount,bRetDo==TRUE?ConvertString("successfully"):ConvertString("failure"),CLIENT_GetLastError());
#ifdef _DEBUG
	OutputDebugString(szTmp);
#endif // _DEBUG
	if (bRetDo)
	{
		printf("find result Count: %d !",pstDoOut->nReturnNum);
	}
	else
	{
		AfxMessageBox(szTmp);
	}

	return bRetDo;
}

void CQueryDiagnosisRes::OnRadioAllDevices() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(FALSE);
}

void CQueryDiagnosisRes::OnRadioOneDevice() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(TRUE);
}
