#include "stdafx.h"
#include "Group4.h"
#include "Group1.h"
#include "3DDraw.h"
#include <d3d9.h>
#include <d3dx9.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable: 4244)
///////////////////////////////////////////////////////////////////////////////

extern CUSTOMVERTEX vertices[];
extern UINT VertexCounter;
extern LPDIRECT3DDEVICE9 g_pd3dDevice; // Our rendering device
int lightx=0;
int lighty=0;


extern UINT MaxPrimitiveCount;
extern UINT MaxVertexCount;

long BkVertexCounter = 0;

///////////////////////////////////////////////////////////////////////////////
long CGroup4::m_Color_Select = 0;
int lastx=0;
int lasty=0;
int lightrad=50;

long CGroup4::GetNumColors()
{
	return 28;
}

COLORREF CGroup4::SelectColor(int CameraX, int CameraY, COLORREF Pix)
{
	
	switch (m_Color_Select)
	{
	case 0: return (RGB(GetRValue(Pix), GetGValue(Pix), GetBValue(Pix)));

	case 1: return (RGB(255-GetRValue(Pix), GetGValue(Pix), GetBValue(Pix)));
	case 2: return (RGB(GetRValue(Pix), 255-GetGValue(Pix), GetBValue(Pix)));
	case 3: return (RGB(GetRValue(Pix), GetGValue(Pix), 255-GetBValue(Pix)));

	case 4: return (RGB(255-GetRValue(Pix), 255-GetGValue(Pix), GetBValue(Pix)));
	case 5: return (RGB(GetRValue(Pix), 255-GetGValue(Pix), 255-GetBValue(Pix)));
	case 6: return (RGB(255-GetRValue(Pix), GetGValue(Pix), 255-GetBValue(Pix)));

	case 7: return (RGB(GetRValue(Pix)*3, GetGValue(Pix)*5, GetBValue(Pix)));
	case 8: return (RGB(GetRValue(Pix), GetGValue(Pix)*3, GetBValue(Pix)*5));
	case 9: return (RGB(GetRValue(Pix)*5, GetGValue(Pix), GetBValue(Pix)*3));

	case 10: return (RGB(GetGValue(Pix), GetBValue(Pix), GetRValue(Pix)));
	case 11: return (RGB(GetBValue(Pix), GetRValue(Pix), GetGValue(Pix)));

	case 12: return (RGB(GetRValue(Pix) +GetGValue(Pix) , GetGValue(Pix)+ GetBValue(Pix), GetBValue(Pix)+GetRValue(Pix)));
	case 13: return (RGB(GetRValue(Pix) *GetGValue(Pix) , GetGValue(Pix)* GetBValue(Pix), GetBValue(Pix)*GetRValue(Pix)));

	case 14: return (RGB(GetRValue(Pix) *CameraX , GetGValue(Pix)* CameraX, GetBValue(Pix)*CameraX));
	case 15: return (RGB(GetRValue(Pix) +150 , GetGValue(Pix)-50, GetBValue(Pix)-50));
	case 16: return (RGB(GetRValue(Pix) -50 , GetGValue(Pix)+150, GetBValue(Pix)-50));
	case 17: return (RGB(GetRValue(Pix) -50 , GetGValue(Pix)-50, GetBValue(Pix)+150));

	case 18: return (RGB(GetRValue(Pix)+150 , GetGValue(Pix)-50, GetBValue(Pix)+150));
	case 19: return (RGB(GetRValue(Pix)-50 , GetGValue(Pix)+150, GetBValue(Pix)+150));
	case 20: return (RGB(GetRValue(Pix)+150 , GetGValue(Pix)+150, GetBValue(Pix)-50));

	case 21: return (RGB(-GetRValue(Pix) , -GetGValue(Pix), -GetBValue(Pix)));
	case 22: return (RGB(GetRValue(Pix) , -GetGValue(Pix), -GetBValue(Pix)));
	case 23: return (RGB(-GetRValue(Pix) , GetGValue(Pix), -GetBValue(Pix)));
	case 24: return (RGB(-GetRValue(Pix) , -GetGValue(Pix), GetBValue(Pix)));

	case 25: return (RGB(50 , 50, GetBValue(Pix)));
	case 26: return (RGB(50 , GetGValue(Pix),50 ));
	case 27: return (RGB(GetRValue(Pix),50,50 ));

	case 28: return (RGB(GetRValue(Pix)*2 , GetGValue(Pix)*2, GetBValue(Pix)*2));

	case 51: return (RGB(GetRValue(Pix)+100,CameraX%50+30, CameraY%50+150));
	case 52: return (RGB(GetRValue(Pix),GetGValue(Pix), 255));
	case 53: return (RGB(GetRValue(Pix)%110+90,CameraX%100, CameraY%100));
	case 54: return (RGB(0,GetGValue(Pix)*3, 0));
	case 55: return (RGB(CameraX/5, GetGValue(Pix),CameraY%100));	
	case 56: return (RGB(CameraX%25+150, GetGValue(Pix)*2,CameraY%25));	
	case 57: return (RGB(255, GetGValue(Pix),GetBValue(Pix)));	
	case 58: return (RGB(CameraX/5, -CameraX/5, CameraX/5));	
	case 59: return (RGB(0, 0,GetBValue(Pix)*3));	
	case 101: return (RGB(CameraX/255, CameraY/255, GetBValue(Pix)));
	case 111: return (RGB(CameraX%25, GetBValue(Pix)*3, CameraY%25 ));
	case 121: return (RGB(GetRValue(Pix), 255, GetBValue(Pix)));
	case 131: return (RGB(GetRValue(Pix)%50+150, 50, GetBValue(Pix)));
	case 141: return (RGB(GetRValue(Pix)*3, 50, 75));
	case 151: return (RGB(GetGValue(Pix),GetGValue(Pix), GetGValue(Pix)));
	case 161: return (RGB(300-GetRValue(Pix),300-CameraX/10, 300-CameraY/10));
	case 171: return (RGB(200-GetRValue(Pix)%50, GetGValue(Pix), 120-GetBValue(Pix)));
	case 181: return (RGB((255-GetRValue(Pix))*3,(255-GetGValue(Pix))*3, 30));	
	case 191: return (RGB(GetBValue(Pix),GetBValue(Pix),GetBValue(Pix)));	
	case 201: return (RGB(155-CameraX/25, 155-GetGValue(Pix),CameraY/10));	
	case 221: return (RGB(255-CameraX%25, 255-GetGValue(Pix),150-CameraY/9));	
	case 222: return (RGB(30, (255-GetGValue(Pix))*3,(255-GetBValue(Pix))*3));
	case 223: return (RGB(255-GetRValue(Pix),255-GetGValue(Pix), 255-GetBValue(Pix)));
	case 224: return (RGB(255-CameraX/25, 80-CameraY/50, 255-GetBValue(Pix)));
	case 225: return (RGB(255-GetRValue(Pix), 255-GetGValue(Pix), 255-GetBValue(Pix)));
	case 226: return (RGB((255-GetRValue(Pix))*3, 30, (255-GetBValue(Pix))*3));
		
	default:  return (RGB(255, 255,255));
		
	}
}

const float xRatio = 1024.0;
const float yRatio = 768.0;
const float zRatio = 768.0;


void AddVertex(double x, double y, double z, COLORREF c)
{
	if (VertexCounter < MaxVertexCount) {
		z=z-2000;

		float fx = float (x / xRatio)-0.5f;
		float fy = float (1 - (y / yRatio))-0.5f;
		float fz = float (z / zRatio);

		/*
		if (VertexCounter % 2000 == 0) {
			TRACE("AddVertex %d\n", VertexCounter);
		}*/
		
		vertices[VertexCounter].x = fx;
		vertices[VertexCounter].y = fy;
		vertices[VertexCounter].z = fz;
		vertices[VertexCounter].color = c;        // The vertex color
//		vertices[VertexCounter].nx = fx;
//		vertices[VertexCounter].ny = -fy;
//		vertices[VertexCounter].nz = fz;
		VertexCounter++;
	}
}

void AddBkVertex(long x, long y, long z, COLORREF c)
{
	UINT CurrVertexCounter = VertexCounter + BkVertexCounter;
	if (CurrVertexCounter < MaxVertexCount) {
		float fx = float (x / xRatio)-0.5f;
		float fy = float (1 - (y / yRatio))-0.5f;
		float fz = float (z / zRatio);

		vertices[CurrVertexCounter].x = fx;
		vertices[CurrVertexCounter].y = fy;
		vertices[CurrVertexCounter].z = fz;
//		vertices[CurrVertexCounter].nx = 0;
//		vertices[CurrVertexCounter].ny = 0;
//		vertices[CurrVertexCounter].nz = 0;
		vertices[CurrVertexCounter].color = c;        // The vertex color
		TRACE("AddBkVertex %d\n", CurrVertexCounter);
		BkVertexCounter++;
	}
}

///////////////////////////////////////////////////////////////////////////////

UINT PointsInShape(D3DPRIMITIVETYPE PrimitiveType)
{
	switch (PrimitiveType)
	{
		case D3DPT_POINTLIST:
			return 1;
		case D3DPT_LINELIST:
			return 2;
		case D3DPT_LINESTRIP:
			return 1;
		case D3DPT_TRIANGLELIST:
			return 3;
		case D3DPT_TRIANGLESTRIP:
			return 1;
		case D3DPT_TRIANGLEFAN:
			ASSERT(FALSE);
			return 1;
	}
	ASSERT(FALSE);
	return 1;
}

void DoDrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	TRACE("DoDrawPrimitive from %d Count %d\n", StartVertex, PrimitiveCount);

	long NBShapePoints = PointsInShape(PrimitiveType);

	UINT LastVertex = StartVertex + PrimitiveCount * NBShapePoints;
	UINT CurrentVertex = StartVertex;
	UINT CurrentPrimitive = 0;
	while (CurrentPrimitive < PrimitiveCount) {
		UINT CurrPrimitiveCount = min(PrimitiveCount - CurrentPrimitive, MaxPrimitiveCount);
		if (CurrPrimitiveCount < PrimitiveCount)
			TRACE("lala\n");

		HRESULT hr = g_pd3dDevice->DrawPrimitive( PrimitiveType, CurrentVertex, CurrPrimitiveCount);
		TRACE("DoDrawPrimitive1 from %d Count %d\n", CurrentVertex, CurrPrimitiveCount);

		if (FAILED(hr)) {
			static int once = 0;
			if (once == 0) {
				once = 1;
				AfxMessageBox("Failed to render scene");
			}
		}
		CurrentVertex += CurrPrimitiveCount * NBShapePoints;
		CurrentPrimitive += CurrPrimitiveCount;
	}
}

///////////////////////////////////////////////////////////////////////////////

void CGroup4::Draw0(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		//g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		DoDrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;
		const d = 2;

		
			if (VertexCounter < MaxVertexCount) {

				float depth = 0.2f;
				const long Width = 20;

				AddVertex(x, y, 0, D3DCOLOR_XRGB(0,255,0));
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(0,0,255));
				AddVertex(x+Width, y+Width, 0, D3DCOLOR_XRGB(255,255,255));

				//TRACE("VertexCounter is %d\n", VertexCounter);
		
		}
	}
}

void CGroup4::Draw1(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
//				COLORREF CurrColor = c;
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));

				float depth = 0.2f;
				int Width = 20;
				int Near=0;

				AddVertex(x, y, Near , CurrColor);
				AddVertex(x+Width, y, Near,  CurrColor);
				AddVertex(x, y+Width, Near, CurrColor);


//				AddVertex(x+Width, y, Near,  D3DCOLOR_XRGB(R/2,G/2,B/2));


//				AddVertex(x+Width/2, y+Width, Near, CurrColor);






/*				AddVertex(x, y, Near, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width, y, Near, CurrColor);
				AddVertex(x+Width/2, y+Width,Near ,D3DCOLOR_XRGB(0,0,0));
				

//				AddVertex(x, y, 3000, D3DCOLOR_XRGB(R/5,G/5,B/5));
				//AddVertex(x+Width, y, 3000, D3DCOLOR_XRGB(R/3,G/3,B/3));
//				AddVertex(x+Width/2, y+Width,3000 ,D3DCOLOR_XRGB(0,0,0));
*/				

		}
	}
}

