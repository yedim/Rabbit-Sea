#include "stdafx.h"
#include "BackGround.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"

CBackGround::CBackGround()
{
}


CBackGround::~CBackGround()
{
}

void CBackGround::Initialize(void)
{
	Pos = D3DXVECTOR3(WIN_X / 2, WIN_Y / 2, 0);

	strTextureKey = L"BackGround_0";

	Angle = 0;
}

int CBackGround::Update(void)
{
	ComputeMatrix();
	return 0;
}

void CBackGround::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}
void CBackGround::Release(void)
{

}
