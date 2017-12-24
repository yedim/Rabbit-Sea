#include "stdafx.h"
#include "Effect.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"


CEffect::CEffect()
{
}

CEffect::~CEffect()
{
}

void CEffect::Initialize(void)
{
	Pos = D3DXVECTOR3(0, 0, 0);
	Angle = 0;
	Radius = 0;

	strTextureKey = L"Effect_0";

	FrameCount = 17; //총 몇장인가
	FrameTimer = 0;

	CurrentIndex = 0;
}
int CEffect::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	FrameTimer += DeltaTime;

	if (FrameTimer > 0.05f)
	{
		FrameTimer = 0;
		++CurrentIndex;
	}

	if (CurrentIndex >= FrameCount)
	{
		return 1;
	}

	/*FrameTimer += DeltaTime * 0.5f;

	CurrentIndex = int((FrameCount ) * (FrameTimer));

	if (CurrentIndex >= FrameCount)
	{
		return 1;
	}*/

	TCHAR szKey[64] = {};
	wsprintf(szKey, L"Effect_%d", CurrentIndex);
	strTextureKey = szKey;

	ComputeMatrix();

	return 0;
}

void CEffect::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CEffect::Release(void)
{

}
