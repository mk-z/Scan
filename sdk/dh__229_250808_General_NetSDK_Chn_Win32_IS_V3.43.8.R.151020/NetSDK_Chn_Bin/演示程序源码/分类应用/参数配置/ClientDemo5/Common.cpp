// Common.cpp: implementation of the CCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Common.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommon::CCommon()
{
	m_nDataMode = -1;	
}

CCommon::~CCommon()
{

}

CString CCommon::GetSysDataString(int nYear, int nMonth, int nDay)
{
	if (-1 == m_nDataMode)
	{
		char buffer[2] = {0};
		if (GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IDATE , buffer, sizeof(buffer)) > 0)
		{
			m_nDataMode = atoi(buffer);
		}	
	}
	
	CString strResult;

	if (m_nDataMode >= 0)
	{
		switch(m_nDataMode)
		{
		case 1:			strResult.Format("%02d-%02d-%04d", nDay, nMonth, nYear);		break;//Day-Month-Year 
		case 2:			strResult.Format("%04d-%02d-%02d", nYear, nMonth,nDay  );		break;//Year-Month-Day 
		default:		strResult.Format("%02d-%02d-%04d", nMonth, nDay, nYear);	    break;//Month-Day-Year 
		}
	}
	
	return strResult;
}
	
CString CCommon::GetIP(CIPAddressCtrl* pIPAddressCtrl)
{
	CString strIP("");
	//初始显示IP
	BYTE Field0 = 0;
	BYTE Field1 = 0;
	BYTE Field2 = 0;
	BYTE Field3 = 0;
	if (NULL != pIPAddressCtrl)
	{
		pIPAddressCtrl->GetAddress(Field0, Field1, Field2, Field3);
	}

	if (0 == Field0 && 0 == Field1 && 0 == Field2 && 0 == Field3)
	{
	}
	else
	{
		strIP.Format("%d.%d.%d.%d",Field0, Field1, Field2, Field3);
	}
	
	return strIP;
}

void CCommon::ShowIP(CIPAddressCtrl* pIPAddressCtrl, LPCTSTR lpszIP)
{
	if (NULL != pIPAddressCtrl && IsWindow(pIPAddressCtrl->m_hWnd))
	{
		//初始显示IP
		int Field0 = 0;
		int Field1 = 0;
		int Field2 = 0;
		int Field3 = 0;
		if ("" != lpszIP)
		{
			CString strIP(lpszIP);
			CString val("");

			int nFirst = 0;
			int nNext = 0;
			strIP.TrimLeft();
			strIP.TrimRight();
			
			//取 Field0
			nNext = strIP.Find('.', nFirst);
			val = strIP.Mid(nFirst, nNext - nFirst);
			val.TrimLeft();
			val.TrimRight();
			Field0 = atoi(val);
			
			//取 Field1
			nFirst = nNext + 1;
			nNext = strIP.Find('.', nFirst);
			val = strIP.Mid(nFirst, nNext - nFirst);
			val.TrimLeft();
			val.TrimRight();
			Field1 = atoi(val);
			
			//取 Field2
			nFirst = nNext + 1;
			nNext = strIP.Find('.', nFirst);
			val = strIP.Mid(nFirst, nNext - nFirst);
			val.TrimLeft();
			val.TrimRight();
			Field2 = atoi(val);
			
			//取 Field3
			nFirst = nNext + 1;
			val = strIP.Mid(nFirst);
			val.TrimLeft();
			val.TrimRight();
			Field3 = atoi(val);

			pIPAddressCtrl->SetAddress(Field0, Field1, Field2, Field3);
		}
		else
		{
			pIPAddressCtrl->ClearAddress();
		}
	}
}

int CCommon::InitComboBox(CComboBox *pCComboBox , int nIndex, LPCTSTR lpszString, DWORD dwData /* = 0 */)
{
	int nRet = -1;
	if (NULL != pCComboBox)
	{	
		nRet = pCComboBox->InsertString(nIndex, lpszString);
		if (nRet >= 0)
		{
			if (CB_ERR == pCComboBox->SetItemData(nRet, dwData))
			{
				ASSERT(FALSE);
			}			
		}
	}

	return nRet;
}

int CCommon::SetCurSelByData(CComboBox *pCComboBox, DWORD dwData)
{
	int nRet = -1;
	
	if (pCComboBox)
	{
	
		int nCount = pCComboBox->GetCount();
		if (nCount > 0)
		{
			BOOL bSetDef = TRUE;
			for (int ni = 0 ; ni < nCount ; ni++)
			{
				if (dwData == (int)pCComboBox->GetItemData(ni))
				{
					nRet = ni;
					bSetDef = FALSE;
					pCComboBox->SetCurSel(ni);
					break;
				}
			}

			if (bSetDef)
			{
				pCComboBox->SetCurSel(nCount - 1);
				nRet =nCount - 1;
			}
		}
	}
	return nRet;
}


CString CCommon::GetCStringLeft(LPCTSTR lpszString, int nCount /* = -1 */)
{
	CString Str(lpszString);
	int ni = nCount;
	while(Str.GetLength() > nCount)
	{
		CString StrTmp = Str.Left(ni);
		Str = StrTmp;
		ni--;
	}

	return Str;
}

