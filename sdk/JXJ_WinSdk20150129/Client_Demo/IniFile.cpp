// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"
#include "direct.h"
#include "shlwapi.h"
#pragma   comment(lib,   "Shlwapi")



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile()
{
	//get the ini file path

}

CIniFile::~CIniFile()
{

}
bool CIniFile::SetIniPath(CString strFullPath)
{
	m_strPath=strFullPath;		//ini file path
	CString strFolderPath;
	int nPos;
	//增加判断文件夹是否存在,如果不存在则新建
	nPos=strFullPath.ReverseFind('\\');   
	strFolderPath=strFullPath.Left(nPos);
	if(!PathFileExists(strFolderPath))
	{
		::_mkdir(strFolderPath); 
	}
	//*/
	DWORD dwFlag=::GetFileAttributes(strFullPath);
	if (0xFFFFFFFF==dwFlag)		//file not exist
	{
		m_boolExist=false;
		return false;
	}
	if (FILE_ATTRIBUTE_DIRECTORY==dwFlag)		//the path is a direct
	{
		m_boolExist=false;
		return false;
	}
	m_boolExist=true;
	return true;
}
bool CIniFile::SetIniPath(CString strExpandPath,CString strFileName)
{

	//CString strIniFile=strIniPath;
	CString strExePath,strFolderPath;
	::GetModuleFileName(NULL,strExePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	int   nPos=strExePath.ReverseFind('\\');   
	strFolderPath=strExePath.Left(nPos);  

	m_strPath=strFolderPath+"\\"+strExpandPath+strFileName;		//ini file path

	//*
	//增加判断文件夹是否存在,如果不存在则新建
	nPos=m_strPath.ReverseFind('\\');   
	strFolderPath=m_strPath.Left(nPos);
	if(!PathFileExists(strFolderPath))
	{
		::_mkdir(strFolderPath); 
	}
	//*/
	DWORD dwFlag=::GetFileAttributes(m_strPath);
	if (0xFFFFFFFF==dwFlag)		//file not exist
	{
		m_boolExist=false;
		return false;
	}
	if (FILE_ATTRIBUTE_DIRECTORY==dwFlag)		//the path is a direct
	{
		m_boolExist=false;
		return false;
	}
	m_boolExist=true;
	return true;
}
CString CIniFile::GetReverseKey(CString strSection , CString strValue)
{//according the value Return key 
	int i,j,iPos=0,iFind=-1;
	char * chAllKeysAndValues , * chTempKeyAndValue;
	chAllKeysAndValues=new char [MAX_ALLKEYS];
	chTempKeyAndValue=new char [MAX_ALLKEYS];
	DWORD dwGetValue;
	CString strKey="",strTempKeyAndValue,strTempValue;

	ZeroMemory(chAllKeysAndValues,MAX_ALLKEYS);
	ZeroMemory(chTempKeyAndValue,MAX_ALLKEYS);

	dwGetValue=::GetPrivateProfileSection(
		(LPCTSTR)strSection,
		chAllKeysAndValues,
		MAX_ALLKEYS/sizeof(TCHAR),
		(LPCTSTR)m_strPath);
	for(i=0; i<MAX_ALLKEYS; i++)
	{   
		if( chAllKeysAndValues[i] == NULL ) 
		{
			if( chAllKeysAndValues[i] == chAllKeysAndValues[i+1] )
				break; 
		}
	}
	if(i!=0)
		i++;

	for(j=0; j<i; j++) 
	{ 
		chTempKeyAndValue[iPos++] = chAllKeysAndValues[j]; 
		if( chAllKeysAndValues[j] == NULL ) 
		{  
			strTempKeyAndValue = chTempKeyAndValue; 
			iFind=strTempKeyAndValue.Find('=');
			strTempValue=strTempKeyAndValue.Mid(iFind+1);
			if(strTempValue==strValue)
			{
				strKey=strTempKeyAndValue.Left(iFind);
				break;
			}
			iPos = 0; 
		} 
	}//*/
	delete [] chAllKeysAndValues;
	delete [] chTempKeyAndValue;
	return strKey;
}

CString CIniFile::GetKeyValue(CString strSection, CString strKey ,CString strDefault)
{//Read Key Value
	//TCHAR chKeyValue[MAX_KEY];
	char * chKeyValue1;
	chKeyValue1=new char[MAX_KEY];

	DWORD dwGetValue;
	CString strKeyValue=_T("");
	dwGetValue=::GetPrivateProfileString(
		(LPCTSTR)strSection,
		(LPCTSTR)strKey,
		_T(""),
		chKeyValue1,
		MAX_KEY/sizeof(TCHAR),
		(LPCTSTR)m_strPath);
	strKeyValue=chKeyValue1;
	delete [] chKeyValue1;
	chKeyValue1=NULL;
	if(strKeyValue.IsEmpty())
		strKeyValue=strDefault;
	return strKeyValue;
}
/*
char * CIniFile::GetCharKeyValue(CString strSection, CString strKey)
{//Read Key Value
	TCHAR chKeyValue[MAX_KEY];
	DWORD dwGetValue;
	CString strKeyValue=_T("");
	dwGetValue=::GetPrivateProfileString(
		(LPCTSTR)strSection,
		(LPCTSTR)strKey,
		_T(""),
		chKeyValue,
		sizeof(chKeyValue)/sizeof(TCHAR),
		(LPCTSTR)m_strPath);

	return chKeyValue;
}*/

int CIniFile::GetIntKeyValue(CString strSection, CString strKey)
{//Read Key Value
	TCHAR chKeyValue[MAX_KEY];
	DWORD dwGetValue;
	CString strKeyValue=_T("");
	dwGetValue=::GetPrivateProfileString(
		(LPCTSTR)strSection,
		(LPCTSTR)strKey,
		_T(""),
		chKeyValue,
		sizeof(chKeyValue)/sizeof(TCHAR),
		(LPCTSTR)m_strPath);

	return atoi(chKeyValue);
}

void CIniFile::SetKeyValue(CString strSection, CString strKey,CString strKeyValue)
{//Set Key Value
	::WritePrivateProfileString(
		(LPCTSTR)strSection,
		(LPCTSTR)strKey,
		(LPCTSTR)strKeyValue,
		(LPCTSTR)m_strPath);
}

void CIniFile::DeleteKey(CString strSection, CString strKey)
{//Delete Key
	::WritePrivateProfileString(
		(LPCTSTR)strSection,
		(LPCTSTR)strKey,
		NULL,
		(LPCTSTR)m_strPath);
}

void CIniFile::DeleteSection(CString strSection)
{//Delete Section
	::WritePrivateProfileString(
		(LPCTSTR)strSection,
		NULL,
		NULL,
		(LPCTSTR)m_strPath);
}



int CIniFile::GetAllSections(CStringArray& strArrSection)
{//取得所有section
	int dwGetValue,i,j,iPos=0;
	TCHAR chAllSections[MAX_ALLKEYS];
	TCHAR chTempAllSections[MAX_ALLKEYS];
	CString strTempKey;
	ZeroMemory(chAllSections,MAX_ALLKEYS);
	ZeroMemory(chTempAllSections,MAX_ALLKEYS);
	dwGetValue=::GetPrivateProfileSectionNames(
		chAllSections,      // 指向一个缓冲区，用来保存返回的所有节名
		sizeof(chAllSections)/sizeof(TCHAR),                  // 参数lpszReturnBuffer的大小
		(LPCTSTR)m_strPath);
	for(i=0; i<MAX_ALLSECTIONS; i++)
	{   
		if( chAllSections[i] == NULL ) 
		{
			if( chAllSections[i] == chAllSections[i+1] )
				break; 
		}
	}
	i++;
	strArrSection.RemoveAll();
	for(j=0; j<i; j++) 
	{ 
		chTempAllSections[iPos++] = chAllSections[j]; 
		if( chAllSections[j] == NULL ) 
		{  
			strTempKey = chTempAllSections; 
			strArrSection.Add( strTempKey.Mid(strTempKey.Find('=')+1) );
			ZeroMemory(chTempAllSections, MAX_KEY);
			iPos = 0; 
		} 
	}
	return strArrSection.GetSize();
}
int CIniFile::GetAllKeysAndValues(CString strSection,CStringArray& strArrKey,CStringArray& strArrKeyValue)
{
	int dwGetValue,i,j,iPos=0;
	char *chAllKeysAndValues1 = NULL;
	char *chTempKeyAndValue1 = NULL;
	chAllKeysAndValues1=new char[MAX_ALLKEYS];
	chTempKeyAndValue1=new char[MAX_ALLKEYS];

	CString strTempKey = _T("");

	memset(chAllKeysAndValues1,'\0',MAX_ALLKEYS);
	memset(chTempKeyAndValue1,'\0',MAX_ALLKEYS);
	dwGetValue=::GetPrivateProfileSection(
		(LPCTSTR)strSection,
		chAllKeysAndValues1,
		MAX_ALLKEYS/sizeof(TCHAR),
		(LPCTSTR)m_strPath);
	for(i=0; i<MAX_ALLSECTIONS; i++)
	{   
		if( chAllKeysAndValues1[i] == '\0' ) 
		{
			if( chAllKeysAndValues1[i] == chAllKeysAndValues1[i+1] )
				break; 
		}
	}
	if(i!=0)//cf++
		i++;
	strArrKey.RemoveAll();
	strArrKeyValue.RemoveAll();
	for(j=0; j<i; j++) 
	{ 
		chTempKeyAndValue1[iPos++] = chAllKeysAndValues1[j]; 
		if( chAllKeysAndValues1[j] == '\0' ) 
		{  
			strTempKey = _T("");
			strTempKey.Format(_T("%s"),chTempKeyAndValue1); 
			strArrKey.Add( strTempKey.Left(strTempKey.Find('=')) );
			strArrKeyValue.Add( strTempKey.Mid(strTempKey.Find('=')+1) );
			memset(chTempKeyAndValue1,'\0',MAX_ALLKEYS);
			iPos = 0; 
		} 
	}
	delete[] chAllKeysAndValues1;
	chAllKeysAndValues1=NULL;
	delete[] chTempKeyAndValue1;
	chTempKeyAndValue1=NULL;
	chAllKeysAndValues1 = NULL;

	return strArrKey.GetSize();
}

int CIniFile::GetAllKeysAndValues1(CString strSection,CStringArray& strArrKey,CStringArray& strArrKeyValue)
{
	int dwGetValue,i,j,iPos=0;
	char *chAllKeysAndValues1 = NULL;
	char *chTempKeyAndValue1 = NULL;
	chAllKeysAndValues1=new char[MAX_ALLKEYS];
	chTempKeyAndValue1=new char[MAX_ALLKEYS];

	CString strTempKey = _T("");

	memset(chAllKeysAndValues1,'\0',MAX_ALLKEYS);
	memset(chTempKeyAndValue1,'\0',MAX_ALLKEYS);
	dwGetValue=::GetPrivateProfileSection(
		(LPCTSTR)strSection,
		chAllKeysAndValues1,
		MAX_ALLKEYS/sizeof(TCHAR),
		(LPCTSTR)m_strPath);
	for(i=0; i<MAX_ALLSECTIONS; i++)
	{   
		if( chAllKeysAndValues1[i] == '\0' ) 
		{
			if( chAllKeysAndValues1[i] == chAllKeysAndValues1[i+1] )
				break; 
		}
	}
	if(i!=0)//cf++
		i++;
	strArrKey.RemoveAll();
	strArrKeyValue.RemoveAll();
	for(j=0; j<i; j++) 
	{ 
		chTempKeyAndValue1[iPos++] = chAllKeysAndValues1[j]; 
		if( chAllKeysAndValues1[j] == '\0' ) 
		{  
			strTempKey = _T("");
			strTempKey.Format(_T("%s"),chTempKeyAndValue1); 
			strArrKey.Add( strTempKey.Left(strTempKey.Find('=')) );
			strArrKeyValue.Add( strTempKey.Mid(strTempKey.Find('=')+1) );
			memset(chTempKeyAndValue1,'\0',MAX_ALLKEYS);
			iPos = 0; 
		} 
	}
	delete[] chAllKeysAndValues1;
	chAllKeysAndValues1=NULL;
	delete[] chTempKeyAndValue1;
	chTempKeyAndValue1=NULL;
	chAllKeysAndValues1 = NULL;

	return strArrKey.GetSize();
}

BOOL CIniFile::GetFileExist()
{
	return 	m_boolExist;
}

