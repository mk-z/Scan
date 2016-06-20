// ConfigAlarmMotionArea.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo5.h"
#include "ConfigAlarmMotionArea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarmMotionArea dialog


CConfigAlarmMotionArea::CConfigAlarmMotionArea(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigAlarmMotionArea::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigAlarmMotionArea)
	m_nAreaThreshold = 0;
	m_nSensitivity = 0;
	//}}AFX_DATA_INIT
	m_bDrawing = FALSE;
	m_blckWid = 0;
	m_blckHght = 0;
	m_stpoint.x = -1;
	m_stpoint.y = -1;
	m_lastpoint.y = -1;
	m_lastpoint.y = -1;

	m_wRows = DH_MOTION_ROW;
	m_wCols = DH_MOTION_COL;

	m_pMotionInfo = NULL;

}


void CConfigAlarmMotionArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigAlarmMotionArea)
	DDX_Control(pDX, IDC_COMBO_DETECT_ID, m_DetectId);
	DDX_Text(pDX, IDC_EDIT_AREATHRESHOLD, m_nAreaThreshold);
	DDV_MinMaxInt(pDX, m_nAreaThreshold, 0, 100);
	DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_nSensitivity);
	DDV_MinMaxInt(pDX, m_nSensitivity, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigAlarmMotionArea, CDialog)
	//{{AFX_MSG_MAP(CConfigAlarmMotionArea)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ADDRECT, OnButtonAddrect)
	ON_BN_CLICKED(IDC_BUTTON_DELRECT, OnButtonDelrect)
	ON_CBN_SELCHANGE(IDC_COMBO_DETECT_ID, OnSelchangeComboDetectId)
	ON_CBN_DROPDOWN(IDC_COMBO_DETECT_ID, OnDropdownComboDetectId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CConfigAlarmMotionArea::InitComboDetectId()
{
    if (!m_pMotionInfo->abDetectRegion)
    {
        m_DetectId.EnableWindow(FALSE);
        return;
    }

    m_DetectId.ResetContent();
    for (int i = 0; i < m_pMotionInfo->nRegionCount; i++)
    {
        CString csChn;
        csChn.Format("%d: ", i);
        csChn += m_pMotionInfo->stuRegion[i].szRegionName;
        m_DetectId.InsertString(-1, csChn);
    }
    
    m_DetectId.SetCurSel(0);
}

/////////////////////////////////////////////////////////////////////////////
// CConfigAlarmMotionArea message handlers

void CConfigAlarmMotionArea::OnOK() 
{
	// TODO: Add extra validation here

    RetrieveRegionInfo();
	
	CDialog::OnOK();
}

BOOL CConfigAlarmMotionArea::OnInitDialog() 
{
	CDialog::OnInitDialog();
	g_SetWndStaticText(this);
	// TODO: Add extra initialization here

    InitComboDetectId();

    CRect dummyRect(0, 0, 0, 0);
    for (int i = 0; i < MAX_MOTION_ROW; i++)
    {
        for (int j = 0; j < MAX_MOTION_COL; j++)
        {
            m_block[i][j].Create(
                NULL, 
                NULL, 
                WS_VISIBLE | WS_CHILD,
                dummyRect,
                this,
                1979,
                NULL);
        }
    }
    ShowRegionInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigAlarmMotionArea::RetrieveRegionInfo()
{
    UpdateData(TRUE);

    BYTE* byRegion;

    
    if (m_pMotionInfo->abDetectRegion)
    {
        const int nDetectId = m_DetectId.GetCurSel();
        CFG_DETECT_REGION& stuRegion = m_pMotionInfo->stuRegion[nDetectId];
        byRegion = (BYTE*)stuRegion.byRegion;
        stuRegion.nMotionRow = m_wRows;
        stuRegion.nMotionCol = m_wCols;
        stuRegion.nThreshold = m_nAreaThreshold;
        stuRegion.nSenseLevel = m_nSensitivity;
    }
    else
    {
        byRegion = (BYTE*)m_pMotionInfo->byRegion;
        m_pMotionInfo->nMotionRow = m_wRows;
        m_pMotionInfo->nMotionCol = m_wCols;
    }

    for (int i = 0; i < m_wRows; i++)
    {
        for (int j = 0; j < m_wCols; j++)
        {
            *(byRegion+i*MAX_MOTION_ROW+j) = m_block[i][j].IsSeleted();
        }
    }

    
}

void CConfigAlarmMotionArea::ShowRegionInfo()
{
    BYTE* byRegion;

    if (m_pMotionInfo->abDetectRegion)
    {
        const int nDetectId = m_DetectId.GetCurSel();
        const CFG_DETECT_REGION& stuRegion = m_pMotionInfo->stuRegion[nDetectId];
        byRegion = (BYTE*)stuRegion.byRegion;
        m_wRows = stuRegion.nMotionRow;
        m_wCols = stuRegion.nMotionCol;
        m_nAreaThreshold = stuRegion.nThreshold;
        m_nSensitivity = stuRegion.nSenseLevel;
    }
    else
    {
        byRegion = (BYTE*)m_pMotionInfo->byRegion;
        m_wRows = m_pMotionInfo->nMotionRow;
        m_wCols = m_pMotionInfo->nMotionCol;

        GetDlgItem(IDC_EDIT_AREATHRESHOLD)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_SENSITIVITY)->EnableWindow(FALSE);
    }
    
    CRect rect;
    GetDlgItem(IDC_AREA_BOARD)->GetClientRect(&rect);
    GetDlgItem(IDC_AREA_BOARD)->ClientToScreen(&rect);
    ScreenToClient(&rect);
    
    if(0 != m_wCols)
    {
        m_blckWid = (rect.Width()-m_wCols+1)/m_wCols;
    }
    if(0 != m_wRows)
    {
        m_blckHght = (rect.Height()-m_wRows+1)/m_wRows;
    }
    
    for (int i = 0; i < m_wRows; i++)
    {
        for (int j = 0; j < m_wCols; j++)
        {
            CRect blockRect(rect.left+j*m_blckWid+j, rect.top+i*m_blckHght+i, rect.left+(j+1)*m_blckWid+j, rect.top+(i+1)*m_blckHght+i);

            m_block[i][j].MoveWindow(&blockRect);

            m_block[i][j].PostMessage(MSG_SHOW);
            m_block[i][j].SetPos(i,j);
            m_block[i][j].SetStatus(*(byRegion+i*MAX_MOTION_ROW+j));
        }
	}
    
    UpdateData(FALSE);
}

void CConfigAlarmMotionArea::SetMaxMotionWindow(int nMaxWindow)
{
    m_nMaxMotionWindow = __min(nMaxWindow , MAX_MOTION_WINDOW);
}

void CConfigAlarmMotionArea::SetArea(CFG_MOTION_INFO* pMotionInfo)
{
    m_pMotionInfo = pMotionInfo;
    
}

void CConfigAlarmMotionArea::RecordPoint(BYTE x, BYTE y)
{
	m_stpoint.x = x;
	m_stpoint.y = y;
	m_lastpoint.x = x;
	m_lastpoint.y = y;
	m_bDrawing = TRUE;
	
	m_block[x][y].PostMessage(MSG_SELETED);
}

BOOL IsBetween(int lft, int mid, int rht)
{
	if (lft >= rht)
	{
		return (mid >= rht && mid <= lft);
	}
	else
	{
		return (mid >= lft && mid <= rht);
	}
}

void CConfigAlarmMotionArea::ReleasePoint()
{
	m_bDrawing = FALSE;
}

void CConfigAlarmMotionArea::MovePoint(DWORD dwParm, BYTE x, BYTE y)
{
	if (!m_bDrawing || !(dwParm&MK_LBUTTON) || (m_lastpoint.x == x && m_lastpoint.y == y))
	{
		return;
	}
	
	for (int i = 0; i < DH_MOTION_ROW; i++)
	{
		for (int j = 0; j < DH_MOTION_COL; j++)
		{
			if(((IsBetween(m_stpoint.x, i, x) && IsBetween(m_stpoint.y, j, y)) &&
				!(IsBetween(m_stpoint.x, i, m_lastpoint.x) && IsBetween(m_stpoint.y, j, m_lastpoint.y))) ||
				(IsBetween(m_stpoint.x, i, m_lastpoint.x) && IsBetween(m_stpoint.y, j, m_lastpoint.y)) &&
				!((IsBetween(m_stpoint.x, i, x) && IsBetween(m_stpoint.y, j, y))))
			{
				m_block[i][j].PostMessage(MSG_SELETED);
			}
		}
	}
	
	m_lastpoint.x = x;
	m_lastpoint.y = y;
}

void CConfigAlarmMotionArea::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CConfigAlarmMotionArea::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bDrawing = FALSE;
	
	CDialog::OnLButtonUp(nFlags, point);
}

