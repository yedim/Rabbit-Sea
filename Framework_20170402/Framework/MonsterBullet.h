#pragma once
#include "Obj.h"
class CMonsterBullet :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMonsterBullet();
	virtual ~CMonsterBullet();
};

