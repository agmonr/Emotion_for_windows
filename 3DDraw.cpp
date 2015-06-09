// 3DDraw.cpp: implementation of the C3DDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "drw.h"
#include "3DDraw.h"
#include "CameraPicture.h"
#include "Dib.h"
#include "Group1.h"
#include "Group4.h"
#include "SetupMatrixDlg.h"

#include "D3DFont.h"
#include <d3d9.h>
#include <d3dx9.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DDraw::C3DDraw(CWnd* pWnd)
:	CMotionBasedDraw(pWnd), m_bInitVB(false)
{
	m_MatrixOptions.SetDefault();
	m_MatrixOptions.ReadSettings();
}

C3DDraw::~C3DDraw()
{
}


void C3DDraw::Init()
{
	InitD3D(m_pWnd->m_hWnd);
	InitFunctions();
}

void C3DDraw::Terminate()
{
	Cleanup();
}

//-----------------------------------------------------------------------------
// Direct3d drawing
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; // Buffer to hold vertices
ID3DXFont* m_pFont = NULL;

CUSTOMVERTEX vertices[VertexNum];
UINT VertexCounter = 0;
UINT MaxPrimitiveCount = 0;
UINT MaxVertexCount = 0;
D3DPRIMITIVETYPE PrimitiveType;
UINT PrimitiveCount = 0;

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: D3DUtil_InitLight()
// Desc: Initializes a D3DLIGHT structure, setting the light position. The
//       diffuse color is set to white; specular and ambient are left as black.
//-----------------------------------------------------------------------------
VOID D3DUtil_InitLight( D3DLIGHT9& light, D3DLIGHTTYPE ltType,
                        FLOAT x, FLOAT y, FLOAT z )
{
    D3DXVECTOR3 vecLightDirUnnormalized(x, y, z);
    ZeroMemory( &light, sizeof(D3DLIGHT9) );
    light.Type        = ltType;
    light.Diffuse.r   = 1.0f;
    light.Diffuse.g   = 1.0f;
    light.Diffuse.b   = 1.0f;
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecLightDirUnnormalized );
    light.Position.x   = x;
    light.Position.y   = y;
    light.Position.z   = z;
    light.Range        = 1000.0f;
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT C3DDraw::InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn off culling, so we see the front and back of the triangle
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting, since we are providing our own vertex colors
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	if (! SUCCEEDED( InitVB() )) {
		return E_FAIL;
	} else {
		m_bInitVB = TRUE;

		D3DCAPS9 caps;
		g_pd3dDevice->GetDeviceCaps(&caps);
		MaxPrimitiveCount = caps.MaxPrimitiveCount;
		MaxVertexCount = caps.MaxVertexIndex;
	}

	// Create font for drawing text
	LOGFONT LogFont;
	ZeroMemory(&LogFont, sizeof(LOGFONT));
	LogFont.lfHeight = 18;
	LogFont.lfWidth = NULL;
	LogFont.lfWeight = 400;
	LogFont.lfCharSet = DEFAULT_CHARSET;
	LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	LogFont.lfQuality = DEFAULT_QUALITY;
	LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	strcpy(LogFont.lfFaceName, "Arial");
	HFONT hFont = CreateFontIndirect(&LogFont);

	HRESULT hResFont = D3DXCreateFont(g_pd3dDevice, hFont, &m_pFont);
	if (FAILED(hResFont)) {
		return E_FAIL;
	}

    // Setup the light
    //D3DLIGHT9 light1;
    //D3DUtil_InitLight( light1, D3DLIGHT_POINT, 0.0f, 0.0f, 1.0f );
    //g_pd3dDevice->SetLight( 0, &light1 );
 	//g_pd3dDevice->LightEnable( 0, TRUE );

    // Device state would normally be set here

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------


