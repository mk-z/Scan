#pragma once
#include <IOSTREAM>
#include <MAP>

// 树控件操作关联数据结构
struct STtreeData
{
	std::string   strName;       // 节点名称
	BOOL          bCheck;        // 是否选中复选框
	struct STtreeData* pBrother; // 兄弟节点
	struct STtreeData* pChild;   // 孩子节点

	void *        pData;         // 节点数据关联面板类
	DWORD         dwMaskControls; // 控制面板上的控件显示
	DWORD         dwProfile;      // 节点关联的参数表指针
};

class CVirtTree:public CTreeCtrl
{
public:
	CVirtTree(CDialog* pParent = NULL);
	~CVirtTree();
public:
	int ResetTree(const STtreeData &stTree);
	void SetChildCheck(HTREEITEM item, BOOL bCheck);
	void SetParentCheck(HTREEITEM item, BOOL bCheck);

	int AddNodeChild(STtreeData & stTree, const STtreeData & stChild);
	int AddNodeBrother(STtreeData & stTree, const STtreeData & stBrother);

	enum EN_NODE_TYPE{EN_NODE_TYPE_CHILD, EN_NODE_TYPE_BROTHER};
	STtreeData* AddNodeNext(STtreeData & stTree, char* szName, void* pData, DWORD dwMaskControls, DWORD dwProfile, 
		STtreeData* pChild, STtreeData* pBrother, BOOL bCheck = FALSE, EN_NODE_TYPE enNodeType = EN_NODE_TYPE_CHILD);
	
	int InitType();
	void DeleteAllData(STtreeData** pData);
	HTREEITEM AddProfile(const STtreeData* pTree);
private:
	int InitData(const STtreeData* pTree);
	HTREEITEM InsertTree(const STtreeData* pTree, HTREEITEM hNext, int x, int y, BOOL bRoot = FALSE);

private:
	CDialog    * m_pParent;
	BOOL         bUseCheckBox;
public:
	DECLARE_MESSAGE_MAP()
	//afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};