#include "stdafx.h"
#include "Group2.h"
#include "Dib.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCameraPicture* CGroup2::m_pCameraPicture = NULL;
COLORREF CGroup2::m_Averages[AVG_SIZE][AVG_SIZE];
CString CGroup2::m_BmpFile;
CStringList CGroup2::m_BmpFiles;
CWnd* CGroup2::m_pWnd = NULL;
bool CGroup2::m_SelectNewBmp = false;;


void CGroup2::DrawBackground(CDC* pDC, COLORREF cr)
{
	CRect Rect;
	m_pWnd->GetClientRect(&Rect);
	CBrush brush(cr);
	pDC->FillRect(&Rect, &brush);
}

void CGroup2::ApplyRgbChangeToDib(CDib& Dib, long RAll, long GAll, long BAll)
{
	CSize size = Dib.GetSize();
	COLORREF Rtotal,Gtotal,Btotal;
	for (int i = 0; i < size.cx; i++) {
		for (int j = 0; j < size.cy; j++) {
			COLORREF c = Dib.GetPixel(i, j);
			if (c > 0) {
				//				COLORREF NewC = RGB(GetRValue(c), GAll, BAll);
				Rtotal=GetRValue(c);
				Gtotal=GetGValue(c);
				Btotal=GetBValue(c);
				
				if (Rtotal>Gtotal && Rtotal>Btotal) Btotal=Gtotal=0;
				else
					if (Gtotal>Rtotal && Gtotal>Btotal) Rtotal=Btotal=0;
					else
						Rtotal=Gtotal=0;
					
					if (RAll>GAll && RAll>BAll) BAll=GAll=0;
					else
						if (GAll>RAll && GAll>BAll) RAll=BAll=0;
						else
							RAll=GAll=0;
						
						
						COLORREF NewC = RGB(Rtotal*RAll, Gtotal*GAll, Btotal*BAll);
						
						//				COLORREF NewC = RGB(GetRValue(c), GetGValue(c), GetBValue(c));
						Dib.SetPixel(i, j, NewC);
			}
		}
	}
}

void CGroup2::BTriangle19(CDC* pDC, CSize& ScreenSize,
						  int CameraX, int CameraY, // position on camera
						  long x, long y, // position on screen
						  long lFactorX, long lFactorY, long CameraFactor,
						  COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}
	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 20, RGB(0,0,b*2));
	CPen* pOld = pDC->SelectObject(&pen);
	
	int posx=-90, posy=-90;
	
	pDC->MoveTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*2/3+posy);
	pDC->LineTo(ScreenSize.cx*1/3+posx, ScreenSize.cy*2/3+posy);
	pDC->LineTo(ScreenSize.cx*1/2+posx, ScreenSize.cy*1/3+posy);
	pDC->LineTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*2/3+posy);
	
	pDC->MoveTo(ScreenSize.cx*1/2+posx, ScreenSize.cy*2/3+ScreenSize.cy*1/9+posy);
	pDC->LineTo(ScreenSize.cx*1/3+posx, ScreenSize.cy*1/3+ScreenSize.cy*1/9+posy);
	pDC->LineTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*1/3+ScreenSize.cy*1/9+posy);
	pDC->LineTo(ScreenSize.cx*1/2+posx, ScreenSize.cy*2/3+ScreenSize.cy*1/9+posy);
	
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 20, RGB(0,g*2,0));
	pDC->SelectObject(&pen);
	
	posx=60, posy=60;
	pDC->MoveTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*2/3+posy);
	pDC->LineTo(ScreenSize.cx*1/3-posx, ScreenSize.cy*2/3+posy);
	pDC->LineTo(ScreenSize.cx*1/2, ScreenSize.cy*1/3-posy);
	pDC->LineTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*2/3+posy);
	
	pDC->MoveTo(ScreenSize.cx*1/2, (int)(ScreenSize.cy*2/3+ScreenSize.cy*1/7.5+posy));
	pDC->LineTo(ScreenSize.cx*1/3-posx, (int)(ScreenSize.cy*1/3+ScreenSize.cy*1/7.5-posy));
	pDC->LineTo(ScreenSize.cx*2/3+posx, (int)(ScreenSize.cy*1/3+ScreenSize.cy*1/7.5-posy));
	pDC->LineTo(ScreenSize.cx*1/2, (int)(ScreenSize.cy*2/3+ScreenSize.cy*1/7.5+posy));	
	
	// овп гег аген
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 20, RGB(r*2,0,0));
	pDC->SelectObject(&pen);
	
	posx=90, posy=110;
	pDC->MoveTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*2/3+posy);
	pDC->LineTo(ScreenSize.cx*1/3-posx, ScreenSize.cy*2/3+posy);
	pDC->LineTo(ScreenSize.cx*1/2, ScreenSize.cy*1/3-posy);
	pDC->LineTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*2/3+posy);
	
	pDC->MoveTo(ScreenSize.cx*1/2, ScreenSize.cy*2/3+ScreenSize.cy*1/6+posy);
	pDC->LineTo(ScreenSize.cx*1/3-posx, ScreenSize.cy*1/3+ScreenSize.cy*1/6-posy);
	pDC->LineTo(ScreenSize.cx*2/3+posx, ScreenSize.cy*1/3+ScreenSize.cy*1/6-posy);
	pDC->LineTo(ScreenSize.cx*1/2, ScreenSize.cy*2/3+ScreenSize.cy*1/6+posy);
	
	pen.DeleteObject();
	pDC->SelectObject(pOld);
	
}

