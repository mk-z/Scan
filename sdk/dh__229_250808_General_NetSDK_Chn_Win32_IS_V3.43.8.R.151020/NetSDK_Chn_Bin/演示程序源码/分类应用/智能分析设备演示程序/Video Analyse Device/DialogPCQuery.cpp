// DialogPCQuery.cpp : implementation file
//

#include "stdafx.h"
#include "Real Load Picture.h"
#include "DialogPCQuery.h"
#include "Utility.h"
#include "DialogEventRule.h"

#include <math.h>
#include <assert.h>

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern const int EVENT_TYPE_COUNT = 26;
extern char* strAlarmList[EVENT_TYPE_COUNT];
extern int nAlarmTypeList[EVENT_TYPE_COUNT];

/////////////////////////////////////////////////////////////////////////////
// CDialogPCQuery dialog


CDialogPCQuery::CDialogPCQuery(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPCQuery::IDD, pParent)
{
	m_pLoadPicDlg = NULL;
	m_nCurSel = -1;
	m_curPage = 0;
	m_szBmpBuffer = new char[1024 * 1024 * 5];//最大5M
	m_dwBmpBufferSize = 0;

	m_hBitmap = 0;
	m_MemDC = NULL;
	m_ClientDC = NULL;
	m_nWidth = 0;
	m_nHeight = 0;
	ZeroMemory(&m_rect, sizeof(RECT));

	m_Font = new CFont;

	//{{AFX_DATA_INIT(CDialogPCQuery)
	m_dateS = COleDateTime::GetCurrentTime();
	m_timeE = COleDateTime::GetCurrentTime();
	m_timeS = COleDateTime::GetCurrentTime();
	m_dateE = COleDateTime::GetCurrentTime();
	m_csLP = _T("");
	m_speedLow = 0;
	m_speedUper = 0;
	m_lane = 0;
	//}}AFX_DATA_INIT
}

CDialogPCQuery::~CDialogPCQuery()
{
	//清空查询结果
	ClearQueryResultData();

	m_Font->DeleteObject();
	delete m_Font;

	delete[] m_szBmpBuffer;
	delete m_ClientDC;
	delete m_MemDC;
}


void CDialogPCQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPCQuery)
	DDX_Control(pDX, IDC_CHECK_STATE, m_ckState);
	DDX_Control(pDX, IDC_COMBO_QSTATE, m_cbQState);
	DDX_Control(pDX, IDC_LIST_RESULT, m_lcResult);
	DDX_DateTimeCtrl(pDX, IDC_DATE_S, m_dateS);
	DDX_DateTimeCtrl(pDX, IDC_TIME_E, m_timeE);
	DDX_DateTimeCtrl(pDX, IDC_TIME_S, m_timeS);
	DDX_DateTimeCtrl(pDX, IDC_DATE_E, m_dateE);
	DDX_Text(pDX, IDC_EDIT_LP, m_csLP);
	DDX_Text(pDX, IDC_EDIT_SPEED_LOW, m_speedLow);
	DDX_Text(pDX, IDC_EDIT_SPEED_UPER, m_speedUper);
	DDX_Text(pDX, IDC_EDIT_LANE, m_lane);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_stuShowBmp);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogPCQuery, CDialog)
	//{{AFX_MSG_MAP(CDialogPCQuery)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESULT, OnClickListResult)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SEL_ALL, OnButtonSelAll)
	ON_BN_CLICKED(IDC_BUTTON_ANTI_SEL, OnButtonAntiSel)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_RESULT, OnKeydownListResult)
	ON_BN_CLICKED(IDC_CHECK_HIDE_NO_LP, OnCheckHideNoLp)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnCbnSelchangeComboType)
	ON_BN_CLICKED(IDC_BUTTON_NEXT_PAGE,		OnBnClickedButtonNextPage)
	ON_BN_CLICKED(IDC_BUTTON_PRE_PAGE,		OnBnClickedButtonPrePage)
	ON_BN_CLICKED(IDC_BUTTON_LAST_PAGE,		OnBnClickedButtonLastPage)
	ON_BN_CLICKED(IDC_BUTTON_FIRST_PAGE,	OnBnClickedButtonFirstPage)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_PIC, OnButtonOpenPic)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPCQuery message handlers

BOOL CDialogPCQuery::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//更新分页字符串
	UpdatePageStr();

	//读取数据文件夹的位置
	string strDataFilePath = GetDataFolder().append(PC_DATA_STORE_FILE);
	
	//读取数据
	FILE* fp = fopen(strDataFilePath.c_str(), "rb");
	if (fp != NULL)
	{
		char szGUID[MAX_GUID_LEN+1] = {0};
		int type = 0;
		int len = 0;
		int checkFlag = 0;
		while(!feof(fp))
		{
			size_t readBytes = 0;
			readBytes = fread(szGUID, 1, MAX_GUID_LEN, fp);
			if (readBytes != MAX_GUID_LEN)
			{
				break;
			}
			readBytes = fread(&type, 1, 4, fp);
			if (readBytes != 4)
			{
				break;
			}

			readBytes = fread(&len, 1, 4, fp);
			if (readBytes != 4)
			{
				break;
			}
			char* info = new char[len];
			ZeroMemory(info, len);
			readBytes = fread(info, 1, len, fp);
			if (readBytes != len)
			{
                delete[] info;
				break;
			}
			readBytes = fread(&checkFlag, 1, 4, fp);
			if (readBytes != 4)
			{
                delete[] info;
				break;
			}

 			ALARM_ITEM item;
 			item.nAlarmType = type;
 			item.nLen = len;
			item.nCheckFlag = checkFlag;
 			item.pAlarmInfo = info;
 			item.strGUID = std::string(szGUID);

			//在这里检查图片，如果记录对应的图片已经不存在了，那么该记录就不装载了
			BOOL bPicExist = IsPicOfRecordExist(szGUID);
			if (bPicExist)
			{
				m_mapAllAlarmItem.insert(std::pair<std::string, ALARM_ITEM>(std::string(szGUID), item));
			}
		}
		fclose(fp);
	}

	//UI中文支持
	g_SetWndStaticText(this);
	
	//设置牌照的字体
	if (NULL != m_Font)
	{
		m_Font->CreateFont(70, 0, 0, 0, 700, 
			FALSE, 
			FALSE,
			0, 
			DEFAULT_CHARSET, 
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, 
			DEFAULT_PITCH | FF_MODERN, 
			"宋体" );
		GetDlgItem(IDC_STATIC_LP)->SetFont(m_Font);
		GetDlgItem(IDC_STATIC_STATE)->SetFont(m_Font);
	}

	//列表框的风格
	m_lcResult.SetExtendedStyle(m_lcResult.GetExtendedStyle()|LVS_EX_FULLROWSELECT); 
	m_lcResult.SetExtendedStyle(m_lcResult.GetExtendedStyle()|LVS_EX_GRIDLINES); 
	m_lcResult.SetExtendedStyle(m_lcResult.GetExtendedStyle()|LVS_EX_CHECKBOXES);

	for (int i = 0; i < EVENT_TYPE_COUNT; i++)
	{
		//过滤条件
		if (i > 0)
		{
			m_cbType.AddString(ConvertString(strAlarmList[i]));
			m_cbType.SetItemData(i - 1, nAlarmTypeList[i]);
		}
	}
	//设置默认的选中项
	const int DEFAULT_SELECT_ITEM = EVENT_IVS_TRAFFICGATE;//如果要更改默认的选中项，修改这个值就可以了，不能选择EVENT_IVS_ALL
	int nSelectItemIndex = 0;
	int nItemCount = sizeof(nAlarmTypeList) / sizeof(nAlarmTypeList[0]);
	for (int j = 0; j < nItemCount; j++)
	{
		if (nAlarmTypeList[j] == DEFAULT_SELECT_ITEM)
		{
			nSelectItemIndex = j;
			break;
		}
	}
	m_cbType.SetCurSel(nSelectItemIndex - 1);
	DWORD dwAlarmType = m_cbType.GetItemData(nSelectItemIndex - 1);
	this->ChangeDisplayTitle(dwAlarmType);

	//State
	{
		for (int i = 0; i < LP_STATE_COUNT; i++)
		{
			m_cbQState.InsertString(i, I2State(i).c_str());
			m_cbQState.SetItemData(i, i);
		}
	}
	m_cbQState.SetCurSel(0);
	std::string strMsg = ConvertStr("Reocrd Count")			+std::string(":")+I2Str(0)	+std::string("  ")
						         + ConvertStr("Not Checked")			+std::string(":")+I2Str(0)	+std::string("  ")
						         + ConvertStr("Right")				+std::string(":")+I2Str(0)	+std::string("  ")
					 	         + ConvertStr("Wrong")				+std::string(":")+I2Str(0)	+std::string("  ")
						         + ConvertStr("No License Plate")		+std::string(":")+I2Str(0)	+std::string("  ")
						         + ConvertStr("Dirty License Plate")	+std::string(":")+I2Str(0)	+std::string("  ")
						         + ConvertStr("False Alarm")			+std::string(":")+I2Str(0)	+std::string("  ");
   GetDlgItem(IDC_STATIC_STAT)->SetWindowText(strMsg.c_str());

	// Pic control
	//m_cPictureWnd.Create(NULL, NULL, WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, 1981);
	//CRect screenRect;
	//GetDlgItem(IDC_STATIC_PICTURE)->GetWindowRect(&screenRect);
	//ScreenToClient(&screenRect);
	//m_cPictureWnd.MoveWindow(screenRect);
	//m_cPictureWnd.ShowWindow(SW_SHOW);

	//Timer
	//SetTimer(10000, 3000, NULL);
	return TRUE;
}

