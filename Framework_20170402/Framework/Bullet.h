#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CBullet();
	virtual ~CBullet();
};

