#pragma once
#include <vector>

/// [TW] ���� Ÿ�� �� ���� ��ó��, �ִ� �ο��� �Ѿ�ٸ� �ڵ����� ���� ���� ������� �ĳ���.
/// Ex. �ִ� �� �� �� �ִ� �ο��� 2���̶�� ����. 0���� �ϳ��� �þ�鼭 ����.
// [ ] [ ]  // [0] [ ] // [1] [0] // [2] [1] // �� �̷��� �þ.
/// 
/// ���ø��� �׳� ���� �ڷ����� �����Ӱ� �ϱ� ����. 
/// ex, �ִ� ũ�Ⱑ 5���� bool���� ��� ���� ť�� ���� �ʹ�? FixedQueue<bool> ex(5);

/// FixedQueue<���� ���� Ÿ��> �̸� (�ִ� ũ��)
//�̷��� �����ָ� �ȴ�.

template <typename T>
class FixedQueue //Ư�� ũ�Ⱑ �Ǹ�, ���Ŀ� ������ �μ����� �޾Ƶ��̰� �� ó���� ���Դ� ������� ��.  
{
public:
	FixedQueue(int queueSize);
	~FixedQueue();

	void Enqueue(T content); //�׳� �ִ� ����. ���� �ִ� �ױ�
	T ContentOfIndex(int index); //�ε��� �� ���� ��ȯ.

private:
	std::vector<T> m_InnerQueue; //ContentOfIndex()�� ���ؼ��� �������� �迭ó�� ���� �����ϴ�.
	int maxSize; // == �ִ� ũ��, ť�� ���� �� ũ�⸦ �Ѿ �� ����.
	int totalCnt; // == ���� ũ��.
};

//ť�� �ִ��� �þ �� �ִ� ũ�⸦ �Ű�������.
template <typename T>
FixedQueue<T>::FixedQueue(int queueSize)
	: maxSize(queueSize), totalCnt(0)
{

}

//MaxSize���� �ϳ� ���� �Ű������� ����, ������ ����!
template <typename T>
T FixedQueue<T>::ContentOfIndex(int index)
{
	return m_InnerQueue[maxSize - index - 1];
}

//���� Ÿ�� �� ���� ��ó��, �ִ� �ο��� �Ѿ�ٸ� �ڵ����� ���� ���� ������� �ĳ���.
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
