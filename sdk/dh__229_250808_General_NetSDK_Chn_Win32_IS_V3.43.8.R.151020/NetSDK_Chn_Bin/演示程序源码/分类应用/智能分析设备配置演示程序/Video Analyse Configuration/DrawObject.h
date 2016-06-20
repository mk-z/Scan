// DrawObject.h: interface for the CDrawObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWOBJECT_H__B1E2A730_1FFE_4B85_B22A_EB63D11EAF15__INCLUDED_)
#define AFX_DRAWOBJECT_H__B1E2A730_1FFE_4B85_B22A_EB63D11EAF15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <AFXTEMPL.H>
#include <math.h>
#include <map>
#include "Common.h"

#define ROADLINECOLOR           RGB(252, 233, 2)       
#define DEDECTLINECOLOR         RGB(255, 0, 0)       
#define DETECTREGIONCOLOR       RGB(0, 255, 0)       
#define STOPLINECOLOR           RGB(198, 165, 42)    
#define PRELINECOLOR            RGB(42, 58, 239)     
#define POSTLINECOLOR           RGB(53, 120, 80)     
#define REDLIGHTREGIONCOLOR     RGB(120, 43, 180)   
#define ATATCHLINECOLOR         RGB(13, 237, 242)       
#define TRACKREGIONCOLOR        RGB(152, 152,0)      

#define     ROADNUMBER          "RoadNumber"
#define     SPEEDWEIGHT         "SpeedWeight"
#define     METRICDISTANCE      "MetricDistance"
#define     SPEEDUPPERLIMIT     "SpeedUpperLimit"
#define     SPEEDLOWERLIMIT     "SpeedLowerLimit"
#define     ROADDIRECTION       "RoadDirection"
#define     TURNENABLE          "TurnEnable"
#define     VEHICLESIZE         "VehcleSize"
#define     VEHICLETYPE         "VehcleType"
#define     PLATETYPE           "PlateType"
#define     PLATENUMBER         "PlateNumber"
#define     DIRECTIONLINE       "DirectionLine"
#define     DIRECTIONREGION     "DirectionRegion"
#define     PERIOD              "Period"
#define     FSUPPERLIMIT        "FSUpperLimit"
#define     NSUPPERLIMIT        "NSUpperLimit"
#define     MINDURATION         "MinDuration"
#define     TITLE               "title"

class CDrawObject  
{
public:
	CDrawObject();
	virtual ~CDrawObject();
	virtual void DrawSelf(CDC* pDC)=0;
};

class CDrawLines:public CDrawObject
{
public:
	CDrawLines(POINT* stuPoints, int nPointsNum, int nType);
	virtual ~CDrawLines();
	virtual void DrawSelf(CDC* pDC);
	void SetPenStly(int nLineType);
	void Paint_Arrow(POINT startPoint,POINT endPoint,HDC hDc_Paint_Arrow);


	POINT m_stuLinePoints[20];
	int m_nPointNum;
	int m_nType;
	CDrawLines* m_rightRoadLine;
	CDrawLines* m_leftRoadLine;

private:
	CPen       m_stuSolidPen;
	CPen       m_stuDotPen;
	COLORREF   m_colorFore;
};

class CDrawText:public CDrawObject  
{
public:
	CDrawText(CString strText, RECT stuRect, float fValue);
	CDrawText(CString strText, RECT stuRect, char strValue[][32], int nList);
	virtual ~CDrawText();
	virtual void DrawSelf(CDC* pDC);

public:
	CString m_strText;
	float m_fValue;
	char (*m_strValue)[32];
	int m_nListSize;
	RECT m_Rect;
};
#endif // !defined(AFX_DRAWOBJECT1_H__B1E2A730_1FFE_4B85_B22A_EB63D11EAF15__INCLUDED_)
