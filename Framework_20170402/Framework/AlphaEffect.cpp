#include "stdafx.h"
#include "AlphaEffect.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"


CAlphaEffect::CAlphaEffect()
{
}


CAlphaEffect::~CAlphaEffect()
{
}

void CAlphaEffect::Initialize(void)
{
	Pos = D3DXVECTOR3(400, 300, 0);
	Angle = 0;
	Radius = 0;
	strTextureKey = L"NextStage";
	
	FrameTimer = 0;

	DrawAlpha = 1.0f;
}
int CAlphaEffect::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	FrameTimer += DeltaTime;

	int T = 5;
	DrawAlpha = (T - FrameTimer) / T;

	if (FrameTimer > T)
	{
		return 1;
	}

	//ComputeMatrix();
	D3DXMatrixIdentity(&matWorld);

	matWorld._41 = Pos.x;
	matWorld._42 = Pos.y;

	return 0;
}

void CAlphaEffect::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(int(255.0f * DrawAlpha), 255, 255, 255));
}
void CAlphaEffect::Release(void)
{

}