void CGroup4::Draw2(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);
				int Width=(R+G+B)/15;

				AddVertex(x, y, -500,CurrColor );
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width/2, y+Width,  G*2 , D3DCOLOR_XRGB(0,0,0));

				
			}

	}
}

void CGroup4::Draw3(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));

				float Depth = (R+G+B)*2;
				const long Width = 20;

				AddVertex(x, y, Depth,D3DCOLOR_XRGB(R/2,100,B));
				AddVertex(x+Width, y,Depth, CurrColor);
				AddVertex(x, y, Depth/2, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width, y+Width, Depth, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width/2, y, Depth/2, D3DCOLOR_XRGB(0,0,0));

				

		}
	}
}


void CGroup4::Draw4(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

			if (VertexCounter < VertexNum) {
				float depth = 0.2f;
				const long Width = 30;

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

/*				AddVertex(x, y, 2500, D3DCOLOR_XRGB(0,0,0));
				AddVertex(x+Width, y, 2500, D3DCOLOR_XRGB(0,0,0));
				AddVertex(x+Width, y+Width,2500, D3DCOLOR_XRGB(0,0,0));

*/
				if (R>200){
				AddVertex(x, 1024, 3500-y*3, CurrColor*2);
				AddVertex(x+Width, 1024, 3500-y*3+50, CurrColor*5);
				AddVertex(x+Width,1024, 3500-y*3, CurrColor*10);
				}

				if (G<100)
				{
				AddVertex(x, 0, 3500-y*3, CurrColor*2);
				AddVertex(x+Width, 0, 3500-y*3+50, CurrColor*5);
				AddVertex(x+Width,0, 3500-y*3, CurrColor*10);
				}

				if (B<100)
				{
				AddVertex(0, y-Width, 3500-x*3, CurrColor*2);
				AddVertex(0, y, 3500-x*3+50, CurrColor*5);
				AddVertex(0,y+Width, 3500-x*3, CurrColor*10);
				}

				if (G>200)
				{
				AddVertex(1024, y-Width, 3500-x*3, CurrColor*2);
				AddVertex(1024, y, 3500-x*3+50, CurrColor*5);
				AddVertex(1024,y+Width, 3500-x*3, CurrColor*10);
				}




		}
	}
}

void CGroup4::Draw5(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

			if (VertexCounter < VertexNum) {
				
				const long Width = 20;

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				AddVertex(x, y, 0, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width, y, 100, D3DCOLOR_XRGB(G/2,B/2,G/2));
				AddVertex(x, y+Width, 200, D3DCOLOR_XRGB(R/2,G/2,B/2));

				AddVertex(x+Width, y, 200, D3DCOLOR_XRGB(G,G,G));
				AddVertex(x, y+Width, 100, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, -100, D3DCOLOR_XRGB(R*2,G*2,B*2));


		}
	}
}

void CGroup4::Draw6(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float depth = 0.2f;
				const long Width = 20;

				AddVertex(x, y, R,D3DCOLOR_XRGB(50,50,50));
				AddVertex(x+Width, y,  G, D3DCOLOR_XRGB(R+50,G,B));
				AddVertex(x, y+Width,  B, D3DCOLOR_XRGB(R+50,G/2+20,B/2+20));

		}
	}
}

void CGroup4::Draw7(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

			

			
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				int oldx=x;
				int oldy=y;
				x=x/2;
				y=y/2;


				if (R+G+B>450)
				{
				AddVertex(x, y, 4000,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+20, y, 4000, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+20, y+10, 4000 , D3DCOLOR_XRGB(R,G,B));
				}
				
				x=512+x;
				if (R>150)
				{
				AddVertex(x, y, 4000,D3DCOLOR_XRGB(R,0,0));
				AddVertex(x+20, y, 4000, D3DCOLOR_XRGB(R,0,0));
				AddVertex(x+20, y+10, 4000 , D3DCOLOR_XRGB(R,0,0));
			
				}

				y=y+736/2;

				if (G>150)
				{
				AddVertex(x, y, 4000,D3DCOLOR_XRGB(0,G,0));
				AddVertex(x+20, y, 4000, D3DCOLOR_XRGB(0,G,0));
				AddVertex(x+20, y+10, 4000 , D3DCOLOR_XRGB(0,G,0));
				}

				x=x-512;

				if (B>150){
				AddVertex(x, y, 4000,D3DCOLOR_XRGB(0,0,B));
				AddVertex(x+20, y, 4000, D3DCOLOR_XRGB(0,0,B));
				AddVertex(x+20, y+10, 4000 , D3DCOLOR_XRGB(0,0,B));
				}



				y=oldy;
				x=oldx;

				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);



				const long Width = float (R+G+B)/3/10;

				if (R+G+B<500)
				{
				AddVertex(x, y, 0,CurrColor);
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width, y+Width/2, R , D3DCOLOR_XRGB(R,0,B/2));
				}



		}
	}
}


void CGroup4::Draw8(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = float (R+G+B)/60;

				AddVertex(x, y, x*2-1500,CurrColor);
				AddVertex(x+Width, y+Width, x*2-1500,CurrColor);
				AddVertex(x-Width, y+Width, x*2-1500 ,D3DCOLOR_XRGB(-R/2,-G/2,-B/2));

				AddVertex(x, y, 3000-x*2,CurrColor);
				AddVertex(x+Width, y+Width, 3000-x*2,CurrColor);
				AddVertex(x-Width, y+Width, 3000-x*2,D3DCOLOR_XRGB(R/2,G/2,B/2));

		}
	}
}




void CGroup4::Draw9(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum && y%2==0) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);



				const long Width = float (R+G+B)/30;

				AddVertex(x, y, y*3,CurrColor);
				AddVertex(x+Width*2, y*3+Width, y*3,CurrColor);
				AddVertex(x-Width*2, y*3+Width, y*3,D3DCOLOR_XRGB(R/2,G/2,B/2));


				AddVertex(x, y, y*3+100,D3DCOLOR_XRGB(255-R,255-G,255-B));
				AddVertex(x+Width, y+Width,y*3+100 ,D3DCOLOR_XRGB(255-R,255-G,255-B));
				AddVertex(x-Width, y+Width, y*3+100 ,D3DCOLOR_XRGB(255-R,255-G,255-B));


		}
	}
}



void CGroup4::Draw10(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = float (R+G+B)/50;

				AddVertex(x, y, R*3,D3DCOLOR_XRGB(R,0,0));
				AddVertex(x+Width, y+Width, R*3,D3DCOLOR_XRGB(R,0,0));
				AddVertex(x-Width, y+Width, R*3,D3DCOLOR_XRGB(R,0,0));

				AddVertex(x+Width, y+Width, G,D3DCOLOR_XRGB(0,G,0));
				AddVertex(x+Width, y, G,D3DCOLOR_XRGB(0,G,0));
				AddVertex(x, y+Width, G,D3DCOLOR_XRGB(0,G,0));

				AddVertex(x-Width, y-Width, -B*2,D3DCOLOR_XRGB(0,0,B));
				AddVertex(x-Width, y, -B*2,D3DCOLOR_XRGB(0,0,B));
				AddVertex(x, y-Width, -B*2,D3DCOLOR_XRGB(0,0,B));
				


		}
	}
}



void CGroup4::Draw11(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);
				const long Width = float (R+G+B)/20;

				AddVertex(x, y, R*3,D3DCOLOR_XRGB(R,0,0));
				AddVertex(x+Width, y+Width, G*3,D3DCOLOR_XRGB(0,G,0));
				AddVertex(x-Width, y+Width, B*3,D3DCOLOR_XRGB(0,0,B));
		}
	}
}



void CGroup4::Draw12(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				int z=(512-x)*(512-x)/400;
				const long Width = float (R+G+B)/25;

				AddVertex(x, y, z,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+Width*2, z,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, z+10,D3DCOLOR_XRGB(0,0,0));

				AddVertex(x, y, z,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+Width*2, z,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y+Width, z+10,D3DCOLOR_XRGB(0,0,0));

				AddVertex(x, y, z+10,D3DCOLOR_XRGB(255,50,0));
				AddVertex(x, y+5, z-10,D3DCOLOR_XRGB(255,50,0));


		}
	}
}


void CGroup4::Draw13(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if ((y+x)%2==0)
		{
		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float depth = 0.2f;
				const long Width = float (R+G+B)/25;

				int W=VertexCounter%10;

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 10,D3DCOLOR_XRGB(W,W,W));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y+Width, 10,D3DCOLOR_XRGB(W,W,W));

		}
		}
	}
}



void CGroup4::Draw14(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float depth = 0.2f;
				const long Width = float (R+G+B)/3/10+1;
				int W=0;

				AddVertex(x, y, 0,D3DCOLOR_XRGB(W,W,W));
				AddVertex(x+Width, y+Width*2, 1024/Width,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width*2, y, 0,D3DCOLOR_XRGB(W,W,W));
				AddVertex(x+Width, y-Width*2, 1024/Width,D3DCOLOR_XRGB(R,G,B));


		}
	}
}





void CGroup4::Draw15(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);

				int z=4000;
				AddVertex(x, y, z,D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+20, y, z,D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+20, y+40, z,D3DCOLOR_XRGB(-R,-G,-B));

				AddVertex(x, y, z,D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+40, y, z,D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+20, y-40, z,D3DCOLOR_XRGB(-R,-G,-B));


				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float depth = 0.2f;
				const long Width = float (R+G+B)/3/20;
				int W=VertexCounter%50*5;

				AddVertex(x, y, 0,D3DCOLOR_XRGB(W,W,W));
				AddVertex(x+Width*2, y, 0,D3DCOLOR_XRGB(W,W,W));
				AddVertex(x+Width, y+Width*2, 10,D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(W,W,W));
				AddVertex(x+Width*2, y, 0,D3DCOLOR_XRGB(W,W,W));
				AddVertex(x+Width, y-Width*2, 10,D3DCOLOR_XRGB(R,G,B));


		}
	}
}


void CGroup4::Draw16(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{

		COLORREF c = Pix;

	


		if (VertexCounter < VertexNum  && ((y-x)%2==0)) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float depth = 0.2f;
				const long Width = float (R+G+B)/3/10;
				int W=0;
				int trans=255;

				AddVertex(x, y, 20,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width*2, y, 0,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width, y-Width*2, -20,D3DCOLOR_COLORVALUE(R,G,B,trans));

				AddVertex(x, y, -20,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width*2, y, 0,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width, y-Width*2, 20,D3DCOLOR_COLORVALUE(R,G,B,trans));
	

		}
	}
}





void CGroup4::Draw17(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
//		g_pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, VertexCounter-1 );
	}
	else
	{
		COLORREF c = Pix;

		if (VertexCounter < VertexNum && ((y-x)%2==0)) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float depth = 0.2f;
				const long Width = float (R+G+B)/25;
				int W=255;
				int trans=0;

				if (R>100)
				{
				AddVertex(x, y, 0,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x-Width*2, y, 10,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x-Width, y-Width, -0.05,D3DCOLOR_COLORVALUE(R,G,B,trans));
				}
				
				if (G>100)
				{
				AddVertex(x, y, 5,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x-Width, y-Width, 5,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width, y-Width, -5,D3DCOLOR_COLORVALUE(R,G,B,trans));
				}

				if (B>100)
				{
				AddVertex(x, y, -10,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width*2, y, 10,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width, y-Width, 0,D3DCOLOR_COLORVALUE(R,G,B,trans));
				}	

				AddVertex(x-Width, y-Width,10,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x+Width, y-Width, -10,D3DCOLOR_COLORVALUE(W,W,W,trans));
				AddVertex(x, y-Width*2, 0,D3DCOLOR_COLORVALUE(R,G,B,trans));



		}
	}
}



void CGroup4::Draw18(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = 20;

				AddVertex(x, y, -R , CurrColor);
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width/2, y+Width*2, R ,D3DCOLOR_XRGB(0,0,0));


				AddVertex(x, y, -G , CurrColor);
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(-R/2,-G/2,-B/2));
				AddVertex(x+Width/2, y+Width*2, G ,D3DCOLOR_XRGB(0,0,0));

				AddVertex(x, y, -B , CurrColor);
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+Width/2, y+Width*2, B ,D3DCOLOR_XRGB(0,0,0));
				

		}
	}
}




