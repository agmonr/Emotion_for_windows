#if !defined(AFX_MEMDC_H__AC3016C3_784E_11D4_ADC4_0060080554CD__INCLUDED_)
#define AFX_MEMDC_H__AC3016C3_784E_11D4_ADC4_0060080554CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemDC.h : header file


#define MAX_POSSIBLE_SCREEN_WIDTH  4096
#define MAX_POSSIBLE_SCREEN_HEIGHT 2048
/////////////////////////////////////////////////////////////////////////////
// CMemDC document



class CMemDC : public CDC
{
	DECLARE_DYNAMIC(CMemDC);
private:
	CBitmap m_Bitmap; // Offscreen bitmap

	CBitmap* m_pOldBitmap; // bitmap originally found in CMemDC
	CRect m_Rect; // Rectangle of drawing area.
public:
	CMemDC(int MaxX=MAX_POSSIBLE_SCREEN_WIDTH,int MaxY=MAX_POSSIBLE_SCREEN_HEIGHT);
	virtual ~CMemDC();
	void AfterDraw(CDC* pDC);
	void BeforeDraw(CDC* pDC);

	CMemDC* operator->() {return this;}	
	// Allow usage as a pointer
	operator CMemDC*() {return this;}

	CBitmap* GetBitmap() { return &m_Bitmap; }
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMDC_H__AC3016C3_784E_11D4_ADC4_0060080554CD__INCLUDED_)
