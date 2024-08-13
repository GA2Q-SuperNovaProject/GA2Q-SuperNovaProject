#pragma once
#include <vector>

/// [TW] 버스 타러 줄 서는 것처럼, 최대 인원을 넘어선다면 자동으로 먼저 들어온 순서대로 쳐낸다.
/// Ex. 최대 줄 설 수 있는 인원이 2명이라고 하자. 0부터 하나씩 늘어나면서 들어옴.
// [ ] [ ]  // [0] [ ] // [1] [0] // [2] [1] // 뭐 이렇게 늘어남.
/// 
/// 템플릿은 그냥 쓰는 자료형을 자유롭게 하기 위해. 
/// ex, 최대 크기가 5개인 bool형을 담는 정적 큐를 쓰고 싶다? FixedQueue<bool> ex(5);

/// FixedQueue<쓰고 싶은 타입> 이름 (최대 크기)
//이렇게 적어주면 된다.

template <typename T>
class FixedQueue //특정 크기가 되면, 이후에 들어오는 인수들을 받아들이고 맨 처음에 들어왔던 순서대로 컷.  
{
public:
	FixedQueue(int queueSize);
	~FixedQueue();

	void Enqueue(T content); //그냥 넣는 역할. 절대 최대 그기
	T ContentOfIndex(int index); //인덱스 별 내용 반환.

private:
	std::vector<T> m_InnerQueue; //ContentOfIndex()를 통해서만 정상적인 배열처럼 접근 가능하다.
	int maxSize; // == 최대 크기, 큐는 절대 이 크기를 넘어설 수 없다.
	int totalCnt; // == 현재 크기.
};

//큐가 최대한 늘어날 수 있는 크기를 매개변수로.
template <typename T>
FixedQueue<T>::FixedQueue(int queueSize)
	: maxSize(queueSize), totalCnt(0)
{

}

//MaxSize보다 하나 작은 매개변수만 수용, 나머지 뻑남!
template <typename T>
T FixedQueue<T>::ContentOfIndex(int index)
{
	return m_InnerQueue[maxSize - index - 1];
}

//버스 타러 줄 서는 것처럼, 최대 인원을 넘어선다면 자동으로 먼저 들어온 순서대로 쳐낸다.
template <typename T>
void FixedQueue<T>::Enqueue(T content)
{
	if (totalCnt < maxSize)
	{
		m_InnerQueue.push_back(content);
		totalCnt++;
	}
	else
	{
		m_InnerQueue.erase(m_InnerQueue.begin());
		m_InnerQueue.push_back(content);
	}

}

template <typename T>
FixedQueue<T>::~FixedQueue()
{
	//
}