void CGroup4::Draw19(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = 20;

				AddVertex(x, y, -R , CurrColor);
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(R/2,G/2,B/2));
				AddVertex(x+Width/2, y+Width, (float) -R ,D3DCOLOR_XRGB(0,0,0));


				AddVertex(x, y, -G , CurrColor);
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(-R/2,-G/2,-B/2));
				AddVertex(x+Width/2, y+Width,  G ,D3DCOLOR_XRGB(0,0,0));

				AddVertex(x, y, -B , CurrColor);
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+Width/2, y+Width, -B ,D3DCOLOR_XRGB(0,0,0));

				if (R>G) {AddVertex(x+Width/2, y+Width, B ,D3DCOLOR_XRGB(R,R,0));}	
				else
				if (G>B) {AddVertex(x+Width/2, y+Width, B ,D3DCOLOR_XRGB(G,0,G));}
				else
				{AddVertex(x+Width/2, y+Width, B ,D3DCOLOR_XRGB(0,B,B));}
				

		}
	}
}



void CGroup4::Draw20(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = 20;

				if (R>G) {
				AddVertex(x, y, -R , D3DCOLOR_XRGB(255,R/2,R/2));
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(R/2,255,R/2));
				AddVertex(x+Width/2, y+Width, -R ,D3DCOLOR_XRGB(0,0,0));
				} else

				if (R>B){
				AddVertex(x, y, -G , D3DCOLOR_XRGB(B/2,255,B/2));
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(B/2,B/2,255));
				AddVertex(x+Width/2, y+Width,  G ,D3DCOLOR_XRGB(0,0,0));
				}
				else
				{
				AddVertex(x, y, -B , D3DCOLOR_XRGB(G/2,G/2,255));
				AddVertex(x+Width, y, 0, D3DCOLOR_XRGB(255,G/2,G/2));
				AddVertex(x+Width/2, y+Width,  -B ,D3DCOLOR_XRGB(0,0,0));
				}
				
				
				

		}
	}
}


void CGroup4::Draw21(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);
				AddVertex(x, y, G*2 , D3DCOLOR_XRGB(R-50,150-G,200+B));
				AddVertex(x+R/10,  y+B/10, R*3 , D3DCOLOR_XRGB(-G,250+B*3,-B));
				AddVertex(x+G/10,  y-R/10 , -B*2 ,D3DCOLOR_XRGB(B*2,-B,B*5));
				
		}
	}
}

void CGroup4::Draw22(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = 20;

				
				AddVertex(x, y, +R , D3DCOLOR_XRGB(R,R*2,R*4));
				AddVertex(x, y+R/10, -G, D3DCOLOR_XRGB(-R*4,-R*2,-R));
				AddVertex(x+R/10, y+R/20 ,+B ,D3DCOLOR_XRGB(0,0,0));

				
				AddVertex(x+G/20, y , -G ,D3DCOLOR_XRGB(0,G*20,0));
				AddVertex(x+G/20, y+G/10,B , D3DCOLOR_XRGB(0,0,G*10));
				AddVertex(x-G/20, y+G/10,R, D3DCOLOR_XRGB(-G*3,0,0));

				AddVertex(x, y+B/10, -B , D3DCOLOR_XRGB(0,0,B*10));
				AddVertex(x+B/20, y, -R, D3DCOLOR_XRGB(B*10,0,0));
				AddVertex(x+B/10, y+R/10 , 0 ,D3DCOLOR_XRGB(255,255,255));
				

				
				
		}
	}
}



void CGroup4::Draw23(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {
				if (y%3==0) y=y+2;

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = 20;

				
				AddVertex(x, y, +R , D3DCOLOR_XRGB(R,R*2,R*4));
				AddVertex(x, y+R/10,  -G, D3DCOLOR_XRGB(-R*4,-R*2,-R));
				AddVertex(x+R/10, y+R/20 , B ,D3DCOLOR_XRGB(0,0,0));

				
				AddVertex(x+G/20, y ,  -G ,D3DCOLOR_XRGB(0,G*20,0));
				AddVertex(x+G/20, y+G/10, B , D3DCOLOR_XRGB(0,0,G*10));
				AddVertex(x-G/20, y+G/10, R, D3DCOLOR_XRGB(-G*3,0,0));

				AddVertex(x, y+B/10,  -B , D3DCOLOR_XRGB(0,0,B*10));
				AddVertex(x+B/20, y,  -R, D3DCOLOR_XRGB(B*10,0,0));
				AddVertex(x+B/10, y+R/10 , 0 ,D3DCOLOR_XRGB(255,255,255));

				AddVertex(x, y , 0 ,D3DCOLOR_XRGB(R,R,0));
				

				
				
		}
	}
}



void CGroup4::Draw24(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = 20;

				
								
				if ((R>G) && (R>B)) 
				{AddVertex(x, y, +R, D3DCOLOR_XRGB(R,0,0));
				AddVertex(x, y , 0 ,D3DCOLOR_XRGB(R,0,R));}
				else
				if ((G>R) && (G>B)) 
				{AddVertex(x, y, +G , D3DCOLOR_XRGB(0,G,0));
				AddVertex(x, y , 0 ,D3DCOLOR_XRGB(0,G,G));}

				else
				{AddVertex(x, y, -B ,D3DCOLOR_XRGB(0,0,B));
				AddVertex(x, y , 0 ,D3DCOLOR_XRGB(B,B,0));}
		
		}
	}
}


void CGroup4::Draw25(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {
				if (y%3==0) y=y+2;

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = 20;


				for (int i=(R%20)+10; i>10; i-=5)
				{
				AddVertex(x+i/2, y+2+i , 0 ,D3DCOLOR_XRGB(i*2,0,i*5));
				AddVertex(x-i, y, -i , D3DCOLOR_XRGB(R+i*5,G+i*5,B-i*10));
				AddVertex(x+i, y-2, i, D3DCOLOR_XRGB(155-i*5,155-i*5,155-i*5));
				
				}

				
		}
	}
}


void CGroup4::Draw26(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				
				float depth = 0.2f;
				const long Width = (R+G+B)/3/15;

				AddVertex(x+Width, y,  -Width , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y, Width, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+Width , 0 ,D3DCOLOR_XRGB(0,0,0));

				AddVertex(x+Width, y+Width*2, -Width , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y+Width*2, 0, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+Width , -Width ,D3DCOLOR_XRGB(0,0,0));


				
		}
	}
}



void CGroup4::Draw27(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/10;
				float depth = 0.2f;
				

				if (lasty < y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(20,0,Width));

				}
				else
				{
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(255,00,255));
				AddVertex(x, y, (float) -Width/300 , D3DCOLOR_XRGB(00,255,00));
				AddVertex(x, y+Width, (float) -Width/300 , D3DCOLOR_XRGB(00,00,255));
				}

				lasty=y;
				
				
		}
	}
}




void CGroup4::Draw28(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {

				if (y%3==0) y=y+2;

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/8;
				float depth = 0.2f;
				


				if (lasty < y)
				{

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(20,0,Width));

				}
				else
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(255,255,00));

				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));

				lasty=y;
				
				
		}
	}
}

void CGroup4::Draw29(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/8;

				

				if (lasty > y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,y%255));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G%255,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(255,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(R%20,G%255,Width));
				}
				else
				{
				AddVertex(x, y,  -Width/600 , D3DCOLOR_XRGB(R,G,00));
				AddVertex(x+Width/2, y+Width/2, -Width/600 , D3DCOLOR_XRGB(R,00,G));
				AddVertex(x, y+Width/2, -Width/600 , D3DCOLOR_XRGB(B,R,G));
				}

				lasty=y;
				
				
		}
	}
}



void CGroup4::Draw30(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%2==0)) {
				if (y%3==0) y=y+2;



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/10;
				float depth = 0.2f;
				

				if (lasty < y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(20,0,Width));
				

				}
				
				if (lastx!=x)
				
				{
				AddVertex(x+Width, y-Width*5, (float) -Width/300 , D3DCOLOR_XRGB(255,255,00));



				lastx=x;
				}

				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));

				

				
				
		}
	}
}





void CGroup4::Draw31(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/10;
				float depth = 0.2f;
				

				if (lasty < y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(20,0,Width));
				}
				
				if (lastx!=x)
				
				{
				AddVertex(x+Width, y-Width*5, (float) -Width/300 , D3DCOLOR_XRGB(255,255,00));

				y=y-Width*5;

				AddVertex(x, y, (float) +R/1000 , D3DCOLOR_XRGB(255,R*2,R*4));
				AddVertex(x, y+R/7, (float) -G/1000, D3DCOLOR_XRGB(255,-R*2,-R));
				AddVertex(x+R/7, y+R/14 , (float) +B/1000 ,D3DCOLOR_XRGB(255,0,0));

				
				AddVertex(x+G/14, y , (float) -G/1000 ,D3DCOLOR_XRGB(255,G*20,0));
				AddVertex(x+G/14, y+G/7, (float) (B/1000) , D3DCOLOR_XRGB(255,0,G*10));
				AddVertex(x-G/14, y+G/7, (float) (R/1000), D3DCOLOR_XRGB(255,0,0));

				AddVertex(x, y+B/7, (float) -B/1000 , D3DCOLOR_XRGB(255,0,B*10));
				AddVertex(x+B/14, y, (float) -R/1000, D3DCOLOR_XRGB(255,0,0));
				AddVertex(x+B/7, y+R/7 , 0 ,D3DCOLOR_XRGB(255,255,255));
				lastx=x;
				}

				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));

				

			
		}
	}
}



void CGroup4::Draw32(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/10;
				float depth = 0.2f;
				

				if (lasty < y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 50,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x-Width, y+Width, 50,D3DCOLOR_XRGB(20,0,Width));
				

				}
				
				if (lastx!=x)
				
				{
				AddVertex(x+Width, y-Width*5, (float) -Width , D3DCOLOR_XRGB(255,255,00));

				y=y-Width*5;

				AddVertex(x, y,  +R , D3DCOLOR_XRGB(255,R*2,R*4));
				AddVertex(x, y+R/5, -G, D3DCOLOR_XRGB(255,-R*2,-R));
				AddVertex(x+R/5, y+R/10 , +B ,D3DCOLOR_XRGB(255,0,0));

				
				AddVertex(x+G/20, y , -G ,D3DCOLOR_XRGB(255,G*20,0));
				AddVertex(x+G/20, y+G/10, B , D3DCOLOR_XRGB(255,0,G*10));
				AddVertex(x-G/20, y+G/10, R, D3DCOLOR_XRGB(255,0,0));

				AddVertex(x, y+B/10, -B, D3DCOLOR_XRGB(255,0,B*10));
				AddVertex(x+B/20, y, -R, D3DCOLOR_XRGB(255,0,0));
				AddVertex(x+B/10, y+R/10 , 0 ,D3DCOLOR_XRGB(255,255,255));
				
				y=y+Width*5;

				AddVertex(x+B/10, y+R/10 , 0 ,D3DCOLOR_XRGB(0,0,255));
				AddVertex(x+B/10, y+R/10 , 0 ,D3DCOLOR_XRGB(0,0,255));

				AddVertex(lastx, lasty ,-G ,D3DCOLOR_XRGB(0,G*20,255));
				AddVertex(lastx+B/5, lasty, B , D3DCOLOR_XRGB(G*10,0,255));
				AddVertex(lastx, lasty+B/2.5, R , D3DCOLOR_XRGB(0,0,255));
				
		
				lastx=x;


				}

			
				lasty=y;
			
		}
	}
}


