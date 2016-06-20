// Alarm.cpp : implementation file
//

#include "stdafx.h"
#include "DemoIVSb.h"
#include "Alarm.h"
#include "DemoIVSbDlg.h"
#include "Preview.h"

#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************************************************/
/*WM_USER_ALAMR_COME的消息函数                                          */
/************************************************************************/
LRESULT CAlarm::OnAlarmCome(WPARAM wParam, LPARAM lParam)
{
	if (!wParam)
	{
		return 0;
	}

	EventPara* ep = (EventPara*)wParam;
	LONG lAnalyzerHandle = ep->lAnalyzerHandle;
	DWORD dwAlarmType = ep->dwAlarmType;
	void* pAlarmInfo = ep->pAlarmInfo;
	DWORD dwBufSize = ep->dwBufSize;
	BYTE* pBuffer = ep->pBuffer;
	int nSequence = ep->nSequence;
	
	AlarmInfoNode* pNode = new AlarmInfoNode;
	if (!pNode || !ep->pAlarmInfo || !ep->pBuffer)
	{
		if (ep)
		{
			if (ep->pBuffer)
			{
				delete []ep->pBuffer;
				ep->pBuffer = NULL;
			}
			
			if (ep->pAlarmInfo)
			{
				delete []ep->pAlarmInfo;
				ep->pAlarmInfo = NULL;
			}
			
			delete ep;
			ep = NULL;
		}
		return 0;
	}
	//所有的结构体的前面的5个成员都是一样的，可以统一的获取时间
	DEV_EVENT_CROSSLINE_INFO* pInfo = (DEV_EVENT_CROSSLINE_INFO*)ep->pAlarmInfo;
	
	//1 获取该事件来自的通道号
	pNode->nChnNum = pInfo->nChannelID;

	//获取事件名称
	strncpy(pNode->szAlarmName, pInfo->szName, _countof(pInfo->szName));
	
	//2 获取事件类型
	pNode->dwRuleType = dwAlarmType;
	
	//3 获取事件触发时间
	memcpy(&pNode->Time, &pInfo->UTC, sizeof(pNode->Time));
	
	//4 存储图片到本地，将目录存在节点中
	TCHAR szModule[MAX_PATH] = {0};
	::GetCurrentDirectory(MAX_PATH, szModule);

	_sntprintf(szModule,
			   MAX_PATH,
			   _T("%s\\Snap"),
			   szModule);
	::CreateDirectory(szModule, NULL);

	_sntprintf(pNode->szFile,
				_countof(pNode->szFile),
				_T("%s\\Chn%02d %04d%02d%02d%02d%02d%02d.jpg"),
				szModule,
				pInfo->nChannelID + 1,
				pNode->Time.dwYear,
				pNode->Time.dwMonth,
				pNode->Time.dwDay,
				pNode->Time.dwHour,
				pNode->Time.dwMinute,
				pNode->Time.dwSecond);
	
	TCHAR szDebug[128] = {0};
	_sntprintf(szDebug, _countof(szDebug), _T("Alarm Come: Chn%02d Type%d\n"), pNode->nChnNum + 1, pNode->dwRuleType);
	::OutputDebugString(szDebug);

	FILE* pFile = fopen(pNode->szFile, "wb");
	if (pFile)
	{
		fwrite(pBuffer, dwBufSize, 1, pFile);
		fclose(pFile);
	}
	else
	{
		OutputDebugString(_T("Can't save file!\n"));
		delete pNode;
		if (ep)
		{
			if (ep->pBuffer)
			{
				delete []ep->pBuffer;
				ep->pBuffer = NULL;
			}

			if (ep->pAlarmInfo)
			{
				delete []ep->pAlarmInfo;
				ep->pAlarmInfo = NULL;
			}

			delete ep;
			ep = NULL;
		}

		return 0;
	}
	
	//将节点存入链表
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		lsAlarmInfo* plsAlarmInfo = pMainDlg->getAlarmInfoList();
		if (plsAlarmInfo)
		{
			plsAlarmInfo->push_back(pNode);
		}

		//TODO实时在Preview窗口里显示对应通道的报警信息
		pMainDlg->m_pdlgPreview->insertAlarmInfo(pNode);
	}
		
	//TODO并且立即在Alarm窗口里满足窗口筛选条件下，显示报警信息
	lsAlarmInfo lsAlarm;
	lsAlarm.push_back(pNode);
	lsAlarm = showAlarmByChannel(&lsAlarm);
	if (!lsAlarm.size())
	{
		if (ep)
		{
			if (ep->pBuffer)
			{
				delete []ep->pBuffer;
				ep->pBuffer = NULL;
			}
			
			if (ep->pAlarmInfo)
			{
				delete []ep->pAlarmInfo;
				ep->pAlarmInfo = NULL;
			}
			
			delete ep;
			ep = NULL;
		}
		return 0;
	}
	
	lsAlarm = showAlarmByTime(&lsAlarm);
	if (!lsAlarm.size())
	{
		if (ep)
		{
			if (ep->pBuffer)
			{
				delete []ep->pBuffer;
				ep->pBuffer = NULL;
			}
			
			if (ep->pAlarmInfo)
			{
				delete []ep->pAlarmInfo;
				ep->pAlarmInfo = NULL;
			}
			
			delete ep;
			ep = NULL;
		}
		return 0;
	}

	lsAlarm = showAlarmByRuleType(&lsAlarm);
	if (!lsAlarm.size())
	{
		if (ep)
		{
			if (ep->pBuffer)
			{
				delete []ep->pBuffer;
				ep->pBuffer = NULL;
			}
			
			if (ep->pAlarmInfo)
			{
				delete []ep->pAlarmInfo;
				ep->pAlarmInfo = NULL;
			}
			
			delete ep;
			ep = NULL;
		}
		return 0;
	}
		
	while(lsAlarm.size())
	{
		insertAlarmInfo(lsAlarm.front());
		lsAlarm.pop_front();
	}
	
	if (ep)
	{
		if (ep->pBuffer)
		{
			delete []ep->pBuffer;
			ep->pBuffer = NULL;
		}
		
		if (ep->pAlarmInfo)
		{
			delete []ep->pAlarmInfo;
			ep->pAlarmInfo = NULL;
		}
		
		delete ep;
		ep = NULL;
	}
	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CAlarm dialog


