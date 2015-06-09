#if !defined(AFX_SELECTDRAWINGSDLG_H__0E3CFE68_1B1B_47C7_AE87_F70DE41EDBC2__INCLUDED_)
#define AFX_SELECTDRAWINGSDLG_H__0E3CFE68_1B1B_47C7_AE87_F70DE41EDBC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDrawingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectDrawingsDlg dialog

class CSelectDrawingsDlg : public CDialog
{
// Construction
public:
	CSelectDrawingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectDrawingsDlg)
	enum { IDD = IDD_DRAWINGS };
	CListBox	m_List;
	//}}AFX_DATA

	CStringList m_Names;
	CMapStringToPtr m_Enable;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDrawingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectDrawingsDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectall();
	afx_msg void OnUnselectall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDRAWINGSDLG_H__0E3CFE68_1B1B_47C7_AE87_F70DE41EDBC2__INCLUDED_)
