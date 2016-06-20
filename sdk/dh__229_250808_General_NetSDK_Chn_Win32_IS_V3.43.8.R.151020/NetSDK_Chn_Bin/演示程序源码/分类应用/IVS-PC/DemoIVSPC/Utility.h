
#pragma once
#include "../include/dhnetsdk.h"
#include <map>
#include <string>
#include <stdio.h>

inline std::string ConvertStr(char* szKeyName)
{
	using namespace std;
	static bool bFirstTime = true;
	static map<std::string, std::string> g_text;
	//第一次的时候把内容装载到map中
	if ( bFirstTime )
	{
		bFirstTime = false;
		const int MAX_ALL_KEY_SIZE = 1024*50;
		const int MAX_SINGLE_KEY_SIZE = 1024;
		const int MAX_SINGLE_VAL_SIZE = 1024;
		char szKeys[MAX_ALL_KEY_SIZE] = {0};
		DWORD dwRet = GetPrivateProfileString("String", NULL, NULL, szKeys, MAX_ALL_KEY_SIZE, "./langchn.ini");
		if (dwRet != 0)
		{
			char* szKey = szKeys;
			char szVal[MAX_SINGLE_VAL_SIZE]; 
			DWORD dwProcessCount = 0;
			while(true)
			{
				memset(szVal, 0, MAX_SINGLE_VAL_SIZE);
				GetPrivateProfileString("String", szKey, szKey, szVal, MAX_SINGLE_VAL_SIZE, "./langchn.ini");
				g_text.insert(pair<std::string, std::string>(szKey, szVal));

				szKey += (strlen(szKey) + 1);
				int nCount = szKey - szKeys;
				if (nCount >= (int)dwRet)
				{
					break;
				}
			}
		}
	}
	//从map中读取
	string strRet = g_text[szKeyName];
	if (strRet.size() != 0)
	{
		return strRet;
	}
	else
	{
		return string(szKeyName);
	}

	
}


/************************************************************************/
/* 获取模块所在的绝对路径                                               */
/************************************************************************/
inline bool GetModulePath(const char* szDllName, char* szModuleDir)
{
	HMODULE hModule = NULL;
	if (szDllName != NULL)
	{
		hModule = ::GetModuleHandle(szDllName);
		if (hModule == NULL)
		{
			return false;
		}
	}
	char szFullDllPath[_MAX_PATH] = {0};
	::GetModuleFileName(hModule, szFullDllPath, _MAX_PATH);
	char* lastBackslash = strrchr(szFullDllPath, '\\');
	int lastBackslashPos = lastBackslash - szFullDllPath + 1;
	strncpy(szModuleDir, szFullDllPath, lastBackslashPos);
	return true;
}

/************************************************************************/
/* 获取模块所在的绝对路径                                               */
/************************************************************************/
inline bool GetModulePath(const char* szDllName, std::string& strModuleDir)
{
	char buf[MAX_PATH] = {0};
	bool bRet = GetModulePath(szDllName, buf);
	if (bRet)
	{
		strModuleDir = std::string(buf);
		return true;
	}
	return false;
}