BOOL CCommon::CheckEditSpace(CWnd* pWnd , int nType)
{
	if (NULL == pWnd)
	{
		return FALSE;
	}

	BOOL bWriteAgain = FALSE;

	CEdit *pEdit = (CEdit*)pWnd;

	CString sRecLen("");	
	pEdit->GetWindowText(sRecLen);

	int nNum = sRecLen.GetLength();
	if (nNum > 0 )
	{
		sRecLen.TrimLeft();
		sRecLen.TrimRight();
		int nNumSecond = sRecLen.GetLength();

		if (nNumSecond != nNum || 1 != nType)
		{
			if (nNumSecond != nNum)
			{
				bWriteAgain = TRUE;
			}

			for (int ni = 0 ; ni < nNumSecond ; ni++)
			{
				if (sRecLen.GetAt(ni) == 32/*ASCII中的空格*/)
				{
					if (!bWriteAgain)
					{
						bWriteAgain = TRUE;
					}

					sRecLen.Delete(ni,1);

					nNumSecond--;

					ni--;
				}
			}
		}
	}

	// 防止死循环只有里面有异常字符才更新编辑框
	if (bWriteAgain)
	{
		pEdit->SetWindowText(sRecLen);
	}
	
	return !bWriteAgain;
}

void CCommon::CheckEditLimitNum(CWnd* pWnd, DWORD dwMin, DWORD dwMax)
{
	if (pWnd)
	{
		BOOL bWriteAgain = FALSE;

		CEdit *pEdit = (CEdit*)pWnd;

		CString sRecLen("");
		pEdit->GetWindowText(sRecLen);

		int nNum = sRecLen.GetLength();
		if ( nNum > 0 )
		{
			for (int ni = 0 ; ni < nNum ; ni++)
			{		
				if (sRecLen.GetAt(ni) > '9' || sRecLen.GetAt(ni) < '0' /*|| ( nNum > 1 && sRecLen.GetAt(ni) == '0')*/)
				{
					if (!bWriteAgain)
					{
						bWriteAgain = TRUE;
					}			

					char data = sRecLen.GetAt(ni);
					if ( data < 0)
					{
						sRecLen.Delete(ni,2);
						nNum -= 2;
					}
					else
					{
						sRecLen.Delete(ni,1);
						nNum -= 1;
					}
					
					ni --;
				}
			}				
		}
		
		DWORD dwNum = atoi(sRecLen);
		if (dwNum < dwMin || dwNum > dwMax || sRecLen.IsEmpty())
		{
			bWriteAgain = TRUE;
			if (dwNum < dwMin){dwNum = dwMin;}
			if (dwNum > dwMax){dwNum = dwMax;}
			sRecLen.Format("%ld",dwNum);
		}

		// 防止死循环只有里面有异常字符才更新编辑框
		if (bWriteAgain)
		{
			pEdit->SetWindowText(sRecLen);
		}
	}
}

BOOL CCommon::CheckEditIsNum(CWnd* pWnd)
{
	if (NULL == pWnd)
	{
		return FALSE;
	}

	BOOL bWriteAgain = FALSE;

	CEdit *pEdit = (CEdit*)pWnd;

	CString sRecLen("");
	pEdit->GetWindowText(sRecLen);

	int nNum = sRecLen.GetLength();
	if ( nNum > 0 )
	{
		for (int ni = 0 ; ni < nNum ; ni++)
		{		
			if (sRecLen.GetAt(ni) > '9' || sRecLen.GetAt(ni) < '0' /*|| ( nNum > 1 && sRecLen.GetAt(ni) == '0')*/)
			{
				if (!bWriteAgain)
				{
					bWriteAgain = TRUE;
				}			

				char data = sRecLen.GetAt(ni);
				if ( data < 0)
				{
					sRecLen.Delete(ni,2);
					nNum -= 2;
				}
				else
				{
					sRecLen.Delete(ni,1);
					nNum -= 1;
				}
				
				ni --;
			}
		}				
	}

	// 防止死循环只有里面有异常字符才更新编辑框
	if (bWriteAgain)
	{
		pEdit->SetWindowText(sRecLen);
	}

	return !bWriteAgain;
} 

CString CCommon::GetEditTextByLimit(CWnd* pWnd)
{
	CString strRet("");
	if (pWnd)
	{
		CEdit *pEdit = (CEdit*)pWnd;
		UINT unLimit = pEdit->GetLimitText();
		CString str("");
		pEdit->GetWindowText(str);
		//UINT uni = unLimit;
		UINT unitotal = str.GetLength();
		UINT uni = 0;
		if(unitotal > unLimit)
		{
			while (uni < unLimit )
			{
				
				if (str.GetAt(uni ) < 0 )
				{	
					uni += 2;


		// 				if (str.GetAt(uni - 1) < 0)
		// 				{
		// 					str = str.Left(uni - 1);
		// 					uni -= 2;
		// 				}
		// 				else
		// 				{
		// 					str = str.Left(uni);
		// 					uni--;
		// 				}
				}
				else
				{
		//				str = str.Left(uni);
		//				uni--;
					uni += 1;
					
				}
				if(uni <= unLimit)
				{
					strRet = str.Left(uni);
				}
			}	
		}
		else
		{
			strRet = str;
		}

		
	//	strRet = str;
	}
	return strRet;
}

BOOL CCommon::FilterSpecialWord(char *pStrInput, int len )
{
	for(int i=0;i<len;i++)
	{
		if(pStrInput[i] == '&')
		{
			return FALSE; 
		}
	}
	return TRUE;
}

