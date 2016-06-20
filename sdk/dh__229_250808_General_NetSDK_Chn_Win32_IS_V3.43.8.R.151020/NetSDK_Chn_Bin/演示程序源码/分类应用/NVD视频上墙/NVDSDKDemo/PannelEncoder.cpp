// PannelEncoder.cpp : implementation file
//

#include "stdafx.h"
#include "NVDSDKDemo.h"
#include "PannelEncoder.h"
#include "NVDSDKDemoDlg.h"
#include "AddDeviceDlg.h"
#include "DevByFileDlg.h"
#include "DevByTimeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPannelEncoder dialog


CPannelEncoder::CPannelEncoder(CWnd* pParent /*=NULL*/)
	: CDialog(CPannelEncoder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPannelEncoder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPannelEncoder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPannelEncoder)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPannelEncoder, CDialog)
	//{{AFX_MSG_MAP(CPannelEncoder)
	ON_BN_CLICKED(IDC_BTN_ADD_ENCODER, OnBtnAddEncoder)
	ON_BN_CLICKED(IDC_BTN_DEL_ENCODER, OnBtnDelEncoder)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK_FILE, OnBtnPlaybackFile)
	ON_BN_CLICKED(IDC_BTN_PLAYBACK_TIME, OnBtnPlaybackTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPannelEncoder message handlers

void CPannelEncoder::OnBtnAddEncoder() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();

	CAddDeviceDlg dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		DEVICE_INFO *pDeviceInfo = new DEVICE_INFO();
		if (pDeviceInfo != NULL)
		{
			pDeviceInfo->strDevName = dlg.m_strDevName;
			pDeviceInfo->strDevUser = dlg.m_strDevUser;
			pDeviceInfo->strDevPwd = dlg.m_strDevPwd;
			pDeviceInfo->strDevIp = dlg.m_strDevIp;
			pDeviceInfo->nDevPort = dlg.m_nDevPort;
			pDeviceInfo->lLoginID = dlg.m_lLoginHandle;
			pDeviceInfo->nDevChannel = dlg.m_nMonitorNum;
			pDeviceInfo->nStreamType = dlg.m_dwStreamType;
			pDeviceInfo->bIsOnline = TRUE;

			CReadWriteMutexLock lock(pParentDlg->m_csDevice);
			pParentDlg->m_lstDevices.push_back(pDeviceInfo);
			lock.Unlock();

			pParentDlg->UpdateDeviceList();
		}
	}
}

	
void CPannelEncoder::OnBtnDelEncoder() 
{
    CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
    if (pParentDlg == NULL)
    {
        return;
    }
    
    DEVICE_INFO* pSelectDevice = pParentDlg->GetSelectEncoderDeviceInfo(); 
    if (pSelectDevice != NULL)
    {
        CReadWriteMutexLock lock(pParentDlg->m_csDevice);
        
        list<DEVICE_INFO*>::iterator it = pParentDlg->m_lstDevices.begin();
        while (it != pParentDlg->m_lstDevices.end())
        {
            DEVICE_INFO *pDeviceInfo = (DEVICE_INFO *)(*it);
            if (pDeviceInfo != NULL)
            {
                if (pDeviceInfo->lLoginID == pSelectDevice->lLoginID)
                {
                    CLIENT_Logout(pSelectDevice->lLoginID);
                    delete pDeviceInfo;
                    pParentDlg->m_lstDevices.erase(it);
                    pParentDlg->m_bUpdataTree1 = TRUE;
                    break;
                }
            }
            
            ++it;
        }
    }
}

void CPannelEncoder::OnBtnPlaybackFile() 
{    
    CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
    if (pParentDlg == NULL)
    {
        return;
    }
    
    DEVICE_INFO* pSelectDevice = pParentDlg->GetSelectEncoderDeviceInfo(); 
    if (pSelectDevice != NULL)
    {
        HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
        if (selectNode != NULL)
        {
            HTREEITEM parentNode = selectNode;
            DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
            if (nData <= 32 && nData >= 0)
            {
                parentNode = pParentDlg->m_decoderTree.GetParentItem(selectNode);		
            }
            
            DECODER_INFO *pDecoderInfo = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
            if (pDecoderInfo != NULL)
            {
                CDevByFileDlg dlg;
                dlg.m_lLoginHandle = pSelectDevice->lLoginID;
                dlg.m_nChannelNum = pSelectDevice->nDevChannel;
                dlg.m_stuPlaybackParam.wDevPort = pSelectDevice->nDevPort;
                dlg.m_stuPlaybackParam.byEncoderID = pParentDlg->m_screenPannel.m_nCurMonitorID*4+pParentDlg->m_screenPannel.m_nCurWndID;
                dlg.m_stuPlaybackParam.bDevChnEnable = 1;
                strcpy(dlg.m_stuPlaybackParam.szDevIp, pSelectDevice->strDevIp);
                strcpy(dlg.m_stuPlaybackParam.szDevUser, pSelectDevice->strDevUser);
                strcpy(dlg.m_stuPlaybackParam.szDevPwd, pSelectDevice->strDevPwd);
                int nResponse = dlg.DoModal();
                if (nResponse == IDOK)
                {
                    SWITCH_TV_PARAM *pPlaybackTvParam = new SWITCH_TV_PARAM;
                    pPlaybackTvParam->nMonitorID = pParentDlg->m_screenPannel.m_nCurMonitorID;
                    pPlaybackTvParam->nWndID = pParentDlg->m_screenPannel.m_nCurWndID;
                    pPlaybackTvParam->lDecLoginID = pDecoderInfo->lLoginID;
                    pPlaybackTvParam->nEncoderNum = dlg.m_stuPlaybackParam.byEncoderID;
                    pPlaybackTvParam->nPlayType = 1;
                    
                    LLONG lHandle = CLIENT_DecTVPlayback(pDecoderInfo->lLoginID, dlg.m_stuPlaybackParam.byEncoderID, 
                        Dec_By_Device_File, (LPVOID)&dlg.m_stuPlaybackParam, sizeof(DEC_PLAYBACK_FILE_PARAM), pPlaybackTvParam);
                    if (lHandle == 0)
                    {
                        delete pPlaybackTvParam;
                        MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
                    }
                    else
                    {
                        pParentDlg->m_screenPannel.SetWndFlash(pPlaybackTvParam->nMonitorID, pPlaybackTvParam->nWndID, TRUE);
                        pParentDlg->m_dlgProcess.SetDlgItemText(IDC_BTN_PLAY, ConvertString("PAUSE"));
                        pParentDlg->m_dlgProcess.ShowWindow(SW_SHOW);
                    }
                }
            }
        }
    }
}

