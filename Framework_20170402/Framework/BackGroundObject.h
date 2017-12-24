#pragma once
#include "Obj.h"
class CBackGroundObject :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CBackGroundObject();
	virtual ~CBackGroundObject();
};

