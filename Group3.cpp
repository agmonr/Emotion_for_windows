#include "stdafx.h"
#include "Group1.h"
#include "Dib.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CGroup1::Draw9(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(R, G, B);
	
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	pDC->MoveTo(R*3,G);
	pDC->LineTo(CameraX*3, B*3);
	
	b.DeleteObject();
	pen.DeleteObject();
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
}

void CGroup1::Lots10(CDC* pDC, CSize& ScreenSize,
					 int CameraX, int CameraY, // position on camera
					 long x, long y, // position on screen
					 long lFactorX, long lFactorY, long CameraFactor,
					 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(R, G,B);
	
	for (int f=0; f<4; f++)
	{
		for (int g=0; g<5; g++)\
		{			
			pDC->SetPixel(CameraX*f,CameraY*g, CurrColor);
		}
	}
}

void CGroup1::LotsOrder11(CDC* pDC, CSize& ScreenSize,
						  int CameraX, int CameraY, // position on camera
						  long x, long y, // position on screen
						  long lFactorX, long lFactorY, long CameraFactor,
						  COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(R, G,B);
	
	for (int f=0; f<4; f++)
	{
		for (int g=0; g<5; g++)\
		{			
			pDC->SetPixel(CameraX+f*200,CameraY+g*200, CurrColor);
		}
	}
}

void CGroup1::LinesTop14(CDC* pDC, CSize& ScreenSize,
						 int CameraX, int CameraY, // position on camera
						 long x, long y, // position on screen
						 long lFactorX, long lFactorY, long CameraFactor,
						 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(R, G, B);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	if (x<ScreenSize.cx/2 && y<ScreenSize.cy/2 )
	{
		pDC->MoveTo (0,0);
		pDC->LineTo(x,y);
	}
	else if (x>ScreenSize.cx/2 && y<ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx,0);
		pDC->LineTo(x,y);
	}
	else if (x<ScreenSize.cx/2 && y>ScreenSize.cy/2 )
	{
		pDC->MoveTo (0,ScreenSize.cy);
		pDC->LineTo(x,y);
	}
	else if (x>ScreenSize.cx/2 && y>ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx,ScreenSize.cy);
		pDC->LineTo(x,y);
	}
	
	b.DeleteObject();	
	pen.DeleteObject();
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
}

void CGroup1::LinesCenter15(CDC* pDC, CSize& ScreenSize,
							int CameraX, int CameraY, // position on camera
							long x, long y, // position on screen
							long lFactorX, long lFactorY, long CameraFactor,
							COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetGValue(Diff);
	long B = GetBValue(Diff);
	COLORREF CurrColor = SelectColor(R,G,B);
	
	long rgb=(R+G+B)/3;
	long lastX = min(x+lFactorX, ScreenSize.cx);
	long lastY = min(y+lFactorY, ScreenSize.cy);
	
	CRect r(x, y, lastX, lastY);
	CBrush b(RGB(0,0,0));
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, CurrColor);
	CPen* pOld = pDC->SelectObject(&pen);
	CBrush* pOldB = pDC->SelectObject(&b);
	
	if (x<ScreenSize.cx/2 && y<ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx/2,ScreenSize.cy/2);
		pDC->LineTo(x,y);
	}
	else if (x>ScreenSize.cx/2 && y<ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx/2,ScreenSize.cy/2);
		pDC->LineTo(x,y);
	}
	else if (x<ScreenSize.cx/2 && y>ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx/2,ScreenSize.cy/2);
		pDC->LineTo(x,y);
	}
	else if (x>ScreenSize.cx/2 && y>ScreenSize.cy/2 )
	{
		pDC->MoveTo (ScreenSize.cx/2,ScreenSize.cy/2);
		pDC->LineTo(x,y);
	}
	
	b.DeleteObject();
	pen.DeleteObject();
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
}
