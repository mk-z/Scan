// DrawFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "DemoIVSPC.h"
#include "DrawFrame.h"


// 坐标相关偏移
#define ORIGIN_OFFSET_X		25
#define ORIGIN_OFFSET_Y		280
#define X_AXIS_LENGTH		800
#define Y_AXIS_LENGTH		280
#define ARROW_LENGTH		5
#define BASE_LINE_OFFSET	50
#define TEXT_OFFSET			5

#define X_SPACE_LENGTH		70  //x轴上，每个刻度的间隔
#define Y_SPACE_LENGTH		30  //y轴上，每个刻度的间隔

#define X_SPACE_NUM			10  //x轴上，分隔的个数
#define Y_SPACE_NUM			8   //y轴上，分隔的个数

// CDrawFrame 对话框

IMPLEMENT_DYNAMIC(CDrawFrame, CDialog)

CDrawFrame::CDrawFrame(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawFrame::IDD, pParent)
	, m_rectClient(0)
	, m_dwStartIndex(0)
	, m_dwCount(0)
	, m_nType(-1)
	, m_bPaint(true)
	, m_nMaxY(0)
{
	memset((void*)&m_dataShow, 0, sizeof(NET_OUT_DOFINDNUMBERSTAT));
}

CDrawFrame::~CDrawFrame()
{
	DeleteCriticalSection(&m_criticalSection);
	UninitData();
}

void CDrawFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrawFrame, CDialog)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDrawFrame 消息处理程序


BOOL CDrawFrame::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	m_pDC = this->GetDC();
	InitializeCriticalSection(&m_criticalSection);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDrawFrame::DrawCoordinate( )
{
	if (m_rectClient.Height() <= 0)
	{
		return;
	}

	POINT xStart, xEnd;
	POINT yStart, yEnd;
	CString line;
    int i = 0;
	int nIndex = 0;
	xStart.x = yStart.x = ORIGIN_OFFSET_X;
	xStart.y = yStart.y = ORIGIN_OFFSET_Y;

	// 画X轴
	xEnd.x   = xStart.x + X_AXIS_LENGTH;
	xEnd.y	 = xStart.y;

	CPen bluePen(PS_SOLID, 0, RGB(0, 0, 255));
	m_pDC->SelectObject(&bluePen);

	m_pDC->MoveTo(xStart);
	m_pDC->LineTo(xEnd);

	// 画X轴箭头
	g_DrawArrow(m_pDC, xEnd, ARROW_RIGHT);

	// 设置字体背景及颜色
	m_pDC->SetBkMode(TRANSPARENT);
	m_pDC->SetTextColor(RGB(0, 0, 255));

	for (i = 0; i <= X_SPACE_NUM; ++i)
	{
		line.Format("%d", i*10);
		m_pDC->TextOut(xStart.x + i*X_SPACE_LENGTH, xStart.y + TEXT_OFFSET, line);
	}

	POINT yEndTemp;
	POINT yStartTemp;
	yStartTemp = yStart;
	yEndTemp = yStart;
	yEndTemp.y = yEndTemp.y - 5;
	for (nIndex = 0; nIndex < X_SPACE_NUM; nIndex++)
	{
		yStartTemp.x = yStartTemp.x + X_SPACE_LENGTH;
		yEndTemp.x = yEndTemp.x + X_SPACE_LENGTH;	
		m_pDC->MoveTo(yStartTemp);
		m_pDC->LineTo(yEndTemp);
	}

	// 画Y轴
	yEnd.x	 = yStart.x;
	yEnd.y	 = yStart.y - Y_AXIS_LENGTH;
	m_pDC->MoveTo(yStart);
	m_pDC->LineTo(yEnd);

	// 画Y轴箭头
	g_DrawArrow(m_pDC,yEnd, ARROW_UP);

	for (i=0; i<Y_SPACE_NUM; ++i)
	{
		CString str;
		str.Format("%d", (i+1)*10);
		m_pDC->TextOut(yStart.x - TEXT_OFFSET*4, yStart.y - (i+1)*Y_SPACE_LENGTH - TEXT_OFFSET*3, str);
	}

	POINT xEndTemp;
	POINT xStartTemp;
	xStartTemp = xStart;
	xEndTemp = xStart;
	xEndTemp.x = xEndTemp.x + 5;
	for (nIndex = 0; nIndex < Y_SPACE_NUM; nIndex++)
	{
		xStartTemp.y = xStartTemp.y - Y_SPACE_LENGTH;
		xEndTemp.y = xEndTemp.y - Y_SPACE_LENGTH;	
		m_pDC->MoveTo(xStartTemp);
		m_pDC->LineTo(xEndTemp);
	}

	// 保存坐标范围
	m_rectRange.left   = yEnd.x;
	m_rectRange.top    = yEnd.y;
	m_rectRange.right  = xEnd.x;
	m_rectRange.bottom = xEnd.y;

}


