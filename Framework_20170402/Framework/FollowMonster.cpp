#include "stdafx.h"
#include "FollowMonster.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"


CFollowMonster::CFollowMonster()
{
}


CFollowMonster::~CFollowMonster()
{
}
void CFollowMonster::Initialize(void)
{
	Pos = D3DXVECTOR3(2000, 300, 0);
	Angle = 0;
	Radius = 35;
	strTextureKey = L"FollowMonster";

	Dir = D3DXVECTOR3(0, 0, 0);

	HP = 3;
}
int CFollowMonster::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	CObj* Player = CObjMgr::GetInst()->GetPlayer();

	D3DXVECTOR3 OriginDir = D3DXVECTOR3(0,0,0);
	OriginDir = Player->Pos - Pos;

	D3DXVec3Normalize( &Dir, &OriginDir);

	Pos += Dir * DeltaTime * 50;

	/////////////////////////////////////
	//���� �𸣴°� ������. �׷� ���Լ��� �ʿ���.
	//������� �������� ���´�.
	float MonsterAngle = acos(Dir.x);
	//acos�� 0~180������ �ۿ� ���� ���� ���Ѵ�.
	//0~180�� �����̴�.
	if (Player->Pos.y >= Pos.y)
	{
		// * 180 / PI�� ���Ȱ��� ��׸��� ��ȯ�ϴ� ��.
		Angle = MonsterAngle * 180 / PI;
	}
	else //180 ~360�� �����̴�.
	{
		Angle = 360 - (MonsterAngle * 180 / PI);
	}

	ComputeMatrix();
	return 0;
}

void CFollowMonster::Render(void)
{
	//�̹����� �����´�.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CFollowMonster::Release(void)
{

}