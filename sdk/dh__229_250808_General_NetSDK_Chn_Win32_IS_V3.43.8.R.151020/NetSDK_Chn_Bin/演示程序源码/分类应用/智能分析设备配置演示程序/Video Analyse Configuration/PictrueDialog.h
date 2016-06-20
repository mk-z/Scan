#if !defined(AFX_PICTRUEDIALOG_H__15CD1931_E4D5_42BF_8B50_75A5A45639A3__INCLUDED_)
#define AFX_PICTRUEDIALOG_H__15CD1931_E4D5_42BF_8B50_75A5A45639A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PictrueDialog.h : header file
//
#pragma  warning (disable:4786)
#include <list>
#include <map>
#include "DrawObject.h"
#include <vector>
using std::list;
#define		PICTURE_BACK_COLOR	RGB(128, 128, 128)
#define     TEXT_LEFT_START    10
#define     TEXT_TOP_START     10
#define     TEXT_HEIGHT        30
#define     TEXT_WIDTH         200

typedef std::map<int, list<CDrawObject*> > MAPCROSSLINE;
typedef list<CDrawObject*>                 LISTLINE;
typedef CDrawObject*                       PCDRAWOBJ;
typedef  std::vector<CPoint*>              VTPOINT;

typedef std::map<CString, MAPCROSSLINE*>    MAPRULES;
/////////////////////////////////////////////////////////////////////////////
// CPictrueDialog dialog

class CPictrueDialog : public CDialog
{
// Construction
public:
	CPictrueDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPictrueDialog();

	void DeleteUnfullLines();
	void DeleteRecourse(void);
	void SetObjsMaxNumber(int nRoadLine, int nDetectLine, int nStopLine,
		int nPreLine, int nPostLine, int nDetectRegion, int nRedLightRegion,
		int nTrackRegion);
	BOOL ValidateObjCount(void);
	void AddDrawLines(POINT *pLinePoints, int nPointNum, int nType);
	void AddDrawLines(POINT* pLeftPoints, int nLeftPointNum, POINT* pRightPoints, 
		int nRightPointNum,int nType);
	void AddDrawText(CString strText, float fValue);
	void AddDrawText(CString strText, POINT TOP);
	void AddDrawText(CString strText, char fValue[][32], int nSize);
	void DrawBackGround(CDC *pDC);
	void DoDraw(CDC *pDC, BOOL bToScreen);
	void AddRules(CString strName, MAPCROSSLINE* pRuleLines);
	void DeletRule(CString strName);

	static void CALLBACK DecodeDrawFunc(long nPort,HDC hDc,LONG nUser);


// Dialog Data
	//{{AFX_DATA(CPictrueDialog)
	enum { IDD = IDD_PICTURE_SHOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictrueDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPictrueDialog)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()


public:
	MAPRULES      m_mRules;            
	MAPCROSSLINE  m_DrawObjectList;    
	int           m_emSelectScene;	  
	CRect         m_Size;              
    int           m_nMaxDetectLine;    
	int           m_nMaxRoadLine;      
	int           m_nMaxStopLine;     
	int           m_nMaxPreLine;       
	int           m_nMaxPostLine;     
	int           m_nMaxRedRegion;    
	int           m_nMaxDetectRegion;  
	int           m_nMaxTrackRegion;   

private:
	CDrawObject*  m_pCurrentObj;       
	CDrawLines*   m_pFirstLine;       
	CDrawLines*   m_pSencondLine;     

	CRect GetRect(CDrawLines* pLine);
	POINT GetCrossPoint(POINT p1, POINT p2, POINT q1, POINT q2);
	BOOL IsLineSegmentCross(POINT pFirst1, POINT pFirst2, POINT pSecond1, POINT pSecond2);
	BOOL SetCross(CDrawLines* pCurrentLine,int emSelectScene);
	BOOL ValidateAngle(CRect &rt);
	BOOL ValidateRect(CRect& rtLeft, CRect& rtRight);
	BOOL LineIntersectLine(CVSPoint* ptOneFirst, CVSPoint* ptTwoFirst, 
		CVSPoint* ptOneSecond, CVSPoint* ptTwoSecond);
	double Multiply(CVSPoint *sp,CVSPoint* ep,CVSPoint* op);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTRUEDIALOG_H__15CD1931_E4D5_42BF_8B50_75A5A45639A3__INCLUDED_)