void CGroup2::Blines2color20(CDC* pDC, CSize& ScreenSize,
							 int CameraX, int CameraY, // position on camera
							 long x, long y, // position on screen
							 long lFactorX, long lFactorY, long CameraFactor,
							 COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}
	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 20, RGB(0,0,b));
	CPen* pOld = pDC->SelectObject(&pen);
	
	DrawBackground (pDC, RGB(200,50,50));	
	
	int sx=ScreenSize.cx/255; int sy=ScreenSize.cy/255;
	
	pDC->MoveTo(sx*r,sy*g);
	pDC->LineTo(sx*b, sx*b);
	
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, r, RGB(0,g,0));
	pDC->SelectObject(&pen);
	pDC->LineTo(ScreenSize.cx-sx*g, sy*g);
	
	
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, g, RGB(r,0,0));
	pDC->SelectObject(&pen);
	pDC->LineTo(sx*r, ScreenSize.cy-sy*r);	
	
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, b, RGB(r,g,0));
	pDC->SelectObject(&pen);
	pDC->LineTo(sx*b,sy*g);
	
	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, r, RGB(r,0,b));
	pDC->SelectObject(&pen);
	pDC->LineTo(ScreenSize.cx/2+sx*b/2,sy*g+b);
	
	pen.DeleteObject();
	pDC->SelectObject(pOld);
	
}


void CGroup2::B9lines(CDC* pDC, CSize& ScreenSize,
					  int CameraX, int CameraY, // position on camera
					  long x, long y, // position on screen
					  long lFactorX, long lFactorY, long CameraFactor,
					  COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
	DrawBackground (pDC, RGB(30,30,30));
	
	CPen* pOld = pDC->SelectObject((CPen*)NULL);
	
	for (m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r=GetRValue (m_Averages[m][n]);	
			g=GetGValue (m_Averages[m][n]);	
			b=GetBValue (m_Averages[m][n]);	
			
			t=r;
			if (g>t) t=g;
			if (b>t) t=b;
			pDC->MoveTo(100+m*sx+t/10,n*sy+t/10+50);
			
			for (int z=0; z<5; z++)
			{
				CPen pen1;
				pen1.CreatePen(PS_SOLID, n, RGB(0,t,0));
				pDC->SelectObject(&pen1);
				pDC->LineTo(100+m*sx-t/5+t/(m+1)+z*6,50+n*sy+t/4+30-z*6);
				pen1.DeleteObject();
				
				CPen pen2;
				pen2.CreatePen(PS_SOLID, m, RGB(0,0,t));
				pDC->SelectObject(&pen2);
				pDC->LineTo(100+m*sx-t/5-t/(m+3)-z*10,50+n*sy-t/5-3+z*4);
				pen2.DeleteObject();
				
				CPen pen3;
				pen3.CreatePen(PS_SOLID, t/20, RGB(t,255-t,0));
				pDC->SelectObject(&pen3);
				pDC->LineTo(100+m*sx-t/5-t/((n+1)*2)+z*4,50+n*sy+t/2-z*6);
				pen3.DeleteObject();
			}
		}
	}	
	pDC->SelectObject(pOld);
}

