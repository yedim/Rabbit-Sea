#pragma once

#include "Defines.h"
#include "Single.h"

class CObj;
class CObjMgr
	: public CSingle<CObjMgr>
{
public:
	// ��ü ������Ʈ�� �����ϴ� ����Ʈ
	list<CObj*>	ObjList[OBJ_MAX];
	// ���� ���������� ����
	STAGE_TYPE	CurrentStageKey;
	// �¿� ��ũ��
	float		ScrollX;
	//�������� ��ȯ�϶�� ����.
	bool		ChangeStage;
	// ���� ��ü�� ���� ũ���� �����ϸ� ��.
	int			ScrollMax;
	// true �������
	bool		Muzuk;

public:
	void AddObject(CObj* Obj, OBJ_TYPE Type);
	void AddObject(CObj* Obj, OBJ_TYPE Type,D3DXVECTOR3 Pos);
	void AddObject(CObj* Obj, OBJ_TYPE Type, D3DXVECTOR3 Pos, D3DXVECTOR3 Dir);
	void AddBackGround(CObj* Obj, OBJ_TYPE Type,float PosX, wstring Texturekey);

public:
	// ���浹. ����� �浹 ����� HP�� �ﵵ�� �ϵ��ڵ� �Ǿ� �ִ�.
	int CollisionSphere(CObj* Obj, OBJ_TYPE Type);
	// �浹�� ����� �ּҸ� ã�ƿ´�.
	CObj* GetObjToCollision(CObj* Obj, OBJ_TYPE Type);
	// �÷��̾��� �ּҸ� �����´�.
	CObj* GetPlayer();
public:
	HRESULT Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);

public:
	CObjMgr();
	~CObjMgr();
};

