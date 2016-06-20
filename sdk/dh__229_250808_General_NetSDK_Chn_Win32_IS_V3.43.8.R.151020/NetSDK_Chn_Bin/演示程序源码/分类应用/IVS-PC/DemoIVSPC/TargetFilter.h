#pragma once
#include "afxwin.h"


// CTargetFilter 对话框
class CTargetFilterPreview;


class CTargetFilter : public CDialog
{
	DECLARE_DYNAMIC(CTargetFilter)

public:
	CTargetFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTargetFilter();

	void ShowView();
	void Init(CFG_OBJECT_SIZEFILTER_INFO* pStObjectFileter, int nChannel);
	void FillData();
	CFG_OBJECT_SIZEFILTER_INFO* GetObjectFilter(void) { return m_pStObjectFileter; }

// 对话框数据
	enum { IDD = IDD_TARGET_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedBtnFilterOk();
	afx_msg void OnBnClickedBtnFilterCancel();	
private:
	CTargetFilterPreview *m_pTargetFilterPreview;
	int m_nChannel;
	int m_nMoudleIndex;
	CFG_OBJECT_SIZEFILTER_INFO* m_pStObjectFileter;

	CComboBox m_comboFilterPattern;
	CComboBox m_comboFilterType;
	CButton m_checkLenWidth;
};
