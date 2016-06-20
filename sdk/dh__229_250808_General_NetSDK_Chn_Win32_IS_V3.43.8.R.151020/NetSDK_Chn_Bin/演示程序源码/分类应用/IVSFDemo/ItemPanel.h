#pragma once
#include <map>
#include <list>
#pragma warning(disable : 4786)


// CItemPanel
class CMatchItem; 
//中间条隐藏按钮高度
#define HIDDING_HEIGHT		24
//列表的高度
#define  PANELHIGHT			225
//每行的高度
#define UNIT_HEIGHT			225
//间距
#define UNIT_SPACE			15
//图片的高度
#define IMAGE_HEIGHT		190
//图片的宽度
#define IMAGE_WIDTH			130
//滑动颗粒大小
#define SCROLL_UNIT			5
//图片的边框
#define IMAGE_MARGIN		15
#define MARGIN_ENLARGE		7
#define IMAGE_ENLARGE		IMAGE_MARGIN - MARGIN_ENLARGE
#define IMAGE_SPACE			10
//间隔背景
#define BACKGROUND_CTWO		RGB(0x39,0x4c,0x6c)
#define BACKGROUND_CONE		RGB(0x39,0x4c,0x6c)
//鼠标移过时的颜色
#define BACKGROUND_COVER	RGB(0x46,0x5e,0x86) 
//行的背景颜色
#define PANELBACKGROUND		RGB(0x96,0xc7,0xef)
//插入速度（新插入数据时的速度）
#define INSERTCONFIGSPEED	30

//允许的最大条数
#define MAX_ROW				100
//每次扩展60个单位长度
#define BUFFER_ROW			MAX_ROW/10
//每次擦除条数
#define CLEARRANGE			MAX_ROW/10

#define MAX_ITEM_NUM        60  

typedef struct srt 
{ 
	char strSrcImgPath[256];		// 需要被匹配的图片的本地路径
	char strFoundImgPath[256];	    // 匹配的图片的本地路径
	char strName[16];               // 人员名字
	char strIdCode[32];		    	// 身份证ID
	char strSex[64];                // 性别
	char strBirthday[64];		    // 生日	
	int		nIndex;					// 在列表中的索引
} Item;

class CItemPanel : public CWnd
{
	DECLARE_DYNAMIC(CItemPanel)
public:
//	Tools::CPicBuffer  test;
	typedef std::map<int,CMatchItem*> ActiveList_t;
	typedef std::list<Item> m_pList;
public:
	CItemPanel();
	~CItemPanel();

	virtual BOOL Create(CWnd* pParentWnd);

	//重新计算内容大小，和更新滚动条。
	virtual void Update(); 
protected:
	ActiveList_t	m_ItemUIList;//被显示的列表
	Item**			m_pItems;//列表
	DWORD			m_nItems;//总条数
	DWORD			m_nIncreaseSection;//每次增加的缓存大小
	int				m_nCountPerPage;//每页的条数 
	DWORD			m_nScrollCountPerPage;
	int				m_nScrollClipHight;
	int				m_nAccelerate;
	DWORD			m_nTopIndex;
	DWORD			m_nHitIndex;
	DWORD			m_nBottomIndex;
	DWORD			m_nFocus;
	CFont			m_font;
	int				m_nBuffer;
	BOOL			m_nInserting;
public:
	void	InsertItem(Item stItem); //暴露给外面的方法
	void    DeleteAllItems();

	void	UpdateVScroll(DWORD nScroll);
	void	ScrollVToPosition(DWORD nIndex);
	void	ScrollByVertical(int nDelta);
	void	ScrollToVertical(DWORD nIndex);
	void	InitialItems();
	BOOL	TestPtInWnd();
	void	DrawEmptyNotification(CDC& dc, CRect& rcClient,int ndebug = 0);

protected:
	DECLARE_MESSAGE_MAP()
	int	m_nScrollWheelLines;	// 鼠标滚轮滚动一次滑动的条数

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

class CMatchItem : public CWnd
{
	DECLARE_DYNAMIC(CMatchItem)

public:
	CMatchItem();
	~CMatchItem();
	Item *m_pItem;
	virtual BOOL Create(CWnd* pParentWnd,CRect rc);

public:
	void DrawImage(CDC *pDC,CRect,BOOL isSrc = TRUE);
	void DrawText(CDC *pDC,CRect);
	BOOL TestPtInImageMatch(CPoint point);
	BOOL TestPtInImageSrc(CPoint point);
	void TestPtInWnd();
	void DrawBackground(CDC *pDC,CRect rc);
	void ExcludeFrame(CRect& rcClient);

protected:
	BOOL  m_bOver;
	BOOL  m_bOverPicSrc;
	BOOL  m_bOverPicMatch;
	CRect m_rcRangeSrc;
	CRect m_rcRangeMatch;
	CFont m_font;
	CFont m_fontBold;
	CRect m_rcFrameSrc;
	CRect m_rcContentSrc;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

