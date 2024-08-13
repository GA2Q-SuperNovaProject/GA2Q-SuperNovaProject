#pragma once
#include "StructDefine.h"

class Matrix2D
{
	//기본적으로 3x3의 매트릭스를 형성한다. 
public:
	Matrix2D(); //그냥 다 0으로 만들어 버리는 기본 생성자.
	Matrix2D(const Matrix2D& rhs); //복사해서 가져오기.
	Matrix2D(float _list[9]);
	// 0 1 2
	// 3 4 5 
	// 6 7 8 순서로 들어갈 것이다.

	//Matrix끼리 곱하는 오버로드.
	Matrix2D operator* (const Matrix2D& _other);
	//(3x3)과 (1x3)을 곱하는 오버로드.
	friend AreaCount operator* (Matrix2D _first, AreaCount _second);

	Matrix2D Transpose(); //전치행렬 리턴.
	//void Print(); 
	//나중에 DebugOutputString과 결합해서 쓸 수도, 
	//콘솔 구현 버전 옮겨놓기.

	//변환된 Transform 값을 리턴하는 
	//함수. Scale, Rotation만을 적용시킨다.
	//다만, 여기서 고려해야 할 점 -> Rotation의 정도를 봐야 한다.
	//Transform값을 받아서 Transform을 리턴하되,
	//이는 SetTransform에 쓰이는 애가 아니다.
	//충돌체크를 위해 사용되는 버전으로.
	//필요한 정보만 가지고 리턴하는,
	//Transform의 다른 버전을 만들어 반환하자.

	//VectorTwo값을 받으면,
	//2D Transformation Matrix의 작용을 받은 좌표값을 반환.
	//Transform 안에.
	AreaCount GetRow(int _index);
	AreaCount GetColumn(int _index);
private:
	float matrix[3][3];

};

//matrix[세로][가로].

//Translate는 따로 구현할 필요X, 자체적으로 이동할 때 반영하기 때문.
//원본 행렬에 Scale을 곱해주고, Rotation을 곱해주면 나온다.
//Rotation은 360도를 기준으로, Degree값이다. 다만, %360해야 최적.

//No Translation, 전치 필요 X.

//그렇다면 무엇을 곱해줘야 하는가?

//콜라이더 계산만을 위해서 사용되는 Transform, 
//SetTransform에 넣으면 안된다.
//Scale이 반환되지 않는다.