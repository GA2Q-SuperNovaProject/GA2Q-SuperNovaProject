#pragma once
#include "StructDefine.h"

class Matrix2D
{
	//�⺻������ 3x3�� ��Ʈ������ �����Ѵ�. 
public:
	Matrix2D(); //�׳� �� 0���� ����� ������ �⺻ ������.
	Matrix2D(const Matrix2D& rhs); //�����ؼ� ��������.
	Matrix2D(float _list[9]);
	// 0 1 2
	// 3 4 5 
	// 6 7 8 ������ �� ���̴�.

	//Matrix���� ���ϴ� �����ε�.
	Matrix2D operator* (const Matrix2D& _other);
	//(3x3)�� (1x3)�� ���ϴ� �����ε�.
	friend AreaCount operator* (Matrix2D _first, AreaCount _second);

	Matrix2D Transpose(); //��ġ��� ����.
	//void Print(); 
	//���߿� DebugOutputString�� �����ؼ� �� ����, 
	//�ܼ� ���� ���� �Űܳ���.

	//��ȯ�� Transform ���� �����ϴ� 
	//�Լ�. Scale, Rotation���� �����Ų��.
	//�ٸ�, ���⼭ ����ؾ� �� �� -> Rotation�� ������ ���� �Ѵ�.
	//Transform���� �޾Ƽ� Transform�� �����ϵ�,
	//�̴� SetTransform�� ���̴� �ְ� �ƴϴ�.
	//�浹üũ�� ���� ���Ǵ� ��������.
	//�ʿ��� ������ ������ �����ϴ�,
	//Transform�� �ٸ� ������ ����� ��ȯ����.

	//VectorTwo���� ������,
	//2D Transformation Matrix�� �ۿ��� ���� ��ǥ���� ��ȯ.
	//Transform �ȿ�.
	AreaCount GetRow(int _index);
	AreaCount GetColumn(int _index);
private:
	float matrix[3][3];

};

//matrix[����][����].

//Translate�� ���� ������ �ʿ�X, ��ü������ �̵��� �� �ݿ��ϱ� ����.
//���� ��Ŀ� Scale�� �����ְ�, Rotation�� �����ָ� ���´�.
//Rotation�� 360���� ��������, Degree���̴�. �ٸ�, %360�ؾ� ����.

//No Translation, ��ġ �ʿ� X.

//�׷��ٸ� ������ ������� �ϴ°�?

//�ݶ��̴� ��길�� ���ؼ� ���Ǵ� Transform, 
//SetTransform�� ������ �ȵȴ�.
//Scale�� ��ȯ���� �ʴ´�.