#include "stdafx.h"
#include "Obj.h"
#include "ObjMgr.h"


CObj::CObj()
{
}

CObj::~CObj()
{
}

void CObj::Initialize(void)
{
}
int CObj::Update(void)
{
	return 0;
}
void CObj::Render(void)
{

}

void CObj::ComputeMatrix()
{
	D3DXMATRIX matScale;
	D3DXMatrixIdentity(&matScale);
	matScale._11 = 1; //가로 크기 변환
	matScale._22 = 1; //세로 크기 변화
	matScale._33 = 1; // 3D 작업때만 씀. 지금은 안씀.

	//자전
	D3DXMATRIX matRotation;
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixRotationZ(&matRotation, Angle * (PI / 180));

	//위치
	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	matTrans._41 = Pos.x - CObjMgr::GetInst()->ScrollX;
	matTrans._42 = Pos.y;

	//위치행렬 만들어주는 함수.
	//D3DXMatrixTranslation(&matTrans, Pos.x, Pos.y, 0);
	matWorld = matScale * matRotation * matTrans;
}
void CObj::Release(void)
{

}