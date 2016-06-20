// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__91BEA165_7ED9_4D5B_BE46_C89FAAB15292__INCLUDED_)
#define AFX_INIFILE_H__91BEA165_7ED9_4D5B_BE46_C89FAAB15292__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_SECTION			255        //Section最大长度
#define MAX_KEY				2048+2048+10+3+2+1   //KeyValues最大长度(3)=(10)+(tab)*2+(2048)*2+
#define MAX_ALLSECTIONS		65535    //所有Section的最大长度
#define MAX_ALLKEYS			65535    //所有KeyValue的最大长度

class CIniFile  
{
public:
	BOOL GetFileExist();
	int GetAllSections(CStringArray& strArrSection);
	int GetAllKeysAndValues(CString  strSection,CStringArray& strArrKey,CStringArray& strArrKeyValue);
	int GetAllKeysAndValues1(CString  strSection,CStringArray& strArrKey,CStringArray& strArrKeyValue);
	void DeleteSection(CString strSection);
	void DeleteKey(CString strSection, CString strKey);
	void SetKeyValue(CString strSection, CString strKey,CString strKeyValue);

	CString GetKeyValue(CString strSection,CString strKey,CString strDefault="");
	CString GetReverseKey(CString strSection , CString strValue); //cf ++ 

	int GetIntKeyValue(CString strSection, CString strKey);
	//char * GetCharKeyValue(CString strSection, CString strKey);

	bool SetIniPath(CString strFullPath);
	bool SetIniPath(CString strExpandPath,CString strFileName);		//set ini file path
	CIniFile();
	virtual ~CIniFile();
	CString m_strPath;		//文件路径
	BOOL m_boolExist;

	
};

#endif // !defined(AFX_INIFILE_H__91BEA165_7ED9_4D5B_BE46_C89FAAB15292__INCLUDED_)

