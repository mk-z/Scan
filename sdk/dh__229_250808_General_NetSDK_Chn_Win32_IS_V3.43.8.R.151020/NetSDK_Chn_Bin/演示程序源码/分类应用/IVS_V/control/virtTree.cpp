#include "StdAfx.h"
#include "virtTree.h"

CVirtTree::CVirtTree(CDialog* pParent /* = NULL */)
{
	m_pParent = pParent;
	bUseCheckBox = FALSE;
}

CVirtTree::~CVirtTree()
{

}

int CVirtTree::InitType()
{
	int iRet = -1;
	UpdateData(FALSE);
	if (bUseCheckBox)
	{
		ModifyStyle(0,TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_CHECKBOXES);
		ModifyStyle( TVS_CHECKBOXES, 0 );
		ModifyStyle( 0, TVS_CHECKBOXES );
		DeleteAllItems();
	}
	else
	{
		ModifyStyle(0,TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES);
		DeleteAllItems();
	}


	SetBkColor(RGB(204,232,205));//设置背景色

	DeleteAllItems();
	UpdateData(TRUE);
	return iRet;
}
HTREEITEM CVirtTree::AddProfile(const STtreeData* pTree)
{
	if (NULL == pTree)
	{
		return 0;
	}

	HTREEITEM hItem = 0;
	HTREEITEM hRoot = GetRootItem();
	if (0 == hRoot)
	{
		hItem = InsertTree(pTree, hRoot, 0, 0, TRUE);
	}
	else
	{

		hItem = InsertTree(pTree, hRoot, 0, 0);
	}
	return hItem;
}
HTREEITEM CVirtTree::InsertTree(const STtreeData* pTree, HTREEITEM hNext, int x, int y, BOOL bRoot /*= FALSE*/)
{
	if (NULL == pTree)
	{
		return 0;
	}

	HTREEITEM hParent = hNext;
	if (bRoot)
	{
		hNext = InsertItem(pTree->strName.c_str(), x, y, TVI_ROOT, TVI_LAST);
		SetItemData(hNext, (unsigned long)pTree);
#ifdef _DEBUG
		char szTmp[MAX_PATH] = {0};
		sprintf(szTmp, "0x%x - 0x%x < %s!\n", hNext, pTree, pTree->strName.c_str());
		OutputDebugString(szTmp);
#endif // _DEBUG
		if (bUseCheckBox)
		{
			SetCheck(hNext,pTree->bCheck);
		}
	}
	else
	{
		hNext = InsertItem(pTree->strName.c_str(), x, y, hParent, TVI_LAST);
		SetItemData(hNext, (unsigned long)pTree);
#ifdef _DEBUG
		char szTmp[MAX_PATH] = {0};
		sprintf(szTmp, "0x%x - 0x%x < %s!\n", hNext, pTree, pTree->strName.c_str());
		OutputDebugString(szTmp);
#endif // _DEBUG
		if (bUseCheckBox)
		{
			SetCheck(hNext,pTree->bCheck);
		}
	}
	HTREEITEM hChild = hNext;
	hChild = InsertTree(pTree->pChild, hChild, x, y);

	STtreeData* pBrother = pTree->pBrother;
	HTREEITEM hBrother = hNext;
	while (NULL != pBrother)
	{
		if (bRoot)
		{
			hBrother = InsertItem(pBrother->strName.c_str(), x, y, TVI_ROOT, TVI_LAST);
			SetItemData(hBrother, (unsigned long)pBrother);
#ifdef _DEBUG
			char szTmp[MAX_PATH] = {0};
			sprintf(szTmp, "0x%x - 0x%x < %s!\n", hBrother, pBrother, pBrother->strName.c_str());
			OutputDebugString(szTmp);
#endif // _DEBUG
			if (bUseCheckBox)
			{
				SetCheck(hBrother,pTree->bCheck);
			}	
		}
		else
		{
			hBrother = InsertItem(pBrother->strName.c_str(), x, y, hParent, TVI_LAST);
			SetItemData(hBrother, (unsigned long)pBrother);
#ifdef _DEBUG
			char szTmp[MAX_PATH] = {0};
			sprintf(szTmp, "0x%x - 0x%x < %s!\n", hBrother, pBrother, pBrother->strName.c_str());
			OutputDebugString(szTmp);
#endif // _DEBUG
			if (bUseCheckBox)
			{
				SetCheck(hBrother,pTree->bCheck);
			}
		}

		HTREEITEM hChild = hNext;
		hChild =InsertTree(pBrother->pChild, hBrother, x, y);

		pBrother = pBrother->pBrother;
	}

	return hNext;
}

int CVirtTree::InitData(const STtreeData* pTree)
{
	if (NULL != pTree && NULL != pTree->pChild)
	{
		bool bCheckAll = false;
		HTREEITEM hRoot = NULL;
		InsertTree(pTree, hRoot, 0, 0, TRUE);
		Expand(GetRootItem(),TVE_EXPAND);

		if (bUseCheckBox)
		{
			SetCheck(hRoot,TRUE);
		}
	}

	return 0;
}

