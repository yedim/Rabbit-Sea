#pragma once
#include "Obj.h"
class CBossMonster :
	public CObj
{
public:
	// 움직임을 제어 하는 변수들
	float	MoveTime;
	float	AttTime;
	int		AttCount;

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CBossMonster();
	virtual ~CBossMonster();
};

