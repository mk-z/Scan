// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo4.h"
#include "ServerDlg.h"
#include "dhplay.h"
#include "hisamr.h"
#include "Alaw_encoder.h"
#include "AACEnc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog


CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginHandle = 0;
	m_hTalkHandle = 0;
	m_bOpenAudioRecord = FALSE;
	m_hisEncodeHandle = NULL;
	m_AACEncodeHandle = NULL;
}


void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_COMBO_TRANSMIT_TYPE, m_ctlTransmitType);
	DDX_Control(pDX, IDC_COMBO_SPEAKER, m_ctlSpeakerChl);
	DDX_Control(pDX, IDC_COMBO_ENCODETYPE, m_ctlEncodeType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
//{{AFX_MSG_MAP(CServerDlg)
ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
ON_BN_CLICKED(IDC_BTN_STARTTALK, OnBtnStarttalk)
ON_BN_CLICKED(IDC_BTN_STOPTALK, OnBtnStoptalk)
ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSMIT_TYPE, OnSelchangeComboTransmitType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

void CServerDlg::OnBtnLogin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString strIp = "";
	CString strUser = "";
	CString strPwd = "";
	int nPort = 0;
	int nError = 0;
	NET_DEVICEINFO deviceInfo = {0};
	
	GetDlgItemText(IDC_IPADDRESS_IP, strIp);
	GetDlgItemText(IDC_EDIT_USER, strUser);
	GetDlgItemText(IDC_EDIT_PWD, strPwd);
	nPort = GetDlgItemInt(IDC_EDIT_PORT);
	
	LONG lLoginHandle = CLIENT_Login((LPSTR)(LPCSTR)strIp, nPort, (LPSTR)(LPCSTR)strUser, (LPSTR)(LPCSTR)strPwd, &deviceInfo, &nError);
	if (lLoginHandle != 0)
	{
		m_lLoginHandle = lLoginHandle;
        m_lDevChnNum = deviceInfo.byChanNum;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_STARTTALK)->EnableWindow(TRUE);

		m_ctlEncodeType.ResetContent();
		//Search the audio talk encode format the device supported 
		int retlen = 0;
		BOOL bSuccess = CLIENT_QueryDevState(m_lLoginHandle, DH_DEVSTATE_TALK_ECTYPE, (char*)&m_lstTalkEncode, sizeof(DHDEV_TALKFORMAT_LIST), &retlen, DEMO_SDK_WAITTIME);
		if (bSuccess && retlen == sizeof(DHDEV_TALKFORMAT_LIST))
		{
			int nIndex = 0;
			CString str;
			for (int i = 0; i < m_lstTalkEncode.nSupportNum; i++)
			{
				switch(m_lstTalkEncode.type[i].encodeType)
				{
				case DH_TALK_DEFAULT:
				case DH_TALK_PCM:
					str =  ConvertString("PCM");
					break;
				case DH_TALK_G711a:
					str = ConvertString("G711a");
					break;
				case DH_TALK_AMR:
					str = ConvertString("AMR");
					break;
				case DH_TALK_G711u:
					str = ConvertString("G711u");
					break;
				case DH_TALK_G726:
					str = ConvertString("G726");
					break;
				case DH_TALK_AAC:
					str = ConvertString("AAC");
					break;
				default:
					str = ConvertString("Unknow");
					break;
				}
                if (0 != str.Compare("Unknow"))
                {
                    CString s;
                    s.Format("_%d%s_%d%s", m_lstTalkEncode.type[i].nAudioBit, ConvertString("Bit"), m_lstTalkEncode.type[i].dwSampleRate, ConvertString("SampleRate"));
                    str += s;
                }
				nIndex = m_ctlEncodeType.AddString(str);
				m_ctlEncodeType.SetItemData(nIndex, i);
			}
			
			if (m_ctlEncodeType.GetCount() > 0)
			{
				m_ctlEncodeType.SetCurSel(0);
			}
		}

		DWORD dwRetBytes = 0;
		DHDEV_SYSTEM_ATTR_CFG stuAttr = { sizeof(DHDEV_SYSTEM_ATTR_CFG) };
		if (!CLIENT_GetDevConfig(lLoginHandle, DH_DEV_DEVICECFG, -1, &stuAttr, stuAttr.dwSize, &dwRetBytes, DEMO_SDK_WAITTIME))
		{
			MessageBox(ConvertString("Get device info failed!"), ConvertString("Prompt"));
		}
        m_lTalkChnNum = stuAttr.byTalkOutChanNum;
        m_ctlSpeakerChl.EnableWindow(bSuccess);
        GetDlgItem(IDC_CHECK_SPEAK)->EnableWindow(bSuccess);
        
        m_ctlTransmitType.ResetContent();
        m_ctlTransmitType.EnableWindow(bSuccess);
        int nIndex = m_ctlTransmitType.AddString(ConvertString("Local(not transmit)"));
        m_ctlTransmitType.SetItemData(nIndex, FALSE);
        
        nIndex = m_ctlTransmitType.AddString(ConvertString("Remote(transmit)"));
        m_ctlTransmitType.SetItemData(nIndex, TRUE);
        m_ctlTransmitType.SetCurSel(0);
        OnSelchangeComboTransmitType();

	}
	else
	{
		m_lLoginHandle = 0;
		ShowLoginErrorReason(nError);
	}
}

void CServerDlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	if(m_bOpenAudioRecord)
	{
		BOOL bSuccess = PLAY_CloseAudioRecord();
		if(bSuccess)
		{
			m_bOpenAudioRecord = FALSE;
			PLAY_Stop(100);
			PLAY_Stop(99);
			PLAY_StopSoundShare(100);
			PLAY_StopSoundShare(99);
			PLAY_CloseStream(100);
			PLAY_CloseStream(99);
		}
		else
		{
			MessageBox(ConvertString("Stop record failed!"), ConvertString("Prompt"));
		}
	}
	
	if(0 != m_hTalkHandle)
	{
		CLIENT_StopTalkEx(m_hTalkHandle);
		m_hTalkHandle = 0;
	}
	
	BOOL bRet = CLIENT_Logout(m_lLoginHandle);
	if(bRet)
	{
		m_lLoginHandle = 0;
        m_lDevChnNum = 0;
        m_lTalkChnNum = 0;
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_LOGOUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STARTTALK)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STOPTALK)->EnableWindow(FALSE);
		
		m_ctlEncodeType.ResetContent();
		m_ctlSpeakerChl.ResetContent();
        m_ctlTransmitType.ResetContent();
	}
	else
	{
		MessageBox(ConvertString("Logout failed!"), ConvertString("Prompt"));
	}
}

//Audio data of audio talk callback function 
void CALLBACK AfxAudioDataCallBack(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CServerDlg *dlg = (CServerDlg *)dwUser;
	dlg->AudioData(lTalkHandle, pDataBuf,dwBufSize,byAudioFlag);
}

//Audio data of the audio talk callback 
void CServerDlg::AudioData(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag)
{
	if(m_hTalkHandle == lTalkHandle)
	{
		if(1 == byAudioFlag)
		{
			//The audio data received from the device 
			
			int nPort = 99;
			//For PCM format withour header , please add 128.
			if (m_curTalkMode.encodeType == DH_TALK_DEFAULT)
			{
				nPort = 100;
				for (int i = 0; i < dwBufSize; i++)
				{
					pDataBuf[i] += 128;
				}
			}
			
			//You can use PLAY SDK to decode to get PCM and then encode to other formats if you to get a uniform formats.
			PLAY_InputData(nPort,(BYTE *)pDataBuf,dwBufSize);
			TRACE("收到音频数据长度：%d \n",dwBufSize);
		}
	}
}