int CCommon::GetMonthDays(DWORD dwYear, DWORD dwMonth)
{
	if (dwMonth < 1 || dwMonth > 12)
	{
		return -1;
	}
	int nDayCount = 0;
	switch(dwMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:	nDayCount = 31;		break;
	case 2:
		{
			nDayCount = 28;
			if (0 == (dwYear%4))
			{
				nDayCount = 29;
			}
		}
	    break;
	default:	nDayCount = 30;		break;
	}

	return nDayCount;
}


//////////////////////////////////////////////////////////////////////////

void W2A_mine(wchar_t *lpszW, char *lpszA)
{
#ifdef WIN32
	int nLen = WideCharToMultiByte(CP_ACP, 0, lpszW, 1, NULL, 0, NULL, NULL); 
    int nRet = WideCharToMultiByte(CP_ACP, 0, lpszW, 1, lpszA, nLen, NULL, NULL);
	if (!nRet) 
	{
		int error = GetLastError();
	}
#endif
}

size_t Utf_Unicode(wchar_t &temp, unsigned char * pUTF8)
{
	int count_bytes = 0;
	unsigned char byte_one = 0, byte_other = 0x3f; // 用于位与运算以提取位值 0x3f-->00111111
	wchar_t tmp_wchar = L'0';
	
	if (!pUTF8)
		return -1;
	
	for (;;) // 检测字节序列长度,根据第一个字节头的1个个数
	{
		if (pUTF8[0] <= 0x7f)
		{
			count_bytes = 1; // ASCII字符: 0xxxxxxx( ~ 01111111)
			byte_one = 0x7f; // 用于位与运算, 提取有效位值, 下同 01111111
			break;
		}
		if ( (pUTF8[0] >= 0xc0) && (pUTF8[0] <= 0xdf) )
		{
			count_bytes = 2; // 110xxxxx(110 00000 ~ 110 111111)
			byte_one = 0x1f; //00011111 第一字节有效位的个数
			break;
		}
		if ( (pUTF8[0] >= 0xe0) && (pUTF8[0] <= 0xef) )
		{
			count_bytes = 3; // 1110xxxx(1110 0000 ~ 1110 1111)
			byte_one = 0x0f; //00001111
			break;
		}
		if ( (pUTF8[0] >= 0xf0) && (pUTF8[0] <= 0xf7) )
		{
			count_bytes = 4; // 11110xxx(11110 000 ~ 11110 111)
			byte_one = 0x07;
			break;
		}
		if ( (pUTF8[0] >= 0xf8) && (pUTF8[0] <= 0xfb) )
		{
			count_bytes = 5; // 111110xx(111110 00 ~ 111110 11)
			byte_one = 0x03;
			break;
		}
		if ( (pUTF8[0] >= 0xfc) && (pUTF8[0] <= 0xfd) )
		{
			count_bytes = 6; // 1111110x(1111110 0 ~ 1111110 1)
			byte_one = 0x01;
			break;
		}
		return 8; // 以上皆不满足则为非法序列
	}
	// 以下几行析取UTF-8编码字符各个字节的有效位值
	//先得到第一个字节的有效位数据
	tmp_wchar = pUTF8[0] & byte_one;
	for (int i=1; i < count_bytes; i++)
	{
		tmp_wchar <<= 6; // 左移6位后与后续字节的有效位值"位或"赋值
		tmp_wchar = tmp_wchar | (pUTF8[i] & byte_other);//先与后或
	}
	// 位值析取__End!
	temp = tmp_wchar;
	return count_bytes;
}

//从sdk copy过来的转换函数
//----------------------------------------------转化最好用这2个函数--------,其他函数有问题.
void Change_Utf8_Assic(unsigned char * pUTF8, char *destbuf, int nUTF8Len, int nUnicodeLen)
{
	//从UTF8 -> GBK, web应用上字串是GBK编码
	//int nSrcStrLen = strlen((char*)pUTF8);
	int nSrcStrLen = nUTF8Len;
	int nDestStrLen = nUnicodeLen /*nSrcStrLen*2*/;
	char* tmpBuf = new char[nDestStrLen*2];
	memset(tmpBuf, 0, nDestStrLen);
	
	//因为中英文混合的, 字宽各有长短, 特别是对于UTF8, 这里统一将其转换为widnows内部使用的标准格式WideChar(不管中英文, 统一2bytes)
	int nNum = MultiByteToWideChar(CP_UTF8, 0, (char*)pUTF8, nSrcStrLen, (LPWSTR)tmpBuf, nDestStrLen);

	//然后将windows内部标准格式的WideChar转为特殊形式的编码,这里转换到web页面上能显示的GBK格式, 但英文只占一个byte
	nNum = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)tmpBuf, nNum, destbuf, nSrcStrLen, NULL, NULL);
	
	delete [] tmpBuf;
	tmpBuf = NULL;
	
	return ;
}

void Change_Assic_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen)
{
	//从GBK -> UTF8
	int nDestStrLen = nlen*2;
	char* tmpBuf = new char[nDestStrLen];
	memset(tmpBuf, 0, nDestStrLen);
	
	//将配置页面上的GBK格式先统一转为windows内部标准格式WideChar
	int nNum = MultiByteToWideChar(CP_ACP, 0, (char*)pStrGBKData, nlen, (LPWSTR)tmpBuf, nDestStrLen);

	//然后将标准格式的WideChar统一转为UTF8编码
	nNum = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)tmpBuf, nNum, pbuf, buflen, NULL, NULL);
	
	delete [] tmpBuf;
	tmpBuf = NULL;
	
	return ;
}
//-------------------------------------------