void CGroup4::Draw33(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
//		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum ) {
//				if (y%3==0) y=y+2;


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;

				
				const long Width = (R+G+B)/3/10;

				AddVertex(x, y, (float) Width/300 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y, (float) -Width/300, D3DCOLOR_XRGB(0,0,0));
				AddVertex(x+Width, y+3, (float) -Width/300, D3DCOLOR_XRGB(R,G,B));

				AddVertex(x+Width, y+Width, (float) Width/100, D3DCOLOR_XRGB(R,G,0));
				AddVertex(x+Width, y+Width+3, (float) Width/100, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+3, y+Width, (float) -Width/100, D3DCOLOR_XRGB(R,0,B));


				AddVertex(x, y+Width, (float) -Width/100, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+3, (float) Width/300 , D3DCOLOR_XRGB(0,-G,-B));
				AddVertex(x, y+3, (float) Width/300 , D3DCOLOR_XRGB(0,-G,-B));
				
			
		}
	}
}




void CGroup4::Draw34(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		if (VertexCounter < VertexNum && (y%2==0)) {
				if (y%3==0) y=y+2;
				

				COLORREF c = Pix;
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float depth = 0.2f;
				const long Width = (R+G+B)/3;

				AddVertex(x, y, 0 , D3DCOLOR_XRGB(0,0,0));

				for (int i=0; i<3; i++)
				{
				AddVertex(x-i*10+23, y-12, Width-125 , D3DCOLOR_XRGB(R-i*10,0,B-i*10));
				AddVertex(x+i*10-24, y+12, -Width+125 , D3DCOLOR_XRGB(R-25+i*10,G-50+i*20,B));
				AddVertex(x+i*10-23, y+11, -Width+125 , D3DCOLOR_XRGB(R-25+i*10,G-50+i*20,B));

				}

				AddVertex(x, y, 0 , D3DCOLOR_XRGB(0,0,0));


			
		}
	}
}


void CGroup4::Draw35(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	if (bRender) 
	{

		long CurrPos = 0;
		long Count = 4; // num of triangles
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );

/*		while (CurrPos < min(MaxPrimitiveCount, VertexCounter-2-Count)) {
			g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, CurrPos, Count );
			CurrPos += Count+2;
		}
*/
	}
	else
	{

		if (VertexCounter < VertexNum){
				if (y%3==0) y=y+50;

				COLORREF c = Pix;
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);

				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float depth = 0.2f;
				const long Width = (R+G+B)/3/10;

				AddVertex(x, y,  Width/2, D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+Width, y+Width, Width, D3DCOLOR_XRGB(R,0,0));
				AddVertex(x+Width, y-Width,  -Width, D3DCOLOR_XRGB(0,G,0));


				AddVertex(x-Width, y-Width, Width, D3DCOLOR_XRGB(0,0,0));
				AddVertex(x-Width, y+Width, -Width, D3DCOLOR_XRGB(R,0,0));
				AddVertex(x+Width, y+Width,  Width, D3DCOLOR_XRGB(0,G,B));
				
		

		}
	}
}


void CGroup4::Draw36(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		if (VertexCounter < VertexNum && y%100<40) {
				
				COLORREF c = Pix;
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				int ava=(R+G+B)/3;
				int Width =ava/10;
				
				int i=Width;

				AddVertex(x, y-i, y , D3DCOLOR_XRGB(ava, 0, ava));
				AddVertex(x+i*2, y+i, y , D3DCOLOR_XRGB(R,0,0));
				AddVertex(x-i*2, y-i, y , D3DCOLOR_XRGB(R,0,B));

				AddVertex(x, y-ava, x , D3DCOLOR_XRGB(ava, 0, ava));
				AddVertex(x+i, y-i, x , D3DCOLOR_XRGB(0,0,B));
				AddVertex(x-i, y+i, x , D3DCOLOR_XRGB(R,G,0));

		
		}
	}
}


void CGroup4::Draw37(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		if (VertexCounter < VertexNum && y%3==0) {
				

				
				COLORREF c = Pix;
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				int ava=(R+G+B)/3;
				int Width =ava*2;;
				
				int i=ava/12;

				if (lasty < y)
				{
				AddVertex(x, y+ava/10, Width , D3DCOLOR_XRGB(ava, 0, ava));
				AddVertex(x+i, y+i, 0 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-i, y+i, 0 , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y+ava/10, Width , D3DCOLOR_XRGB(ava, 0, ava));
				AddVertex(x+i, y-i, 0 , D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x-i, y-i, 0 , D3DCOLOR_XRGB(-R,-G,-B));

				AddVertex(x, y+ava/10, Width , D3DCOLOR_XRGB(ava, 0, ava));
				AddVertex(x-i, y+i, 0 , D3DCOLOR_XRGB(G,B,R));
				AddVertex(x-i, y-i, 0 , D3DCOLOR_XRGB(-G,-B,-R));

				AddVertex(x, y+ava/10, Width , D3DCOLOR_XRGB(ava, 0, ava));
				AddVertex(x+i, y+i, 0 , D3DCOLOR_XRGB(R,B,G));
				AddVertex(x+i, y-i, 0 , D3DCOLOR_XRGB(-R,-B,-G));
				}

				if (lastx!=x)
				
				{
				
				AddVertex(x-i, y, -0.01 , D3DCOLOR_XRGB(155+R%100, 155+G%100, 0));
				AddVertex(x+i, y-i, -0.01 , D3DCOLOR_XRGB(155+R%100, 155+G%100, 0));
				AddVertex(x+i/2, y-R/2, 0.01 , D3DCOLOR_XRGB(155+R%100, 155+G%100, 0));

				AddVertex(x-i, y, 0.01 , D3DCOLOR_XRGB(0, 0, 155+B%100));
				AddVertex(x+i, y-i, 0.01 , D3DCOLOR_XRGB(0,0, 155+B%100));
				AddVertex(x+i/2, y-G/2, -0.01 , D3DCOLOR_XRGB(255,155+G%100, 155+B%100));

				AddVertex(x-i, y, -0.01 , D3DCOLOR_XRGB(155+R%100,0, B%100));
				AddVertex(x+i, y-i, -0.01 , D3DCOLOR_XRGB(155+R%100,0, B%100));
				AddVertex(x+i/2, y-B/2, 0.01 , D3DCOLOR_XRGB(155+R%100,255, B%100));
				lastx=x;
				}

				lasty=y;

		
		}
	}
}






void CGroup4::Draw38(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		if (VertexCounter < VertexNum && y%10>5) {
				

				
				COLORREF c = Pix;
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

			
				int ava=(R+G+B)/3;
				int Width =ava;
				int i=ava/20;

				
				AddVertex(x, y,  -Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y,  -Width , D3DCOLOR_XRGB(R,0, B));
				AddVertex(x, y+i*2,  Width , D3DCOLOR_XRGB(0,0, B));


				AddVertex(x+i, y+i*2,  Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y,  -Width , D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+i*2,  Width , D3DCOLOR_XRGB(R,G, B));
				
		
		}
	}
}



void CGroup4::Draw39(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		if (VertexCounter < VertexNum && y%10>6) {
				

				
				COLORREF c = Pix;
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				
				int ava=(R+G+B)/3;
				int Width =ava;
				int i=ava/10;

				
				AddVertex(x, y, -Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y,  -Width , D3DCOLOR_XRGB(R,0, B));
				AddVertex(x, y+i*2,  Width , D3DCOLOR_XRGB(0,0, B));
				AddVertex(x+i, y+i*2,  Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y,  -Width , D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+i*2,  Width , D3DCOLOR_XRGB(R,G, B));


				AddVertex(x, y+i,  -Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y+i,  -Width , D3DCOLOR_XRGB(R,0, B));
				AddVertex(x, y+i*3,  Width , D3DCOLOR_XRGB(0,0, B));
				AddVertex(x+i, y+i*3,  Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y+i,  -Width , D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+i*3,  Width , D3DCOLOR_XRGB(R,G, B));


				AddVertex(x, y+i,  -Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y+i,  -Width , D3DCOLOR_XRGB(R,0, B));
				AddVertex(x, y+i*3,  -Width , D3DCOLOR_XRGB(0,0, B));
				AddVertex(x+i, y+i*3,  -Width , D3DCOLOR_XRGB(R,G, B));
				AddVertex(x+i, y+i,  -Width , D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+i*3,  -Width , D3DCOLOR_XRGB(R,G, B));
				
		
		}
	}
}



void CGroup4::Draw40(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%3==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;

				float depth = 0.2f;
				const long Width = (R+G+B)/3/10;
				for (int i=0; i<360; i+=90)
				{
				AddVertex(x+cos(i)*ava, y+sin(i)*ava, VertexNum/256, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(i+90)*ava, y+sin(i+90)*ava, VertexNum/256, D3DCOLOR_XRGB(R,G,B));
				}



				
		}
	}
}


void CGroup4::Draw41(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%10>5) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int Width = ava;

				for (int i=0; i<360; i+=90)
				{
				AddVertex(x, y-2, -Width , D3DCOLOR_XRGB(255,255,255));
				AddVertex(x+cos(i)*ava, y+sin(i)*ava, 0 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-cos(i)*ava, y-sin(i)*ava, 0 , D3DCOLOR_XRGB(R,G,B));
				}



				
		}
	}
}


void CGroup4::Draw42(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum  && y%2==0 && x%3==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/35;

				float depth = 0.2f;
				const long Width = (R+G+B)/3/10;

				for (int i=0; i<30; i+=5)
				{
				AddVertex(x+cos(i)*ava, y+sin(i)*ava,  i  , D3DCOLOR_XRGB(R,0,0));
				AddVertex(x+cos(i+60)*ava, y+sin(i+60)*ava, 0 , D3DCOLOR_XRGB(255,0,B));
				AddVertex(x-cos(i+120)*ava, y-sin(i+120)*ava, -i , D3DCOLOR_XRGB(R,0,255));
				}
			
		}
	}
}



void CGroup4::Draw43(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				int Width = (R+G+B)/3/10;
						

				if (lastx!=x)
				
				{
				AddVertex(x+Width, y-Width*5, -Width, D3DCOLOR_XRGB(0,G,00));

				lastx=x;
				}

				AddVertex(x+Width, y+Width*10, Width , D3DCOLOR_XRGB(R,0,0));
				AddVertex(x-Width, y, -Width , D3DCOLOR_XRGB(00,00,B));
	
		}
	}
}



void CGroup4::Draw44(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);

				const long Width = (R+G+B)/3/10;

				AddVertex(x, y, 0 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y, 0 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0 , D3DCOLOR_XRGB(R,G,B));

				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				
				R=-R;
				int z=1000;
				int oldx=x; int oldy=y; x=x/2; y=768-y;

				if (R<-150)
				{
				AddVertex(x, y, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, z , D3DCOLOR_XRGB(R,G,B));
				}

				else
					
				{

				R=-R; B=-B;
				x=oldx; x=1024-x; y=y/2; z=2000; 
				AddVertex(x, y, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, z , D3DCOLOR_XRGB(R,G,B));
				}
				

			
		}
	}
}


void CGroup4::Draw45(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{

		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
		lightx=lightx+=5;
		lighty=lighty+=5;

	

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));

				const int Width = (R+G+B)/3/10;
				
				
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				if (R>100 && G>50 && B>50)
				{

				AddVertex(x, y, R*2 , D3DCOLOR_XRGB(R+100,G,B));
				AddVertex(x+Width, y, G*2 , D3DCOLOR_XRGB(R+100,G,B));
				AddVertex(x+Width, y+Width, B*2 , D3DCOLOR_XRGB(R+100,G,B));

				AddVertex(x, y, R , D3DCOLOR_XRGB(R,G+100,B));
				AddVertex(x+Width, y+Width, G , D3DCOLOR_XRGB(R,G+100,B));
				AddVertex(x, y+Width, B , D3DCOLOR_XRGB(R,G+100,B));				}

				}
			

	}
}


void CGroup4::Draw46(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{

		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );

	

	}
	else
	{
		COLORREF c = Pix;





			if (VertexCounter < VertexNum) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));

				int Width = (R+G+B)/3/10;

				
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				if (R>100)
				{
				for (int i=0; i<360; i+=120)
				{
				AddVertex(x+cos(i+30)*R/10, y+sin(i+30)*R/10, sin(i+30)*R/5 , D3DCOLOR_XRGB(R+100,G,B));
				AddVertex(x+cos(i)*G/11, y+sin(i)*G/10, sin(i)*G/5 , D3DCOLOR_XRGB(R,G+100,B));
				AddVertex(x+cos(i+60)*B/10, y+sin(i+60)*B/10, -sin(i+60)*B/5 , D3DCOLOR_XRGB(R,G,B+100));
				}
				}
		}

	}
}


