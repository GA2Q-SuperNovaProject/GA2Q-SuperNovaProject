#pragma once

/// <summary>
/// 인터페이스
/// Update 및  Render의 최상위 인터페이스
/// 2023.02.07 [nadong]
/// </summary>
class IUpdatable
{
public:
	virtual void Update() abstract;
	virtual void Render() abstract;
};