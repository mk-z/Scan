#pragma once

// 网络库初始化
BOOL InitNetSDK();


// 网络库回调函数
void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

void CALLBACK HaveReconnFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

