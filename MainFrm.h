// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__44AC1802_9CDE_4915_9404_1199104532D6__INCLUDED_)
#define AFX_MAINFRM_H__44AC1802_9CDE_4915_9404_1199104532D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVideoCapture;
class CDib;
class CCameraPicture;
class CBaseDraw;
class CDRWDoc;

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	bool m_bFullScreen;
	WINDOWPLACEMENT m_wpPrev;
	CRect m_FullScreenWindowRect;

	CRect m_FullViewRect;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	public:
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

public:

	void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);

///////////////////////////////////////////
	void OnDraw(CDC* pDC);

	long m_RefreshRate; // msec
	CString m_PicturesFolder;
	long m_NewImageRate; // sec
	BOOL m_bMotionColorsAffectWholeImage; 

	UINT m_RefreshTimerId;
	UINT m_ChangeStaticPicTimerId;
	UINT m_ChangeDrawTimerId;

	bool m_bInDlg;
	bool m_bActive;

	CList<CBaseDraw*, CBaseDraw*> m_Drawings;

	CBaseDraw* GetCurrDraw() { return m_Drawings.GetHead(); }
// Operations
public:
	void ReadSettings();
	void WriteSettings();
	void InitTimers();

	void DoActivate(bool bActive);

	void ProcessChange();
protected:
	CVideoCapture* m_pVideoCapture;
	CCameraPicture* m_pCameraPicture;
///////////////////////////////////////////
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateViewFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewSettings();
	afx_msg void OnViewNewSettings();
	afx_msg void OnUpdateViewSettings(CCmdUI* pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnAppAbout();
	afx_msg void OnDoNextDraw();
	afx_msg void OnToggleCapture();
	afx_msg void OnSelectFuntions();
	afx_msg void OnPaint();
	afx_msg void OnSetupMatrix();
	afx_msg void OnMoveViewPoint();
	//}}AFX_MSG
public:
	afx_msg void OnViewFullScreen();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__44AC1802_9CDE_4915_9404_1199104532D6__INCLUDED_)
