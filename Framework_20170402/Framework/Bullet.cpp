#include "stdafx.h"
#include "Bullet.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}
void CBullet::Initialize(void)
{
	Pos = D3DXVECTOR3(0, 100, 0);
	Angle = 0;

	strTextureKey = L"Bullet";
	Radius = 26;

	Dir = D3DXVECTOR3(1, 0, 0);
}
int CBullet::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();
	Pos = Pos + (Dir * DeltaTime * 300);

	//총알이
	//몬스터 전체랑 충돌체크를 한다.
	int Result = CObjMgr::GetInst()->CollisionSphere(this, OBJ_MONSTER);
	if (Result == 1)
	{
		return 1;
	}

	//총알이 화면 밖으로 나갔을때 삭제처리 한다.!
	float ScrollX = CObjMgr::GetInst()->ScrollX;

	if (Pos.y < 0 || Pos.y > WIN_Y ||
		Pos.x - ScrollX < 0 || Pos.x - ScrollX > WIN_X)
	{
		return 1;
	}

	ComputeMatrix();

	return 0;
}

void CBullet::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CBullet::Release(void)
{

}