#pragma	once
#include "Vec2.h" //이 .은 무엇을 할까..
#include "Body.h"

class Transform;
class GameObject;

//Force쓸때 주의, 
struct Force
{ 
public:
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	static Vec2 AddDragForce(GameObject* gameObject, float k); //항력
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	static Vec2 AddFrictionForce(GameObject* gameObject, float k); //마찰력
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	//otherObject 방향으로 끌려간다!
	static Vec2 AddGravityForce(GameObject* gameObject, GameObject* otherObject, float G, float minDistance, float maxDistance); //Gravitational, 그냥 중력X.
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	static Vec2 AddSpringForce(GameObject* gameObject, const Vec2& anchor, float restLength, float k);

private:
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	static Vec2 AddDragForceWithBody(const Body* body, Transform* bodyTransform, float k);
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	static Vec2 AddFrictionForceWithBody(const Body* body, Transform* bodyTransform, float k);
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	static Vec2 AddGravityForceWithBody(const Body* a, Vec2 aPos, const Body* b, Vec2 bPos, float G, float minDistance, float maxDistance);
	//주의: 넣을 때 Local/World 다르게 넣으려면 같아야 한다!!!
	static Vec2 AddSpringForceWithBody(const Body* p, Transform* bodyTransform, const Vec2& anchor, float restLength, float k);
};

