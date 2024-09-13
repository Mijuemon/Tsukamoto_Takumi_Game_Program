#pragma once

#include "Vector/Vector2D.h"
#include "Vector/Vector3D.h"

//���w�Ŏg���萔
namespace MY_MATH
{
	//2��
	constexpr float TWO_PI = 6.283185307179586476925286766559f;

	//��
	constexpr float PI = 3.1415926535897932384626433832795f;

	//1/(2��)
	constexpr float INVERSE_TWO_PI = 1.0f / TWO_PI;

	//1/��
	constexpr float INVERSE_PI = 1.0f / PI;

	//�[���x�N�g��
	constexpr Vector2D ZERO_VECTOR_2D = { 0.0f,0.0f };

	//�[���x�N�g��
	constexpr Vector3D ZERO_VECTOR_3D = { 0.0f,0.0f,0.0f };

	//4��/3
	constexpr float FOUR_PI_OVER_THREE = 1.3333333333333333333333333333333f * PI;

	//��/2
	constexpr float HALF_PI = 0.5f * PI;

	//��/3
	constexpr float PI_OVER_THREE = 0.3333333333333333333333333333333f * PI;

	//��/4
	constexpr float PI_OVER_FOUR = 0.25f * PI;

	//��/6
	constexpr float PI_OVER_SIX = 0.1666666666666666666666666666666f * PI;

	//��/8
	constexpr float PI_OVER_EIGHT = 0.125f * PI;

	//��/10
	constexpr float PI_OVER_TEN = 0.1f * PI;

	//��/20
	constexpr float PI_OVER_TWENTY = 0.05f * PI;

	//���W�A���p�ɕϊ�����Ƃ��Ɏg���萔
	constexpr float RADIAN_CONVERT_COEFFICIENT = PI / 180.0f;
}

//���w�N���X
class MyMath
{
public:
	template<class T>
	static inline T Abs(const T num)
	{
		return num >= (T)0 ? num : -num;
	}

	//�����v�Z
	static float GetDistance(float x1, float y1, float x2, float y2);

	//���W�A���p��
	static float RadianNormalize(float rad);

	//�f�B�O���[���烉�W�A���ɂ���
	static constexpr float DegreesToRadian(float degrees)
	{
		return degrees * MY_MATH::RADIAN_CONVERT_COEFFICIENT;
	}

	//�f�B�O���[���烉�W�A���ɂ���
	static constexpr float DegreesToRadian(int degrees)
	{
		return static_cast<float>(degrees * MY_MATH::RADIAN_CONVERT_COEFFICIENT);
	}
};
