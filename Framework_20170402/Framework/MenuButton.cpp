#include "stdafx.h"
#include "MenuButton.h"
#include "TextureMgr.h"
#include "DeviceMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Mouse.h"

CMenuButton::CMenuButton()
{
}


CMenuButton::~CMenuButton()
{
}

void CMenuButton::Initialize(void)
{
	Pos = D3DXVECTOR3(0, 0, 0);
	Angle = 0;
	Radius = 0;

	strTextureKey = L"StartButton";

	Width = 99;
	Height = 99;
}
int CMenuButton::Update(void)
{
	float DeltaTime = CTimeMgr::GetInst()->GetTime();

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		POINT MousePos = CMouse::GetMousePos();

		if (MousePos.x > Pos.x - Width / 2
			&& MousePos.x < Pos.x + Width / 2
			&& MousePos.y > Pos.y - Height / 2
			&& MousePos.y < Pos.y + Height / 2)
		{
			CObjMgr::GetInst()->CurrentStageKey = STAGE_TWO;
			CObjMgr::GetInst()->ChangeStage = true;
		}
	}

	ComputeMatrix();

	return 0;
}

void CMenuButton::Render(void)
{
	//이미지를 가져온다.
	TEXINFO*	pTexInfo = CTextureMgr::GetInst()->GetTextureInfo(strTextureKey);

	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexInfo->TexInfo.Width / 2.f
		, pTexInfo->TexInfo.Height / 2.f, 0.f);

	CDeviceMgr::GetInst()->GetSprite()->SetTransform(&matWorld);

	CDeviceMgr::GetInst()->GetSprite()->Draw(pTexInfo->pTexture
		, NULL, &vCenter, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}
void CMenuButton::Release(void)
{

}