HBRUSH CConfigAlarmMotionArea::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


void CConfigAlarmMotionArea::OnButtonAddrect() 
{
	// TODO: Add your control notification handler code here
// 	CFG_MOTION_WINDOW stuWnd = {0};
// 	stuWnd.nThreshold = GetDlgItemInt(IDC_EDIT_AREATHRESHOLD, &stuWnd.nThreshold, FALSE);
// 	stuWnd.nSensitive = GetDlgItemInt(IDC_EDIT_SENSITIVITY, &stuWnd.nSensitive, FALSE);
// 
// 	m_dlgAreaDraw.AddWnd(stuWnd);
}

void CConfigAlarmMotionArea::OnButtonDelrect() 
{
	// TODO: Add your control notification handler code here
// 	m_dlgAreaDraw.DeleteWnd();
// 
// 	SetDlgItemInt(IDC_EDIT_AREATHRESHOLD, -1, TRUE);
// 	SetDlgItemInt(IDC_EDIT_SENSITIVITY, -1, TRUE);
// 
// 	Invalidate(TRUE);
}

void CConfigAlarmMotionArea::ShowParam(const CFG_MOTION_WINDOW& stuMotionWnd)
{
	SetDlgItemInt(IDC_EDIT_AREATHRESHOLD, stuMotionWnd.nThreshold, TRUE);
	SetDlgItemInt(IDC_EDIT_SENSITIVITY, stuMotionWnd.nSensitive, TRUE);
}


void CConfigAlarmMotionArea::OnSelchangeComboDetectId() 
{
	// TODO: Add your control notification handler code here
	ShowRegionInfo();
}

void CConfigAlarmMotionArea::OnDropdownComboDetectId() 
{
	// TODO: Add your control notification handler code here
	RetrieveRegionInfo();
}
