#pragma once

/// <summary>
/// �������̽�
/// Update ��  Render�� �ֻ��� �������̽�
/// 2023.02.07 [nadong]
/// </summary>
class IUpdatable
{
public:
	virtual void Update() abstract;
	virtual void Render() abstract;
};