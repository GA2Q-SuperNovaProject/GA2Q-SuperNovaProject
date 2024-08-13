#pragma once
#include "Vec2.h"
class Transform
{
public:
	Transform(Vec2 position, float rotation, Vec2 scale); //Collider는 자동적으로 설정된다.
	virtual ~Transform();

	Vec2 GetPosition() const { return m_Position; }
	void SetPosition(Vec2 val) { m_Position = val; }

	//[TW] 자동으로 360도로 나눠서 리턴.
	float GetRotation() const;
	void SetRotation(float val) { m_Rotation = val; }

	Vec2 GetScale() const { return m_Scale; }
	void SetScale(Vec2 val) { m_Scale = val; }

	/// Get-Setter가 있으면서 왜 Value를 Public으로 노출?
	/// -> L-Value, R-Value 구분 사용 위해 [TW]
	Vec2 m_Position;
	float m_Rotation;
	Vec2 m_Scale; //[TW] 웬만하면 Circle형 물체 사용시, Scale의 x,y를 같게 할 것. Rect는 상관X.

private:
	
};

/// [TW] 이제부터 바뀔 체제:
/// Transform에 m_position이 생길 것이고, 
/// GameObject에서 m_Position이 들어갔던 원래 위치는 Transform으로 대체될 것.
/// GameObject는 내부적으로 생성자에서 동적할당된 Transform을 갖고 있으며, (포인터)
///  내부적으로 자신의 생성자에서 동적 할당된 Collider를 갖고 있다.
/// 당연히, GameObject가 어떤 모양인지 받을 필요도 있고 (eColType 지정).

/// 이를 자연스럽게 오가는 체제까지 완성 후,
/// 씬 단위 옵젝 찾기/Instantiate 들어갈 것.
/// 
/// 나중에 Transform 위주로 Position도 바꾸어야!

///출력은 D2D SetTransform 활용, 충돌처리 위해서 이는 후에 바뀜.
///
