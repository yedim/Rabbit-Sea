#pragma once

#include "Defines.h"

class CMouse
{
public:
	static POINT	MousePos;

public:
	static void SetMousePos()
	{
		//�����쿡�� ��ǥ�� �޾ƿ��� �Լ�
		GetCursorPos(&MousePos);

		//OS ���� ��ǥ���� Ŭ���̾�Ʈ �������� ��ǥ�� ��ȯ���ش�.
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

