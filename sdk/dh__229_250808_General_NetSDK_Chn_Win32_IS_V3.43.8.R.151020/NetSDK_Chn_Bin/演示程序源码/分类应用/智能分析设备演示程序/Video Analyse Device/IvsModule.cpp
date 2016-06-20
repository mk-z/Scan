#include "StdAfx.h"
#include "IvsModule.h"

#include <math.h>

CRITICAL_SECTION CIvsModule::m_cs;
std::map<int,IvsDecodeInfo> CIvsModule::m_decode_info_map;		// 解码端口号 ==> 解码信息
std::list<IvsChnlInfo>	CIvsModule::m_chnl_info_list;			// 通道信息表

HANDLE CIvsModule::m_hIvsHeap = 0;
 
BOOL CIvsModule::Init()
{
	InitializeCriticalSection(&m_cs);

	m_hIvsHeap = HeapCreate(0,1 * 1024 * 1024,0);
	if (m_hIvsHeap)
	{
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CIvsModule::UnInit()
{
	DeleteCriticalSection(&m_cs);

	if (NULL != m_hIvsHeap)
	{
		HeapDestroy(m_hIvsHeap);
	}
	return 0;
}

void* CIvsModule::AllocateMemory(UINT nSize)
{
	return HeapAlloc(m_hIvsHeap,0,nSize);
}

void CIvsModule::FreeMemory(void* pMem)
{
	HeapFree(m_hIvsHeap,0,pMem);
}

//************************************
// 方法:	public static CIvsLogic::OnOpenDeviceRealplay
// 摘要:	打开设备通道视频时,记录其智能分析规则信息和解码信息
// 返回:
//		int
// 参数:
//		LONG lDevHandle			设备句柄
//		LONG lDevId				设备ID
//		int nChnlIdx			通道序号
//		int nDecoderPort		解码端口号
//		HWND hwnd				视频显示窗口
//************************************
int CIvsModule::OnOpenDeviceRealplay(LONG lDevHandle,int nChnlIdx,
									int nDecoderPort,HWND hwnd,int nChnlCnt)
{
	int nRetVal = -1;
	
	ReloadIvsRuleReq* pReq = (ReloadIvsRuleReq*)AllocateMemory(sizeof(ReloadIvsRuleReq));
	
	if (NULL != pReq)
	{
		pReq->devHandle	= lDevHandle;
		pReq->nChnlIdx	= nChnlIdx;
		pReq->bReloadCfg= false;
		pReq->bAddNew	= true;
		pReq->nDecPort	= nDecoderPort;
		pReq->hVideoWnd	= hwnd;
		pReq->nChnlCnt = nChnlCnt;
		
		ReloadIvsRuleProc(pReq);
		
		FreeMemory(pReq);
	}
	
	return nRetVal;
}
// 重新读取通道的智能分析规则
void CIvsModule::ReloadIvsRuleProc(ReloadIvsRuleReq* pReq)
{
	
	DEV_INFO devInfo;
	memset((void*)&devInfo,0x0,sizeof(devInfo));
	
	devInfo.m_ChannelCount = pReq->nChnlCnt;
	devInfo.m_LoginHandle = pReq->devHandle;
	int iRet = GetDeviceIvsConfig(devInfo);
	if (iRet == -1)
	{
		AfxMessageBox("获取IVS配置数据失败!");
		return;
	}
	
	if (0 != pReq->devHandle)
	{
		ReloadChannelIvsRule(pReq->devHandle,devInfo,pReq->nChnlIdx,pReq->bAddNew,pReq->nDecPort);
		
		if (pReq->nDecPort >= 0)
		{
			IvsDecodeInfo decode_info;
			
			decode_info.dev_id		= pReq->devHandle;
			decode_info.chnl_idx	= pReq->nChnlIdx;
			decode_info.decoder_id	= pReq->nDecPort;
			decode_info.hwnd		= pReq->hVideoWnd;
			
			decode_info.bShowRule	= true;
			decode_info.bShowObj	= true;
			decode_info.bShowLocus	= true;
			
			m_decode_info_map.insert(std::make_pair(pReq->nDecPort,decode_info));
		}
	}
}

// 获取设备智能分析配置
int CIvsModule::GetDeviceIvsConfig(DEV_INFO& devInfo)
{
	if (NULL == devInfo.m_LoginHandle)
	{
		return -1;
	}
	
	CFG_CAP_ANALYSE_INFO *pchnl_cap = new CFG_CAP_ANALYSE_INFO;
	char szOutBuffer[32*1024] = {0};
	int nError = 0;
	
	// 通道智能分析能力
	for(int i = 0 ; i < devInfo.m_ChannelCount; ++i)
	{
		ZeroMemory(pchnl_cap,sizeof(*pchnl_cap));
		
		BOOL bSuccess = CLIENT_QueryNewSystemInfo(devInfo.m_LoginHandle,
			CFG_CAP_CMD_VIDEOANALYSE,i,
			szOutBuffer,sizeof(szOutBuffer),&nError);
		
		if (bSuccess)
		{
			int nRetLen = 0;
			
			BOOL bRet = CLIENT_ParseData(CFG_CAP_CMD_VIDEOANALYSE,szOutBuffer,
				(char*)pchnl_cap,sizeof(CFG_CAP_ANALYSE_INFO),
				&nRetLen);
			
			if (bRet && (pchnl_cap->nSupportedRulesNum > 0) && (pchnl_cap->nMaxRules > 0))
			{
				devInfo.m_Channel[i].m_bSupportIvs = TRUE;
				devInfo.m_Channel[i].m_bEnableIvs  = TRUE;
				devInfo.m_Channel[i].m_bAtmIvs = FALSE;
				
				int nMaxRuleStructSize = GetRulesMaxStructSize(pchnl_cap->dwRulesType, pchnl_cap->nSupportedRulesNum);
				devInfo.m_Channel[i].m_nMaxRuleStructSize = nMaxRuleStructSize;
				devInfo.m_Channel[i].m_nMaxRuleNum = pchnl_cap->nMaxRules;
			}
		}
	}
	
	delete pchnl_cap;
	pchnl_cap = NULL;
	return 0;
}

int CIvsModule::GetRulesMaxStructSize(DWORD *pRulesTypes, int nRuleNum)
{
	int nMaxSize = 0;
	int nSize = 0;
	for (int i = 0; i < nRuleNum; i++)
	{
		if (EVENT_IVS_CROSSLINEDETECTION == pRulesTypes[i])  //警戒线
		{
			nSize = sizeof(CFG_CROSSLINE_INFO);
		}
		else if (EVENT_IVS_CROSSREGIONDETECTION == pRulesTypes[i])  //警戒区
		{
			nSize = sizeof(CFG_CROSSREGION_INFO);
		}
		else if (EVENT_IVS_PASTEDETECTION == pRulesTypes[i])  //ATM贴条
		{
			nSize = sizeof(CFG_PASTE_INFO);
		}
		else if (EVENT_IVS_LEFTDETECTION == pRulesTypes[i])  //遗留物监测
		{
			nSize = sizeof(CFG_LEFT_INFO);
		}
		else if (EVENT_IVS_STAYDETECTION == pRulesTypes[i])  // 停留事件
		{
			nSize = sizeof(CFG_STAY_INFO);
		}
		else if (EVENT_IVS_WANDERDETECTION == pRulesTypes[i]) //徘徊
		{
			nSize = sizeof(CFG_WANDER_INFO);
		}
		else if (EVENT_IVS_PRESERVATION == pRulesTypes[i]) // 物品保全事件
		{
			nSize = sizeof(CFG_PRESERVATION_INFO);
		}
		else if (EVENT_IVS_MOVEDETECTION == pRulesTypes[i]) // 移动事件
		{
			nSize = sizeof(CFG_MOVE_INFO);
		}
		else if (EVENT_IVS_TAILDETECTION == pRulesTypes[i]) //尾随 （未实现）
		{
			nSize = sizeof(CFG_TAIL_INFO);
		}
		else if (EVENT_IVS_RIOTERDETECTION == pRulesTypes[i])  //聚集
		{
			nSize = sizeof(CFG_RIOTER_INFO);
		}
		else if (EVENT_IVS_FIREDETECTION == pRulesTypes[i]) // 火警事件（未实现）
		{
			nSize = sizeof(CFG_FIRE_INFO);
		}
		else if (EVENT_IVS_SMOKEDETECTION == pRulesTypes[i]) // 烟雾报警事件（未实现）
		{
			nSize = sizeof(CFG_SMOKE_INFO);
		}
		else if (EVENT_IVS_FIGHTDETECTION == pRulesTypes[i]) // 斗殴事件（未实现）
		{
			nSize = sizeof(CFG_FIGHT_INFO);
		}
		else if (EVENT_IVS_FLOWSTAT == pRulesTypes[i]) // 流量统计事件
		{
			nSize = sizeof(CFG_FLOWSTAT_INFO);
		}
		else if (EVENT_IVS_NUMBERSTAT == pRulesTypes[i])	// 数量统计事件
		{
			nSize = sizeof(CFG_NUMBERSTAT_INFO);
		}
		else if (EVENT_IVS_TRAFFICCONTROL == pRulesTypes[i]) 
		{
			nSize = sizeof(CFG_TRAFFICCONTROL_INFO);
		}
		else if (EVENT_IVS_TRAFFICACCIDENT == pRulesTypes[i])
		{
			nSize = sizeof(CFG_TRAACCIDENT_INFO);
		}
		else if (EVENT_IVS_TRAFFICJUNCTION == pRulesTypes[i])
		{
			nSize = sizeof(CFG_TRAJUNCTION_INFO);
		}
		else if (EVENT_IVS_TRAFFICGATE == pRulesTypes[i])
		{
			nSize = sizeof(CFG_TRAFFICGATE_INFO);
		}
		else if (EVENT_IVS_FACEDETECT == pRulesTypes[i])	//人脸检测
		{
			nSize = sizeof(CFG_FACEDETECT_INFO);
		}
		else if (EVENT_IVS_ELECTROSPARKDETECTION == pRulesTypes[i]) // 电火花事件 
		{
			nSize = sizeof(DEV_EVENT_ELECTROSPARK_INFO);   
		}
		else if (EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY == pRulesTypes[i]) // 交通-斑马线行人优先
		{
			nSize = sizeof(DEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO);   
		}
		
		if (nSize > nMaxSize)
		{
			nMaxSize = nSize;
		}
	}
	
	return nMaxSize;
}

//************************************
// 方法:	protected CIvsLogic::ReloadChannelIvsRule
// 摘要:	  重新读取设备通道智能分析规则
// 返回:
//		int		0: 成功		-1: 失败
// 参数:
//		LONG lDevHandle		设备句柄
//		LONG lDevId			设备ID
//		int nChnlIdx		通道序号
//		bool bAddNew		如果还没有相关通道记录,是否添加新的记录(true: 增加/更新记录   false: 仅更新记录)
//************************************
int CIvsModule::ReloadChannelIvsRule(LONG lDevHandle,DEV_INFO &devInfo,int nChnlIdx,
									bool bAddNew /* = true */,
									int  nDecPort/*= -1 */)
{
	// 不支持智能分析功能
	if (!devInfo.m_Channel[nChnlIdx].m_bSupportIvs)
	{
		return -1;
	}

	/*============================================
		取设备智能分析规则
	=============================================*/
 	CFG_ANALYSERULES_INFO cfg_rule = {0};
 	IvsRule* pivs_rule = new IvsRule;
	if (pivs_rule == NULL)
	{
		return -1;
	}

 	char szBuffer[64 * 1024] = {0};
 	int  nError;
 	BOOL bSuccess;

	bSuccess = CLIENT_GetNewDevConfig(lDevHandle,CFG_CMD_ANALYSERULE,
									nChnlIdx,szBuffer,sizeof(szBuffer),&nError,3000);

	if (bSuccess)
	{
		int nMaxRuleStructSize = devInfo.m_Channel[nChnlIdx].m_nMaxRuleStructSize;
		int nMaxRuleNum = devInfo.m_Channel[nChnlIdx].m_nMaxRuleNum;
		int nBufLen = (sizeof(CFG_RULE_INFO) + nMaxRuleStructSize) * nMaxRuleNum;
		cfg_rule.pRuleBuf = new char[nBufLen];
		cfg_rule.nRuleLen = nBufLen;
		bSuccess = CLIENT_ParseData(CFG_CMD_ANALYSERULE,szBuffer,
									(char*)&cfg_rule,sizeof(cfg_rule),&nError);
	}
	DWORD dwErr = CLIENT_GetLastError();

	if (!bSuccess)
	{
		return -1;
	}

	/*============================================
		保存各条规则到规则信息表中
	=============================================*/
	IvsChnlInfo* pIvsChnl;
	IvsChnlInfo chnl_info;
	int nRuleIdx;

	chnl_info.dev_id = lDevHandle;
	chnl_info.chnl_idx = nChnlIdx;
 	chnl_info.bEnableIvs = (0 != devInfo.m_Channel[nChnlIdx].m_bEnableIvs);
 	chnl_info.bAtm = devInfo.m_Channel[nChnlIdx].m_bAtmIvs;
	chnl_info.bPreset = 0;
	chnl_info.live_dec_id = nDecPort;

	pIvsChnl = &chnl_info;

	int nLenIndex = 0;
	for(nRuleIdx = 0; nRuleIdx < cfg_rule.nRuleCount && nLenIndex < cfg_rule.nRuleLen; ++nRuleIdx)
	{
		IvsRuleInfo rule = {0};
		CopyMemory(&rule.stuRuleInfo, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_RULE_INFO));
		nLenIndex += sizeof(CFG_RULE_INFO);

		switch(rule.stuRuleInfo.dwRuleType)
		{
			//警戒线
			case EVENT_IVS_CROSSLINEDETECTION:
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_CROSSLINE_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuCrossLineCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_CROSSLINE_INFO));
					nLenIndex += sizeof(CFG_CROSSLINE_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuCrossLineCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuCrossLineCfg.szRuleName, MAX_NAME_LEN);
				}
				break;
			}
			//警戒区
			case EVENT_IVS_CROSSREGIONDETECTION:
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_CROSSREGION_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuCrossRegionCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_CROSSREGION_INFO));
					nLenIndex += sizeof(CFG_CROSSREGION_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuCrossRegionCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuCrossRegionCfg.szRuleName, MAX_NAME_LEN);
				}
				break;
			}
			//ATM贴条
			case EVENT_IVS_PASTEDETECTION:
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_PASTE_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuPasteCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_PASTE_INFO));
					nLenIndex += sizeof(CFG_PASTE_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuPasteCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuPasteCfg.szRuleName, MAX_NAME_LEN);
				}
				break;
			}
			//物品遗留
			case EVENT_IVS_LEFTDETECTION:
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_LEFT_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuLetfCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_LEFT_INFO));
					nLenIndex += sizeof(CFG_LEFT_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuLetfCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuLetfCfg.szRuleName, MAX_NAME_LEN);
				}
				break;
			}
			//人脸检测
			case EVENT_IVS_FACEDETECT:
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_FACEDETECT_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuFaceDetectCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_FACEDETECT_INFO));
					nLenIndex += sizeof(CFG_FACEDETECT_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuFaceDetectCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuFaceDetectCfg.szRuleName, MAX_NAME_LEN);
				}
				break;
			}
			//徘徊
			case EVENT_IVS_WANDERDETECTION:
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_WANDER_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuWanderCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_WANDER_INFO));
					nLenIndex += sizeof(CFG_WANDER_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuWanderCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuWanderCfg.szRuleName, MAX_NAME_LEN);
				}
				break;
			}
			//聚集
			case EVENT_IVS_RIOTERDETECTION:
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_RIOTER_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuRioterCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_RIOTER_INFO));
					nLenIndex += sizeof(CFG_RIOTER_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuRioterCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuRioterCfg.szRuleName, MAX_NAME_LEN);
				}
				break;
			}
			case EVENT_IVS_STAYDETECTION:// 停留事件
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_STAY_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuStayCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_STAY_INFO));
					nLenIndex += sizeof(CFG_STAY_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuStayCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuStayCfg.szRuleName, MAX_NAME_LEN);
				}
			}
			break;
			case EVENT_IVS_PRESERVATION:// 物品保全事件
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_PRESERVATION_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuPreseRvationCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_PRESERVATION_INFO));
					nLenIndex += sizeof(CFG_PRESERVATION_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuPreseRvationCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuPreseRvationCfg.szRuleName, MAX_NAME_LEN);
				}
			}
			break;
			case EVENT_IVS_MOVEDETECTION:// 移动事件
			{
				if (rule.stuRuleInfo.nRuleSize == sizeof(CFG_MOVE_INFO))
				{
					CopyMemory(&rule.ruleEvent.stuMoveCfg, cfg_rule.pRuleBuf + nLenIndex, sizeof(CFG_MOVE_INFO));
					nLenIndex += sizeof(CFG_MOVE_INFO);
					rule.bRuleEnable = rule.ruleEvent.stuMoveCfg.bRuleEnable;
					strncpy(rule.szRuleName, rule.ruleEvent.stuMoveCfg.szRuleName, MAX_NAME_LEN);
				}
			}
			break;	
		}


		if (rule.bRuleEnable)
		{
			pivs_rule->rule_id = nRuleIdx;
			pivs_rule->trigger_cnt = 0;
			CopyMemory(&pivs_rule->ruleInfo,&rule,sizeof(rule));

			pIvsChnl->rule_map.insert(std::make_pair(nRuleIdx,pivs_rule));
		}
	}
	delete[] cfg_rule.pRuleBuf;

	/*============================================
		查找设备通道信息,更新内存中的设备通道(规则)信息表
	=============================================*/
	std::list<IvsChnlInfo>::iterator	itor;
	bool bFound = false;

	itor = m_chnl_info_list.begin();

	for(; itor != m_chnl_info_list.end(); itor++)
	{
		if ((itor->dev_id == devInfo.m_ID) && (itor->chnl_idx == nChnlIdx))
		{
			bFound = true;
			break;
		}
	}

	if (bFound)
	{
		int nOldDecPort = itor->live_dec_id;

		*itor = *pIvsChnl;

		if (nOldDecPort >= 0)
		{
			itor->live_dec_id = nOldDecPort;
		}
		else if (nDecPort >= 0)
		{
			itor->live_dec_id = nDecPort;
		}

		return 0;
	}
	else if (bAddNew)
	{
		m_chnl_info_list.push_back(chnl_info);
		return 0;
	}
	else
	{
		return -1;
	}
}


