// Real Load Picture.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Real Load Picture.h"
#include "Real Load PictureDlg.h"
#include "Utility.h"

#include <math.h>
#include <atlconv.h>
#include <assert.h>

//#include <gdiplus.h>
//#pragma comment(lib, "gdiplus.lib")

//using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE

static char THIS_FILE[] = __FILE__;
#endif

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

const COLORREF RESERVED_COLOR = RGB(255, 255, 255);
const int   HIMETRIC_INCH = 2540;

// void RenderJPG(IPicture *pPicture, HWND hwnd)
// {
// 
// }

HBITMAP ExtractBitmap(IPicture *pPicture, int &nWidth, int &nHeight)
{
	DWORD dwError = 0;
	CDC* pDC = CWnd::GetDesktopWindow()->GetDC();
	
	long hmWidth;
	long hmHeight;
	pPicture->get_Width(&hmWidth);
	pPicture->get_Height(&hmHeight);
	
	nWidth = MulDiv(hmWidth, pDC->GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
	nHeight = MulDiv(hmHeight, pDC->GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH);
	
	CDC dcMem;
	BOOL bRet = dcMem.CreateCompatibleDC(pDC);
	if (!bRet)
	{
		dwError = ::GetLastError();
		char szMsg[512] = {0};
		sprintf(szMsg, "CreateCompatibleDC error in ExtractBitmap of code %d", dwError);
		return NULL;
	}
	HBITMAP  hBitmap=::CreateCompatibleBitmap(pDC->m_hDC,nWidth,nHeight); 
	if (hBitmap == NULL)
	{
		dwError = ::GetLastError();
		char szMsg[512] = {0};
		sprintf(szMsg, "CreateCompatibleBitmap error in ExtractBitmap of code %d", dwError);
		return NULL;
	}
	
	HBITMAP pOldBM = (HBITMAP)::SelectObject(dcMem.m_hDC, hBitmap);
	HRESULT hr = pPicture->Render(dcMem, 0, 0, nWidth, nHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);
	::SelectObject(dcMem.m_hDC, pOldBM);
	
	CWnd::GetDesktopWindow()->ReleaseDC(pDC);
	dcMem.DeleteDC();
	return hBitmap;
	
	
	
	// 	DWORD dwError = 0;
	// 	CDC* pDC = CWnd::GetDesktopWindow()->GetDC();
	// 
	// 	long hmWidth;
	// 	long hmHeight;
	// 	pPicture->get_Width(&hmWidth);
	// 	pPicture->get_Height(&hmHeight);
	// 	
	// 	nWidth = MulDiv(hmWidth, pDC->GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
	// 	nHeight = MulDiv(hmHeight, pDC->GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH);
	// 
	// 	CDC dcMem;
	// 	BOOL bRet = dcMem.CreateCompatibleDC(pDC);
	// 	if (!bRet)
	// 	{
	// 		dwError = ::GetLastError();
	// 		char szMsg[512] = {0};
	// 		sprintf(szMsg, "CreateCompatibleDC error in ExtractBitmap of code %d", dwError);
	// 		return NULL;
	// 	}
	// 	HBITMAP  hBitmap=::CreateCompatibleBitmap(pDC->m_hDC,nWidth,nHeight); 
	// 	if (hBitmap == NULL)
	// 	{
	// 		dwError = ::GetLastError();
	// 		char szMsg[512] = {0};
	// 		sprintf(szMsg, "CreateCompatibleBitmap error in ExtractBitmap of code %d", dwError);
	// 		return NULL;
	// 	}
	// 
	// 	HBITMAP pOldBM = (HBITMAP)::SelectObject(dcMem.m_hDC, hBitmap);
	// 	HRESULT hr = pPicture->Render(dcMem, 0, 0, nWidth, nHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);
	// 	::SelectObject(dcMem.m_hDC, pOldBM);
	// 
	// 	CWnd::GetDesktopWindow()->ReleaseDC(pDC);
	// 	dcMem.DeleteDC();
	// 	return hBitmap;
	
	
	/*
	ASSERT(pPicture);
	
	  if (!pPicture)
	  return NULL;
	  
		CBitmap bmMem;
		CDC dcMem;
		CDC* pDC = CWnd::GetDesktopWindow()->GetDC();
		
		  if (dcMem.CreateCompatibleDC(pDC))
		  {
		  long hmWidth;
		  long hmHeight;
		  
			pPicture->get_Width(&hmWidth);
			pPicture->get_Height(&hmHeight);
			
			  nWidth = MulDiv(hmWidth, pDC->GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
			  nHeight = MulDiv(hmHeight, pDC->GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH);
			  
				if (bmMem.CreateCompatibleBitmap(pDC, nWidth, nHeight))
				{
				CBitmap* pOldBM = dcMem.SelectObject(&bmMem);
				HRESULT hr = pPicture->Render(dcMem, 0, 0, nWidth, nHeight, 0, hmHeight, hmWidth, -hmHeight, NULL);
				dcMem.SelectObject(pOldBM);
				}
				else
				{
				DWORD dwError = ::GetLastError();
				int a = 0;
				a++;
				}
				}
				
				  CWnd::GetDesktopWindow()->ReleaseDC(pDC);
				  
					//xyg add
					//if(dcMem.m_hDC) ::DeleteDC(dcMem.Detach());
					//
					HBITMAP hBmp = (HBITMAP)bmMem.Detach();
					
					  return hBmp;
	*/
}


HBITMAP LoadImageFile(LPCSTR szImagePath, int &nWidth, int &nHeight)
{
	USES_CONVERSION;
	IPicture* pPicture = NULL;
	
	HBITMAP hbm = NULL;
	HRESULT hr = S_FALSE;
	try
	{
		hr = OleLoadPicturePath(T2OLE(szImagePath), NULL, 0, RESERVED_COLOR, IID_IPicture, (LPVOID*)&pPicture);
		//hr = OleLoadPicturePath(T2OLE("cc"), NULL, 0, RESERVED_COLOR, IID_IPicture, (LPVOID*)&pPicture);
	}
	catch (CMemoryException* e)
	{
		::MessageBox(NULL, ConvertString("Bad JPG file!"),ConvertString("Prompt"), 0);
		//return NULL;
	}
	catch (CFileException* e)
	{
		MessageBox(NULL, ConvertString("Bad JPG file!"),ConvertString("Prompt"), 0);
		//return NULL;
	}
	catch (CException* e)
	{
		MessageBox(NULL, ConvertString("Bad JPG file!"),ConvertString("Prompt"), 0);
		//return NULL;
	}
	
	//XYG ADD [BEGIN]
	//TEMP FOR TEST
	if ( (S_OK != hr) || (NULL == pPicture) )
	{
		char szMSG[128] = {0};
		sprintf(szMSG, "OleLoadPicturePath failed of hr = %ld",E_POINTER);
		MessageBox(NULL, szMSG,ConvertString("Prompt"), 0);
	}
	//XYG ADD [END]
	
	
	if (pPicture)
	{
		hbm = ExtractBitmap(pPicture,nWidth, nHeight);
		if (hbm == NULL)
		{
			MessageBox(NULL, ConvertString("ExtractBitmap failed"),ConvertString("Prompt"), 0);
		}
		pPicture->Release();
	}
	
	return hbm;
}

int RenderJPG(const char* szImagePath, HWND hwnd)
{
	USES_CONVERSION;
	IPicture* pPic = NULL;
	HRESULT hr = S_FALSE;
	
	CDC* pDC = CWnd::FromHandle(hwnd)->GetWindowDC();
	
	hr = OleLoadPicturePath(T2OLE(szImagePath), NULL, 0, RESERVED_COLOR, IID_IPicture, (LPVOID*)&pPic);
	if (FAILED(hr))
	{
		AfxMessageBox("OleLoadPicturePath装载图像失败!");
		return -1;
	}
	
	OLE_XSIZE_HIMETRIC hmWidth; 
	OLE_YSIZE_HIMETRIC hmHeight; 
	pPic->get_Width(&hmWidth); 
	pPic->get_Height(&hmHeight); 
	double fX,fY; 
	fX = (double)pDC->GetDeviceCaps(HORZRES)*(double)hmWidth/((double)pDC->GetDeviceCaps(HORZSIZE)*100.0); 
	fY = (double)pDC->GetDeviceCaps(VERTRES)*(double)hmHeight/((double)pDC->GetDeviceCaps(VERTSIZE)*100.0); 
	//if(FAILED(pPic->Render(*pDC,0,0,(DWORD)fX,(DWORD)fY,0,hmHeight,hmWidth,-hmHeight,NULL))) 
	
	RECT rect;
	CWnd::FromHandle(hwnd)->GetWindowRect(&rect);
	hr = pPic->Render(*pDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0, hmHeight, hmWidth, -hmHeight, NULL);
	if (FAILED(hr))
	{
		AfxMessageBox("渲染图像失败!"); 
	}
	pPic->Release(); 
	::ReleaseDC(hwnd, pDC->m_hDC);
	
	return 0;
}


BOOL IsPicOfRecordExist(char* szGUID)
{
	std::string strFolder = GetDataFolder();
	std::string strJpgPath = strFolder + std::string(szGUID) + std::string(".jpg");
	HANDLE hFile=CreateFile(strJpgPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	else
	{
		::CloseHandle(hFile);
		return TRUE;
	}
	
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
CString ConvertString(CString strText)
{
	char *val = new char[200];
	CString strIniPath,strRet;
	
	memset(val,0,200);
	GetPrivateProfileString("String",strText,"",
		val,200,"./langchn.ini");
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//If there is no corresponding string in ini file then set it to be deafault value(English).
		strRet=strText;
	}
	delete[] val;
	return strRet;
}

//Set static text for dialogue box(English->current language)
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;
	
	//Set main window title 
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}
	
	//Set small window title
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//The next small window 
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//Set current language text for small window. 
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);
		
		//Next small window 
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}




