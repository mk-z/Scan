// DrawObject1.cpp: implementation of the CDrawObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Video Analyse Configuration.h"
#include "DrawObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawObject::CDrawObject()
{

}

CDrawObject::~CDrawObject()
{

}

/************************************************************************/
/*                               line module                            */
/************************************************************************/

CDrawLines::CDrawLines(POINT* stuPoints, int nPointsNum, int nType)
{
	//m_stuLinePoints = stuPoints;
	memcpy(m_stuLinePoints, stuPoints, sizeof(POINT) * nPointsNum);
	m_nPointNum = nPointsNum;
	m_nType = nType;
	m_rightRoadLine = NULL;
	m_leftRoadLine = NULL;

	SetPenStly(m_nType);
}

CDrawLines::~CDrawLines()
{

}

void CDrawLines::SetPenStly(int nType)
{
	switch(m_nType)
	{
	case eRoadLine:
		{
			m_colorFore = ROADLINECOLOR;
		}
		break;
	case eDetectLine:
		{
			m_colorFore = DEDECTLINECOLOR;
		}
		break;
	case eDetectArea:
		{
			m_colorFore = DETECTREGIONCOLOR;
		}
	case eStopLine:
		{
			m_colorFore = DEDECTLINECOLOR;
		}
		break;
	case ePreLine:
		{
			m_colorFore = PRELINECOLOR;
		}
		break;
	case ePostLine:
		{
			m_colorFore = POSTLINECOLOR;
		}
		break;
	case eStopLightRegion:
		{
			m_colorFore = REDLIGHTREGIONCOLOR;
		}
	case eTrackRegion:
		{
			m_colorFore = TRACKREGIONCOLOR;
		}
		break;
	}
}

void CDrawLines::DrawSelf(CDC* pDC)
{
	if (pDC == NULL)
	{
		return;
	}

	CPen *pOldPen = pDC->GetCurrentPen();

	CPen newPen;
	if (m_nType == eTrackRegion)
	{
		newPen.CreatePen(PS_DOT, 2, m_colorFore);
	}
	else
	{
		newPen.CreatePen(PS_SOLID, 3, m_colorFore);
	}
	
	pDC->SelectObject(&newPen);

	for(int i = 0; i < m_nPointNum - 1; i++)
	{
		pDC->MoveTo(m_stuLinePoints[i]);
		pDC->LineTo(m_stuLinePoints[i + 1]);
	}
	
	if (m_nType == eStopLightRegion || m_nType == eDetectArea || m_nType == eTrackRegion)
	{
		pDC->MoveTo(m_stuLinePoints[m_nPointNum - 1]);
		pDC->LineTo(m_stuLinePoints[0]);
	}

	if (m_nType == eRoadLine)
	{
		Paint_Arrow(m_stuLinePoints[m_nPointNum - 2],m_stuLinePoints[m_nPointNum - 1], pDC->GetSafeHdc());
	}
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();

	if (m_rightRoadLine != NULL && m_leftRoadLine != NULL)
	{	
		
		newPen.CreatePen(PS_DOT, 1, ATATCHLINECOLOR);
		pDC->SelectObject(&newPen);
		pDC->MoveTo(m_rightRoadLine->m_stuLinePoints[0]);
		pDC->LineTo(m_leftRoadLine->m_stuLinePoints[0]);

		int nPointNum = m_rightRoadLine->m_nPointNum;
		pDC->MoveTo(m_rightRoadLine->m_stuLinePoints[nPointNum - 1]);
		nPointNum = m_leftRoadLine->m_nPointNum;
		pDC->LineTo(m_leftRoadLine->m_stuLinePoints[nPointNum - 1]);
	}
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();
}

void CDrawLines::Paint_Arrow(POINT startPoint,POINT endPoint,HDC hDc_Paint_Arrow)
{
	double dThetaArrow;
	double dOffsetX1;
	double dOffsetY1;
	BYTE ArrowLength=10;
	if ( endPoint.x<startPoint.x )
	{
		dThetaArrow=atan((double) (startPoint.y-endPoint.y)/(startPoint.x-endPoint.x));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow-3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow-3.14159/6);
		
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y,NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow+3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow+3.14159/6);
		
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
	}
	else if ( endPoint.x>startPoint.x )
	{
		dThetaArrow=atan((double) (startPoint.y-endPoint.y)/(startPoint.x-endPoint.x));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow-3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow-3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x-dOffsetX1),(int)(endPoint.y-dOffsetY1));
		dOffsetX1=ArrowLength*cos(dThetaArrow+3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow+3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x-dOffsetX1),(int)(endPoint.y-dOffsetY1));
	}
	else
	{
		startPoint.x++;
		dThetaArrow=atan((double) (startPoint.y-endPoint.y)/(startPoint.x-endPoint.x));
		
		dOffsetX1=ArrowLength*cos(dThetaArrow-3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow-3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
		dOffsetX1=ArrowLength*cos(dThetaArrow+3.14159/6);
		dOffsetY1=ArrowLength*sin(dThetaArrow+3.14159/6);
		MoveToEx(hDc_Paint_Arrow,endPoint.x,endPoint.y, NULL);
		LineTo(hDc_Paint_Arrow,(int)(endPoint.x+dOffsetX1),(int)(endPoint.y+dOffsetY1));
	}
}

