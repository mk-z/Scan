// PannelDecoder.cpp : implementation file
//

#include "stdafx.h"
#include "NVDSDKDemo.h"
#include "PannelDecoder.h"
#include "NVDSDKDemoDlg.h"
#include "AddDecoderDlg.h"
#include "SearchTVDlg.h"
#include "AudioTalkDlg.h"
#include "DecTourDlg.h"
#include "VideoOutDlg.h"
#include "ShowChannelStateDlg.h"
#include "TVAdjustdlg.h"
#include "TourCfg.h"
#include "DecoderInfoDlg.h"
#include "DecodePolicyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPannelDecoder dialog


CPannelDecoder::CPannelDecoder(CWnd* pParent /*=NULL*/)
	: CDialog(CPannelDecoder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPannelDecoder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPannelDecoder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPannelDecoder)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPannelDecoder, CDialog)
	//{{AFX_MSG_MAP(CPannelDecoder)
	ON_BN_CLICKED(IDC_BTN_ADD_DECODER, OnBtnAddDecoder)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(IDC_BTN_AUDIOTALK, OnBtnAudiotalk)
	ON_BN_CLICKED(IDC_BTN_TOUR, OnBtnTour)
	ON_BN_CLICKED(IDC_BNT_VIDEOOUT, OnBntVideoout)
	ON_BN_CLICKED(IDC_BNT_CHANNEL_STATE, OnBntChannelState)
	ON_BN_CLICKED(IDC_BNT_TV_ADJUST, OnBntTvAdjust)
	ON_BN_CLICKED(IDC_BNT_TOUR_CFG, OnBntTourCfg)
	ON_BN_CLICKED(IDC_BUTTON_ENCODER_INFO, OnButtonEncoderInfo)
	ON_BN_CLICKED(IDC_BTN_DEL_DECODER, OnBtnDelDecoder)
	ON_BN_CLICKED(IDC_BUTTON_DECODEPOLICY, OnButtonDecodepolicy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPannelDecoder message handlers

void CPannelDecoder::OnBtnDelDecoder() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	
	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}

		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder != NULL)
		{
			CReadWriteMutexLock lock(pParentDlg->m_csDecoder);
			
			list<DECODER_INFO*>::iterator it = pParentDlg->m_lstDecoders.begin();
			while (it != pParentDlg->m_lstDecoders.end())
			{
				DECODER_INFO *pDecoderInfo = (DECODER_INFO *)(*it);
				if (pDecoderInfo != NULL)
				{
					if (pDecoderInfo->lLoginID == pSelectDecoder->lLoginID)
					{
						CLIENT_Logout(pSelectDecoder->lLoginID);
						delete pDecoderInfo;
						pParentDlg->m_lstDecoders.erase(it);
						pParentDlg->m_bUpdataTree2 = TRUE;
						break;
					}
				}
				
				++it;
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}

void CPannelDecoder::OnBtnAddDecoder() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();

	CAddDecoderDlg dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		CLIENT_SetOperateCallBack(dlg.m_lLoginHandle, MessDataCallBackFunc, (LDWORD)pParentDlg);
		CLIENT_SetDecPlaybackPos(dlg.m_lLoginHandle, DecPlayBackPosFunc, (LDWORD)pParentDlg);
		CLIENT_StartListenEx(dlg.m_lLoginHandle);

		DECODER_INFO *pDecoderInfo = new DECODER_INFO();
		if (pDecoderInfo != NULL)
		{
			pDecoderInfo->strDecName = dlg.m_strDecName;
			pDecoderInfo->strDecUser = dlg.m_strDecUser;
			pDecoderInfo->strDecPwd = dlg.m_strDecPwd;
			pDecoderInfo->strDecIp = dlg.m_strDecIp;
			pDecoderInfo->nDecPort = dlg.m_nDecPort;
			pDecoderInfo->lLoginID = dlg.m_lLoginHandle;
			pDecoderInfo->nDecChannel = dlg.m_nMonitorNum;
			pDecoderInfo->bIsOnline = TRUE;
			for (int i = 0; i < NVD_ENCODER_MAX; i++)
			{
				pDecoderInfo->dwTotalSize[i] = 0;
				pDecoderInfo->dwCurSize[i] = 0;
			}
				
			BOOL bRet = CLIENT_QueryDecoderInfo(dlg.m_lLoginHandle, &pDecoderInfo->devDecInfo);
			if (FALSE == bRet)
			{
				MessageBox(ConvertString("Query NVD failed!"), ConvertString("Prompt"));
 			}
			
			if (pDecoderInfo->devDecInfo.nMonitorNum != pDecoderInfo->nDecChannel)
			{
				// 
			}
					
			CReadWriteMutexLock lock(pParentDlg->m_csDecoder);
			pParentDlg->m_lstDecoders.push_back(pDecoderInfo);
			lock.Unlock();

			pParentDlg->UpdateDecoderList();
		}		
	}
}

