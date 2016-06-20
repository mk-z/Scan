// P2PClientTest.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#ifdef WIN32
#include <windows.h>
#define sleep(s) Sleep(s * 1000) 
#else
#include <unistd.h>
#endif


/***************************************************
NAME:          checkClientOnline
FUNCTION:      check the status of proxy client until status is DHProxyStateOnline
PARAMETER:
               handler[IN]:  the handle of proxy client
RETURN VALUE:  0-succeed,-1-failed
****************************************************/
int checkClientOnline(ProxyClientHandler handler)
{
	int nRet = -1;
	int i = 5;// try 5 times
    int state = 0;
    do
    {
        ///<get the status of proxy client
        if (DHProxyClientState(handler, &state) < 0)
        {
            printf("[Demo] proxy client check state failed!\n");
        }

        if (state == DHProxyStateOnline)
        {
            printf("[Demo] proxy client check state:On line!\n");
			nRet = 0;
            break;
        }
		i--;
        sleep(1);
    } while (i >= 0);
	return nRet;
}


/***************************************************
NAME:          checkDeviceOnline
FUNCTION:      check the status of device until status is DHProxyStateOnline
PARAMETER:
               handler[IN]:  the handle of proxy client
               uuid   [IN]:  the ID of device, in general is sequence number of device.
RETURN VALUE:  0-succeed,-1-failed
****************************************************/
int checkDeviceOnline(ProxyClientHandler handler, char *uuid)
{
	int nRet = -1;
	int i = 5;// try 5 times
    int state = 0;
    do
    {
        if (DHProxyClientServerState(handler, uuid, &state) < 0)
        {
            printf("[Demo] proxy client check server state failed!\n");
        }

        if (state == DHProxyStateOnline)
        {
            printf("[Demo] proxy client check state: OnLine!\n");
			nRet = 0;
            break;
        }
		i--;
        sleep(1);
    } while (i >= 0);
	return nRet;
}


/***************************************************
NAME:         checkPortState
FUNCTION:     check the channel status of proxy client
PARAMETER:
              handler[IN]:  the handle of proxy client
              port   [IN]:  the local port of mapping remote device.
RETURN VALUE:
              >= 0 : success, and need to wait continue
              -1: failed, and need to connect again

****************************************************/
int checkPortState(ProxyClientHandler handler, int port)
{
    int state = 0;
    DHProxyClientMapPortRate rate;

    if (DHProxyClientChannelstate(handler, port, &state) < 0)
    {
        printf("[Demo] proxy client get state failed!\n");
        return -1;
    }

    if (state == DHP2PChannelStateNonExist)
    {
        printf("[Demo] proxy client state: NonExist!\n");
        return -1;
    }

    if (state == DHP2PChannelStateInit)
    {
        printf("[Demo] proxy client state: Initing!\n");
        return 0;
    }

    printf("[Demo] proxy client create channel ok!\n");

    if (DHProxyClientQueryRate(handler, port, &rate) < 0)
    {
        printf("[Demo] proxy client query rate failed!\n");
        return -1;
    }


    ///>Next is the proccessing logic of application layer. At this time, the local port is listening, and you just need to connect (127.0.0.1, port) and establish a TCP connection,
    ///>then, you can access the remote device.
    ///>If the application want to quit, just set the value of variable is_need_stop to 1.

    ///> TO DO


    printf("[Demo] current recv rate:%.3f\n", rate.curRecvRate);
    return state;
}

/***************************************************
NAME:         checkRemoteInfo
FUNCTION:     check the Remote Device NAT Address
PARAMETER:
              handler[IN]:  the handle of proxy client
              port   [IN]:  the local port of mapping remote device.
RETURN VALUE:
              0 : success, and need to wait continue
              -1: failed, and need to connect again

****************************************************/
int checkRemoteNATInfo(ProxyClientHandler handler, int port)
{
   DHProxyClientRemotePortInfo info;
   if(DHProxyClientQueryRemoetInfo(handler, port, &info) < 0)
   {
       printf("[Demo] proxy client query stat info failed!\n");
       return -1;
   }

   printf("[Demo] localPort:%d, remoteID: %s, remoteAddress:%s:%d\n",
           port, info.remoteId, info.remoteIp, info.remotePort);

   return 0;
}

// 断线回调
void __stdcall DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
	if(dwUser == 0)
	{
		return;
	}
}
// 实时监视数据回调函数原形
void __stdcall RealDataCallBack(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser)
{
	printf("Recive real data,lRealHandle:%d, dwBufSize:%d\n", lRealHandle, dwBufSize);
}

