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

	// ��ġ�� ������ ��������.
	if(FAILED(CheckDevice()))
		return E_FAIL;

	// ��ġ�� ��ǥ�ϴ� ��ü�� ������.
	if(FAILED(MakeDevice(Mode)))
		return E_FAIL;

	if(FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		//��������Ʈ ��ü���� ����
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CDeviceMgr::CheckDevice( void )
{
	D3DCAPS9			d3dCaps;
	ZeroMemory(&d3dCaps, sizeof(D3DCAPS9));

	// ��ġ�� ������ ����ü�� ��´�.
	if(FAILED(m_pDirect->GetDeviceCaps(D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL
		, &d3dCaps)))
	{
		//����û�� �������� ����
		return E_FAIL;
	}

	// Ư������(���ؽ����μ���)������ ���縦 �Ѵ�.
	// ���ؽ� ���μ��� : ���Ǻ�ȭ + ����
	if(d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// ���� ��������� ��ġ�� ���� ����� �����Ѵ�.
		m_BehaviorFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		m_BehaviorFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}	
	return S_OK;
}

// ��ġ�� ��ǥ�ϴ� ��ü�� �����Ѵ�
HRESULT CDeviceMgr::MakeDevice(WINMODE	Mode)
{
	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetDevParameters(d3dpp, Mode);

	if(FAILED(m_pDirect->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL
		, g_hWnd, m_BehaviorFlag, &d3dpp, &m_pDevice)))
	{
		//��ġ ���� ����
		return E_FAIL;
	}

	return S_OK;		
}

void CDeviceMgr::SetDevParameters(D3DPRESENT_PARAMETERS& d3dpp
								  , WINMODE Mode)
{
	//ȭ�� ũ�⸦ ����. �ӽ÷� ���� 800 ���� 600���� ��������
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
	// ���ۿ� ������ �����Ѵ�.	
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
