#include "DxLib.h"
#include "Camera.h"
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"
#include "Player/Player.h"
#include <math.h>
#include <Effekseer/Effekseer.h>
#include <Input/GamePad/GamePad.h>
#include <Input/Mouse/Mouse.h>
#include <Input/Input.h>
#include <Common.h>


//�J�����������֐�
void Camera::Init(void)
{
	// �J�����̐ݒ�
	SetCameraNearFar(1.0f, 27000.0f);

	SetupCamera_Perspective(MY_MATH::PI_OVER_THREE);

	pos_ = { 0.0f, CAMERA::POS_Y_DISTANCE, CAMERA::POS_Z_DISTANCE };	//�J�����ʒu
	target_ = { 0.0f, 0.0f, 0.0f };												//�����_
	up_ = { 0.0f, 1.0f, 0.0f };												//�����
	rot_ = { MY_MATH::PI_OVER_SIX, 0.0f, 0.0f };						//�J�����p�x

	dir_ = { 0.0f,0.0f,1.0f };

	distanceToPlayer_ = CAMERA::POS_Z_DISTANCE;

	//�J�����ʒu�ݒ�
	SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

}

//�J�����s�������֐�
void Camera::Step(const Vector3D& playerPos)
{
	//�J�����̑Ώە�
	target_ = playerPos;

	if (Input::IsKeyKeep(GAME_INPUT::TURBO))
	{
		//�J�������������ő�̋����ɂ���
		distanceToPlayer_ = CAMERA::MAX_DISTANCE;

		// ����]
		if (InputKeyBoard::IsKeyDown(KEY::LEFT))
		{
			rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_�̍��E�̊p�x�Ƃ̒�`��� -�� < �� <= ��
			if (rot_.y < -MY_MATH::PI)
			{
				rot_.y = MY_MATH::PI;
			}

		}

		// �E��]
		if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
		{
			rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

			// rot_�̍��E�̊p�x�Ƃ̒�`��� -�� <= �� < ��
			if (rot_.y > MY_MATH::PI)
			{
				rot_.y = -MY_MATH::PI;
			}

		}

		return;
	}

	//�v���C���[�̈ʒu����J�����̈ʒu�܂ł̃x�N�g���쐬
	dir_ = playerPos - pos_;

	//�x�N�g���̒����擾
	distanceToPlayer_ = dir_.L2Norm();

	//�J�������߂Â���ŏ��̋����ȏ㗣��Ă���Ȃ�
	distanceToPlayer_ >= CAMERA::MIN_DISTANCE ?

		//�J�������������ő�̋����ȏ㗣��Ă�����
		(distanceToPlayer_ >= CAMERA::MAX_DISTANCE ?

		//�J�������������ő�̋����ɂ���
		distanceToPlayer_ = CAMERA::MAX_DISTANCE

		//�Z����Βǂ�������
		: distanceToPlayer_ -= CAMERA::SPEED)

		//�J�������߂Â���ŏ��̋����ɂ���
		: distanceToPlayer_ = CAMERA::MIN_DISTANCE;

	//�������猩�ĉ������ɉ�]
	if (InputKeyBoard::IsKeyDown(KEY::UP))
	{
		rot_.x -= CAMERA::ROT_UP_DOWN_SPEED;

		// rot_�̏㉺�̊p�x�Ƃ̒�`��́@(��/2) + ��/100 <= �� <= (��/2) - ��/100
		if (rot_.x < 0.0f)
		{
			rot_.x = 0.0f;
		}
	}

	//�������猩�ď�����ɉ�]
	if (InputKeyBoard::IsKeyDown(KEY::DOWN))
	{
		rot_.x += CAMERA::ROT_UP_DOWN_SPEED;

		// rot_�̏㉺�̊p�x�Ƃ̒�`��� (-��/2) + ��/100 <= �� <= (��/2) - ��/100
		if (rot_.x > MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x = MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED;
		}
	}

	//�������猩�ĉE�����ɉ�]
	if (InputKeyBoard::IsKeyDown(KEY::LEFT))
	{
		rot_.y -= CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_�̍��E�̊p�x�Ƃ̒�`��� -�� < �� <= ��
		if (rot_.y < -MY_MATH::PI)
		{
			rot_.y = MY_MATH::PI;
		}

	}

	//�������猩�č������ɉ�]
	if (InputKeyBoard::IsKeyDown(KEY::RIGHT))
	{
		rot_.y += CAMERA::ROT_RIGHT_LEFT_SPEED;

		// rot_�̍��E�̊p�x�Ƃ̒�`��� -�� <= �� < ��
		if (rot_.y > MY_MATH::PI)
		{
			rot_.y = -MY_MATH::PI;
		}

	}

	//�Q�[���p�b�h��R�X�e�B�b�N�擾
	const Vector3D GamePadRStick = InputGamePad::GetRStickVector().Normalize();

	if (MyMath::Abs(GamePadRStick.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(GamePadRStick.y) > Common::KINDA_SMALL_NUMBER)
	{
		rot_ += GamePadRStick * CAMERA::GAMEPAD_ROT_COEFFICIENT;

		//rot_.x < (-��/2) + (��/100)
		if (rot_.x < -MY_MATH::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x = -MY_MATH::HALF_PI + CAMERA::ROT_UP_DOWN_SPEED;
		}

		//rot_.x > (��/2) - (��/100)
		if (rot_.x > MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED)
		{
			rot_.x = MY_MATH::HALF_PI - CAMERA::ROT_UP_DOWN_SPEED;
		}


		//rot_.y < -��/2
		if (rot_.y < -MY_MATH::PI)
		{
			rot_.y = MY_MATH::PI;
		}

		//rot_.y > ��/2
		if (rot_.y > MY_MATH::PI)
		{
			rot_.y = -MY_MATH::PI;
		}
	}
}

//�J�����X�V�֐�
void Camera::UpDate(void)
{
	//�s��ɂ��J�����ʒu�v�Z
	Matrix3D RetCameraMat = Matrix3D::GetTranslateMatrix(target_)
		* Matrix3D::GetYawMatrix(rot_.y)
		* Matrix3D::GetPitchMatrix(rot_.x)
		* Matrix3D::GetTranslateMatrix(-target_.x, -target_.y, -target_.z - distanceToPlayer_);

	pos_ = RetCameraMat * target_;

	//�J���������Ă�������v�Z
	dir_ = Matrix3D::GetTranslateMatrix(dir_)
		* Matrix3D::GetYawMatrix(rot_.y)
		* Matrix3D::GetPitchMatrix(-dir_.x) * dir_;

	//�J�����ʒu�ݒ�
	SetCameraPositionAndTargetAndUpVec(pos_, target_, up_);

}