void CGroup4::Draw47(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{


			g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
		
	

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%2==0) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));

				
				
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				const long Width = (R+G+B)/3/5;
				

				int x1=0;
				int y1=0;

				if (x>512) x1=1024;
				if (y>768/2) y1=768;

				AddVertex(x1, y1, 4000 , D3DCOLOR_XRGB(0,0,0));
				AddVertex(x+Width, y, -Width*5 , D3DCOLOR_XRGB(y%10*25,x%10*25,B));
				AddVertex(x+Width, y+Width , 0, D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y, Width*4 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width*2, y+Width, -Width , D3DCOLOR_XRGB(y%10*25,x%10*25,B));
				AddVertex(x, y+Width, 0 , D3DCOLOR_XRGB(R,G,B));
			}


			

	}
}




void CGroup4::Draw48(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%2==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/32;

				
				int Width = ava*4+128;

				for (int i=0; i<360; i+=60)
				{
				AddVertex(x+cos(i)*ava, y+sin(i)*ava, -Width , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(i+30)*ava, y+sin(i+30)*ava, -Width , D3DCOLOR_XRGB(R/3,G/3,B/3));
				AddVertex(x+cos(i+60)*ava, y+sin(i+60)*ava, -Width , D3DCOLOR_XRGB(R/10,G/10,B/10));
				}



				
		}
	}
}



void CGroup4::Draw49(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%2==0 && x%2==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/32;

				
				int Width = ava;
				int depth = Width*10-125;
				if (Width>10)
				{
				
					if (R>150)
					{
				AddVertex(x, y, depth , D3DCOLOR_XRGB(255,255,255));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y , depth, D3DCOLOR_XRGB(0,0,0));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y , depth, D3DCOLOR_XRGB(0,0,0));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));
					}

					if (G>150 || B>150)
					{



				AddVertex(x, y-Width*2,depth , D3DCOLOR_XRGB(255,255,255));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y-Width*2, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y-Width*2 , depth, D3DCOLOR_XRGB(0,0,0));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y-Width*2, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y-Width*2 ,depth , D3DCOLOR_XRGB(0,0,0));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));
				}}
				
		}
	}
}


void CGroup4::Draw50(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%2==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				long R1=0, G1=0, B1=255;
				long R2=255, G2=100, B2=100;

				x=x+x%2;

				float ava=5-(R+G+B)/40;
				long Width = (R+G+B)/50;
				int depth = Width*10-125;
				

				AddVertex(x, y, depth , D3DCOLOR_XRGB(R1,G1,B1));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y , depth, D3DCOLOR_XRGB(R2, G2, B2));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y , depth, D3DCOLOR_XRGB(R2, G2,B2));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y-Width*2,depth , D3DCOLOR_XRGB(R1, G1, B1));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y-Width*2, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y-Width*2 , depth, D3DCOLOR_XRGB(R2, G2, B2));
				AddVertex(x+Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x, y-Width*2, depth , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y-Width*2 ,depth , D3DCOLOR_XRGB(R2, G2, B2 ));
				AddVertex(x-Width, y-Width,depth , D3DCOLOR_XRGB(R,G,B));

				
		}
	}
}



void CGroup4::Draw51(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



		if (VertexCounter < VertexNum && (y%5==0)) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/50;

				float depth = 0.2f;
				const long Width = (R+G+B)/3;
				for (int i=0; i<360; i+=90)
				{
				AddVertex(x+cos(i)*ava, y+sin(i)*ava, -Width , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(i-20)*ava/2, y+sin(i-20)*ava/2, 0 , D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+cos(i+20)*ava, y+sin(i+20)*ava, i/10 , D3DCOLOR_XRGB(R,G,B));
				}
				
		}
	}
}



void CGroup4::Draw52(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;


				const long Width = (R+G+B)/3/10;
				int z;
				z=1000-((x-512)/15)*((x-512)/15);

				
				AddVertex(x, y+ava, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y, z , D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x, y, z, D3DCOLOR_XRGB(R,G,B));



				
		}
	}
}

void CGroup4::Draw53(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;


				const long Width = (R+G+B)/3/10;
				int z;
				z=((x-512)/12)*((x-512)/12);

				
				AddVertex(x, y+ava, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y, z , D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x, y, z, D3DCOLOR_XRGB(R,G,B));



				
		}
	}
}



void CGroup4::Draw54(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;


				const long Width = (R+G+B)/3/10;
				int z=((x-512)/12)*((x-512)/12);

				
				
				
				AddVertex(x, y, 000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+ava, 2000  , D3DCOLOR_XRGB(0,0,0));
				AddVertex(x, y, 2000 , D3DCOLOR_XRGB(R,G,B));



				
		}
	}
}



void CGroup4::Draw55(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
			g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;


				const long Width = (R+G+B)/3/10;
				int z=((x-512)/12)*((x-512)/12);

				
				
				
				AddVertex(x-ava, y, 000 , D3DCOLOR_XRGB(0,0,0));
				AddVertex(x+ava, y+ava, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-ava, y+ava, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-ava, y-ava, z  , D3DCOLOR_XRGB(R,G,B));

			
		}
	}
}

void CGroup4::Draw56(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;


				const long Width = (R+G+B)/3/10;
				int z;
				z=((x-512)/15)*((x-512)/15)+((y-512)/16)*((y-512)/15);

				AddVertex(x, y+ava, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y, z , D3DCOLOR_XRGB(0,0,0));
				AddVertex(x, y, z, D3DCOLOR_XRGB(R,G,B));
				
		}
	}
}







void CGroup4::Draw57(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
			g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%3==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				long Width = (R+G+B)/3/10;
				int z;
				z=((x-512)/15)*((x-512)/15)+((y-512)/16)*((y-512)/15);

				AddVertex(x, y, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y,2000 , D3DCOLOR_XRGB(0,0,0));

				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				for (int i=0; i<360; i+=120)
				{
					
				AddVertex(x-sin(i)*20, y-cos(i)*20, z , D3DCOLOR_XRGB(x%10*10,G,B));
				AddVertex(x+sin(i)*20, y+cos(i)*20, z , D3DCOLOR_XRGB(x%10*10,G-y%10*10,B));
				}




				
		}
	}
}

void CGroup4::Draw58(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
			g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && x%3==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);

				const long Width = (R+G+B)/3/10;
				int z;
				z=((x-512)/15)*((x-512)/15)+((y-512)/16)*((y-512)/15);

				AddVertex(x, y, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y,2000 , D3DCOLOR_XRGB(0,0,0));

				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);



				AddVertex(x-sin(10)*20, y-cos(10)*20, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(10)*20, y+cos(10)*20, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(190)*20, y+cos(190)*20, z , D3DCOLOR_XRGB(R-50,G-30,B+50));




				
		}
	}
}



void CGroup4::Draw59(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
			g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);


				
				AddVertex(x,0, y*2  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+10,0, y*2+10  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+10,2, y*2+10  , D3DCOLOR_XRGB(R,G,B));

/*				AddVertex(x,1024, y*2  , D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+10,1024, y*2+10  , D3DCOLOR_XRGB(-R,-G,-B));
				AddVertex(x+12,1022, y*2+10  , D3DCOLOR_XRGB(-R,-G,-B));
*/				



				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);
				x=x*2;

				if (R>220 || G>220 || B>220)
				{
				AddVertex(512, 768/2,4000 , D3DCOLOR_XRGB(0,0,0));
				AddVertex(x, y, x  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+10, x+10  , D3DCOLOR_XRGB(R,G,B));
				}


		}
	}
}


void CGroup4::Draw60(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
		lasty=0;
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%2==0) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/10;

				

				if (lasty < y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(20,0,Width));
				

				}
				
				if (lastx!=x)
				
				{
					if (x<512) 	AddVertex(0, y, 4000 , D3DCOLOR_XRGB(255,255,00));
					else
						AddVertex(1024, y, 4000 , D3DCOLOR_XRGB(255,255,00));


				lastx=x;
				}

				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));

				

				
				
		}
	}
}


void CGroup4::Draw61(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum ) {



				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				const long Width = (R+G+B)/3/10;
			

				for (int i=0; i<30; i+=10)
				{

					if (i>0 && (R>200 || G>200 || B>200))
					{
				int co=i*10;
				AddVertex(x, y, i*100,D3DCOLOR_XRGB(R-co,G-co,0));
				AddVertex(x+Width*2, y, i*100,D3DCOLOR_XRGB(R-co,G-co,B-co));
				AddVertex(x+Width, y+Width, i*100,D3DCOLOR_XRGB(R-co,G-co,B-co));
					}
				}
				
				
		}
	}
}


void CGroup4::Draw62(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;

				if (R<128) R=R*2;
							else R=256;

				if (G<128) G=G*2;
							else G=256;

				if (B<128) B=B*2;
							else B=256;


				int i=ava*2;
				
				AddVertex(x+cos(ava)*i, y+sin(ava)*i, ava*5 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+60)*i, y+sin(ava+60)*i, ava*5 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+120)*i, y+sin(ava+120)*i, ava*5 , D3DCOLOR_XRGB(R,G,B));



	
				
		}
	}
}


void CGroup4::Draw63(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%3==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;

				if (R<128) R=R*2;
							else R=256;

				if (G<128) G=G*2;
							else G=256;

				if (B<128) B=B*2;
							else B=256;
				
				
				for (int i=ava; i>00; i-=15)
				{
				R=R+i; G=G+i; B=B+i;
				AddVertex(x+cos(ava+i)*i, y+sin(ava)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+60)*i, y+sin(ava+i+60)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+120)*i, y+sin(ava+i+120)*i, 1000 , D3DCOLOR_XRGB(R,G,B));

				i=i+50;
				AddVertex(x+cos(ava+i)*i, y+sin(ava)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+60)*i, y+sin(ava+i+60)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+120)*i, y+sin(ava+i+120)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				i=i-50;
				
				}



			
				
		}
	}
}



void CGroup4::Draw64(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;

				if (R<128) R=R*2;
							else R=256;

				if (G<128) G=G*2;
							else G=256;

				if (B<128) B=B*2;
							else B=256;

							
							

				for (int i=ava; i>00; i-=20)
				{
				R=R+i; G=G+i; B=B+i;
				AddVertex(x+cos(ava+i)*i, y+sin(ava)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+60)*i, y+sin(ava+i+60)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+120)*i, y+sin(ava+i+120)*i, 1000 , D3DCOLOR_XRGB(R,G,B));

				i=i+50;
				AddVertex(x+cos(ava+i)*i, y+sin(ava)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+60)*i, y+sin(ava+i+60)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+i+120)*i, y+sin(ava+i+120)*i, 1000 , D3DCOLOR_XRGB(R,G,B));
				i=i-50;
				}



			
				
		}
	}
}


void CGroup4::Draw65(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/10;

				int r1=R/6;
				int g1=G/6;
				int b1=B/6;
							


				for (int i=0; i<360; i+=60)
				{

				AddVertex(x, y, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(i)*ava, y+sin(i)*ava, 1000+ava*3 , D3DCOLOR_XRGB(R-r1,G-g1,B-b1));
				AddVertex(x+cos(i+30)*ava, y+sin(i+30)*ava, 1000+ava*3 , D3DCOLOR_XRGB(R-r1*2,G-g1*2,B-b1*2));
				R=R-r1;
				G=G-g1;
				B=B+b1;
				}



			
				
		}
	}
}


void CGroup4::Draw66(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%7==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/10;

				int r1=R/6;
				int g1=G/6;
				int b1=B/6;
							


				for (int i=0; i<360; i+=60)
				{

				AddVertex(x, y, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(i)*ava, y+sin(i)*ava, 1000+ava*3 , D3DCOLOR_XRGB(R-r1,G-g1,B-b1));
				AddVertex(x+cos(i+30)*ava, y+sin(i+30)*ava, 1000+ava*3 , D3DCOLOR_XRGB(R-r1*2,G-g1*2,B-b1*2));
				R=R-r1;
				G=G-g1;
				B=B+b1;
				}



			
				
		}
	}
}