CAlarm::CAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarm)
	//}}AFX_DATA_INIT
}


void CAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarm)
	DDX_Control(pDX, IDC_ALARM_DTP_STARTTIME, m_dtpStartTime);
	DDX_Control(pDX, IDC_ALARM_DTP_STARTDATE, m_dtpStartDate);
	DDX_Control(pDX, IDC_ALARM_DTP_ENDTIME, m_dtpEndTime);
	DDX_Control(pDX, IDC_ALARM_DTP_ENDDATE, m_dtpEndDate);
	DDX_Control(pDX, IDC_ALARM_TREE_RULESEL, m_treeRuleType);
	DDX_Control(pDX, IDC_ALARM_LIST_ALARMINFO, m_lsAlarmInfo);
	DDX_Control(pDX, IDC_ALARM_CMB_CHANNEL, m_cmbChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarm, CDialog)
	//{{AFX_MSG_MAP(CAlarm)
	ON_CBN_SELCHANGE(IDC_ALARM_CMB_CHANNEL, OnSelchangeAlarmCmbChannel)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_ALARM_DTP_STARTDATE, OnDatetimechangeAlarmDtpStartdate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_ALARM_DTP_STARTTIME, OnDatetimechangeAlarmDtpStarttime)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_ALARM_DTP_ENDDATE, OnDatetimechangeAlarmDtpEnddate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_ALARM_DTP_ENDTIME, OnDatetimechangeAlarmDtpEndtime)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_ALARM_LIST_ALARMINFO, OnDblclkAlarmListAlarminfo)
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_CLICK, IDC_ALARM_TREE_RULESEL, OnClickAlarmTreeRulesel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_ALAMR_COME, OnAlarmCome)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarm message handlers

