// Common.h: interface for the CCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMON_H__D9E1918F_1913_4DA5_9303_BDF22FED44C5__INCLUDED_)
#define AFX_COMMON_H__D9E1918F_1913_4DA5_9303_BDF22FED44C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define		THUMWIDTH		32
#define		THUMHEIGHT		32

#define _DELETE_(x) if(x){delete x;x = NULL;}
#define _DEL_ARRAY_(x) if(x){delete [] x; x = NULL;}
#define MEM_ZERO(stu) memset(&stu, 0, sizeof(stu))
#define SET_SIZE(stu) stu.dwSize = sizeof(stu)

typedef enum _VIDEO_STANDARD    //视频制式 
{
	PAL = 0,
	NTSC
} VIDEO_STANDARD;

typedef struct tagRESOLUTION
{
    CAPTURE_SIZE	emType;		//分辨类型
	int		nWidth;
	int		nHeight;
	char*   pTypeName;
} RESOLUTION, *PRESOLUTION, *LPRESOLUTION;

void Change_Utf8_Unicode(unsigned char * pUTF8, char *destbuf, int nUTF8Len, int nUniCodeLen);
void Change_Unicode_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen);
void Change_Utf8_Assic(unsigned char * pUTF8, char *destbuf, int nUTF8Len, int nUnicodeLen);
void Change_Assic_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen);

class CCommon  
{
public:
	int GetStrUTF8LengthFromGBK(char *pStrGBKData);
	CCommon();
	virtual ~CCommon();

	CString GetSysDataString(int nYear, int nMonth, int nDay);
		
	//CComboBox
	static int InitComboBox(CComboBox *pCComboBox , int nIndex, LPCTSTR lpszString, DWORD dwData = 0);

	//根据内部数据
	static int SetCurSelByData(CComboBox *pCComboBox, DWORD dwData);

	//获取IP
	CString GetIP(CIPAddressCtrl* pIPAddressCtrl);
	//显示IP地址
	void ShowIP(CIPAddressCtrl* pIPAddressCtrl, LPCTSTR lpszIP);

	CString GetCStringLeft(LPCTSTR lpszString, int nCount = -1);//-1代表不截取字符到终结符为止
	
	//获取这个月的天数
	int GetMonthDays(DWORD dwYear, DWORD dwMonth);
	
	void CheckEditLimitNum(CWnd* pWnd, DWORD dwMin, DWORD dwMax);

	CString GetEditTextByLimit(CWnd* pWnd);

	BOOL FilterSpecialWord(char *pStrInput, int len );

	//检差输入是不是数字
	BOOL CheckEditIsNum(CWnd* pWnd);
	//去除首尾空格
	BOOL CheckEditSpace(CWnd* pWnd , int nType = 1);//0为去除所有空格  1为不去除 中间空格 
	
//	HBITMAP LoadPicture(CString theFileName, CWnd* pWnd, long lWidth = THUMWIDTH, long lHeight = THUMHEIGHT);

	CString Get_Utf8_To_Unicode(unsigned char * pUTF8);
    
	BOOL CheckAllChr(CWnd* pWnd);
	BOOL CheckAllNum(CWnd* pWnd);
	

	int log2i(unsigned long x);
	//写数据  
	BOOL		WriteStructInfo(  LPCTSTR lpszSection,  // section name
								  LPCTSTR lpszKey,      // key name
								  char*   lpStruct,     // data buffer
								  UINT    uSizeStruct,  // size of data buffer
								  LPCTSTR szFile        // initialization file
								);

	//读数据
	BOOL		ReadStructInfo(	  LPCTSTR lpszSection,  // section name
								  LPCTSTR lpszKey,      // key name
								  char*   lpStruct,     // return buffer
								  UINT	  uSizeStruct,  // size of return buffer
								  LPCTSTR szFile        // initialization file name
								);


		/************************************************************************
	*	函数名称：	ReadResolution
	*	功能描述：	读取分辨率结构体
	*	参数列表：	lpszResolution	——[IN, OUT]分辨率结构体
	*				emVideoStandard	——[IN]视频制式, 默认PAL
	*				bSort			——[IN]是否排序，默认不排序
	*	返回值：	读取成功返回TRUE，失败返回FALSE;
	************************************************************************/
	BOOL ReadResolution( LPRESOLUTION    lpszResolution,         // 返回的分辨率结构体
						 int             nResoStructSize,        // 分辨率结构体大小
						 VIDEO_STANDARD  emVideoStandard = PAL,  // 视频制式
						 BOOL            bSort = FALSE           // 是否排序，默认不排序
						);
protected:

	int m_nDataMode;
private:
	static int compare(const void *arg1, const void *arg2); // 用于排序分辨率的比较函数
};

#endif // !defined(AFX_COMMON_H__D9E1918F_1913_4DA5_9303_BDF22FED44C5__INCLUDED_)
