#include "Enemy.h"
#include "EnemyParameter.h"
#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/Player.h"
#include <Player/PlayerParameter.h>
#include <Matrix/Matrix3D.h>
#include "State/Idle/Idle.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	Enemy::Enemy()
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		radius_ = ENEMY::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = MY_MATH::ZERO_VECTOR_3D;
		velocity_ = MY_MATH::ZERO_VECTOR_3D;
		rot_ = MY_MATH::ZERO_VECTOR_3D;
	}

	//�f�X�g���N�^
	Enemy::~Enemy()
	{

	}

	//�����������֐�
	void Enemy::Init(void)
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		knockBackTimeCount_ = 0;
		scoreNum_ = ENEMY::ADD_SCORE_NUM;
		radius_ = ENEMY::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = ENEMY::INIT_POS;
		velocity_ = MY_MATH::ZERO_VECTOR_3D;
		rot_ = MY_MATH::ZERO_VECTOR_3D;

		stateMachine_.MakeState<Idle>(ENEMY_STATE::IDLE);
		
	}

	//�s�������֐�
	void Enemy::Step(const Vector3D& playerPos)
	{
		//���S���Ă�������s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		//�m�b�N�o�b�N��Ԃ̏���
		if (state_ == ENEMY::STATE::KNOCK_BACK)
		{
			//�m�b�N�o�b�N��Ԃ̏�����60�񂳂�Ă�����
			if (knockBackTimeCount_ > 60)
			{
				//����������
				knockBackTimeCount_ = 0;
				isAlive_ = false;
				state_ = ENEMY::STATE::SEARCH;
				pos_ = MY_MATH::ZERO_VECTOR_3D;
				rot_ = MY_MATH::ZERO_VECTOR_3D;
				velocity_ = MY_MATH::ZERO_VECTOR_3D;

				return;
			}

			//�����̑��x���ʒu�ɉ��Z���A��ɏ㏸������
			pos_ += velocity_;
			pos_.y += 9.5f;

			//��]������
			rot_.x += MY_MATH::INVERSE_TWO_PI;

			//�m�b�N�o�b�N��Ԃ̎��Ԍv��
			++knockBackTimeCount_;


			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//�������^�[������
			return;
		}


		velocity_ = playerPos - pos_;

		//�ʒu���Z
		pos_ += velocity_.Normalize() * ENEMY::SPEED;

		//�d�͂������Ă��n�ʂɂ߂荞�܂Ȃ���Ώ���������
		pos_.y - ENEMY::GRAVITY > 10.0f ? pos_.y -= ENEMY::GRAVITY : pos_.y = 10.0f;

		//�p�x�ƌv�Z
		rot_.y = atan2f(velocity_.x, velocity_.z) - DX_PI_F;

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

	}


	//�`�揈���֐�
	void Enemy::Draw(void)
	{
		//���S���Ă���ꍇ�͎��s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		//�`�揈��
		MV1DrawModel(handle_);

	}

	//�o�������֐�
	void Enemy::AppearanceRequest(void)
	{
		//�����ʒu�ݒ�
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(static_cast<float>(GetRand(359)))) *
			Matrix3D::GetTranslateMatrix(ENEMY::INIT_POS) * MY_MATH::ZERO_VECTOR_3D;

		//���ґh��
		isAlive_ = true;

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//�����蔻�菈��
	void Enemy::HitCalculation(void)
	{
		//HP�����炷
		--hp_;

		//HP��0�ȉ��ɂȂ�����
		if (hp_ <= 0)
		{
			//���S����
			state_ = ENEMY::STATE::KNOCK_BACK;
		}
	}
}
