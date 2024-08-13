#pragma once
#include <windows.h>

//[TW] FixedRate
const float FPS = 60.0f;
const int MILLISECS_PER_FRAME = 1000 / FPS;
const float FIXED_FPS = 1.0f / FPS;

const int PIXELS_PER_METER = 50;

class TimeManager
{
public:
	//Ÿ�� �Ŵ��� �̱������� ����
	static TimeManager& GetInstance()
	{
		static TimeManager inst;
		return inst;
	}

	void Initialize();
	void StartCheckTime();
	void EndCheckTime();
	float GetDeltaTime();

private:
	TimeManager();
	~TimeManager();

	float m_deltaTime;	// ��Ÿ Ÿ��

	// �� �̵��� * 1/�����Ӽ� = �ѹ��� �̵��ؾ��ϴ� ��
	// FPS�� ���ϰ�
	// 1 �����Ӵ� �ð� �� ���� �� ������ 
	// DeltaTime�� ���� �� �ִ�
	// DeltaTime�� Ÿ�ӸŴ������� ��� ���ؾ��Ѵ�
	LARGE_INTEGER	m_llCurCount;
	LARGE_INTEGER	m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;
	double			m_dDT;		 // DeltaTime (0) ������ ������ �ð���
	double			m_dAcc;		 // (0) 1�� üũ�� ���� ���� �ð�
	UINT			m_iCallCount;// (0) �Լ� ȣ�� Ƚ�� üũ
	UINT			m_iFPS;		 // �ʴ� ȣ�� Ƚ�� üũ

	// ���� ��Ƽ���� ���� ����-> ���������ս� ī���ͳ� ���������ս� �������� ����
	// �Լ��� ����ϱ� ���ؼ��� ũ�Ⱑ ū �������� �ʿ�
	// ��? �� �ڼ��� �ð����� �����ϱ� ���ؼ�
	// ��ȣ�� �ִ� 64��Ʈ ������ �����͸� �����ϱ� ���� ����� ����� ���� �ڷ���


};