void Change_Utf8_Unicode(unsigned char * pUTF8, char *destbuf, int nUTF8Len, int nUniCodeLen)
{
#ifdef WIN32
	size_t num = 0;
	wchar_t  temp = 0;
	int index = 0;
	unsigned char *pOrginUTF8 = pUTF8;
	while (1)
	{ 
		if((pUTF8-pOrginUTF8)>=nUTF8Len) //长度限制
		{
			break;
		}
		if(*pUTF8 == NULL/* || *pUTF8== '0'*/)
		{
			break;
		}
		num = Utf_Unicode(temp, pUTF8);
		if(num == 8)
		{
			pUTF8 = pUTF8 + 1;
		}
		else
		{
			char buffer[2] = {0};
			W2A_mine(&temp, buffer);
			if(num < 2)
			{
				destbuf[index] = buffer[0];
				index ++;
			}
			else
			{
				destbuf[index] = buffer[0];
				destbuf[index+1] = buffer[1];
				index += 2;
			}
			pUTF8 = pUTF8 + num;
		}
	}
#else	//linux
	iconv_t cd = iconv_open("gbk","utf-8"); 
	if(cd==(iconv_t)-1)
	{
		printf("iconv_t fail.\n");
	}
	
	size_t inLen = strlen((char*)pUTF8);
	size_t outLen = inLen;
	unsigned int nconv = iconv(cd, (char**)&pUTF8, &inLen, &destbuf, &outLen);
	
	iconv_close(cd);
#endif

	return ;
}

CString CCommon::Get_Utf8_To_Unicode(unsigned char * pUTF8)
{
/*
0000 - 007F 　　　　　　　　　　　　　　　0xxxxxxx
0080 - 07FF 　　　　　　　　　　　　　　　110xxxxx 10xxxxxx
0800 - FFFF 　　　　　　　　　　　　　　　1110xxxx 10xxxxxx 10xxxxxx
首字符最高位为0时为通用英文
字符最高位1时表示 属于多字节字符一员
字符最高位开始连续N位为1后面跟0 表示该字符有N个字节(这算法1个字符最多可以加到8字节)
*/

	unsigned char ch[13] = {0};
	memcpy(ch, pUTF8, 12);
	int i, j;
	for (i = 0 ; i < 12 ; i++)
	{
		if (ch[11 - i] > 191)//10111111
		{
			for (j = 0 ; j < 8 ; j++)
			{
				if (0 == ((0x80>>j) & ch[11-i]))
				{
					j--;
					break;
				}
			}
			
			if (i < j)
			{
				ch[11 - i] = 0;
			}

			break;
		}		
	}
	char chTmp[256];
	memset(chTmp, 0, 256 * sizeof(char));
	Change_Utf8_Unicode(ch, chTmp, 256, 256);
	CString str(chTmp);
	return str;
}
////////////////////////////////////////////////////////////////////////////
//字符格式转换函数 A2W

void A2W_Mine(char *lpszA, wchar_t *lpszW)
{
#ifdef WIN32
	int nLen = MultiByteToWideChar(CP_ACP, 0, lpszA, 2, NULL, NULL);
	int nRet = MultiByteToWideChar(CP_ACP, 0, lpszA, 2, lpszW, nLen);
	if (!nRet) 
	{
		//TRACE("convert error");
		int error = GetLastError();
	}
#else	//linux
	size_t result = mbstowcs(lpszW, lpszA, (size_t)1);
#endif
}

size_t Single_UNICODE_UTF8(char * dest_str, wchar_t src_wchar)
{
	int count_bytes = 0;
	wchar_t byte_one = 0, byte_other = 0x3f; // 用于位与运算以提取位值 0x3f--->00111111
	unsigned char utf_one = 0, utf_other = 0x80; // 用于"位或"置标UTF-8编码 0x80--->1000000
	wchar_t tmp_wchar = L'0'; // 用于宽字符位置析取和位移(右移6位)
	unsigned char tmp_char = '0';
	
	if (!src_wchar)//
		return (size_t)-1;
	
	for (;;) // 检测字节序列长度
	{
		if (src_wchar <= 0x7f)
		{ // <=01111111
			count_bytes = 1; // ASCII字符: 0xxxxxxx( ~ 01111111)
			byte_one = 0x7f; // 用于位与运算, 提取有效位值, 下同
			utf_one = 0x0;
			break;
		}
		if ( (src_wchar > 0x7f) && (src_wchar <= 0x7ff) )
		{ // <=0111,11111111
			count_bytes = 2; // 110xxxxx 10xxxxxx[1](最多11个1位, 简写为11*1)
			byte_one = 0x1f; // 00011111, 下类推(1位的数量递减)
			utf_one = 0xc0; // 11000000
			break;
		}
		if ( (src_wchar > 0x7ff) && (src_wchar <= 0xffff) )
		{ //0111,11111111<=11111111,11111111
			count_bytes = 3; // 1110xxxx 10xxxxxx[2](MaxBits: 16*1)
			byte_one = 0xf; // 00001111
			utf_one = 0xe0; // 11100000
			break;
		}
		if ( (src_wchar > 0xffff) && (src_wchar <= 0x1fffff) )
		{ //对UCS-4的支持..
			count_bytes = 4; // 11110xxx 10xxxxxx[3](MaxBits: 21*1)
			byte_one = 0x7; // 00000111
			utf_one = 0xf0; // 11110000
			break;
		}
		if ( (src_wchar > 0x1fffff) && (src_wchar <= 0x3ffffff) )
		{
			count_bytes = 5; // 111110xx 10xxxxxx[4](MaxBits: 26*1)
			byte_one = 0x3; // 00000011
			utf_one = 0xf8; // 11111000
			break;
		}
		if ( (src_wchar > 0x3ffffff) && (src_wchar <= 0x7fffffff) )
		{
			count_bytes = 6; // 1111110x 10xxxxxx[5](MaxBits: 31*1)
			byte_one = 0x1; // 00000001
			utf_one = 0xfc; // 11111100
			break;
		}
		return (size_t)-1; 
	}
	
	tmp_wchar = src_wchar;
	for (int i = count_bytes; i > 1; i--)
	{ // 一个宽字符的多字节降序赋值
		tmp_char = (unsigned char)(tmp_wchar & byte_other);///后6位与byte_other 00111111
		dest_str[i - 1] = (tmp_char | utf_other);/// 在前面加10----跟10000000或
		tmp_wchar >>= 6;//右移6位
	}
	
	tmp_char = (unsigned char)(tmp_wchar & byte_one);
	dest_str[0] = (tmp_char | utf_one);
	
	return count_bytes;
}

