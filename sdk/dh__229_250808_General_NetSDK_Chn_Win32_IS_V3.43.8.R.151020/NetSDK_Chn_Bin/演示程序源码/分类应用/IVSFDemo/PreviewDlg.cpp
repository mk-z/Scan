// PreviewDlg.cpp : implementation file
//
#include "stdafx.h"
#include "IVSFDemo.h"
#include "PreviewDlg.h"
#include "AlarmShow.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_EVENT_LIST_NUM 100
#define WM_USER_DELET_EVENTLIST_EXCEEDITEM (WM_USER + 1)

/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg dialog


CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDlg::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CPreviewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nChannelCount = 0;
	m_lLogHandle = 0;
	m_pIVSFDemodlg = NULL;
	m_lRealPlayHandle = 0;
	m_pAlarmShow = NULL;
	InitializeCriticalSection(&m_csAlarmItems);
}

void CPreviewDlg::OnDestroy()
{
	CDialog::OnDestroy();

	Clean();
	DeleteCriticalSection(&m_csAlarmItems);

	if (NULL != m_pAlarmShow)
	{
		delete m_pAlarmShow;
		m_pAlarmShow = NULL;
	}
}


void CPreviewDlg::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewDlg)
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_cbChannel);
	DDX_Control(pDX, IDC_LIST_EVENT, m_lsEvent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialog)
	//{{AFX_MSG_MAP(CPreviewDlg)
	ON_BN_CLICKED(IDC_BUTTON_STARTVIEW, OnButtonStartview)
	ON_BN_CLICKED(IDC_BUTTON_STOPVIEW, OnButtonStopview)
	ON_MESSAGE(WM_USER_DELET_EVENTLIST_EXCEEDITEM, OnDeletExceededItems)
	ON_NOTIFY(NM_CLICK, IDC_LIST_EVENT, OnClickListEvent)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPreviewDlg, CDialog)
	//{{AFX_DISPATCH_MAP(CPreviewDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IPreviewDlg to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {E22755D5-08FD-436B-8AD9-CF22B1ACFD10}
static const IID IID_IPreviewDlg =
{ 0xe22755d5, 0x8fd, 0x436b, { 0x8a, 0xd9, 0xcf, 0x22, 0xb1, 0xac, 0xfd, 0x10 } };

BEGIN_INTERFACE_MAP(CPreviewDlg, CDialog)
	INTERFACE_PART(CPreviewDlg, IID_IPreviewDlg, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg message handlers

void CPreviewDlg::OnButtonStartview() 
{
	if (m_lLogHandle != 0)
	{
		int nIndex = m_cbChannel.GetCurSel();
		int nChannel = m_cbChannel.GetItemData(nIndex);
		HWND hWnd = GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd();
		m_lRealPlayHandle = CLIENT_RealPlayEx(m_lLogHandle, nChannel, hWnd, DH_RType_Realplay);
		if (m_lRealPlayHandle == 0)
		{
			MessageBox(ConvertString("real play failed"), ConvertString("Prompt"));
			return;
		}

		GetDlgItem(IDC_BUTTON_STOPVIEW)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STARTVIEW)->EnableWindow(FALSE);
	}
	else
	{
		MessageBox(ConvertString("please log device first"), ConvertString("Prompt"));
	}

	return;
}

void CPreviewDlg::OnButtonStopview() 
{
	if (m_lRealPlayHandle != 0)
	{
		BOOL bRet = CLIENT_StopRealPlayEx(m_lRealPlayHandle);
		if (!bRet)
		{
			MessageBox(ConvertString("stop real play failed"), ConvertString("Prompt"));
		}
		m_lRealPlayHandle = 0;
	}

	GetDlgItem(IDC_BUTTON_STOPVIEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STARTVIEW)->EnableWindow(TRUE);
	return;
}

