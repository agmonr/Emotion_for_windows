#include "stdafx.h"
#include "Group1.h"
#include "Dib.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


long CGroup1::m_Color_Select = 0;

long CGroup1::GetNumColors()
{
	return 27;
}

COLORREF CGroup1::SelectColor(int CameraX, int CameraY, COLORREF Pix)
{
//			m_Color_Select=26;

	switch (m_Color_Select)
	{
	case 0: return (RGB(GetRValue(Pix)%110+90,CameraX%100, CameraY%100));
	case 1: return (RGB(GetRValue(Pix)+100,CameraX%50+30, CameraY%50+150));
	case 2: return (RGB(GetRValue(Pix),GetGValue(Pix), 255));
	case 3: return (RGB(255,GetGValue(Pix), 255));
	case 4: return (RGB(0,GetGValue(Pix)*3, 0));
	case 5: return (RGB(CameraX%255*3, GetGValue(Pix),CameraY%100));	
	case 6: return (RGB(CameraX%25+150, GetGValue(Pix)*2,CameraY%25));	
	case 7: return (RGB(255, GetGValue(Pix),GetBValue(Pix)));	
	case 8: return (RGB(255, 255,GetBValue(Pix)));	
	case 9: return (RGB(0, 0,GetBValue(Pix)*3));	
	case 10: return (RGB(CameraX%255, CameraY%255, GetBValue(Pix)));
	case 11: return (RGB(CameraX%25, CameraY%25, GetBValue(Pix)*3));
	case 12: return (RGB(GetRValue(Pix), 255, GetBValue(Pix)));
	case 13: return (RGB(GetRValue(Pix)%50+150, 50, GetBValue(Pix)));
	case 14: return (RGB(GetRValue(Pix)*3, 0, 0));
	case 15: return (RGB(GetGValue(Pix),GetGValue(Pix), GetGValue(Pix)));
	case 16: return (RGB(300-GetRValue(Pix),300-CameraX%255, 300-CameraY%255));
	case 17: return (RGB(200-GetRValue(Pix)%50,CameraX%25, 120-CameraY%25));
	case 18: return (RGB((255-GetRValue(Pix))*3,(255-GetGValue(Pix))*3, 30));	
	case 19: return (RGB(GetBValue(Pix),GetBValue(Pix),GetBValue(Pix)));	
	case 20: return (RGB(255-CameraX%255, 255-GetGValue(Pix),255-CameraY%255));	
	case 21: return (RGB(255-CameraX%25, 255-GetGValue(Pix),255-CameraY%25));	
	case 22: return (RGB(30, (255-GetGValue(Pix))*3,(255-GetBValue(Pix))*3));
	case 23: return (RGB(GetRValue(Pix),GetRValue(Pix), GetRValue(Pix)));
	case 24: return (RGB(255-CameraX%255, 255-CameraY%255, 255-GetBValue(Pix)));
	case 25: return (RGB(255-CameraX%25, 255-CameraY%25, 255-GetBValue(Pix)));
	case 26: return (RGB((255-GetRValue(Pix))*3, 30, (255-GetBValue(Pix))*3));
		
	default:  return (RGB(255, 255,255));
		
	}
}

void CGroup1::DrawBasic(CDC* pDC, CSize& ScreenSize,
						int CameraX, int CameraY, // position on camera
						long x, long y, // position on screen
						long lFactorX, long lFactorY, long CameraFactor,
						COLORREF Pix, COLORREF PrevPix, DWORD)
						
{


	long lastX = min(x+(lFactorX * CameraFactor), ScreenSize.cx);
	long lastY = min(y+(lFactorY * CameraFactor), ScreenSize.cy);
	
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);

	CRect r(x, y, lastX, lastY);
	CBrush b(CurrColor);
	pDC->FillRect(&r, &b);
}

