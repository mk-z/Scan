// AlarmShow.cpp : implementation file
//

#include "stdafx.h"
#include "IVSFDemo.h"
#include "AlarmShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlarmShow dialog


CAlarmShow::CAlarmShow(CWnd* pParent /*=NULL*/)
	: CDialog(CAlarmShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAlarmShow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAlarmShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAlarmShow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAlarmShow, CDialog)
	//{{AFX_MSG_MAP(CAlarmShow)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlarmShow message handlers
BOOL CAlarmShow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	
	m_Panel.Create(this);
	CRect rc;
	GetClientRect(&rc);
	
	m_Panel.MoveWindow(&rc, TRUE);
	m_Panel.ShowWindow(SW_SHOW);
	
	return TRUE;
}

BOOL CAlarmShow::ShowAlarmInfo(CString strFilePre, DEV_EVENT_FACERECOGNITION_INFO* pAlarmInfo)
{
	if (pAlarmInfo == NULL)
	{
		return FALSE;
	}

	// clear old info
	m_Panel.DeleteAllItems();

	// show alarm
	CString strSrcFile = strFilePre + SRCFILE + ".jpg";
	CString strTemp;
	for (int i = 0; i < pAlarmInfo->nCandidateNum; i++)
	{
		Item stItem = {0};

		strTemp = strFilePre + MATCHFILE + I2Str(i) + "_0.jpg";
		strncpy(stItem.strSrcImgPath, (LPSTR)(LPCTSTR)strSrcFile, 256);
		strncpy(stItem.strFoundImgPath, (LPSTR)(LPCTSTR)strTemp, 256);

		strncpy(stItem.strName, pAlarmInfo->stuCandidates[i].stPersonInfo.szPersonName, 16);
		strncpy(stItem.strIdCode, pAlarmInfo->stuCandidates[i].stPersonInfo.szID, 32);

		strTemp.Format("%d-%d-%d",pAlarmInfo->stuCandidates[i].stPersonInfo.wYear, 
			pAlarmInfo->stuCandidates[i].stPersonInfo.byMonth, pAlarmInfo->stuCandidates[i].stPersonInfo.byDay);
		strncpy(stItem.strBirthday, (LPSTR)(LPCTSTR)strTemp, 64);

		if (pAlarmInfo->stuCandidates[i].stPersonInfo.bySex == 0)
		{
			strncpy(stItem.strSex, ConvertString("male"), 64);
		}
		else
		{
			strncpy(stItem.strSex, ConvertString("female"), 64);
		}
		
		m_Panel.InsertItem(stItem);
	}
	
	return TRUE;
}

void CAlarmShow::ClearShow()
{
	// clear old info
	m_Panel.DeleteAllItems();
}