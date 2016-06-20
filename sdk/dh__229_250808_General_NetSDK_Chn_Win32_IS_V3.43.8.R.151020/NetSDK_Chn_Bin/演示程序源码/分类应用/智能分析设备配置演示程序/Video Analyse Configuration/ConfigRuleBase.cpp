// ConfigRuleBase.cpp : implementation file
//

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "ConfigRuleBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigRuleBase dialog


CConfigRuleBase::CConfigRuleBase(DWORD dwCmd)
{
	m_dwCmd = dwCmd;
}

CConfigRuleBase::~CConfigRuleBase()
{
	if (m_stuInfo != NULL)
	{
		delete m_stuInfo;
		m_stuInfo = NULL;
	}
}

/*
void CConfigRuleBase::GetRuleInfo(CConfigRules* pParentWnd, long lLoginId, 
									   void* pInfo, int nChannelId)
{
	if (pParentWnd != NULL)
	{
		m_pParentWnd = pParentWnd;
		
		m_lLoginId = lLoginId;
		
		m_nCurrentChannel = nChannelId;
		
		switch (m_dwCmd)
		{
		case EVENT_IVS_CROSSLINEDETECTION:
			{
				m_stuInfo = new CFG_CROSSLINE_INFO;
				if (pInfo != NULL && m_stuInfo != NULL)
				{
					memset(&m_stuInfo, 0, sizeof(CFG_CROSSLINE_INFO));
					memcpy(&m_stuInfo, pInfo, sizeof(CFG_CROSSLINE_INFO));
				}
			}
			break;
		case EVENT_IVS_CROSSREGIONDETECTION:
			{
				m_stuInfo = new CFG_CROSSREGION_INFO;
				if (pInfo != NULL && m_stuInfo != NULL)
				{		
					memset(&m_stuInfo, 0, sizeof(CFG_CROSSREGION_INFO));
					memcpy(&m_stuInfo, pInfo, sizeof(CFG_CROSSREGION_INFO));
				}
			}
			break;
		case EVENT_IVS_FACEDETECT:
			{
				m_stuInfo = new CFG_FACEDETECT_INFO;

				if (pInfo != NULL && m_stuInfo != NULL)
				{
					memset(&m_stuInfo, 0, sizeof(CFG_FACEDETECT_INFO));
					memcpy(&m_stuInfo, pInfo, sizeof(CFG_FACEDETECT_INFO));
				}
			}
			break;
		case EVENT_IVS_PASTEDETECTION:
			{
				m_stuInfo = new CFG_PASTE_INFO;
				if (pInfo != NULL && m_stuInfo != NULL)
				{
					memset(&m_stuInfo, 0, sizeof(CFG_PASTE_INFO));
					memcpy(&m_stuInfo, pInfo, sizeof(CFG_PASTE_INFO));
				}
			}
			break;
		case EVENT_IVS_RIOTERDETECTION:
			{
				m_stuInfo = new CFG_RIOTER_INFO;
				if (pInfo != NULL && m_stuInfo != NULL)
				{
					memset(&m_stuInfo, 0, sizeof(CFG_RIOTER_INFO));
					memcpy(&m_stuInfo, pInfo, sizeof(CFG_RIOTER_INFO));
				}
			}
			break;
		case EVENT_IVS_WANDERDETECTION:
			{
				m_stuInfo = new CFG_WANDER_INFO;
				if (pInfo != NULL && m_stuInfo != NULL)
				{
					memset(&m_stuInfo, 0, sizeof(CFG_WANDER_INFO));
					memcpy(&m_stuInfo, pInfo, sizeof(CFG_WANDER_INFO));
				}
			}
			break;
		default:
			break;
		}
	}
	
	return;
}

void CConfigRuleBase::ShowRuleInfo()
{
	int nObjectTypeNum = 0;
	char				szObjectTypes[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];		// 相应物体类型列表
	switch (m_dwCmd)
	{
	case EVENT_IVS_CROSSLINEDETECTION:
		{
			CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)m_stuInfo;
			if (NULL == pInfo)
				return;
			m_strRuleName = pInfo->szRuleName;
			m_bEnable = pInfo->bRuleEnable;

			nObjectTypeNum = pInfo->nObjectTypeNum;
			memcpy((void*)szObjectTypes,pInfo->szObjectTypes,sizeof(szObjectTypes));

			{
				CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_DIRECT);
				if (pBox)
				{
					int n = pBox->GetCount();
					if (pInfo->nDirection < n)
					{
						pBox->SetCurSel(pInfo->nDirection);
					}
				}
			}
			
			{
				CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO2);
				if (pBox)
				{
					int n = pBox->GetCount();
					if (pInfo->nTriggerPosition < n)
					{
						pBox->SetCurSel(pInfo->nTriggerPosition);
					}
				}
			}
	
		}
		break;
	case EVENT_IVS_CROSSREGIONDETECTION:
		{
			CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)m_stuInfo;
			if (NULL == pInfo)
				return;
		}
		break;
	case EVENT_IVS_FACEDETECT:
		{
			CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)m_stuInfo;
			if (NULL == pInfo)
				return;
		}
		break;
	case EVENT_IVS_PASTEDETECTION:
		{
			CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)m_stuInfo;
			if (NULL == pInfo)
				return;
		}
		break;
	case EVENT_IVS_RIOTERDETECTION:
		{
			CFG_CROSSLINE_INFO* pInfo = (CFG_CROSSLINE_INFO*)m_stuInfo;
			if (NULL == pInfo)
				return;
		}
		break;
	case EVENT_IVS_WANDERDETECTION:
		{
			CFG_WANDER_INFO* pInfo = (CFG_WANDER_INFO*)m_stuInfo;
			if (NULL == pInfo)
				return;
		}
		break;
	default:
		break;
	}
	
	m_clObjType.DeleteAllItems();
	if (m_clObjType.GetHeaderCtrl())
	{
		int nColumCount = m_clObjType.GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumCount; i++)
		{
			m_clObjType.DeleteColumn(0);
		}
	}
	
	m_clObjType.SetExtendedStyle(m_clObjType.GetExtendedStyle() | 
		LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_clObjType.InsertColumn(0, ConvertString("ObjectType"), LVCFMT_LEFT, 80, -1); 
	for(int i = 0; i < m_pParentWnd->m_nSupportedObjTypeNum; i++)
	{
		m_clObjType.InsertItem(LVIF_TEXT|LVIF_STATE,i,ConvertString(m_pParentWnd->m_gObjectTypeName[i]),0,LVIS_SELECTED,0,0);
		
		for(int k = 0; k < nObjectTypeNum; k++)
		{
			if(strcmp(szObjectTypes[k], m_pParentWnd->m_gObjectTypeName[i]) == 0)
			{
				m_clObjType.SetCheck(i, TRUE);
				break;
			}
		}
	}
	return;
} 
*/
