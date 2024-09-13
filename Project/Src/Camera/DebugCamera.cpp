#include "DebugCamera.h"
#include "Camera.h"
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"

//�J�����������֐�
void DebugCamera::Init(void)
{
	// �J�����̐ݒ�
	SetCameraNearFar(1.0f, 27000.0f);

	SetupCamera_Perspective(MY_MATH::PI_OVER_THREE);

	pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };		//�J�����ʒu
	target_ = { 0.0f, 100.0f, 0.0f };										//�����_
	up_ = { 0.0f, 1.0f, 0.0f };												//�����
	rot_ = { MY_MATH::PI_OVER_SIX, 0.0f, 0.0f };							//�J�����p�x

	dir_ = { 0.0f,0.0f,1.0f };

	//�J�����ʒu�ݒ�
	SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

}

//�J�����s�������֐�
void DebugCamera::Step(const Vector3D& playerPos)
{
	//�J�����̏ꏊ�ݒ�

	//���V�t�g�L�[�������Ă���Ɖ���
	float speed = InputKeyBoard::IsKeyDown(KEY::L_SHIFT) ? CAMERA::FAST_SPEED : CAMERA::SPEED;
	Vector3D cameraSpeed = { speed * sinf(rot_.y),0.0f,speed * cosf(rot_.y) };

	//�㏸
	if (InputKeyBoard::IsKeyDown(KEY::Q))
	{
		pos_.y -= speed;
		target_.y -= speed;
	}

	//���~
	if (InputKeyBoard::IsKeyDown(KEY::E))
	{
		pos_.y += speed;
		target_.y += speed;
	}

	//�O�ړ�
	if (InputKeyBoard::IsKeyDown(KEY::W))
	{
		pos_ = pos_ + cameraSpeed;
		target_ = target_ + cameraSpeed;
	}
	//��ړ�
	if (InputKeyBoard::IsKeyDown(KEY::S))
	{
		pos_ = pos_ - cameraSpeed;
		target_ = target_ - cameraSpeed;
	}

	//���V�t�g�L�[�������Ă���Ɖ���
	//���E�ɐ����ړ�����̂� ��/2 ����
	float left_right_speed = InputKeyBoard::IsKeyDown(KEY::L_SHIFT) ? CAMERA::FAST_SPEED : CAMERA::SPEED;
	Vector3D left_right_cameraSpeed = { left_right_speed * sinf(rot_.y + MY_MATH::HALF_PI),0.0f,left_right_speed * cosf(rot_.y + MY_MATH::HALF_PI) };

	//���ړ�
	if (InputKeyBoard::IsKeyDown(KEY::A))
	{
		//���Ȃ̂ō��Ɉړ�
		pos_ -= left_right_cameraSpeed;
		target_ -= left_right_cameraSpeed;
	}
	//�E�ړ�
	if (InputKeyBoard::IsKeyDown(KEY::D))
	{
		//�a�Ȃ̂ŉE�Ɉړ�
		pos_ += left_right_cameraSpeed;
		target_ += left_right_cameraSpeed;
	}


	// �E��]
	if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
	{
		rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_�̍��E�̊p�x�Ƃ̒�`��� -2�� < �� <= 2��
		if (rot_.y <= -DX_PI_F)
		{
			rot_.y = 0.0f;
		}

	}

	// ����]
	if (InputKeyBoard::IsKeyDown(KEY::LEFT))
	{
		rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_�̍��E�̊p�x�Ƃ̒�`��� -2�� <= �� < 2��
		if (rot_.y >= DX_PI_F)
		{
			rot_.y = 0.0f;
		}

	}

	//���]
	if (InputKeyBoard::IsKeyDown(KEY::UP))
	{
		// rot_�̏㉺�̊p�x�Ƃ̒�`��� (-��/2) + ��/100 <= �� <= (��/2) - ��/100
		if (rot_.x > -MY_MATH::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;
		}
	}

	//����]
	if (InputKeyBoard::IsKeyDown(KEY::DOWN))
	{
		// rot_�̏㉺�̊p�x�Ƃ̒�`��́@(��/2) + ��/100 <= �� <= (��/2) - ��/100
		if (rot_.x < MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x += CAMERA::ROT_UP_DOWN_SPEED;
		}

	}

	// �E��]
	if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
	{
		rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_�̍��E�̊p�x�Ƃ̒�`��� -2�� < �� <= 2��
		if (rot_.y <= -MY_MATH::PI)
		{
			rot_.y = 0.0f;
		}

	}

	// ����]
	if (InputKeyBoard::IsKeyDown(KEY::LEFT))
	{
		rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_�̍��E�̊p�x�Ƃ̒�`��� -2�� <= �� < 2��
		if (rot_.y >= MY_MATH::PI)
		{
			rot_.y = 0.0f;
		}

	}
}

//�J�����X�V�֐�
void DebugCamera::UpDate(void)
{
	//�s��ɂ��J�����ʒu�v�Z
	Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
		* Matrix3D::GetYawMatrix(rot_.y)
		* Matrix3D::GetPitchMatrix(rot_.x)
		* Matrix3D::GetTranslateMatrix(-target_);

	pos_ = RetCameraMat * target_;

	//
	dir_ = Matrix3D::GetYawMatrix(rot_.y) * dir_;

	//�J�����ʒu�ݒ�
	SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);
}
