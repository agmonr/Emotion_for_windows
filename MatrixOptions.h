#ifndef _MATRIXOPTIONS_H_
#define _MATRIXOPTIONS_H_

#include <d3dx9.h>

struct MatrixOptions
{
	// World matrix
	float fRotateX, fRotateY, fRotateZ;

	// View matrix
	D3DXVECTOR3 EyePt, LookAtPt, UpVec;

	// Projection Matrix
	float FieldOfView; // radians
	float Aspect;
	float ZNear, ZFar;

	MatrixOptions() :
		fRotateX(0), fRotateY(0), fRotateZ(0),

		// View matrix
		EyePt(0,0,0), LookAtPt(0,0,0), UpVec(0,0,0),

		// Projection Matrix
		FieldOfView(0), // radians
		Aspect(0),
		ZNear(0), ZFar(0)
	{}

	void SetDefault();

	void ReadSetting(float& f, LPCTSTR Entry);
	void ReadSetting(int& f, LPCTSTR Entry);

	void WriteSetting(float f, LPCTSTR Entry);
	void WriteSetting(int f, LPCTSTR Entry);

	void ReadSettings();

	void WriteSettings();
};

#endif //_MATRIXOPTIONS_H_