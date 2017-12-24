#pragma once
#include "Obj.h"
class CMenuButton :
	public CObj
{
public:
	int Width;
	int Height;
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMenuButton();
	virtual ~CMenuButton();
};

