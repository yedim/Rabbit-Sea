#pragma once

template <typename T>
class CSingle
{
private:
	static	T*		m_pInst;

public:
	static T* GetInst(void)
	{
		//ó�� GetInst�Լ� ȣ��ÿ��� m_pInst�� NULL�� �����̴�.
		//�׷��� �Ʒ� �ڵ带 ���� �Ҵ��Ѵ�.
		//�� ���� ȣ�� �ɶ��� �̹� �Ҵ�� m_pInst�� ���ϸ� �ذ���.
		//�� �ѹ��� ��������� ���� ������ �������ٴ� ��.
		if(m_pInst == NULL)
			m_pInst = new T;

		return m_pInst;
	}

	void DestoryInst(void)
	{
		delete m_pInst;
		m_pInst = NULL;
	}

public:
	CSingle(void) {};

public:
	~CSingle(void) {};
};

//����ƽ ���� �ʱ�ȭ - ���ø� Ŭ������ ��쿡 ��ó�� ǥ���Ѵ�.
template <typename T>
T* CSingle<T>::m_pInst = NULL;