#include "EnemyBomber.h"
#include "EnemyParameter.h"
#include "Math/MyMath.h"
#include "Common/Common.h"
#include "Player/Player.h"
#include <Player/PlayerParameter.h>
#include <Matrix/Matrix3D.h>

namespace BOUDAMA
{
	//�R���X�g���N�^
	EnemyBomber::EnemyBomber()
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		radius_ = ENEMY_BOMBER::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;


		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		knockBackTimeCount_ = 0;
		attackChargeCount_ = 0;
	}

	//�f�X�g���N�^
	EnemyBomber::~EnemyBomber()
	{

	}

	//�����������֐�
	void EnemyBomber::Init(void)
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		hp_ = 3;
		radius_ = ENEMY_BOMBER::RADIUS;
		knockBackTimeCount_ = 0;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = ENEMY_BOMBER::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;


		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		knockBackTimeCount_ = 0;
		attackChargeCount_ = 0;
	}

	//�s�������֐�
	void EnemyBomber::Step(const Vector3D& playerPos)
	{
		//���S���Ă�������s���Ȃ�
		if (!isAlive_)
		{
			return;
		}


		if (state_ == ENEMY::STATE::KNOCK_BACK)
		{
			if (knockBackTimeCount_ > 60)
			{
				knockBackTimeCount_ = 0;
				isAlive_ = false;
				state_ = ENEMY::STATE::SEARCH;
				pos_ = MyMath::ZERO_VECTOR_3D;
				rot_ = MyMath::ZERO_VECTOR_3D;
				velocity_ = MyMath::ZERO_VECTOR_3D;
			}

			pos_ += velocity_;
			pos_.y += 9.5f;

			rot_.x += MyMath::INVERSE_TWO_PI;

			//�m�b�N�o�b�N�̎��Ԍv��
			++knockBackTimeCount_;

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);


			return;
		}


		//�v���C���[�T�����
		if (state_ == ENEMY::STATE::SEARCH)
		{
			velocity_ += dir_.Normalize() * 0.125f;

			//���̑��x�𒴂�����
			if (velocity_.SquareL2Norm() > ENEMY_BOMBER::MAX_SPEED * ENEMY_BOMBER::MAX_SPEED)
			{
				velocity_ = velocity_.Normalize() * ENEMY_BOMBER::MAX_SPEED;
			}

			pos_ += velocity_;

			if (MyMath::Abs(pos_.x) > ENEMY_BOMBER::MAX_POS_X_Z)
			{
				pos_.x = 0.0f < pos_.x ? ENEMY_BOMBER::MAX_POS_X_Z : -ENEMY_BOMBER::MAX_POS_X_Z;
				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			if (MyMath::Abs(pos_.z) > ENEMY_BOMBER::MAX_POS_X_Z)
			{
				pos_.z = 0.0f < pos_.z ? ENEMY_BOMBER::MAX_POS_X_Z : -ENEMY_BOMBER::MAX_POS_X_Z;

				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);


			//�ړ�����p�x�؂�ւ����Ԍv��
			++moveAngleChangeCount_;

			if (moveAngleChangeCount_ >= ENEMY_BOMBER::MOVEANGLE_CHANGE_MAX_NUM)
			{
				dir_ = dir_ * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

				//�p�x�؂�ւ��ݒ�
				rot_.y = atan2f(-dir_.x, -dir_.z);

				//���x������
				velocity_ = { 0.0f,0.0f,0.0f };

				//�ړ�����p�x�؂�ւ����ԏ�����
				moveAngleChangeCount_ = 0;
			}

			//�v���C���[�����E�͈͓̔��ɋ��Ȃ��Ȃ�֐��E�o
			if (Vector3D::Dot(dir_, playerPos) < 0.0f)
			{
				return;
			}

			//�v���C���[���߂��ɂ�����
			if ((playerPos - pos_).SquareL2Norm() < ENEMY_BOMBER::SQUARE_FIND_OUT_RANGE)
			{
				//�v���C���[������ԂɈڍs
				state_ = ENEMY::STATE::FIND_OUT;

				velocity_ = { 0.0f,0.0f,0.0f };

				return;
			}

			return;
		}

		//�v���C���[�������
		if (state_ == ENEMY::STATE::FIND_OUT)
		{
			//�v���C���[�̕�������������
			dir_ = playerPos - pos_;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			MV1SetRotationXYZ(handle_, rot_);

			//���������̔������Ԍv��
			++findOutReactionCount_;

			//��莞�Ԍo������ǂ�������ԂɈڍs
			if (findOutReactionCount_ >= ENEMY_BOMBER::REACTION_MAX_TIME)
			{
				state_ = ENEMY::STATE::CHASE;
				findOutReactionCount_ = 0;

				return;
			}

			return;
		}

		//�v���C���[�ǐՏ��
		if (state_ == ENEMY::STATE::CHASE)
		{
			//�������g����v���C���[�܂ł̃x�N�g���쐬
			dir_ = playerPos - pos_;

			//�P�ʃx�N�g���ɂ��ăX�J���[�{�����x�ɉ��Z
			velocity_ += dir_.Normalize() * ENEMY_BOMBER::CHASE_SPEED;

			//�ʒu�ɉ��Z
			pos_ += velocity_;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			//��苗���܂ŋ߂Â�����
			if (dir_.SquareL2Norm() < ENEMY_BOMBER::SQUARE_CHASE_MIN_RANGE)
			{
				//�U�����ߏ�ԂɈڍs
				state_ = ENEMY::STATE::CHARGE;

				velocity_ = { 0.0f,0.0f,0.0f };
			}

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}


		//�U�����ߏ��
		if (state_ == ENEMY::STATE::CHARGE)
		{
			//�U�����ߎ��Ԍv��
			++attackChargeCount_;

			//�v���C���[�̂ق�������
			dir_ = playerPos - pos_;
			rot_.y = atan2f(-dir_.x, -dir_.z);

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//�U�����ߎ��Ԍo��
			if (attackChargeCount_ > ENEMY_BOMBER::ATTACK_CHARGE_MAX_TIME)
			{
				//�U����ԂɈڍs
				state_ = ENEMY::STATE::ATTACK;

				//�ō����x�ɐݒ�
				velocity_ = dir_.Normalize() * ENEMY_BOMBER::MAX_SPEED * 2.0f;

				//�U�����ߎ��ԏ�����
				attackChargeCount_ = 0;

				return;
			}

			return;
		}

		//�U�����
		if (state_ == ENEMY::STATE::ATTACK)
		{

		}
	}


	//�`�揈���֐�
	void EnemyBomber::Draw(void)
	{
		if (!isAlive_)
		{
			return;
		}

		//���f���`��
		MV1DrawModel(handle_);

	}

	//�o�������֐�
	void EnemyBomber::AppearanceRequest(void)
	{
		//�����ʒu�ݒ�
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))) *
			Matrix3D::GetTranslateMatrix(ENEMY_BOMBER::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//�p�x������
		rot_ = { 0.0f,0.0f,0.0f };

		//���ґh��
		isAlive_ = true;

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//�����蔻�菈��
	void EnemyBomber::HitCalculation(void)
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
