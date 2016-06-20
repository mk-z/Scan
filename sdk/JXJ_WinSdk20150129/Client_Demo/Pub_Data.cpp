#include "stdafx.h"
#include "Pub_Data.h"



CPub_Data::CPub_Data(void)
{
	g_iCountDevice = 0;
	g_iIsPlayNum = 0;
	g_strUser = _T("");
	g_strPassword = _T("");
	g_iDevicePort = 0;
	for( int i = 0; i < GET_MAX_DEV_NUM; i++ )
	{
		g_iChancel[i] = -1;
		g_vLoginHandle[i] = NULL;
		g_vStreamHandle[i] = NULL;
		g_vTalkHandle[i] = NULL;
		g_iStreamType[i] = 0;
		g_iCountHide[i] = 0;
		g_iCountInterset[i] = 0;
		g_iCountHideAlarm[i] = 0;
		g_iCountMoveSense[i] = 0;
		g_bTalk[i] = FALSE;
		g_DeviceClose[i] = FALSE;
		g_hAddItem[i] = NULL;
		g_lRecodeStartTime[i] = -1;  //录像开始时间
		g_lRecodeEndTime[i] = -1;
		g_lFrameCount[i] = 0;   //帧数
		g_iServerFlag[i] = -1;
		m_nDrawCount[i] = 0;
		g_iCountPerson[i] = 0;
		g_iRecFileID[i]    = -1;
	}

	g_strLoginIp = _T("");
	g_iStaticScreenWidth = 0;       //静态窗口的宽
	g_iStaticScreenHeight = 0;		//静态窗口的高
	g_iCutScreenNum = 0;
	g_iMoveX = 0;
	g_iMoveY = 0;
	g_iStaticToScreenX = 0;
	g_iStaticToScreenY = 0;
	g_iMainWindowX = 0;
	g_iMainWindowY = 0;
	g_iMainWindowW = 0;
	g_iMainWindowH = 0;
	g_iAttributeIng = -1;
	g_iPlayBack = -1;
	g_iWarningCount = 0;
	g_iReplace = -1;
	g_iDeleteDevice = -1;
	g_iFullScreenId = -1;
	g_iShowTimeDlgFlag = 0;
	m_iVideoIndex = 0;
	g_setPos = 0;

	g_iLanguageFlag = 0;
	g_iCutScreenNum = -1; 
	g_iCutScreenWidth = -1;
	g_iDownIndex = -1;
	g_bDragDown = FALSE;
	g_iWarnIpIndex = 0;
	
	g_bAllFullScreen = FALSE;
	g_bOpenStreamInAttribute = FALSE;
	g_iIoWarningChannelNul = 0;
	g_iPlayWndFlag = -1;
	g_iDownLoadPos = 0;
	g_iChannelNo = 0;

	m_iJointActionChannel = 0;
	m_iJointRecTime = 0;
	m_iJointOut = 0;
	m_iJointOutTime = 0;
	m_iJointTakePicChannel = 0;
	m_iJoinTakePicLever = 0;
	m_iTakePicFtpUp = 0;
	m_iTakePicCount = 0;
	m_iJointVoice = 0;
	m_iJointVoiceTime = 0;
	m_iJointEmail = 0;
	g_iFormatProgress = -1;
	g_iControlDevRet = -1;
	g_bUpgDeviceClose = FALSE;

	g_bHideAlarmDrawBorder = FALSE;  //是否画框
	g_bMoveAlarmDrawBorder = FALSE;
	g_bHideDrawBorder = FALSE;
	g_bInterestDrawBorder = FALSE;
}


CPub_Data::~CPub_Data(void )
{

}

BOOL CPub_Data::FreeObj(void*  pObj)
{
	if(pObj)
	{
		delete pObj;
		pObj = NULL;
		return TRUE;
	}
	return FALSE;
}
