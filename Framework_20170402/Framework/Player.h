#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	//키가 연속으로 눌러지는 것을 방지하기 위한 변수.
	float BulletTimer;
	bool PressKey;

	//플레이어 현재 강화 단계 2단계가 3발
	int	 PlayerUpgrade;

	//무적 시간체크를 위한 변수
	float UnbeatableTime; 

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	void CollisionCheck();
	void KeyCheck();

public:
	CPlayer();
	virtual ~CPlayer();
};

