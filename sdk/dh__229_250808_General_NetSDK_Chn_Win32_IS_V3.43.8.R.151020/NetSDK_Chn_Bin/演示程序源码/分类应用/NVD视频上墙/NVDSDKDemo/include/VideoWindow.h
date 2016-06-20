// VideoWindow.h: interface for the CVideoWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOWINDOW_H__8F66A9A5_DA81_4191_892F_CBC8E0A7A1A2__INCLUDED_)
#define AFX_VIDEOWINDOW_H__8F66A9A5_DA81_4191_892F_CBC8E0A7A1A2__INCLUDED_

#include "WndContainer.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////

typedef enum __SPLIT_TYPE
{
	SPLIT1 = 1,
	SPLIT4 = 4,
	SPLIT9 = 9,
	SPLIT16 = 16,
} SPLIT_TYPE;

#define GET_PARENT_DIALOG			((CNVDSDKDemoDlg *)(this->GetParent()))

//////////////////////////////////////////////////////////////////////////
class CVideoWindow : public CWndContainer
{
public:
	CVideoWindow();
	virtual ~CVideoWindow();

public:
	int SetShowWindow(SPLIT_TYPE nMain, SPLIT_TYPE nSub=SPLIT4);

	CWnd* GetShowWindow(int nMain, int nSub);

	CWnd* GetActiveWindow();

	void SetActiveWindow(int nMain, int nSub);

	int GetMonitorCurWndNum(int nMain);

	int GetMonitorWndNum(int nMain);

	void SetMonitorMultiScreen(int nMain, BOOL bFlag);

	void SetWndFlash(int nMain, int nSub, BOOL bFlag);

	int m_nCurMonitorID;
	int m_nCurWndID;

public:
	virtual void OnVideoLButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void OnVideoLButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void OnVideoLButtonDblClk(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoRButtonDown(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoRButtonUp(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoMove(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);
	virtual void onVideoMoving(int nMonitorID, int nWndID, WPARAM wParam, LPARAM lParam);

};

#endif // !defined(AFX_VIDEOWINDOW_H__8F66A9A5_DA81_4191_892F_CBC8E0A7A1A2__INCLUDED_)
