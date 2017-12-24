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
	matScale._11 = 1; //���� ũ�� ��ȯ
	matScale._22 = 1; //���� ũ�� ��ȭ
	matScale._33 = 1; // 3D �۾����� ��. ������ �Ⱦ�.

	//����
	D3DXMATRIX matRotation;
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixRotationZ(&matRotation, Angle * (PI / 180));

	//��ġ
	D3DXMATRIX matTrans;
	D3DXMatrixIdentity(&matTrans);
	matTrans._41 = Pos.x - CObjMgr::GetInst()->ScrollX;
	matTrans._42 = Pos.y;

	//��ġ��� ������ִ� �Լ�.
	//D3DXMatrixTranslation(&matTrans, Pos.x, Pos.y, 0);
	matWorld = matScale * matRotation * matTrans;
}
void CObj::Release(void)
{

}