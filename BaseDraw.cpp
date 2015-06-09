// BaseDraw.cpp: implementation of the CBaseDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRW.h"
#include "BaseDraw.h"
#include "CameraPicture.h"
#include "Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseDraw::CBaseDraw()
{

}

CBaseDraw::~CBaseDraw()
{

}

//////////////////////////////////////////////////////////////////////


void CBaseDraw::CalcColorAreas(const CDib* pCameraDib, COLORREF Averages[AVG_SIZE][AVG_SIZE])
{
	CSize CameraSize = pCameraDib->GetSize();
	long FactorX = CameraSize.cx / AVG_SIZE;
	long FactorY = CameraSize.cy / AVG_SIZE;
	long SampleFactor = 5;
	long CountPoints[AVG_SIZE][AVG_SIZE];
	_int64 R[AVG_SIZE][AVG_SIZE], G[AVG_SIZE][AVG_SIZE], B[AVG_SIZE][AVG_SIZE];

	for (int i = 0; i < AVG_SIZE; i++) {
		for (int j = 0; j < AVG_SIZE; j++) {
			CountPoints[i][j] = 0;
			R[i][j] = G[i][j] = B[i][j] = 0;
		}
	}

	for (int CameraX=0; CameraX < CameraSize.cx; CameraX += SampleFactor)
	{
		for (int CameraY=0; CameraY < CameraSize.cy; CameraY += SampleFactor)
		{
			long x = CameraX / FactorX;
			long y = CameraY / FactorY;
			if (x < AVG_SIZE && y < AVG_SIZE) { 
				COLORREF Curr = pCameraDib->GetPixel(CameraX, CameraY); 
				R[x][y] += GetRValue(Curr);
				G[x][y] += GetGValue(Curr);
				B[x][y] += GetBValue(Curr);
				CountPoints[x][y]++;
			}
		}
	}

	for (i = 0; i < AVG_SIZE; i++) {
		for (int j = 0; j < AVG_SIZE; j++) {
			if (CountPoints[i][j] > 0) {
				_int64 AvgR = R[i][j] / CountPoints[i][j]; 
				_int64 AvgG = G[i][j] / CountPoints[i][j]; 
				_int64 AvgB = B[i][j] / CountPoints[i][j]; 
				Averages[i][j] = RGB(AvgR, AvgG, AvgB);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
