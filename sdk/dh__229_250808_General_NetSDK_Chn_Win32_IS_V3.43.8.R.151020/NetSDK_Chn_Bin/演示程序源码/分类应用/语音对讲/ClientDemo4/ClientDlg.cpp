// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo4.h"
#include "ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog


CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginHandle = 0;
	m_hTalkHandle = 0;
	m_bRecordStatus = FALSE;
}


void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_COMBO_TRANSMIT_TYPE, m_ctlTransmitType);
	DDX_Control(pDX, IDC_COMBO_SPEAKER, m_ctlSpeakerChl);
	DDX_Control(pDX, IDC_COMBO_ENCODETYPE, m_ctlEncodeType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_BN_CLICKED(IDC_BTN_LOGOUT, OnBtnLogout)
	ON_BN_CLICKED(IDC_BTN_STARTTALK, OnBtnStarttalk)
	ON_BN_CLICKED(IDC_BTN_STOPTALK, OnBtnStoptalk)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_TRANSMIT_TYPE, OnSelchangeComboTransmitType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

void CClientDlg::OnBtnLogin() 
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
		//Search the audio talk encode formats then device supported 
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
					str = ConvertString("PCM");
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
				case  DH_TALK_MP3:
					str = ConvertString("MP3");
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

void CClientDlg::OnBtnLogout() 
{
	// TODO: Add your control notification handler code here
	if(m_bRecordStatus)
	{
		CLIENT_RecordStop();
		m_bRecordStatus = FALSE;
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
void CALLBACK AudioDataCallBack(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
	CClientDlg *dlg = (CClientDlg *)dwUser;
	dlg->AudioData(lTalkHandle, pDataBuf,dwBufSize,byAudioFlag);
}

//Audio data of the audio talk callback 
void CClientDlg::AudioData(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag)
{
	if(m_hTalkHandle == lTalkHandle)
	{
		if(0 == byAudioFlag)
		{
			//It means it is the audio data from the local reocrd library
			//TRACE("The audio data lenght to be sent：%d \n",dwBufSize);
			long lSendLen = CLIENT_TalkSendData(lTalkHandle, pDataBuf, dwBufSize);
			if(lSendLen != (long)dwBufSize)
			{
				//Error occurred when sending the user audio data to the device
				
			}
		}
		else if(1 == byAudioFlag)
		{
			//It means it has received the audio data from the device.
			CLIENT_AudioDec(pDataBuf, dwBufSize);
			//TRACE("The audio data lenght received：%d \n",dwBufSize);
#ifdef _DEBUG
			FILE *stream;
			if( (stream = fopen("E:\\Talk.txt", "a+b")) != NULL )
			{
				int numwritten = fwrite( pDataBuf, sizeof( char ), dwBufSize, stream );
				fclose( stream );
			}
#endif
		}
	}
}

void CClientDlg::OnBtnStarttalk() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_lLoginHandle)
	{
		//	First set audio encode format in audio talk 
		m_curTalkMode.encodeType = DH_TALK_DEFAULT;	// DH_TALK_DEFAULT is default way. Usually it is pcm type without head.
		m_curTalkMode.dwSampleRate = 8000;
		m_curTalkMode.nAudioBit = 8;

		int nIndex = m_ctlEncodeType.GetCurSel();
		if (-1 != nIndex)
		{
			DWORD dwItemData = m_ctlEncodeType.GetItemData(nIndex);
			m_curTalkMode = m_lstTalkEncode.type[dwItemData];
		}
		
	//	m_curTalkMode.dwSampleRate = 16000;
	//	m_curTalkMode.nAudioBit = 16;
		
		BOOL bSuccess = CLIENT_SetDeviceMode(m_lLoginHandle, DH_TALK_ENCODE_TYPE, &m_curTalkMode);

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
		LONG lTalkHandle = CLIENT_StartTalkEx(m_lLoginHandle, AudioDataCallBack, (DWORD)this);
		if(0 != lTalkHandle)
		{
			m_hTalkHandle = lTalkHandle;
			GetDlgItem(IDC_BTN_STARTTALK)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_STOPTALK)->EnableWindow(TRUE);
	
			//	Then enbale local record function.(Does not call it if it is a one-direction audio talk.)
			BOOL bSuccess = CLIENT_RecordStart();
			if(bSuccess)
			{
				m_bRecordStatus = TRUE;
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

void CClientDlg::OnBtnStoptalk() 
{
	// TODO: Add your control notification handler code here
	if(0 != m_lLoginHandle)
	{
		if(m_bRecordStatus)
		{
			//Stop local record 
			CLIENT_RecordStop();
			m_bRecordStatus = FALSE;
		}

		if(0 != m_hTalkHandle)
		{
			//Stop audio talk to the device 
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
	}
	else
	{
		MessageBox(ConvertString("Please login first!"), ConvertString("Prompt"));
	}
}

BOOL CALLBACK MessCallBackFunc(LONG lCommand, LLONG lLoginID, char *pBuf, DWORD dwBufLen, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
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
			CClientDlg* pClientDlg = (CClientDlg*)dwUser;
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

BOOL CClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here
    SetDlgItemText(IDC_IPADDRESS_IP, "172.8.2.52");
	SetDlgItemText(IDC_EDIT_PORT, "37777");
	SetDlgItemText(IDC_EDIT_USER, "admin");
	SetDlgItemText(IDC_EDIT_PWD, "admin");
	UpdateData(FALSE);
	CLIENT_SetDVRMessCallBack(MessCallBackFunc, (DWORD)this);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClientDlg::ShowLoginErrorReason(int nError)
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

void CClientDlg::ShowTalkErrorReason(int nError)
{
	if(NET_ERROR_TALK_REJECT == nError)		MessageBox(ConvertString("Talk reject!"), ConvertString("Prompt"));
	else if(NET_ERROR_TALK_RESOURCE_CONFLICIT == nError)	MessageBox(ConvertString("Talk resource conflict!"), ConvertString("Prompt"));
	else if(NET_ERROR_TALK_UNSUPPORTED_ENCODE == nError)	MessageBox(ConvertString("Talk unsupported Encode!"), ConvertString("Prompt"));
	else if(NET_ERROR_TALK_RIGHTLESS == nError)	MessageBox(ConvertString("Talk rightless!"), ConvertString("Prompt"));
	else	MessageBox(ConvertString("Talk failed!"), ConvertString("Prompt"));
}

void CClientDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_bRecordStatus)
	{
		CLIENT_RecordStop();
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

void CClientDlg::OnSelchangeComboTransmitType() 
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