void CGroup2::Blinesfromcenter(CDC* pDC, CSize& ScreenSize,
							   int CameraX, int CameraY, // position on camera
							   long x, long y, // position on screen
							   long lFactorX, long lFactorY, long CameraFactor,
							   COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}
	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	CPen* pOld = pDC->SelectObject((CPen*)NULL);
	
	int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
	DrawBackground (pDC, RGB(20,20,20));	
	
	for (m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r=GetRValue (m_Averages[m][n]);	
			g=GetGValue (m_Averages[m][n]);	
			b=GetBValue (m_Averages[m][n]);	
			
			t=r;
			if (g>t) t=g;
			if (b>t) t=b;
			pDC->MoveTo(ScreenSize.cx/2,ScreenSize.cy/2);
			
			CPen pen1;
			pen1.CreatePen(PS_SOLID, 2-n, RGB(t,t/2,0));
			pDC->SelectObject(&pen1);
			pDC->LineTo(m*sx-t/5+t/(m+2),n*sy+t/4);
			pen1.DeleteObject();
			
			
			CPen pen2;
			pen2.CreatePen(PS_SOLID, m, RGB(t,t/2,255-t));
			pDC->SelectObject(&pen2);
			pDC->LineTo(100+m*sx-t/3-t/(m+3),50+n*sy-t/3-3);
			pen2.DeleteObject();
			
		}
	}
	pDC->SelectObject(pOld);
}


void CGroup2::Ellipse(CDC* pDC, CSize& ScreenSize,
					  int CameraX, int CameraY, // position on camera
					  long x, long y, // position on screen
					  long lFactorX, long lFactorY, long CameraFactor,
					  COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}
	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	//pen.CreatePen(PS_SOLID, 20, RGB(0,0,b));
	CPen* pOld = pDC->SelectObject((CPen*)NULL);	
	
	int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
	
	DrawBackground (pDC, RGB(0,120,25));	
	
	for (m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r=GetRValue (m_Averages[m][n]);	
			g=GetGValue (m_Averages[m][n]);	
			b=GetBValue (m_Averages[m][n]);	
			
			t=r;
			if (g>t) t=g;
			if (b>t) t=b;
			
			for (int z=0; z<t/10; z++)
			{
				CPen pen;
				pen.CreatePen(PS_SOLID, z*t%5, RGB(t*3+z*3,255-b%50+z*3,z*10));
				pDC->SelectObject(&pen);
				
				pDC->Ellipse(m*sx+50+z*6+r/10,n*sy+50+z*6+g/10,m*sx+70+z*10+b/20, n*sy+70+z*10+t/10);
				pen.DeleteObject();	
			}		
		}
	}	
	pDC->SelectObject(pOld);
}

void CGroup2::Brectangle24(CDC* pDC, CSize& ScreenSize,
						   int CameraX, int CameraY, // position on camera
						   long x, long y, // position on screen
						   long lFactorX, long lFactorY, long CameraFactor,
						   COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	CPen* pOld = pDC->SelectObject((CPen*)NULL);	
	
	int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
	
	DrawBackground (pDC, RGB(0,50,25));	
	
	for (m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r=GetRValue (m_Averages[m][n]);	
			g=GetGValue (m_Averages[m][n]);	
			b=GetBValue (m_Averages[m][n]);	
			
			t=r;
			if (g>t) t=g;
			if (b>t) t=b;
			
			for (int z=0; z<t/10; z++)
			{
				CPen pen;
				pen.CreatePen(PS_SOLID, z*t%5, RGB(t*3+z*3,255-b%50+z*3,z*10));
				pDC->SelectObject(&pen);
				pDC->Rectangle(m*sx+50+z*6+r/10,n*sy+50+z*6+g/10,m*sx+70+z*10+b/20, n*sy+70+z*10+t/10);
				pen.DeleteObject();
			}		
		}
	}
	
	pDC->SelectObject(pOld);
}

void CGroup2::BColorLines25(CDC* pDC, CSize& ScreenSize,
							int CameraX, int CameraY, // position on camera
							long x, long y, // position on screen
							long lFactorX, long lFactorY, long CameraFactor,
							COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	CPen* pOld = pDC->SelectObject((CPen*)NULL);		
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
		
		long count=AVG_SIZE*AVG_SIZE;
		r/=count; g/=count; b/=count;
		
		int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
		
		DrawBackground (pDC, RGB(0,0,50));	
		
		for (m=0; m<AVG_SIZE; m++)
		{
			pDC->MoveTo(m*sx,0);
			for (int n=0; n<AVG_SIZE; n++)
			{
				r=GetRValue (m_Averages[m][n]);	
				g=GetGValue (m_Averages[m][n]);	
				b=GetBValue (m_Averages[m][n]);	
				
				t=r;
				if (g>t) t=g;
				if (b>t) t=b;
				
				for (int c=0; c<3; c++)
				{					
					if (c==0) 
					{
						CPen pen;
						pen.CreatePen(PS_SOLID, t%10, RGB(r*2,0,0));
						pDC->SelectObject(&pen);
						pDC->LineTo(r+m*sx,r+n*sy);
						pen.DeleteObject();
					}
					else if (c==1) 
					{
						CPen pen;
						pen.CreatePen(PS_SOLID, t%10, RGB(0,g*2,0));
						pDC->SelectObject(&pen);
						pDC->LineTo(g+m*sx,g+n*sy);
						pen.DeleteObject();
					}else if (c==2) 
					{
						CPen pen;
						pen.CreatePen(PS_SOLID, t%10, RGB(0,0,b*2));
						pDC->SelectObject(&pen);
						pDC->LineTo(b+m*sx,b+n*sy);
						pen.DeleteObject();
					}
				}			
			}
		}
	}
	
}

