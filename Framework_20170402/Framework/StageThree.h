#pragma once
#include "Stage.h"
class CStageThree :
	public CStage
{
public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CStageThree();
	virtual ~CStageThree();
};

