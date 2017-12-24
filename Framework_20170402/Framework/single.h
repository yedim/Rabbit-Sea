#pragma once

template <typename T>
class CSingle
{
private:
	static	T*		m_pInst;

public:
	static T* GetInst(void)
	{
		//처음 GetInst함수 호출시에는 m_pInst가 NULL인 상태이다.
		//그래서 아래 코드를 만나 할당한다.
		//그 다음 호출 될때는 이미 할당된 m_pInst를 리턴만 해간다.
		//즉 한번만 만들어지고 같은 변수를 가져간다는 것.
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

//스테틱 변수 초기화 - 템플릿 클래스인 경우에 이처럼 표기한다.
template <typename T>
T* CSingle<T>::m_pInst = NULL;