HRESULT C3DDraw::InitVB()
{
    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( VertexNum*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID C3DDraw::Cleanup()
{
	if (m_pFont)
		m_pFont->Release();

    if( g_pVB != NULL )        
        g_pVB->Release();

    if( g_pd3dDevice != NULL ) 
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )       
        g_pD3D->Release();
}

void C3DDraw::DoSetupMatrix()
{
	CSetupMatrixDlg dlg(m_pWnd);
	dlg.m_MatrixOptions = m_MatrixOptions;
	if (dlg.DoModal() == IDOK) {
		m_MatrixOptions = dlg.m_MatrixOptions;
		m_MatrixOptions.WriteSettings();
	}
}

void C3DDraw::OnMoveViewPoint(UINT CommandId)
{
	switch (CommandId)
	{
	case ID_MOVE_UP:
		m_MatrixOptions.EyePt.y=m_MatrixOptions.EyePt.y+0.25;
		break;
	case ID_MOVE_DOWN:
		m_MatrixOptions.EyePt.y=m_MatrixOptions.EyePt.y-0.25;
		break;

	case ID_MOVE_RIGHT:	
		m_MatrixOptions.EyePt.x=m_MatrixOptions.EyePt.x-abs(m_MatrixOptions.EyePt.z)*0.01-0.1;
		break;

	case ID_MOVE_LEFT:
		m_MatrixOptions.EyePt.x=m_MatrixOptions.EyePt.x+abs(m_MatrixOptions.EyePt.z)*0.01+0.1;
		break;
	case ID_MOVE_FORWARD:
		m_MatrixOptions.EyePt.z=m_MatrixOptions.EyePt.z+0.5;
		break;
	case ID_MOVE_BACK:
		m_MatrixOptions.EyePt.z=m_MatrixOptions.EyePt.z-0.5;
			break;


	case ID_LOOK_LEFT:	
		m_MatrixOptions.LookAtPt.x=m_MatrixOptions.LookAtPt.x+abs(m_MatrixOptions.EyePt.z)*0.01+0.1;
		break;

	case ID_LOOK_RIGHT:
		m_MatrixOptions.LookAtPt.x=m_MatrixOptions.LookAtPt.x-abs(m_MatrixOptions.EyePt.z)*0.01-0.1;
		break;

		
	case ID_LOOK_UP:
		m_MatrixOptions.LookAtPt.y=m_MatrixOptions.LookAtPt.y+abs(m_MatrixOptions.EyePt.z)*0.01+0.1;
		break;
	case ID_LOOK_DOWN:
		m_MatrixOptions.LookAtPt.y=m_MatrixOptions.LookAtPt.y-abs(m_MatrixOptions.EyePt.z)*0.01-0.1;
		break;



	case ID_LOOK_ZOOMIN:
		m_MatrixOptions.LookAtPt.z=m_MatrixOptions.LookAtPt.z+abs(m_MatrixOptions.EyePt.z)*0.01+0.1;
		break;
	case ID_LOOK_ZOOMOUT:
		m_MatrixOptions.LookAtPt.z=m_MatrixOptions.LookAtPt.z-abs(m_MatrixOptions.EyePt.z)*0.01-0.1;
		break;
	
	
	case ID_DEFAULT_MATRIX:
		m_MatrixOptions.SetDefault();
		break;
	}
	m_MatrixOptions.WriteSettings();
}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------

//#define MakeRadians(angle) ( (float)((angle / 180.0) * D3DX_PI) )
float MakeRadians(float angle)
{
	return (float)((angle / 180.0) * D3DX_PI);
}

VOID C3DDraw::SetupMatrices()
{
	D3DXMATRIXA16 MatWorld;

    D3DXMATRIX MatTemp;  // Temp matrix for rotations.
    D3DXMATRIX MatRot;   // Final rotation matrix, applied to 
                         // pMatWorld.
 
    // Using the left-to-right order of matrix concatenation,
    // apply the translation to the object's world position
    // before applying the rotations.
    D3DXMatrixTranslation(&MatWorld, 0, 0, 0);
    D3DXMatrixIdentity(&MatRot);

    // Now, apply the orientation variables to the world matrix
	{
        // Produce and combine the rotation matrices.
		D3DXMatrixRotationX(&MatTemp, MakeRadians(m_MatrixOptions.fRotateX));         // Pitch
		D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);

		D3DXMatrixRotationY(&MatTemp, MakeRadians(m_MatrixOptions.fRotateY));           // Yaw
		D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);

		D3DXMatrixRotationZ(&MatTemp, MakeRadians(m_MatrixOptions.fRotateZ));          // Roll
		D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
		// Apply the rotation matrices to complete the world matrix.
		D3DXMatrixMultiply(&MatWorld, &MatRot, &MatWorld);
		g_pd3dDevice->SetTransform( D3DTS_WORLD, &MatWorld );
	}

	// View matrix
    D3DXVECTOR3 vEyePt( m_MatrixOptions.EyePt );
    D3DXVECTOR3 vLookatPt( m_MatrixOptions.LookAtPt );
    D3DXVECTOR3 vUpVec( m_MatrixOptions.UpVec );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, MakeRadians(m_MatrixOptions.FieldOfView),
		m_MatrixOptions.Aspect, m_MatrixOptions.ZNear, m_MatrixOptions.ZFar );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID C3DDraw::Render(DrawFunc* pDrawFunc, LPCTSTR FuncName)
{
	if (! m_bInitVB) {
		return;
	}

    // Clear the backbuffer to a blue color רקע
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Setup the world, view, and projection matrices
        SetupMatrices();

		{
			// Now we fill the vertex buffer. To do this, we need to Lock() the VB to
			// gain access to the vertices. This mechanism is required becuase vertex
			// buffers may be in device memory.
			VOID* pVertices;
			size_t size = sizeof(vertices);
			if (! FAILED( g_pVB->Lock( 0, size, (void**)&pVertices, 0 ) ) )
			{
				// draw the background
				/*
				CGroup4::DrawBackground(NULL, CSize(0,0), 
						0,0, // position on camera 
						0,0, // position on screen 
						0,0,0,
						0,0,
						0);*/

				memcpy( pVertices, vertices, size );
				g_pVB->Unlock();


				// Draw the triangles in the vertex buffer. This is broken into a few
				// steps. We are passing the vertices down a "stream", so first we need
				// to specify the source of that stream, which is our vertex buffer. Then
				// we need to let D3D know what vertex shader to use. Full, custom vertex
				// shaders are an advanced topic, but in most cases the vertex shader is
				// just the FVF, so that D3D knows what type of vertices we are dealing
				// with. Finally, we call DrawPrimitive() which does the actual rendering
				// of our geometry (in this case, just one triangle).
				g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
				g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );

				// draw the background
				/*
				CGroup4::DrawBackground(NULL, CSize(0,0), 
						0,0, // position on camera 
						0,0, // position on screen 
						0,0,0,
						0,0,
						1);*/

				pDrawFunc(NULL, CSize(0,0), 
						0,0, // position on camera 
						0,0, // position on screen 
						0,0,0,
						0,0,
						1);


			}
		}

		// draw function name
		if (FuncName && _tcslen(FuncName) > 0) {
			CRect r(0,0,400,20);
			CString Text;
			Text.Format("%s %d (%d,%d)", FuncName, VertexCounter, MaxPrimitiveCount, MaxVertexCount);
			m_pFont->Begin();
	        m_pFont->DrawText( Text, -1, &r, DT_TOP|DT_LEFT|DT_SINGLELINE, D3DCOLOR_XRGB(255,100,100));

			Text.Format("Eye: %0.0f,%0.0f,(%0.0f+6) LookAt: %0.0f,%0.0f,%0.0f",
				m_MatrixOptions.EyePt.x,
				m_MatrixOptions.EyePt.y,
				m_MatrixOptions.EyePt.z,
				m_MatrixOptions.LookAtPt.x,
				m_MatrixOptions.LookAtPt.y,
				m_MatrixOptions.LookAtPt.z);

			CRect r1(0,25,400,45);
	        m_pFont->DrawText( Text, -1, &r1, DT_TOP|DT_LEFT|DT_SINGLELINE, D3DCOLOR_XRGB(255,100,100));
			

			m_pFont->End();
		}



        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