void CDrawFrame::DrawFrame()
{
	if (m_dwCount<=0)
	{
		return;
	}
	
	DrawLine(true);
	DrawLine(false);

	CPen bluePen(PS_SOLID, 0, RGB(0, 0, 255));
	m_pDC->SelectObject(bluePen);
}

void CDrawFrame::DrawLine(bool bEnter)
{
	CPen greenPen(PS_SOLID, 0, RGB(50, 200, 50));
	CPen redPen(PS_SOLID, 0, RGB(200, 50,50));
	if (bEnter)
	{
		HGDIOBJ hOldObj = m_pDC->SelectObject(&greenPen);
	}
	else
	{
		HGDIOBJ hOldObj = m_pDC->SelectObject(&redPen);
	}

	// 查找数据中的最大值，这样可以算出y轴的比例
	int nZoom = GetZoom();
	switch(m_nType)
	{
	case 0://分
		if (bEnter)
		{
			DrawPointEnter(nZoom, ConvertString("Time(minute)"));
		}
		else
		{
			DrawPointExit(nZoom, ConvertString("Time(minute)"));
		}
		break;
	case 1://时
		if (bEnter)
		{
			DrawPointEnter(nZoom, ConvertString("Time(Hour)"));
		}
		else
		{
			DrawPointExit(nZoom, ConvertString("Time(Hour)"));
		}
		break;
	case 2://天
		if (bEnter)
		{
			DrawPointEnter(nZoom, ConvertString("Time(Day)"));
		}
		else
		{
			DrawPointExit(nZoom, ConvertString("Time(Day)"));
		}
		break;
	case 3://周
		if (bEnter)
		{
			DrawPointEnter(nZoom, ConvertString("Time(Week)"));
		}
		else
		{
			DrawPointExit(nZoom, ConvertString("Time(Week)"));
		}
		break;
	case 4://月
		if (bEnter)
		{
			DrawPointEnter(nZoom, ConvertString("Time(Month)"));
		}
		else
		{
			DrawPointExit(nZoom, ConvertString("Time(Month)"));
		}
		break;
	case 5://季度
		if (bEnter)
		{
			DrawPointEnter(nZoom, ConvertString("Time(Season)"));
		}
		else
		{
			DrawPointExit(nZoom, ConvertString("Time(Season)"));
		}
		break;
	case 6://年
		if (bEnter)
		{
			DrawPointEnter(nZoom, ConvertString("Time(Year)"));
		}
		else
		{
			DrawPointExit(nZoom, ConvertString("Time(Year)"));
		}
		break;
	default:
		break;
	}

	if (bEnter)
	{
		m_pDC->SetTextColor(RGB(50, 200, 50));
		m_pDC->TextOut(m_rectRange.right + TEXT_OFFSET,  m_rectRange.bottom - TEXT_OFFSET*15
							, ConvertString("Enter Num(Green)"));
	}
	else
	{
		m_pDC->SetTextColor(RGB(200, 50, 50));
		m_pDC->TextOut(m_rectRange.right + TEXT_OFFSET, m_rectRange.bottom - TEXT_OFFSET*7
							, ConvertString("Exit Num(Red)"));	
	}
};

int CDrawFrame::GetZoom()
{
	DWORD dwCount = 0;
	for (int i = m_dwStartIndex; i < (int)m_dwCount; ++i)
	{
		if (m_dataShow.pstuNumberStat[i].nEnteredSubTotal > (int)dwCount)
		{
			dwCount = m_dataShow.pstuNumberStat[i].nEnteredSubTotal;
		}

		if (m_dataShow.pstuNumberStat[i].nExitedSubtotal > (int)dwCount)
		{
			dwCount = m_dataShow.pstuNumberStat[i].nExitedSubtotal;
		}
	}
	
	int nZoom = 1;
	if (dwCount<=80)
	{
		nZoom = 1;
	}
	else if (dwCount<=800)
	{
		nZoom = 10;
	}
	else if (dwCount<=8000)
	{
		nZoom = 100;
	}
	else if (dwCount<=80000)
	{
		nZoom = 1000;
	}
	else if (dwCount<=800000)
	{
		nZoom = 10000;
	}
	else if (dwCount<=8000000)
	{
		nZoom = 100000;
	}
	if (m_nMaxY < dwCount*Y_SPACE_LENGTH/(10*nZoom))
	{
		m_nMaxY = dwCount*Y_SPACE_LENGTH/(10*nZoom);
	}
	
	return nZoom;
};

