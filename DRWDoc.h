#include "bmp.h"

// DRWDoc.h : interface of the CDRWDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRWDOC_H__E15DC5E3_ED48_4FB8_B16C_3323516278AE__INCLUDED_)
#define AFX_DRWDOC_H__E15DC5E3_ED48_4FB8_B16C_3323516278AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDRWDoc : public CDocument
{
protected: // create from serialization only
	CDRWDoc();
	DECLARE_DYNCREATE(CDRWDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDRWDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDRWDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDRWDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRWDOC_H__E15DC5E3_ED48_4FB8_B16C_3323516278AE__INCLUDED_)
