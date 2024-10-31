#include "EnemyMonster.h"
#include "EnemyParameter.h"
#include <Math/MyMath.h>
#include <Matrix/Matrix3D.h>

namespace BOUDAMA
{
	//�R���X�g���N�^
	EnemyMonster::EnemyMonster()
	{
		//������
		handle_ = -1;
		attackChargeCount_ = 0;
		attackTimeCount_ = 0;
		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		isAlive_ = true;
		hp_ = 3;
		radius_ = ENEMY_BOMBER::RADIUS;
		state_ = ENEMY::STATE::SEARCH;
		pos_ = MY_MATH::ZERO_VECTOR_3D;
		velocity_ = MY_MATH::ZERO_VECTOR_3D;
		rot_ = MY_MATH::ZERO_VECTOR_3D;
	}

	//�f�X�g���N�^
	EnemyMonster::~EnemyMonster()
	{

	}

	//�����������֐�
	void EnemyMonster::Init(void)
	{
		//������
		handle_ = -1;
		attackChargeCount_ = 0;
		attackTimeCount_ = 0;
		findOutReactionCount_ = 0;
		moveAngleChangeCount_ = 0;
		knockBackTimeCount_ = 0;
		scoreNum_ = ENEMY_MONSTER::ADD_SCORE_NUM;
		state_ = ENEMY::STATE::SEARCH;
		isAlive_ = false;
		hp_ = 3;
		radius_ = ENEMY_BOMBER::RADIUS;
		pos_ = ENEMY_MONSTER::INIT_POS;
		velocity_ = MY_MATH::ZERO_VECTOR_3D;
		rot_ = MY_MATH::ZERO_VECTOR_3D;
		dir_ = { 0.0f,0.0f,1.0f };

		dir_ *= Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

		rot_.y = atan2f(-dir_.x, -dir_.z);

		pos_ *= Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

		MV1SetScale(handle_, VECTOR(2.0f, 2.0f, 2.0f));

	}

	//�s�������֐�
	void EnemyMonster::Step(const Vector3D& playerPos)
	{
		//���S���Ă���ꍇ�͎��s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		//�m�b�N�o�b�N��Ԃ̏���
		if (state_ == ENEMY::STATE::KNOCK_BACK)
		{
			//�m�b�N�o�b�N��Ԃ̏�����120�񂳂�Ă�����
			if (knockBackTimeCount_ > 120)
			{
				knockBackTimeCount_ = 0;
				isAlive_ = false;
				state_ = ENEMY::STATE::SEARCH;
				pos_ = MY_MATH::ZERO_VECTOR_3D;
				rot_ = MY_MATH::ZERO_VECTOR_3D;
				velocity_ = MY_MATH::ZERO_VECTOR_3D;

				//�ʒu�E�p�x�ݒ�
				MV1SetPosition(handle_, pos_);
				MV1SetRotationXYZ(handle_, rot_);

				return;
			}

			//�m�b�N�o�b�N��Ԃ̎��Ԍv��
			++knockBackTimeCount_;


			//�����̑��x���ʒu�ɉ��Z���A��ɏ㏸������
			pos_ += velocity_;
			pos_.y += ENEMY_MONSTER::KNOCKBACK_Y_POWER;

			rot_.x += MY_MATH::PI_OVER_TEN;

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}

		//�d�͂������Ă��n�ʂɂ߂荞�܂Ȃ���Ώ���������
		pos_.y - ENEMY::GRAVITY >= ENEMY_MONSTER::GROUND_POS_Y ? pos_.y -= ENEMY::GRAVITY : pos_.y = ENEMY_MONSTER::GROUND_POS_Y;

		//�v���C���[�T�����
		if (state_ == ENEMY::STATE::SEARCH)
		{
			velocity_ += dir_.Normalize() * 0.125f;

			//���̑��x�𒴂�����
			if (velocity_.SquareL2Norm() > ENEMY_MONSTER::MAX_SPEED * ENEMY_MONSTER::MAX_SPEED)
			{
				velocity_ = velocity_.Normalize() * ENEMY_MONSTER::MAX_SPEED;
			}

			pos_ += velocity_;

			if (MyMath::Abs(pos_.x) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.x = 0.0f < pos_.x ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;
				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			if (MyMath::Abs(pos_.z) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.z = 0.0f < pos_.z ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;

				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);


			//�ړ�����p�x�؂�ւ����Ԍv��
			++moveAngleChangeCount_;

			if (moveAngleChangeCount_ >= ENEMY_MONSTER::MOVEANGLE_CHANGE_MAX_NUM)
			{
				dir_ = dir_ * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359)));

				//�p�x�؂�ւ��ݒ�
				rot_.y = atan2f(-dir_.x, -dir_.z);

				//���x������
				velocity_ = MY_MATH::ZERO_VECTOR_3D;

				//�ړ�����p�x�؂�ւ����ԏ�����
				moveAngleChangeCount_ = 0;
			}