void CPreviewDlg::OperateStream(BOOL bResume)
{

	if (bResume)
	{
		if (!GetDlgItem(IDC_BUTTON_STARTVIEW)->IsWindowEnabled())
		{
			if (m_lLogHandle != 0)
			{
				int nIndex = m_cbChannel.GetCurSel();
				int nChannel = m_cbChannel.GetItemData(nIndex);
				HWND hWnd = GetDlgItem(IDC_STATIC_PREVIEW)->GetSafeHwnd();
				m_lRealPlayHandle = CLIENT_RealPlayEx(m_lLogHandle, nChannel, hWnd, DH_RType_Realplay);
				if (m_lRealPlayHandle == 0)
				{
					MessageBox(ConvertString("real play failed"), ConvertString("Prompt"));
					return;
				}
			}
		}
		else if (!GetDlgItem(IDC_BUTTON_STOPVIEW)->IsWindowEnabled())
		{
			if (m_lRealPlayHandle != 0)
			{
				BOOL bRet = CLIENT_StopRealPlayEx(m_lRealPlayHandle);
				if (!bRet)
				{
					MessageBox(ConvertString("stop real play failed"), ConvertString("Prompt"));
				}
				m_lRealPlayHandle = 0;
			}
		}
	}
	else
	{
		if (m_lRealPlayHandle != 0)
		{
			BOOL bRet = CLIENT_StopRealPlayEx(m_lRealPlayHandle);
			if (!bRet)
			{
				MessageBox(ConvertString("stop real play failed"), ConvertString("Prompt"));
			}
		}
	}

}

BOOL CPreviewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);

	m_pAlarmShow = new CAlarmShow();
	if (m_pAlarmShow != NULL)
	{
		m_pAlarmShow->Create(CAlarmShow::IDD,this);
		CRect rc;
		GetDlgItem(IDC_STATIC_ALARMVIEW)->GetWindowRect(&rc);
		ScreenToClient(&rc);
		
		m_pAlarmShow->MoveWindow(&rc, TRUE);
		m_pAlarmShow->ShowWindow(SW_SHOW);
	}

	return TRUE;
}