void Change_Unicode_UTF8(char *pStrGBKData, int nlen, char *pbuf, int buflen)
{
#ifdef WIN32

	int oldlen = 0;
	int newlen = 0;
	char *pUTF8 = new char[nlen*2+2];
	memset(pUTF8, 0 , nlen*2+2);

	while(oldlen < nlen)
	{
		if(*(pStrGBKData + oldlen) >= 0)
		{
			*(pUTF8 + newlen) = *(pStrGBKData + oldlen);
			newlen ++;
			oldlen ++;
		}
		else
		{
			char tmpbuf[8] = {0};
			wchar_t pUnicode;
			A2W_Mine(pStrGBKData + oldlen, &pUnicode);
			Single_UNICODE_UTF8(tmpbuf, pUnicode);
			*(pUTF8 + newlen) = tmpbuf[0];
			*(pUTF8 + newlen + 1) = tmpbuf[1];
			*(pUTF8 + newlen + 2) = tmpbuf[2];
			newlen += 3;
			oldlen += 2;
		}
	}

	pUTF8[newlen] = '\0';
	memcpy(pbuf, pUTF8, (nlen*2+2 > buflen)? buflen : nlen*2+2);
	delete pUTF8;
	
#else	//linux
	iconv_t cd = iconv_open("utf-8","gbk"); 
	if(cd==(iconv_t)-1)
	{
		printf("iconv_t fail.\n");
	}
	
	size_t inLen = nlen;
	size_t outLen = buflen;
	unsigned int nconv = iconv(cd, &pStrGBKData, &inLen, &pbuf, &outLen);
	
	iconv_close(cd);
#endif

	return ;
}


//HBITMAP CCommon::LoadPicture(CString theFileName, CWnd* pWnd, long lWidth /* = THUMWIDTH */, long lHeight /* = THUMHEIGHT */)
/*{
	if (NULL == pWnd || lWidth < 1 || lHeight < 1)
	{
	}

	CString pFSize;
	WCHAR wpath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, theFileName, -1, wpath, MAX_PATH);

	IPicture* pPic;
	OleLoadPicturePath(wpath, NULL, NULL, NULL, IID_IPicture,(LPVOID*)&pPic);

	if (pPic==NULL) 
	{
		return NULL;
	}

	HBITMAP hPic = NULL;
	pPic->get_Handle((UINT*)&hPic);

	long nWidth  = lWidth;
	long nHeight = lHeight;

	long mWid,mHei;
	pPic->get_Height(&mHei);
	pPic->get_Width(&mWid);

	HBITMAP hPicRet = (HBITMAP)CopyImage(hPic, IMAGE_BITMAP, nWidth, nHeight , LR_COPYDELETEORG); 

	
	HBRUSH hBrushBorder=::CreateSolidBrush(RGB(192, 192, 192));
	HBRUSH hBrushBk=::CreateSolidBrush(RGB(255, 255, 255));

	RECT rcBorder;
	rcBorder.left=rcBorder.top=0;
	rcBorder.right	=	lWidth;
	rcBorder.bottom	=	lHeight;

	const float fRatio=(float)lHeight/lWidth;

	int XDest = 0;
	int YDest = 0;
	int nDestWidth = 0;
	int nDestHeight = 0;

	const float fImgRatio=(float)mHei/mWid;
	if(fImgRatio > fRatio)
	{
		nDestWidth=(int)(lHeight/fImgRatio);
		XDest=(lWidth-nDestWidth)/2;
		YDest=0;
		nDestHeight=lHeight;
	}
	else
	{
		XDest=0;
		nDestWidth=lWidth;
		nDestHeight=(int)(lWidth*fImgRatio);
		YDest=(lHeight-nDestHeight)/2;
	}

	CClientDC cdc(pWnd);
	HDC hDC=::CreateCompatibleDC(cdc.m_hDC);
	HBITMAP bm = CreateCompatibleBitmap(cdc.m_hDC, lWidth, lHeight);
	HBITMAP pOldBitmapImage = (HBITMAP)SelectObject(hDC,bm);

	::FillRect(hDC, &rcBorder, hBrushBk);

	::FrameRect(hDC, &rcBorder, hBrushBorder);

	HBITMAP hBmReturn= (HBITMAP)::SelectObject(hDC, pOldBitmapImage);

	CDC hdcSrc, hdcDst;

	hdcSrc.CreateCompatibleDC(NULL);
	hdcDst.CreateCompatibleDC(NULL);

	CBitmap* hbmSrcT = (CBitmap*) hdcSrc.SelectObject(hPicRet);
	CBitmap* hbmDstT = (CBitmap*) hdcDst.SelectObject(hBmReturn);

	hdcDst.BitBlt(XDest,YDest,nDestWidth, nDestHeight, &hdcSrc,0,0,SRCCOPY); 

	pOldBitmapImage = (HBITMAP)SelectObject(hdcDst.m_hDC,bm);

	DeleteDC(hDC);
	DeleteObject(hBrushBorder);
	DeleteObject(hBrushBk);

	return pOldBitmapImage;

}*/

