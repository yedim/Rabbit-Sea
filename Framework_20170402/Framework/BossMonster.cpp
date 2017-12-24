#include "stdafx.h"
#include "BossMonster.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "MonsterBullet.h"

CBossMonster::CBossMonster()
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	Pos = D3DXVECTOR3(2000, 300, 0);
	Angle = 0;
	Radius = 90;
	strTextureKey = L"BossMonster";

	HP = 10;
	Dir = D3DXVECTOR3(0, 1, 0);

	MoveTime = 0;
	AttTime = 0;
	AttCount = 0;
}

int CBossMonster::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	Pos += Dir * DeltaTime * 50;

	MoveTime += DeltaTime;
	//일정시간이 지나면 방향벡터를 바꿔준다.
	if (MoveTime > 2.0f)
	{
		MoveTime = 0;
		Dir.y = Dir.y * -1;
	}

	AttTime += DeltaTime;
	if (AttTime > 1.0f) //1초에 한번씩 
	{
		++AttCount;
		AttTime = 0;
		CObjMgr::GetInst()->AddObject(new CMonsterBullet, OBJ_MONSTER_BULLET
			, Pos);

		if (AttCount > 3)
		{
			AttCount = 0;
			CObjMgr::GetInst()->AddObject(new CMonsterBullet, OBJ_MONSTER_BULLET
				, Pos, D3DXVECTOR3(-1,1,0));
			CObjMgr::GetInst()->AddObject(new CMonsterBullet, OBJ_MONSTER_BULLET
				, Pos, D3DXVECTOR3(-1, -1, 0));
		}
	}

	ComputeMatrix();
	return 0;
}

void CBossMonster::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CBossMonster::Release(void)
{

}