void CGroup4::Draw67(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%5==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				if (R>G && R>B)
				{G=0;
				B=0;
				}

				else
					if (G>R && G>B)
					{R=0;
					B=0;
					}

					else
					{G=0;
					R=0;
					}


				AddVertex(x, y, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+30, y, 1000+ava*3 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+10, y-20, 1000+ava*3 , D3DCOLOR_XRGB(0,0,0));

				AddVertex(x, y, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+30, y, 1000+ava*3 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+20, 1000+ava*3 , D3DCOLOR_XRGB(0,0,0));
			
				
		}
	}
}




void CGroup4::Draw68(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				if (R<G && R<B)
				{G=0;
				B=0;
				R=255-R;
				}

				else
					if (G<R && G<B)
					{R=0;
					B=0;
					G=255-G;
					}

					else
					{G=0;
					R=0;
					B=255-B;
					}

				if (R>150)
				{
				AddVertex(x, y, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+20, y, 1000+ava*3 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+10, y-10, 1000+ava*3 , D3DCOLOR_XRGB(255,255,255));
				}

				if (B>150 || G>150)
				{

				AddVertex(x, y, 1000 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+20, y, 1000+ava*3 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y+10, 1000+ava*3 , D3DCOLOR_XRGB(255,255,255));
				}
			
				

				

		}
	}
}






void CGroup4::DrawB01(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
//		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3 );
//		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
//	g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, min(VertexCounter-2, 1000) );
			g_pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, VertexCounter-1 );

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				
				if (x%2 == 0) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/50;

				int z=1000;
			
				
				AddVertex(x-ava, y, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y+ava, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-ava, y+ava, z  , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-ava, y-ava, z  , D3DCOLOR_XRGB(R,G,B));
				}
			
		}
	}
}



void CGroup4::DrawB02(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				if (x%5 == 0) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;


				const long Width = (R+G+B)/3/10;
				for (int i=0; i<360; i+=80)
				{
				AddVertex(x+cos(i)*ava, y+sin(i)*ava, ava*50 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(i+20)*ava, y+sin(i+20)*ava, ava*50 , D3DCOLOR_XRGB(R,G,B));

				}

			AddVertex(x, y, ava*50 , D3DCOLOR_XRGB(R-30,G-30,B-30));
				}
		}
	}
}






void CGroup4::DrawB03(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				if ((x+y)%10 == 0) {
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;


				const long Width = (R+G+B)/3/10;
				for (int i=0; i<360; i+=20)
				{
				AddVertex(x+cos(i)*ava+i/50, y+sin(i)*ava+i/50, y+sin(i)*ava*20 , D3DCOLOR_XRGB(R,G,B));


				}
				}

				
		}
	}
}





void CGroup4::DrawB04(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				if ((x+y)%8 == 0) {
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;


				const long Width = (R+G+B)/3/10;
				for (int i=0; i<360; i+=30)
				{
				AddVertex(x+cos(i)*ava*1.5, y+sin(i)*ava, ava*50 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(i+20)*ava*1.5, y+sin(i+20)*ava, ava*50 , D3DCOLOR_XRGB(R,G,B));

				}

			AddVertex(x, y, ava*50 , D3DCOLOR_XRGB(R-30,G-30,B-30));
				}
		}
	}
}

void CGroup4::DrawB05(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%4==0) {
				

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;

				if (R<128) R=R*2;
							else R=256;

				if (G<128) G=G*2;
							else G=256;

				if (B<128) B=B*2;
							else B=256;


				for (int i=40; i>00; i-=5)
				{
				AddVertex(x+cos(ava+i*10)*i, y+sin(ava+i*10)*i, ava*i , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(ava+(i+10)*10)*i, y+sin(ava+(i+10)*10)*i, ava*i , D3DCOLOR_XRGB(R,G,B));
				

				}


		}
				
		
	}
}



void CGroup4::DrawB06(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/4);
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, VertexCounter/4, VertexCounter/3 );
	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				if ((x+y)%7 == 0) {

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;

				if (R<128) R=R*2;
							else R=256;

				if (G<128) G=G*2;
							else G=256;

				if (B<128) B=B*2;
							else B=256;


				for (int i=50; i>00; i-=10)
				{
				AddVertex(x+cos(ava+i*10)*i, y+sin(ava+i*10)*i, ava*i , D3DCOLOR_XRGB(R,G,B));
				i=i-10;
				AddVertex(x+cos(ava+i*10)*i, y+sin(ava+i*10)*i, ava*i , D3DCOLOR_XRGB(R,G,B));
				i=i+10;
				AddVertex(x-cos(ava+i*10)*i, y+sin(ava-i*10)*i, ava*i , D3DCOLOR_XRGB(R,G,B));
				i=i-10;
				AddVertex(x-cos(ava+i*10)*i, y+sin(ava-i*10)*i, ava*i , D3DCOLOR_XRGB(R,G,B));
				i=i+10;
				}


				}
				
		}
	}
}



void CGroup4::DrawB07(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				if ((x+y)%8 == 0) {
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/30;


				for (int i=360; i>00; i-=20)
				{

				AddVertex(x+cos(i)*ava+i%30, y+sin(i)*ava+i%40, ava*10 , D3DCOLOR_XRGB(R,G,B));
				}


				}
				
		}
	}
}

















void CGroup4::DrawC01(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	

		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%3==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=ava;			
				
				AddVertex(x, y, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava*2, y, z+ava , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y+ava, z+ava*2 , D3DCOLOR_XRGB(R,G,B));

				R=-R;
				G=-G;
				B=B*2;
				z=z+1000;
				ava=ava*10;
				x=x-400;
				AddVertex(x, y, z , D3DCOLOR_XRGB(R-G,G-B,B-R));
				AddVertex(x+ava*2, y, z+ava , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y+ava, z+ava*2 , D3DCOLOR_XRGB(R+G,G+B,B+R));


				
				
		}
	}
}



void CGroup4::DrawC02(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=ava*2;			
				
				AddVertex(x, y, z , ava);
				AddVertex(x+ava*2, y, z+ava , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y+ava, z+ava*2 , D3DCOLOR_XRGB(R,G,B));

				R=-R;
				G=-G;
				B=B*2;
				z=z+1000;

				x=x-400;

				if (y%10==0)
				{
				AddVertex(x, 768-R, G , D3DCOLOR_XRGB(R-G,G-B,B-R));
				AddVertex(R, 768-G, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(z, 768-R, G , D3DCOLOR_XRGB(R+G,G+B,B+R));
				}

				if ((y%12)==0)
				{
				AddVertex(400-x, R, G , D3DCOLOR_XRGB(R-G,G-B,B-R));
				AddVertex(400-R, G, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(400-z,  R, G , D3DCOLOR_XRGB(R+G,G+B,B+R));
				}

				
				
		}
	}
}


void CGroup4::DrawC03(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=ava*2;			
				
				AddVertex(x, y, z , ava);
				AddVertex(x+ava*2, y, z+ava , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+ava, y+ava, z+ava*2 , D3DCOLOR_XRGB(R,G,B));

				R=-R;
				G=-G;
				B=B*2;
				z=z+1000;

				x=x-400;

				y=y*3;
				R=R*5;
				G=0;

				if (y%5==0)
				{
				AddVertex(x, y,  G , D3DCOLOR_XRGB(R-G,G-B,B-R));
				AddVertex(x+300, y ,  0 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+150, y+300 , G , D3DCOLOR_XRGB(R+G,G+B,B+R));


				AddVertex(R+200, y, B , D3DCOLOR_XRGB(R-G,G-B,B-R));
				AddVertex(R, y,  1024-B , D3DCOLOR_XRGB(R,G,B));
				AddVertex(R+150, y+300 , 1024-G , D3DCOLOR_XRGB(R+G,G+B,B+R));

				}

				
				
		}
	}
}


void CGroup4::DrawC04(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum && y%3==0) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=ava*100;			
				
				
				AddVertex(x+cos(x)*y, y+sin(y)*x, z , ava);
				AddVertex(x+cos(x+10)*y, y+sin(y+10)*x, z+ava , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+cos(x-10)*y, y+sin(y-10)*x, z+ava , D3DCOLOR_XRGB(R,G,B));
				
		
				
		}
	}
}



void CGroup4::DrawC05(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=120-y;			
				z=z*10+2500;
				x=x;
				
				AddVertex(x-10, y, z , D3DCOLOR_XRGB(y%10*25,y%10*25,B));
				AddVertex(x+10, y, z , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x, y-ava*2, z+ava , D3DCOLOR_XRGB(x%5*20+150,0,0));
				


		
				
		}
	}
}


void CGroup4::DrawC06(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=ava*2;			
				
				if (y%2==0 || (ava*5>240))
				{
				AddVertex(x+100*cos(x), y+100*sin(y),		z, D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+100*cos(x+20), y+100*sin(y),	z+ava , D3DCOLOR_XRGB(R*6,0 ,B*9));
				AddVertex(x+100*cos(x), y+100*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,-G,-B));
				}
				
		}
	}
}



void CGroup4::DrawC07(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;


				int z=ava*2;			
				R=R*5;
				B=B*5;

				if (y%10==0 && ava>20)
				{
				AddVertex(R+50*cos(x), G+50*sin(y),		z, D3DCOLOR_XRGB(R,G,B));
				AddVertex(R+50*cos(x+20), G+50*sin(y),	z+ava , D3DCOLOR_XRGB(R*6,0 ,B*9));
				AddVertex(R+50*cos(x), G+50*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,-G,-B));
				}


				if (y%11==0 && ava>20)
				{
				AddVertex(G+50*cos(x), B+50*sin(y),		z, D3DCOLOR_XRGB(R,0,B));
				AddVertex(G+50*cos(x+20), B+50*sin(y),	z+ava , D3DCOLOR_XRGB(R*6,0 ,B*9));
				AddVertex(G+50*cos(x), B+50*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,0,-B));
				}


				if (y%12==0)
				{
				AddVertex(B+50*cos(x), R+50*sin(y),		z, D3DCOLOR_XRGB(0,R,B));
				AddVertex(B+50*cos(x+20), R+50*sin(y),	z+ava , D3DCOLOR_XRGB(0, G*6 ,B*9));
				AddVertex(B+50*cos(x), R+50*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(0,-R,-B));
				}


				if (y%100==0)
				{
				AddVertex(R+50*cos(x), G+50*sin(y),		z, D3DCOLOR_XRGB(B,R,0));
				AddVertex(G+50*cos(x+20), B+50*sin(y),	z+ava , D3DCOLOR_XRGB(G*6 ,B*9,0));
				AddVertex(B+50*cos(x), R+50*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,-B,0));
				}






				
		}
	}
}




void CGroup4::DrawC08(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=ava*2;			
				R=R*5;
				B=B*5;

				if (y%10==0)
				{
				AddVertex(R+ava*cos(x), G+ava*sin(y),		z, D3DCOLOR_XRGB(R,G,B));
				AddVertex(R+ava*cos(x+20), G+ava*sin(y),	z+ava , D3DCOLOR_XRGB(R*6,0 ,B*9));
				AddVertex(R+ava*cos(x), G+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,-G,-B));
				}


				if (y%11==0)
				{
				AddVertex(G+ava*cos(x), B+ava*sin(y),		z, D3DCOLOR_XRGB(R,0,B));
				AddVertex(G+ava*cos(x+20), B+ava*sin(y),	z+ava , D3DCOLOR_XRGB(R*6,0 ,B*9));
				AddVertex(G+ava*cos(x), B+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,0,-B));
				}


				if (y%12==0)
				{
				AddVertex(B+ava*cos(x), R+ava*sin(y),		z, D3DCOLOR_XRGB(0,R,B));
				AddVertex(B+ava*cos(x+20), R+ava*sin(y),	z+ava , D3DCOLOR_XRGB(0, G*6 ,B*9));
				AddVertex(B+ava*cos(x), R+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(0,-R,-B));
				}



				if (y%13==0)
				{
				AddVertex(R-B+ava*cos(x), R+ava*sin(y),		z, D3DCOLOR_XRGB(0,R,B));
				AddVertex(R-B+ava*cos(x+20), R+ava*sin(y),	z+ava , D3DCOLOR_XRGB(0, G*6 ,B*9));
				AddVertex(R-B+ava*cos(x), R+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(0,-R,-B));
				}


				if (y%59==0)
				{
				AddVertex(R+ava*cos(x), G+ava*sin(y),		z, D3DCOLOR_XRGB(B,R,0));
				AddVertex(G+ava*cos(x+20), B+ava*sin(y),	z+ava , D3DCOLOR_XRGB(G*6 ,B*9,0));
				AddVertex(B+ava*cos(x), R+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,-B,0));
				}

			
		}
	}
}