//************************************
// 方法:	protected static CIvsLogic::DrawIvsRuleProc
// 摘要:	  在视频画面上绘制智能分析规则
// 返回:
//		int
// 参数:
//		IvsChnlInfo * pChnlInfo		解码通道信息
//		HDC hdc						设备环境
//************************************
int CIvsModule::DrawIvsRuleProc(IvsChnlInfo* pChnlInfo,HDC hdc)
{
	const int nLineWidth = 2;
	IvsRuleMap::iterator itor_rule;
	IvsRule* pIvsRule;

	itor_rule = pChnlInfo->rule_map.begin();

	for(; itor_rule != pChnlInfo->rule_map.end(); ++itor_rule)
	{
		pIvsRule = itor_rule->second;

		if (pIvsRule->ruleInfo.bRuleEnable)
		{
			if (pIvsRule->trigger_cnt > 0)
			{
				--pIvsRule->trigger_cnt;

				if (0 == pIvsRule->trigger_cnt % 5)
				{
					continue;
				}
				else
				{
					SetDCPenColor(hdc,Color_RuleAlarm);
					SetTextColor(hdc,Color_RuleAlarm);
				}
			}
			else
			{
				SetDCPenColor(hdc,Color_RuleNormal);
				SetTextColor(hdc,Color_RuleNormal);
			}

			DrawIvsRule(pIvsRule,hdc);
		}
	}

	return 0;
}