BOOL CAlarm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	g_SetWndStaticText(this);

	m_treeRuleType.ModifyStyle(TVS_CHECKBOXES, 0, 0);
	m_treeRuleType.ModifyStyle(0, TVS_CHECKBOXES, 0);

	m_lsAlarmInfo.SetExtendedStyle(m_lsAlarmInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_lsAlarmInfo.InsertColumn(0, ConvertString(_T("ChannelID")), LVCFMT_LEFT, 80, -1);
	m_lsAlarmInfo.InsertColumn(1, ConvertString(_T("EventType")), LVCFMT_LEFT, 100, -1);
	m_lsAlarmInfo.InsertColumn(2, ConvertString(_T("TriggerTime")), LVCFMT_LEFT, 100, -1);
	m_lsAlarmInfo.InsertColumn(3, ConvertString(_T("RuleName")), LVCFMT_LEFT, 80, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/*
 *	
 */
void CAlarm::initAlarmDlg(int nChnCount)
{
	if (!nChnCount)
	{
		return;
	}

	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	SYSTEMTIME stEndDate;
	m_dtpEndDate.GetTime(&stEndDate);

	stEndDate.wDay += 1;
	m_dtpEndTime.SetTime(&stEndDate);


	//清空事件类型树
	m_treeRuleType.DeleteAllItems();

	//清空组合框
	m_cmbChannel.ResetContent();
	
	TCHAR szItem[16] = {0};
	for (int i = 0; i < nChnCount; i++)
	{
		_sntprintf(szItem, _countof(szItem), _T("%s%02d"), ConvertString(_T("Channel")), i + 1);
		m_cmbChannel.InsertString(i, szItem);
		ZeroMemory(szItem, _countof(szItem));
	}
	
	m_cmbChannel.SetCurSel(0);
	
	//清空报警信息表格
	m_lsAlarmInfo.DeleteAllItems();
	

	//初始化事件类型树控件
	if (pMainDlg->getCurrentChannel() >= 0)
	{
		int nChnNum = pMainDlg->getCurrentChannel();
		CFG_CAP_ANALYSE_INFO* pCapInfo = pMainDlg->getCapAnalyseInfo(nChnNum);
		CFG_ANALYSEGLOBAL_INFO* pGlobalInfo = pMainDlg->getAnalyseGlobalInfo(nChnNum);
		if (!pCapInfo || !pGlobalInfo)
		{
			return;
		}

		int i = 0;
		BOOL bRet = FALSE;

		for (i = 0; i < pCapInfo->nSupportedSceneNum; i++)
		{
			if (strcmp(pGlobalInfo->szSceneType,
					   pCapInfo->stSupportScenes.stScenes[i].szSceneName) == 0)
			{
				bRet = TRUE;
				break;
			}
		}

		if (!bRet)
		{
			return;
		}

		for (int j = 0; j < pCapInfo->stSupportScenes.stScenes[i].nSupportRules; j++)
		{
			DWORD dwType = pCapInfo->stSupportScenes.stScenes[i].stSpportRules[j].dwSupportedRule;
			CString strName = g_convertRuleTypeToString(dwType);
			HTREEITEM hItem = m_treeRuleType.InsertItem(strName);
			m_treeRuleType.SetItemData(hItem, dwType);
			m_treeRuleType.SetCheck(hItem);
		}
	}
}
/*
 *	
 */
void CAlarm::uninitAlarmDlg()
{
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (pMainDlg)
	{
		pMainDlg->stopAlarmCallBack();
	}

	m_lsAlarmInfo.DeleteAllItems();
	m_cmbChannel.ResetContent();
	m_treeRuleType.DeleteAllItems();
}
/*
 *	按照当前选择的通道号来选择筛选报警信息
 */
lsAlarmInfo CAlarm::showAlarmByChannel(lsAlarmInfo* plsAlarmInfo)
{
	lsAlarmInfo lsAInfo;
	
	if (!plsAlarmInfo->size())// || m_cmbChannel.GetCurSel() < 0)
	{
		return lsAInfo;
	}

	int nChnNum = m_cmbChannel.GetCurSel();
	
	lsAlarmInfo::iterator it = plsAlarmInfo->begin();
	for (; it != plsAlarmInfo->end(); ++it)
	{
		AlarmInfoNode* pAlarmNode = (AlarmInfoNode*)*it;
		if (pAlarmNode->nChnNum == nChnNum)
		{
			lsAInfo.push_back(pAlarmNode);
		}
	}

	return lsAInfo;
}
/*
 *	按照当前选择的时间区间来筛选报警信息
 */
lsAlarmInfo CAlarm::showAlarmByTime(lsAlarmInfo* plsAlarmInfo)
{
	lsAlarmInfo lsAInfo;

	if (!plsAlarmInfo)
	{
		return lsAInfo;
	}

	
	CTime ctStartData, ctEndDate, ctStartTime, ctEndTime;
	m_dtpStartDate.GetTime(ctStartData);
	m_dtpEndDate.GetTime(ctEndDate);
	m_dtpStartTime.GetTime(ctStartTime);
	m_dtpEndTime.GetTime(ctEndTime);
	
	CTime ctStart(ctStartData.GetYear(),
				ctStartData.GetMonth(),
				ctStartData.GetDay(),
				ctStartTime.GetHour(),
				ctStartTime.GetMinute(),
				ctStartTime.GetSecond());
	CTime ctEnd(ctEndDate.GetYear(),
				ctEndDate.GetMonth(),
				ctEndDate.GetDay(),
				ctEndTime.GetHour(),
				ctEndTime.GetMinute(),
				ctEndTime.GetSecond());

	SYSTEMTIME stStart, stEnd;
	ctStart.GetAsSystemTime(stStart);
	ctEnd.GetAsSystemTime(stEnd);
	
	if (ctStart >= ctEnd)
	{
		return lsAInfo;
	}

	if (lsAInfo.size())
	{
		//已经过其他条件筛选
		lsAlarmInfo::iterator it = lsAInfo.begin();
		for (; it != lsAInfo.end(); ++it)
		{
			AlarmInfoNode* pAlarmNode = (AlarmInfoNode*)*it;
			CTime ctNode(pAlarmNode->Time.dwYear,
						pAlarmNode->Time.dwMonth,
						pAlarmNode->Time.dwDay,
						pAlarmNode->Time.dwHour,
						pAlarmNode->Time.dwMinute,
						pAlarmNode->Time.dwSecond);
			if (ctNode > ctEnd || ctNode < ctStart)
			{
				lsAInfo.erase(it);
			}				
		}
	}
	else
	{
		//未经过其他条件筛选
		lsAlarmInfo::iterator it = plsAlarmInfo->begin();
		for(; it != plsAlarmInfo->end(); ++it)
		{
			AlarmInfoNode* pAlarmNode = (AlarmInfoNode*)*it;
			CTime ctNode(pAlarmNode->Time.dwYear,
				pAlarmNode->Time.dwMonth,
				pAlarmNode->Time.dwDay,
				pAlarmNode->Time.dwHour,
				pAlarmNode->Time.dwMinute,
				pAlarmNode->Time.dwSecond);
			if (ctNode <= ctEnd && ctNode >= ctStart)
			{
				lsAInfo.push_back(pAlarmNode);
			}
		}
	}

	return lsAInfo;
}
/*
 *	按照事件类型来筛选报警信息
 */
lsAlarmInfo CAlarm::showAlarmByRuleType(lsAlarmInfo* plsAlarmInfo)
{
	lsAlarmInfo lsAInfo;
	if (!plsAlarmInfo)
	{
		return lsAInfo;
	}

	while(plsAlarmInfo->size())
	{
		AlarmInfoNode* pNode = plsAlarmInfo->front();

		HTREEITEM hItem = m_treeRuleType.GetRootItem();
		while(hItem)
		{
			if (m_treeRuleType.GetItemData(hItem) == pNode->dwRuleType
				&& m_treeRuleType.GetCheck(hItem))
			{
				lsAInfo.push_back(pNode);
				break;
			}

			hItem = m_treeRuleType.GetNextSiblingItem(hItem);
		}

		plsAlarmInfo->pop_front();
	}

	return lsAInfo;
}
/*
 *	
 */
void CAlarm::insertAlarmInfo(AlarmInfoNode* pAlarmInfoNode)
{
	if (!pAlarmInfoNode)
	{
		return;
	}

	int nCount = m_lsAlarmInfo.GetItemCount();
	m_lsAlarmInfo.InsertItem(nCount, _T(""));
	
	CString strTmp;
	strTmp.Format(_T("%s%02d"), ConvertString(_T("Channel")), pAlarmInfoNode->nChnNum + 1);
	m_lsAlarmInfo.SetItemText(nCount, 0, strTmp);
	strTmp.Empty();
	
	strTmp = g_convertRuleTypeToString(pAlarmInfoNode->dwRuleType);
	m_lsAlarmInfo.SetItemText(nCount, 1, strTmp);
	strTmp.Empty();
	
	strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), 
				pAlarmInfoNode->Time.dwYear,
				pAlarmInfoNode->Time.dwMonth,
				pAlarmInfoNode->Time.dwDay,
				pAlarmInfoNode->Time.dwHour,
				pAlarmInfoNode->Time.dwMinute,
				pAlarmInfoNode->Time.dwSecond);
	m_lsAlarmInfo.SetItemText(nCount, 2, strTmp);
	strTmp.Empty();

	m_lsAlarmInfo.SetItemText(nCount, 3, pAlarmInfoNode->szAlarmName);
	
	m_lsAlarmInfo.SetItemData(nCount, (DWORD)pAlarmInfoNode);
}
/*
 *	
 */
