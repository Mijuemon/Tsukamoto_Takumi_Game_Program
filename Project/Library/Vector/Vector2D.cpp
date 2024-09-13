#include "Vector2D.h"

// �n�_�ƏI�_����x�N�g�����쐬
Vector2D Vector2D::VecCreate(const Vector2D& start, const Vector2D& end)
{
	//�I�_ - �n�_
	return Vector2D(end.x - start.x, end.y - start.y);
}

// �x�N�g���̑����Z
Vector2D Vector2D::VecAdd(const Vector2D& vec1, const Vector2D& vec2)
{
	//�e���������Z
	return Vector2D(vec1.x + vec2.x, vec1.y + vec2.y);
}

//L2�m����
float Vector2D::VecL2Norm(const Vector2D& vec)
{
	// ||vec||_2 = ��(|vec.x|^2 + |vec.y|^2)
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

//�P�ʃx�N�g���쐬
Vector2D Vector2D::Normalize(const Vector2D& vec)
{
	Vector2D result;

	//�x�N�g���̒��������߂�
	float vec_norm = VecL2Norm(vec);

	//�e�����𒷂��Ŋ��萳�K������
	result.x = vec.x / vec_norm;
	result.y = vec.y / vec_norm;

	return result;
}

//�P�ʃx�N�g�����쐬���X�J���[�{
Vector2D Vector2D::VecNormalizeAndScalartimes(const Vector2D& vec, float scale)
{
	float vec_norm = VecL2Norm(vec);

	return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
}

//�x�N�g�����쐬���P�ʃx�N�g���ɂ��ăX�J���[�{
Vector2D Vector2D::VecNormalizeAndScalartimes(const Vector2D& start, const Vector2D& end, float scale)
{
	Vector2D vec;

	vec.x = end.x - start.x;
	vec.y = end.y - start.y;

	float vec_norm = VecL2Norm(vec);

	return { (vec.x / vec_norm) * scale, (vec.y / vec_norm) * scale };
}

// �x�N�g���̃X�J���[�{
Vector2D Vector2D::VecScalartimes(const Vector2D& vec, float scale)
{
	//�e�������X�J���[�{
	return Vector2D(vec.x * scale, vec.y * scale);
}

// �x�N�g���̓���
float Vector2D::VecDot(const Vector2D& vec1, const Vector2D& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

// �x�N�g���̌��������W�A���p�Ŏ擾
float Vector2D::VecDir(const Vector2D& vec)
{
	return atan2f(vec.y, vec.x);
}