//************************************
// 方法:	protected static CIvsLogic::DrawIvsRule
// 摘要:	  绘制智能分析规则
// 返回:
// 参数:
//		IvsRule * pIvsRule		规则信息
//		HDC hdc					设备环境
//************************************
void CIvsModule::DrawIvsRule(IvsRule* pIvsRule,HDC hdc)
{
	IvsRuleInfo& rule = pIvsRule->ruleInfo;
	int nRuleType = pIvsRule->ruleInfo.stuRuleInfo.dwRuleType;

	CFG_POLYLINE* pRulePoint = NULL;
	int nPtCnt =0 ,nPtIdx;

	CFG_POLYLINE* pRulePoint2 = NULL;  //围栏需要使用
	int nPtCnt2 =0 ;

	bool bRuleEnable = false;
	switch(nRuleType)
	{
		// 警戒线
	case EVENT_IVS_CROSSLINEDETECTION:
		nPtCnt = rule.ruleEvent.stuCrossLineCfg.nDetectLinePoint;
		pRulePoint = rule.ruleEvent.stuCrossLineCfg.stuDetectLine;
		break;

		// 警戒区
	case EVENT_IVS_CROSSREGIONDETECTION:
		nPtCnt = rule.ruleEvent.stuCrossRegionCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuCrossRegionCfg.stuDetectRegion);
		break;

		// ATM贴条
	case EVENT_IVS_PASTEDETECTION:
		nPtCnt = rule.ruleEvent.stuPasteCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuPasteCfg.stuDetectRegion);
		break;

		//物品遗留
	case EVENT_IVS_LEFTDETECTION:
		nPtCnt = rule.ruleEvent.stuLetfCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuLetfCfg.stuDetectRegion);
		break;

		//人脸检测
	case EVENT_IVS_FACEDETECT:
		nPtCnt = rule.ruleEvent.stuFaceDetectCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuFaceDetectCfg.stuDetectRegion);
		break;

		//徘徊
	case EVENT_IVS_WANDERDETECTION:
		nPtCnt = rule.ruleEvent.stuWanderCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuWanderCfg.stuDetectRegion);
		break;

		//聚集
	case EVENT_IVS_RIOTERDETECTION:
		nPtCnt = rule.ruleEvent.stuRioterCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuRioterCfg.stuDetectRegion);
		break;
	case EVENT_IVS_STAYDETECTION:
		nPtCnt = rule.ruleEvent.stuStayCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuStayCfg.stuDetectRegion);
		break;
	case EVENT_IVS_PRESERVATION:// 物品保全事件
		nPtCnt = rule.ruleEvent.stuPreseRvationCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuPreseRvationCfg.stuDetectRegion);
		break;
	case EVENT_IVS_MOVEDETECTION:// 移动事件
		nPtCnt = rule.ruleEvent.stuMoveCfg.nDetectRegionPoint;
		pRulePoint = (CFG_POLYLINE*)(rule.ruleEvent.stuMoveCfg.stuDetectRegion);
		break;
	case EVENT_IVS_VIDEOABNORMALDETECTION:// 视频异常事件
		nPtCnt = 0;
		pRulePoint = NULL;
		break;
	}

	if ((NULL == pRulePoint) || (nPtCnt <= 1))
	{
		return;
	}

	/*============================================
		连接定义规则的各个点
	=============================================*/

	MoveToEx(hdc,pRulePoint[0].nX,pRulePoint[0].nY,NULL);

	for(nPtIdx = 1; nPtIdx < nPtCnt; ++nPtIdx)
	{
		LineTo(hdc,pRulePoint[nPtIdx].nX,pRulePoint[nPtIdx].nY);
	}

	switch(nRuleType)
	{
	case EVENT_IVS_CROSSLINEDETECTION://警戒线: 绘制方向标识
		{
			if(nPtCnt >= 2 && pRulePoint != NULL)
			{
				POINT ptStart,ptEnd;

				int nDirection = rule.ruleEvent.stuCrossLineCfg.nDirection;
				for(nPtIdx = 0; nPtIdx < nPtCnt -1 ; ++nPtIdx)
				{
					ptStart.x = pRulePoint[nPtIdx].nX;
					ptStart.y = pRulePoint[nPtIdx].nY;

					ptEnd.x = pRulePoint[(nPtIdx + 1) % nPtCnt].nX;
					ptEnd.y = pRulePoint[(nPtIdx + 1) % nPtCnt].nY;

					int nDistance = sqrt((double)((ptEnd.x - ptStart.x) * (ptEnd.x - ptStart.x) + (ptEnd.y - ptStart.y) * (ptEnd.y - ptStart.y)));
					if (nDistance > Min_Distance)
					{
						DrawDirectionArrow(hdc,ptStart,ptEnd,nDirection);
					}
				}

			}

		}
		break;
	case EVENT_IVS_CROSSREGIONDETECTION: //警戒区: 在每一条边上绘制方向标识
		{
			LineTo(hdc,pRulePoint[0].nX,pRulePoint[0].nY);
			int nDirection = rule.ruleEvent.stuCrossRegionCfg.nDirection;
			HRGN hrgn = CreatePolygonRgn((const POINT*)pRulePoint,nPtCnt,WINDING);
			POINT ptStart,ptEnd;
			if(hrgn != NULL)
			{
				for(nPtIdx = 0; nPtIdx < nPtCnt; ++nPtIdx)
				{
					ptStart.x = pRulePoint[nPtIdx].nX;
					ptStart.y = pRulePoint[nPtIdx].nY;

					ptEnd.x = pRulePoint[(nPtIdx + 1) % nPtCnt].nX;
					ptEnd.y = pRulePoint[(nPtIdx + 1) % nPtCnt].nY;

					int nDistance = sqrt((double)((ptEnd.x - ptStart.x) * (ptEnd.x - ptStart.x) + (ptEnd.y - ptStart.y) * (ptEnd.y - ptStart.y)));
					if (nDistance > Min_Distance)
					{
						DrawDirectionArrow(hdc,ptStart,ptEnd,nDirection,hrgn);
					}
				}
				DeleteObject(hrgn);
			}


		}
		break;
	default:
		LineTo(hdc,pRulePoint[0].nX,pRulePoint[0].nY);
		break;
	}

	TextOutA(hdc,pRulePoint[0].nX,pRulePoint[0].nY,
		pIvsRule->ruleInfo.szRuleName,lstrlenA(pIvsRule->ruleInfo.szRuleName));
}

