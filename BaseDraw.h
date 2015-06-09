// BaseDraw.h: interface for the CBaseDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEDRAW_H__4CFFAB92_77B1_4E28_8DCD_3638C4548949__INCLUDED_)
#define AFX_BASEDRAW_H__4CFFAB92_77B1_4E28_8DCD_3638C4548949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDib;
class CCameraPicture;

#define StaticResFactor 2
#define CameraResFactor 1
#define ColorDiffThreshold 22

#define AVG_SIZE 5

class CBaseDraw  
{
public:
	CBaseDraw();
	virtual ~CBaseDraw();

	virtual IsStaticDraw() { return false; }
	virtual IsCameraDraw() { return false; }
	virtual IsMotionDraw() { return false; }
	virtual Is3DDraw() { return false; }

	virtual void Init() = 0;
	virtual void Terminate() = 0;

protected:
	void CalcColorAreas(const CDib* pCameraDib, COLORREF Averages[AVG_SIZE][AVG_SIZE]);
};

#endif // !defined(AFX_BASEDRAW_H__4CFFAB92_77B1_4E28_8DCD_3638C4548949__INCLUDED_)
