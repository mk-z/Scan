#pragma once
#include "afxcmn.h"
#include <map>
#include "SetTimeDlg.h"
#include "DeviceUserDlg.h"
#include "DeviceUpdateDlg.h"
#include "EncodeDlg.h"
#include "OsdSet.h"
#include "VideoHide.h"
#include "PictureSet.h"
#include "InterestArea.h"
#include "NetParam.h"
#include "PppoeSet.h"
#include "DNSSet.h"
#include "EMailSet.h"
#include "UPNPSet.h"
#include "FTPSet.h"
#include "VideoPlan.h"
#include "HideWarning.h"
#include "MoveSenseSet.h"
#include "SerialSet.h"
#include "CloudSet.h"
#include "IoWarning.h"
#include "WarningUpload.h"
#include "GB28181Set.h"
#include "LostWarning.h"
#include "NetDiskSet.h"
#include "AvdSet.h"
#include "NetStatus.h"
#include "JointAction.h"
#include "SerachWifi.h"
#include "DeviceState.h"
#include "ChannelStream.h"
#include "Ir_CutSet.h"
#include "SystemMsgDlg.h"
#include "NetWorkFaultCheck.h"
#include "PeaOscCfg.h"
#include "HxhtConfig.h"
#include "HwSetDlg.h"
#include "CpcSetDlg.h"
#include "PirAlarmDlg.h"
#include "RtspServerDlg.h"
#include "HerdAnalyse.h"
#include "ElevatorSet.h"
#include "ZteCfgDlg.h"

typedef std::map<HTREEITEM, CWnd*> PAGE_MAP;
// CCAttributeDlg 对话框

class CCAttributeDlg : public CDialog
{
	DECLARE_DYNAMIC(CCAttributeDlg)

public:
	CCAttributeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCAttributeDlg();
// 对话框数据
	enum { IDD = IDD_DIALOG_ATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CSetTimeDlg			m_cSetTimeDlg;
	CDeviceUserDlg		m_cUserDlg;
	CDeviceUpdateDlg	m_cUpdateDlg;
	CEncodeDlg			m_cEncode;
	COsdSet 			m_cOsdSetDlg;
	CVideoHide			m_videoHide;
	CPictureSet			m_cPitcure;
	CNetParam 			m_netParam;
	CPppoeSet			m_pSet;
	CEMailSet 			m_eMailSet;
	CUPNPSet 			m_upnpSet;
	CFTPSet				m_ftpSet;
	CGB28181Set 		m_gbs8181;
	CVideoPlan			m_videoPlan;
	CNetDiskSet 		m_netdisk;
	CHideWarning 		m_hideWarning;
	CLostWarning 		m_lostWarn;
	CWarningUpload 		m_upload;
	CSerialSet 			m_serial;
	CCloudSet			m_cloudSet;
	CMoveSenseSet		m_moveSense;
	CIoWarning 			m_ioWarn;
	CInterestArea 		m_interest;
	CDNSSet 			m_dnsSet;
	CAvdSet 			m_avdSet;
	CNetStatus 			m_netStatus;
	CJointAction		m_jointAction;
	CSerachWifi 		m_serachWifi;
	CDeviceState		m_deviceState;
	CChannelStream 		m_channelStream;
	CSystemMsgDlg		m_cSysMsgDlg;
	CIr_CutSet 			m_iR_Cut;
	CNetWorkFaultCheck	m_NetworkFaultCheck;
	CPeaOscCfg 			m_peaoscCfg;
	CHxhtConfig			m_m_HxhtConfig;
	CHwSetDlg			m_hwSetDlg;
	CCpcSetDlg			m_cpcSetDlg;
	CPirAlarmDlg		m_pirAlarm;
	CRtspServerDlg		m_rtspServer;
	CHerdAnalyse		m_herdAnalyse;
	CElevatorSet		m_elevatorSet;
	CZteCfgDlg			m_zteCfg;
public:
	CTreeCtrl m_AttributeTree;
	PAGE_MAP m_PageMap;
	HTREEITEM m_hSelItem;
	void InitTree();
	void InitTreeEnglish();
	void FlashWnd(CWnd *pSelPage);

	afx_msg void OnTvnSelchangedTreeAttribute(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	void EnablePlayWnd(int iIndex);
	void EnableBorderDlg();
//	afx_msg void OnMove(int x, int y);
	afx_msg void OnMove(int x, int y);
	
};
