// FindRecode.cpp : 实现文件
//

#include "stdafx.h"
#include "Client_Demo.h"
#include "FindRecode.h"


// CFindRecode 对话框

IMPLEMENT_DYNAMIC(CFindRecode, CDialog)

CFindRecode::CFindRecode(CWnd* pParent /*=NULL*/)
	: CDialog(CFindRecode::IDD, pParent)
{

}

CFindRecode::~CFindRecode()
{
}

void CFindRecode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFindRecode, CDialog)
END_MESSAGE_MAP()


// CFindRecode 消息处理程序
