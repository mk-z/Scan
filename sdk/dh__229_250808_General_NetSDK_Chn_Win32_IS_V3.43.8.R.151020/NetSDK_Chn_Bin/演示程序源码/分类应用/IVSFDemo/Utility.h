
#pragma once
#include "include/dhnetsdk.h"
#include <string>
#include "Picture.h"

#define PICDIR "PCStore\\"
#define SRCFILE "_src"
#define MATCHFILE "_match_"   

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
/* GUID to  CString                                                 */
/************************************************************************/
inline CString GuidToString(const GUID &guid)
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
	return CString(buf);
}

inline CString I2Str(const int v)
{
	char szVal[10] = {0};
	itoa(v, szVal, 10);
	return CString(szVal);
}

class CGuard
{
public:
	CGuard(CRITICAL_SECTION* pCS)
		:m_lock(pCS)
	{
		EnterCriticalSection(m_lock);
	}
	virtual ~CGuard()
	{
		LeaveCriticalSection(m_lock);
	}
	
private:
	CRITICAL_SECTION* m_lock;
};