void CPannelEncoder::OnBtnPlaybackTime() 
{
	// TODO: Add your control notification handler code here
	CNVDSDKDemoDlg *pParentDlg = (CNVDSDKDemoDlg*)this->GetParent();
    if (pParentDlg == NULL)
    {
        return;
    }
    
    DEVICE_INFO* pSelectDevice = pParentDlg->GetSelectEncoderDeviceInfo(); 
    if (pSelectDevice != NULL)
    {
        HTREEITEM selectNode = pParentDlg->m_decoderTree.GetSelectedItem();
        if (selectNode != NULL)
        {
            HTREEITEM parentNode = selectNode;
            DWORD nData = pParentDlg->m_decoderTree.GetItemData(selectNode);
            if (nData <= 32 && nData >= 0)
            {
                parentNode = pParentDlg->m_encoderTree.GetParentItem(selectNode);
            }
            
            DECODER_INFO *pDecoderInfo = (DECODER_INFO *)pParentDlg->m_decoderTree.GetItemData(parentNode);
            if (pDecoderInfo != NULL)
            {
                CDevByTimeDlg dlg;
                dlg.m_lLoginHandle = pSelectDevice->lLoginID;
                dlg.m_nChannelNum = pSelectDevice->nDevChannel;
                dlg.m_stuPlaybackParam.wDevPort = pSelectDevice->nDevPort;
                dlg.m_stuPlaybackParam.byEncoderID = pParentDlg->m_screenPannel.m_nCurMonitorID*4+pParentDlg->m_screenPannel.m_nCurWndID;
                dlg.m_stuPlaybackParam.bDevChnEnable = 1;
                strcpy(dlg.m_stuPlaybackParam.szDevIp, pSelectDevice->strDevIp);
                strcpy(dlg.m_stuPlaybackParam.szDevUser, pSelectDevice->strDevUser);
                strcpy(dlg.m_stuPlaybackParam.szDevPwd, pSelectDevice->strDevPwd);
                int nResponse = dlg.DoModal();
                if (nResponse == IDOK)
                {
                    SWITCH_TV_PARAM *pPlaybackTvParam = new SWITCH_TV_PARAM;
                    pPlaybackTvParam->nMonitorID = pParentDlg->m_screenPannel.m_nCurMonitorID;
                    pPlaybackTvParam->nWndID = pParentDlg->m_screenPannel.m_nCurWndID;
                    pPlaybackTvParam->lDecLoginID = pDecoderInfo->lLoginID;
                    pPlaybackTvParam->nEncoderNum = dlg.m_stuPlaybackParam.byEncoderID;
                    pPlaybackTvParam->nPlayType = 2;
                    
                    LLONG lHandle = CLIENT_DecTVPlayback(pDecoderInfo->lLoginID, dlg.m_stuPlaybackParam.byEncoderID, 
                        Dec_By_Device_Time, (LPVOID)&dlg.m_stuPlaybackParam, sizeof(DEC_PLAYBACK_TIME_PARAM), pPlaybackTvParam);
                    if (lHandle == 0)
                    {
                        delete pPlaybackTvParam;
                        MessageBox(ConvertString("Playback failed!"), ConvertString("Prompt"));
                    }
                    else
                    {
                        pParentDlg->m_screenPannel.SetWndFlash(pPlaybackTvParam->nMonitorID, pPlaybackTvParam->nWndID, TRUE);
                        pParentDlg->m_dlgProcess.ShowWindow(SW_SHOW);
                    }
                }
            }
        }
    }
}

BOOL CPannelEncoder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
