#if !defined(AFX_CONFIGCOVER_H__426AD004_1BE9_4A91_83A7_E50A813F4900__INCLUDED_)
#define AFX_CONFIGCOVER_H__426AD004_1BE9_4A91_83A7_E50A813F4900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigCover.h : header file
//
#include "dhnetsdk.h"

/////////////////////////////////////////////////////////////////////////////
// CConfigCover dialog

class CConfigCover : public CDialog
{
// Construction
public:
	void CleanAll();
	void InitDlgInfo(int nLength);
	CConfigCover(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigCover)
	enum { IDD = IDD_CONFIG_COVER };
	CComboBox	m_ctlVideoWidget;
	CComboBox	m_ctlCoverType;
	CListCtrl	m_ctlCoverLst;
	CComboBox	m_ctlChannel;
	BOOL        m_bEncodeEnable;
	BOOL        m_bPreViewEnable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigCover)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigCover)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonModify();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonReadall();
	afx_msg void OnSelchangeComboChanno();
	afx_msg void OnItemchangedListCovers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCancelMode();
//	afx_msg void OnEditchangeComboVideowidget();
	afx_msg void OnSelchangeComboVideowidget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	template <class T> void ShowVideoWidget(const T *pInfo, int i = 0)
	{
		if(NULL == pInfo)
		{
			return;
		}

		//m_ctlCoverLst.DeleteAllItems();

		//for (int i = 0; i < n; ++i)
		{
			CString strID;
			strID.Format("%d", i);

			//Rect Info
			CString	 strLeft;
			strLeft.Format("%d", pInfo[i].stuRect.nLeft);
			CString	 strRight;
			strRight.Format("%d", pInfo[i].stuRect.nRight);
			CString	 strTop;
			strTop.Format("%d", pInfo[i].stuRect.nTop);
			CString	 strBottom;
			strBottom.Format("%d", pInfo[i].stuRect.nBottom);

			//Blend Info;
			CString strPreviewMain;
			if(pInfo[i].bPreviewBlend)
			{
				strPreviewMain = ConvertString("true");
			}
			else
			{
				strPreviewMain = ConvertString("false");
			}
			
			CString strBlendMain;
			if(pInfo[i].bEncodeBlend)
			{
				strBlendMain = ConvertString("true");
			}
			else
			{
				strBlendMain = ConvertString("false");
			}

			CString strBlendExtra1;
			if(pInfo[i].bEncodeBlendExtra1)
			{
				strBlendExtra1 = ConvertString("true");
			}
			else
			{
				strBlendExtra1 = ConvertString("false");
			}

			CString strBlendExtra2;
			if(pInfo[i].bEncodeBlendExtra2)
			{
				strBlendExtra2 = ConvertString("true");
			}
			else
			{
				strBlendExtra2 = ConvertString("false");
			}

			CString strBlendExtra3;
			if(pInfo[i].bEncodeBlendExtra3)
			{
				strBlendExtra3 = ConvertString("true");
			}
			else
			{
				strBlendExtra3 = ConvertString("false");
			}

			CString strBlendBlendSnapshot;
			if(pInfo[i].bEncodeBlendSnapshot)
			{
				strBlendBlendSnapshot = ConvertString("true");
			}
			else
			{
				strBlendBlendSnapshot = ConvertString("false");
			}

			//Front Color Info
			CString strFRed;
			strFRed.Format("%d", pInfo[i].stuFrontColor.nRed);
			CString strFGreen;
			strFGreen.Format("%d", pInfo[i].stuFrontColor.nGreen);
			CString strFBule;
			strFBule.Format("%d", pInfo[i].stuFrontColor.nBlue);
			CString strFAlpha;
			strFAlpha.Format("%d", pInfo[i].stuFrontColor.nAlpha);

			//Back Color Info
			CString strBRed;
			strBRed.Format("%d", pInfo[i].stuBackColor.nRed);
			CString strBGreen;
			strBGreen.Format("%d", pInfo[i].stuBackColor.nGreen);
			CString strBBlue;
			strBBlue.Format("%d", pInfo[i].stuBackColor.nBlue);
			CString strBAlpha;
			strBAlpha.Format("%d", pInfo[i].stuBackColor.nAlpha);
			
			int nIndex = m_ctlCoverLst.GetItemCount();
			m_ctlCoverLst.InsertItem(LVIF_TEXT|LVIF_STATE,nIndex,strID,0,LVIS_SELECTED,0,0);
			
			m_ctlCoverLst.SetItemText(nIndex,1,strLeft);
			m_ctlCoverLst.SetItemText(nIndex,2,strTop);
			m_ctlCoverLst.SetItemText(nIndex,3,strRight);
			m_ctlCoverLst.SetItemText(nIndex,4,strBottom);
			m_ctlCoverLst.SetItemText(nIndex, 5, strPreviewMain);
			m_ctlCoverLst.SetItemText(nIndex, 6, strBlendMain);
			m_ctlCoverLst.SetItemText(nIndex, 7, strBlendExtra1);
			m_ctlCoverLst.SetItemText(nIndex, 8, strBlendExtra2);
			m_ctlCoverLst.SetItemText(nIndex, 9, strBlendExtra3);
			m_ctlCoverLst.SetItemText(nIndex, 10, strBlendBlendSnapshot);
			m_ctlCoverLst.SetItemText(nIndex, 11, strFRed);
			m_ctlCoverLst.SetItemText(nIndex, 12, strFGreen);
			m_ctlCoverLst.SetItemText(nIndex, 13, strFBule);
			m_ctlCoverLst.SetItemText(nIndex, 14, strFAlpha);
			m_ctlCoverLst.SetItemText(nIndex, 15, strBRed);
			m_ctlCoverLst.SetItemText(nIndex, 16, strBGreen);
			m_ctlCoverLst.SetItemText(nIndex, 17, strBBlue);
			m_ctlCoverLst.SetItemText(nIndex, 18, strBAlpha);
		}
		
		UpdateData(FALSE);
	}
	void ShowVideoWidgetChannelTitle(AV_CFG_VideoWidgetChannelTitle *pChannelTitleInfo);
	void ShowVideoWidgetTimeTitle(AV_CFG_VideoWidgetTimeTitle *pTimeTitleInfo);
	void ShowVideoWidgetCover(AV_CFG_VideoWidgetCover *pVideoWidgetCover, int nNum);

	template <class T> void SaveVideoWidget(T *pInfo, int *nNum = NULL)
	{
		UpdateData(TRUE);
		if(NULL == pInfo)
		{
			return ;
		}
		
		int nCount = m_ctlCoverLst.GetItemCount();
		nCount = nCount > AV_CFG_Max_Video_Widget_Cover ? AV_CFG_Max_Video_Widget_Cover: nCount;
		if (nNum)
		{
			*nNum = nCount;
		}

		int i = 0;
		for(i = 0; i < nCount; i++)
		{
			CString strTmp;

			//Rect Info
			strTmp = m_ctlCoverLst.GetItemText(i, 1);
			pInfo[i].stuRect.nLeft = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 2);
			pInfo[i].stuRect.nTop = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 3);
			pInfo[i].stuRect.nRight = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 4);
			pInfo[i].stuRect.nBottom = atol(strTmp);
			
			//Blend Info
			strTmp = m_ctlCoverLst.GetItemText(i, 5);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				pInfo[i].bPreviewBlend = 1;
			}
			else
			{
				pInfo[i].bPreviewBlend = 0;
			}

			strTmp = m_ctlCoverLst.GetItemText(i, 6);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				pInfo[i].bEncodeBlend = 1;
			}
			else
			{
				pInfo[i].bEncodeBlend = 0;
			}
			
			strTmp = m_ctlCoverLst.GetItemText(i, 7);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				pInfo[i].bEncodeBlendExtra1 = 1;
			}
			else
			{
				pInfo[i].bEncodeBlendExtra1 = 0;
			}
			
			strTmp = m_ctlCoverLst.GetItemText(i, 8);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				pInfo[i].bEncodeBlendExtra2 = 1;
			}
			else
			{
				pInfo[i].bEncodeBlendExtra2 = 0;
			}
			
			strTmp = m_ctlCoverLst.GetItemText(i, 9);
			if(strTmp == "true" || strTmp  == ConvertString("true"))
			{
				pInfo[i].bEncodeBlendExtra3 = 1;
			}
			else
			{
				pInfo[i].bEncodeBlendExtra3 = 0;
			}
			
			strTmp = m_ctlCoverLst.GetItemText(i, 10);
			if(strTmp == "true" || strTmp == ConvertString("true"))
			{
				pInfo[i].bEncodeBlendSnapshot = 1;
			}
			else
			{
				pInfo[i].bEncodeBlendSnapshot = 0;
			}
			
			// Front color
			strTmp = m_ctlCoverLst.GetItemText(i, 11);
			pInfo[i].stuFrontColor.nRed = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 12);
			pInfo[i].stuFrontColor.nGreen = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 13);
			pInfo[i].stuFrontColor.nBlue = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 14);
			pInfo[i].stuFrontColor.nAlpha = atol(strTmp);
			
			// Back  color
			strTmp = m_ctlCoverLst.GetItemText(i, 15);
			pInfo[i].stuBackColor.nRed = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 16);
			pInfo[i].stuBackColor.nGreen = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 17);
			pInfo[i].stuBackColor.nBlue = atol(strTmp);
			strTmp = m_ctlCoverLst.GetItemText(i, 18);
			pInfo[i].stuBackColor.nAlpha = atol(strTmp);
		}
	}
	void SaveVideoWidgetChannelTitle(AV_CFG_VideoWidgetChannelTitle *pChannelTitleInfo);
	void SaveVideoWidgetTimeTitle(AV_CFG_VideoWidgetTimeTitle *pTimeTitleInfo);
	void SaveVideoWidgetCover(AV_CFG_VideoWidgetCover *pVideoWidgetCover, int *nNum);
	BOOL JudgeColor(int nColor);
	BOOL JudgeCoordinate(int nCoordinate);


	int m_nCurChannel;
	int m_nChannelCount;
	DHDEV_VIDEOCOVER_CFG m_channelCoverInfo[32];
	void SaveChannelInfo(int nNum,int nVideoWidget);
	void InitListView();
	BOOL m_bNewProtocol;//32б╥ртио
	AV_CFG_VideoWidget *m_pstVideoWidget;
	int	 m_nVideoWidget;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGCOVER_H__426AD004_1BE9_4A91_83A7_E50A813F4900__INCLUDED_)
