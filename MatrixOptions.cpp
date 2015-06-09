#include "stdafx.h"
#include "MatrixOptions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



void MatrixOptions::SetDefault()
{
	fRotateX = fRotateY = fRotateZ = 0;
	
	// View matrix
	EyePt.x = 0.0;
	EyePt.y = 0.0;
	EyePt.z = -6.0;
	
	LookAtPt.x = 0.0;
	LookAtPt.y = 0.0;
	LookAtPt.z = 0.0;
	
	UpVec.x = 0.0;
	UpVec.y = 1.0;
	UpVec.z = 0.0;
	
	// Projection Matrix
	FieldOfView = 25.0; // degrees
	Aspect = 1.0;
	ZNear = 0.0;
	ZFar = 20.0;
}

void MatrixOptions::ReadSetting(float& f, LPCTSTR Entry)
{
	CString s = AfxGetApp()->GetProfileString("Matrix", Entry);
	if (s.GetLength() > 0) {
		f = (float)atof(s);
	}
}
void MatrixOptions::ReadSetting(int& f, LPCTSTR Entry)
{
	CString s = AfxGetApp()->GetProfileString("Matrix", Entry);
	if (s.GetLength() > 0) {
		f = atoi(s);
	}
}

void MatrixOptions::WriteSetting(float f, LPCTSTR Entry)
{
	CString s;
	s.Format("%f", f);
	AfxGetApp()->WriteProfileString("Matrix", Entry, s);
}
void MatrixOptions::WriteSetting(int f, LPCTSTR Entry)
{
	CString s;
	s.Format("%d", f);
	AfxGetApp()->WriteProfileString("Matrix", Entry, s);
}

void MatrixOptions::ReadSettings()
{
	ReadSetting(fRotateX, "fRotateX");
	ReadSetting(fRotateY, "fRotateY");
	ReadSetting(fRotateZ, "fRotateZ");
	
	ReadSetting(EyePt.x, "EyePtX");
	ReadSetting(EyePt.y, "EyePtY");
	ReadSetting(EyePt.z, "EyePtZ");
	
	ReadSetting(LookAtPt.x, "LookAtPtX");
	ReadSetting(LookAtPt.y, "LookAtPtY");
	ReadSetting(LookAtPt.z, "LookAtPtZ");
	
	ReadSetting(UpVec.x, "UpVecX");
	ReadSetting(UpVec.y, "UpVecY");
	ReadSetting(UpVec.z, "UpVecZ");
	
	ReadSetting(FieldOfView, "FieldOfView");
	ReadSetting(Aspect, "Aspect");
	ReadSetting(ZNear, "ZNear");
	ReadSetting(ZFar, "ZFar");
}

void MatrixOptions::WriteSettings()
{
	WriteSetting(fRotateX, "fRotateX");
	WriteSetting(fRotateY, "fRotateY");
	WriteSetting(fRotateZ, "fRotateZ");
	
	WriteSetting(EyePt.x, "EyePtX");
	WriteSetting(EyePt.y, "EyePtY");
	WriteSetting(EyePt.z, "EyePtZ");
	
	WriteSetting(LookAtPt.x, "LookAtPtX");
	WriteSetting(LookAtPt.y, "LookAtPtY");
	WriteSetting(LookAtPt.z, "LookAtPtZ");
	
	WriteSetting(UpVec.x, "UpVecX");
	WriteSetting(UpVec.y, "UpVecY");
	WriteSetting(UpVec.z, "UpVecZ");
	
	WriteSetting(FieldOfView, "FieldOfView");
	WriteSetting(Aspect, "Aspect");
	WriteSetting(ZNear, "ZNear");
	WriteSetting(ZFar, "ZFar");
}