bool CDrawFrame::CheckTimeLost(NET_TIME timeStart, NET_TIME timeEnd)
{
	bool bState = false;

	switch(m_nType)
	{
	case 0:
		if (abs((int(timeStart.dwMinute - timeEnd.dwMinute))) > 1
			&&abs(int(timeStart.dwHour-timeEnd.dwHour))==0)
		{
			bState = true;
		}
		break;
	case 1:
		if (abs(int(timeStart.dwHour - timeEnd.dwHour))>1
			&&abs(int(timeStart.dwDay - timeEnd.dwDay))==0)
		{
			bState = true;
		}
		break;
	case 2:
		if (abs(int(timeStart.dwDay - timeEnd.dwDay))>1
			&&abs(int(timeStart.dwMonth - timeEnd.dwMonth))==0)
		{
			bState = true;
		}
		break;
	case 3://周
		if (abs(int(timeStart.dwDay - timeEnd.dwDay))>7
			&&abs(int(timeStart.dwMonth - timeEnd.dwMonth))==0)
		{
			bState = true;
		}
		break;
	case 4://月
		if (abs(int(timeStart.dwMonth - timeEnd.dwMonth))>1
			&&abs(int(timeStart.dwYear-timeEnd.dwYear))==0)
		{
			bState = true;
		}
		break;
	case 5:
		if (abs(int(timeStart.dwMonth - timeEnd.dwMonth))>3
			&&abs(int(timeStart.dwYear-timeEnd.dwYear))==0)
		{
			bState = true;
		}
		break;
	case 6:
		if (abs(int(timeStart.dwYear - timeEnd.dwYear))>1)
		{
			bState = true;
		}
		break;
	default:
		bState = true;
	}
	return bState;
};

void CDrawFrame::DrawPointEnter(int nZoom, CString strShow)
{
	if (m_dwCount == 1)//只有1条数，不画线
	{
		return;
	}

	POINT pointStart,pointEnd;
	CString strStartTime;
	for (int nIndex = m_dwStartIndex; nIndex < int(m_dwStartIndex+m_dwCount-1); ++nIndex)
	{
		if (CheckTimeLost(m_dataShow.pstuNumberStat[nIndex].stuStartTime,
			m_dataShow.pstuNumberStat[nIndex+1].stuEndTime))
		{
			continue;
		}
		//开始点信息
		//计算进入时间坐标
		pointStart.x = m_rectRange.left + X_SPACE_LENGTH/10*(nIndex-m_dwStartIndex);
		//计算进入总数坐标
		pointStart.y = m_rectRange.bottom - 
			Y_SPACE_LENGTH/10 *m_dataShow.pstuNumberStat[nIndex].nEnteredSubTotal/nZoom;
		//结束点信息
		//计算进入时间坐标
		pointEnd.x = m_rectRange.left + X_SPACE_LENGTH/10*((nIndex+1)-m_dwStartIndex);
		//计算进入总数坐标
		pointEnd.y = m_rectRange.bottom - 
			Y_SPACE_LENGTH/10 *m_dataShow.pstuNumberStat[nIndex+1].nEnteredSubTotal/nZoom;

		m_pDC->MoveTo(pointStart);
		m_pDC->LineTo(pointEnd);
		m_pDC->Ellipse(pointStart.x-2, pointStart.y-2, pointStart.x+2, pointStart.y+2);
		m_pDC->Ellipse(pointEnd.x-2, pointEnd.y-2, pointEnd.x+2, pointEnd.y+2);
	}

	if (m_dwCount>0)
	{
		strStartTime.Format("%04d-%02d-%02d %02d:%02d:%02d", 
			m_dataShow.pstuNumberStat[m_dwStartIndex].stuStartTime.dwYear,
			m_dataShow.pstuNumberStat[m_dwStartIndex].stuStartTime.dwMonth,
			m_dataShow.pstuNumberStat[m_dwStartIndex].stuStartTime.dwDay,
			m_dataShow.pstuNumberStat[m_dwStartIndex].stuStartTime.dwHour,
			m_dataShow.pstuNumberStat[m_dwStartIndex].stuStartTime.dwMinute,
			m_dataShow.pstuNumberStat[m_dwStartIndex].stuStartTime.dwSecond);
	}

	m_pDC->TextOut(m_rectRange.right + TEXT_OFFSET, m_rectRange.bottom - TEXT_OFFSET
		, ConvertString(strShow));

	m_pDC->TextOut(m_rectRange.right + TEXT_OFFSET, m_rectRange.bottom + TEXT_OFFSET*2
		,ConvertString(strStartTime));
	
	CString str = ConvertString("Enter Num/Exit Num(Units:");
	CString strNum;
	strNum.Format("%d", nZoom);
	str += strNum;
	str += ")";
	m_pDC->TextOut(m_rectRange.left + TEXT_OFFSET*2, m_rectRange.top, str);
};