static const DWORD SIZE_comminute = 20000;//20000字节
static const DWORD SIZE_bufhead = 48;

BOOL CCommon::WriteStructInfo(LPCTSTR lpszSection, LPCTSTR lpszKey, char* lpStruct, UINT uSizeStruct, LPCTSTR szFile )
{	
	BOOL bResult = FALSE;
	{
		CString str("");
		char* pNewBuf = new char[SIZE_comminute + SIZE_bufhead];
		
		bResult = TRUE;
		for (int ni = 0 ; ni*SIZE_comminute < uSizeStruct ; ni++)
		{
			ZeroMemory(pNewBuf, SIZE_comminute + SIZE_bufhead);
			DWORD dwNewBufSize = ((ni+1)*SIZE_comminute > uSizeStruct)?(uSizeStruct-ni*SIZE_comminute):SIZE_comminute;
			
			//数据头赋值
			*(DWORD*)pNewBuf = uSizeStruct;
			*(DWORD*)(pNewBuf+SIZE_bufhead-4) = dwNewBufSize;
			*(DWORD*)(pNewBuf+SIZE_bufhead-8) = ni;

			//数据拷贝
			memcpy(pNewBuf+SIZE_bufhead, lpStruct + (ni*SIZE_comminute), dwNewBufSize);

			str.Format("%s_%02d", lpszKey, ni);
			bResult &= WritePrivateProfileStruct(lpszSection,  str,  pNewBuf,  SIZE_comminute + SIZE_bufhead,  szFile);
			if (!bResult)
			{
				break;
			}
		}

		_DEL_ARRAY_(pNewBuf);
	}	
	
	TRACE("WriteStructInfo:%d\n\r",uSizeStruct);
	bResult = TRUE;

	return bResult;
}
	
BOOL CCommon::ReadStructInfo(LPCTSTR lpszSection, LPCTSTR lpszKey, char* lpStruct, UINT uSizeStruct, LPCTSTR szFile )
{	
	BOOL bResult = FALSE;	

	{
		CString str(lpszKey);
		char* pNewBuf = new char[SIZE_comminute + SIZE_bufhead];

		bResult = TRUE;
		for (int ni = 0 ; ni*SIZE_comminute < uSizeStruct ; ni++)
		{
			ZeroMemory(pNewBuf, SIZE_comminute + SIZE_bufhead);
			str.Format("%s_%02d", lpszKey, ni);
			bResult &= GetPrivateProfileStruct(lpszSection,  str,  pNewBuf,  SIZE_comminute + SIZE_bufhead,  szFile);
			if (!bResult)
			{
				break;
			}

			if (0 == ni && *(DWORD*)pNewBuf != uSizeStruct)//总数据长度和外面请求的不一样
			{
				bResult = FALSE;
				break;
			}

			if (*(DWORD*)(pNewBuf+SIZE_bufhead-8) != ni)//数据包乱序
			{
				bResult = FALSE;
				break;
			}

			DWORD dwNewBufSize = *(DWORD*)(pNewBuf+SIZE_bufhead-4);
			if (dwNewBufSize > SIZE_comminute)//数据异常导致 长度异常
			{
				bResult = FALSE;
				break;
			}
		
			memcpy(lpStruct + (ni*SIZE_comminute), pNewBuf+SIZE_bufhead, dwNewBufSize);
		}

		_DEL_ARRAY_(pNewBuf);
	}

	return bResult;
}

int CCommon::log2i(unsigned long x)
{
	int r = 31;
	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) 
	{
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) 
	{
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) 
	{
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) 
	{
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) 
	{
		x <<= 1;
		r -= 1;
	}
	return r;
}