/************************************************************************/
/* 在所有结果集中添加一条记录                                           */
/************************************************************************/
void CDialogPCQuery::AddAlarm(ALARM_ITEM& item)
{
	m_mapAllAlarmItem.insert(std::pair<std::string, ALARM_ITEM>(std::string(item.strGUID), item));
}

/************************************************************************/
/* 通过GUID来获取所有记录中的一条记录                                   */
/************************************************************************/
ALARM_ITEM* CDialogPCQuery::GetAlarmItemByGUID(const char* szGUID)
{
	std::string strGUID(szGUID);
	AlarmMap::iterator iter = this->m_mapAllAlarmItem.find(strGUID);
	if ( iter != m_mapAllAlarmItem.end() )
	{
		return &(iter->second);
	}
	return NULL;
}

/************************************************************************/
/* 通过GUID来获取查询结果中的一条记录                                   */
/************************************************************************/
ALARM_ITEM* CDialogPCQuery::GetQuerryedAlarmItemByGUID(const char* szGUID)
{
	std::string strGUID(szGUID);
	AlarmMap::iterator iter = this->m_mapQueryResult.find(strGUID);
	if ( iter != m_mapQueryResult.end() )
	{
		return &(iter->second);
	}
	return NULL;
}

/************************************************************************/
/* 改变列表框的标题                                                     */
/************************************************************************/
void CDialogPCQuery::ChangeDisplayTitle(DWORD dwAlarmType)
{
	int nStructSize = 0;
	std::vector<ColDes> vTitle;
	BOOL bRet = GetStructInfo(dwAlarmType, NULL, GET_SI_TITLE, NULL, NULL, &vTitle, NULL);
	if (!bRet)
	{
		MessageBox(ConvertString("Alarm type not supported yet"), ConvertString("Prompt"));
		return;
	}
	//先删除所有的列
	int nItemCount = m_lcResult.GetItemCount();
	m_lcResult.DeleteAllItems();
	while(m_lcResult.DeleteColumn(0)){}

	//再添加对应的列
	int nColCount = vTitle.size();
	LV_COLUMN lvc;
	lvc.mask=LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM;
	lvc.fmt=LVCFMT_LEFT;

	//第一列用来表示是否经过人工检查,只是包含车牌的记录类型需要检查
	if ( (dwAlarmType == EVENT_IVS_TRAFFICGATE)
		|| (dwAlarmType == EVENT_IVS_TRAFFICCONTROL)
		|| (dwAlarmType == EVENT_IVS_TRAFFICJUNCTION)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_VEHICLEINROUTE)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_RUNREDLIGHT)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_OVERLINE)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_RETROGRADE)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_TURNLEFT)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_TURNRIGHT)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_UTURN)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_OVERSPEED)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_UNDERSPEED)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_PARKING)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_WRONGROUTE)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_CROSSLANE)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_OVERYELLOWLINE)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE)
		|| (dwAlarmType == EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY))
	{
        std::string strText = ConvertStr("State");
		lvc.pszText = (char*)strText.c_str();
		lvc.cx = 100;
		lvc.iSubItem = 0;
		m_lcResult.InsertColumn(0, &lvc);
	}

	for(int j = 1; j <= nColCount; j++) {//插入各列
		lvc.pszText = (char*)(vTitle[j-1].strColTitle.c_str());
		lvc.cx = vTitle[j-1].nColWidth;
		lvc.iSubItem = j;
		m_lcResult.InsertColumn(j, &lvc);
	}
}

/************************************************************************/
/* 查询记录响应函数                                                     */
/************************************************************************/
void CDialogPCQuery::OnButtonQuery() 
{
	if (UpdateData(TRUE) == FALSE)
	{
		return;
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_LANE))->GetCheck() != 0)
	{
		if (m_lane <= 0)
		{
			MessageBox(ConvertString("Lane input error"),ConvertString("Prompt"));
			return;
		}
	}
	if ( ((CButton*)GetDlgItem(IDC_CHECK_SPEED))->GetCheck() != 0)
	{
		if (m_speedLow > m_speedUper)
		{
			MessageBox(ConvertString("Speed input error"),ConvertString("Prompt"));
			return;
		}
	}
	AlarmMap::iterator iterMap = this->m_mapQueryResult.begin();
	for ( ; iterMap != this->m_mapQueryResult.end(); iterMap++)
	{
		delete[] (iterMap->second.pAlarmInfo);
	}
	m_mapQueryResult.clear();

	AlarmMap::iterator iter = this->m_mapAllAlarmItem.begin();
  	for (; iter != m_mapAllAlarmItem.end(); iter++)
  	{
		AddOneItem(iter->second);
  	}
	DisplayResultPage(1);
	UpdatePageStr();
	UpdateAccuracyStr();
	m_nCurSel = -1;
}