void CGroup4::DrawC09(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/15;

				int z=ava*2;
				ava=ava*2;			
				R=R*5;
				B=B*5;
				
				if (y%10==0)
				{
				AddVertex(R+ava*cos(x), G+ava*sin(y),		z, D3DCOLOR_XRGB(R,G,B));
				AddVertex(R+ava*cos(x+20), G+ava*sin(y),	z+ava , D3DCOLOR_XRGB(R*6,0 ,B*9));
				AddVertex(R+ava*cos(x), G+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,-G,-B));
				}


				if (y%11==0)
				{
				AddVertex(G+ava*cos(x), B+ava*sin(y),		z, D3DCOLOR_XRGB(R,0,B));
				AddVertex(G+ava*cos(x+20), B+ava*sin(y),	z+ava , D3DCOLOR_XRGB(R*6,0 ,B*9));
				AddVertex(G+ava*cos(x), B+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,0,-B));
				}


				if (y%12==0)
				{
				AddVertex(B+ava*cos(x), R+ava*sin(y),		z, D3DCOLOR_XRGB(0,R,B));
				AddVertex(B+ava*cos(x+20), R+ava*sin(y),	z+ava , D3DCOLOR_XRGB(0, G*6 ,B*9));
				AddVertex(B+ava*cos(x), R+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(0,-R,-B));
				}

				if (y%13==0)
				{
				AddVertex(R-B+ava*cos(x), R+ava*sin(y),		z, D3DCOLOR_XRGB(0,R,B));
				AddVertex(R-B+ava*cos(x+20), R+ava*sin(y),	z+ava , D3DCOLOR_XRGB(0, G*6 ,B*9));
				AddVertex(R-B+ava*cos(x), R+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(0,-R,-B));
				}


				if (y%9==0)
				{
				AddVertex(B+ava*cos(x), B+R+ava*sin(y),		z, D3DCOLOR_XRGB(R,B,0));
				AddVertex(B+ava*cos(x+20), B+R+ava*sin(y),	z+ava , D3DCOLOR_XRGB(G*6 ,B*9,0));
				AddVertex(B+ava*cos(x), B+R+ava*sin(y-20),	z+ava*2 , D3DCOLOR_XRGB(-R,-B,0));
				}


			
		}
	}
}



void CGroup4::DrawD01(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


					

				int z=y*100-1000;
//				y=;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y ,      z , D3DCOLOR_XRGB(R/10,G,B));
				AddVertex(x+20 , y ,   z*1.2 ,D3DCOLOR_XRGB(x,0,y));


				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 ,D3DCOLOR_XRGB(x,0,y));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y ,      z , D3DCOLOR_XRGB(R/10,G,B));



			
				
		}
	}
}


void CGroup4::DrawD02(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


					

				int z=y*10-1000;
//				y=;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,0,B));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 ,D3DCOLOR_XRGB(x,y,0));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,0,B));




			
				
		}
	}
}



void CGroup4::DrawD03(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


					

				int z=y*10-1000;
//				y=;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,0,B));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 ,D3DCOLOR_XRGB(0,y,x));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(0,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(0,G,B));




			
				
		}
	}
}


void CGroup4::DrawD04(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				

				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				R=z;
				G=z;
				B=z;
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(z,z,z));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));




			
				
		}
	}
}



void CGroup4::DrawD05(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/6;
				

				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				

				if (R<G && R<B)
				{G=0;
				B=150;
				R=255-R;
				}

				else
					if (G<R && G<B)
					{R=0;
					B=150;
					G=255-G;
					}

					else
					{G=0;
					R=!50;
					B=255-B;
					}





				
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));




			
				
		}
	}
}



void CGroup4::DrawD06(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				float ava=(R+G+B)/6;
				

				

				if (R<G && R<B)
				{G=0;
				B=255;
				R=255-R;
				}

				else
					if (G<R && G<B)
					{R=0;
					B=0;
					G=255-G;
					}

					else
					{G=0;
					R=0;
					B=255-B;
					}


				int z=y*10-1000;
				y=300-sin(x/10)*300;
				x=512-cos(x/10)*512;

				
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;

				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));




			
				
		}
	}
}


void CGroup4::DrawD07(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				

				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				R=z;
				G=0;
				B=0;
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(z,z,z));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));




			
				
		}
	}
}


void CGroup4::DrawD08(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				

				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				R=0;
				G=z;
				B=0;
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(z,z,z));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

	
		}
	}
}



void CGroup4::DrawD09(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				

				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				R=0;
				G=0;
				B=z;
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(z,z,z));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));




			
				
		}
	}
}




void CGroup4::DrawD10(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				float ava=(R+G+B)/10;

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				

				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;
				
				R=z;
				G=0;
				B=z;
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(z,z,z));
				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));




			
				
		}
	}
}



void CGroup4::DrawD11(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, VertexCounter/3);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));


				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				float ava=(R+G+B)/10;
				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;

				R=z;
				G=z;
				B=z;

				

				if (R%3==0)
				{
				R=z;
				G=0;
				B=z;
				}
				else
					if (R%4==0)
					{
					
					G=0;
					B=0;
					}

					else
					if (R%5==0) R=0;
		


				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(z,z,z));
				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				x=x+5;
				y=300-sin(x)*300;
				x=512-cos(x)*512;


				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));




			
				
		}
	}
}


void CGroup4::DrawE01(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
	
	
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;
				y=300-sin(x)*300;
				x=512-cos(x)*512;

				R=z;
				G=z;
				B=z;

				
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


		


				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(z,z,z));
				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+50 ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				
//				y=300-sin(x)*300;
//				x=512-cos(x)*512;


				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
			
			

		
				
		}
	}
}




void CGroup4::DrawE02(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				int z=y*10-1000;
				y=300-sin(y/5)*300;
				x=512-cos(x/5)*512;






				R=z;
				G=z;
				B=z;

				
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);


				if (R>G && R>B)
				{
				R=255;
				G=0;
				B=0;
				}
				

					if (G>R && G>B)
					{
					R=0;
					G=255;
					B=0;
					
					}

				
					if (B>R && B>G) 
					{
					R=0;
					G=255;
					B=255;
						
						
					}

				AddVertex(x+20 , y ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+50 ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(0,G,B));		
				AddVertex(x-20 ,y*1.2 ,   z*1.2 , D3DCOLOR_XRGB(R,G,B));

				
		}
	}
}












void CGroup4::DrawE03(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;
//				x=x/300;
//frd				y=y/512;

				y=300-sin(y)*300;
				
				x=512-cos(x)*512;

				int length=R*100;

				R=z;
				G=z;
				B=z;

				
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);
				
				z=z*1.2;
				y=y*1.2;

		
				


				AddVertex(x ,y ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+R , y ,   length , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x+R , y ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+R/2 ,y+R/2 ,   length , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x+R/2 ,y+R/2 ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y ,   length , D3DCOLOR_XRGB(R,G,B));

			
				AddVertex(x ,y+R/3 ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+R , y+R/3 ,   length , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x+R , y+R/3 ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+R/2 ,y-R/2+R/3 ,   length , D3DCOLOR_XRGB(R,G,B));

				AddVertex(x+R/2 ,y+R/2+R/3 ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y+R ,   length , D3DCOLOR_XRGB(R,G,B));

				
		}
	}
}







void CGroup4::DrawE04(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				y=300-sin(y)*300;
				
				x=512-cos(x)*512;

				int length=R*100;

				R=z;
				G=z;
				B=z;

				
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);
				
				z=z*1.2;
				y=y*1.2;

		
				
				for (int i=0; i<360; i+=20)

				{			
				AddVertex(x ,y ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length*5 , D3DCOLOR_XRGB(R,G,B));
				
				}
				

				
		}
	}
}



void CGroup4::DrawE05(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



		
				
				for (int i=0; i<360; i+=20)

				{			

				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				y=300-sin(y)*300;
				
				x=512-cos(x)*512;

				int length=R*100;

				R=z;
				G=z;
				B=z;

				
				
				z=z*1.2;
				y=y*1.2;


				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x ,y ,   length*2 , D3DCOLOR_XRGB(R,G,B));

				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);

				
				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i+20)*50 , y+cos(i+20)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
				
				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i+180)*50 , y+cos(i+180)*50 ,   length , D3DCOLOR_XRGB(R,G,B));

				

				}
				
			
		}
	}
}




void CGroup4::DrawE06(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



		
				
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				y=300-sin(y)*300;
				
				x=512-cos(x)*512;

				int length=R*100;

				R=z;
				G=z;
				B=z;

				
				
				z=z*1.2;
				y=y*1.2;


				long R1=GetRValue(CurrColor);
				long G1=GetGValue(CurrColor);
				long B1=GetBValue(CurrColor);

				if (R1>G1 && R1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				else

				if (G1>R1 && G1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				if (B1>R1 && B1>G1)
				{R1=R1/2;
				G1=G1/2;
				B1=B1*2;
				}


				AddVertex(x ,y ,   length*2 , D3DCOLOR_XRGB(R,G,B));

				for (int i=G; i<G+360; i+=40)

				{			

				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R1,G1,B1));
				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length*0.8 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i+20)*50 , y+cos(i+20)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
				
//				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
//				AddVertex(x+sin(i+180)*50 , y+cos(i+180)*50 ,   length , D3DCOLOR_XRGB(R,G,B));

				

				}
				
			
		}
	}
}



void CGroup4::DrawE07(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



		
				
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				y=300-sin(y)*300;
				
				x=512-cos(x)*512;

				int length=R*100;

				R=z;
				G=z;
				B=z;

				
				
				z=z*1.2;
				y=y*1.2;


				long R1=GetRValue(CurrColor);
				long G1=GetGValue(CurrColor);
				long B1=GetBValue(CurrColor);

				if (R1>G1 && R1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				else

				if (G1>R1 && G1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				if (B1>R1 && B1>G1)
				{R1=R1/2;
				G1=G1/2;
				B1=B1*2;
				}


				

				for (int i=G; i<G+360; i+=40)

				{			
				AddVertex(x ,y ,   length*2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R1,G1,B1));
				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length*0.8 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i+20)*50 , y+cos(i+20)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
				
//				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
//				AddVertex(x+sin(i+180)*50 , y+cos(i+180)*50 ,   length , D3DCOLOR_XRGB(R,G,B));

				

				}
				
			
		}
	}
}



