#pragma once
#include "HerdAnalyseScreen.h"
#include "HerdTimeDlg.h"
#include "afxwin.h"
#include "VideoTime.h"
#include "afxcmn.h"

// CHerdAnalyse 对话框

class CHerdAnalyse : public CDialog
{
	DECLARE_DYNAMIC(CHerdAnalyse)

public:
	CHerdAnalyse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHerdAnalyse();

// 对话框数据
	enum { IDD = IDD_DIALOG_HerdAnalyse };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnCbnSelchangeComboQuadr();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonTimeset();


	BOOL PreTranslateMessage(MSG* pMsg); //按钮按下和松开
	void SetWndData();
	void ShowVideoTime(int iIndex);
	void SliderCtrlSetPos();


	CHerdAnalyseScreen	m_herdAnalyseScreen;
	CVideoTime		m_cVideoTime;
	
	CButton			m_enable;
	CComboBox		m_upInterval;
	CComboBox		m_quadr;
	CEdit			m_quadrID;
	CEdit			m_quadrName;
	CEdit			m_inner_percent;
	CEdit			m_outer_percent;
	CSliderCtrl		m_edge;
	CSliderCtrl		m_binary;
	CSliderCtrl		m_blur;
	CSliderCtrl		m_contour;
	CSliderCtrl		m_dilate;
	CSliderCtrl		m_erode;
	CSliderCtrl		m_hierarchy;
	CSliderCtrl		m_mask;

};
