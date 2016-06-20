#if !defined(AFX_CONFIGRULES_H__25B6EF32_EF48_4D8B_BED0_83118C4CD313__INCLUDED_)
#define AFX_CONFIGRULES_H__25B6EF32_EF48_4D8B_BED0_83118C4CD313__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigRules.h : header file
//
#include "PictrueDialog.h"
#include "Common.h"
#include "DrawObject.h"
#include <map>

typedef struct
{
	DWORD dwObjType;
	CWnd* pWnd;
}RULEDLGINFO;

typedef     std::map<int, RULEDLGINFO*> MAPWND;
#define     PICTRUE_REAL_SIZE   8192
#define     MAX_CHANNEL_NUM     16
/////////////////////////////////////////////////////////////////////////////
// CConfigRules dialog

class CConfigRules : public CDialog
{
// Construction
public:
	CConfigRules(CWnd* pParent = NULL);   // standard constructor
	~CConfigRules();

// Dialog Data
	//{{AFX_DATA(CConfigRules)
	enum { IDD = IDD_CONFIG_RULES };
	CTreeCtrl	m_ctRuleTree;
	CComboBox	m_cbChannel;
	CString	m_strAddRuleName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigRules)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigRules)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSaveR();
	afx_msg void OnButtonRefreshR();
	afx_msg void OnSelchangeComboChannelR();
	afx_msg void OnButtonAddruleR();
	afx_msg void OnButtonDeletruleR();
	afx_msg void OnSelchangedTreeRules(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	LLONG m_lLogID;
	LLONG m_lRealPlayHandle;
	CRect m_childRect;
	int m_nChannelCount;
	int m_nCurrentChannel;
	int m_nMaxRuleNum;
	int m_nMaxRuleStructSize;
	HTREEITEM m_hPreSelectNode;
	// 防止崩溃
	CRITICAL_SECTION	m_csRuleTree;
	std::map<HTREEITEM,DWORD>   m_mapTreeData;

	CFG_ANALYSERULES_INFO m_gChannelRules[MAX_CHANNEL_NUM];
	CWnd* m_dlgRule;

	void GetProportion(CRect stuWindowSize);
	void GetDeviceCap(void);
	void Refresh(void);
	HTREEITEM FindTreeNode(DWORD Type);
	void CleanRuleTree();
	void InputRuleInfo(MAPCROSSLINE &pMapLine, void* pRuleInfo, DWORD dwRuleType,
		float fProportionX, float fProportionY);
	int GetNodeChildCount(HTREEITEM hRootItem);
	void ShowChannelRule(int nChannelId);
	void ShowTreeNodeInfo(HTREEITEM hTreeNode);
	BOOL SaveChannelRuleInfo(int nChannelId);
	BOOL SaveTreeNodeInfo(HTREEITEM hTreeNode);
	void InsertChildNode2EvtTree(int nChannelId,int &nHaveReadLen);

	/* 树控件管理数据存在崩溃问题*/
	DWORD MyGetItemData(HTREEITEM hItem);
	BOOL MySetItemData(HTREEITEM hItem, DWORD dwData);
	BOOL MyDeleteItem(HTREEITEM hItem);
	HTREEITEM MyInsertItem(LPCTSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter);
public:
	int m_nSupportedObjTypeNum;
	char m_gObjectTypeName[MAX_OBJECT_LIST_SIZE][MAX_NAME_LEN];      // device supported object types
	int	m_nSupportedRulesNum;							 
	DWORD m_gRulesTypes[MAX_RULE_LIST_SIZE];						 // device supported event types
	float m_fProportionX;      
	float m_fProportionY;
	CPictrueDialog m_stuPicShow;

	CPictrueDialog* GetPictrueWnd();
	void Init(int nChannelCount);
	void Clear();
	void StopRealPlay();
	void StartRealPay();
	int GetRulesMaxStructSize(DWORD *pRulesTypes, int nRuleNum);
	BOOL RuleNameHasExit(CString strNewRuleName, CString strCurrentRuleName);
	HTREEITEM GetSelectEventNode();
	void InPutExitLinesToPicture(CPictrueDialog* pPicShow, HTREEITEM hTreeNode, 
		float fProportionX, float fProportionY);

	friend void CALLBACK ChannelAutoDraw(LLONG lLoginID, LLONG lPlayHandle, HDC hDC, LDWORD dwUser);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGRULES_H__25B6EF32_EF48_4D8B_BED0_83118C4CD313__INCLUDED_)