void CGroup2::BColorLines26(CDC* pDC, CSize& ScreenSize,
							int CameraX, int CameraY, // position on camera
							long x, long y, // position on screen
							long lFactorX, long lFactorY, long CameraFactor,
							COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	CPen* pOld = pDC->SelectObject((CPen*)NULL);	
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
		
		long count=AVG_SIZE*AVG_SIZE;
		r/=count; g/=count; b/=count;
		
		int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
		
		DrawBackground (pDC, RGB(0,0,25));	
		
		for (m=0; m<AVG_SIZE; m++)
		{
			for (int c=0; c<3; c++)
			{			
				pDC->MoveTo(m*sx,0);
				for (int n=0; n<AVG_SIZE; n++)
				{
					r=GetRValue (m_Averages[m][n]);	
					g=GetGValue (m_Averages[m][n]);	
					b=GetBValue (m_Averages[m][n]);	
					
					t=r;
					if (g>t) t=g;
					if (b>t) t=b;
					
					if (c==0) 
					{
						CPen pen;
						pen.CreatePen(PS_SOLID, t%8, RGB(r*2,0,0));
						pDC->SelectObject(&pen);
						pDC->LineTo(r+m*sx,r+n*sy);
						pen.DeleteObject();
					}
					else if (c==1) 
					{
						CPen pen;
						pen.CreatePen(PS_SOLID, t%8, RGB(0,g*2,0));
						pDC->SelectObject(&pen);
						pDC->LineTo(g+m*sx+c*5,g+n*sy-c*5);
						pen.DeleteObject();
					}
					else if (c==2) 
					{
						CPen pen;
						pen.CreatePen(PS_SOLID, t%8, RGB(0,0,b*2));
						pDC->SelectObject(&pen);
						pDC->LineTo(b+m*sx-c*5,b+n*sy+c*5);
						pen.DeleteObject();
					}
				}				
			}
		}
	}		
	pDC->SelectObject(pOld);
}

void CGroup2::BColorLines27(CDC* pDC, CSize& ScreenSize,
							int CameraX, int CameraY, // position on camera
							long x, long y, // position on screen
							long lFactorX, long lFactorY, long CameraFactor,
							COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}
	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	CPen* pOld = pDC->SelectObject((CPen*)NULL);
	
	int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
	
	DrawBackground (pDC, RGB(0,0,b));	
	
	for (int n=0; n<AVG_SIZE; n++)
	{
		for (int c=0; c<3; c++)
		{
			pDC->MoveTo(0,n*sy);
			for (m=0; m<AVG_SIZE; m++)
			{
				r=GetRValue (m_Averages[m][n]);	
				g=GetGValue (m_Averages[m][n]);	
				b=GetBValue (m_Averages[m][n]);	
				
				t=r;
				if (g>t) t=g;
				if (b>t) t=b;
						
				if (c==0) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%8, RGB(r*2,0,0));
					pDC->SelectObject(&pen);
					pDC->LineTo(r+m*sx,r+n*sy);
					pen.DeleteObject();
				}
				else if (c==1) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%8, RGB(0,g*2,0));
					pDC->SelectObject(&pen);
					pDC->LineTo(g+m*sx+c*5,g+n*sy-c*5);
					pen.DeleteObject();
				}
				else if (c==2) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%8, RGB(0,0,b*2));
					pDC->SelectObject(&pen);
					pDC->LineTo(b+m*sx-c*5,b+n*sy+c*5);
					pen.DeleteObject();
				}
			}
			
		}
	}
	
	pDC->SelectObject(pOld);
}

