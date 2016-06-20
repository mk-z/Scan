#if !defined(AFX_CONFIGRULEBASE_H__6E90B008_92A2_42B3_B5BC_48C436335A48__INCLUDED_)
#define AFX_CONFIGRULEBASE_H__6E90B008_92A2_42B3_B5BC_48C436335A48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigRuleBase.h : header file
//
#include "ConfigRules.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigRuleBase dialog

class CConfigRuleBase
{
public:
	CString	m_strRuleName;
	BOOL	m_bEnable;
	CListCtrl	m_clObjType;

public:
	CConfigRules*		m_pParentWnd;
	long				m_lLoginId;
	int					m_nCurrentChannel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGRULEBASE_H__6E90B008_92A2_42B3_B5BC_48C436335A48__INCLUDED_)