void CGroup1::Draw1(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
					
{
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, x%4, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	pDC->Ellipse(x, y, lastX+4, lastY+4);
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	b.DeleteObject();
	pen.DeleteObject();
}

void CGroup1::Draw2(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	
	CFont f;
	f.CreatePointFont(R%100+50, "Arial", pDC);
	CFont* pOld = pDC->SelectObject(&f);
	COLORREF OldT = pDC->SetTextColor(CurrColor);
	COLORREF OldBK = pDC->SetBkColor(RGB(0,0,0));
	pDC->TextOut(x, y, "XOX");
	
	pDC->SelectObject(pOld);
	f.DeleteObject();
	pDC->SetTextColor(OldT);
	pDC->SetBkColor(OldBK);	
}

void CGroup1::Draw3(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CPen pen;
	pen.CreatePen(x%4, x%5, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	
	pDC->ArcTo(x, y, lastX+7, lastY+7, x, y, lastX-7, lastY-7);
	
	pDC->SelectObject(pOld);
	pen.DeleteObject();
}

void CGroup1::Draw4(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, R%5, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	pDC->Rectangle(x, y, lastX+R%10, lastY+G%10);
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	b.DeleteObject();
	pen.DeleteObject();
}

void CGroup1::Draw5(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(1,1,1));
	CPen pen;
	pen.CreatePen(PS_SOLID, R%5, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	pDC->MoveTo(x,y);
	pDC->LineTo(lastX+R%20, lastY+R%20);
	
	pen.DeleteObject();
	CurrColor = RGB(CameraX%(B+1),GetRValue(Pix),CameraY%20);
	pen.CreatePen(PS_SOLID, G%5, CurrColor);
	pOld = pDC->SelectObject(&pen);
	pDC->LineTo(lastX-G%20, lastY+G%20);
	
	pen.DeleteObject();
	CurrColor = RGB(CameraX%(B+1),CameraY%20,GetRValue(Pix));
	pen.CreatePen(PS_SOLID, B%5, CurrColor);
	pOld = pDC->SelectObject(&pen);
	pDC->LineTo(lastX+B%20, lastY-B%20);
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	
	pen.DeleteObject();
	b.DeleteObject();
}

void CGroup1::Draw6(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CPen pen;
	pen.CreatePen(PS_SOLID, R%5, CurrColor);	
	CPen* pOld = pDC->SelectObject(&pen);
	
	pDC->LineTo(lastX, lastY);
	
	pDC->SelectObject(pOld);
	pen.DeleteObject();	
}

void CGroup1::Draw7(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, R%4, CurrColor);
	
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	pDC->Ellipse(x,y,lastX+R%20, lastY+G%20);
	pDC->MoveTo(x,y);
	if (R>G)	
	{
		pDC->LineTo(int(x+R%10), int(y+G%10));
		pDC->MoveTo(x,y);
	}
	else if (R>B)	
	{
		pDC->LineTo(int(x-G%10), int(y+B%10));
		pDC->MoveTo(x,y);
	}
	else if (G>B)
	{
		pDC->LineTo(int(x+R%10), int(y-G%10));
		pDC->MoveTo(x,y);
	}
	else
	{
		pDC->LineTo(int(x-B%10), int(y-R%10));
		pDC->MoveTo(x,y);
	}
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	b.DeleteObject();
	pen.DeleteObject();
}



//////////////////////////////////////////////////////////////////////
// Magen David

void CGroup1::Draw8(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CPen pen;
	pen.CreatePen(PS_SOLID, R/75, CurrColor);
	
	CPen* pOld = pDC->SelectObject(&pen);
	
	pDC->MoveTo(x,y);
	pDC->LineTo(int(x*1.03), int(y*1.06));
	pDC->LineTo(int(x*0.96), int(y*1.06));
	pDC->LineTo(x,y);
	
	pDC->MoveTo(int(x*0.96), int(y*1.02));
	pDC->LineTo(int(x*1.04), int(y*1.02));
	pDC->LineTo(x, int(y*1.1));
	pDC->LineTo(int(x*0.96), int(y*1.02));
	
	pen.DeleteObject();
	pDC->SelectObject(pOld);
}

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void CGroup1::ChangeCircle12(CDC* pDC, CSize& ScreenSize,
							 int CameraX, int CameraY, // position on camera
							 long x, long y, // position on screen
							 long lFactorX, long lFactorY, long CameraFactor,
							 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, rgb%5, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	pDC->Ellipse(x, y, lastX+rgb%30, lastY+rgb%30);	
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	pen.DeleteObject();
	b.DeleteObject();
}

void CGroup1::Cats(CDC* pDC, CSize& ScreenSize,
							 int CameraX, int CameraY, // position on camera
							 long x, long y, // position on screen
							 long lFactorX, long lFactorY, long CameraFactor,
							 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	

	CBrush b(RGB(B,R,G));
	CPen pen;
	pen.CreatePen(PS_SOLID, rgb%5, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	


	pDC->Ellipse(x, y, x+25, y+30);	

	b.DeleteObject();
	
	CBrush c(RGB(255,255,255));
	int x1=-11; int y1=-8;
	pDC->Ellipse(x+14+x1, y+18+y1, x+x1, y+y1);	

	x1=-7; y1=0;
	pDC->Ellipse(x+14+x1, y+18+y1, x+x1, y+y1);	


//	pDC->Ellipse(x+10, y, x-7, y-17);	


	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	pen.DeleteObject();
	b.DeleteObject();
	c.DeleteObject();
}

//////////////////////////////////////////////////////////////////////
void CGroup1::ChangeRect13(CDC* pDC, CSize& ScreenSize,
						   int CameraX, int CameraY, // position on camera
						   long x, long y, // position on screen
						   long lFactorX, long lFactorY, long CameraFactor,
						   COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, rgb%3, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	pDC->Rectangle(x, y, lastX+rgb%10, lastY+rgb%10);	
	
	pen.DeleteObject();
	b.DeleteObject();
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void CGroup1::ColorHigh16(CDC* pDC, CSize& ScreenSize,
						  int CameraX, int CameraY, // position on camera
						  long x, long y, // position on screen
						  long lFactorX, long lFactorY, long CameraFactor,
						  COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);	
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, rgb%3, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	pDC->Ellipse(x-rgb%15,y+rgb%15,x+rgb%15,y-rgb%15);
	pDC->MoveTo(x-rgb%15,y-rgb%15);
	pDC->LineTo(x+rgb%15,y+rgb%15);
	pDC->MoveTo(x-rgb%15,y+rgb%15);
	pDC->LineTo(x+rgb%15,y-rgb%15);
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	b.DeleteObject();
	pen.DeleteObject();
}

//////////////////////////////////////////////////////////////////////
void CGroup1::EllipsHigh17(CDC* pDC, CSize& ScreenSize,
						   int CameraX, int CameraY, // position on camera
						   long x, long y, // position on screen
						   long lFactorX, long lFactorY, long CameraFactor,
						   COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, rgb%3, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	pDC->Ellipse(x,y,x+rgb%8,y+rgb%50);
	pDC->LineTo(x,y);
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	b.DeleteObject();
	pen.DeleteObject();
}

//////////////////////////////////////////////////////////////////////
void CGroup1::Text18(CDC* pDC, CSize& ScreenSize,
					 int CameraX, int CameraY, // position on camera
					 long x, long y, // position on screen
					 long lFactorX, long lFactorY, long CameraFactor,
					 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);	
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	COLORREF OldT = pDC->SetTextColor(CurrColor);
	COLORREF OldBK = pDC->SetBkColor(RGB(255,255,255)-CurrColor);
	pDC->TextOut(x,y,"אריה");
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	pDC->SetTextColor(OldT);
	pDC->SetBkColor(OldBK);
	b.DeleteObject();
	pen.DeleteObject();
}


void CGroup1::ColorNames(CDC* pDC, CSize& ScreenSize,
						 int CameraX, int CameraY, // position on camera
						 long x, long y, // position on screen
						 long lFactorX, long lFactorY, long CameraFactor,
						 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(CameraX, CameraY, Pix);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, R%10, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	COLORREF OldT = pDC->SetTextColor(CurrColor);
	COLORREF OldBK = pDC->SetBkColor(RGB(255,255,255)-CurrColor);
	
	CFont f;
	CFont* pOldFont= NULL;
	long FontSize = min(40, B % 20);
	f.CreatePointFont(FontSize, "David", pDC);
	pOldFont = pDC->SelectObject(&f);
	if (B>G && B>R)  
	{
		pDC->TextOut(x,y,"רבין");
	}
	else if (G>B && G>R)
	{	
		pDC->TextOut(x,y,"הסתה");
	}
	else	
	{
		pDC->SetTextColor(CurrColor*3);
		pDC->SetBkColor(RGB(255,255,255)-CurrColor*3);
		pDC->TextOut(x,y,"דם זועק");
	}
	
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
	pDC->SelectObject(pOldFont);
	pDC->SetTextColor(OldT);
	pDC->SetBkColor(OldBK);
	b.DeleteObject();
	pen.DeleteObject();
	f.DeleteObject();
}