void CPannelDecoder::OnBtnSearch() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();

	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}

		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder != NULL)
		{
			CSearchTVDlg dlg;
			dlg.SetDlgParam(pSelectDecoder->lLoginID, pSelectDecoder->nDecChannel);
			int nResponse = dlg.DoModal();
			if (IDOK == nResponse)
			{
				
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}

void CPannelDecoder::OnBtnAudiotalk() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();

	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_encoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pDecoderInfo = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pDecoderInfo != NULL)
		{
			CAudioTalkDlg dlg;
			int nResponse = dlg.DoModal();
			if (IDOK == nResponse)
			{
				
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}

void CPannelDecoder::OnBtnTour() 
{
 	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
 	
 	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
 	if (selectNode != NULL)
 	{
 		HTREEITEM parentNode = selectNode;
 		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
 		if (nData <= 16 && nData >= 0)
 		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
 		}
 		
 		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
 		if (pSelectDecoder != NULL)
		{
			CDecTourDlg dlg;
			dlg.SetDlgParam(pSelectDecoder->lLoginID, pSelectDecoder->nDecChannel);
			int nResponse = dlg.DoModal();
			if (IDOK == nResponse)
			{
				
			}
 		}
 	}
 	else
 	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}

void CPannelDecoder::OnBntVideoout() 
{
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	
	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder != NULL)
		{
			CVideoOutDlg dlg;
			dlg.SetDlgParam(pSelectDecoder->lLoginID);
			int nResponse = dlg.DoModal();
			if (IDOK == nResponse)
			{
				
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}

void CPannelDecoder::OnBntChannelState() 
{
	// TODO: Add your control notification handler code here

	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	
	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder->lLoginID != 0)
		{
			CShowChannelStateDlg dlg;
			//dlg.SetDlgParam( pSelectDecoder->nDecChannel);
			dlg.SetDlgParam( pSelectDecoder->devDecInfo.nEncoderNum);
			dlg.DoModal();
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}


BOOL CPannelDecoder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPannelDecoder::OnBntTvAdjust() 
{
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	
	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder != NULL)
		{
			CTVAdjustdlg dlg;
			dlg.SetDlgParam(pSelectDecoder->lLoginID, pSelectDecoder->nDecChannel);
			int nResponse = dlg.DoModal();
			if (IDOK == nResponse)
			{
				
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
	
}

void CPannelDecoder::OnBntTourCfg() 
{
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	
	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder != NULL)
		{
			int nRet = 0;
			DWORD dwRetLen = 0;
			DEV_ENCODER_CFG stuDecInfo = {0};
			int nTourNum = 0;
			
			nRet = CLIENT_GetDevConfig(pSelectDecoder->lLoginID, DH_DEV_ENCODER_CFG, -1, &stuDecInfo, sizeof(DEV_ENCODER_CFG), &dwRetLen, 2000);
			if (nRet && dwRetLen == sizeof(DEV_ENCODER_CFG))
			{
				nTourNum = stuDecInfo.bDecodeTour;
			}
				
			CTourCfg dlg;
			
			dlg.SetDlgParam(pSelectDecoder->lLoginID, nTourNum, pParentDlg->m_screenPannel.m_nCurMonitorID*4+pParentDlg->m_screenPannel.m_nCurWndID);
			int nResponse = dlg.DoModal();
			if (IDOK == nResponse)
			{
				
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
	
	
}

void CPannelDecoder::OnButtonEncoderInfo() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	
	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder != NULL)
		{
			CDecoderInfoDlg encoderInfoDlg;
			encoderInfoDlg.SetLoginHandle(pSelectDecoder->lLoginID);
			encoderInfoDlg.DoModal();
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}

void CPannelDecoder::OnButtonDecodepolicy() 
{
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
	
	HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
	if (selectNode != NULL)
	{
		HTREEITEM parentNode = selectNode;
		DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
		if (nData <= 16 && nData >= 0)
		{
			parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);
		}
		
		DECODER_INFO *pSelectDecoder = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
		if (pSelectDecoder != NULL)
		{
			DecodePolicyDlg dlg;
			dlg.SetDlgParam(pSelectDecoder->lLoginID);
			int nResponse = dlg.DoModal();
			if (IDOK == nResponse)
			{
				
			}
		}
	}
	else
	{
		MessageBox(ConvertString("Select NVD first!"), ConvertString("Prompt"));
	}
}