//************************************
// 方法:	public CIvsLogic::DrawDirectionArrow
// 摘要:	  绘制警戒线方向箭头
// 返回:
//		void
// 参数:
//		HDC hdc
//		POINT ptStart		起点
//		POINT ptEnd			终点
//		int nDirection		方向
//		HRGN hrgn			默认值为NULL,不为NULL时表示为警戒区的一条边绘制方向箭头
//							此时nDireciton参数表示警戒区方向(进出警戒区)
//************************************
void CIvsModule::DrawDirectionArrow(HDC hdc,POINT ptStart,POINT ptEnd,int nDirection,HRGN hrgn /*=NULL*/)
{
	double angle;
	XFORM xform;
	POINT ptTemp,ptA,ptB;
	SIZE szView;
	int arrow_len,tmp_len;

	if ((nDirection < 0) || (nDirection > 2))
	{
		return;
	}

	SaveDC(hdc);
	GetViewportExtEx(hdc,&szView);

	LPtoDP(hdc,&ptStart,1);
	LPtoDP(hdc,&ptEnd,1);

	SetMapMode(hdc,MM_ISOTROPIC);
	SetViewportExtEx(hdc,szView.cx,szView.cy,NULL);
	SetWindowExtEx(hdc,IVS_VIDEO_WIDTH,IVS_VIDEO_HEIGHT,NULL);
	SetViewportOrgEx(hdc,0,0,NULL);

	DPtoLP(hdc,&ptStart,1);
	DPtoLP(hdc,&ptEnd,1);

	// 箭头顶部到警戒线的距离为20个像素点
	ptTemp.x = ptTemp.y = 20;
	DPtoLP(hdc,&ptTemp,1);
	arrow_len = ptTemp.x;

	/*
		取警戒线中点为世界坐标系原点,x轴与警戒线重合,且正方向向上,
		y轴垂直于警戒线.世界坐标系旋转angle弧度后与页面坐标系重合.
		1 顺时针旋转时角度为负值,逆时针旋转角度为正值.
		2 页面坐标系x轴水平向右,y轴垂直向下
	*/
	if (ptEnd.x != ptStart.x)
	{
		angle = atan2(1.0 * (ptEnd.y - ptStart.y),1.0 * (ptEnd.x - ptStart.x));
	}
	else if (ptEnd.y - ptStart.y >= 0)
	{
		angle = M_PI / 2;
	}
	else
	{
		angle = -M_PI / 2;
	}

	// 坐标系原点平移到警戒线中点,然后旋转使得x轴与警戒线重合
	xform.eM11 = float(cos(angle));
	xform.eM12 = float(sin(angle));
	xform.eM21 = float(-sin(angle));
	xform.eM22 = float(cos(angle));
	xform.eDx  = ((ptStart.x + ptEnd.x) / 2.0f);
	xform.eDy  = ((ptStart.y + ptEnd.y) / 2.0f);

	SetGraphicsMode(hdc,GM_ADVANCED);
	SetWorldTransform(hdc,&xform);

	// 绘制与x轴垂直的线段,因为x轴与警戒线重合,所以绘制出的线段也是与警戒线垂直的
	MoveToEx(hdc,0,arrow_len,NULL);
	LineTo(hdc,0,-arrow_len);

	// 绘制箭头.箭头长10个像素点,箭头角度60度(M_PI / 3)
	tmp_len = int(arrow_len / 2.0 * tan(M_PI / 6));

	ptA.x = 0;
	ptA.y = -arrow_len;
	ptB.x = 0;
	ptB.y = arrow_len;

	/*============================================
		为警戒线绘制方向箭头
	=============================================*/
	if (NULL == hrgn)
	{
		// R --> L
		if ((1 == nDirection) || (2 == nDirection))
		{
			MoveToEx(hdc,0,-arrow_len,NULL);
			LineTo(hdc,tmp_len,-arrow_len / 2);

			MoveToEx(hdc,0,-arrow_len,NULL);
			LineTo(hdc,-tmp_len,-arrow_len / 2);
		}

		// L --> R
		if ((0 == nDirection) || (2 == nDirection))
		{
			MoveToEx(hdc,0,arrow_len,NULL);
			LineTo(hdc,tmp_len,arrow_len / 2);

			MoveToEx(hdc,0,arrow_len,NULL);
			LineTo(hdc,-tmp_len,arrow_len / 2);
		}

		RestoreDC(hdc,-1);
	}
	/*============================================
		为警戒区的一条边绘制方向箭头
	=============================================*/
	else
	{
		LPtoDP(hdc,&ptA,1);
		LPtoDP(hdc,&ptB,1);

		RestoreDC(hdc,-1);

		DPtoLP(hdc,&ptA,1);
		DPtoLP(hdc,&ptB,1);

		BOOL aInRgn = PtInRegion(hrgn,ptA.x,ptA.y);
		BOOL bInRgn = PtInRegion(hrgn,ptB.x,ptB.y);
		while (!aInRgn && !bInRgn)
		{
			ptA.y += 10;
			ptB.y -= 10;
			//BOOL aInRgn = PtInRegion(hrgn,ptA.x,ptA.y);
			//BOOL bInRgn = PtInRegion(hrgn,ptB.x,ptB.y);
			aInRgn = PtInRegion(hrgn,ptA.x,ptA.y);
			bInRgn = PtInRegion(hrgn,ptB.x,ptB.y);

		}

		POINT ptArrow,ptOther;

		SaveDC(hdc);

		SetMapMode(hdc,MM_ISOTROPIC);
		SetViewportExtEx(hdc,szView.cx,szView.cy,NULL);
		SetWindowExtEx(hdc,IVS_VIDEO_WIDTH,IVS_VIDEO_HEIGHT,NULL);
		SetViewportOrgEx(hdc,0,0,NULL);

		SetGraphicsMode(hdc,GM_ADVANCED);
		SetWorldTransform(hdc,&xform);

		ptA.x = 0;
		ptA.y = -arrow_len;
		ptB.x = 0;
		ptB.y = arrow_len;

		// 进入区域
		if ((0 == nDirection) || (2 == nDirection))
		{
			if (aInRgn)
			{
				ptArrow = ptA;
				ptOther = ptB;
			}
			else if (bInRgn)
			{
				ptArrow = ptB;
				ptOther = ptA;
			}
			//else
			//{
			//	return;
			//}
		}
		// 离开区域
		else if ((1 == nDirection) || (2 == nDirection))
		{
			if (!aInRgn)
			{
				ptArrow = ptA;
				ptOther = ptB;
			}
			else if (!bInRgn)
			{
				ptArrow = ptB;
				ptOther = ptA;
			}
			//else
			//{
			//	return;
			//}
		}

		if (ptArrow.y < 0)
		{
			arrow_len = (-1) * arrow_len;
		}

		MoveToEx(hdc,ptArrow.x,ptArrow.y,NULL);
		LineTo(hdc,tmp_len,arrow_len / 2);

		MoveToEx(hdc,ptArrow.x,ptArrow.y,NULL);
		LineTo(hdc,-tmp_len,arrow_len / 2);

		// 进入/离开区域
		if (2 == nDirection)
		{
			arrow_len = (-1) * arrow_len;

			MoveToEx(hdc,ptOther.x,ptOther.y,NULL);
			LineTo(hdc,tmp_len,arrow_len / 2);

			MoveToEx(hdc,ptOther.x,ptOther.y,NULL);
			LineTo(hdc,-tmp_len,arrow_len / 2);
		}

		RestoreDC(hdc,-1);
	}
}

