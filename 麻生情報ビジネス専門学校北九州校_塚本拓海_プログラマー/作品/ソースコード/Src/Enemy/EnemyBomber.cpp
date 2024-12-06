#include "EnemyBomber.h"
#include "EnemyParameter.h"

#include "Math/MyMath.h"
#include "Common/Common.h"

#include <Matrix/Matrix3D.h>

#include "State/RandomWalk/RandomWalk.h"
#include "State/FindOut/FindOut.h"
#include "State/Chase/Chase.h"
#include "State/KnockBack/KnockBack.h"
#include "State/Corpse/Corpse.h"
#include "State/Idle/Idle.h"

namespace BOUDAMA
{
	//�����������֐�
	void EnemyBomber::Init(void)
	{
		//������
		handle_ = -1;
		isAlive_ = false;
		hp_ = BOMBER::HP;
		radius_ = BOMBER::RADIUS;
		pos_ = BOMBER::INIT_POS;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;
		dir_ = { 0.0f,0.0f,1.0f };

		rot_.y = std::atan2(-dir_.x, -dir_.z);

		bombThrowStunTime_ = 0;

		stateMachine_ = std::make_unique<EnemyBase::StateMachineType>();

		stateMachine_->AddState<RandomWalk>(ENEMY_STATE::RANDOM_WALK, ENEMY_STATE::FIND_OUT, BOMBER::SPEED, BOMBER::MAX_SPEED, BOMBER::FIND_OUT_RANGE);
		stateMachine_->AddState<FindOut>(ENEMY_STATE::FIND_OUT, ENEMY_STATE::CHASE, BOMBER::REACTION_MAX_TIME);
		stateMachine_->AddState<Chase>(ENEMY_STATE::CHASE, ENEMY_STATE::IDLE, BOMBER::CHASE_SPEED);
		stateMachine_->AddState<Idle>(ENEMY_STATE::IDLE, ENEMY_STATE::RANDOM_WALK, BOMBER::REACTION_MAX_TIME);
		stateMachine_->AddState<KnockBack>(ENEMY_STATE::KNOCK_BACK, ENEMY_STATE::RANDOM_WALK);
		stateMachine_->AddState<Corpse>(ENEMY_STATE::CORPSE);

		stateMachine_->ChangeState(ENEMY_STATE::RANDOM_WALK);

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//�s�������֐�
	void EnemyBomber::Step(const Vector3D& playerPos)
	{
		//���S���Ă�������s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		targetPosition_ = playerPos;

		stateMachine_->Step();

		if (pos_.y <= BOMBER::GROUND_POS_Y)
		{
			pos_.y = BOMBER::GROUND_POS_Y;
		}

		floatMotionTheta_ < MyMath::TWO_PI ? floatMotionTheta_ += MyMath::INVERSE_TWO_PI : floatMotionTheta_ = 0.0f;

		pos_.y += 2.0f * std::sin(floatMotionTheta_);

		if (0 < bombThrowStunTime_)
		{
			bombThrowStunTime_ <= 600 ? ++bombThrowStunTime_ : bombThrowStunTime_ = 0;

			//�ʒu�E�p�x�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}
		
		bomb_->SetPos(pos_ + BOMB::HOLD_UP_DISTANCE);
		
		Vector3D myPosToTargetPos = targetPosition_ - pos_;

		if (myPosToTargetPos.SquareL2Norm() <= BOMBER::SQUARE_FIND_OUT_RANGE && Vector3D::Dot(dir_, myPosToTargetPos.Normalize()) > 0.0f)
		{
			Vector3D throwVelocity = myPosToTargetPos.Normalize() * 100.0f;
			throwVelocity.y = BOMBER::SPEED;

			bomb_->SetVelocity(throwVelocity);
			bomb_->AppearanceRequest();

			++bombThrowStunTime_;

			stateMachine_->ChangeState(ENEMY_STATE::IDLE);
		}

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
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

		DrawLine3D(pos_, pos_ + dir_ * BOMBER::FIND_OUT_RANGE, GetColor(255, 0, 0));
	}

	//�o�������֐�
	void EnemyBomber::AppearanceRequest(void)
	{
		//�����ʒu�ݒ�
		pos_ = Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))) *
			Matrix3D::GetTranslateMatrix(BOMBER::INIT_POS) * MyMath::ZERO_VECTOR_3D;

		//�p�x������
		rot_ = MyMath::ZERO_VECTOR_3D;

		//���ґh��
		isAlive_ = true;

		bomb_->SetIsActive(true);

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}
}