void CServerDlg::OnBtnStarttalk() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_lLoginHandle)
	{
		//	First set audio talk audio encode format
		m_curTalkMode.encodeType = DH_TALK_DEFAULT;	// DH_TALK_DEFAULT is default way. Usually it is PCM without head.
		m_curTalkMode.dwSampleRate = 8000;
		m_curTalkMode.nAudioBit = 8;
		
		int nIndex = m_ctlEncodeType.GetCurSel();
		if (-1 != nIndex)
		{
			DWORD dwItemData = m_ctlEncodeType.GetItemData(nIndex);
			m_curTalkMode = m_lstTalkEncode.type[dwItemData];
		}

		if (m_curTalkMode.encodeType == DH_TALK_AAC)
		{
			if (NULL == m_AACEncodeHandle) 
			{
				m_AACEncodeHandle = AAC_Enc_Open(m_curTalkMode.dwSampleRate, 2, 64000, 100*1024);
				if (NULL == m_AACEncodeHandle) 
				{
					return ;
				}
			}
		}
		
		BOOL bSuccess = CLIENT_SetDeviceMode(m_lLoginHandle, DH_TALK_ENCODE_TYPE, &m_curTalkMode);
		
		//	Set server way(There is no decode in external SDK)
		bSuccess = CLIENT_SetDeviceMode(m_lLoginHandle, DH_TALK_SERVER_MODE, NULL);
		
		// 设置喊话参数
		NET_SPEAK_PARAM stSpeak = {sizeof(NET_SPEAK_PARAM)};
		stSpeak.nMode = 0;
		stSpeak.nSpeakerChannel = 0;
		CButton* pButton = reinterpret_cast<CButton*>(GetDlgItem(IDC_CHECK_SPEAK));
		if (0 != pButton)
		{
			if (BST_CHECKED == pButton->GetCheck())
			{
				stSpeak.nMode = 1; // 喊话
			}
		}
        // 语音对讲通道
        nIndex = m_ctlSpeakerChl.GetCurSel();
        if (-1 != nIndex)
        {
            stSpeak.nSpeakerChannel = m_ctlSpeakerChl.GetItemData(nIndex);
		}
		bSuccess = CLIENT_SetDeviceMode(m_lLoginHandle, DH_TALK_SPEAK_PARAM, &stSpeak);
		if (!bSuccess)
		{
			MessageBox(ConvertString("Set speaker param failure!"), ConvertString("Prompt"));
		}
		
        // 设置转发模式
        NET_TALK_TRANSFER_PARAM stTransfer = {sizeof(NET_TALK_TRANSFER_PARAM)};
        nIndex = m_ctlTransmitType.GetCurSel();
        if (-1 != nIndex)
        {
            DWORD dwItemData = m_ctlTransmitType.GetItemData(nIndex);
            stTransfer.bTransfer = dwItemData;
        }
        bSuccess = CLIENT_SetDeviceMode(m_lLoginHandle, DH_TALK_TRANSFER_MODE, &stTransfer);
        if (!bSuccess)
        {
            MessageBox(ConvertString("Set transfer mode failure!"), ConvertString("Prompt"));
        }

		//	Then enable audio talk 
		LONG lTalkHandle = CLIENT_StartTalkEx(m_lLoginHandle, AfxAudioDataCallBack, (DWORD)this);
		if(0 != lTalkHandle)
		{
			m_hTalkHandle = lTalkHandle;
			GetDlgItem(IDC_BTN_STARTTALK)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_STOPTALK)->EnableWindow(TRUE);
			
			//	Then enable local record audio function (Does not call it when it is a one-direction audio talk)
			BOOL bSuccess = StartAudioRecord();
			if(bSuccess)
			{
				m_bOpenAudioRecord = TRUE;
			}
			else
			{
				CLIENT_StopTalkEx(m_hTalkHandle);
				m_hTalkHandle = 0;
				GetDlgItem(IDC_BTN_STARTTALK)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_STOPTALK)->EnableWindow(FALSE);
				MessageBox(ConvertString("Start local record failed!"), ConvertString("Prompt"));
			}
		}
		else
		{
			MessageBox(ConvertString("Open talk failed!"), ConvertString("Prompt"));
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

void CServerDlg::OnBtnStoptalk() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_lLoginHandle)
	{
		if(m_bOpenAudioRecord)
		{
			BOOL bSuccess = PLAY_CloseAudioRecord();
			if(bSuccess)
			{
				m_bOpenAudioRecord = FALSE;
				PLAY_Stop(100);
				PLAY_Stop(99);
				PLAY_StopSoundShare(100);
				PLAY_StopSoundShare(99);
				PLAY_CloseStream(100);
				PLAY_CloseStream(99);
			}
			else
			{
				MessageBox(ConvertString("Stop record failed!"), ConvertString("Prompt"));
			}
		}
		
		if(0 != m_hTalkHandle)
		{
			//Stop audio talk to the device.
			BOOL bSuccess = CLIENT_StopTalkEx(m_hTalkHandle);
			if(bSuccess)
			{
				m_hTalkHandle = 0;
				GetDlgItem(IDC_BTN_STARTTALK)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_STOPTALK)->EnableWindow(FALSE);
			}
			else
			{
				MessageBox(ConvertString("Stop talk failed!"), ConvertString("Prompt"));
			}
		}
		
		if (m_curTalkMode.encodeType == DH_TALK_AAC && m_AACEncodeHandle)
		{
			AAC_Enc_Close(m_AACEncodeHandle);
			m_AACEncodeHandle = NULL;
		}
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