//************************************
// 方法:	protected static CIvsLogic::DrawIvsObjectProc
// 摘要:		在视频画面上绘制运动轨迹和运动目标外框
// 返回:
//		int
// 参数:
//		IvsDecodeInfo * pDecodeInfo	解码信息
//		HDC hdc						设备环境
//************************************
int CIvsModule::DrawIvsObjectProc(IvsChnlInfo* pChnlInfo,IvsDecodeInfo* pDecInfo,HDC hdc)
{
	IvsObjectMap::iterator itor_obj;
	IvsObjectMap::iterator itor_end;
	IvsObject* pIvsObj;
	bool bNotShow;

	//add by wanglei 2011-01-11
	//增加判断规则是否包含警戒线或者警戒区，若不包含则不画运动目标轨迹
	IvsRuleMap::iterator itor_rule;
	bool bShowocus = false;
	itor_rule = pChnlInfo->rule_map.begin();
	for(; itor_rule != pChnlInfo->rule_map.end(); ++itor_rule)
	{
		if (EVENT_IVS_CROSSLINEDETECTION == itor_rule->second->ruleInfo.stuRuleInfo.dwRuleType 
			|| EVENT_IVS_CROSSREGIONDETECTION == itor_rule->second->ruleInfo.stuRuleInfo.dwRuleType
			/*|| EVENT_IVS_CROSSFENCEDETECTION ==itor_rule->second.ruleInfo.stuRuleInfo.dwRuleType
			|| EVENT_IVS_RETROGRADEDETECTION == itor_rule->second.ruleInfo.stuRuleInfo.dwRuleType
			|| EVENT_IVS_ABNORMALRUNDETECTION == itor_rule->second.ruleInfo.stuRuleInfo.dwRuleType*/)
		{
			bShowocus = true;
			break;
		}
	}

	// 对于每个运动目标
	itor_end = pChnlInfo->mapId2Obj.end();
	itor_obj = pChnlInfo->mapId2Obj.begin();

	while(itor_obj != itor_end)
	{
		bNotShow = false;

		pIvsObj = &(itor_obj->second);

		// 目标触发报警
		if (pIvsObj->alarm_cnt > 0)
		{
			if (0 == pIvsObj->alarm_cnt % 5)
			{
				bNotShow = true;
			}
			else
			{
				SetDCPenColor(hdc,Color_LocusAlarm);
			}
		}
		// 目标正常运动
		else
		{
			SetDCPenColor(hdc,Color_LocusNormal);
		}

		if (!bNotShow && pIvsObj->opt_type != IvsOjbOpt_HideLocus)
		{
			// 绘制各段运动轨迹
			if (pDecInfo->bShowLocus && bShowocus)
			{
				DrawIvsObjectLocus(pIvsObj,hdc);
			}

			// 绘制运动目标外框
			if (pDecInfo->bShowObj)
			{
				DrawIvsObjectBoundBox(pIvsObj,hdc);
			}
		}

		// 报警计数和显示计数修正
		if (pIvsObj->display_cnt > 0)
		{
			--pIvsObj->display_cnt;
		}

		if (pIvsObj->alarm_cnt > 0)
		{
			--pIvsObj->alarm_cnt;
		}

		if (pIvsObj->display_cnt <= 0)
		{
			itor_obj = pChnlInfo->mapId2Obj.erase(itor_obj);
		}
		else
		{
			++itor_obj;
		}
	}

	return 0;
}

