// 3DDraw.h: interface for the C3DDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DDRAW_H__DEE0BC45_7778_420C_BC01_8AC211306BF7__INCLUDED_)
#define AFX_3DDRAW_H__DEE0BC45_7778_420C_BC01_8AC211306BF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CameraBasedDraw.h"
#include "MatrixOptions.h"

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z; // The transformed position for the vertex
//	FLOAT nx, ny, nz;  // normal
    DWORD color;        // The vertex color
};
#define VertexNum (400000)

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)


class C3DDraw : public CMotionBasedDraw  
{
public:
	C3DDraw(CWnd* pWnd);
	virtual ~C3DDraw();

	virtual Is3DDraw() { return true; }


	// Direct3d drawing
	DWORD Init3D();
	VOID Render(DrawFunc* pDrawFunc, LPCTSTR FuncName);
	VOID Cleanup();
	HRESULT InitVB();
	HRESULT PrepareVB();
	HRESULT InitD3D( HWND hWnd );
	BOOL m_bInitVB;

	VOID SetupMatrices();

	void DoSetupMatrix();
	void OnMoveViewPoint(UINT CommandId);

	// Overrides
	virtual void Init();
	virtual void InitFunctions();
	virtual void Terminate();
	virtual void Draw(CSize ScreenSize, CDC* pDC, CCameraPicture* pCameraPicture);

	MatrixOptions m_MatrixOptions;
};

#endif // !defined(AFX_3DDRAW_H__DEE0BC45_7778_420C_BC01_8AC211306BF7__INCLUDED_)