void CAlarm::clearAllAlarmInfo()
{
	m_lsAlarmInfo.DeleteAllItems();
}

void CAlarm::showAlarmInfo()
{
	OnSelchangeAlarmCmbChannel();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CAlarm::OnSelchangeAlarmCmbChannel() 
{
	// TODO: Add your control notification handler code here
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}

	clearAllAlarmInfo();
	lsAlarmInfo lsAlarm = showAlarmByChannel(pMainDlg->getAlarmInfoList());
	if (!lsAlarm.size())
	{
		return;
	}

	lsAlarm = showAlarmByTime(&lsAlarm);
	if (!lsAlarm.size())
	{
		return;
	}

	lsAlarm = showAlarmByRuleType(&lsAlarm);	
	while(lsAlarm.size())
	{
		insertAlarmInfo(lsAlarm.front());
		lsAlarm.pop_front();
	}
}

void CAlarm::OnDatetimechangeAlarmDtpStartdate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	OnSelchangeAlarmCmbChannel();
}

void CAlarm::OnDatetimechangeAlarmDtpStarttime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	OnSelchangeAlarmCmbChannel();
}

void CAlarm::OnDatetimechangeAlarmDtpEnddate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	OnSelchangeAlarmCmbChannel();
}

void CAlarm::OnDatetimechangeAlarmDtpEndtime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	OnSelchangeAlarmCmbChannel();
}