//绘制轨迹
void CIvsModule::DrawIvsObjectLocus(IvsObject* pIvsObj, HDC hdc)
{
	const int X_SCALE = IVS_VIDEO_WIDTH  / LOCUS_WIDTH;
	const int Y_SCALE = IVS_VIDEO_HEIGHT / LOCUS_HEIGHT;

	bool bFirstPoint = true;
	POINT lastPoint[2] = {{-1,-1},{-1,-1}};
	IvsLocus::iterator itor_seg;
	IvsLocusSeg::iterator itor_pt;

	itor_seg = pIvsObj->obj_locus.begin();

	// 绘制轨迹段
	for( ; itor_seg != pIvsObj->obj_locus.end(); itor_seg++)
	{
		itor_pt = itor_seg->begin();

		for (; itor_pt != itor_seg->end(); itor_pt++)
		{
			if (bFirstPoint)
			{
				MoveToEx(hdc,X_SCALE * itor_pt->nX,Y_SCALE * itor_pt->nY,NULL);
				bFirstPoint = false;
			}
			else
			{
				LineTo(hdc,X_SCALE * itor_pt->nX,Y_SCALE * itor_pt->nY);
			}

			lastPoint[1] = lastPoint[0];
			lastPoint[0].x = itor_pt->nX;
			lastPoint[0].y = itor_pt->nY;
		}
	}

	// 轨迹方向
	/*
	if ((lastPoint[0].x >= 0) && (lastPoint[0].y >= 0)
		&& (lastPoint[1].x >= 0) && (lastPoint[1].y >= 0))
	{
		DrawLocusDirectionArrow(hdc,lastPoint[1],lastPoint[0]);
	}
	*/
}