int CVirtTree::ResetTree(const STtreeData &stTree)
{
	InitType();
	InitData(&stTree);
	return 0;
}


/************************************************************************/
/* 设置子节点的选中状态                                              */
/************************************************************************/
void CVirtTree::SetChildCheck(HTREEITEM item, BOOL bCheck)
{
	HTREEITEM child = GetChildItem(item);
	while(child)
	{
		SetCheck(child, bCheck);
		SetChildCheck(child, bCheck);
		child = GetNextItem(child, TVGN_NEXT);
	}
}

/************************************************************************/
/* 设置父节点选中状态                                                 */
/************************************************************************/
void CVirtTree::SetParentCheck(HTREEITEM item, BOOL bCheck)
{
	HTREEITEM parent = GetParentItem(item);
	if(parent == NULL)
		return;

	if(bCheck)
		SetCheck(parent, bCheck);
	else
	{
		HTREEITEM bro = GetNextItem(item, TVGN_NEXT);
		BOOL bFlag = false;
		while(bro)
		{
			if(GetCheck(bro))
			{
				bFlag = true;
				break;
			}
			bro = GetNextItem(bro, TVGN_NEXT);
		}
		if(!bFlag)
		{
			bro = GetNextItem(item, TVGN_PREVIOUS);
			while(bro)
			{
				if(GetCheck(bro))
				{
					bFlag = true;
					break;
				}
				bro = GetNextItem(bro, TVGN_PREVIOUS);
			}
		}
		if(!bFlag)
			SetCheck(parent, false);
	}
	SetParentCheck(parent, GetCheck(parent));
}

BEGIN_MESSAGE_MAP(CVirtTree, CTreeCtrl)
//ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CVirtTree::OnTvnSelchanged)
//ON_NOTIFY_REFLECT(NM_CLICK, &CVirtTree::OnNMClick)
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void CVirtTree::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	//
	// \屏蔽空格、回车等按键对列表的复选框左右
	//

	//CVirtTree::OnKeyDown(nChar, nRepCnt, nFlags);
}
//void CVirtTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//
//	*pResult = 1;
//}
//
//void CVirtTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: Add your control notification handler code here
//
//	*pResult = 1;
//}


int CVirtTree::AddNodeChild(STtreeData & stTree,const STtreeData & stChild)
{
	stTree.pChild = new STtreeData;
	stTree.pChild->bCheck = stChild.bCheck;
	stTree.pChild->pBrother = stChild.pBrother;
	stTree.pChild->pChild = stChild.pChild;
	stTree.pChild->pData = stChild.pData;
	stTree.pChild->strName = stChild.strName;
	stTree.pChild->dwMaskControls = stChild.dwMaskControls;
	stTree.pChild->dwProfile = stChild.dwProfile;
	return 0;
}
int CVirtTree::AddNodeBrother(STtreeData & stTree, const STtreeData & stBrother)
{
	stTree.pBrother = new STtreeData;
	stTree.pBrother->bCheck = stBrother.bCheck;
	stTree.pBrother->pBrother = stBrother.pBrother;
	stTree.pBrother->pChild = stBrother.pChild;
	stTree.pBrother->pData = stBrother.pData;
	stTree.pBrother->strName = stBrother.strName;
	stTree.pBrother->dwMaskControls = stBrother.dwMaskControls;
	stTree.pBrother->dwProfile = stBrother.dwProfile;
	return 0;
}
STtreeData* CVirtTree::AddNodeNext(STtreeData & stTree, char* szName, void* pData, DWORD dwMaskControls, DWORD dwProfile, 
	STtreeData* pChild, STtreeData* pBrother, BOOL bCheck /*= FALSE*/,  EN_NODE_TYPE enNodeType /*= EN_NODE_TYPE_CHILD*/)
{
	STtreeData * pNode = NULL;
	if ( EN_NODE_TYPE_CHILD == enNodeType)
	{
		stTree.pChild = new STtreeData;
		pNode = stTree.pChild;
	}
	else if (EN_NODE_TYPE_BROTHER == enNodeType)
	{
		stTree.pBrother = new STtreeData;
		pNode = stTree.pBrother;
	}
	if (NULL == pNode)
	{
		return 0;
	}
	pNode->bCheck = bCheck;
	pNode->pBrother = pBrother;
	pNode->pChild = pChild;
	pNode->pData = pData;
	pNode->strName = szName;
	pNode->dwMaskControls = dwMaskControls;
	pNode->dwProfile = dwProfile;

	return pNode;
}

void CVirtTree::DeleteAllData(STtreeData** pData)
{
	if (NULL == (*pData) || NULL == pData)
	{
		return;
	}

	if (NULL != (*pData)->pChild)
	{
		DeleteAllData(&(*pData)->pChild);
	}
	
	if (NULL != (*pData)->pBrother)
	{
		DeleteAllData(&(*pData)->pBrother);
	}

	if (NULL == (*pData)->pChild && NULL == (*pData)->pBrother)
	{
		SAFE_DELETE((*pData));
		return;
	}
}