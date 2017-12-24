#include "StdAfx.h"
#include "DeviceMgr.h"

CDeviceMgr* CDeviceMgr::m_pInst = NULL;
CDeviceMgr::CDeviceMgr(void)
: m_pDirect(NULL)
, m_BehaviorFlag(0)
, m_pDevice(NULL)
, m_pSprite(NULL)
{
}

CDeviceMgr::~CDeviceMgr(void)
{
	Release();
}

HRESULT CDeviceMgr::InitDevice(WINMODE	Mode)
{
	m_pDirect = Direct3DCreate9(D3D_SDK_VERSION);

	// 장치의 성능을 조사하자.
	if(FAILED(CheckDevice()))
		return E_FAIL;

	// 장치를 대표하는 객체를 만들자.
	if(FAILED(MakeDevice(Mode)))
		return E_FAIL;

	if(FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		//스프라이트 객체생성 실패
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CDeviceMgr::CheckDevice( void )
{
	D3DCAPS9			d3dCaps;
	ZeroMemory(&d3dCaps, sizeof(D3DCAPS9));

	// 장치의 정보를 구조체에 담는다.
	if(FAILED(m_pDirect->GetDeviceCaps(D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL
		, &d3dCaps)))
	{
		//장지청보 가져오기 실패
		return E_FAIL;
	}

	// 특정성능(버텍스프로세싱)에대한 조사를 한다.
	// 버텍스 프로세싱 : 점의변화 + 조명
	if(d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// 위의 결과에따라 장치의 동작 방식을 결정한다.
		m_BehaviorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		m_BehaviorFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}	
	return S_OK;
}

// 장치를 대표하는 객체를 생성한다
HRESULT CDeviceMgr::MakeDevice(WINMODE	Mode)
{
	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetDevParameters(d3dpp, Mode);

	if(FAILED(m_pDirect->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL
		, g_hWnd, m_BehaviorFlag, &d3dpp, &m_pDevice)))
	{
		//장치 생성 실패
		return E_FAIL;
	}

	return S_OK;		
}

void CDeviceMgr::SetDevParameters(D3DPRESENT_PARAMETERS& d3dpp
								  , WINMODE Mode)
{
	//화면 크기를 지정. 임시로 가로 800 세로 600으로 고정했음
	d3dpp.BackBufferWidth = WIN_X;
	d3dpp.BackBufferHeight = WIN_Y;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = BOOL(Mode);

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void CDeviceMgr::Render_Begin( void )
{
	// 버퍼에 내용을 삭제한다.	
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL
		, D3DCOLOR_ARGB(255, 0, 0, 0), 1.f, 0);

	m_pDevice->BeginScene();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceMgr::Render_End( void )
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void CDeviceMgr::Release(void)
{
}