int _tmain(int argc, char*argv[])
{
	/************************************************************************/
	/*Init P2P Client By P2P serverIP,Port and secret                       */
	/************************************************************************/
    char serverIp[128] = {0};
    int serverPort = 0;
    char serverSecret[128] = {0};
    char deviceId[128] = {0};
    int devicePort = 0;
	ProxyClientHandler client;
	int local_port = 0; ///>the mapping port of remote device.

	printf("Please input the P2P server ip or domain name.\r\n");
	scanf("%s", serverIp);
    printf("Please input the P2P server port.\r\n");
    scanf("%d", &serverPort);
    printf("Please input the P2P server secret.\r\n");
    scanf("%s", serverSecret);

    ///>DHProxyClientInit(P2P server ip, P2P server port, P2P server authentication secret)
    client = DHProxyClientInit(serverIp, serverPort, serverSecret);

	/************************************************************************/
	/*Check the status of proxy client until status is DHProxyStateOnline   */
	/************************************************************************/
    if (0 > checkClientOnline(client))
    {
		printf("P2P Client is not Online.\r\n");
		scanf("%d", &devicePort);
		DHProxyClientRelease(client);
		return 0;
    }

	/************************************************************************/
	/*Check the status of device until status is DHProxyStateOnline         */
	/************************************************************************/
	printf("Please input the device ID which you want to access.\r\n");
	scanf("%s", deviceId);

    ///>Then check the status of remote device
	if (0 > checkDeviceOnline(client, deviceId))
	{
		printf("Device is not Online.\r\n");
		scanf("%d", &devicePort);
		DHProxyClientRelease(client);
		return 0;
	}
	/************************************************************************/
	/*Create a connecting channel and process                               */
	/************************************************************************/
	printf("Please input the device port which you want to connect.\r\n");
	scanf("%d", &devicePort);	// Dahua Device TCP Port
	bool bAddPortSucceed = false;
	int nTimes = 3;
    do {
        ///>create P2P connecting channel
        DHProxyClientAddPort(client, deviceId, devicePort, &local_port);
		int nCheckPortTimes = 3;
        do
        {
            ///>check the status of P2P channel
            int ret = checkPortState(client, local_port);
            if (ret < 0)
            {
                break;
            }
            else if(ret == DHP2PChannelStateActive)
            {
                ///> check remote device NAT Address
                checkRemoteNATInfo(client, local_port);
				bAddPortSucceed = true;
				break;
            }
			nCheckPortTimes--;
            sleep(3);
        } while (0<=nCheckPortTimes);
		nTimes--;
        sleep(1);
    }while(!bAddPortSucceed && 0<=nTimes);	// if failed,try again

	if (!bAddPortSucceed)
	{
		printf("AddPort Failed.\r\n");
		scanf("%d", &devicePort);
		DHProxyClientRelease(client);
		return 0;
	}
	/************************************************************************/
	/*Init NetSDK、login device                                       */
	/************************************************************************/
	unsigned long ulUser = 0;
	int nInitRet = CLIENT_Init(DisConnectFunc,ulUser);
	printf("=====CLIENT_Init: %d\n",nInitRet);
	LLONG lRet = 0;
	NET_DEVICEINFO stDevInfo = {0};
	int nError = 0;
	char szDevIp[32] = {"127.0.0.1"};	
	int nPort = local_port;	// P2P: 127.0.0.1,Localport as a device
	int nSpecCap = 19;		// nSpecCap = 19为web私网穿透登陆方式
	char szName[16] = {"admin"};
	char szPWD[16] = {"admin"};	// Device username,password
	lRet = CLIENT_LoginEx(szDevIp, nPort, szName, szPWD, nSpecCap, NULL, &stDevInfo, &nError);
	std::cout << "CLIENT_LoginEx return code: "<< lRet << " nError: "<< nError << std::endl;
	if (NULL == lRet)
	{
		printf("=====Login failed!\n");
	}
	/************************************************************************/
	/*Use as normal device,eg:Real play								*/
	/************************************************************************/
	else
	{
		int nChannelID = 0; // 视频输入通道从0开始 
		LLONG lRealHandle = CLIENT_RealPlayEx(lRet,0,NULL,DH_RType_Realplay);
		if (NULL == lRealHandle)
		{
			printf("=====CLIENT_RealPlayEx failed! ErrorCode:0x%x\n", CLIENT_GetLastError());
		}
		else
		{
			CLIENT_SetRealDataCallBack(lRealHandle, RealDataCallBack, NULL);
			sleep(3);
			CLIENT_StopRealPlayEx(lRealHandle);
		}
	}
	printf("Please input any key to continue...\n");
	scanf("%d", &devicePort);
	/************************************************************************/
	/* Logout Device、clean up SDK                                    */
	/************************************************************************/
	BOOL bLogout = CLIENT_Logout(lRet);
	std::cout << "CLIENT_Logout return code: "<< bLogout << std::endl;
	CLIENT_Cleanup();

	/************************************************************************/
	/*Delete the P2P channel and local port,release resource before exit P2P*/
	/************************************************************************/
    DHProxyClientDelPort(client, local_port);
    DHProxyClientRelease(client);
    return 0;
}