/************************************************************************/
/*                           text module                                */
/************************************************************************/

CDrawText::CDrawText(CString strText, RECT stuRect, float fValue)
{
	m_strText = strText;
	m_Rect.bottom = stuRect.bottom;
	m_Rect.left = stuRect.left;
	m_Rect.right = stuRect.right;
	m_Rect.top = stuRect.top;

	m_fValue = fValue;
}

CDrawText::CDrawText(CString strText, RECT stuRect, char fValue[][32], int nListSize)
{
	m_strText = strText;
	m_Rect.bottom = stuRect.bottom;
	m_Rect.left = stuRect.left;
	m_Rect.right = stuRect.right;
	m_Rect.top = stuRect.top;
	

	m_strValue = fValue;
	m_nListSize = nListSize;
}

CDrawText::~CDrawText()
{
	for(int i = 0; i < 32; i++)
	{
		if (m_strValue[i] != NULL)
		{
			char *pChar = m_strValue[i];
			delete[] pChar;
		}
	}
}

void CDrawText::DrawSelf(CDC* pDC)
{
	if (pDC == NULL)
	{
		return;
	}

	char szText[1024] = {0};
	int nLen = 0;
	CString strText = ConvertString(m_strText);
	nLen = strText.GetLength();
	memcpy(szText, strText, nLen);
	if (m_strText == METRICDISTANCE)
	{
		sprintf(szText + nLen, ": %.3f m ", m_fValue);
	}
	else if (m_strText == SPEEDUPPERLIMIT || m_strText == SPEEDLOWERLIMIT)
	{
		sprintf(szText + nLen, ": %.0f km ", m_fValue);
	}
	else if (m_strText == PERIOD || m_strText == MINDURATION)
	{
		sprintf(szText + nLen, ": %.0f s ", m_fValue);
	}
	else if (m_strText == FSUPPERLIMIT)
	{
		sprintf(szText + nLen, ": %.0f /s ", m_fValue);
	}
	else if (m_strText == NSUPPERLIMIT)
	{
		sprintf(szText + nLen, ": %.0f  ", m_fValue);
	}
	else if (m_strText == ROADDIRECTION)
	{
		int nDirect = m_fValue;
		switch(nDirect)
		{
		case 0:
			{
				strcat(szText, ConvertString(": Straight"));
			}
			break;
		case 1:
			{
				strcat(szText, ConvertString(": Left"));
			}
			break;
		case 2:
			{
				strcat(szText, ConvertString(": LeftStraight"));
			}
			break;
		case 3:
			{
				strcat(szText, ConvertString(": Right"));
			}
			break;
		case 4:
			{
				strcat(szText, ConvertString(": RighStraight"));
			}
			break;
		}
	}
	else if (m_strText == PLATENUMBER)
	{
		if (m_fValue == 0)
		{
			strcat(szText, ConvertString(": odd"));
		}
		else if (m_fValue == 1)
		{
			strcat(szText, ConvertString(": even"));
		}
		else if (m_fValue == 2)
		{
			strcat(szText, ConvertString(": both"));
		}
	}
	else if (m_strText == DIRECTIONLINE)
	{
		if (m_fValue == 0)
		{
			strcat(szText, ConvertString(": LeftToRight"));
		}
		else if (m_fValue == 1)
		{
			strcat(szText, ConvertString(": RightToLeft"));
		}
		else if (m_fValue == 2)
		{
			strcat(szText, ConvertString(": Both"));
		}
	}
	else if (m_strText == DIRECTIONREGION)
	{
		if (m_fValue == 0)
		{
			strcat(szText, ": enter");
		}
		else if (m_fValue == 1)
		{
			strcat(szText, ": leave");
		}
		else if (m_fValue == 2)
		{
			strcat(szText, ": enter and leave");
		}
	}
	else if (m_strText == TURNENABLE)
	{
		if (m_fValue == 0)
		{
			strcat(szText, ConvertString(": not Enable"));
		}
		else if (m_fValue == 1)
		{
			strcat(szText, ConvertString(": Enable"));
		}
	}
	else if (m_strText == VEHICLETYPE || m_strText == VEHICLESIZE || m_strText == PLATETYPE)
	{
		strcat(szText, ": ");
		for (int i = 0; i < m_nListSize; i++)
		{
			strcat(szText, m_strValue[i]);
			strcat(szText, ", ");
		}
	}
	else if (m_strText != TITLE)
	{
		sprintf(szText + nLen, ": %.0f ", m_fValue);
	}

	pDC->DrawText(szText, &m_Rect, DT_RIGHT);
}
