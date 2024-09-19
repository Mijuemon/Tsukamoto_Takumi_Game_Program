#pragma once

#include "DxLib.h"
#include <math.h>

//�񎟌��̎�����̃x�N�g���N���X
class Vector2D
{
public:
	//�����o�ϐ�
	float x, y;

	constexpr Vector2D() noexcept : x(0.0f), y(0.0f) {}
	explicit constexpr Vector2D(float initNum) noexcept : x(initNum), y(initNum) {}
	constexpr Vector2D(float init_x, float init_y) noexcept : x(init_x), y(init_y) {}
	constexpr Vector2D(const Vector2D& vec) noexcept : x(vec.x), y(vec.y) {}
	constexpr Vector2D(const VECTOR& vec) noexcept : x(vec.x), y(vec.y) {}

	//�����ɓ��͂����l���擾����֐�(x = value_x, y = value_y)
	inline constexpr Vector2D VGet(float value_x, float value_y) { this->x = value_x, this->y = value_y; return *this; }
	//�����ɓ��͂����l���擾����֐�(x = y = value)
	inline constexpr Vector2D VGet(float value) { this->x = value, this->y = value; return *this; }
	//�����ɓ��͂����l���擾����֐�(x = vec.x, y = vec.y)
	inline constexpr Vector2D VGet(const Vector2D& vec) { this->x = vec.x, this->y = vec.y; return *this; }

	//Vector2D�̉��Z�̒�`
	inline Vector2D operator+(const Vector2D& vec) const { this->x + vec.x, this->y + vec.y; return *this; }

	//Vector2D�̉��Z����̒�`
	inline Vector2D operator+=(const Vector2D& vec) { return *this = *this + vec; }

	//Vector2D�̌��Z�̒�`
	inline Vector2D operator-(const Vector2D& vec) const { this->x - vec.x, this->y - vec.y; return *this; }

	//Vector2D�̌��Z����̒�`
	inline Vector2D operator-=(const Vector2D& vec) { return *this = *this - vec; }

	//Vector2D�̃X�J���[�{�̒�`
	inline Vector2D operator*(float scale) const { return Vector2D(this->x * scale, this->y * scale); }

	inline Vector2D operator*(const Vector2D& vec) const { this->x* vec.x, this->y* vec.y; return *this; }

	//Vector2D�̃X�J���[�{����̒�`
	inline Vector2D operator*=(float scale) { return *this = *this * scale; }

	inline Vector2D operator*=(const Vector2D& vec) { return *this = *this * vec; }

	//Vector2D�̏��Z�̒�`
	inline Vector2D operator/(const Vector2D& vec) const { this->x / vec.x, this->y / vec.y; return *this; }

	//Vector2D�̏��Z����̒�`
	inline Vector2D operator/=(const Vector2D& vec) { return *this = *this / vec; }

	//Vector2D�̑���̒�`
	inline Vector2D operator=(const Vector2D& vec) { this->x = vec.x, this->y = vec.y; return *this; }

	//����x�N�g������
	inline bool operator==(const Vector2D& vec) const { return (x == vec.x && y == vec.y); }
	inline bool operator!=(const Vector2D& vec) const { return !(*this == vec); }

	//DX���C�u�����̃x�N�g���\���̂ւ̃L���X�g���Z�q
	inline operator VECTOR() const { return VECTOR{ (float)x,(float)y,0.0f }; }

	//�n�_�I�_�x�N�g���쐬
	Vector2D VecCreate(const Vector2D& start, const Vector2D& end);

	//�x�N�g���a
	Vector2D VecAdd(const Vector2D& vec1, const Vector2D& vec2);

	//L2�m����
	inline float VecL2Norm(const Vector2D& vec);

	//�P�ʃx�N�g���쐬
	Vector2D Normalize(const Vector2D& vec);

	//�P�ʃx�N�g�����쐬���X�J���[�{
	Vector2D VecNormalizeAndScalartimes(const Vector2D& vec, float scale);

	//�x�N�g�����쐬���P�ʃx�N�g���ɂ��ăX�J���[�{
	Vector2D VecNormalizeAndScalartimes(const Vector2D& start, const Vector2D& end, float scale);

	//�x�N�g���̃X�J���[�{
	Vector2D VecScalartimes(const Vector2D& vec, float scale);

	//����
	inline float VecDot(const Vector2D& vec1, const Vector2D& vec2);

	//�x�N�g���̊p�x�Ƃ��擾
	inline float VecDir(const Vector2D& vec);
};
