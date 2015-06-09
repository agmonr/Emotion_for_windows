#if !defined(AFX_MOTIONSETTINGSDLG_H__40F8AA7A_2F8A_4169_95DD_57F4E0C71141__INCLUDED_)
#define AFX_MOTIONSETTINGSDLG_H__40F8AA7A_2F8A_4169_95DD_57F4E0C71141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MotionSettingsDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CMotionSettingsDlg dialog

class CMotionSettingsDlg : public CDialog
{
// Construction
public:
	CMotionSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMotionSettingsDlg)
	enum { IDD = IDD_MOTION_SETTINGS };
	BOOL	m_bGroup1;
	BOOL	m_bGroup2;
	UINT	m_Timer1;
	UINT	m_Timer2;
	UINT	m_TimerColor;
	BOOL	m_bGroup3;
	UINT	m_Timer3;
	CString	m_CaptureFolder;
	UINT	m_CaptureMsec;
	UINT	m_CameraFactor;
	BOOL	m_UseSameFile;
	CString	m_FileName;
	UINT	m_MinNeighbours;
	UINT	m_ColorThreshold;
	BOOL	m_DisplayFunctionName;
	BOOL	m_AutoAdjust;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMotionSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMotionSettingsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOTIONSETTINGSDLG_H__40F8AA7A_2F8A_4169_95DD_57F4E0C71141__INCLUDED_)
