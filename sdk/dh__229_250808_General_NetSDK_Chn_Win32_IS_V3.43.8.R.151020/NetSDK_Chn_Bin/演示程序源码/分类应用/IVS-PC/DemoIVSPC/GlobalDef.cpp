#include "StdAfx.h"
#include "GlobalDef.h"





/*
 *	
 */
CString ConvertString(CString strText)
{
	char *val = new char[200];
	CString strIniPath, strRet;
	
	memset(val,0,200);
	GetPrivateProfileString("String", strText, "", val, 200, "./langchn.ini");
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//If there is no corresponding string in ini file then set it to be deafault value(English).
		strRet=strText;
	}
	delete[] val;
	return strRet;
}
/*
 *	
 */
//Set static text for dialogue box(English->current language)
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;
	
	//Set main window title 
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText = ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}
	
	//Set small window title
	CWnd * pChild = pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//The next small window 
			pChild = pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//Set current language text for small window. 
		pChild->GetWindowText(strCaption);
		strText = ConvertString(strCaption);
		pChild->SetWindowText(strText);
		
		//Next small window 
		pChild = pChild->GetWindow(GW_HWNDNEXT);
	}
}

int g_getStructSize(int nRuleType)
{
	int nSize = 0;

	switch(nRuleType)
	{
	case EVENT_IVS_CROSSREGIONDETECTION:
		nSize = sizeof(CFG_CROSSREGION_INFO);
		break;
	default:
		break;
	}
	return nSize;
}

CString g_ConvertRuleTypeToString(DWORD dwType)
{
	CString strName;

	switch(dwType)
	{
		//0Paste
	 case EVENT_IVS_PASTEDETECTION:	
		 strName = _T("Paste");
		 break;
		 //1
	 case EVENT_IVS_CROSSFENCEDETECTION:
		 strName = _T("CrossFence");
		 break;
		 //2
	 case EVENT_IVS_CROSSLINEDETECTION:
		 strName = _T("CrossLine");
		 break;
		 //3CrossRegion
	 case EVENT_IVS_CROSSREGIONDETECTION:
		 strName = _T("CrossRegin");
		 break;
		 //4Move
	 case EVENT_IVS_MOVEDETECTION:
		 strName = _T("Move");
		 break;
		 //5Left
	 case EVENT_IVS_LEFTDETECTION:
		 strName = _T("Left");
		 break;
		 //6Parking
	 case EVENT_IVS_PARKINGDETECTION:
		 strName = _T("Parking");
		 break;
		 //7Preservation
	 case EVENT_IVS_PRESERVATION:
		 strName = _T("Preservation");
		 break;
		 //8Retro
	 case EVENT_IVS_RETROGRADEDETECTION:
		 strName = _T("Retrograde");
		 break;
		 //9Stay
	 case EVENT_IVS_STAYDETECTION:
		 strName = _T("Stay");
		 break;
		 //10TakenAway
	 case EVENT_IVS_TAKENAWAYDETECTION:
		 strName = _T("TakenAway");
		 break;
		 //11VideoAbnormal
	 case EVENT_IVS_VIDEOABNORMALDETECTION:
		 strName = _T("VideoAbnormal");
		 break;
		 //12Wander
	 case EVENT_IVS_WANDERDETECTION:
		 strName = _T("Wander");
		 break;
	}

	return strName;
}


int g_ConvertRuleTypeToStructSize(DWORD dwType)
{
	int nLen = 0;
	
	switch(dwType)
	{
		//0Paste
	case EVENT_IVS_PASTEDETECTION:
		nLen = sizeof(CFG_PASTE_INFO);
		break;
		//1
	case EVENT_IVS_CROSSFENCEDETECTION:
		nLen = sizeof(CFG_CROSSFENCEDETECTION_INFO);
		break;
		//2
	case EVENT_IVS_CROSSLINEDETECTION:
		nLen = sizeof(CFG_CROSSLINE_INFO);
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		nLen = sizeof(CFG_CROSSREGION_INFO);
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		nLen = sizeof(CFG_MOVE_INFO);
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		nLen = sizeof(CFG_LEFT_INFO);
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		nLen = sizeof(CFG_PARKINGDETECTION_INFO);
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		nLen = sizeof(CFG_PRESERVATION_INFO);
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		nLen = sizeof(CFG_RETROGRADEDETECTION_INFO);
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		nLen = sizeof(CFG_STAY_INFO);
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		nLen = sizeof(CFG_TAKENAWAYDETECTION_INFO);
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		nLen = sizeof(CFG_VIDEOABNORMALDETECTION_INFO);
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		nLen = sizeof(CFG_WANDER_INFO);
		break;
	}
	
	return nLen;
}