void C3DDraw::Draw(CSize ScreenSize, CDC* pDC, 
					 CCameraPicture* pCameraPicture)
{
	VertexCounter = 0;

	CDib* pCameraDib = pCameraPicture->GetCurrCameraDib();

	if (m_NextDraw) {
		SelectRandDrawFunc();
	}
	if (m_NextColor) {
		CGroup4::m_Color_Select++;
		CGroup4::m_Color_Select %= CGroup4::GetNumColors();	
	}

	DrawFunc* pDrawFunc = NULL;

	SelectDrawFunction(pDrawFunc);

	if (pDrawFunc) 
	{
		CSize CameraSize = pCameraDib->GetSize();
		
		const int CameraSizeX = CameraSize.cx;
		const int CameraSizeY = CameraSize.cy;
		// By camera image
		double FactorX = (double)ScreenSize.cx / (double)CameraSizeX;
		double FactorY = (double)ScreenSize.cy / (double)CameraSizeY;
		long lFactorX = (long)FactorX;
		long lFactorY = (long)FactorY;
		if (FactorX - (double)lFactorX > 0.5) lFactorX++;
		if (FactorY - (double)lFactorY > 0.5) lFactorY++;

		const int CameraFactor = min(40, max(m_TempCameraFactor, 1));

		long PixCount = 0;
		GetMotionPoints(ScreenSize, pCameraPicture, MotionPixels, MAX_PIXELS, PixCount);

		for (int i = 0; i < PixCount; i++) 
		{
			pDrawFunc(pDC, ScreenSize, 
				MotionPixels[i].CameraX, MotionPixels[i].CameraY, // position on camera 
				MotionPixels[i].x, MotionPixels[i].y, // position on screen 
				lFactorX, lFactorY, CameraFactor,
				MotionPixels[i].Pix, MotionPixels[i].PrevPix, 0);

		}

		CString FuncName;
		// Display name
		if (m_DisplayFunctionName)
		{
			LPTSTR szName = NULL; 
			if (m_FunctionNames.Lookup(pDrawFunc, szName)) {
				FuncName = szName;
			}
		}

		// Render the scene
		Render(pDrawFunc, FuncName);		
	}


	if (m_NextDraw == TRUE) {
		long TimerPeriod = m_TimerGroup[m_GroupSelect];
		m_DrawTimerId = ::SetTimer(NULL, 555, TimerPeriod, TimerProc);
		m_NextDraw = FALSE;
	}
	if (m_NextColor == TRUE) {
		long TimerPeriod = m_TimerColor;
		m_ColorTimerId = ::SetTimer(NULL, 999, TimerPeriod, TimerProc);
		m_NextColor = FALSE;
	}
	if (m_NextCapture == TRUE) {
		long TimerPeriod = m_TimerCapture;
		if (TimerPeriod > 0) {
			DoCapture(pDC, ScreenSize);
			m_CaptureTimerId = ::SetTimer(NULL, 777, TimerPeriod, TimerProc);
			m_NextCapture = FALSE;
		}
	}
}