void CALLBACK AudioCallFunction(LPBYTE pDataBuffer, DWORD DataLength, void* pUser)
{
	if(pUser == 0)
	{
		return;
	}
	CServerDlg *dlg = (CServerDlg *)pUser;
	dlg->AudioRecord(pDataBuffer, DataLength);
}

void CServerDlg::AudioRecord(LPBYTE pDataBuffer, DWORD DataLength)
{
	char* pCbData = NULL;
	pCbData = new char[102400];
	if (NULL == pCbData) 
	{
		return;
	}
	int  iCbLen = 0;
	
	if (m_curTalkMode.encodeType == DH_TALK_DEFAULT || m_curTalkMode.encodeType == DH_TALK_PCM)	
	{
		if (m_curTalkMode.nAudioBit == 8)
		{
			for( int j = 0 ; j < DataLength; j++)
			{
				*(pDataBuffer + j) += 128;
			}
		}
		
		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;
		
		pCbData[4]=m_curTalkMode.nAudioBit==8?0x07:0x0C;
		if( 8000 == m_curTalkMode.dwSampleRate )
		{
			pCbData[5]=0x02;//8k
		}
		else if(16000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x04;
		}
		else if(48000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x09;
		}
		
		*(DWORD*)(pCbData+6)=DataLength;
		memcpy(pCbData+8, pDataBuffer, DataLength);
		
		iCbLen = 8+DataLength;
	}
	else if (m_curTalkMode.encodeType == DH_TALK_G711a)
	{
		if (g711a_Encode((char*)pDataBuffer, pCbData+8, DataLength, &iCbLen) != 1)
		{
			goto end;
		}
		
		//Private bit stream format frame head 
		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;
		
		pCbData[4]=0x0E; //G711A
		
		if( 8000 == m_curTalkMode.dwSampleRate )
		{
			pCbData[5]=0x02;//8k
		}
		else if(16000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x04;
		}
		else if(48000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x09;
		}
		
		pCbData[6]=BYTE(iCbLen&0xff);
		pCbData[7]=BYTE(iCbLen>>8);
		
		iCbLen += 8;
	}
	else if (m_curTalkMode.encodeType == DH_TALK_AMR)
	{
		//AMR encode
		iCbLen = AMR_Encode_Frame(m_hisEncodeHandle,(HI_S16*)pDataBuffer,
			(HI_U8*)(pCbData+8),MR102,MIME);
		if (iCbLen <= 0)
		{
			goto end;
		}
		
		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;
		
		pCbData[4]=0x14; //AMR
		if( 8000 == m_curTalkMode.dwSampleRate )
		{
			pCbData[5]=0x02;//8k
		}
		else if(16000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x04;
		}
		else if(48000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x09;
		}
		
		pCbData[6]=BYTE(iCbLen&0xff);
		pCbData[7]=BYTE(iCbLen>>8);
		
		iCbLen += 8;
	}
	else if (m_curTalkMode.encodeType == DH_TALK_G711u)
	{
		if (g711u_Encode((char*)pDataBuffer, pCbData+8, DataLength, &iCbLen) != 1)
		{
			goto end;
		}
		
		//Private bit stream format frame head 
		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;
		
		pCbData[4]=0x0A; //G711u
		if( 8000 == m_curTalkMode.dwSampleRate )
		{
			pCbData[5]=0x02;//8k
		}
		else if(16000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x04;
		}
		else if(48000 == m_curTalkMode.dwSampleRate)
		{
			pCbData[5] = 0x09;
		}
		
		pCbData[6]=BYTE(iCbLen&0xff);
		pCbData[7]=BYTE(iCbLen>>8);
		
		iCbLen += 8;
	}
	else if (m_curTalkMode.encodeType == DH_TALK_AAC)
	{
		//先单通道转双通道	
		BYTE * outBuf = new BYTE[DataLength*2]; 
		if (outBuf == NULL)
		{
			delete[] pCbData;
			return;
		}
		
		int i = 0;
		for (i = (DataLength/2 - 1); i >= 0; i--) 
		{
			outBuf[4 * i]     = pDataBuffer[2 * i];
			outBuf[4 * i + 1] = pDataBuffer[2 * i + 1];
			outBuf[4 * i + 2] = pDataBuffer[2 * i];
			outBuf[4 * i + 3] = pDataBuffer[2 * i + 1];
		}
		
		//AAC encode
		if(m_AACEncodeHandle)
		{
			unsigned int nOutlen = 0;
			int nRet = AAC_Enc_Encode(m_AACEncodeHandle, outBuf, DataLength*2, (unsigned char *)(pCbData+8), &nOutlen);
			if (nOutlen > 0)
			{
				iCbLen = nOutlen;
				pCbData[0]=0x00;
				pCbData[1]=0x00;
				pCbData[2]=0x01;
				pCbData[3]=0xF0;
				
				pCbData[4]=0x1A; //AAC
				if( 8000 == m_curTalkMode.dwSampleRate )
				{
					pCbData[5]=0x02;//8k
				}
				else if(16000 == m_curTalkMode.dwSampleRate)
				{
					pCbData[5] = 0x04;
				}
				else if(48000 == m_curTalkMode.dwSampleRate)
				{
					pCbData[5] = 0x09;
                }
                else if (32000 == m_curTalkMode.dwSampleRate)
                {
                    pCbData[5] = 0x07;
				}
				
				pCbData[6]=BYTE(iCbLen&0xff);
				pCbData[7]=BYTE(iCbLen>>8);
				
				/*FILE * pf =fopen("d://aac.aac", "a+b");
				if (pf)
				{
				fwrite((unsigned char *)(pCbData+8), 1, nOutlen, pf);
				fclose(pf);
			}*/
				iCbLen += 8;
			}
		}
		
		if (outBuf)
		{
			delete []outBuf;
		}
	}
	else
	{
		goto end;
	}
	
	// Send the data from the PC to DVR
	CLIENT_TalkSendData(m_hTalkHandle, (char *)pCbData, iCbLen);
	
end:
	if (pCbData != NULL)
	{
		delete[] pCbData;
	}
}