int g_GetStructInfo(DWORD dwAlarmType)
{
	int nLen = 0;
	
	switch(dwAlarmType)
	{
		//0Paste
	case EVENT_IVS_PASTEDETECTION:
		nLen = sizeof(DEV_EVENT_PASTE_INFO);
		break;
		//1
	case EVENT_IVS_CROSSFENCEDETECTION:
		nLen = sizeof(DEV_EVENT_CROSSFENCEDETECTION_INFO);
		break;
		//2
	case EVENT_IVS_CROSSLINEDETECTION:
		nLen = sizeof(DEV_EVENT_CROSSLINE_INFO);
		break;
		//3CrossRegion
	case EVENT_IVS_CROSSREGIONDETECTION:
		nLen = sizeof(DEV_EVENT_CROSSREGION_INFO);
		break;
		//4Move
	case EVENT_IVS_MOVEDETECTION:
		nLen = sizeof(DEV_EVENT_MOVE_INFO);
		break;
		//5Left
	case EVENT_IVS_LEFTDETECTION:
		nLen = sizeof(DEV_EVENT_LEFT_INFO);
		break;
		//6Parking
	case EVENT_IVS_PARKINGDETECTION:
		nLen = sizeof(DEV_EVENT_PARKINGDETECTION_INFO);
		break;
		//7Preservation
	case EVENT_IVS_PRESERVATION:
		nLen = sizeof(DEV_EVENT_PRESERVATION_INFO);
		break;
		//8Retro
	case EVENT_IVS_RETROGRADEDETECTION:
		nLen = sizeof(DEV_EVENT_RETROGRADEDETECTION_INFO);
		break;
		//9Stay
	case EVENT_IVS_STAYDETECTION:
		nLen = sizeof(DEV_EVENT_STAY_INFO);
		break;
		//10TakenAway
	case EVENT_IVS_TAKENAWAYDETECTION:
		nLen = sizeof(DEV_EVENT_TAKENAWAYDETECTION_INFO);
		break;
		//11VideoAbnormal
	case EVENT_IVS_VIDEOABNORMALDETECTION:
		nLen = sizeof(DEV_EVENT_VIDEOABNORMALDETECTION_INFO);
		break;
		//12Wander
	case EVENT_IVS_WANDERDETECTION:
		nLen = sizeof(DEV_EVENT_WANDER_INFO);
		break;
	}

	return nLen;
}



void g_DrawArrow(CDC *pDC, POINT pointStart, ARROW_DIRECTION_TYPE eArrowDirection)
{
	POINT ArrowEnd1, ArrowEnd2;

	pDC->MoveTo(pointStart);

	switch (eArrowDirection)
	{
	case ARROW_UP:
		ArrowEnd1.x = pointStart.x - 5;
		ArrowEnd1.y = pointStart.y + 5;
		ArrowEnd2.x = pointStart.x + 5;
		ArrowEnd2.y = pointStart.y + 5;
		break;

	case ARROW_DOWN:
		ArrowEnd1.x = pointStart.x - 5;
		ArrowEnd1.y = pointStart.y - 5;
		ArrowEnd2.x = pointStart.x + 5;
		ArrowEnd2.y = pointStart.y - 5;
		break;

	case ARROW_LEFT:
		ArrowEnd1.x = pointStart.x + 5;
		ArrowEnd1.y = pointStart.y - 5;
		ArrowEnd2.x = pointStart.x + 5;
		ArrowEnd2.y = pointStart.y + 5;
		break;

	case ARROW_RIGHT:
		ArrowEnd1.x = pointStart.x - 5;
		ArrowEnd1.y = pointStart.y - 5;
		ArrowEnd2.x = pointStart.x - 5;
		ArrowEnd2.y = pointStart.y + 5;
		break;

	default:
		ArrowEnd1.x = pointStart.x;
		ArrowEnd1.y = pointStart.y;
		ArrowEnd2.x = pointStart.x;
		ArrowEnd2.y = pointStart.y;
		break;
	}

	pDC->LineTo(ArrowEnd1);
	pDC->MoveTo(pointStart);
	pDC->LineTo(ArrowEnd2);

}


void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, LONG lParam, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}

	//Stream port number according to the real-time handle.
	//Input the stream data getting from the card
	BOOL bInput = FALSE;
	if(0 != g_nPlayPort)
	{
		switch(dwDataType) {
		case 0:
			//Original data 
			bInput = g_PlayAPI.PLAY_InputData(g_nPlayPort, pBuffer, dwBufSize);
			break;
		case 1:
			//Standard video data 

			break;
		case 2:
			//yuv data 

			break;
		case 3:
			//pcm audio data 

			break;
		case 4:
			//Original audio data 

			break;
		default:
			break;
		}	
	}
}