			//�v���C���[�����E�͈͓̔��ɋ��Ȃ��Ȃ�֐��E�o
			if (Vector3D::Dot(dir_, playerPos) < 0.0f)
			{
				return;
			}

			//�v���C���[���߂��ɂ�����
			if ((playerPos - pos_).SquareL2Norm() < ENEMY_MONSTER::SQUARE_FIND_OUT_RANGE)
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
			//���������̔������Ԍv��
			++findOutReactionCount_;

			//�v���C���[�̂ق�������
			dir_ = playerPos - pos_;
			dir_.y = 0.0f;
			rot_.y = atan2f(-dir_.x, -dir_.z);

			MV1SetRotationXYZ(handle_, rot_);

			//��莞�Ԍo������ǂ�������ԂɈڍs
			if (findOutReactionCount_ >= ENEMY_MONSTER::REACTION_MAX_TIME)
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
			dir_.y = 0.0f;

			//�P�ʃx�N�g���ɂ��ăX�J���[�{�����x�ɉ��Z
			velocity_ += dir_.Normalize() * ENEMY_MONSTER::CHASE_SPEED;

			//�ʒu�ɉ��Z
			pos_ += velocity_;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			//��苗���܂ŋ߂Â�����
			if (dir_.SquareL2Norm() < ENEMY_MONSTER::SQUARE_FIND_OUT_RANGE)
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
			dir_ = playerPos - pos_;
			dir_.y = 0.0f;

			rot_.y = atan2f(-dir_.x, -dir_.z);

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//�U�����ߎ��Ԍv��
			++attackChargeCount_;

			if (attackChargeCount_ > ENEMY_MONSTER::ATTACK_CHARGE_MAX_TIME)
			{
				//�U����ԂɈڍs
				state_ = ENEMY::STATE::ATTACK;

				//�ō����x�ɐݒ�
				velocity_ = dir_.Normalize() * ENEMY_MONSTER::MAX_SPEED * 2.0f;

				//�U�����ߎ��ԏ�����
				attackChargeCount_ = 0;

				return;
			}

			return;
		}

		//�U�����
		if (state_ == ENEMY::STATE::ATTACK)
		{
			pos_ += velocity_;

			if (MyMath::Abs(pos_.x) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.x = 0.0f < pos_.x ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;
				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			if (MyMath::Abs(pos_.z) > ENEMY_MONSTER::MAX_POS_X_Z)
			{
				pos_.z = 0.0f < pos_.z ? ENEMY_MONSTER::MAX_POS_X_Z : -ENEMY_MONSTER::MAX_POS_X_Z;

				dir_ = -dir_;
				velocity_ = -velocity_;
			}

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			//�U�����Ԍv��
			++attackTimeCount_;

			if (attackTimeCount_ > ENEMY_MONSTER::ATTACK_MAX_TIME)
			{
				state_ = ENEMY::STATE::SEARCH;

				attackTimeCount_ = 0;
			}

			return;
		}
	}

	//�`�揈���֐�
	void EnemyMonster::Draw(void)
	{
		if (!isAlive_)
		{
			return;
		}

		MV1DrawModel(handle_);

		DrawLine3D(pos_, pos_ + dir_.Normalize() * ENEMY_MONSTER::FIND_OUT_RANGE, GetColor(255, 0, 0));

	}

	//�o�������֐�
	void EnemyMonster::AppearanceRequest(void)
	{
		//�����ʒu�ݒ�
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(static_cast<float>(GetRand(359))))
			* Matrix3D::GetTranslateMatrix(ENEMY_MONSTER::INIT_POS) * MY_MATH::ZERO_VECTOR_3D;

		//���ґh��
		isAlive_ = true;

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}


	//�����蔻�菈��
	void EnemyMonster::HitCalculation(void)
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
