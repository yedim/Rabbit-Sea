#include "stdafx.h"
#include "MonsterBullet.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"


CMonsterBullet::CMonsterBullet()
{
}


CMonsterBullet::~CMonsterBullet()
{
}
void CMonsterBullet::Initialize(void)
{
	Pos = D3DXVECTOR3(0, 100, 0);
	Angle = 0;

	strTextureKey = L"MonsterBullet";
	Radius = 16;

	Dir = D3DXVECTOR3(-1, 0, 0);
}
int CMonsterBullet::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	Pos = Pos + (Dir * DeltaTime * 400);

	//�Ѿ��� ���� ��ü�� �浹üũ�� �Ѵ�.
	int Result = CObjMgr::GetInst()->CollisionSphere(this, OBJ_PLAYER);
	if (Result == 1)
	{
		return 1;
	}

	//�Ѿ��� ȭ�� ������ �������� ����ó�� �Ѵ�.!
	float ScrollX = CObjMgr::GetInst()->ScrollX;
	if (Pos.y < 0 || Pos.y > 600 ||
		Pos.x - ScrollX < 0 || Pos.x - ScrollX > 800)
	{
		return 1;
	}

	ComputeMatrix();

	return 0;
}

void CMonsterBullet::Render(void)
{
	//�̹����� �����´�.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CMonsterBullet::Release(void)
{

}