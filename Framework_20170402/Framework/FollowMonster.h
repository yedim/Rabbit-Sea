#pragma once
#include "Obj.h"
class CFollowMonster :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CFollowMonster();
	virtual ~CFollowMonster();
};