int CCommon::GetStrUTF8LengthFromGBK(char *pStrGBKData)
{
	int nlen = strlen(pStrGBKData);
	int nDestStrLen = nlen*2;
	
	if(0 == nlen)
	{
		return 0;
	}
	
	char* pUnicodeBuf = new char[nDestStrLen];
	memset(pUnicodeBuf, 0, nDestStrLen); //转换缓存尽量开大
	
	char* pUTF8 = new char[nDestStrLen];
	memset(pUTF8, 0, nDestStrLen); //最终得到的UTF8编码, 同样也搞大点
	
	//将配置页面上的GBK格式先统一转为windows内部标准格式WideChar
	int nNum = MultiByteToWideChar(CP_ACP, 0, (char*)pStrGBKData, nlen, (LPWSTR)pUnicodeBuf, nDestStrLen);
	
	//然后将标准格式的WideChar统一转为UTF8编码
	nNum = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)pUnicodeBuf, nNum, pUTF8, nDestStrLen, NULL, NULL);
	
	int nUTF8Len = strlen(pUTF8);
	
	delete [] pUnicodeBuf;
	delete [] pUTF8;
	
	return nUTF8Len; //将最终得到UTF8编码的长度返回

}

BOOL CCommon::CheckAllNum(CWnd* pWnd)
{
	if (NULL == pWnd)
	{
		return FALSE;
	}
	
	BOOL bAllNum = FALSE;
	
	CEdit *pEdit = (CEdit*)pWnd;
	
	CString sRecLen("");
	pEdit->GetWindowText(sRecLen);
	int nCount = 0;
	
	int nNum = sRecLen.GetLength();
	if ( nNum > 0 )
	{
		for (int ni = 0 ; ni < nNum ; ni++)
		{		
			if (sRecLen.GetAt(ni) >  '0' && sRecLen.GetAt(ni) < '9' ||  sRecLen.GetAt(ni) == '9' || sRecLen.GetAt(ni) == '0')
			{
				nCount++;
				
				if (nCount == nNum)
				{
					bAllNum = TRUE;
				}			
				// 				
				// 				char data = sRecLen.GetAt(ni);
				// 				if ( data < 0)
				// 				{
				// 					sRecLen.Delete(ni,2);
				// 					nNum -= 2;
				// 				}
				// 				else
				// 				{
				// 					sRecLen.Delete(ni,1);
				// 					nNum -= 1;
				// 				}
				
				/*				ni --;*/
			}
		}				
	}
	return bAllNum;
}

BOOL CCommon::CheckAllChr(CWnd* pWnd)
{
	if (NULL == pWnd)
	{
		return FALSE;
	}
	
	BOOL bAllChr = FALSE;
	
	CEdit *pEdit = (CEdit*)pWnd;
	
	CString sRecLen("");
	pEdit->GetWindowText(sRecLen);
	sRecLen.MakeLower();
	int nCount = 0;
	
	int nNum = sRecLen.GetLength();
	if ( nNum > 0 )
	{
		for (int ni = 0 ; ni < nNum ; ni++)
		{		
			if (sRecLen.GetAt(ni) > 'a' && sRecLen.GetAt(ni) < 'z' || sRecLen.GetAt(ni) == 'a' || sRecLen.GetAt(ni) == 'z')
			{
				nCount++;
				
				if (nCount == nNum)
				{
					bAllChr = TRUE;
				}			
				// 				
				// 				char data = sRecLen.GetAt(ni);
				// 				if ( data < 0)
				// 				{
				// 					sRecLen.Delete(ni,2);
				// 					nNum -= 2;
				// 				}
				// 				else
				// 				{
				// 					sRecLen.Delete(ni,1);
				// 					nNum -= 1;
				// 				}
				
				/*				ni --;*/
			}
		}				
	}
	return bAllChr;
	
	
}