void CDrawFrame::DrawPointExit(int nZoom, CString strShow)
{
	if (m_dwCount == 1)//只有1条数，不画线
	{
		return;
	}

	POINT pointStart,pointEnd;
	for (int nIndex = m_dwStartIndex; nIndex < int(m_dwStartIndex+m_dwCount-1); ++nIndex)
	{
		if (CheckTimeLost(m_dataShow.pstuNumberStat[nIndex].stuStartTime,
			m_dataShow.pstuNumberStat[nIndex+1].stuEndTime))
		{
			continue;
		}
		//计算出时间坐标
		pointStart.x = m_rectRange.left + X_SPACE_LENGTH/10*(nIndex-m_dwStartIndex);
		//计算出总数坐标
		pointStart.y = m_rectRange.bottom - 
			Y_SPACE_LENGTH/10 *m_dataShow.pstuNumberStat[nIndex].nExitedSubtotal/nZoom;

		//计算出时间坐标
		pointEnd.x = m_rectRange.left + X_SPACE_LENGTH/10*((nIndex+1)-m_dwStartIndex);
		//计算出总数坐标
		pointEnd.y = m_rectRange.bottom - 
			Y_SPACE_LENGTH/10 *m_dataShow.pstuNumberStat[nIndex+1].nExitedSubtotal/nZoom;
		m_pDC->MoveTo(pointStart);
		m_pDC->LineTo(pointEnd);
		m_pDC->Ellipse(pointStart.x-2, pointStart.y-2, pointStart.x+2, pointStart.y+2);
		m_pDC->Ellipse(pointEnd.x-2, pointEnd.y-2, pointEnd.x+2, pointEnd.y+2);
	}
};


void CDrawFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()

	EnterCriticalSection(&m_criticalSection);
	if (m_bPaint)
	{
		DrawCoordinate();
		DrawFrame();
	}
	LeaveCriticalSection(&m_criticalSection);
}


void CDrawFrame::SetRectClient(const CRect & rect)
{
	m_rectClient = rect;
};


void CDrawFrame::InitData(NET_OUT_DOFINDNUMBERSTAT& dataShow, DWORD dwStartIndex, DWORD dwCount, int nType)
{
	EnterCriticalSection(&m_criticalSection);
	UninitData();

	m_dataShow.nBufferLen = dataShow.nBufferLen;
	m_dataShow.pstuNumberStat = (DH_NUMBERSTAT*)new char[dataShow.nBufferLen];
	memcpy(m_dataShow.pstuNumberStat, dataShow.pstuNumberStat, dataShow.nBufferLen);
	m_dataShow.nCount = dataShow.nCount;

	m_dwStartIndex = dwStartIndex;
	m_dwCount = dwCount;
	m_nType = nType;
	SetPaint(true);
	m_nMaxY = 0;
	LeaveCriticalSection(&m_criticalSection);
};


void CDrawFrame::UninitData()
{
	if (m_dataShow.pstuNumberStat)
	{
		delete [] m_dataShow.pstuNumberStat;
		m_dataShow.pstuNumberStat = NULL;
	}
	memset(&m_dataShow, 0, sizeof(NET_OUT_DOFINDNUMBERSTAT));

	m_dwStartIndex = 0;
	m_dwCount = 0;
	m_nType = -1;
	SetPaint(false);
};
void CDrawFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (m_bPaint && m_nMaxY != -1)
	{
		if ((LONG)point.x < m_rectRange.left || (LONG)point.x > m_rectRange.right
			|| (LONG)point.y > m_rectRange.bottom || m_rectRange.bottom -(LONG)point.y  > (LONG)m_nMaxY )
		{
			CString str;
			str.Format("point.y=%d, m_rectRange.bottom=%d, m_nMaxY=%d\r\n", point.y, m_rectRange.bottom, m_nMaxY);
			TRACE(str);
			return;
		}
		int nXLen = point.x - m_rectRange.left;
		if (0 < nXLen && nXLen < X_SPACE_LENGTH * 10)
		{
			int nXNum = nXLen / (X_SPACE_LENGTH / 10);
			if (nXNum > (int)m_dwCount)
			{
				return;
			}
			int nDataIndex = m_dwStartIndex + nXNum;
			if (!CheckTimeLost(m_dataShow.pstuNumberStat[nDataIndex].stuStartTime,
				m_dataShow.pstuNumberStat[nDataIndex + 1].stuEndTime))
			{
				this->GetParent()->PostMessage(WM_MSG_SHOW, 0
					, (LPARAM)&(m_dataShow.pstuNumberStat[nDataIndex].stuStartTime));
			}
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}