/************************************************************************/
/* GUID to std::string                                                  */
/************************************************************************/
inline std::string GuidToString(const GUID &guid)
{
    char buf[64] = {0};
	sprintf(
		buf, 
		"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return std::string(buf);
}

/************************************************************************/
/* NET_TIME to char                                                     */
/************************************************************************/
inline void NetTime2Str(NET_TIME& netTime, char* buf)
{
	sprintf(buf, "%d-%d-%d %d:%d:%d", 
				netTime.dwYear,
				netTime.dwMonth,
				netTime.dwDay,
				netTime.dwHour,
				netTime.dwMinute,
				netTime.dwSecond);
}

inline std::string D2Str(const double v)
{
	char szVal[20] = {0};
	sprintf(szVal,  "%lf", v);
	return std::string(szVal);
}

inline std::string I2Str(const int v)
{
	char szVal[10] = {0};
	_itoa(v, szVal, 10);
	return std::string(szVal);
}

inline std::string MakeColorStr(DWORD dwColorRGBA)
{
	BYTE* byV = (BYTE*)(&dwColorRGBA);
	char szV[25] = {0};
	
	DWORD dwTest = 0x00000001;
	BYTE* byPoint = (BYTE*)(&dwTest);
	if (byPoint[3] == 0x01)
	{
		sprintf(szV, "R=%d,G=%d,B=%d,A=%d", byV[0], byV[1], byV[2], byV[3]);
	}
	else
	{
		sprintf(szV, "R=%d,G=%d,B=%d,A=%d", byV[3], byV[2], byV[1], byV[0]);
	}

	return std::string(szV);
}



inline std::string MakePointer(DH_POINT pV)
{
	char* szText = new char[1024*5];
	sprintf(szText, "{X=%d,Y=%d}", pV.nx, pV.ny);
	std::string strRet(szText);
	delete[] szText;
	return strRet;
}

inline std::string MakePointers(DH_POINT* pV, int nPointCount)
{
	std::string strRet;
	for (int i = 0; i < nPointCount; i++)
	{
		strRet.append(MakePointer(*(pV + i)));
	}
	return strRet;
}



inline std::string MakeRect(DH_RECT rectV)
{
	char szText[128] = {0};
	sprintf(szText, "Left=%d,Top=%d,Right=%d,Bottom=%d", rectV.left, rectV.top, rectV.right, rectV.bottom);
	return std::string(szText);
}


// 物体动作:1:Appear 2:Move 3:Stay 4:Remove 5:Disappear 6:Split 7:Merge 8:Rename
inline std::string MakeActionStr(int nV)
{
	switch (nV)
	{
	case 1:
		return ConvertStr("Appear");
	case 2:
		return ConvertStr("Move");
	case 3:
		return ConvertStr("Stay");
	case 4:
		return ConvertStr("Remove");
	case 5:
		return ConvertStr("Disappear");
	case 6:
		return ConvertStr("Split");
	case 7:
		return ConvertStr("Merge");
	case 8:
		return ConvertStr("Rename");
	default:
		return ConvertStr("Unknow");
	}
}

inline std::string MakeSnapTypeStr(BYTE byV)
{
	switch (byV)
	{
	case 0:
		return ConvertStr("Radar upper limit");
	case 1:
		return ConvertStr("Radar lower limit");
	case 2:
		return ConvertStr("Vehicle inspection device upper limit");
	case 3:
		return ConvertStr("Vehicle inspection device lower limit");
	case 4:
		return ConvertStr("Reverse");
	case 5:
		return ConvertStr("Cross red light");
	case 6:
		return ConvertStr("Red light turn on");
	case 7:
		return ConvertStr("Red light turn off");
	case 8:
		return ConvertStr("All or gate");
	default:
		return ConvertStr("Unknow");
	}
}


inline std::string MakeRedLightDirStr(BYTE byV)
{
   if (byV == 0)
   {
	   return ConvertStr("Left");
   }
   else if (byV == 1)
   {
	   return ConvertStr("Straight");
   }
   else if (byV == 2)
   {
	   return ConvertStr("Right");
   }
   return std::string("Unknow");
}


inline std::string MakeLightColorStr(BYTE byV)
{
	if (byV == 0)
	{
		return ConvertStr("Green");
	}
	else if (byV == 1)
	{
		return ConvertStr("Red");
	}
	else if (byV == 2)
	{
		return ConvertStr("Yellow");
	}
	return std::string("Unknow");
}

inline std::string MakeLightColorStr2(BYTE byV)
{
	if (byV == 1)
	{
		return ConvertStr("Green");
	}
	else if (byV == 2)
	{
		return ConvertStr("Red");
	}
	else if (byV == 3)
	{
		return ConvertStr("Yellow");
	}
	return std::string("Unknow");
}

/***********************************************************************/
/*交通路口事件违章类型*/
// 第一位:闯红灯; RunRedLight
// 第二位:不按规定车道行驶;WrongLane
// 第三位:逆行; Retrograde
// 第四位：违章掉头;U-Trun
// 第五位:交通堵塞;TrafficJam
// 第六位:交通异常空闲TrafficIdle
// default: TrafficJunction
/************************************************************************/
inline std::string BR2StrForTrafficJunction(DWORD dwBR)
{
	std::string strRet;
	char* szSpliterStr = " && ";
	if (dwBR & 0x00000001)
	{
		strRet.append(ConvertStr("RunRedLight"));
	}
	if (dwBR & 0x00000002)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("WrongLane"));
	}
	if (dwBR & 0x00000004)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("Retrograde"));
	}
	if (dwBR & 0x00000008)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("U-Trun"));
	}
	if (dwBR & 0x00000016)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("TrafficJam"));
	}
	if (dwBR & 0x00000032)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("TrafficIdle"));
	}
	if (strRet.size() == 0)
	{
		strRet.append(ConvertStr("TrafficJunction"));
	}
	
	return strRet;
}