//绘制目标外框
void CIvsModule::DrawIvsObjectBoundBox(IvsObject* pIvsObj, HDC hdc)
{
	const int X_SCALE = IVS_VIDEO_WIDTH  / LOCUS_WIDTH;
	const int Y_SCALE = IVS_VIDEO_HEIGHT / LOCUS_HEIGHT;
	
	IvsRect& rc = pIvsObj->obj_rect;
	
	MoveToEx(hdc,	X_SCALE*rc.left,	Y_SCALE*rc.top,NULL);	// 左上
	LineTo(hdc,		X_SCALE*rc.right,	Y_SCALE*rc.top);		// ==> 右上
	LineTo(hdc,		X_SCALE*rc.right,	Y_SCALE*rc.bottom);		// ==> 右下
	LineTo(hdc,		X_SCALE*rc.left,	Y_SCALE*rc.bottom);		// ==> 左下
	LineTo(hdc,		X_SCALE*rc.left,	Y_SCALE*rc.top);		// ==> 左上
}

// 从码流中提取智能分析信息
void __stdcall CIvsModule::GetIvsInfoProc(char* pBuf,long nKey,
										 long  nObjLen,long nTotalLen,
										 void*  nType,
										 void*  nUser)
{
	if (NULL == pBuf)
	{
		return;
	}

	EnterCriticalSection(&m_cs);
	std::map<int,IvsDecodeInfo>::iterator itor_decode;
	std::list<IvsChnlInfo>::iterator itor_chnl;
	/*============================================
		场景更新
	=============================================*/
	if (IVSINFOTYPE_PRESETPOS == nKey)
	{
		int nDecPort = *(int*)nType;
		DWORD dwPresetPos = *(DWORD*)pBuf;
		
		itor_decode = m_decode_info_map.find(nDecPort);
		
		if (itor_decode != m_decode_info_map.end())
		{
			itor_chnl = m_chnl_info_list.begin();
			
			for(; itor_chnl != m_chnl_info_list.end(); ++itor_chnl)
			{
				if ((itor_chnl->dev_id == itor_decode->second.dev_id)
					&& (itor_chnl->chnl_idx == itor_decode->second.chnl_idx))
				{
					break;
				}
			}
			
			if (itor_chnl != m_chnl_info_list.end())
			{
				if (itor_chnl->bPreset != (BYTE)dwPresetPos)
				{
					if (0 == nTotalLen)
					{
						itor_chnl->bPreset = 0xFF;
					}
					else
					{
						itor_chnl->bPreset = (BYTE)dwPresetPos;
					}
				}
			}
		}
	}
	/*============================================
		运动轨迹
	=============================================*/
	else if (IVSINFOTYPE_MOTINTRKS == nKey)
	{
		PRIVATE_IVS_OBJ* pIvsObj = (PRIVATE_IVS_OBJ*)pBuf;

		itor_decode = m_decode_info_map.find(pIvsObj->decode_id);

		if (itor_decode == m_decode_info_map.end())
		{
			LeaveCriticalSection(&m_cs);
			return;
		}
		else
		{
			itor_chnl = m_chnl_info_list.begin();

			for(; itor_chnl != m_chnl_info_list.end(); ++itor_chnl)
			{
				if ((itor_chnl->dev_id == itor_decode->second.dev_id)
					&& (itor_chnl->chnl_idx == itor_decode->second.chnl_idx))
				{
					break;
				}
			}

			if (itor_chnl == m_chnl_info_list.end())
			{
				LeaveCriticalSection(&m_cs);
				return;
			}
		}

		IvsChnlInfo* pChnlInfo = &(*itor_chnl);

		if (pIvsObj->decode_id != pChnlInfo->live_dec_id)
		{
			return;
		}
		// 解码通道IVS数据丢失,清空运动目标列表
		else if (2 == *(int*)nType)
		{
			itor_chnl->mapId2Obj.clear();
		}
		// 添加/更新运动目标信息
		else if (1 == *(int*)nType)
		{
			IvsObjectMap::iterator itor_obj;
			IvsObjectMap::iterator itor_end;
			int nIdx,nObjCnt;

			itor_end = pChnlInfo->mapId2Obj.end();

			nObjCnt = nTotalLen / nObjLen;

			for (nIdx = 0; nIdx < nObjCnt; ++nIdx)
			{
				pIvsObj = (PRIVATE_IVS_OBJ*)(pBuf + nIdx * sizeof(PRIVATE_IVS_OBJ));

				itor_obj = pChnlInfo->mapId2Obj.find(pIvsObj->obj_id);
				if (IvsOjbOpt_DelOjb == pIvsObj->operator_type)
				{
					if (itor_obj != itor_end)
					{
						//if (itor_obj->second.display_cnt <= 0)
						{
							pChnlInfo->mapId2Obj.erase(itor_obj);
							itor_end = pChnlInfo->mapId2Obj.end();
						}
					}
				}
				else
				{
					IvsLocusSeg   locus_seg;
					PRIVATE_IVS_POINT* p_last_pt = NULL;
					CFG_POLYLINE ivs_point;
					int nPointIdx;

					for(nPointIdx = 0;
						(nPointIdx < pIvsObj->trackpt_num) && (nPointIdx < MAX_TRACKPOINT_NUM);
						++nPointIdx)
					{
						ivs_point.nX = pIvsObj->track_point[nPointIdx].x;
						ivs_point.nY = pIvsObj->track_point[nPointIdx].y;
						locus_seg.push_back(ivs_point);
					}

					if (nPointIdx > 0)
					{
						p_last_pt =  &(pIvsObj->track_point[nPointIdx - 1]);
					}
					else
					{
						if (itor_obj != itor_end)
						{
							itor_obj->second.opt_type = pIvsObj->operator_type;
						}
						continue;
					}

					// 新增一个运动目标,在其运动轨迹段列表中加入第一段运动轨迹
					if (itor_obj == itor_end)
					{
						IvsObject ivs_obj;

						ivs_obj.object_id  = pIvsObj->obj_id;
						ivs_obj.opt_type = pIvsObj->operator_type;
						ivs_obj.alarm_cnt   = 0;
						ivs_obj.display_cnt = IVS_INFO_SHOW_FRAMES;

						ivs_obj.obj_rect.left   = p_last_pt->x - p_last_pt->xSize;
						ivs_obj.obj_rect.right  = p_last_pt->x + p_last_pt->xSize;
						ivs_obj.obj_rect.top    = p_last_pt->y - p_last_pt->ySize;
						ivs_obj.obj_rect.bottom = p_last_pt->y + p_last_pt->ySize;

						ivs_obj.obj_locus.push_back(locus_seg);

						pChnlInfo->mapId2Obj.insert(std::make_pair(pIvsObj->obj_id,ivs_obj));
						
						if (pChnlInfo->mapId2Obj.size() > MAX_IVS_OBJECT_CNT)
						{
							itor_obj = pChnlInfo->mapId2Obj.begin();
							pChnlInfo->mapId2Obj.erase(itor_obj);
						}
					}
					// 在已有运动目标的运动轨迹段列表中增加一段运动轨迹
					else
					{
						itor_obj->second.opt_type = pIvsObj->operator_type;
						itor_obj->second.obj_locus.push_back(locus_seg);

						itor_obj->second.display_cnt = IVS_INFO_SHOW_FRAMES;

						itor_obj->second.obj_rect.left   = p_last_pt->x - p_last_pt->xSize;
						itor_obj->second.obj_rect.right  = p_last_pt->x + p_last_pt->xSize;
						itor_obj->second.obj_rect.top    = p_last_pt->y - p_last_pt->ySize;
						itor_obj->second.obj_rect.bottom = p_last_pt->y + p_last_pt->ySize;

						if (itor_obj->second.obj_locus.size() > MAX_IVS_LOCUS_SEG_CNT)
						{
							itor_obj->second.obj_locus.pop_front();
						}
					}
				}
			}
		}
	}

	LeaveCriticalSection(&m_cs);
}

