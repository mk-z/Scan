#if !defined(AFX_PROFILEINFO1_H__75D44D18_BC47_42E2_A801_C0769006B39F__INCLUDED_)
#define AFX_PROFILEINFO1_H__75D44D18_BC47_42E2_A801_C0769006B39F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfileInfo1.h : header file
//
class CProfileCfg;
/////////////////////////////////////////////////////////////////////////////
// CProfileInfo1 dialog
class CProfileInfo1 : public CDialog
{
// Construction
public:
	CProfileInfo1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProfileInfo1)
	enum { IDD = IDD_DLG_PROFILE_INFO1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProfileInfo1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProfileInfo1)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeEditProfileName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CProfileCfg*      m_pParent;

public:
	enum EN_MASK_CONTROLS{ EN_MASK_CONTROLS_NAME = 1,
		EN_MASK_CONTROLS_ENABLE = 2,
		EN_MASK_CONTROLS_MINDURATION = 4,
		EN_MASK_CONTROLS_ALARMLOW = 8,
		EN_MASK_CONTROLS_ALARMUP = 16,

		EN_MASK_CONTROLS_ERRLOW = 32,
		EN_MASK_CONTROLS_ERRUP = 64,
		EN_MASK_CONTROLS_UVD = 128
	};

#define MASK_TYPE_ONE (CProfileInfo1::EN_MASK_CONTROLS_ENABLE\
	| CProfileInfo1::EN_MASK_CONTROLS_MINDURATION\
	)
#define MASK_TYPE_TWO (CProfileInfo1::EN_MASK_CONTROLS_ENABLE\
	| CProfileInfo1::EN_MASK_CONTROLS_MINDURATION\
	| CProfileInfo1::EN_MASK_CONTROLS_ALARMLOW\
	| CProfileInfo1::EN_MASK_CONTROLS_ERRLOW\
	)
#define MASK_TYPE_THREE (CProfileInfo1::EN_MASK_CONTROLS_ENABLE\
	| CProfileInfo1::EN_MASK_CONTROLS_MINDURATION\
	| CProfileInfo1::EN_MASK_CONTROLS_ALARMLOW\
	| CProfileInfo1::EN_MASK_CONTROLS_ERRLOW\
	| CProfileInfo1::EN_MASK_CONTROLS_UVD\
	)
#define MASK_TYPE_FOUR (CProfileInfo1::EN_MASK_CONTROLS_ENABLE\
	| CProfileInfo1::EN_MASK_CONTROLS_MINDURATION\
	| CProfileInfo1::EN_MASK_CONTROLS_ALARMLOW\
	| CProfileInfo1::EN_MASK_CONTROLS_ALARMUP\
	| CProfileInfo1::EN_MASK_CONTROLS_ERRLOW\
	| CProfileInfo1::EN_MASK_CONTROLS_ERRUP\
	)

#define VideoDitherDetection    MASK_TYPE_TWO
#define VideoStriationDetection MASK_TYPE_THREE
#define VideoLossDetection      MASK_TYPE_ONE
#define VideoCoverDetection     MASK_TYPE_TWO
#define VideoFrozenDetection    MASK_TYPE_ONE
#define VideoBrightnessDetection MASK_TYPE_FOUR
#define VideoContrastDetection  MASK_TYPE_FOUR
#define VideoUnbalanceDetection MASK_TYPE_TWO
#define VideoNoiseDetection     MASK_TYPE_TWO
#define VideoBlurDetection      MASK_TYPE_TWO
#define VideoSceneChangeDetection MASK_TYPE_TWO

	void EnableControls(DWORD dwMaskControls);

	void UpdateDataToDlg(char* szType, CFG_VIDEO_DIAGNOSIS_PROFILE * pstProfile);
	
	void GetDlgData(char* szType, CFG_VIDEO_DIAGNOSIS_PROFILE * pstProfile);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROFILEINFO1_H__75D44D18_BC47_42E2_A801_C0769006B39F__INCLUDED_)
