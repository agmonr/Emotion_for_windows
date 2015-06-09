#if !defined(AFX_SETUPMATRIXDLG_H__9D867DD8_8C7E_4530_B6EC_B0B8F8B8BBAE__INCLUDED_)
#define AFX_SETUPMATRIXDLG_H__9D867DD8_8C7E_4530_B6EC_B0B8F8B8BBAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupMatrixDlg.h : header file
//
#include "MatrixOptions.h"

/////////////////////////////////////////////////////////////////////////////
// CSetupMatrixDlg dialog

class CSetupMatrixDlg : public CDialog
{
// Construction
public:
	CSetupMatrixDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupMatrixDlg)
	enum { IDD = IDD_MATRICES };
	//}}AFX_DATA

	MatrixOptions m_MatrixOptions;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupMatrixDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupMatrixDlg)
	afx_msg void OnDefault();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPMATRIXDLG_H__9D867DD8_8C7E_4530_B6EC_B0B8F8B8BBAE__INCLUDED_)