CIvsModule::~CIvsModule()
{
	IvsChnlInfo* pChnlInfo = NULL;
	
	std::list<IvsChnlInfo>::iterator itor_chnl;
	
	itor_chnl = m_chnl_info_list.begin();
	
	for(; itor_chnl != m_chnl_info_list.end(); ++itor_chnl)
	{
		pChnlInfo = &(*itor_chnl);

		{
			std::map<int,IvsRule*>::iterator it = pChnlInfo->rule_map.begin();
			while (it != pChnlInfo->rule_map.end())
			{
				IvsRule *pIvsRule = (*it).second;
				if (pIvsRule != NULL)
				{
					delete pIvsRule;
				}
				it++;
			}
			pChnlInfo->rule_map.clear();
		}
	}	
}

//************************************
// 方法:	public static CIvsLogic::DrawIvsInfoProc
// 摘要:	  在视频画面上绘制智能分析信息(规则,运动目标外框和运动轨迹)
// 返回:
//		int		0: 成功		<0: 失败
// 参数:
//		HDC hdc			设备环境
//		long nPort		解码句柄
//		LONG nUser		用户参数
//************************************
void CIvsModule::DrawIvsInfoProc(long nPort,HDC hdc,LONG nUser)
{
	//AX_Write_Guard<AX_RW_Mutex> lock_write(mutex);

	IvsChnlInfo* pChnlInfo = NULL;
	IvsDecodeInfo* pDecInfo = NULL;

	std::map<int,IvsDecodeInfo>::iterator itor_decode;
	std::list<IvsChnlInfo>::iterator itor_chnl;

	itor_decode = m_decode_info_map.find(nPort);
	if (itor_decode == m_decode_info_map.end())
	{
		return;
	}

	itor_chnl = m_chnl_info_list.begin();

	for(; itor_chnl != m_chnl_info_list.end(); ++itor_chnl)
	{
		if ((itor_chnl->dev_id == itor_decode->second.dev_id)
			&& (itor_chnl->chnl_idx == itor_decode->second.chnl_idx))
		{
			break;
		}
	}

	if (itor_chnl == m_chnl_info_list.end())
	{
		return;
	}

	pDecInfo  = &(itor_decode->second);
	pChnlInfo = &(*itor_chnl);

	if (!(pChnlInfo->bEnableIvs))
	{
		return;
	}

	/*============================================
		准备设备环境: 设置映射模式,设置字体
	=============================================*/
	RECT rcVideoWnd;
	LONG nWidth,nHeight;

	FromHandle(pDecInfo->hwnd)->GetWindowRect(&rcVideoWnd);
	//GetWindowRect(pDecInfo->hwnd ,&rcVideoWnd);
	nWidth  = rcVideoWnd.right  - rcVideoWnd.left;
	nHeight = rcVideoWnd.bottom - rcVideoWnd.top;
	if ((nWidth <= 0) || (nHeight <= 0))
	{
		return;
	}

	SaveDC(hdc);

	SetBkMode(hdc,TRANSPARENT);
	SetMapMode(hdc,MM_ANISOTROPIC);
	SetViewportExtEx(hdc,nWidth,nHeight,NULL);
	SetWindowExtEx(hdc,IVS_VIDEO_WIDTH,IVS_VIDEO_HEIGHT,NULL);
	SetViewportOrgEx(hdc,0,0,NULL);
	SelectObject(hdc,GetStockObject(DC_PEN));

	// 设置字体为系统默认GUI字体
	LOGFONT logfont={0};
	HFONT hFont;
	POINT pt;

	pt.x = pt.y = HIWORD(GetDialogBaseUnits());
	DPtoLP(hdc,&pt,1);

	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	if (sizeof(logfont) == GetObject(hFont,sizeof(logfont),&logfont))
	{
		logfont.lfHeight = -1 * abs(pt.x);
		hFont = CreateFontIndirect(&logfont);
		SelectObject(hdc,(HGDIOBJ)hFont);
	}
	else
	{
		SelectObject(hdc,(HGDIOBJ)hFont);
		hFont = NULL;
	}

	/*============================================
		绘制智能分析规则和目标运动轨迹与外框
	=============================================*/

	if (pDecInfo->bShowRule)
	{
		DrawIvsRuleProc(pChnlInfo,hdc);
	}

	if (pDecInfo->bShowLocus || pDecInfo->bShowObj)
	{
		DrawIvsObjectProc(pChnlInfo,pDecInfo,hdc);
	}

	RestoreDC(hdc,-1);
	DeleteObject((HGDIOBJ)hFont);

	return;
}

void CIvsModule::ClearData()
{
	m_decode_info_map.clear();
	m_chnl_info_list.clear();
}