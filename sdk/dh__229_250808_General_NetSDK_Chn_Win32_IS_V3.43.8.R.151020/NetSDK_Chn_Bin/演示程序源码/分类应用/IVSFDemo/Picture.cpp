// CPicture.cpp: implementation of the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Picture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//----------------CFileProcess class------------------------------------
//constructor
CFileProcess::CFileProcess()
{
	m_File = NULL;         //File *m_File;
}

//destructor !
CFileProcess::~CFileProcess()
{
//	this->Close();
}

//opens a file either for reading or writing
BOOL CFileProcess::Open(char * FileName , FILE_OPENMODE Open_Mode)
{

	switch (Open_Mode)
	{
		case OFM_READ:
			m_File = fopen(FileName, "rb");
			break;
		case OFM_WRITE:
			m_File = fopen(FileName, "wb");
			break;
	}

	//ASSERT(m_File != NULL);
	if(!m_File) 
		return FALSE;
	return TRUE;
}


//Reads data from the file stream.
BOOL CFileProcess::Read(VOID * zBuffer, DWORD cSize)
{
	DWORD dwFreadReslut = fread(zBuffer, sizeof(BYTE), cSize, m_File);
	if(dwFreadReslut < cSize)
		return FALSE;
	return TRUE;
}

//Writes data to the file stream.
BOOL CFileProcess::Write(VOID * zBuffer,DWORD cSize)
{
	//fwrite :write size*count byte to buffer.
	if(fwrite(zBuffer, sizeof(BYTE), cSize, m_File) < cSize)
       return FALSE;
	return TRUE;
}

//Gets the File Size
LONG CFileProcess::GetSize(VOID)
{
	long t_location =  ftell(m_File);
	//moves the file pointer to  a specified location 
	fseek(this->m_File, 0, SEEK_END);

	long f_size = ftell(this->m_File);
	fseek(this->m_File ,t_location, SEEK_SET);
	return f_size;
}

//Closes the File
VOID CFileProcess::Close(VOID)
{
	if(m_File)
	{
		fclose(this->m_File);
	    this->m_File  = NULL;
	}
	return;
}

//-----------------------
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPicture::CPicture()
{
	m_pic = NULL;
	hGlobal = NULL;
	m_pPict = NULL;

}

CPicture::~CPicture()
{
	this->FreePicture();

}



void CPicture::Render(CDC* pDC, LPRECT pDrawRect, LPRECT pSrcRect/*=NULL*/,LPCRECT prcWBounds/*=NULL*/)
{
    if (pDC == NULL || m_pPict == NULL) return ;
    
	CRect recrDest(pDrawRect);
	
	
	
    long Width  = 0;
    long Height = 0;
    m_pPict->get_Width(&Width);
    m_pPict->get_Height(&Height);
	
	
	
	CRect SrcRect(0,0,Width,Height);
	
	
	
	if(pSrcRect){
		SrcRect=*pSrcRect;
	}
	CRect DrawRect(pDrawRect);
    HRESULT hrP = NULL;
	
	
	
    hrP = m_pPict->Render(pDC->m_hDC,
		DrawRect.left,                  // Left
		DrawRect.top,                   // Top
		DrawRect.Width(), // Right
		DrawRect.Height(), // Bottom
		SrcRect.left,
		SrcRect.top,
		SrcRect.Width(),
		SrcRect.Height(),
		prcWBounds);
	
	
	
    if (SUCCEEDED(hrP)) return;
	AfxThrowMemoryException();
    return;
}
/*
OUR MAIN FUNCTION
*/
HBITMAP CPicture::LoadPicture(char *FileName)
{
	FreePicture();

	CFileProcess cFile;  //the image file
	
	//if we couldn't open the image file then we should get out of here
    if(!cFile.Open(FileName, OFM_READ)) 
		return NULL;

	//we must know exactly the buffer size to allocate
	//in order to read the image in it
	//so get the image file size
    long nSize = cFile.GetSize(); 
	//allocate enough memory to hold the image
	//it must be allocated using GlobalAlloc
	//otherwise it will fail...try using new or malloc and you'll see!!!
	hGlobal = GlobalAlloc(GMEM_MOVEABLE, nSize);
	
	//get pointer to first byte
	void* pData = GlobalLock(hGlobal);
	
	//read the file in the prev allocated memory
	if(!cFile.Read(pData, nSize)) 
		return NULL;;
	//we don't need the file any more so close it
	cFile.Close();
	GlobalUnlock(hGlobal); 

	IStream* pStream = NULL;
    //ole routines....
	//creates a stream from our handle
	//don't know why and how?
	if (CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) != S_OK)
		return NULL;

	HRESULT hr;
	//aha..now let ole reads the image and load it for us
	//param3:Reference to the identifier of the interface 
               // describing the type of interface pointer to return
	//param4: Address of output variable that receives interface  pointer requested in riid
	hr = OleLoadPicture(pStream, nSize, FALSE, IID_IPicture, (LPVOID*)&this->m_pic);
	if(hr != S_OK)
		return NULL;
	
	pStream->Release();
	