/************************************************************************/
/* 通过GUID来删除一条记录                                           */
/************************************************************************/
void CDialogPCQuery::RemoveItemByGUID(const char* szGUID)
{
	std::string strGUID(szGUID);
	AlarmMap::iterator iter = this->m_mapAllAlarmItem.find(strGUID);
	if ( iter != m_mapAllAlarmItem.end() )
	{
		delete[] (iter->second.pAlarmInfo);
		m_mapAllAlarmItem.erase(iter);
	}
}

/************************************************************************/
/* 通过GUID来删除一条查询记录                                           */
/************************************************************************/
void CDialogPCQuery::RemoveReultItemByGUID(const char* szGUID)
{
	AlarmMap::iterator iter = this->m_mapQueryResult.begin();
	for(; iter != m_mapQueryResult.end(); iter++)
	{
		if (strcmp(szGUID,  iter->second.strGUID.c_str()) == 0)
		{
			delete[] (iter->second.pAlarmInfo);
			m_mapQueryResult.erase(iter);
			break;
		}
	}
}

/************************************************************************/
/* 查询记录                                                             */
/************************************************************************/
void CDialogPCQuery::AddOneItem(ALARM_ITEM& item)
{
	char* pInfo = new char[item.nLen];
	memcpy(pInfo, item.pAlarmInfo, item.nLen);

	/************************************************************************/
	/* 在这里做查询比较,                                                    */
	/************************************************************************/
	int nAlarmType =item.nAlarmType;
	//先比较类型
	int nSel = m_cbType.GetCurSel();
	if (nSel < 0)
	{
		delete[] pInfo;
		return;
	}
	DWORD dwAlarmType = m_cbType.GetItemData(nSel);
	if (dwAlarmType != nAlarmType)
	{
		delete[] pInfo;
		return;
	}
	/************************************************************************/
	/* 比较开始时间                                                   */
	/************************************************************************/
	
	if ( ((CButton*)GetDlgItem(IDC_CHECK_START_TIME))->GetCheck() != 0)
	{
		switch(nAlarmType)
		{
		case EVENT_IVS_CROSSLINEDETECTION:
		case EVENT_IVS_CROSSREGIONDETECTION:
		case EVENT_IVS_PASTEDETECTION:
		case EVENT_IVS_LEFTDETECTION:
		case EVENT_IVS_STAYDETECTION:
		case EVENT_IVS_WANDERDETECTION:
		case EVENT_IVS_PRESERVATION:
		case EVENT_IVS_MOVEDETECTION:
		case EVENT_IVS_TAILDETECTION:
		case EVENT_IVS_RIOTERDETECTION:
		case EVENT_IVS_FIREDETECTION:
		case EVENT_IVS_SMOKEDETECTION:
		case EVENT_IVS_FIGHTDETECTION:
		case EVENT_IVS_FLOWSTAT:
		case EVENT_IVS_NUMBERSTAT:
		case EVENT_IVS_TRAFFICCONTROL:
		case EVENT_IVS_TRAFFICACCIDENT:
		case EVENT_IVS_TRAFFICJUNCTION:
		case EVENT_IVS_TRAFFICGATE:
		case EVENT_TRAFFICSNAPSHOT:
		case EVENT_IVS_FACEDETECT:
		case EVENT_IVS_TRAFFIC_RUNREDLIGHT:
		case EVENT_IVS_TRAFFIC_OVERLINE:
		case EVENT_IVS_TRAFFIC_RETROGRADE:
		case EVENT_IVS_TRAFFIC_TURNLEFT:
		case EVENT_IVS_TRAFFIC_TURNRIGHT:	
		case EVENT_IVS_TRAFFIC_UTURN:		
		case EVENT_IVS_TRAFFIC_OVERSPEED:	
		case EVENT_IVS_TRAFFIC_UNDERSPEED:
		case EVENT_IVS_TRAFFICJAM:
		case EVENT_IVS_TRAFFIC_PARKING:
		case EVENT_IVS_TRAFFIC_WRONGROUTE:
		case EVENT_IVS_TRAFFIC_CROSSLANE:
		case EVENT_IVS_TRAFFIC_OVERYELLOWLINE:
		case EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER:
		case EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE:
		case EVENT_IVS_ELECTROSPARKDETECTION:
		case EVENT_IVS_PRISONERRISEDETECTION:
		case EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY:
			//所有的这些结构的前面的成员是相同的，可以统一处理
			{
				DEV_EVENT_TRAFFICSNAPSHOT_INFO* pCommonInfo = (DEV_EVENT_TRAFFICSNAPSHOT_INFO*)pInfo;
				NET_TIME_EX netQueryStartTime = {m_dateS.GetYear(),
					 						m_dateS.GetMonth(),
					 						m_dateS.GetDay(),
					 						m_timeS.GetHour(),
					 						m_timeS.GetMinute(),
 											m_timeS.GetSecond()};
				if (NetTimeExCmp(pCommonInfo->UTC, netQueryStartTime) == -1)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		default:
			{
				MessageBox(ConvertString("Alarm type not supported yet"),ConvertString("Prompt"));
			}
		}
	}
	/************************************************************************/
	/* 比较结束时间                                                   */
	/************************************************************************/
	if ( ((CButton*)GetDlgItem(IDC_CHECK_END_TIME))->GetCheck() != 0)
	{
		switch(nAlarmType)
		{
		case EVENT_IVS_CROSSLINEDETECTION:
		case EVENT_IVS_CROSSREGIONDETECTION:
		case EVENT_IVS_PASTEDETECTION:
		case EVENT_IVS_LEFTDETECTION:
		case EVENT_IVS_STAYDETECTION:
		case EVENT_IVS_WANDERDETECTION:
		case EVENT_IVS_PRESERVATION:
		case EVENT_IVS_MOVEDETECTION:
		case EVENT_IVS_TAILDETECTION:
		case EVENT_IVS_RIOTERDETECTION:
		case EVENT_IVS_FIREDETECTION:
		case EVENT_IVS_SMOKEDETECTION:
		case EVENT_IVS_FIGHTDETECTION:
		case EVENT_IVS_FLOWSTAT:
		case EVENT_IVS_NUMBERSTAT:
		case EVENT_IVS_TRAFFICCONTROL:
		case EVENT_IVS_TRAFFICACCIDENT:
		case EVENT_IVS_TRAFFICJUNCTION:
		case EVENT_IVS_TRAFFICGATE:
		case EVENT_TRAFFICSNAPSHOT:
		case EVENT_IVS_FACEDETECT:
		case EVENT_IVS_TRAFFIC_RUNREDLIGHT:
		case EVENT_IVS_TRAFFIC_OVERLINE:
		case EVENT_IVS_TRAFFIC_RETROGRADE:
		case EVENT_IVS_TRAFFIC_TURNLEFT:
		case EVENT_IVS_TRAFFIC_TURNRIGHT:	
		case EVENT_IVS_TRAFFIC_UTURN:		
		case EVENT_IVS_TRAFFIC_OVERSPEED:	
		case EVENT_IVS_TRAFFIC_UNDERSPEED:
		case EVENT_IVS_TRAFFICJAM:
		case EVENT_IVS_TRAFFIC_PARKING:
		case EVENT_IVS_TRAFFIC_WRONGROUTE:
		case EVENT_IVS_TRAFFIC_CROSSLANE:
		case EVENT_IVS_TRAFFIC_OVERYELLOWLINE:
		case EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER:
		case EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE:
		case EVENT_IVS_ELECTROSPARKDETECTION:
		case EVENT_IVS_PRISONERRISEDETECTION:
		case EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY:
			//所有的这些结构的前面的成员是相同的，可以统一处理
			{
				DEV_EVENT_TRAFFICSNAPSHOT_INFO* pCommonInfo = (DEV_EVENT_TRAFFICSNAPSHOT_INFO*)pInfo;
				NET_TIME_EX netQueryEndTime = {m_dateE.GetYear(),
												m_dateE.GetMonth(),
												m_dateE.GetDay(),
												m_timeE.GetHour(),
												m_timeE.GetMinute(),
												m_timeE.GetSecond()};
				if (NetTimeExCmp(netQueryEndTime, pCommonInfo->UTC) == -1)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		default:
			{
				MessageBox(ConvertString("Alarm type not supported yet"),ConvertString("Prompt"));
			}
		}
	}
	/************************************************************************/
	/* 比较牌照(物体上的文字，不一定就是牌照)                                 */
	/************************************************************************/
	//由于有些报警是没有牌照的，所以牌照的比较只是针对有牌照的报警，没有牌照的报警将都被过滤掉
	if ( ((CButton*)GetDlgItem(IDC_CHECK_LP))->GetCheck() != 0)
	{
		switch(nAlarmType)
		{
		case EVENT_IVS_TRAFFICCONTROL:
		case EVENT_IVS_TRAFFICJUNCTION:
		case EVENT_IVS_TRAFFICGATE:
		case EVENT_IVS_TRAFFIC_PARKING:
		case EVENT_IVS_TRAFFIC_WRONGROUTE:
		case EVENT_IVS_TRAFFIC_CROSSLANE:
		case EVENT_IVS_TRAFFIC_OVERYELLOWLINE:
		case EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER:
		case EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE:
		case EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY:
			//所有的这些结构的前面的成员是相同的，可以统一处理
			{
				DEV_EVENT_TRAFFICGATE_INFO* pInfoWithLP = (DEV_EVENT_TRAFFICGATE_INFO*)pInfo;
				char* szLP = m_csLP.GetBuffer(0);
				if (stricmp(szLP, pInfoWithLP->stuObject.szText) != 0)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_RUNREDLIGHT:
		case EVENT_IVS_TRAFFIC_OVERLINE:
		case EVENT_IVS_TRAFFIC_RETROGRADE:
		case EVENT_IVS_TRAFFIC_TURNLEFT:
		case EVENT_IVS_TRAFFIC_TURNRIGHT:
		case EVENT_IVS_TRAFFIC_UTURN:
		case EVENT_IVS_TRAFFIC_OVERSPEED:
		case EVENT_IVS_TRAFFIC_UNDERSPEED:
			{
				DEV_EVENT_TRAFFIC_UNDERSPEED_INFO* pInfoWithLP = (DEV_EVENT_TRAFFIC_UNDERSPEED_INFO*)pInfo;
				char* szLP = m_csLP.GetBuffer(0);
				if (stricmp(szLP, pInfoWithLP->stuObject.szText) != 0)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFICACCIDENT:
			{
				char* szLP = m_csLP.GetBuffer(0);
				DEV_EVENT_TRAFFICACCIDENT_INFO* pInfoWithLP = (DEV_EVENT_TRAFFICACCIDENT_INFO*)pInfo;
				int nObjectNum = pInfoWithLP->nObjectNum;
				for (int i = 0; i < nObjectNum; i++)
				{
					if (stricmp(szLP, pInfoWithLP->stuObjectIDs[i].szText) != 0)
					{
						continue;
					}
					else
					{
						break;
					}
				}
			}
			break;
		default:
			{
				delete[] pInfo;
				return;
			}
		}
	}
	/************************************************************************/
	/* 比较车速                                                             */
	/************************************************************************/
	if ( ((CButton*)GetDlgItem(IDC_CHECK_SPEED))->GetCheck() != 0)
	{
 		int nSpeedLow = GetDlgItemInt(IDC_EDIT_SPEED_LOW);
 		int nSpeedUper = GetDlgItemInt(IDC_EDIT_SPEED_UPER);
		switch(nAlarmType)
		{
		case EVENT_TRAFFICSNAPSHOT:
			{
				DEV_EVENT_TRAFFICSNAPSHOT_INFO* pInfoTmp = (DEV_EVENT_TRAFFICSNAPSHOT_INFO*)pInfo;
				bool bFind = false;
				for (int i = 0; i <pInfoTmp->bCarWayCount; i++)
				{
					for (int j = 0; j < pInfoTmp->stuCarWayInfo[i].bSigCount; j++)
					{
						int nSpeed = pInfoTmp->stuCarWayInfo[i].stuSigInfo[j].snSpeed;
						if ( (nSpeed >= nSpeedLow) || (nSpeed <= nSpeedUper) )
						{
							bFind = true;
							break;
						}
						if (bFind)
						{
							break;
						}
					}
				}
				if (!bFind)
				{
					delete[] pInfo;
					return;
				}
			}
			break;
		case EVENT_IVS_TRAFFICGATE:
			{
				DEV_EVENT_TRAFFICGATE_INFO* pInfoTmp = (DEV_EVENT_TRAFFICGATE_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if ( (nSpeed < nSpeedLow) || (nSpeed > nSpeedUper) )
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFICJUNCTION:
			{
				DEV_EVENT_TRAFFICJUNCTION_INFO* pInfoTmp = (DEV_EVENT_TRAFFICJUNCTION_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if ( (nSpeed < nSpeedLow) || (nSpeed > nSpeedUper) )
				{
					delete[] pInfo;
					return;
				}
				break;
			}

		case EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE:
			{
				DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if ((nSpeed <nSpeedLow )|| nSpeed >nSpeedUper)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER:
			{
				DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if (nSpeed < nSpeedLow || nSpeed >nSpeedUper)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_OVERYELLOWLINE:
			{
				DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO*)pInfo;
				int nSpeed= pInfoTmp->nSpeed;
				if (nSpeed < nSpeedLow || nSpeed > nSpeedUper)
				{
					delete[] pInfo;
					return ;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_CROSSLANE:
			{
				DEV_EVENT_TRAFFIC_CROSSLANE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_CROSSLANE_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if (nSpeed < nSpeedLow || nSpeed >nSpeedUper)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_WRONGROUTE:
			{
				DEV_EVENT_TRAFFIC_WRONGROUTE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_WRONGROUTE_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if (nSpeed < nSpeedLow|| nSpeed > nSpeedUper)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_UNDERSPEED:
			{
				DEV_EVENT_TRAFFIC_UNDERSPEED_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_UNDERSPEED_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if (nSpeed <nSpeedLow || nSpeed >nSpeedUper)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_OVERSPEED:
			{
				DEV_EVENT_TRAFFIC_OVERSPEED_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_OVERSPEED_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if (nSpeed < nSpeedLow || nSpeed >nSpeedUper)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_RUNREDLIGHT:
			{
				DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO*)pInfo;
				int nSpeed = pInfoTmp->nSpeed;
				if (nSpeed < nSpeedLow || nSpeed > nSpeedUper)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		default:
			{
				delete[] pInfo;
				return;
			}
		}
	}
	/************************************************************************/
	/* 比较车道                                                             */
	/************************************************************************/
	if ( ((CButton*)GetDlgItem(IDC_CHECK_LANE))->GetCheck() != 0)
	{
		int nLane = GetDlgItemInt(IDC_EDIT_LANE);
		switch(nAlarmType)
		{
		case EVENT_IVS_TRAFFIC_RUNREDLIGHT:
			{
				DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_OVERLINE:
			{
				DEV_EVENT_TRAFFIC_OVERLINE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_OVERLINE_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_RETROGRADE:
			{
				DEV_EVENT_TRAFFIC_RETROGRADE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_RETROGRADE_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_TURNRIGHT:
			{
				DEV_EVENT_TRAFFIC_TURNRIGHT_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_TURNRIGHT_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_TURNLEFT:
			{
				DEV_EVENT_TRAFFIC_TURNLEFT_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_TURNLEFT_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_UTURN:
			{
				DEV_EVENT_TRAFFIC_UTURN_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_UTURN_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_OVERSPEED:
			{
				DEV_EVENT_TRAFFIC_OVERSPEED_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_OVERSPEED_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_UNDERSPEED:
			{
				DEV_EVENT_TRAFFIC_UNDERSPEED_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_UNDERSPEED_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_TRAFFICSNAPSHOT:
			{
				DEV_EVENT_TRAFFICSNAPSHOT_INFO* pInfoTmp = (DEV_EVENT_TRAFFICSNAPSHOT_INFO*)pInfo;
				bool bFind = false;
				for (int i = 0; i <pInfoTmp->bCarWayCount; i++)
				{
					if (pInfoTmp->stuCarWayInfo[i].bCarWayID == nLane)
					{
						bFind = true;
						break;
					}
				}
				if (!bFind)
				{
					delete[] pInfo;
					return;
				}
			}
			break;
		case EVENT_IVS_TRAFFICGATE:
			{
				DEV_EVENT_TRAFFICGATE_INFO* pInfoTmp = (DEV_EVENT_TRAFFICGATE_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
			}
			break;
		case EVENT_IVS_TRAFFICJUNCTION:
			{
				DEV_EVENT_TRAFFICJUNCTION_INFO* pInfoTmp = (DEV_EVENT_TRAFFICJUNCTION_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
			}
			break;
		case EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE:
			{
				DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER:
			{
				DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_OVERYELLOWLINE:
			{
				DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_CROSSLANE:
			{
				DEV_EVENT_TRAFFIC_CROSSLANE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_CROSSLANE_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_WRONGROUTE:
			{
				DEV_EVENT_TRAFFIC_WRONGROUTE_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_WRONGROUTE_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFICJAM:
			{
				DEV_EVENT_TRAFFICJAM_INFO* pInfoTmp = (DEV_EVENT_TRAFFICJAM_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		case EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY:
			{
				DEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO* pInfoTmp = (DEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO*)pInfo;
				if (pInfoTmp->nLane != nLane)
				{
					delete[] pInfo;
					return;
				}
				break;
			}
		default:
			delete[] pInfo;
		}
	}
	/************************************************************************/
	/* 审核状态                                */
	/************************************************************************/
	if ( ((CButton*)GetDlgItem(IDC_CHECK_STATE))->GetCheck() != 0)
	{
		int nState = m_cbQState.GetItemData(m_cbQState.GetCurSel());
		if (nState != item.nCheckFlag)
		{
			delete[] pInfo;
			return;
		}
	}

	//到这里说明符合了上述了所有条件
	ALARM_ITEM ai;
	ai.strGUID = item.strGUID;
	ai.nAlarmType = nAlarmType;
	ai.pAlarmInfo = pInfo;
	ai.nCheckFlag = item.nCheckFlag;
	this->m_mapQueryResult.insert(std::pair<std::string, ALARM_ITEM>(std::string(item.strGUID), ai));
}


/************************************************************************/
/* 更新分页字符串                                                       */
/************************************************************************/
void CDialogPCQuery::UpdatePageStr()
{
	int nRecordCount = this->m_mapQueryResult.size();
	int nPageCount  = (nRecordCount / SINGLE_PAGE_SIZE) + ( (nRecordCount % SINGLE_PAGE_SIZE == 0) ? 0 : 1 );//总页数
	char szPageStr[32] = {0};
	sprintf(szPageStr, "%d / %d", this->m_curPage, nPageCount);
	SetDlgItemText(IDC_STATIC_PAGE_TEXT, szPageStr);
}

/************************************************************************/
/* 显示记录                                                             */
/************************************************************************/
void CDialogPCQuery::DisplayResultPage(UINT page)
{
	//清除上次的显示记录
	ClearResultListCtrl();

	int nDisplayPage = page;
	BOOL bRet = TRUE;
	int nRecordCount = this->m_mapQueryResult.size();
	if (nRecordCount == 0)
	{
		this->m_curPage = 0;
		MessageBox(ConvertString("No record!"),ConvertString("Prompt"));
		return;
	}
	
	vector<ColDes> vTitles;
	std::map<std::string, ALARM_ITEM>::iterator iterMap =  this->m_mapQueryResult.begin();
	bRet = GetStructInfo((*iterMap).second.nAlarmType,
									NULL,
									GET_SI_TITLE,
									NULL,
									NULL,
									&vTitles,
									NULL);
	size_t stVTitlesCount = vTitles.size();
	if (stVTitlesCount == 0)
	{
		return;
	}
	LV_ITEM lvi;
	lvi.mask=LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	lvi.iSubItem=0;
	lvi.pszText= "";
	lvi.iImage = 0;
	
	int nPageCount  = (nRecordCount / SINGLE_PAGE_SIZE) + ( (nRecordCount % SINGLE_PAGE_SIZE == 0) ? 0 : 1 );//总页数
	if (nPageCount == 0)
	{
		return;
	}
	if(nDisplayPage > nPageCount)
	{
		nDisplayPage = nPageCount;
	}
	int nStartIndex = (nDisplayPage - 1) * SINGLE_PAGE_SIZE;	//起始下标
	int nLastPageCount = (nRecordCount % SINGLE_PAGE_SIZE == 0) ? (SINGLE_PAGE_SIZE) : (nRecordCount % SINGLE_PAGE_SIZE);
	int nOffset =  (nPageCount == nDisplayPage) ? (nLastPageCount) : (SINGLE_PAGE_SIZE);
	int nEndIndex = nStartIndex + nOffset;
	this->m_curPage = nDisplayPage;
	
	vector<string> vContents;
	std::map<std::string, ALARM_ITEM>::iterator iter =  this->m_mapQueryResult.begin();
	int index = 0;
	int test = 0;
	for (; iter != this->m_mapQueryResult.end(); iter++)
	{
		if ( index < nStartIndex || index >= nEndIndex)
		{
			index++;
			continue;
		}
		lvi.iItem =index-nStartIndex;

		//在这里检查是否有车牌，如果不需要显示没有车牌的事件，那么continue
		CButton* checkBtn = (CButton*)(GetDlgItem(IDC_CHECK_HIDE_NO_LP));
		//hide event without license
		if (checkBtn->GetCheck() != 0)
		{
			if (IsTypeHasLP(iter->second.nAlarmType))
			{
				DEV_EVENT_TRAFFICGATE_INFO* pInfo = (DEV_EVENT_TRAFFICGATE_INFO*)(iter->second.pAlarmInfo);
				if (strcmp(pInfo->stuObject.szText, "") == 0)//车牌为空
				{
					//index--;
					continue;
				}
			}
		}

		//Get data
		vContents.clear();
		bRet = GetStructInfo(iter->second.nAlarmType,
			iter->second.pAlarmInfo,
									GET_SI_CONTENT,
									NULL,
									NULL,
									&vTitles,
									&vContents);
		if ( (vContents.size() % stVTitlesCount) != 0)//内容的条数，必须是标题的条数的整数倍，否则说明有误，需要修改GetStructInfo
		{
			assert(0);
		}
		
		//Display data
		int nDisplayCount = (int)(vContents.size() / stVTitlesCount);//记录的数量=内容的数量/标题的数量
		for (int nCurDisplayIndex = 0; nCurDisplayIndex < nDisplayCount; nCurDisplayIndex++)
		{
			m_lcResult.InsertItem(&lvi);
			char* szGUID = new char[MAX_GUID_LEN+1];
			memset(szGUID, 0, MAX_GUID_LEN+1);
			strcpy(szGUID, iter->second.strGUID.c_str());

			m_lcResult.SetItemData(lvi.iItem, (DWORD)(szGUID));

			m_lcResult.SetItemText(lvi.iItem, 0, I2State(iter->second.nCheckFlag).c_str());
			for (int i = 1; i <= (int)stVTitlesCount; i++)
			{
				const char* szContent =  vContents[(nCurDisplayIndex * (int)stVTitlesCount) + i -1].c_str();
				m_lcResult.SetItemText(lvi.iItem, i, vContents[(nCurDisplayIndex * (int)stVTitlesCount) + i -1].c_str());//显示向量中的对应字符串
			}
		}        
		index++;
	}
}

/************************************************************************/
/* 显示图片                                                             */
/************************************************************************/
BOOL CDialogPCQuery::DisplayPic(const char* szBMPFilePath)
{

	RenderJPG(szBMPFilePath, m_stuShowBmp.GetSafeHwnd());
	return TRUE;
	BOOL bShowFull = ((CButton*)GetDlgItem(IDC_CHECK_SHOW_FULL))->GetCheck();
	if(!bShowFull)
	{
		//m_cPictureWnd.ShowWindow(SW_HIDE);
		
		//HBITMAP hBitmap; //Define .BMP object handle.
		BITMAP BM; 
		if (m_MemDC == NULL)
		{
			m_MemDC = new CDC;
			if (m_ClientDC == NULL)
			{
				m_ClientDC = new CClientDC(&m_stuShowBmp);
			}
			m_stuShowBmp.GetClientRect(&m_rect);
			m_MemDC->CreateCompatibleDC(m_ClientDC); 
		}
		if (m_hBitmap != NULL)
		{
			::DeleteObject(m_hBitmap);
		}
		m_hBitmap = LoadImageFile(szBMPFilePath, m_nWidth, m_nHeight);
		
		if(m_hBitmap != NULL)
		{
			m_MemDC->SelectObject(m_hBitmap);
			::GetObject(m_hBitmap,sizeof(BM),&BM);
			
			m_ClientDC->SetStretchBltMode(STRETCH_HALFTONE);
			m_ClientDC->StretchBlt(0,0,(m_rect.right - m_rect.left),(m_rect.bottom - m_rect.top), m_MemDC,0,0,m_nWidth,m_nHeight,SRCCOPY);
			//::DeleteObject(m_hBitmap);
		}
	}
	return TRUE;
}

/************************************************************************/
/* 保存当前的信息，注意在关闭程序的时候会强制保存一次信息               */
/************************************************************************/
void CDialogPCQuery::OnButtonSave() 
{
	this->SaveDataToDisk();
}

void CDialogPCQuery::SaveDataToDisk()
{
	//读取数据文件夹的位置
	string strDataFilePath = GetDataFolder().append(PC_DATA_STORE_FILE);
	
	//保存数据
	FILE* fp = fopen(strDataFilePath.c_str(), "wb");
	if ( fp == NULL)
	{
		MessageBox(ConvertString("Save data failed"),ConvertString("Prompt"));
		return;
	}
	AlarmMap::iterator iter = this->m_mapAllAlarmItem.begin();
	for (; iter != m_mapAllAlarmItem.end(); iter++)
	{
		//写文件
		fwrite(iter->second.strGUID.c_str(), 1, MAX_GUID_LEN, fp); //GUID
		fwrite(&(iter->second.nAlarmType), 1, 4, fp);	 //报警类型
		fwrite(&(iter->second.nLen), 1, 4, fp);			 //报警结构长度
		fwrite(iter->second.pAlarmInfo, 1, iter->second.nLen, fp);//报警信息
		fwrite(&(iter->second.nCheckFlag), 1, 4, fp);			  //人工检查标记
	}
	fclose(fp);
}

/************************************************************************/
/* 删除选中项                                                            */
/************************************************************************/
void CDialogPCQuery::OnButtonDelete() 
{
	//删除向量中的GUID相同的记录
	int nRowCount = m_lcResult.GetItemCount();
	char* szGUID = NULL;
	for (int i = nRowCount -1; i >=0; i--)
	{
		if (m_lcResult.GetCheck(i))
		{
			szGUID = ((char*)(m_lcResult.GetItemData(i)));
			//删除记录集和查询结果中的数据
			RemoveItemByGUID(szGUID);
			RemoveReultItemByGUID(szGUID);

			//删除硬盘上的文件
			string strJpgFilePath = GetDataFolder();
			strJpgFilePath.append(szGUID);
			strJpgFilePath.append(".jpg");
			::DeleteFile(strJpgFilePath.c_str());

			// 同步删除事件界面上对应的信息
			if (NULL != m_pLoadPicDlg)
			{
				m_pLoadPicDlg->DeletAlarmInfo(szGUID);
			}

		}
	}

	//重新显示记录
	this->DisplayResultPage(this->m_curPage);

	//更新分页字符
	this->UpdatePageStr();

	//更新正确率
	this->UpdateAccuracyStr();
}

/************************************************************************/
/* 全选记录                                                             */
/************************************************************************/
void CDialogPCQuery::OnButtonSelAll() 
{
	int nRow = m_lcResult.GetItemCount();
	for (int i = 0; i < nRow; i++)
	{
		m_lcResult.SetCheck(i, TRUE);
	}
}

/************************************************************************/
/* 反选记录                                                             */
/************************************************************************/
void CDialogPCQuery::OnButtonAntiSel() 
{
	int nRow = m_lcResult.GetItemCount();
	for (int i = 0; i < nRow; i++)
	{
		m_lcResult.SetCheck(i, !(m_lcResult.GetCheck(i)));
	}
}

/************************************************************************/
/* 关闭对话框                                                           */
/************************************************************************/
void CDialogPCQuery::OnDestroy() 
{
	CDialog::OnDestroy();

	//关闭定时器
	//KillTimer(10000);

	//保存数据
	this->SaveDataToDisk();

	//清空记录集
	this->ClearRecordData();

	//释放显示列表中的GUID字符串空间
	this->ClearResultListCtrl();
}

/************************************************************************/
/* 更改显示的数据类型的时候，需要清理数据，以及改变列表框的标题，分页字符*/
/************************************************************************/
void CDialogPCQuery::OnCbnSelchangeComboType()
{
	int nCurSel = m_cbType.GetCurSel();
	if (nCurSel < 0)
	{
		return;
	}

	//清空显示列表
	this->ClearResultListCtrl();

	//清空查询结果
	this->ClearQueryResultData();

	//更新分页字符串
	this->m_curPage = 0;
	this->UpdatePageStr();

	//改变标题
	DWORD dwAlarmType = m_cbType.GetItemData(nCurSel);
	this->ChangeDisplayTitle(dwAlarmType);
}

/************************************************************************/
/* 用系统默认的程序打开图片                                             */
/************************************************************************/
void CDialogPCQuery::OnButtonOpenPic()
{
	//获取选中的记录的下标
	int nCurIndex = (int)m_lcResult.GetFirstSelectedItemPosition() -1;
	if ( (nCurIndex < 0) ||(nCurIndex >= m_lcResult.GetItemCount()) )
	{
		return;
	}
	//获取JPG文件的路径
	std::string strDataFolder = GetDataFolder();
	char* szGUID = (char*)(m_lcResult.GetItemData(nCurIndex));
	string strJpgFilePath = strDataFolder + string(szGUID) + string(".jpg");
	//用默认的软件打开文件
	::ShellExecute(NULL, NULL, strJpgFilePath.c_str(), "explore", NULL, SW_SHOWMAXIMIZED);  
}


/************************************************************************/
/* 显示后一页的记录                                                     */
/************************************************************************/
void CDialogPCQuery::OnBnClickedButtonNextPage()
{
	int nRecordCount = this->m_mapQueryResult.size();
	int nPageCount  = (nRecordCount / SINGLE_PAGE_SIZE) + ( (nRecordCount % SINGLE_PAGE_SIZE == 0) ? 0 : 1 );//总页数
	if ( m_curPage < nPageCount)
	{
		m_curPage++;
		this->DisplayResultPage(m_curPage);
		this->UpdatePageStr();
	}
}

/************************************************************************/
/* 显示前一页的记录                                                     */
/************************************************************************/
void CDialogPCQuery::OnBnClickedButtonPrePage()
{
	int nRecordCount = m_mapQueryResult.size();
	int nPageCount  = (nRecordCount / SINGLE_PAGE_SIZE) + ( (nRecordCount % SINGLE_PAGE_SIZE == 0) ? 0 : 1 );//总页数
	if ( m_curPage > 1)
	{
		m_curPage--;
		this->DisplayResultPage(m_curPage);
		this->UpdatePageStr();
	}
}

/************************************************************************/
/* 显示最后一页的记录                                                   */
/************************************************************************/
void CDialogPCQuery::OnBnClickedButtonLastPage()
{
	int nRecordCount = m_mapQueryResult.size();
	int nPageCount  = (nRecordCount / SINGLE_PAGE_SIZE) + ( (nRecordCount % SINGLE_PAGE_SIZE == 0) ? 0 : 1 );//总页数
	if ((nPageCount == 0) || (nPageCount==m_curPage))
	{
		return;
	}
	this->DisplayResultPage(nPageCount);
	m_curPage = nPageCount;
	this->UpdatePageStr();
}

/************************************************************************/
/* 显示第一页的记录                                                     */
/************************************************************************/
void CDialogPCQuery::OnBnClickedButtonFirstPage()
{
	if(m_curPage == 1 || m_curPage == 0)
	{
		return;
	}
	this->DisplayResultPage(1);
	m_curPage = 1;
	this->UpdatePageStr();
}
/************************************************************************/
/* 清空记录集及对应的值,只有保存好数据之后才能清空                      */
/************************************************************************/
void CDialogPCQuery::ClearRecordData()
{
	AlarmMap::iterator iter = this->m_mapAllAlarmItem.begin();
	for (; iter != m_mapAllAlarmItem.end(); iter++)
	{
		delete[] (iter->second.pAlarmInfo);
	}
	m_mapAllAlarmItem.clear();
}

/************************************************************************/
/* 清空查询结果集及对应的值                                             */
/************************************************************************/
void CDialogPCQuery::ClearQueryResultData()
{
	AlarmMap::iterator iter = this->m_mapQueryResult.begin();
	while (iter != m_mapQueryResult.end())
	{
		delete[] (iter->second.pAlarmInfo);
		iter++;
	}
	m_mapQueryResult.clear();
}

/************************************************************************/
/* 清空显示列表及对应的值                                               */
/************************************************************************/
void CDialogPCQuery::ClearResultListCtrl()
{
	int nItemCount = m_lcResult.GetItemCount();
	for ( int i = nItemCount - 1; i >= 0; i-- )
	{
		char* pCh = (char*) m_lcResult.GetItemData(i);
		delete pCh;
		pCh = NULL;
		//delete[] (char*)(m_lcResult.GetItemData(i));
	}
	m_lcResult.DeleteAllItems();
}

/************************************************************************/
/* 更新静态文本显示框中的状态                                           */
/************************************************************************/
void CDialogPCQuery::UpdateStaticCtrlState(int stateIndex)
{
	std::string strState = I2State(stateIndex);
	GetDlgItem(IDC_STATIC_STATE)->SetWindowText(strState.c_str());
}

/************************************************************************/
/* 更新状态                                                             */
/************************************************************************/
void CDialogPCQuery::UpdateEventState(int nItemIndex)
{
	//获取选中行的GUID
	char* szGUID = (char*)(m_lcResult.GetItemData(nItemIndex));

	//计算新的状态
	ALARM_ITEM* alarmItemAll = this->GetAlarmItemByGUID(szGUID);
	ALARM_ITEM* alarmItemRes = this->GetQuerryedAlarmItemByGUID(szGUID);
	int nStateIndex = alarmItemAll->nCheckFlag;
	int nNewStateIndex = (nStateIndex + 1 > (LP_STATE_COUNT -1) ) ? (0) : (nStateIndex + 1);
	
	//改变记录中的
	alarmItemAll->nCheckFlag = nNewStateIndex;
	alarmItemRes->nCheckFlag = nNewStateIndex;

	//改变列表框中显示的状态
	std::string strState = I2State(nNewStateIndex);
	m_lcResult.SetItemText(nItemIndex, 0, strState.c_str());

	//改变静态文本的状态显示
	UpdateStaticCtrlState(nNewStateIndex);

	//改变正确率
	UpdateAccuracyStr();
}

/************************************************************************/
/* 更新准确率                                                           */
/************************************************************************/
void CDialogPCQuery::UpdateAccuracyStr()
{
	int nRecordCount = 0;
	int nNotCheck = 0;
	int nRight = 0;
	int nWrong = 0;
	int nNoLP = 0;
	int nDitryLP = 0;
	int nFalseAlarm = 0;
	AlarmMap::iterator iter = m_mapQueryResult.begin();
	for (; iter != m_mapQueryResult.end(); iter++)
	{
		switch(iter->second.nCheckFlag)
		{
		case 0:
			nNotCheck++;
			break;
		case 1:
			nRight++;
			break;
		case 2:
			nWrong++;
			break;
		case 3:
			nNoLP++;
			break;
		case 4:
			nDitryLP++;
			break;
		case 5:
			nFalseAlarm++;
		}
	}
	int nAccuracy = 0;
	if (nWrong + nRight != 0)
	{
		nAccuracy = (int)(nRight * 100  / (nWrong + nRight) + 0.5);
	}
	nRecordCount = (int)(m_mapQueryResult.size());

	std::string strMsg = ConvertStr("Reocrd Count")			+std::string(":")+I2Str(nRecordCount)	+std::string("  ")
						+ConvertStr("Not Checked")			+std::string(":")+I2Str(nNotCheck)		+std::string("  ")
						+ConvertStr("Right")				+std::string(":")+I2Str(nRight)			+std::string("  ")
						+ConvertStr("Wrong")				+std::string(":")+I2Str(nWrong)			+std::string("  ")
						+ConvertStr("No License Plate")		+std::string(":")+I2Str(nNoLP)			+std::string("  ")
						+ConvertStr("Dirty License Plate")	+std::string(":")+I2Str(nDitryLP)		+std::string("  ")
						+ConvertStr("False Alarm")			+std::string(":")+I2Str(nFalseAlarm)	+std::string("  ");
	GetDlgItem(IDC_STATIC_STAT)->SetWindowText(strMsg.c_str());
}

/************************************************************************/
/*  屏蔽回车和ESC                                                       */
/************************************************************************/
BOOL CDialogPCQuery::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg-> message   ==   WM_KEYDOWN) 
    { 
		switch(pMsg-> wParam) 
		{
		case   VK_RETURN://屏蔽回车 
			return   TRUE; 
		case   VK_ESCAPE://屏蔽ESC
			return   TRUE; 
		} 
    } 
	return CDialog::PreTranslateMessage(pMsg);
}

/************************************************************************/
/* 显示 整个图片，牌照图片，以及牌照文字                                */
/************************************************************************/
void CDialogPCQuery::DisplaySelectedPicInfo(int nItemIndex, CListCtrl* listCtrl)
{
	//检查下标的合法性
	if ( (nItemIndex < 0) 
	   ||(nItemIndex >= listCtrl->GetItemCount())
	   )
	{
		return;
	}

	//读取数据文件夹的位置
	std::string strDataFolder = GetDataFolder();
	
	//获取记录ID
	char* szGUID = (char*)(listCtrl->GetItemData(nItemIndex));
	strDataFolder.append(szGUID);

	//获取记录文件
	std::string strJpgFilePath = strDataFolder.append(".jpg");
	
	//显示牌照（物体上的文字）
	ALARM_ITEM* itemPtr = this->GetAlarmItemByGUID(szGUID);
	TryDisplayLP(itemPtr->nAlarmType, itemPtr->pAlarmInfo, GetDlgItem(IDC_STATIC_LP));

	

	TryDisplayImageAndLPPart(strJpgFilePath.c_str(), 
							itemPtr, 
							&m_stuShowBmp,
							GetDlgItem(IDC_STATIC_LP_IMAGE));

	//显示图片
	//this->DisplayPic(strJpgFilePath.c_str());
	//m_lastBMPFilePath = strJpgFilePath;
	
	//显示图片中的车牌
	//TryDisplayLPPic(strJpgFilePath.c_str(), itemPtr, GetDlgItem(IDC_STATIC_LP_IMAGE));






	//更新当前的静态文本区的状态
	this->UpdateStaticCtrlState(itemPtr->nCheckFlag);

	//改变当前的选中项
	//m_nCurSel = itemIndex;
}

/************************************************************************/
/* 鼠标点击列表框的响应函数                                             */
/************************************************************************/
void CDialogPCQuery::OnClickListResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	if (phdn->iItem == -1)
	{
		return;
	}
	
	int newIndex = phdn->iItem;
	DisplaySelectedPicInfo(newIndex, &m_lcResult);
	
	//改变当前的选中项
	m_nCurSel = phdn->iItem;
	
	*pResult = 0;
}


/************************************************************************/
/* 键盘按下列表框的响应函数                                             */
/************************************************************************/
void CDialogPCQuery::OnKeydownListResult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	int nCurIndex = (int)m_lcResult.GetFirstSelectedItemPosition() - 1;
	
	//显示下一条或上一条记录
	if (pLVKeyDow->wVKey == 38 || pLVKeyDow->wVKey == 40)
	{
		int newIndex = 0;
		if (pLVKeyDow->wVKey == 38)//up
		{
			newIndex = (nCurIndex == 0)? nCurIndex : nCurIndex -1;
		}
		else//down
		{
			newIndex = (nCurIndex == m_lcResult.GetItemCount()-1) ? nCurIndex : nCurIndex + 1;
		}
		DisplaySelectedPicInfo(newIndex, &m_lcResult);
	}
	
	//空格,用来改变当前行的状态
	if (pLVKeyDow->wVKey == 32)
	{
		UpdateEventState(nCurIndex);
		*pResult = 1;
		return;
	}
	
	//Ctrl,用来勾选当前行
	if (pLVKeyDow->wVKey == 17)
	{
		m_lcResult.SetCheck(nCurIndex, !(m_lcResult.GetCheck(nCurIndex)));
	}

	//39 -> :	37 <-  //未用
	if (pLVKeyDow->wVKey == 37 || pLVKeyDow->wVKey == 39)
	{
	}
	
	*pResult = 0;
}

/************************************************************************/
/* 隐藏或显示没有拍照的记录                                             */
/************************************************************************/
void CDialogPCQuery::OnCheckHideNoLp() 
{
	this->DisplayResultPage(m_curPage);
}

/************************************************************************/
/* 改变牌照文字显示框的背景色和文字颜色                                 */
/************************************************************************/
HBRUSH CDialogPCQuery::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd-> GetDlgCtrlID() == IDC_STATIC_LP)
	{
		pDC-> SetBkColor(RGB(0,0,255)); 
		pDC-> SetTextColor(RGB(255,255,255)); 
	}
	return hbr;
}

// void CDialogPCQuery::OnTimer(UINT nIDEvent) 
// {
// 	if (nIDEvent == 10000)
// 	{	
// 		int nCurIndex = (int)m_lcResult.GetFirstSelectedItemPosition() - 1;
// 		DisplaySelectedPicInfo(nCurIndex, &m_lcResult);
// 	}
// 	
// 	CDialog::OnTimer(nIDEvent);
// }


