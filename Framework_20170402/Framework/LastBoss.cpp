#include "stdafx.h"
#include "LastBoss.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "MonsterBullet.h"

CLastBoss::CLastBoss()
{
}


CLastBoss::~CLastBoss()
{
}

void CLastBoss::Initialize(void)
{
	Pos = D3DXVECTOR3(1500, 400, 0);
	Angle = 0;
	Radius = 100;
	strTextureKey = L"LastBossMonster";

	HP = 100;
	Dir = D3DXVECTOR3(0, 0, 0);
}

int CLastBoss::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	Pos += Dir * DeltaTime * 50;
	ComputeMatrix();
	return 0;
}

void CLastBoss::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CLastBoss::Release(void)
{

}