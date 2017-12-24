#pragma once

#include "Defines.h"
#include "Single.h"

class CObj;
class CObjMgr
	: public CSingle<CObjMgr>
{
public:
	// 전체 오브젝트를 관리하는 리스트
	list<CObj*>	ObjList[OBJ_MAX];
	// 현재 스테이지를 저장
	STAGE_TYPE	CurrentStageKey;
	// 좌우 스크롤
	float		ScrollX;
	//스테이지 전환하라는 변수.
	bool		ChangeStage;
	// 게임 전체의 가로 크기라고 생각하면 됨.
	int			ScrollMax;
	// true 무적모드
	bool		Muzuk;

public:
	void AddObject(CObj* Obj, OBJ_TYPE Type);
	void AddObject(CObj* Obj, OBJ_TYPE Type,D3DXVECTOR3 Pos);
	void AddObject(CObj* Obj, OBJ_TYPE Type, D3DXVECTOR3 Pos, D3DXVECTOR3 Dir);
	void AddBackGround(CObj* Obj, OBJ_TYPE Type,float PosX, wstring Texturekey);

public:
	// 구충돌. 현재는 충돌 대상의 HP를 깍도록 하드코딩 되어 있다.
	int CollisionSphere(CObj* Obj, OBJ_TYPE Type);
	// 충돌한 대상의 주소를 찾아온다.
	CObj* GetObjToCollision(CObj* Obj, OBJ_TYPE Type);
	// 플레이어의 주소를 가져온다.
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

