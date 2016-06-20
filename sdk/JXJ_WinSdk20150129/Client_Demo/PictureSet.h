#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPictureSet 对话框

class CPictureSet : public CDialog
{
	DECLARE_DYNAMIC(CPictureSet)

public:
	CPictureSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPictureSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_PICTURESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CComboBox			m_comChannel;
	CSliderCtrl			m_Compare;
	CSliderCtrl			m_Light;
	CSliderCtrl			m_Gray;
	CSliderCtrl			m_Saturation;
	CSliderCtrl			m_Shar;
	CButton				m_Image;
	CButton				m_RollTurn;
	CComboBox			m_Flicker;
	CComboBox			m_WhiteType;
	CSliderCtrl			m_White_Red;
	CSliderCtrl			m_White_Blue;
	CComboBox			m_LightType;
	CSliderCtrl			m_LightWakeUp;
	CComboBox			m_AutoLight;
	CComboBox			m_OutSprat;
	CComboBox			m_Rote;
	CComboBox			m_bShutter;
	CSliderCtrl			m_WidthState;
	CSliderCtrl			m_JiBianCheck;


	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonFlash();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	

	void		SliderCtrlSetPos();
	BOOL		PreTranslateMessage(MSG* pMsg); //按钮按下和松开
	int			ReFreshDisPlayWindow();
	int			ReFreshPictureWindow();

private:
	JDisplayParameter		m_display;
	JPictureInfo			m_picture;
};
