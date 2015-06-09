

// DRWView.h : interface of the CDRWView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRWVIEW_H__58D92118_E255_4311_8598_627EC5C6385D__INCLUDED_)
#define AFX_DRWVIEW_H__58D92118_E255_4311_8598_627EC5C6385D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDRWView : public CView
{
protected: // create from serialization only
	CDRWView();
	DECLARE_DYNCREATE(CDRWView)

// Attributes
public:
	CDRWDoc* GetDocument();

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRWView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDRWView();

// Generated message map functions
protected:
	//{{AFX_MSG(CDRWView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DRWView.cpp
inline CDRWDoc* CDRWView::GetDocument()
   { return (CDRWDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRWVIEW_H__58D92118_E255_4311_8598_627EC5C6385D__INCLUDED_)