BOOL TryDisplayLP(const DWORD dwAlarmType, const void* pAlarmInfo, CWnd* window)
{
	switch(dwAlarmType)
	{
		//下列的三种情况，前面部分采用相同的结构，可以统一处理
	case EVENT_IVS_TRAFFICGATE:
	case EVENT_IVS_TRAFFICJUNCTION:
	case EVENT_IVS_TRAFFICCONTROL:
		{
			DEV_EVENT_TRAFFICGATE_INFO* pCMInfo = (DEV_EVENT_TRAFFICGATE_INFO*)pAlarmInfo;
			std::string strLP = MakeLP(pCMInfo->stuObject.szText);
			window->SetWindowText(strLP.c_str());
		}
		break;
	default:
		break;
	}
	
	return TRUE;
}

BOOL IsTypeHasLP(DWORD dwAlarmType)
{
	switch(dwAlarmType)
	{
	case EVENT_IVS_TRAFFICGATE:
	case EVENT_IVS_TRAFFICJUNCTION:
	case EVENT_IVS_TRAFFICCONTROL:
		return TRUE;
		
	default:
		return FALSE;
	}
}

BOOL TryDisplayImageAndLPPart(const char* szJPGPath, const ALARM_ITEM* item, CWnd* fullImageWindow, CWnd* lpImageWindow)
{
	CDC* pLPDC = lpImageWindow->GetWindowDC();
	CDC* pDC = fullImageWindow->GetWindowDC();
	CDC* pSrcDC = CWnd::GetDesktopWindow()->GetDC();
	{
		CWnd* window = fullImageWindow;
		CDC* cdc = window->GetDC();
		RECT rect;
		window->GetClientRect(&rect);
		CBrush brush(RGB(100,100,160));
		cdc->FillRect(&rect, &brush);
		fullImageWindow->ReleaseDC(cdc);
	}
	{
		CWnd* window = lpImageWindow;
		CDC* cdc = window->GetDC();
		RECT rect;
		window->GetClientRect(&rect);
		CBrush brush(RGB(100,100,160));
		cdc->FillRect(&rect, &brush);
		fullImageWindow->ReleaseDC(cdc);
	}
	
	USES_CONVERSION;
	IPicture* pPic = NULL;
	HRESULT hr = S_FALSE;
	BOOL bRet = FALSE;
	//装载图片
	hr = OleLoadPicturePath(T2OLE(szJPGPath), NULL, 0, RESERVED_COLOR, IID_IPicture, (LPVOID*)&pPic);
	if (FAILED(hr))
	{
		OutputDebugString("OleLoadPicturePath装载图像失败!");
	}
	if (pPic == NULL)
	{
		goto CLEAN;
	}
	//显示全图
	OLE_XSIZE_HIMETRIC hmWidth; 
	OLE_YSIZE_HIMETRIC hmHeight; 
	pPic->get_Width(&hmWidth); 
	pPic->get_Height(&hmHeight); 
	RECT rect;
	fullImageWindow->GetWindowRect(&rect);
	hr = pPic->Render(*pDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0, hmHeight, hmWidth, -hmHeight, NULL);
	if (FAILED(hr))
	{
		OutputDebugString("渲染全图失败!"); 
	}
	
	//显示车牌图
	if (IsTypeHasLP(item->nAlarmType))//判断事件内容是否包含车牌
	{
		DEV_EVENT_TRAFFICGATE_INFO* pCMInfo = (DEV_EVENT_TRAFFICGATE_INFO*)(item->pAlarmInfo);
		if (strcmp(pCMInfo->stuObject.szText, "") == 0)
		{
			//无车牌，直接返回
			goto CLEAN;
		}
		
		
		
		DEV_EVENT_TRAFFICGATE_INFO* trafficGate = (DEV_EVENT_TRAFFICGATE_INFO*)(item->pAlarmInfo);
		DH_RECT* dRect = &(trafficGate->stuObject.BoundingBox);
		//1.BoundingBox的值是在8192*8192坐标系下的值，必须转化为图片中的坐标
		//2.OSD在图片中占了64行,如果没有OSD，下面的关于OSD的处理需要去掉(把OSD_HEIGHT置为0)
		const int OSD_HEIGHT = 64;
		long nWidth;
		long nHeight;
		nWidth =  MulDiv(hmWidth, pSrcDC->GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
		nHeight = MulDiv(hmHeight, pSrcDC->GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH);
		nHeight = nHeight - OSD_HEIGHT;
		if ( (nWidth <= 0) || (nHeight <=0) )
		{
			goto CLEAN;
			return false;
		}
		DH_RECT dstRect = {0};
		
		dstRect.left	= ceil((double)(nWidth  * dRect->left)   / 8192);
		dstRect.right	= ceil((double)(nWidth  * dRect->right)  / 8192);
		dstRect.bottom	= ceil((double)(nHeight * dRect->bottom) / 8192);
		dstRect.top		= ceil((double)(nHeight * dRect->top)    / 8192);
		
		double rate = (double)hmWidth / (double)nWidth;
		int x = (double)dstRect.left * rate;
		int y = (double)(dstRect.top + OSD_HEIGHT) * rate;
		int w = (double)(dstRect.right - dstRect.left) * rate;
		int h = (double)(dstRect.bottom - dstRect.top) * rate;
		
		lpImageWindow->GetWindowRect(&rect);
		hr = pPic->Render(*pLPDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 
			x, 
			hmHeight - y, 
			w, 
			0-h, 	
			NULL);
		
		if (FAILED(hr))
		{
			OutputDebugString("渲染车牌失败!"); 
		}
	}
	
	
CLEAN:
	if (pPic != NULL)
	{
		pPic->Release(); 
	}
	fullImageWindow->ReleaseDC(pDC);
	lpImageWindow->ReleaseDC(pLPDC);
	CWnd::GetDesktopWindow()->ReleaseDC(pSrcDC);
	return 0;
}


// BOOL TryDisplayLPPic(const char* szImagePath, const ALARM_ITEM* item, CWnd* window)
// {
// 	RenderJPG(szImagePath, window->GetSafeHwnd());
// 	return TRUE;
// 	//尝试显示图片
// 	if (item == NULL)
// 	{
// 		return FALSE;
// 	}
// 	if (IsTypeHasLP(item->nAlarmType))
// 	{
// 		CDC* m_MemDC = NULL;
// 		HBITMAP m_hBitmap = NULL;
// 		CClientDC* m_ClientDC = NULL; 
// 		RECT m_rect = {0};
// 		int m_nWidth = 0;
// 		int m_nHeight = 0;
// 
// 		BITMAP BM; 
// 		if (m_MemDC == NULL)
// 		{
// 			m_MemDC = new CDC;
// 			if (m_ClientDC == NULL)
// 			{
// 				m_ClientDC = new CClientDC(window);
// 			}
// 			window->GetClientRect(&m_rect);
// 			m_MemDC->CreateCompatibleDC(m_ClientDC); 
// 		}
// 		if (m_hBitmap != NULL)
// 		{
// 			::DeleteObject(m_hBitmap);
// 		}
// 		m_hBitmap = LoadImageFile(szImagePath, m_nWidth, m_nHeight);
// 		
// 		if(m_hBitmap != NULL)
// 		{
// 			m_MemDC->SelectObject(m_hBitmap);
// 			::GetObject(m_hBitmap,sizeof(BM),&BM);
// 
// 			DEV_EVENT_TRAFFICGATE_INFO* trafficGate = (DEV_EVENT_TRAFFICGATE_INFO*)(item->pAlarmInfo);
// 			DH_RECT* dRect = &(trafficGate->stuObject.BoundingBox);
// 			//1.BoundingBox的值是在8192*8192坐标系下的值，必须转化为图片中的坐标
// 			//2.OSD在图片中占了64行,如果没有OSD，下面的关于OSD的处理需要去掉(把OSD_HEIGHT置为0)
// 			const int OSD_HEIGHT = 64;
// 			int nWidth = m_nWidth;
// 			int nHeight = m_nHeight - OSD_HEIGHT;
// 			if ( (nWidth <= 0) || (nHeight <=0) )
// 			{
// 				return false;
// 			}
// 			DH_RECT dstRect = {0};
// 			dstRect.left	= ceil((double)(nWidth  * dRect->left)   / 8192);
// 			dstRect.right	= ceil((double)(nWidth  * dRect->right)  / 8192);
// 			dstRect.bottom	= ceil((double)(nHeight * dRect->bottom) / 8192);
// 			dstRect.top		= ceil((double)(nHeight * dRect->top)    / 8192);
// 			
// 			CClientDC* pClientDC = new CClientDC(window);
// 			pClientDC->SetStretchBltMode(STRETCH_HALFTONE);
// 			RECT rect = {0};
// 			window->GetWindowRect(&rect);
// 			pClientDC->StretchBlt(0,0, rect.right - rect.left, rect.bottom - rect.top,
// 				m_MemDC,
// 				dstRect.left, dstRect.top + OSD_HEIGHT, dstRect.right - dstRect.left, dstRect.bottom - dstRect.top,
// 				SRCCOPY);
// 			delete pClientDC;
// 		}
// 		
// 		if (m_MemDC != NULL)
// 		{
// 			delete m_MemDC;
// 		}
// 
// 		if (m_hBitmap != NULL)
// 		{
// 			::DeleteObject(m_hBitmap);
// 		}
// 		
// 		if (m_ClientDC != NULL)
// 		{
// 			delete m_ClientDC;
// 		}
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
// 	return FALSE;
// }


std::string GetDataFolder()
{
	std::string strCfgFilePath;
	std::string strCfgDefaultFolder;
	GetModulePath("dhnetsdk.dll", strCfgFilePath);
	strCfgDefaultFolder = strCfgFilePath;
	strCfgFilePath.append(CFG_CFG_FILE_NAME);
	strCfgDefaultFolder.append(PC_DATA_STORE_FOLDER);
	char szFolder[1024] = {0};
	::GetPrivateProfileString(CFG_SECTION_CFG, CFG_KEY_DATA_PATH, strCfgDefaultFolder.c_str(), szFolder, 1024, strCfgFilePath.c_str());
	return std::string(szFolder);
}


/////////////////////////////////////////////////////////////////////////////
// CRealLoadPictureApp

BEGIN_MESSAGE_MAP(CRealLoadPictureApp, CWinApp)
//{{AFX_MSG_MAP(CRealLoadPictureApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealLoadPictureApp construction

CRealLoadPictureApp::CRealLoadPictureApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRealLoadPictureApp object

CRealLoadPictureApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRealLoadPictureApp initialization

BOOL CRealLoadPictureApp::InitInstance()
{
	AfxEnableControlContainer();
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	//Startup of GDI plus
	//GdiplusStartupInput gdiplusStartupInput;
	//ULONG_PTR gdiplusToken;
	//GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	
	CRealLoadPictureDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void GetVehicleInfo(int  nGetWhat, DH_MSG_OBJECT *pObject, std::vector<ColDes>* vTitles, std::vector<std::string>* vContent)
{
	if (nGetWhat & GET_SI_TITLE)
	{
		
		vTitles->push_back(ColDesObj("Vehicle ID", 80));
		vTitles->push_back(ColDesObj("Vehicle Type", 80));
		vTitles->push_back(ColDesObj("Vehicle SubType", 80));
		vTitles->push_back(ColDesObj("Vehicle Confidence", 120));
		vTitles->push_back(ColDesObj("Vehicle Action", 100));
		vTitles->push_back(ColDesObj("Vehicle BoundingBox", 200));
		vTitles->push_back(ColDesObj("Vehicle Center", 120));
		vTitles->push_back(ColDesObj("Vehicle Polygon Point Count", 180));
		vTitles->push_back(ColDesObj("Vehicle Contour", 100));
		vTitles->push_back(ColDesObj("Vehicle Color", 120));
		vTitles->push_back(ColDesObj("Vehicle Text", 120));
		vTitles->push_back(ColDesObj("Vehicle ShotFrame", 120));
	}
	if (nGetWhat & GET_SI_CONTENT && pObject != NULL)
	{
		vContent->push_back(I2Str(pObject->nObjectID));
		vContent->push_back(std::string(pObject->szObjectType));
		vContent->push_back(std::string(pObject->szObjectSubType));
		vContent->push_back(I2Str(pObject->nConfidence));
		vContent->push_back(MakeActionStr(pObject->nAction));
		vContent->push_back(MakeRect(pObject->BoundingBox));
		vContent->push_back(MakePointer(pObject->Center));
		vContent->push_back(I2Str(pObject->nPolygonNum));
		vContent->push_back(MakePointers(pObject->Contour, pObject->nPolygonNum));
		vContent->push_back(MakeColorStr(pObject->rgbaMainColor));
		vContent->push_back(std::string(pObject->szText));
		vContent->push_back(I2Str(pObject->bShotFrame));
	}
}

void GetPlateInfo(int  nGetWhat, DH_MSG_OBJECT *pObject, std::vector<ColDes>* vTitles, std::vector<std::string>* vContent)
{
	if (nGetWhat & GET_SI_TITLE)
	{
		vTitles->push_back(ColDesObj("Plate ID", 80));
		vTitles->push_back(ColDesObj("Plate Type", 80));
		vTitles->push_back(ColDesObj("Plate Confidence", 120));
		vTitles->push_back(ColDesObj("Plate Action", 100));
		vTitles->push_back(ColDesObj("Plate BoundingBox", 200));
		vTitles->push_back(ColDesObj("Plate Center", 120));
		vTitles->push_back(ColDesObj("Plate Polygon Point Count", 180));
		vTitles->push_back(ColDesObj("Plate Contour", 100));
		vTitles->push_back(ColDesObj("Plate Color", 120));
		vTitles->push_back(ColDesObj("Plate Text", 120));
	}
	if (nGetWhat & GET_SI_CONTENT && pObject != NULL)
	{
		vContent->push_back(I2Str(pObject->nObjectID));
		vContent->push_back(std::string(pObject->szObjectType));
		vContent->push_back(I2Str(pObject->nConfidence));
		vContent->push_back(MakeActionStr(pObject->nAction));
		vContent->push_back(MakeRect(pObject->BoundingBox));
		vContent->push_back(MakePointer(pObject->Center));
		vContent->push_back(I2Str(pObject->nPolygonNum));
		vContent->push_back(MakePointers(pObject->Contour, pObject->nPolygonNum));
		vContent->push_back(MakeColorStr(pObject->rgbaMainColor));
		vContent->push_back(std::string(pObject->szText));
	}
}
void GettrafficCarInfo(int  nGetWhat, DEV_EVENT_TRAFFIC_TRAFFICCAR_INFO *pTrafficCar, std::vector<ColDes>* vTitles, std::vector<std::string>* vContent)
{
	if (nGetWhat & GET_SI_TITLE)
	{
		vTitles->push_back(ColDesObj("trafficCar szPlateNumber", 120));
		vTitles->push_back(ColDesObj("trafficCar szPlateType", 120));
		vTitles->push_back(ColDesObj("trafficCar szPlateColor", 120));
		vTitles->push_back(ColDesObj("trafficCar szVehicleColor", 120));
		vTitles->push_back(ColDesObj("trafficCar nSpeed", 120));
		vTitles->push_back(ColDesObj("trafficCar szEvent", 120));
		vTitles->push_back(ColDesObj("trafficCar szViolationCode", 120));
		vTitles->push_back(ColDesObj("trafficCar szViolationDesc", 120));
		vTitles->push_back(ColDesObj("trafficCar nLowerSpeedLimit", 120));
		vTitles->push_back(ColDesObj("trafficCar nUpperSpeedLimit", 120));
		vTitles->push_back(ColDesObj("trafficCar nOverSpeedMargin", 120));
		vTitles->push_back(ColDesObj("trafficCar nUnderSpeedMargin", 120));
		vTitles->push_back(ColDesObj("trafficCar nLane", 120));
		vTitles->push_back(ColDesObj("trafficCar nVehicleSize", 120));
		vTitles->push_back(ColDesObj("trafficCar fVehicleLength", 120));
		vTitles->push_back(ColDesObj("trafficCar nSnapshotMode", 120));
		vTitles->push_back(ColDesObj("trafficCar szChannelName", 120));
		vTitles->push_back(ColDesObj("trafficCar szMachineName", 120));
		vTitles->push_back(ColDesObj("trafficCar szMachineGroup", 120));
		vTitles->push_back(ColDesObj("trafficCar szRoadwayNo", 120));
		vTitles->push_back(ColDesObj("trafficCar szDrivingDirection", 120));
	}
	if (nGetWhat & GET_SI_CONTENT && pTrafficCar != NULL)
	{
		vContent->push_back(std::string(pTrafficCar->szPlateNumber));
		vContent->push_back(std::string(pTrafficCar->szPlateType));
		vContent->push_back(std::string(pTrafficCar->szPlateColor));
		vContent->push_back(std::string(pTrafficCar->szVehicleColor));
		vContent->push_back(I2Str(pTrafficCar->nSpeed));
		vContent->push_back(std::string(pTrafficCar->szEvent));
		vContent->push_back(std::string(pTrafficCar->szViolationCode));
		vContent->push_back(std::string(pTrafficCar->szViolationDesc));
		vContent->push_back(I2Str(pTrafficCar->nLowerSpeedLimit));
		vContent->push_back(I2Str(pTrafficCar->nUpperSpeedLimit));
		vContent->push_back(I2Str(pTrafficCar->nOverSpeedMargin));
		vContent->push_back(I2Str(pTrafficCar->nUnderSpeedMargin));
		vContent->push_back(I2Str(pTrafficCar->nLane));
		vContent->push_back(I2Str(pTrafficCar->nVehicleSize));
		vContent->push_back(D2Str(pTrafficCar->fVehicleLength));
		vContent->push_back(I2Str(pTrafficCar->nSnapshotMode));
		vContent->push_back(std::string(pTrafficCar->szChannelName));
		vContent->push_back(std::string(pTrafficCar->szMachineName));
		vContent->push_back(std::string(pTrafficCar->szMachineGroup));
		vContent->push_back(std::string(pTrafficCar->szRoadwayNo));
		{
			std::string str;
			for (int i=0;i<3;i++)
			{
				str.append(pTrafficCar->szDrivingDirection[i]);
			}
			vContent->push_back(str);
		}
	}
}
BOOL GetStructInfo(int nAlarmType,
				   void* pAlarmInfo,
				   int  nGetWhat,
				   int* nStructSize,
				   DH_EVENT_FILE_INFO* pFileInfo,
				   std::vector<ColDes>* vTitles, 
				   std::vector<std::string>* vContent)
				   
{
	using namespace std;
	
	//It only support traffic event now
	switch(nAlarmType)
	{
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
	case EVENT_IVS_TRAFFICCONTROL:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFICCONTROL_INFO);
			}
			
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Content", 70));
				vTitles->push_back(ColDesObj("Color", 120));
			}
			
			DEV_EVENT_TRAFFICCONTROL_INFO* pInfo = (DEV_EVENT_TRAFFICCONTROL_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(string(pInfo->stuObject.szText));
				vContent->push_back(MakeColorStr(pInfo->stuObject.rgbaMainColor));
				
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
			
		}
		break;
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
	case EVENT_IVS_TRAFFICACCIDENT:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFICACCIDENT_INFO);
			}
			
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Objects", 100));
				
				//PRIVATE_MSG_OBJECT
				vTitles->push_back(ColDesObj("Object ID", 80));
				vTitles->push_back(ColDesObj("Object Type", 80));
				vTitles->push_back(ColDesObj("Object Confidence", 120));
				vTitles->push_back(ColDesObj("Object Action", 100));
				vTitles->push_back(ColDesObj("Object BoundingBox", 200));
				vTitles->push_back(ColDesObj("Object Center", 120));
				vTitles->push_back(ColDesObj("Object Polygon Point Count", 180));
				vTitles->push_back(ColDesObj("Object Contour", 100));
				vTitles->push_back(ColDesObj("Object Color", 120));
				vTitles->push_back(ColDesObj("Object Text", 120));
				
			}
			
			DEV_EVENT_TRAFFICACCIDENT_INFO* pInfo = (DEV_EVENT_TRAFFICACCIDENT_INFO*)pAlarmInfo;
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				//一个报警，多条记录
				for (int i = 0; i < pInfo->nObjectNum; i ++)
				{
					//报警信息
					vContent->push_back(I2Str(pInfo->nChannelID + 1));
					vContent->push_back(string(pInfo->szName));
					vContent->push_back(D2Str(pInfo->PTS));
					vContent->push_back(NetTimeEx2Str(pInfo->UTC));
					vContent->push_back(I2Str(pInfo->nEventID));
					vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
					vContent->push_back(I2Str(pInfo->nObjectNum));
					
					//PRIVATE_MSG_OBJECT
					vContent->push_back(I2Str(pInfo->stuObjectIDs[i].nObjectID));
					vContent->push_back(string(pInfo->stuObjectIDs[i].szObjectType));
					vContent->push_back(I2Str(pInfo->stuObjectIDs[i].nConfidence));
					vContent->push_back(MakeActionStr(pInfo->stuObjectIDs[i].nAction));
					vContent->push_back(MakeRect(pInfo->stuObjectIDs[i].BoundingBox));
					vContent->push_back(MakePointer(pInfo->stuObjectIDs[i].Center));
					vContent->push_back(I2Str(pInfo->stuObjectIDs[i].nPolygonNum));
					vContent->push_back(MakePointers(pInfo->stuObjectIDs[i].Contour, pInfo->stuObjectIDs[i].nPolygonNum));
					vContent->push_back(MakeColorStr(pInfo->stuObjectIDs[i].rgbaMainColor));
					vContent->push_back(MakeLP(pInfo->stuObjectIDs[i].szText));
					
					
				}
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
	case EVENT_IVS_TRAFFICJUNCTION:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFICJUNCTION_INFO);
			}
			
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				vTitles->push_back(ColDesObj("BreakingRule",100));
				vTitles->push_back(ColDesObj("RedLightUTC", 140));
				
				//PRIVATE_MSG_OBJECT
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			
			DEV_EVENT_TRAFFICJUNCTION_INFO* pInfo = (DEV_EVENT_TRAFFICJUNCTION_INFO*)pAlarmInfo;
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				vContent->push_back(BR2StrForTrafficJunction(pInfo->dwBreakingRule));
				vContent->push_back(NetTimeEx2Str(pInfo->RedLightUTC));
				
				//PRIVATE_MSG_OBJECT
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);

				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
			return	TRUE;
		}
		break;
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
	case EVENT_IVS_TRAFFICGATE:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFICGATE_INFO);
			}
			
			DEV_EVENT_TRAFFICGATE_INFO* pInfo = (DEV_EVENT_TRAFFICGATE_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				vTitles->push_back(ColDesObj("Speed", 50));
				vTitles->push_back(ColDesObj("SpeedUpperLimit", 120));
				vTitles->push_back(ColDesObj("SpeedLowerLimit", 120));
				vTitles->push_back(ColDesObj("BreakingRule", 130));
				vTitles->push_back(ColDesObj("485information", 80));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);				
				
				// Vehicle
				vTitles->push_back(ColDesObj("Vehicle ID", 80));
				vTitles->push_back(ColDesObj("Vehicle Type", 80));
				vTitles->push_back(ColDesObj("Vehicle SubType", 80));
				vTitles->push_back(ColDesObj("Vehicle Confidence", 120));
				vTitles->push_back(ColDesObj("Vehicle Action", 100));
				vTitles->push_back(ColDesObj("Vehicle BoundingBox", 200));
				vTitles->push_back(ColDesObj("Vehicle Center", 120));
				vTitles->push_back(ColDesObj("Vehicle Polygon Point Count", 180));
				vTitles->push_back(ColDesObj("Vehicle Contour", 100));
				vTitles->push_back(ColDesObj("Vehicle Color", 120));
				vTitles->push_back(ColDesObj("Vehicle Text", 120));
				vTitles->push_back(ColDesObj("Vehicle ShotFrame", 120));
				
				vTitles->push_back(ColDesObj("FilePath",200));
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				vContent->push_back(I2Str(pInfo->nSpeed));
				vContent->push_back(I2Str(pInfo->nSpeedUpperLimit));
				vContent->push_back(I2Str(pInfo->nSpeedLowerLimit));
				vContent->push_back(BR2StrForTrafficGate(pInfo->dwBreakingRule));
				vContent->push_back(Hex2Str(pInfo->stuSigInfo.byRedundance,sizeof(pInfo->stuSigInfo.byRedundance)));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				vContent->push_back(I2Str(pInfo->stuVehicle.nObjectID));
				vContent->push_back(string(pInfo->stuVehicle.szObjectType));
				vContent->push_back(string(pInfo->szVehicleType));
				vContent->push_back(I2Str(pInfo->stuVehicle.nConfidence));
				vContent->push_back(MakeActionStr(pInfo->stuVehicle.nAction));
				vContent->push_back(MakeRect(pInfo->stuVehicle.BoundingBox));
				vContent->push_back(MakePointer(pInfo->stuVehicle.Center));
				vContent->push_back(I2Str(pInfo->stuVehicle.nPolygonNum));
				vContent->push_back(MakePointers(pInfo->stuVehicle.Contour, pInfo->stuObject.nPolygonNum));
				vContent->push_back(MakeColorStr(pInfo->stuVehicle.rgbaMainColor));
				vContent->push_back(string(pInfo->stuVehicle.szText));
				vContent->push_back(I2Str(pInfo->stuVehicle.bShotFrame));
				
				vContent->push_back(string(pInfo->szFilePath));
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
		/************************************************************************/
		/*                                                                      */
		/************************************************************************/
	case EVENT_TRAFFICSNAPSHOT:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFICSNAPSHOT_INFO);
			}
			
			DEV_EVENT_TRAFFICSNAPSHOT_INFO* pInfo = (DEV_EVENT_TRAFFICSNAPSHOT_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				//报警级别
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane Count", 80));//车道数
				
				//车道级别
				vTitles->push_back(ColDesObj("Lane Number", 100));//当前车道号
				vTitles->push_back(ColDesObj("Snap Count", 100));//被触发抓拍的个数
				
				//抓拍级别
				vTitles->push_back(ColDesObj("Speed", 100));//当前车的速度，km/h
				vTitles->push_back(ColDesObj("Car Len", 100));//当前车长,分米为单位
				vTitles->push_back(ColDesObj("Red Light Time", 100));//当前车道红灯时间,秒.毫秒
				vTitles->push_back(ColDesObj("Snap Time", 100));//当前车道抓拍时间
				vTitles->push_back(ColDesObj("Snap Seq", 100));//当前车道抓拍序号
				vTitles->push_back(ColDesObj("Snap Type", 100));// 当前车道的抓拍类型
				vTitles->push_back(ColDesObj("Red Light Dir", 120));// 红灯方向
				vTitles->push_back(ColDesObj("Light Color", 100));// 交通灯颜色
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				//每个报警有多个通道，每个通道有多个抓图，因此记录需要被分成多条。
				//但是这些记录的GUID相同,在删除任何一条的时候，会把其他的也删除
				for (int i = 0; i < pInfo->bCarWayCount; i ++)
				{
					for (int j = 0; j < pInfo->stuCarWayInfo[i].bSigCount; j++)
					{
						//报警级别
						vContent->push_back(I2Str(pInfo->nChannelID + 1));
						vContent->push_back(string(pInfo->szName));
						vContent->push_back(D2Str(pInfo->PTS));
						vContent->push_back(NetTimeEx2Str(pInfo->UTC));
						vContent->push_back(I2Str(pInfo->nEventID));
						vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
						vContent->push_back(I2Str(pInfo->bCarWayCount));
						
						//车道级别
						vContent->push_back(I2Str(pInfo->stuCarWayInfo[i].bCarWayID));
						vContent->push_back(I2Str(pInfo->stuCarWayInfo[i].bSigCount));
						
						//抓拍级别
						vContent->push_back(I2Str(pInfo->stuCarWayInfo[i].stuSigInfo[j].snSpeed));
						vContent->push_back(I2Str(pInfo->stuCarWayInfo[i].stuSigInfo[j].snCarLength));
						vContent->push_back(D2Str(pInfo->stuCarWayInfo[i].stuSigInfo[j].fRedTime));
						vContent->push_back(D2Str(pInfo->stuCarWayInfo[i].stuSigInfo[j].fCapTime));
						vContent->push_back(I2Str(pInfo->stuCarWayInfo[i].stuSigInfo[j].bSigSequence));
						vContent->push_back(MakeSnapTypeStr(pInfo->stuCarWayInfo[i].stuSigInfo[j].bType));
						vContent->push_back(MakeRedLightDirStr(pInfo->stuCarWayInfo[i].stuSigInfo[j].bDirection));
						vContent->push_back(MakeLightColorStr(pInfo->stuCarWayInfo[i].stuSigInfo[j].bLightColor));
					}
				}
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
			
		}
		break;
	case EVENT_IVS_TRAFFIC_RUNREDLIGHT:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO);
			}
			
			DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO* pInfo = (DEV_EVENT_TRAFFIC_RUNREDLIGHT_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				vTitles->push_back(ColDesObj("Speed", 50));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);				
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// light state
				vTitles->push_back(ColDesObj("light state", 120));
				
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);				
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				vContent->push_back(I2Str(pInfo->nSpeed));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				// light state
				vContent->push_back(MakeLightColorStr2(pInfo->nLightState));
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
			return	TRUE;
		}
		break;
	case EVENT_IVS_TRAFFIC_OVERLINE:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_OVERLINE_INFO);
			}
			
			DEV_EVENT_TRAFFIC_OVERLINE_INFO* pInfo = (DEV_EVENT_TRAFFIC_OVERLINE_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);				
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_RETROGRADE:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_RETROGRADE_INFO);
			}
			
			DEV_EVENT_TRAFFIC_RETROGRADE_INFO* pInfo = (DEV_EVENT_TRAFFIC_RETROGRADE_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);				
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);				
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_TURNLEFT:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_TURNLEFT_INFO);
			}
			
			DEV_EVENT_TRAFFIC_TURNLEFT_INFO* pInfo = (DEV_EVENT_TRAFFIC_TURNLEFT_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);				
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_TURNRIGHT:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_TURNRIGHT_INFO);
			}
			
			DEV_EVENT_TRAFFIC_TURNRIGHT_INFO* pInfo = (DEV_EVENT_TRAFFIC_TURNRIGHT_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);				
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_UTURN:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_UTURN_INFO);
			}
			
			DEV_EVENT_TRAFFIC_UTURN_INFO* pInfo = (DEV_EVENT_TRAFFIC_UTURN_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_OVERSPEED:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_OVERSPEED_INFO);
			}
			
			DEV_EVENT_TRAFFIC_OVERSPEED_INFO* pInfo = (DEV_EVENT_TRAFFIC_OVERSPEED_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				vTitles->push_back(ColDesObj("Speed", 50));
				vTitles->push_back(ColDesObj("SpeedUpperLimit", 120));
				vTitles->push_back(ColDesObj("SpeedLowerLimit", 120));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nLane));
				vContent->push_back(I2Str(pInfo->nSpeed));
				vContent->push_back(I2Str(pInfo->nSpeedUpperLimit));
				vContent->push_back(I2Str(pInfo->nSpeedLowerLimit));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);				
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,  &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_UNDERSPEED:
		{
			//Size
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_OVERSPEED_INFO);
			}
			
			DEV_EVENT_TRAFFIC_OVERSPEED_INFO* pInfo = (DEV_EVENT_TRAFFIC_OVERSPEED_INFO*)pAlarmInfo;
			//Title
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("License Plate", 100));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				vTitles->push_back(ColDesObj("Speed", 50));
				vTitles->push_back(ColDesObj("SpeedUpperLimit", 120));
				vTitles->push_back(ColDesObj("SpeedLowerLimit", 120));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);	
				
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			//Content
			if (nGetWhat & GET_SI_CONTENT && pInfo != NULL)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(MakeLP(pInfo->stuObject.szText));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nLane));
				vContent->push_back(I2Str(pInfo->nSpeed));
				vContent->push_back(I2Str(pInfo->nSpeedUpperLimit));
				vContent->push_back(I2Str(pInfo->nSpeedLowerLimit));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);				
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFICJAM:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFICJAM_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 50));
				vTitles->push_back(ColDesObj("Sequence", 70));
				vTitles->push_back(ColDesObj("AlarmIntervalTime", 120));
				vTitles->push_back(ColDesObj("StartJaming", 180));
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
				
			}
			DEV_EVENT_TRAFFICJAM_INFO* pInfo = (DEV_EVENT_TRAFFICJAM_INFO*)pAlarmInfo;
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nLane));
				vContent->push_back(I2Str(pInfo->nSequence));
				vContent->push_back(I2Str(pInfo->nAlarmIntervalTime));
				vContent->push_back(NetTimeEx2Str(pInfo->stuStartJamTime));
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			if (nGetWhat & GET_SI_FILEINFO && pInfo != NULL)
			{
				memcpy(pFileInfo,&(pInfo->stuFileInfo),sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_PARKING:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_PARKING_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Sequence", 70));
				vTitles->push_back(ColDesObj("StartParkingTime", 120));
				vTitles->push_back(ColDesObj("AlarmIntervalTime", 120));
				vTitles->push_back(ColDesObj("ParkingAllowedTime", 120));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);				
			}
			DEV_EVENT_TRAFFIC_PARKING_INFO* pInfo = (DEV_EVENT_TRAFFIC_PARKING_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nSequence));
				vContent->push_back(NetTimeEx2Str(pInfo->stuStartParkingTime));
				vContent->push_back(I2Str(pInfo->nAlarmIntervalTime));
				vContent->push_back(I2Str(pInfo->nParkingAllowedTime));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
				
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_WRONGROUTE:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_WRONGROUTE_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 70));
				vTitles->push_back(ColDesObj("Speed", 70));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			DEV_EVENT_TRAFFIC_WRONGROUTE_INFO* pInfo = (DEV_EVENT_TRAFFIC_WRONGROUTE_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nLane));
				vContent->push_back(I2Str(pInfo->nSpeed));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_CROSSLANE:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_CROSSLANE_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Speed", 70));
				vTitles->push_back(ColDesObj("Lane", 70));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				
			}
			DEV_EVENT_TRAFFIC_CROSSLANE_INFO* pInfo = (DEV_EVENT_TRAFFIC_CROSSLANE_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nSpeed));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_OVERYELLOWLINE:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Speed", 70));
				vTitles->push_back(ColDesObj("Lane", 70));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO* pInfo = (DEV_EVENT_TRAFFIC_OVERYELLOWLINE_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nSpeed));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_DRIVINGONSHOULDER:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Speed", 70));
				vTitles->push_back(ColDesObj("Lane", 70));
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				
			}
			DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO* pInfo = (DEV_EVENT_TRAFFIC_DRIVINGONSHOULDER_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nSpeed));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_YELLOWPLATEINLANE:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Chn", 40));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Speed", 70));
				vTitles->push_back(ColDesObj("Lane", 70));
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
				
			}
			DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO* pInfo = (DEV_EVENT_TRAFFIC_YELLOWPLATEINLANE_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID + 1));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				vContent->push_back(I2Str(pInfo->nSpeed));
				vContent->push_back(I2Str(pInfo->nLane));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_FLOWSTATE:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_FLOWSTAT_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("Period", 120));
				vTitles->push_back(ColDesObj("LaneCnt", 120));
				vTitles->push_back(ColDesObj("Vehicles", 120));
				vTitles->push_back(ColDesObj("Lane", 120));
				vTitles->push_back(ColDesObj("OverSpeedVehicles", 120));
				vTitles->push_back(ColDesObj("UnderSpeedVehicles", 120));
				vTitles->push_back(ColDesObj("MotoVehicles", 120));
				vTitles->push_back(ColDesObj("SmallVehicles", 120));
				vTitles->push_back(ColDesObj("MediumVehicles", 120));
				vTitles->push_back(ColDesObj("LargeVehicles", 120));
				vTitles->push_back(ColDesObj("LongVehicles", 120));
				vTitles->push_back(ColDesObj("AverageLength", 120));
				vTitles->push_back(ColDesObj("AverageSpeed", 120));
				vTitles->push_back(ColDesObj("Density", 120));
				vTitles->push_back(ColDesObj("SpaceHeadway", 120));
				vTitles->push_back(ColDesObj("SpaceOccupyRatio", 120));
				vTitles->push_back(ColDesObj("TimeHeadway", 120));
				vTitles->push_back(ColDesObj("TimeOccupyRatio", 120));
				vTitles->push_back(ColDesObj("MachineName", 120));
				vTitles->push_back(ColDesObj("MachineAddress", 120));
				vTitles->push_back(ColDesObj("DrivingDirection[0]", 120));
				vTitles->push_back(ColDesObj("DrivingDirection[1]", 120));
				vTitles->push_back(ColDesObj("DrivingDirection[2]", 120));
			}
			DEV_EVENT_TRAFFIC_FLOWSTAT_INFO* pInfo = (DEV_EVENT_TRAFFIC_FLOWSTAT_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				for (int i=0;i<pInfo->nLaneCnt;i++)
				{
					vContent->push_back(string(pInfo->szName));
					vContent->push_back(D2Str(pInfo->PTS));
					vContent->push_back(NetTimeEx2Str(pInfo->UTC));
					vContent->push_back(I2Str(pInfo->nEventID));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nPeriod));					
					vContent->push_back(I2Str(pInfo->nLaneCnt));
					
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nVehicles));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nLane));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nOverSpeedVehicles));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nUnderSpeedVehicles));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nMotoVehicles));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nSmallVehicles));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nMediumVehicles));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nLargeVehicles));
					vContent->push_back(I2Str(pInfo->stTrafficFlowStats[i].nLongVehicles));
					vContent->push_back(D2Str(pInfo->stTrafficFlowStats[i].fAverageLength));
					vContent->push_back(D2Str(pInfo->stTrafficFlowStats[i].fAverageSpeed));
					vContent->push_back(D2Str(pInfo->stTrafficFlowStats[i].fDensity));
					vContent->push_back(D2Str(pInfo->stTrafficFlowStats[i].fSpaceHeadway));
					vContent->push_back(D2Str(pInfo->stTrafficFlowStats[i].fSpaceOccupyRatio));
					vContent->push_back(D2Str(pInfo->stTrafficFlowStats[i].fTimeHeadway));
					vContent->push_back(D2Str(pInfo->stTrafficFlowStats[i].fTimeOccupyRatio));
					vContent->push_back(string(pInfo->stTrafficFlowStats[i].szMachineName));
					vContent->push_back(string(pInfo->stTrafficFlowStats[i].szMachineAddress));
					vContent->push_back(string(pInfo->stTrafficFlowStats[i].szDrivingDirection[0]));
					vContent->push_back(string(pInfo->stTrafficFlowStats[i].szDrivingDirection[1]));
					vContent->push_back(string(pInfo->stTrafficFlowStats[i].szDrivingDirection[2]));
				}
			}
		}
		break;
		
	case EVENT_IVS_TRAFFIC_STAY:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_STAY_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				vTitles->push_back(ColDesObj("Lane", 120));
				//vTitles->push_back(ColDesObj("Mark", 120));
				vTitles->push_back(ColDesObj("Sequence", 120));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			DEV_EVENT_TRAFFIC_STAY_INFO* pInfo = (DEV_EVENT_TRAFFIC_STAY_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nLane));
				//vContent->push_back(I2Str(pInfo->nMark));
				vContent->push_back(I2Str(pInfo->nSequence));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
		
	case EVENT_IVS_TRAFFIC_VEHICLEINROUTE:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_VEHICLEINROUTE_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				
				vTitles->push_back(ColDesObj("Lane", 120));
				//vTitles->push_back(ColDesObj("Mark", 120));
				vTitles->push_back(ColDesObj("Sequence", 120));
				vTitles->push_back(ColDesObj("Speed", 120));
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			DEV_EVENT_TRAFFIC_VEHICLEINROUTE_INFO* pInfo = (DEV_EVENT_TRAFFIC_VEHICLEINROUTE_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nLane));
				//vContent->push_back(I2Str(pInfo->nMark));
				vContent->push_back(I2Str(pInfo->nSequence));
				vContent->push_back(I2Str(pInfo->nSpeed));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);
				
			}
			
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	case EVENT_IVS_TRAFFIC_MANUALSNAP:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_MANUALSNAP_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("channel",80));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				
				vTitles->push_back(ColDesObj("Lane", 120));
				vTitles->push_back(ColDesObj("EventAction", 80));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			DEV_EVENT_TRAFFIC_MANUALSNAP_INFO* pInfo = (DEV_EVENT_TRAFFIC_MANUALSNAP_INFO*)pAlarmInfo;
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				vContent->push_back(I2Str(pInfo->nLane));				
				vContent->push_back(I2Str(pInfo->bEventAction));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);				
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}			
		}
		break;
		
    case EVENT_IVS_TRAFFIC_PEDESTRAINPRIORITY:
		{
			if (nGetWhat & GET_SI_SIZE)
			{
				*nStructSize = sizeof(DEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO);
			}
			if (nGetWhat & GET_SI_TITLE)
			{
				vTitles->push_back(ColDesObj("channel",80));
				vTitles->push_back(ColDesObj("Event Name", 80));
				vTitles->push_back(ColDesObj("PTS", 120));
				vTitles->push_back(ColDesObj("Time", 150));
				vTitles->push_back(ColDesObj("Event ID", 70));
				vTitles->push_back(ColDesObj("SnapFlags", 140));
				
				// file info
				vTitles->push_back(ColDesObj("GroupId", 80));
				vTitles->push_back(ColDesObj("GroupCount", 80));
				vTitles->push_back(ColDesObj("GroupIndex", 80));
				
				vTitles->push_back(ColDesObj("Lane", 120));
				vTitles->push_back(ColDesObj("EventAction", 80));
				
				// plate
				GetPlateInfo( GET_SI_TITLE, 0, vTitles, 0);
				
				// Vehicle
				GetVehicleInfo( GET_SI_TITLE, 0, vTitles, 0);
				// trafficCar
				GettrafficCarInfo( GET_SI_TITLE, 0, vTitles, 0);
			}
			DEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO* pInfo = (DEV_EVENT_TRAFFIC_PEDESTRAINPRIORITY_INFO*)pAlarmInfo;
			
			if (nGetWhat & GET_SI_CONTENT)
			{
				vContent->push_back(I2Str(pInfo->nChannelID));
				vContent->push_back(string(pInfo->szName));
				vContent->push_back(D2Str(pInfo->PTS));
				vContent->push_back(NetTimeEx2Str(pInfo->UTC));
				vContent->push_back(I2Str(pInfo->nEventID));
				vContent->push_back(DWORDFlag2Str(pInfo->dwSnapFlagMask));
				
				// file info
				vContent->push_back(I2Str(pInfo->stuFileInfo.nGroupId));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bCount));
				vContent->push_back(I2Str(pInfo->stuFileInfo.bIndex));
				vContent->push_back(I2Str(pInfo->nLane));				
				vContent->push_back(I2Str(pInfo->bEventAction));
				
				// plate
				GetPlateInfo( GET_SI_CONTENT, &pInfo->stuObject, vTitles, vContent);
				
				// Vehicle
				GetVehicleInfo( GET_SI_CONTENT, &pInfo->stuVehicle, vTitles, vContent);				
				
				// trafficCar
				GettrafficCarInfo( GET_SI_CONTENT, &pInfo->stTrafficCar, vTitles, vContent);
			}
			
			if (nGetWhat & GET_SI_FILEINFO && pFileInfo != NULL)
			{
				memcpy(pFileInfo, &(pInfo->stuFileInfo), sizeof(DH_EVENT_FILE_INFO));
			}
		}
		break;
	default:
		return -1;	
	}
	
	return TRUE;
}