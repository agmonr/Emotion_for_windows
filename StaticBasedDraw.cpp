// StaticBasedDraw.cpp: implementation of the CStaticBasedDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRW.h"
#include "StaticBasedDraw.h"
#include "CameraPicture.h"
#include "Dib.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaticBasedDraw::CStaticBasedDraw()
{

}

CStaticBasedDraw::~CStaticBasedDraw()
{

}

//////////////////////////////////////////////////////////////////////

void CStaticBasedDraw1::ProcessCameraChangeOnStatic(CCameraPicture* pCameraPicture)
{
	if (! pCameraPicture->IsInitialized()) {
		return;
	}
	
	// Calculate average of change between 2 camera pictures
	long RAll(0),GAll(0),BAll(0);
	CUtils::CalcColorChage(pCameraPicture, RAll, GAll, BAll);

	CDib* pCameraDib = pCameraPicture->GetCurrCameraDib();
	CDib* pPrevCameraDib = pCameraPicture->GetPrevCameraDib();
	CSize CameraSize = pCameraDib->GetSize();
	CSize StaticSize = pCameraPicture->GetDibDraw()->GetSize();

	DisplayByCamera(StaticSize, CameraSize, pCameraDib, pPrevCameraDib, pCameraPicture->GetDibDraw(), RAll, GAll, BAll);
//	DisplayByStatic(StaticSize, CameraSize, pCameraDib, pPrevCameraDib, pCameraPicture->GetDibDraw(), RAll, GAll, BAll);
}

void CStaticBasedDraw1::DisplayByStatic(CSize& StaticSize, CSize& CameraSize, 
										CDib* pCameraDib, CDib* pPrevCameraDib,
										CDib* pDibDraw,
										long RAll, long GAll, long BAll)
{
	for (int x=0; x < StaticSize.cx; x+=StaticResFactor)
	{
		for (int y=0; y < StaticSize.cy; y+=StaticResFactor)
		{
			long CameraX = MulDiv(x, CameraSize.cx, StaticSize.cx);
			CameraX -= CameraX % CameraResFactor;
			long CameraY = MulDiv(y, CameraSize.cy, StaticSize.cy);
			CameraY -= CameraY % CameraResFactor;
			
			if (CameraX < CameraSize.cx && CameraY < CameraSize.cy) {
				long Diff = pCameraDib->GetPixel(CameraX, CameraY) - pPrevCameraDib->GetPixel(CameraX, CameraY);
				long R = GetRValue(Diff);
				long G = GetRValue(Diff);
				long B = GetRValue(Diff);
				
				COLORREF CurrColor = pDibDraw->GetPixel(x,y);
				// check if a significant change was made
				if (/*m_bMotionColorsAffectWholeImage ||*/
					! (R == G && R == B && (R < ColorDiffThreshold || R > 255 - ColorDiffThreshold))) {

					long R = min(255, GetRValue(CurrColor) + RAll);
					long G = min(255, GetGValue(CurrColor) + GAll);
					long B = min(255, GetBValue(CurrColor) + BAll);

					CurrColor = RGB(R,G,B);

					// change the color on the static pic
					long lastX = min(x+StaticResFactor, StaticSize.cx);
					long lastY = min(y+StaticResFactor, StaticSize.cy);
					pDibDraw->SetRect(x, y, lastX, lastY, CurrColor);
				}
			}
		}
	}
}

void CStaticBasedDraw1::DisplayByCamera(CSize& StaticSize, CSize& CameraSize, 
							   CDib* pCameraDib, CDib* pPrevCameraDib,
							   CDib* pDibDraw,
							   long RAll, long GAll, long BAll)
{
	// By camera image
	double FactorX = (double)StaticSize.cx / (double)CameraSize.cx;
	double FactorY = (double)StaticSize.cy / (double)CameraSize.cy;
	long lFactorX = (long)FactorX;
	long lFactorY = (long)FactorY;
	if (FactorX - (double)lFactorX > 0.5) lFactorX++;
	if (FactorY - (double)lFactorY > 0.5) lFactorY++;

	for (int CameraX=0; CameraX < CameraSize.cx; CameraX++)
	{
		for (int CameraY=0; CameraY < CameraSize.cy; CameraY++)
		{
			long x = (long)((double)CameraX * FactorX);
			long y = (long)((double)CameraY * FactorY);
		
			if (CameraX < CameraSize.cx && CameraY < CameraSize.cy) {
				long Diff = pCameraDib->GetPixel(CameraX, CameraY) - pPrevCameraDib->GetPixel(CameraX, CameraY);
				long R = GetRValue(Diff);
				long G = GetRValue(Diff);
				long B = GetRValue(Diff);
				
				COLORREF CurrColor = pDibDraw->GetPixel(x,y);
				// check if a significant change was made
				if (! (R == G && R == B && (R < ColorDiffThreshold || R > 255 - ColorDiffThreshold))) {

					long R = min(255, GetRValue(CurrColor) + RAll);
					long G = min(255, GetGValue(CurrColor) + GAll);
					long B = min(255, GetBValue(CurrColor) + BAll);

					CurrColor = RGB(R,G,B);

					// change the color on the static pic
					long lastX = min(x+lFactorX, StaticSize.cx);
					long lastY = min(y+lFactorY, StaticSize.cy);
					x = max(x, 0);
					y = max(y, 0);
					pDibDraw->SetRect(x, y, lastX, lastY, CurrColor);
				}
			}
		}
	}
}