BOOL CServerDlg::StartAudioRecord()
{
	//	First confirm decode port.DH_TALK_DEFAULT is 100 port number and then rest is 99 port number.
	int nPort = 99;
	if (m_curTalkMode.encodeType == DH_TALK_DEFAULT)
	{
		nPort = 100;
	}
	
	//	Then specify frame length 
	int nFrameLength = 1024;
	switch(m_curTalkMode.encodeType)
	{
	case DH_TALK_DEFAULT:
	case DH_TALK_PCM:
		nFrameLength = 1024;
		break;
	case DH_TALK_G711a:
		nFrameLength = 1280;
		break;
	case DH_TALK_AMR:
		nFrameLength = 320;
		break;
	case DH_TALK_G711u:
		nFrameLength = 320;
		break;
	case DH_TALK_G726:
		nFrameLength = 320;
		break;
	case DH_TALK_AAC:
		nFrameLength = 1024;
	default:
		break;
	}

	if (m_curTalkMode.dwSampleRate == 48000)//如果采样率48K，更新音频长度
	{
		nFrameLength = 48*40*2; // 采样率*40*2
	}

	BOOL bRet = FALSE;
	
	//	Then call PLAYSDK library to begin recording audio 
	bool bOpenRet = PLAY_OpenStream(nPort,0,0,1024*900);
	if(bOpenRet)
	{
		BOOL bPlayRet = PLAY_Play(nPort,0);
		if(bPlayRet)
		{
			PLAY_PlaySoundShare(nPort);
			BOOL bSuccess = PLAY_OpenAudioRecord(AudioCallFunction,m_curTalkMode.nAudioBit,m_curTalkMode.dwSampleRate,nFrameLength,0,this);
			if(bSuccess)
			{
				bRet = TRUE;
			}
			else
			{
				PLAY_StopSoundShare(nPort);
				PLAY_Stop(nPort);
				PLAY_CloseStream(nPort);
			}
		}
		else
		{
			PLAY_CloseStream(nPort);
		}
	}
	
	return bRet;
}

void CServerDlg::ShowLoginErrorReason(int nError)
{
	if(1 == nError)		MessageBox(ConvertString("incorrect password!"), ConvertString("Prompt"));
	else if(2 == nError)	MessageBox(ConvertString("no this account! "), ConvertString("Prompt"));
	else if(3 == nError)	MessageBox(ConvertString("time out!"), ConvertString("Prompt"));
	else if(4 == nError)	MessageBox(ConvertString("account have been logined!"), ConvertString("Prompt"));
	else if(5 == nError)	MessageBox(ConvertString("account have been locked!"), ConvertString("Prompt"));
	else if(6 == nError)	MessageBox(ConvertString("The user has listed into illegal!"), ConvertString("Prompt"));
	else if(7 == nError)	MessageBox(ConvertString("The system is busy!"), ConvertString("Prompt"));
	else if(9 == nError)	MessageBox(ConvertString("You Can't find the network server!"), ConvertString("Prompt"));
	else	MessageBox(ConvertString("Login falied!"), ConvertString("Prompt"));
}

