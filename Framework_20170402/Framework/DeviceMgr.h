#pragma once

#include "Defines.h"

class CDeviceMgr
{
private:
	static	CDeviceMgr*		m_pInst;

public:
	static CDeviceMgr* GetInst(void)
	{
		if (m_pInst == NULL)
			m_pInst = new CDeviceMgr;

		return m_pInst;
	}

	void DestoryInst(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}
private:
	DWORD					m_BehaviorFlag;
private:	
	LPDIRECT3D9				m_pDirect;
	LPDIRECT3DDEVICE9		m_pDevice;
	LPD3DXSPRITE			m_pSprite;

public:
	LPDIRECT3DDEVICE9	GetDevice(void) {
		return m_pDevice;}
	LPD3DXSPRITE	GetSprite(void) {
		return m_pSprite;}

public: 
	HRESULT InitDevice(WINMODE Mode);	// 초기화
	HRESULT CheckDevice(void);	//조사
	HRESULT MakeDevice(WINMODE Mode); //객체를 생성
	void SetDevParameters(D3DPRESENT_PARAMETERS& d3dpp, WINMODE Mode);

public:
	void Render_Begin(void);
	void Render_End(void);
	void Release(void);

public:
	CDeviceMgr(void);
public:
	~CDeviceMgr(void);
};

