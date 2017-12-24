#include "stdafx.h"
#include "Monster.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "TimeMgr.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}
void CMonster::Initialize(void)
{
	Pos = D3DXVECTOR3(0, 0, 0);
	Angle = 0;
	Radius = 25;
	strTextureKey = L"Monster";

	HP = 3;
	Dir = D3DXVECTOR3(0, 0, 0);
	MoveTime = 0;
}

int CMonster::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	Pos += Dir * (DeltaTime * 50);

	//시간을 누적시킨다.
	MoveTime += DeltaTime;
	//일정시간이 지나면 방향벡터를 바꿔준다.
	if (MoveTime > 2.0f)
	{
		MoveTime = 0;
		Dir.x = Dir.x * -1;

		if (Dir.x > 0)
		{
			strTextureKey = L"Monster_R";
		}
		else
		{
			strTextureKey = L"Monster";
		}
	}

	ComputeMatrix();
	return 0;
}

void CMonster::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CMonster::Release(void)
{

}