//	if ((hr = OleLoadPicture(pStream, nSize, FALSE, IID_IPicture, (LPVOID *)&this->m_pic)) != S_OK)
//		return NULL;
	HBITMAP hbmp = NULL;
	//return an HBITMAP to our image like the LoadImage function does
	//we might need the handle
	this->m_pic->get_Handle((OLE_HANDLE *) &hbmp);
	return hbmp;
}


//an overloaded version of the above to draw the picture
//as well in a given DC
HBITMAP CPicture::LoadPicture(char *FileName, HDC hdc)
{
	HBITMAP hbmp = this->LoadPicture(FileName);
	this->DrawPicture(hdc, 0, 0, this->_GetWidth(), _GetHeight());
	return hbmp;
}

//an overloaded version of the above to draw the picture
//as well in a given DC , give the rect, width and height
HBITMAP CPicture::LoadPicture(char *FileName, HDC hdc, long cx, long cy)
{
	HBITMAP hbmp = this->LoadPicture(FileName);
	this->DrawPicture(hdc, 0, 0, cx,cy);
	return hbmp;
}

//returns the width of the loaded image  
DWORD CPicture::_GetWidth(VOID)
{
    
	if(! m_pic) 
		return 0;
	OLE_XSIZE_HIMETRIC pWidth;
	m_pic->get_Width(&pWidth);
	HDC tDC = ::CreateCompatibleDC(0);
	int nWidth	= MulDiv(pWidth, ::GetDeviceCaps(tDC, LOGPIXELSX), HIMETRIC_INCH);
	DeleteDC(tDC);
	return (DWORD) nWidth;
}


//returns the height of the loaded image
DWORD CPicture::_GetHeight(VOID)
{
	if(! m_pic) 
		return 0;
	OLE_YSIZE_HIMETRIC pHeight;

	m_pic->get_Height(&pHeight);
	HDC tDC = ::CreateCompatibleDC(0);

	int nHeight	= MulDiv(pHeight, ::GetDeviceCaps(tDC, LOGPIXELSY), HIMETRIC_INCH);
	DeleteDC(tDC);
	
	return (DWORD) nHeight;
}

//returns the current DC of the loaded image
HDC CPicture::_GetDC(VOID)
{
	if(! m_pic) 
		return NULL;
	HDC pDC ;
	m_pic->get_CurDC(&pDC);
	return  pDC;
}

//returns the Handle of the loaded image(HBITMAP)
HBITMAP CPicture::_GetHandle( VOID )
{
	if(! m_pic) 
		return NULL; 

	HBITMAP hbmp;
	m_pic->get_Handle((OLE_HANDLE *) &hbmp);
	return  hbmp;
}


//Draws the image in a specified DC..with given dimensions
//specify -1 for width and height if you like to draw
//with original dimensions
BOOL CPicture::DrawPicture(HDC hdc,long x,long y,long cx,long cy)
{
	if(!m_pic) 
		return FALSE;

	LONG pHeight,pWidth;
	if(cx == -1) 
		cx = this->_GetWidth();
	if(cy == -1) 
		cy = this->_GetHeight();
	m_pic->get_Width(&pWidth);
    m_pic->get_Height(&pHeight);
	if (m_pic->Render(hdc, x, y, cx, cy, 0, pHeight, pWidth,-pHeight, NULL) != S_OK)
		return FALSE ;
	
	return TRUE;
}

//Cleans up
VOID CPicture::FreePicture(VOID)
{
	if(m_pic)
	{
		m_pic->Release();
		m_pic = NULL;
	}

	if(hGlobal)
	{
		GlobalFree(hGlobal);
		hGlobal = NULL;
	}
}
