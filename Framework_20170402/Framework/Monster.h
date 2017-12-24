#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	float	MoveTime;

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMonster();
	virtual ~CMonster();
};