void CAlarm::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	//首先在主窗口停止报警回调，然后析构本窗口
	uninitAlarmDlg();
}
/*
 *	
 */
void CAlarm::OnDblclkAlarmListAlarminfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	CPoint pt;
	GetCursorPos(&pt);
	m_lsAlarmInfo.ScreenToClient(&pt);

	int nItem = m_lsAlarmInfo.HitTest(pt);
	if (-1 == nItem)
	{
		return;
	}

	AlarmInfoNode* pAlarmInfo = (AlarmInfoNode*)m_lsAlarmInfo.GetItemData(nItem);
	if (!pAlarmInfo)
	{
		return;
	}
	
	USES_CONVERSION;
	IPicture* pPic = NULL;
	HRESULT hr = S_FALSE;
	BOOL bRet = FALSE;

	//装载图片
	hr = OleLoadPicturePath(T2OLE(pAlarmInfo->szFile), NULL, 0, RGB(255, 255, 255), IID_IPicture, (LPVOID*)&pPic);
	if (FAILED(hr) || !pPic)
	{
		OutputDebugString("OleLoadPicturePath load image failed\n");
		return;
	}

	//显示全图
	OLE_XSIZE_HIMETRIC hmWidth; 
	OLE_YSIZE_HIMETRIC hmHeight; 
	pPic->get_Width(&hmWidth); 
	pPic->get_Height(&hmHeight);
	
	RECT rect;
	GetDlgItem(IDC_ALARM_STATIC_VIEW)->GetWindowRect(&rect);

	hr = pPic->Render(*(GetDlgItem(IDC_ALARM_STATIC_VIEW)->GetDC()), 
					  0, 
					  0, 
					  rect.right - rect.left, 
					  rect.bottom - rect.top, 
					  0, 
					  hmHeight, 
					  hmWidth, 
					  -hmHeight, 
					  NULL);
	if (FAILED(hr))
	{
		OutputDebugString("Render image failed\n"); 
	}
}

