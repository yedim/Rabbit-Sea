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
	//내가 모르는게 각도다. 그럼 역함수가 필요함.
	//결과값은 라디안으로 들어온다.
	float MonsterAngle = acos(Dir.x);
	//acos은 0~180도까지 밖에 값을 주지 못한다.
	//0~180도 사이이다.
	if (Player->Pos.y >= Pos.y)
	{
		// * 180 / PI는 라디안값을 디그리로 변환하는 것.
		Angle = MonsterAngle * 180 / PI;
	}
	else //180 ~360도 사이이다.
	{
		Angle = 360 - (MonsterAngle * 180 / PI);
	}

	ComputeMatrix();
	return 0;
}

void CFollowMonster::Render(void)
{
	//이미지를 가져온다.
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