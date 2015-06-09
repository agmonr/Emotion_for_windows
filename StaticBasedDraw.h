// StaticBasedDraw.h: interface for the CStaticBasedDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATICBASEDDRAW_H__7BF9BA11_28DD_4B57_9433_E9911A9B9A26__INCLUDED_)
#define AFX_STATICBASEDDRAW_H__7BF9BA11_28DD_4B57_9433_E9911A9B9A26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseDraw.h"

class CDib;
class CCameraPicture;

class CStaticBasedDraw : public CBaseDraw
{
public:
	CStaticBasedDraw();
	virtual ~CStaticBasedDraw();

	virtual IsStaticDraw() { return true; }
	virtual void ProcessCameraChangeOnStatic(CCameraPicture* pCameraPicture) = 0;
};

class CStaticBasedDraw1 : public CStaticBasedDraw  
{
public:
	virtual void ProcessCameraChangeOnStatic(CCameraPicture* pCameraPicture);

	void DisplayByStatic(CSize& StaticSize, CSize& CameraSize, 
		CDib* pCameraDib, CDib* pPrevCameraDib, CDib* pDibDraw,
		long RAll, long GAll, long BAll);
	void DisplayByCamera(CSize& StaticSize, CSize& CameraSize, 
		CDib* pCameraDib, CDib* pPrevCameraDib, CDib* pDibDraw,
		long RAll, long GAll, long BAll);
};

#endif // !defined(AFX_STATICBASEDDRAW_H__7BF9BA11_28DD_4B57_9433_E9911A9B9A26__INCLUDED_)