void C3DDraw::InitFunctions()
{
	AddFunction(CGroup4::Draw0, m_Group[0], "Draw0");
	AddFunction(CGroup4::Draw1, m_Group[0], "Draw1");
	AddFunction(CGroup4::Draw2, m_Group[0], "Draw2");
	AddFunction(CGroup4::Draw3, m_Group[0], "Draw3");
	AddFunction(CGroup4::Draw4, m_Group[0], "Draw4");
	AddFunction(CGroup4::Draw5, m_Group[0], "Draw5");
	AddFunction(CGroup4::Draw6, m_Group[0], "Draw6");
	AddFunction(CGroup4::Draw7, m_Group[0], "Draw7");
	AddFunction(CGroup4::Draw8, m_Group[0], "Draw8");
	AddFunction(CGroup4::Draw9, m_Group[0], "Draw9");
	AddFunction(CGroup4::Draw10, m_Group[0], "Draw10");
	AddFunction(CGroup4::Draw11, m_Group[0], "Draw11");
	AddFunction(CGroup4::Draw12, m_Group[0], "Draw12");
	AddFunction(CGroup4::Draw13, m_Group[0], "Draw13");
	AddFunction(CGroup4::Draw14, m_Group[0], "Draw14");
	AddFunction(CGroup4::Draw15, m_Group[0], "Draw15");
	AddFunction(CGroup4::Draw16, m_Group[0], "Draw16");
	AddFunction(CGroup4::Draw17, m_Group[0], "Draw17");
	AddFunction(CGroup4::Draw18, m_Group[0], "Draw18");
	AddFunction(CGroup4::Draw19, m_Group[0], "Draw19");
	AddFunction(CGroup4::Draw20, m_Group[0], "Draw20");
	AddFunction(CGroup4::Draw21, m_Group[0], "Draw21");
	AddFunction(CGroup4::Draw22, m_Group[0], "Draw22");
	AddFunction(CGroup4::Draw23, m_Group[0], "Draw23");
	AddFunction(CGroup4::Draw24, m_Group[0], "Draw24");
	AddFunction(CGroup4::Draw25, m_Group[0], "Draw25");
	AddFunction(CGroup4::Draw26, m_Group[0], "Draw26");
	AddFunction(CGroup4::Draw27, m_Group[0], "Draw27");
	AddFunction(CGroup4::Draw28, m_Group[0], "Draw28");
	AddFunction(CGroup4::Draw29, m_Group[0], "Draw29");
	AddFunction(CGroup4::Draw30, m_Group[0], "Draw30");
	AddFunction(CGroup4::Draw31, m_Group[0], "Draw31");
	AddFunction(CGroup4::Draw32, m_Group[0], "Draw32");
	AddFunction(CGroup4::Draw33, m_Group[0], "Draw33");
	AddFunction(CGroup4::Draw34, m_Group[0], "Draw34");
	AddFunction(CGroup4::Draw35, m_Group[0], "Draw35");
	AddFunction(CGroup4::Draw36, m_Group[0], "Draw36");
	AddFunction(CGroup4::Draw37, m_Group[0], "Draw37");
	AddFunction(CGroup4::Draw38, m_Group[0], "Draw38");
	AddFunction(CGroup4::Draw39, m_Group[0], "Draw39");
	AddFunction(CGroup4::Draw40, m_Group[0], "Draw40");
	AddFunction(CGroup4::Draw41, m_Group[0], "Draw41");
	AddFunction(CGroup4::Draw42, m_Group[0], "Draw42");
	AddFunction(CGroup4::Draw43, m_Group[0], "Draw43");
	AddFunction(CGroup4::Draw44, m_Group[0], "Draw44");
	AddFunction(CGroup4::Draw45, m_Group[0], "Draw45");
	AddFunction(CGroup4::Draw46, m_Group[0], "Draw46");
	AddFunction(CGroup4::Draw47, m_Group[0], "Draw47");
	AddFunction(CGroup4::Draw48, m_Group[0], "Draw48");
	AddFunction(CGroup4::Draw49, m_Group[0], "Draw49");
	AddFunction(CGroup4::Draw50, m_Group[0], "Draw50");
	AddFunction(CGroup4::Draw51, m_Group[0], "Draw51");
	AddFunction(CGroup4::Draw52, m_Group[0], "Draw52");
	AddFunction(CGroup4::Draw53, m_Group[0], "Draw53");
	AddFunction(CGroup4::Draw54, m_Group[0], "Draw54");
	AddFunction(CGroup4::Draw55, m_Group[0], "Draw55");
	AddFunction(CGroup4::Draw56, m_Group[0], "Draw56");
	AddFunction(CGroup4::Draw57, m_Group[0], "Draw57");
	AddFunction(CGroup4::Draw58, m_Group[0], "Draw58");
	AddFunction(CGroup4::Draw59, m_Group[0], "Draw59");
	AddFunction(CGroup4::Draw60, m_Group[0], "Draw60");
	AddFunction(CGroup4::Draw61, m_Group[0], "Draw61"); 
	AddFunction(CGroup4::Draw62, m_Group[0], "Draw62"); 
	AddFunction(CGroup4::Draw63, m_Group[0], "Draw63"); 
//	AddFunction(CGroup4::Draw64, m_Group[0], "Draw64"); 
	AddFunction(CGroup4::Draw65, m_Group[0], "Draw65"); 
	AddFunction(CGroup4::Draw66, m_Group[0], "Draw66"); 
	AddFunction(CGroup4::Draw67, m_Group[0], "Draw67"); 
	AddFunction(CGroup4::Draw68, m_Group[0], "Draw68"); 
//	AddFunction(CGroup4::Draw69, m_Group[0], "Draw69"); 

	AddFunction(CGroup4::DrawB01, m_Group[0], "DrawB01"); 
	AddFunction(CGroup4::DrawB02, m_Group[0], "DrawB02"); 
	AddFunction(CGroup4::DrawB03, m_Group[0], "DrawB03"); 
	AddFunction(CGroup4::DrawB04, m_Group[0], "DrawB04"); 
	AddFunction(CGroup4::DrawB05, m_Group[0], "כוכבית"); 
	AddFunction(CGroup4::DrawB06, m_Group[0], "DrawB06"); 


	AddFunction(CGroup4::DrawC01, m_Group[0], "DrawC01"); 
	AddFunction(CGroup4::DrawC02, m_Group[0], "DrawC02"); 
	AddFunction(CGroup4::DrawC03, m_Group[0], "DrawC03"); 
	AddFunction(CGroup4::DrawC04, m_Group[0], "DrawC04"); 
	AddFunction(CGroup4::DrawC05, m_Group[0], "DrawC05"); 
	AddFunction(CGroup4::DrawC06, m_Group[0], "DrawC06"); 
	AddFunction(CGroup4::DrawC07, m_Group[0], "DrawC07"); 
	AddFunction(CGroup4::DrawC08, m_Group[0], "DrawC08"); 
	AddFunction(CGroup4::DrawC09, m_Group[0], "DrawC09"); 


	AddFunction(CGroup4::DrawD01, m_Group[0], "DrawD01"); 
	AddFunction(CGroup4::DrawD02, m_Group[0], "DrawD02"); 
	AddFunction(CGroup4::DrawD03, m_Group[0], "DrawD03"); 
	AddFunction(CGroup4::DrawD04, m_Group[0], "DrawD04"); 
	AddFunction(CGroup4::DrawD05, m_Group[0], "DrawD05"); 
	AddFunction(CGroup4::DrawD06, m_Group[0], "DrawD06"); 
	AddFunction(CGroup4::DrawD07, m_Group[0], "DrawD07"); 
	AddFunction(CGroup4::DrawD08, m_Group[0], "DrawD08"); 
	AddFunction(CGroup4::DrawD09, m_Group[0], "DrawD09"); 
	AddFunction(CGroup4::DrawD10, m_Group[0], "DrawD10"); 
	AddFunction(CGroup4::DrawD11, m_Group[0], "DrawD11"); 

	AddFunction(CGroup4::DrawE01, m_Group[0], "DrawE01"); 
	AddFunction(CGroup4::DrawE02, m_Group[0], "DrawE02"); 
	AddFunction(CGroup4::DrawE03, m_Group[0], "DrawE03"); 
	AddFunction(CGroup4::DrawE04, m_Group[0], "DrawE04"); 
	AddFunction(CGroup4::DrawE05, m_Group[0], "DrawE05"); 
	AddFunction(CGroup4::DrawE06, m_Group[0], "DrawE06"); 
	AddFunction(CGroup4::DrawE07, m_Group[0], "DrawE07"); 
	AddFunction(CGroup4::DrawE08, m_Group[0], "DrawE08"); 

	AddFunction(CGroup4::DrawF01, m_Group[0], "Paris 2999"); 
//	AddFunction(CGroup4::DrawF01, m_Group[0], "DrawF01"); 
	AddFunction(CGroup4::DrawF02, m_Group[0], "April Paris 3000"); 

	AddFunction(CGroup4::DrawG01, m_Group[0], "DrawG01"); 
	AddFunction(CGroup4::DrawG02, m_Group[0], "DrawG02"); 

}