void CPreviewDlg::Init(CIVSFDemoDlg* pDlg, LONG lLogHandle)
{
	m_pIVSFDemodlg = pDlg;
	m_lLogHandle = lLogHandle;

	m_lsEvent.DeleteAllItems();
	while(m_lsEvent.DeleteColumn(0)){}
	m_lsEvent.SetExtendedStyle(m_lsEvent.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_lsEvent.InsertColumn(0, ConvertString(_T("ChannelID")), LVCFMT_LEFT, 60, -1);
	m_lsEvent.InsertColumn(1, ConvertString(_T("RuleName")), LVCFMT_LEFT, 100, -1);
	m_lsEvent.InsertColumn(2, ConvertString(_T("TriggerTime")), LVCFMT_LEFT, 130, -1);
	m_lsEvent.InsertColumn(3, ConvertString(_T("CandidateNum")), LVCFMT_LEFT, 130, -1);

	GetDlgItem(IDC_BUTTON_STOPVIEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STARTVIEW)->EnableWindow(TRUE);

	return;
}

void CPreviewDlg::Clean()
{
	//先删除所有的列
	int nItemCount = m_lsEvent.GetItemCount();
	int i = 0;
	for (i = 0 ; i < nItemCount; i++)
	{
		char* szGUID = (char*)(m_lsEvent.GetItemData(i));
		if (NULL != szGUID)
		{
			delete[] szGUID;
		}
	}
	m_lsEvent.DeleteAllItems();
	while(m_lsEvent.DeleteColumn(0)){}

	EnterCriticalSection(&m_csAlarmItems);
	std::list<AlarmItem*>::iterator iter = m_lsAlarmItems.begin();
	for (; iter != m_lsAlarmItems.end(); )
	{
		AlarmItem* pAlarmItem = (AlarmItem*)(*iter);
		delete pAlarmItem;
		m_lsAlarmItems.erase(iter++);
	}
	LeaveCriticalSection(&m_csAlarmItems);

	if (m_lRealPlayHandle != 0)
	{
		BOOL bRet = CLIENT_StopRealPlayEx(m_lRealPlayHandle);
		if (!bRet)
		{
			MessageBox(ConvertString("stop real play failed"), ConvertString("Prompt"));
		}
		m_lRealPlayHandle = 0;
	}

	if (m_pAlarmShow)
	{
		m_pAlarmShow->ClearShow();
	}
}

void CPreviewDlg::SetChannelCount(int nChannel)
{
	m_nChannelCount = nChannel;
	
	char szBuf[16] = {0};
	int nIndex = 0;
	m_cbChannel.ResetContent();
	for (int i = 0; i < m_nChannelCount; i++)
	{
		CString strName = ConvertString("channel") + itoa(i, szBuf, 10);
		nIndex = m_cbChannel.AddString(strName);
		m_cbChannel.SetItemData(nIndex, i);
	}
	m_cbChannel.SetCurSel(0);

	return;
}

void CPreviewDlg::ShowAlarmInfo(DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize)
{
	if (dwAlarmType == EVENT_IVS_FACERECOGNITION)
	{
		EventData* pEventData = new EventData;
		pEventData->dwAlarmType = dwAlarmType;

		pEventData->pAlarmInfo = new DEV_EVENT_FACERECOGNITION_INFO;
		memset(pEventData->pAlarmInfo, 0, sizeof(DEV_EVENT_FACERECOGNITION_INFO));
		memcpy(pEventData->pAlarmInfo, pAlarmInfo, sizeof(DEV_EVENT_FACERECOGNITION_INFO));

		pEventData->pBuffer = new BYTE[dwBufSize];
		memcpy(pEventData->pBuffer, pBuffer, dwBufSize * sizeof(BYTE));
		pEventData->dwBufSize = dwBufSize;
		
		HWND hwnd = this->GetSafeHwnd();
		::PostMessage(hwnd, WM_USER_DELET_EVENTLIST_EXCEEDITEM, (DWORD)pEventData, 0);
	}


	
}

LRESULT CPreviewDlg::OnDeletExceededItems(WPARAM wParam, LPARAM lParam)
{
	EventData* pEventData = (EventData*)wParam;
	if (NULL != pEventData)
	{
		this->ShowEventInfo(pEventData->dwAlarmType, pEventData->pAlarmInfo, pEventData->pBuffer, pEventData->dwBufSize);
		if (NULL != pEventData->pAlarmInfo)
		{
			DEV_EVENT_FACERECOGNITION_INFO *pAlarmInfo = (DEV_EVENT_FACERECOGNITION_INFO*)pEventData->pAlarmInfo;
			delete pAlarmInfo;
		}

		if (NULL != pEventData->pBuffer)
		{
			delete []pEventData->pBuffer;
		}
		
		delete pEventData;
	}


	return 0;
}

void CPreviewDlg::ShowEventInfo(DWORD dwAlarmType, void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize)
{
	if (dwAlarmType == EVENT_IVS_FACERECOGNITION)
	{
		DEV_EVENT_FACERECOGNITION_INFO* pFaceRecognitionInfo = (DEV_EVENT_FACERECOGNITION_INFO*)pAlarmInfo;
		
		int nItemIndex = 0; 
		
		// ChannelID
		char szBuf[16] = {0};
		CString strChannel = ConvertString("channel") + itoa(pFaceRecognitionInfo->nChannelID, szBuf, 10);
		nItemIndex = m_lsEvent.InsertItem(LVIF_TEXT|LVIF_STATE,0, strChannel, 0,LVIS_SELECTED,0,0);
		
		// RuleName
		m_lsEvent.SetItemText(0, 1, pFaceRecognitionInfo->szName);
		
		// TriggerTime
		CString strTime;
		strTime.Format(_T("%04d%02d%02d%02d%02d%02d"), 
			pFaceRecognitionInfo->UTC.dwYear,
			pFaceRecognitionInfo->UTC.dwMonth,
			pFaceRecognitionInfo->UTC.dwDay,
			pFaceRecognitionInfo->UTC.dwHour,
			pFaceRecognitionInfo->UTC.dwMinute,
			pFaceRecognitionInfo->UTC.dwSecond);
		m_lsEvent.SetItemText(0, 2, strTime);
		
		// cadidate number
		CString strCadidateNum;
		strCadidateNum.Format("%d", pFaceRecognitionInfo->nCandidateNum);
		m_lsEvent.SetItemText(0, 3, strCadidateNum);
		
		//save alarm info
		GUID guid = {0};
		HRESULT hr =  CoCreateGuid(&guid);	
		CString strGuid = GuidToString(guid);
		CString strFolder = GetDataFolder();
		CString strPicFile = strFolder + strTime + strGuid;
		SaveAlarmInfo(pAlarmInfo, pBuffer, dwBufSize, strPicFile,strGuid);
		
		// show pictures
		if (NULL != m_pAlarmShow)
		{
			m_pAlarmShow->ShowAlarmInfo(strPicFile, pFaceRecognitionInfo);
		}
		
		//
		char* szGuid = new char[64];
		strncpy(szGuid, (LPSTR)(LPCTSTR)strGuid, 64);
		m_lsEvent.SetItemData(nItemIndex, (DWORD)szGuid);
	}

	while(m_lsEvent.GetItemCount() > MAX_EVENT_LIST_NUM)
	{
		int nIndex = m_lsEvent.GetItemCount() - 1;
		char* szGuid = (char*)m_lsEvent.GetItemData(nIndex);
		m_lsEvent.SetItemData(nIndex, 0);
		m_lsEvent.DeleteItem(nIndex);
		
		// 删除对应报警信息
		EnterCriticalSection(&m_csAlarmItems);
		std::list<AlarmItem*>::iterator iter = m_lsAlarmItems.begin();
		for (; iter != m_lsAlarmItems.end(); )
		{
			AlarmItem* pAlarmItem = (AlarmItem*)(*iter);
			CString strGuid = szGuid;
			if(strGuid == pAlarmItem->strGuid)
			{
				delete pAlarmItem;
				m_lsAlarmItems.erase(iter++);
				break;
			}
		}
		LeaveCriticalSection(&m_csAlarmItems);

		if (szGuid != NULL)
		{
			delete []szGuid;
		}
	}
}

void CPreviewDlg::SaveAlarmInfo(void* pAlarmInfo, BYTE *pBuffer, DWORD dwBufSize, CString strFilePreName, CString strGuid)
{
	
	AlarmItem* pAlarmItem = new AlarmItem;
	memcpy(&(pAlarmItem->stAlarmInfo), pAlarmInfo, sizeof(pAlarmItem->stAlarmInfo));
	pAlarmItem->strFilePre = strFilePreName;
	pAlarmItem->strGuid = strGuid;

	EnterCriticalSection(&m_csAlarmItems);
	m_lsAlarmItems.push_back(pAlarmItem);
	LeaveCriticalSection(&m_csAlarmItems);

	//save picture
	int nOffSet = 0;
	int nFileLenth = 0;

	// src picture
	CString strFileSrc = strFilePreName + SRCFILE + ".jpg";
	FILE* fpSrcPic = fopen((LPSTR)(LPCTSTR)strFileSrc,"wb");
	if (fpSrcPic != NULL)
	{
		nOffSet = pAlarmItem->stAlarmInfo.stuObject.stPicInfo.dwOffSet;
		nFileLenth = pAlarmItem->stAlarmInfo.stuObject.stPicInfo.dwFileLenth;
		fwrite(pBuffer + nOffSet, 1, nFileLenth, fpSrcPic);
		fclose(fpSrcPic);
	}
	else
	{
		int nErr = GetLastError();
	}

	// match picture
	CString strFileMatch;
	FILE *fpMatchPic = NULL;
	for (int i = 0; i < pAlarmItem->stAlarmInfo.nCandidateNum; i++)
	{
		for (int j = 0; j < pAlarmItem->stAlarmInfo.stuCandidates[i].stPersonInfo.wFacePicNum; j++)
		{
			strFileMatch = strFilePreName + MATCHFILE + I2Str(i) + "_" + I2Str(j) + ".jpg";
			fpMatchPic = NULL;
			fpMatchPic = fopen((LPSTR)(LPCTSTR)strFileMatch,"wb");
			if (fpMatchPic != NULL)
			{
				nOffSet = pAlarmItem->stAlarmInfo.stuCandidates[i].stPersonInfo.szFacePicInfo[j].dwOffSet;
				nFileLenth = pAlarmItem->stAlarmInfo.stuCandidates[i].stPersonInfo.szFacePicInfo[j].dwFileLenth;
				fwrite(pBuffer + nOffSet, 1, nFileLenth, fpMatchPic);
				fclose(fpMatchPic);
			}
		}


	}
}

CString CPreviewDlg::GetDataFolder()
{
	char szFolder[256] = {0};

	bool bRet = GetModulePath("dhnetsdk.dll", szFolder);
	if (bRet)
	{
		sprintf(szFolder+strlen(szFolder), PICDIR);
	}

	return CString(szFolder);
}

void CPreviewDlg::OnClickListEvent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	if (phdn->iItem == -1)
	{
		return;
	}
	int newIndex = phdn->iItem;

	char* pGuid = (char*)m_lsEvent.GetItemData(newIndex);

	ShowItemInfo(pGuid);
	
	*pResult = 0;
}

void CPreviewDlg::ShowItemInfo(char* pGuid)
{
	if (pGuid == NULL)
	{
		return;
	}

	std::list<AlarmItem*>::iterator iter = m_lsAlarmItems.begin();
	for (; iter != m_lsAlarmItems.end(); iter++)
	{
		if (_stricmp(pGuid, (LPSTR)(LPCTSTR)(*iter)->strGuid) == 0)
		{
			break;
		}
	}

	if (iter != m_lsAlarmItems.end() && m_pAlarmShow != NULL)
	{
		m_pAlarmShow->ShowAlarmInfo((*iter)->strFilePre, &((*iter)->stAlarmInfo));
	}
}