void CAlarm::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SYSTEMTIME st;
	m_dtpEndDate.GetTime(&st);

	st.wDay += 1;
	m_dtpEndDate.SetTime(&st);

	CDialog::OnLButtonUp(nFlags, point);
}

void CAlarm::OnClickAlarmTreeRulesel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	CPoint pt;
	GetCursorPos(&pt);
	m_treeRuleType.ScreenToClient(&pt);
	
	UINT uiFlag = -1;
	HTREEITEM hHitItem = m_treeRuleType.HitTest(pt, &uiFlag);
	if (!hHitItem)
	{
		return;
	}
	
	CDemoIVSbDlg* pMainDlg = (CDemoIVSbDlg*)AfxGetMainWnd();
	if (!pMainDlg)
	{
		return;
	}
	
	clearAllAlarmInfo();
	lsAlarmInfo lsAlarm = showAlarmByChannel(pMainDlg->getAlarmInfoList());
	if (!lsAlarm.size())
	{
		return;
	}
	
	lsAlarm = showAlarmByTime(&lsAlarm);
	if (!lsAlarm.size())
	{
		return;
	}
	//
	m_treeRuleType.SelectItem(hHitItem);
	
	BOOL bCheck = FALSE;
	
	if (uiFlag & TVHT_ONITEMSTATEICON)
	{
		if (m_treeRuleType.GetCheck(hHitItem) != 0)
		{
			//turn to false
		}
		else
		{
			//turn to true
			bCheck = TRUE;
		}
	} 
	else
	{
		if (m_treeRuleType.GetCheck(hHitItem) != 0)
		{
			bCheck = TRUE;
		} 
		else
		{
			bCheck = FALSE;
		}
	}
	
	BOOL bRet = FALSE;
	lsAlarmInfo::iterator it = lsAlarm.begin();
	while(it != lsAlarm.end())
	{
		AlarmInfoNode* pNode = *it;
		if (!pNode)
		{
			lsAlarm.erase(it++);
			continue;
		}

		bRet = FALSE;
		
		HTREEITEM hItem = m_treeRuleType.GetRootItem();
		while(hItem)
		{
			if (hItem == hHitItem)
			{
				if (pNode->dwRuleType == m_treeRuleType.GetItemData(hHitItem)
					&& (bCheck == FALSE))
				{
					lsAlarm.erase(it++);
					bRet = TRUE;
					break;
				} 
			} 
			else
			{
				if (pNode->dwRuleType == m_treeRuleType.GetItemData(hItem)
					&& (m_treeRuleType.GetCheck(hItem) == FALSE))
				{
					lsAlarm.erase(it++);
					bRet = TRUE;
					break;
				} 
			}
			
			hItem = m_treeRuleType.GetNextSiblingItem(hItem);
		}

		if (!bRet)
		{
			it++;
		}
	}

	while(lsAlarm.size())
	{
		insertAlarmInfo(lsAlarm.front());
		lsAlarm.pop_front();
	}
}
