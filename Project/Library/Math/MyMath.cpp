#include "MyMath.h"
#include <math.h>

// �_P(x1, y1)����_Q(x2, y2)�܂ł̋�����Ԃ�
float MyMath::GetDistance(float x1, float y1, float x2, float y2)
{
	// �_P����_Q�܂ł̒������ΕӂƂ��钼�p�O�p�`�����A
	// �s�^�S���X�̒藝����Εӂ̒������v�Z����B
	// �@�܂��͒�ӂ̒������v�Z����
	float a = x2 - x1;

	// �A�������v�Z����
	float b = y2 - y1;

	// �B�Εӂ�2��̒l���v�Z����
	float double_c = a * a + b * b;

	// �C2��̒l�Ȃ̂ŕ��������v�Z���Ē����Ƃ���
	// �@��������<math.h>��sqrtf�֐��Ŏ擾�ł���
	return sqrtf(double_c);
}

// ��]�l��0�`2�΂̒l�ɂ���
float MyMath::RadianNormalize(float rad)
{
	float result = rad;
	if (result < 0.0f) {
		while (result < 0.0f) {
			result += DX_TWO_PI_F;
		}
	}
	else if (result > DX_TWO_PI_F) {
		while (result <= DX_TWO_PI_F) {
			result -= DX_TWO_PI_F;
		}
	}

	return result;
}