void CGroup2::BColorLines28(CDC* pDC, CSize& ScreenSize,
							int CameraX, int CameraY, // position on camera
							long x, long y, // position on screen
							long lFactorX, long lFactorY, long CameraFactor,
							COLORREF Pix, COLORREF PrevPix, DWORD)
{
	long Diff = Pix - PrevPix;
	long R = GetRValue(Diff);
	long G = GetRValue(Diff);
	long B = GetRValue(Diff);
	
	COLORREF avg=0;
	long r=0, b=0, g=0, t=0;
	for (int m=0; m<AVG_SIZE; m++)
	{
		for (int n=0; n<AVG_SIZE; n++)
		{
			r+=GetRValue (m_Averages[m][n]);	
			g+=GetGValue (m_Averages[m][n]);	
			b+=GetBValue (m_Averages[m][n]);	
		}
	}
	
	long count=AVG_SIZE*AVG_SIZE;
	r/=count; g/=count; b/=count;
	
	CPen* pOld = pDC->SelectObject((CPen*)NULL);
	int sx=ScreenSize.cx/5; int sy=ScreenSize.cy/5;
	
	DrawBackground (pDC, RGB(0,0,b));	
	
	for (int n=0; n<AVG_SIZE; n++)
	{
		for (int c=0; c<3; c++)
		{			
			pDC->MoveTo(0,n*sy);
			for (m=0; m<AVG_SIZE; m++)
			{
				r=GetRValue (m_Averages[m][n]);	
				g=GetGValue (m_Averages[m][n]);	
				b=GetBValue (m_Averages[m][n]);	
				
				t=r;
				if (g>t) t=g;
				if (b>t) t=b;
				
				if (c==0) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%8, RGB(r*2,0,0));
					pDC->SelectObject(&pen);
					pDC->LineTo(r+m*sx,r+n*sy);
					pen.DeleteObject();
				}
				else if (c==1) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%8, RGB(0,g*2,0));
					pDC->SelectObject(&pen);
					pDC->LineTo(g+m*sx+c*5,g+n*sy-c*5);
					pen.DeleteObject();
				}
				else if (c==2) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%8, RGB(0,0,b*2));
					pDC->SelectObject(&pen);
					pDC->LineTo(b+m*sx-c*5,b+n*sy+c*5);
					pen.DeleteObject();
				}
			}
			
		}
	}
	
	for (m=0; m<AVG_SIZE; m++)
	{
		for (int c=0; c<3; c++)
		{			
			pDC->MoveTo(m*sx,0);
			for (n=0; n<AVG_SIZE; n++)
			{
				r=GetRValue (m_Averages[m][n]);	
				g=GetGValue (m_Averages[m][n]);	
				b=GetBValue (m_Averages[m][n]);	
				
				t=r;
				if (g>t) t=g;
				if (b>t) t=b;
				
				if (c==0) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%5, RGB(r*2,0,0));
					pDC->SelectObject(&pen);
					pDC->LineTo(r+m*sx,r+n*sy);
					pen.DeleteObject();
				}
				else if (c==1) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%5, RGB(0,g*2,0));
					pDC->SelectObject(&pen);
					pDC->LineTo(g+m*sx+c*5,g+n*sy-c*5);
					pen.DeleteObject();
				}
				else if (c==2) 
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, t%5, RGB(0,0,b*2));
					pDC->SelectObject(&pen);
					pDC->LineTo(b+m*sx-c*5,b+n*sy+c*5);
					pen.DeleteObject();
				}
			}
		}
	}
	
	pDC->SelectObject(pOld);
}

void CGroup2::DrawBitmap29(CDC* pDC, CSize& ScreenSize,
						   int CameraX, int CameraY, // position on camera
						   long x, long y, // position on screen
						   long lFactorX, long lFactorY, long CameraFactor,
						   COLORREF Pix, COLORREF PrevPix, DWORD)
{
	CDib Dib;
	if (m_SelectNewBmp) {
		char FileName[1024];
		::GetModuleFileName(AfxGetInstanceHandle(), FileName, 1024);
		CString sFileName(FileName);
		int index = sFileName.ReverseFind('\\');
		if (index > 0) {
			CString PicsDir = sFileName.Left(index) + "\\PIC";
			CUtils::SelectPic(PicsDir, m_BmpFiles, m_BmpFile);
			m_SelectNewBmp = false;
		}
	}
	
	if (! m_BmpFile.IsEmpty() && Dib.Load(m_BmpFile)) {
		
		long RAll(0),GAll(0),BAll(0);
		CUtils::CalcColorChage(m_pCameraPicture, RAll, GAll, BAll);
		ApplyRgbChangeToDib(Dib, RAll, GAll, BAll);
		
		CRect ScreenRect(CPoint(0,0), ScreenSize);
		Dib.Draw(*pDC, &ScreenRect, NULL);
	}
}