/************************************************************************/
/*卡口事件的违章类型*/
//第一位:逆行; Retrograde
// 第二位:压线行驶; Overline
// 第三位:超速行驶; Overspeed
// 第四位：欠速行驶;Underspeed
// 第五位:闯红灯; RunRedLight
//否则默认为: Trafficgate
/************************************************************************/
inline std::string BR2StrForTrafficGate(DWORD dwBR)
{
	std::string strRet;
	char* szSpliterStr = " && ";
	if (dwBR & 0x00000001)
	{
		strRet.append(ConvertStr("Retrograde"));
	}
	if (dwBR & 0x00000002)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("Overline"));
	}
	if (dwBR & 0x00000004)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("Overspeed"));
	}
	if (dwBR & 0x00000008)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("Underspeed"));
	}
	if (dwBR & 0x00000016)
	{
		if (strRet.size() != 0)
		{
			strRet.append(szSpliterStr);
		}
		strRet.append(ConvertStr("RunRedLight"));
	}
	if (strRet.size() == 0)
	{
		strRet.append(ConvertStr("Trafficgate"));
	}
	return strRet;
}

/************************************************************************/
/* NET_TIME to std::string                                              */
/************************************************************************/
inline std::string NetTime2Str(const NET_TIME& netTime)
{
	char buf[128] = {0};
	sprintf(buf, "%d-%d-%d %d:%d:%d", 
				netTime.dwYear, netTime.dwMonth, netTime.dwDay,
				netTime.dwHour, netTime.dwMinute, netTime.dwSecond);
	return std::string(buf);
}


/************************************************************************/
/* 比较两个NET_TIME的大小                                               */
/************************************************************************/
#define CMP(L, R) {if( (L) > (R) ){return 1;}else if( (L) < (R) ){return -1;}}
inline int NetTimeCmp(NET_TIME& left, NET_TIME& right)
{
	CMP(left.dwYear, right.dwYear)
	CMP(left.dwMonth, right.dwMonth)
	CMP(left.dwDay, right.dwDay)
	CMP(left.dwHour, right.dwHour)
	CMP(left.dwMinute, right.dwMinute)
	CMP(left.dwSecond, right.dwSecond)
	return 0;
}

/************************************************************************/
/* NET_TIME to std::string                                              */
/************************************************************************/
inline std::string NetTimeEx2Str(const NET_TIME_EX& netTime)
{
	char buf[128] = {0};
	sprintf(buf, "%d-%d-%d %d:%d:%d.%d", 
					netTime.dwYear, netTime.dwMonth, netTime.dwDay, netTime.dwHour,
					netTime.dwMinute, netTime.dwSecond, netTime.dwMillisecond );
	return std::string(buf);
}


/************************************************************************/
/* 比较两个NET_TIME的大小                                               */
/************************************************************************/
#define CMP(L, R) {if( (L) > (R) ){return 1;}else if( (L) < (R) ){return -1;}}
inline int NetTimeExCmp(NET_TIME_EX& left, NET_TIME_EX& right)
{
	CMP(left.dwYear, right.dwYear)
	CMP(left.dwMonth, right.dwMonth)
	CMP(left.dwDay, right.dwDay)
	CMP(left.dwHour, right.dwHour)
	CMP(left.dwMinute, right.dwMinute)
	CMP(left.dwSecond, right.dwSecond)
	CMP(left.dwMillisecond, right.dwMillisecond)
	return 0;
}