void CServerDlg::ShowTalkErrorReason(int nError)
{
	if(NET_ERROR_TALK_REJECT == nError)		MessageBox(ConvertString("Talk reject!"), ConvertString("Prompt"));
	else if(NET_ERROR_TALK_RESOURCE_CONFLICIT == nError)	MessageBox(ConvertString("Talk resource conflict!"), ConvertString("Prompt"));
	else if(NET_ERROR_TALK_UNSUPPORTED_ENCODE == nError)	MessageBox(ConvertString("Talk unsupported Encode!"), ConvertString("Prompt"));
	else if(NET_ERROR_TALK_RIGHTLESS == nError)	MessageBox(ConvertString("Talk rightless!"), ConvertString("Prompt"));
	else	MessageBox(ConvertString("Talk failed!"), ConvertString("Prompt"));
}

BOOL CALLBACK MessCallBackFuncServer(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    if (NULL == pBuf)
    {
        return FALSE;
    }
    CString str;
    switch(lCommand)
    {
        // 处理异步接口返回结果
    case DH_TALK_FAILD_EVENT:
        {
            DEV_TALK_RESULT *pSetRet =(DEV_TALK_RESULT *)pBuf;
			CServerDlg* pClientDlg = (CServerDlg*)dwUser;
			if (NULL != pClientDlg)
			{
				PostMessage(pClientDlg->GetSafeHwnd(), WM_COMMAND, IDC_BTN_STOPTALK, 0);
				pClientDlg->ShowTalkErrorReason(pSetRet->dwResultCode);
			}
        }
        break;
    default:
        break;
    }
    return TRUE;
}

BOOL CServerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_IPADDRESS_IP, "172.12.2.159");
	SetDlgItemText(IDC_EDIT_PORT, "37777");
	SetDlgItemText(IDC_EDIT_USER, "admin");
	SetDlgItemText(IDC_EDIT_PWD, "admin");
	UpdateData(FALSE);
	CLIENT_SetDVRMessCallBack(MessCallBackFuncServer, (DWORD)this);
	if (HI_SUCCESS != AMR_Encode_Init(&m_hisEncodeHandle, 0)) 
	{
		m_hisEncodeHandle = 0;
	}
	
	AAC_Enc_Init();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CServerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_hisEncodeHandle != NULL) 
	{
		AMR_Encode_Exit(&m_hisEncodeHandle);
	}
	
	AAC_Enc_DeInit();
	
	if(m_bOpenAudioRecord)
	{
		PLAY_CloseAudioRecord();
		PLAY_Stop(100);
		PLAY_Stop(99);
		PLAY_StopSoundShare(100);
		PLAY_StopSoundShare(99);
		PLAY_CloseStream(100);
		PLAY_CloseStream(99);
	}
	
	if(0 != m_hTalkHandle)
	{
		CLIENT_StopTalkEx(m_hTalkHandle);
	}
	
	if (m_lLoginHandle != 0)
	{
		CLIENT_Logout(m_lLoginHandle);
	}
}

void CServerDlg::OnSelchangeComboTransmitType() 
{
	// TODO: Add your control notification handler code here
    int nIndex = m_ctlTransmitType.GetCurSel();
    if (-1 != nIndex)
    {
        LONG lChnNum = 0;
        DWORD dwItemData = m_ctlTransmitType.GetItemData(nIndex);
        if (FALSE == dwItemData)
        {
            lChnNum = m_lTalkChnNum;
        }
        else if (TRUE == dwItemData)
        {
            lChnNum = m_lDevChnNum;
        }

        m_ctlSpeakerChl.ResetContent();
        
        for(int i=0; i< lChnNum; i++)
        {
            char szTmp[MAX_PATH] = {0};
            sprintf(szTmp,"speaker_%d", i);
            int nIndex = m_ctlSpeakerChl.AddString(szTmp);
            m_ctlSpeakerChl.SetItemData(nIndex, i);
            m_ctlSpeakerChl.SetCurSel(0);
        }
	}
}
