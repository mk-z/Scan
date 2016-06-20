#include "StdAfx.h"
#include "SdkCallback.h"

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	printf("DisConnectFunc: ip: %s,dvr:%d  !\n",pchDVRIP,nDVRPort);
	
	if(dwUser == 0)
	{
		return;
	}
}
void CALLBACK HaveReconnFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	printf("HaveReconnFunc Reconnecting !\n");
	return;
}

BOOL InitNetSDK()
{
	BOOL bSuccess = CLIENT_Init(DisConnectFunc, (DWORD)0);
	if (bSuccess)
	{
		//设置断线重连
		CLIENT_SetAutoReconnect(HaveReconnFunc, (DWORD)0);
	}
	else
	{
		printf("InitNetSDK err !\n");
	}
	
	return bSuccess;
}