/************************************************************************/
/* 人工检查状态 0:未检查，1:正确 2:错误                                */
/************************************************************************/
const int LP_STATE_COUNT = 6;//牌照人工检查的状态的个数,更新下面的状态的时候，一定要更新这个变量
inline std::string I2State(int nState)
{
	switch(nState)
	{
	case 0:
		return ConvertStr("Not Checked");
		break;
	case 1:
		return ConvertStr("Right");
		break;
	case 2:
		return ConvertStr("Wrong");
	    break;
	case 3:
		return ConvertStr("No License Plate");
		break;
	case 4:
		return ConvertStr("Dirty License Plate");
		break;
	case 5:
		return ConvertStr("False Alarm");
		break;


		//下面的不是状态值
	default:
		return ConvertStr("Unknow State");
	    break;
	}
}

inline std::string MakeLP(char* szLP)
{
	if (strcmp(szLP, "") == 0)
	{
		std::string strRet = ConvertStr("No License plate");
		return strRet;
	}
	else
	{
		return std::string(szLP);
	}
}

// utf8 --> ansi
inline int ConvertUtf8ToAnsi(const char* lpszUtf8, int nUtf8Len, char* lpszAnsi, int nAnsiLen)
{
	if (lpszUtf8 == NULL || lpszAnsi == NULL || nUtf8Len <= 0 || nAnsiLen <= 0)
	{
		return 0;
	}

#ifdef WIN32	
	unsigned short* pWchar = new unsigned short[nUtf8Len + 1];
	ZeroMemory(pWchar, sizeof(unsigned short) * (nUtf8Len + 1));

	int nWideLen = MultiByteToWideChar(CP_UTF8, 0, lpszUtf8, nUtf8Len, (LPWSTR)pWchar, nUtf8Len);
	nAnsiLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)pWchar, nWideLen, lpszAnsi, nAnsiLen-1, 0, 0);
	lpszAnsi[nAnsiLen] = 0;
	delete[] pWchar;
	return nAnsiLen;
#else
	strncpy(lpszAnsi, (char*)lpszUtf8, __min(nUtf8Len, nAnsiLen));
	return __min(nUtf8Len, nAnsiLen);
#endif
}

inline std::string ConvertUtf8ToAnsi( const std::string& strUtf8 )
{
	std::string strAnsi;
	int nAnsiLen = strUtf8.length() + 1;
	char* pszAnsi = new char[nAnsiLen];
	memset(pszAnsi, 0, nAnsiLen);

	ConvertUtf8ToAnsi(strUtf8.c_str(), strUtf8.length(), pszAnsi, nAnsiLen);
	strAnsi = pszAnsi;
	delete[] pszAnsi;
	return strAnsi;
}

// ansi --> utf8
inline int ConvertAnsiToUtf8(const char* lpszAnsi, int nAnsiLen, char* lpszUtf8, int nUtf8Len)
{
	if (lpszUtf8 == NULL || lpszAnsi == NULL || nUtf8Len <= 0 || nAnsiLen <= 0)
	{
		return 0;
	}

#ifdef WIN32
	unsigned short* pWchar = new unsigned short[nAnsiLen + 1];
	ZeroMemory(pWchar, sizeof(unsigned short) * (nAnsiLen + 1));

	int nWideLen = MultiByteToWideChar(CP_ACP, 0, lpszAnsi, nAnsiLen, (LPWSTR)pWchar, nAnsiLen);
	nUtf8Len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pWchar, nWideLen, lpszUtf8, nUtf8Len-1, 0, 0);
	lpszUtf8[nUtf8Len] = 0;

	delete[] pWchar;
	return nUtf8Len;
#else
	memcpy(lpszUtf8, lpszAnsi,  __min(nUtf8Len, nAnsiLen));
	return __min(nUtf8Len, nAnsiLen);
#endif
}

inline std::string ConvertAnsiToUtf8( const std::string& strAnsi )
{
	std::string strUtf8;
	int nUtf8Len = strAnsi.length() * 2 + 1;
	char* pszUtf8 = new char[nUtf8Len];
	memset(pszUtf8, 0, nUtf8Len);

	ConvertAnsiToUtf8(strAnsi.c_str(), strAnsi.length(), pszUtf8, nUtf8Len);
	strUtf8 = pszUtf8;
	delete[] pszUtf8;
	return strUtf8;
}
