#include "Matrix2D.h"

Matrix2D::Matrix2D() //�⺻ ������, 0�ʱ�ȭ.
{
	for (int i = 0; i < 3; i++) //���� 
	{
		for (int j = 0; j < 3; j++) //���� 
		{
			matrix[j][i] = 0.f;
		}
	}
}

Matrix2D::Matrix2D(const Matrix2D& rhs) // ���� ������
{
	for (int i = 0; i < 3; i++) //���� 
	{
		for (int j = 0; j < 3; j++) //���� 
		{
			matrix[j][i] = rhs.matrix[j][i];
		}
	}
}

Matrix2D::Matrix2D(float _list[9])
{
	int _index = 0;
	for (int i = 0; i < 3; i++) //���� 
	{
		for (int j = 0; j < 3; j++) //���� 
		{
			matrix[j][i] = _list[_index];
			_index++;
		}
	}
}

//�� ������ ���� ��� �� ���� �ϼ�����
Matrix2D Matrix2D::operator*(const Matrix2D& _other)
{
	Matrix2D mulMatrix;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				mulMatrix.matrix[i][j] += _other.matrix[i][k] * this->matrix[k][j];
			} //other�� ����!
		}
	}
	return mulMatrix;
}

Matrix2D Matrix2D::Transpose() //�ڽ��� ��ġ����� ��ȯ�Ѵ�. (�ڽ� ���� X) 
{
	Matrix2D trMatrix;
	for (int i = 0; i < 3; i++) //���� 
	{
		for (int j = 0; j < 3; j++) //���� 
		{
			trMatrix.matrix[i][j] = matrix[j][i];
		}
	}
	return trMatrix;
}

AreaCount Matrix2D::GetRow(int _index)
{
	AreaCount tmpRow;
	tmpRow.area[0] = this->matrix[_index][0];
	tmpRow.area[1] = this->matrix[_index][1];
	tmpRow.area[2] = this->matrix[_index][2];
	return tmpRow;
}

AreaCount Matrix2D::GetColumn(int _index)
{
	AreaCount tmpColumn;
	tmpColumn.area[0] = this->matrix[0][_index];
	tmpColumn.area[1] = this->matrix[1][_index];
	tmpColumn.area[2] = this->matrix[2][_index];
	return tmpColumn;
}

//void Matrix2D::Print()
//{
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++) 
//		{
//			std::cout << matrix[j][i] << " ";
//		}
//		std::cout << std::endl;
//	}
//}

//

AreaCount operator* (Matrix2D _first, AreaCount _second)
{
	//���⼭ AreaCount�� ����1, ����3�� �����Ǿ� �ִ�.
	AreaCount toReturn;
	toReturn.area[0] = _first.matrix[0][0] * _second.area[0] + _first.matrix[0][1] * _second.area[1] + _first.matrix[0][2] * _second.area[2];

	toReturn.area[1] = _first.matrix[1][0] * _second.area[0] + _first.matrix[1][1] * _second.area[1] + _first.matrix[1][2] * _second.area[2];

	toReturn.area[2] = _first.matrix[2][0] * _second.area[0] + _first.matrix[2][1] * _second.area[1] + _first.matrix[2][2] * _second.area[2];

	return toReturn;
}