void CGroup4::DrawE08(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {



		
				
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				
				int length=R*100;

				R=z;
				G=z;
				B=z;

				
				
				z=z*1.2;
				y=y*1.2;


				long R1=GetRValue(CurrColor);
				long G1=GetGValue(CurrColor);
				long B1=GetBValue(CurrColor);

				if (R1>G1 && R1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				else

				if (G1>R1 && G1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				if (B1>R1 && B1>G1)
				{R1=R1/2;
				G1=G1/2;
				B1=B1*2;
				}

				int y1=300-sin(y+R)*300;;
				int x1=512-cos(x+G)*512;
				y=300-sin(y)*300;
				x=512-cos(x)*512;
				

			for (int i=G; i<G+360; i+=40)

				{			
				AddVertex(x1 ,y1 ,   length*2 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R1,G1,B1));
				AddVertex(x1+sin(i+180)*50 , y1+cos(i-90)*50 ,   length*0.8 , D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+sin(i+240)*50 , y+cos(i+23)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
				
//				AddVertex(x+sin(i)*50 , y+cos(i)*50 ,   length , D3DCOLOR_XRGB(R,G,B));
//				AddVertex(x+sin(i+180)*50 , y+cos(i+180)*50 ,   length , D3DCOLOR_XRGB(R,G,B));

			}				

				}
	}
}

					


void CGroup4::DrawF01(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
		lasty=0;

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				y=300-sin(y)*300;
				
				x=512-cos(x)*512;

				int length=R*100;

				R=z;
				G=z;
				B=z;

				

				z=z*1.5;
				y=y*1.2;


				long R1=GetRValue(CurrColor);
				long G1=GetGValue(CurrColor);
				long B1=GetBValue(CurrColor);

				if (R1>G1 && R1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				else

				if (G1>R1 && G1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				if (B1>R1 && B1>G1)
				{R1=R1/2;
				G1=G1/2;
				B1=B1*2;
				}





				int Width=R;


				if (lasty < y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y+Width*2, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(20,0,Width));
				}
				
				if (lastx!=x)
				
				{
				AddVertex(x+Width, y-Width*5, (float) -Width/300 , D3DCOLOR_XRGB(255,255,00));

				y=y-Width*5;

				AddVertex(x, y, (float) +R/1000 , D3DCOLOR_XRGB(255,R*2,R*4));
				AddVertex(x, y+R/7, (float) -G/1000, D3DCOLOR_XRGB(255,-R*2,-R));
				AddVertex(x+R/7, y+R/14 , (float) +B/1000 ,D3DCOLOR_XRGB(255,0,0));

				
				AddVertex(x+G/14, y , (float) -G/1000 ,D3DCOLOR_XRGB(255,G*20,0));
				AddVertex(x+G/14, y+G/7, (float) (B/1000) , D3DCOLOR_XRGB(255,0,G*10));
				AddVertex(x-G/14, y+G/7, (float) (R/1000), D3DCOLOR_XRGB(255,0,0));

				AddVertex(x, y+B/7, (float) -B/1000 , D3DCOLOR_XRGB(255,0,B*10));
				AddVertex(x+B/14, y, (float) -R/1000, D3DCOLOR_XRGB(255,0,0));
				AddVertex(x+B/7, y+R/7 , 0 ,D3DCOLOR_XRGB(255,255,255));
				lastx=x;
				}

				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));

		}
	}
}



void CGroup4::DrawF02(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
		lasty=0;

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				y=300-sin(y)*300;
				
				x=512-cos(x)*512;

				int length=R*100;

				R=z;
				G=z;
				B=z;

				

				z=z*1.5;
				y=y*1.2;


				long R1=GetRValue(CurrColor);
				long G1=GetGValue(CurrColor);
				long B1=GetBValue(CurrColor);

				if (R1>G1 && R1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				else

				if (G1>R1 && G1>B1)
				{R1=R1*2;
				G1=G1/2;
				B1=B1/2;
				}

				if (B1>R1 && B1>G1)
				{R1=R1/2;
				G1=G1/2;
				B1=B1*2;
				}





				int Width=R+G+B;


				if (lasty < y)
				{
				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,G,0));
				AddVertex(x, y-Width*2, 0,D3DCOLOR_XRGB(R,G,B));
				AddVertex(x-Width, y+Width, 0.05,D3DCOLOR_XRGB(30,Width,Width));

				AddVertex(x, y, 0,D3DCOLOR_XRGB(R,0,B));
				AddVertex(x, y-Width*5, 0,D3DCOLOR_XRGB(0,G,B));
				AddVertex(x+Width, y+Width, 0.05,D3DCOLOR_XRGB(20,0,Width));
				}
				
				if (lastx!=x)
				
				{
				AddVertex(x+Width, y-Width*5, (float) -Width/300 , D3DCOLOR_XRGB(255,255,00));

				y=y-Width*5;

				AddVertex(x, y, +R , D3DCOLOR_XRGB(255,R*2,R*4));
				AddVertex(x, y+R/7, -G, D3DCOLOR_XRGB(255,-R*2,-R));
				AddVertex(x+R/7, y+R/14 , +B ,D3DCOLOR_XRGB(255,0,0));

				
				AddVertex(x+G/14, y ,  G ,D3DCOLOR_XRGB(255,G*20,0));
				AddVertex(x+G/14, y+G/7, B , D3DCOLOR_XRGB(255,0,G*10));
				AddVertex(x-G/14, y+G/7, R, D3DCOLOR_XRGB(255,0,0));

				AddVertex(x, y+B/7, (float) -B/1000 , D3DCOLOR_XRGB(255,0,B*10));
				AddVertex(x+B/14, y, (float) -R/1000, D3DCOLOR_XRGB(255,0,0));
				AddVertex(x+B/7, y+R/7 , 0 ,D3DCOLOR_XRGB(255,255,255));
				lastx=x;
				}

				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));
				AddVertex(x+Width, y, (float) -Width/300 , D3DCOLOR_XRGB(00,00,00));

		}
	}
}




void CGroup4::DrawG01(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
		lasty=0;

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {

				
				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));



				float ava=(R+G+B)/10;
				int z=y*10-1000;

				int x1=x;
				int y1=y;
				y=300-sin(y)*300;
				x=512-cos(x)*512;

				int length=R*100;

				AddVertex(x-x1, y-y1 ,  G ,D3DCOLOR_XRGB(255,G*20,0));
				AddVertex(x+x1, y+y1, B , D3DCOLOR_XRGB(255,0,G*10));
		}
	}
}



void CGroup4::DrawG02(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
if (bRender) 
	{
	
		
		g_pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, VertexCounter/2);
		lasty=0;

	}
	else
	{
		COLORREF c = Pix;



			if (VertexCounter < VertexNum) {


				long R = GetRValue(c);
				long G = GetGValue(c);
				long B = GetBValue(c);
				COLORREF CurrColor = SelectColor(x, y, RGB(R,G,B));
				R=GetRValue(CurrColor);
				G=GetGValue(CurrColor);
				B=GetBValue(CurrColor);






				float ava=(R+G+B)/10;
				int z=y*10-1000;

				int x1=x;
				int y1=y;
				y=300-sin(y)*300;
				x=512-cos(x)*512;

				int length=R*100;

				if (R>G && R>B)
				{
				R=255;
				G=255;
				B=0;
				}
				

					if (G>R && G>B)
					{
					R=0;
					G=255;
					B=255;
					
					}

				
					if (B>R && B>G) 
					{
					R=0;
					G=0;
					B=255;
						
						
					}


				AddVertex(x-x1, y-y1 ,  G ,D3DCOLOR_XRGB(R, G, B));
				AddVertex(x+x1, y+y1, B , D3DCOLOR_XRGB(R, G , B));
		}
	}
}










///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void CGroup4::DrawBackground(CDC* pDC, CSize& ScreenSize,
					int CameraX, int CameraY, // position on camera
					long x, long y, // position on screen
					long lFactorX, long lFactorY, long CameraFactor,
					COLORREF Pix, COLORREF PrevPix, DWORD bRender)
					
{
	static long InitVertexCounter = 0;
	if (bRender) 
	{
		HRESULT hr = g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, InitVertexCounter, BkVertexCounter/3 );
		TRACE("Background from %d Count %d\n", InitVertexCounter, BkVertexCounter/3);
		if (FAILED(hr))
			TRACE("lala\n");
		InitVertexCounter = 0;
	}
	else
	{
		COLORREF red = D3DCOLOR_XRGB(255,0,0);
		COLORREF green = D3DCOLOR_XRGB(0,255,0);
		COLORREF blue = D3DCOLOR_XRGB(0,0,255);
		COLORREF white = D3DCOLOR_XRGB(255,255,255);

		long Height = 768;
		long Width = 1024;
		long Far = 2000;
		long Near = -2500;

		int x1=0;
		int x2=80;
		int x3=183;

		int y1=40;
		int y2=31;
		int y3=86;

		int z1=69;
		int z2=67;
		int z3=145;

		int t1=190;
		int t2=159;
		int t3=142;

		int s1=193;
		int s2=141;

		InitVertexCounter = VertexCounter;
		BkVertexCounter = 0;
		//רצפה
		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(x1,x2,x3));
		AddBkVertex(Width,Height,Far, D3DCOLOR_XRGB(y1,y2,y3));
		AddBkVertex(Width,Height,Near,D3DCOLOR_XRGB(z1,z2,z3));

		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(x1,x2,x3));
		AddBkVertex(0,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));
		AddBkVertex(Width,Height,Far, D3DCOLOR_XRGB(y1,y2,y3));

		//תקרה
		AddBkVertex(0,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(Width,0,Far, D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(Width,0,Near,D3DCOLOR_XRGB(t1,t2,t3));

		AddBkVertex(0,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(Width,0,Far, D3DCOLOR_XRGB(s1,y2,s2));

		//קיר ימין
		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(x1,x2,x3));
		AddBkVertex(0,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1,y2,s2));

		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(0,x2,x3));
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(0,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));

		//קיר שמאל
		AddBkVertex(Width,Height,Near,D3DCOLOR_XRGB(z1,z2,z3));
		AddBkVertex(Width,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(Width,0,Far,D3DCOLOR_XRGB(s1,y2,s2));

		AddBkVertex(Width,Height,Near,D3DCOLOR_XRGB(z1,z2,z3));
		AddBkVertex(Width,0,Far,D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(Width,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));

		//קיר נגדי
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1-30,y1-30,s2-30));
		AddBkVertex(Width,0,Far,D3DCOLOR_XRGB(s1-30,y1-30,s2-30));
		AddBkVertex(Width,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));


		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1-30,y1-30,s2-30));
		AddBkVertex(0,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));
		AddBkVertex(Width,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));
	}
}



void CGroup4::DrawBackground1()
					
{
		COLORREF red = D3DCOLOR_XRGB(255,0,0);
		COLORREF green = D3DCOLOR_XRGB(0,255,0);
		COLORREF blue = D3DCOLOR_XRGB(0,0,255);
		COLORREF white = D3DCOLOR_XRGB(255,255,255);

		long Height = 768;
		long Width = 1024;
		long Far = 2000;
		long Near = -2500;

		int x1=0;
		int x2=80;
		int x3=183;

		int y1=40;
		int y2=31;
		int y3=86;

		int z1=69;
		int z2=67;
		int z3=145;

		int t1=190;
		int t2=159;
		int t3=142;

		int s1=193;
		int s2=141;

		//רצפה
		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(x1,x2,x3));
		AddBkVertex(Width,Height,Far, D3DCOLOR_XRGB(y1,y2,y3));
		AddBkVertex(Width,Height,Near,D3DCOLOR_XRGB(z1,z2,z3));

		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(x1,x2,x3));
		AddBkVertex(0,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));
		AddBkVertex(Width,Height,Far, D3DCOLOR_XRGB(y1,y2,y3));


		//תקרה

		AddBkVertex(0,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(Width,0,Far, D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(Width,0,Near,D3DCOLOR_XRGB(t1,t2,t3));

		AddBkVertex(0,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(Width,0,Far, D3DCOLOR_XRGB(s1,y2,s2));


		//קיר ימין
		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(x1,x2,x3));
		AddBkVertex(0,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1,y2,s2));

		AddBkVertex(0,Height,Near,D3DCOLOR_XRGB(0,x2,x3));
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(0,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));


		//קיר שמאל

		AddBkVertex(Width,Height,Near,D3DCOLOR_XRGB(z1,z2,z3));
		AddBkVertex(Width,0,Near,D3DCOLOR_XRGB(t1,t2,t3));
		AddBkVertex(Width,0,Far,D3DCOLOR_XRGB(s1,y2,s2));

		AddBkVertex(Width,Height,Near,D3DCOLOR_XRGB(z1,z2,z3));
		AddBkVertex(Width,0,Far,D3DCOLOR_XRGB(s1,y2,s2));
		AddBkVertex(Width,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));


		//קיר נגדי
		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1-30,y1-30,s2-30));
		AddBkVertex(Width,0,Far,D3DCOLOR_XRGB(s1-30,y1-30,s2-30));
		AddBkVertex(Width,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));


		AddBkVertex(0,0,Far,D3DCOLOR_XRGB(s1-30,y1-30,s2-30));
		AddBkVertex(0,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));
		AddBkVertex(Width,Height,Far,D3DCOLOR_XRGB(y1,y2,y3));
}

