#pragma once
#include <chrono>
#include <time.h>

//�׳� �׻� ������ ���� �ִٰ� ��������. 
//��׵��� ���� N�ʸ��� �ϳ��� �����Ѵ�.
class Timer
{
public:
	static Timer& GetInstance()
	{
		static Timer inst;
		return inst;
	}
	uint64_t counterFive = 0;
	uint64_t counterTen = 0;
	uint64_t counterOne = 0;
};