BOOL CCommon::ReadResolution(LPRESOLUTION lpszResolution, int nResoStructSize, VIDEO_STANDARD emVideoStandard, BOOL bSort)
{
	BOOL bRet = FALSE;

	if (NULL == lpszResolution || nResoStructSize != sizeof(RESOLUTION) * CAPTURE_SIZE_NR)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	RESOLUTION stPALSlu[CAPTURE_SIZE_NR] = 
	{
		//PAL
		CAPTURE_SIZE_D1,	704,	576,	"D1" ,
		CAPTURE_SIZE_HD1,	352,	576,	"HD1",
		CAPTURE_SIZE_BCIF,	704,	288,	"BCIF",
		CAPTURE_SIZE_CIF,	352,	288,	"CIF",
		CAPTURE_SIZE_QCIF,	176,	144,	"QCIF",
		CAPTURE_SIZE_VGA,	640,	480,	"VGA", 
		CAPTURE_SIZE_QVGA,	320,	240,	"QVGA",
		CAPTURE_SIZE_SVCD,	480,	480,	"SVCD",
		CAPTURE_SIZE_QQVGA,	160,	128,	"QQVGA",
		CAPTURE_SIZE_SVGA,	800,	592,	"SVGA",
		CAPTURE_SIZE_XVGA,	1024,	768,	"XVGA",
		CAPTURE_SIZE_WXGA,	1280,	800,	"WXGA",
		CAPTURE_SIZE_SXGA,	1280,	1024,	"SXGA",
		CAPTURE_SIZE_WSXGA,	1600,	1024,	"WSXGA",
		CAPTURE_SIZE_UXGA,	1600,	1200,	"UXGA",
		CAPTURE_SIZE_WUXGA,	1900,	1200,	"WUXGA",
		CAPTURE_SIZE_LTF,	240,	192,	"LTF",
		CAPTURE_SIZE_720,	1280,	720,	"720P",
		CAPTURE_SIZE_1080,	1920,	1080,	"1080P",
		CAPTURE_SIZE_1_3M,	1280,	960,	"1.3M",
		CAPTURE_SIZE_2M,	1872,	1408,	"2M",
		CAPTURE_SIZE_5M,	3744,	1408,	"5M",
		CAPTURE_SIZE_3M,	2048,	1536,	"3M",
		CAPTURE_SIZE_5_0M,	2432,	2050,	"2432x2050",
		CPTRUTE_SIZE_1_2M,	1216,	1024,	"1216x1024",
		CPTRUTE_SIZE_1408_1024,	1408,	1024,	"1408x1024",
		CPTRUTE_SIZE_8M,	3296,	2472,	"8M",
		CPTRUTE_SIZE_2560_1920,	2560,	1920,	"2560x1920",
		CAPTURE_SIZE_960H,	960,	576,	"960H",
		CAPTURE_SIZE_960_720,960,   720,    "960x720",
		CAPTURE_SIZE_NHD,    640,   360,    "NHD",
		CAPTURE_SIZE_QNHD,   320,   180,    "QNHD",
		CAPTURE_SIZE_QQNHD,  160,   90,     "QQNHD"
	};
	RESOLUTION stNTSCSlu[CAPTURE_SIZE_NR] = 
	{
		//NTSC
		CAPTURE_SIZE_D1,	704,	480,	"D1" ,
		CAPTURE_SIZE_HD1,	352,	480,	"HD1" ,
		CAPTURE_SIZE_BCIF,	704,	240,	"BCIF",
		CAPTURE_SIZE_CIF,	352,	240,	"CIF",
		CAPTURE_SIZE_QCIF,	176,	120,	"QCIF",
		CAPTURE_SIZE_VGA,	640,	480,	"VGA",
		CAPTURE_SIZE_QVGA,	320,	240,	"QVGA",
		CAPTURE_SIZE_SVCD,	480,	480,	"SVCD",
		CAPTURE_SIZE_QQVGA,	160,	128,	"QQVGA",
		CAPTURE_SIZE_SVGA,	800,	592,	"SVGA",
		CAPTURE_SIZE_XVGA,	1024,	768,	"XVGA",
		CAPTURE_SIZE_WXGA,	1280,	800,	"WXGA",
		CAPTURE_SIZE_SXGA,	1280,	1024,	"SXGA",
		CAPTURE_SIZE_WSXGA,	1600,	1024,	"WSXGA",
		CAPTURE_SIZE_UXGA,	1600,	1200,	"UXGA",
		CAPTURE_SIZE_WUXGA,	1900,	1200,	"WUXGA",
		CAPTURE_SIZE_LTF,	240,	192,	"LTF",
		CAPTURE_SIZE_720,	1280,	720,	"720P",
		CAPTURE_SIZE_1080,	1920,	1080,	"1080P",
		CAPTURE_SIZE_1_3M,	1280,	960,	"1.3M",
		CAPTURE_SIZE_2M,	1872,	1408,	"2M",
		CAPTURE_SIZE_5M,	3744,	1408,	"5M",
		CAPTURE_SIZE_3M,	2048,	1536,	"3M",
		CAPTURE_SIZE_5_0M,	2432,	2050,	"5_0M",
		CPTRUTE_SIZE_1_2M,	1216,	1024,	"1_2M",
		CPTRUTE_SIZE_1408_1024,	1408,	1024,	"1408_1024",
		CPTRUTE_SIZE_8M,	3296,	2472,	"8M",
		CPTRUTE_SIZE_2560_1920,	2560,	1920,	"2560_1920",
		CAPTURE_SIZE_960H,	960,	480,	"960H",
		CAPTURE_SIZE_960_720,960,   720,    "960x720",
		CAPTURE_SIZE_NHD,    640,   360,    "NHD",
		CAPTURE_SIZE_QNHD,   320,   180,    "QNHD",
		CAPTURE_SIZE_QQNHD,  160,   90,     "QQNHD"
	};

	if (bSort)
	{
		qsort( (void *)stPALSlu, (size_t)CAPTURE_SIZE_NR, sizeof(RESOLUTION), CCommon::compare );
		qsort( (void *)stNTSCSlu, (size_t)CAPTURE_SIZE_NR, sizeof(RESOLUTION), CCommon::compare );
	}

	switch (emVideoStandard)
	{
	case PAL:
		{
			memcpy(lpszResolution, &stPALSlu, sizeof(stPALSlu));
			bRet = TRUE;
		}
		
		break;
	case NTSC:
		{
			memcpy(lpszResolution, &stNTSCSlu, sizeof(stNTSCSlu));
			bRet = TRUE;
		}
		break;
	default:
		bRet = FALSE;
		break;
	}

	return bRet;
}

int CCommon::compare( const void *arg1, const void *arg2 )
{
	int iRet = 0;
	PRESOLUTION pSlu1 = (PRESOLUTION)arg1;
	PRESOLUTION pSlu2 = (PRESOLUTION)arg2;
	
	
	if(pSlu1->nWidth*pSlu1->nHeight < pSlu2->nWidth*pSlu2->nHeight)
	{
		iRet = 1;
	}
	else if(pSlu1->nWidth*pSlu1->nHeight > pSlu2->nWidth*pSlu2->nHeight)
	{
		iRet = -1;
	}
	else if(pSlu1->nWidth*pSlu1->nHeight == pSlu2->nWidth*pSlu2->nHeight)
	{
		if(pSlu1->nWidth > pSlu2->nWidth)
		{
			iRet = 1;
		}
		else
		{
			iRet = -1;
		}
	}
	
	return iRet;	
}