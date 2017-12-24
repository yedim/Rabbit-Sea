#pragma once

#include "Defines.h"

class CMouse
{
public:
	static POINT	MousePos;

public:
	static void SetMousePos()
	{
		//윈도우에서 좌표를 받아오는 함수
		GetCursorPos(&MousePos);

		//OS 절대 좌표에서 클라이언트 기준으로 좌표를 변환해준다.
		ScreenToClient(g_hWnd, &MousePos);
	}
	static POINT GetMousePos()
	{
		return MousePos;
	}
public:
	CMouse();
	~CMouse();
};

