//-----------------------------------------------------------------------------
// File: ProgressiveMesh.cpp
//
// Desc: Sample of creating progressive meshes in D3D
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include "stdafx.h"
#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <commdlg.h>
#include <D3DX9.h>
#include "DXUtil.h"
#include "D3DEnumeration.h"
#include "D3DSettings.h"
#include "D3DUtil.h"

#include "mesh.h"


//-----------------------------------------------------------------------------
// Name: CMeshRender()
// Desc: Constructor
//-----------------------------------------------------------------------------
CMeshRender::CMeshRender()
{
    // Initialize member variables
    DXUtil_GetDXSDKMediaPathCb( m_strInitialDir, sizeof(m_strInitialDir) );
    _tcscpy( m_strMeshFilename, _T("Sphere.x") );//_T("Tiger.x") );

    m_pPMeshes           = NULL;
    m_cPMeshes           = 0;
    m_pPMeshFull         = NULL;
    m_bShowOptimized     = TRUE;

    m_dwNumMaterials     = 0L;
    m_mtrlMeshMaterials  = NULL;
    m_pMeshTextures      = NULL;

    m_bDisplayHelp       = FALSE;

    m_bInitDone          = FALSE;

	m_pd3dDevice = NULL;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Called once per frame, the call is the entry point for 3d
//       rendering. This function sets up render states, clears the
//       viewport, and renders the scene.
//-----------------------------------------------------------------------------
HRESULT CMeshRender::Render()
{
    if (!m_bInitDone)
        return S_OK;

    // Clear the backbuffer
    //m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
    //                     0x000000ff, 1.0f, 0x00000000 );

    {
        if( m_pPMeshes )
        {
            // Set and draw each of the materials in the mesh
            for( DWORD i=0; i<m_dwNumMaterials; i++ )
            {
                m_pd3dDevice->SetMaterial( &m_mtrlMeshMaterials[i] );
                m_pd3dDevice->SetTexture( 0, m_pMeshTextures[i] );
                if (m_bShowOptimized)
                    m_pPMeshes[m_iPMeshCur]->DrawSubset( i );
                else
                    m_pPMeshFull->DrawSubset( i );
            }
        }
    }

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: InitDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMeshRender::InitDeviceObjects()
{
    DWORD cVerticesPerMesh;

    // Load mesh
    LPD3DXBUFFER pAdjacencyBuffer = NULL;
    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;
    LPD3DXMESH   pMesh = NULL;
    LPD3DXPMESH  pPMesh = NULL;
    LPD3DXMESH   pTempMesh;
    LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
    void*        pVertices;
    TCHAR        strMediaPath[512];
    HRESULT      hr;
    DWORD        dw32BitFlag;
    DWORD        cVerticesMin;
    DWORD        cVerticesMax;
    DWORD        iPMesh;
    D3DXWELDEPSILONS Epsilons;
    DWORD        i;
    D3DXMATERIAL* d3dxMaterials;

    // Find the path to the mesh
    if( FAILED( DXUtil_FindMediaFileCb( strMediaPath, sizeof(strMediaPath), m_strMeshFilename ) ) )
        return E_FAIL;//D3DAPPERR_MEDIANOTFOUND;

    // Load the mesh from the specified file
    if( FAILED( hr = D3DXLoadMeshFromX( strMediaPath, D3DXMESH_MANAGED, m_pd3dDevice,
                                        &pAdjacencyBuffer, &pD3DXMtrlBuffer, NULL, 
                                        &m_dwNumMaterials, &pMesh ) ) )
    {
        // hide error so that device changes will not cause exit, shows blank screen instead
        goto End;
    }

    dw32BitFlag = (pMesh->GetOptions() & D3DXMESH_32BIT);

    // perform simple cleansing operations on mesh
    if( FAILED( hr = D3DXCleanMesh( pMesh, (DWORD*)pAdjacencyBuffer->GetBufferPointer(), &pTempMesh, 
                                           (DWORD*)pAdjacencyBuffer->GetBufferPointer(), NULL ) ) )
    {
        m_dwNumMaterials = 0;
        goto End;
    }
    SAFE_RELEASE(pMesh);
    pMesh = pTempMesh;

    //  Perform a weld to try and remove excess vertices like the model bigship1.x in the DX9.0 SDK (current model is fixed)
    //    Weld the mesh using all epsilons of 0.0f.  A small epsilon like 1e-6 works well too
    memset(&Epsilons, 0, sizeof(D3DXWELDEPSILONS));
    if( FAILED( hr = D3DXWeldVertices( pMesh, 0, &Epsilons, 
                                                (DWORD*)pAdjacencyBuffer->GetBufferPointer(), 
                                                (DWORD*)pAdjacencyBuffer->GetBufferPointer(), NULL, NULL ) ) )
    {
        m_dwNumMaterials = 0;
        goto End;
    }

    // verify validity of mesh for simplification
    if( FAILED( hr = D3DXValidMesh( pMesh, (DWORD*)pAdjacencyBuffer->GetBufferPointer(), NULL ) ) )
    {
        m_dwNumMaterials = 0;
        goto End;
    }

    // Allocate a material/texture arrays
    d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    m_mtrlMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
    m_pMeshTextures     = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

    // Copy the materials and load the textures
    for( i=0; i<m_dwNumMaterials; i++ )
    {
        m_mtrlMeshMaterials[i] = d3dxMaterials[i].MatD3D;
        m_mtrlMeshMaterials[i].Ambient = m_mtrlMeshMaterials[i].Diffuse;

        // Find the path to the texture and create that texture
        DXUtil_FindMediaFileCb( strMediaPath, sizeof(strMediaPath), d3dxMaterials[i].pTextureFilename );
        if( FAILED( D3DXCreateTextureFromFile( m_pd3dDevice, strMediaPath, 
                                               &m_pMeshTextures[i] ) ) )
            m_pMeshTextures[i] = NULL;
    }
    pD3DXMtrlBuffer->Release();
    pD3DXMtrlBuffer = NULL;


    // Lock the vertex buffer, to generate a simple bounding sphere
    hr = pMesh->GetVertexBuffer( &pVertexBuffer );
    if( FAILED(hr) )
        goto End;

    hr = pVertexBuffer->Lock( 0, 0, &pVertices, D3DLOCK_NOSYSLOCK );
    if( FAILED(hr) )
        goto End;

    hr = D3DXComputeBoundingSphere( (D3DXVECTOR3*)pVertices, pMesh->GetNumVertices(),
                                    D3DXGetFVFVertexSize(pMesh->GetFVF()),
                                    &m_vObjectCenter, &m_fObjectRadius );
    pVertexBuffer->Unlock();
    pVertexBuffer->Release();

    if( FAILED(hr) || m_dwNumMaterials == 0 )
        goto End;

    if ( !(pMesh->GetFVF() & D3DFVF_NORMAL) )
    {
        hr = pMesh->CloneMeshFVF( dw32BitFlag|D3DXMESH_MANAGED, pMesh->GetFVF() | D3DFVF_NORMAL, 
                                            m_pd3dDevice, &pTempMesh );
        if (FAILED(hr))
            goto End;

        D3DXComputeNormals( pTempMesh, NULL );

        pMesh->Release();
        pMesh = pTempMesh;
    }

    hr = D3DXGeneratePMesh( pMesh, (DWORD*)pAdjacencyBuffer->GetBufferPointer(),
                            NULL, NULL, 1, D3DXMESHSIMP_VERTEX, &pPMesh);
    if( FAILED(hr) )
        goto End;

    cVerticesMin = pPMesh->GetMinVertices();
    cVerticesMax = pPMesh->GetMaxVertices();

    cVerticesPerMesh = (cVerticesMax - cVerticesMin) / 10;

    m_cPMeshes = max(1, (DWORD)ceil((cVerticesMax - cVerticesMin) / (float)cVerticesPerMesh));
    m_pPMeshes = new LPD3DXPMESH[m_cPMeshes];
    if (m_pPMeshes == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto End;
    }
    memset(m_pPMeshes, 0, sizeof(LPD3DXPMESH) * m_cPMeshes);

    // clone full size pmesh
    hr = pPMesh->ClonePMeshFVF( D3DXMESH_MANAGED | D3DXMESH_VB_SHARE, pPMesh->GetFVF(), m_pd3dDevice, &m_pPMeshFull );
    if (FAILED(hr))
        goto End;

    // clone all the separate pmeshes
    for (iPMesh = 0; iPMesh < m_cPMeshes; iPMesh++)
    {
        hr = pPMesh->ClonePMeshFVF( D3DXMESH_MANAGED | D3DXMESH_VB_SHARE, pPMesh->GetFVF(), m_pd3dDevice, &m_pPMeshes[iPMesh] );
        if (FAILED(hr))
            goto End;

        // trim to appropriate space
        hr = m_pPMeshes[iPMesh]->TrimByVertices(cVerticesMin + cVerticesPerMesh * iPMesh, cVerticesMin + cVerticesPerMesh * (iPMesh+1), NULL, NULL);
        if (FAILED(hr))
            goto End;

        hr = m_pPMeshes[iPMesh]->OptimizeBaseLOD(D3DXMESHOPT_VERTEXCACHE, NULL);
        if (FAILED(hr))
            goto End;
    }

    // set current to be maximum number of vertices
    m_iPMeshCur = m_cPMeshes - 1;
    hr = m_pPMeshes[m_iPMeshCur]->SetNumVertices(cVerticesMax);
    if (FAILED(hr))
        goto End;

    hr = m_pPMeshFull->SetNumVertices(cVerticesMax);
    if (FAILED(hr))
        goto End;
End:
    SAFE_RELEASE( pAdjacencyBuffer );
    SAFE_RELEASE( pD3DXMtrlBuffer );
    SAFE_RELEASE( pMesh );
    SAFE_RELEASE( pPMesh );

    if (FAILED(hr))
    {
        for (iPMesh = 0; iPMesh < m_cPMeshes; iPMesh++)
        {
            SAFE_RELEASE( m_pPMeshes[iPMesh] );
        }

        delete []m_pPMeshes;
        m_cPMeshes = 0;
        m_pPMeshes = NULL;
        SAFE_RELEASE( m_pPMeshFull )
    }

    return hr;
}

//-----------------------------------------------------------------------------
// Name: RestoreDeviceObjects()
// Desc: Initialize scene objects.
//-----------------------------------------------------------------------------
HRESULT CMeshRender::RestoreDeviceObjects()
{
    // Setup render state
    m_pd3dDevice->SetRenderState( D3DRS_LIGHTING,     TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );
    m_pd3dDevice->SetRenderState( D3DRS_ZENABLE,      TRUE );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    m_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

    // Setup the light
    D3DLIGHT9 light;
    D3DUtil_InitLight( light, D3DLIGHT_DIRECTIONAL, 1.0f, -1.0f, 1.0f );
    m_pd3dDevice->SetLight( 0, &light );
    m_pd3dDevice->LightEnable( 0, TRUE );

    D3DLIGHT9 light1;
    D3DUtil_InitLight( light1, D3DLIGHT_DIRECTIONAL, 1.0f, 10.0f, -1.0f );
    m_pd3dDevice->SetLight( 1, &light1 );
    m_pd3dDevice->LightEnable( 1, TRUE );

    m_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00333333 );


    m_bInitDone = TRUE;

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: DeleteDeviceObjects()
// Desc: Called when the app is exiting, or the device is being changed,
//       this function deletes any device dependent objects.
//-----------------------------------------------------------------------------
HRESULT CMeshRender::DeleteDeviceObjects()
{
    DWORD iPMesh;

    if( m_pMeshTextures != NULL)
    {
        for( UINT i=0; i<m_dwNumMaterials; i++ )
            SAFE_RELEASE( m_pMeshTextures[i] );
    }
    SAFE_DELETE_ARRAY( m_pMeshTextures );

    SAFE_RELEASE( m_pPMeshFull );
    for (iPMesh = 0; iPMesh < m_cPMeshes; iPMesh++)
    {
        SAFE_RELEASE( m_pPMeshes[iPMesh] );
    }
    m_cPMeshes = 0;
    delete []m_pPMeshes;

    SAFE_DELETE_ARRAY( m_mtrlMeshMaterials );
    m_dwNumMaterials = 0L;

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: SetNumVertices()
// Desc: Sets the number of vertices to display on the current progressive mesh
//-----------------------------------------------------------------------------
void
CMeshRender::SetNumVertices(DWORD dwNumVertices)
{
    m_pPMeshFull->SetNumVertices( dwNumVertices );

    // if current pm valid for desired value, then set the number of vertices directly
    if ((dwNumVertices >= m_pPMeshes[m_iPMeshCur]->GetMinVertices()) && (dwNumVertices <= m_pPMeshes[m_iPMeshCur]->GetMaxVertices()))
    {
        m_pPMeshes[m_iPMeshCur]->SetNumVertices( dwNumVertices );
    }
    else  // search for the right one
    {
        m_iPMeshCur = m_cPMeshes - 1;

        // look for the correct "bin" 
        while (m_iPMeshCur > 0)
        {
            // if number of vertices is less than current max then we found one to fit
            if (dwNumVertices >= m_pPMeshes[m_iPMeshCur]->GetMinVertices())
                break;

            m_iPMeshCur -= 1;
        }

        // set the vertices on the newly selected mesh
        m_pPMeshes[m_iPMeshCur]->SetNumVertices( dwNumVertices );
    }
}
