#include "RandomWalk.h"

#include "Math/MyMath.h"
#include "Matrix/Matrix3D.h"

namespace BOUDAMA
{
	//�����������֐�
	void RandomWalk::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir(owner->GetDir().Normalize() * moveSpeed_);
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void RandomWalk::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->AddVelocity(owner->GetDir());

			//���̑��x�𒴂�����
			if (owner->GetVelocity().SquareL2Norm() > squareMaxMoveSpeed_)
			{
				owner->SetVelocity(owner->GetVelocity().Normalize() * maxMoveSpeed_);
			}

			owner->MovePos(owner->GetDir() * moveSpeed_);

			//�[�ɍs�����甽�΂�����
			if (maxMovementRange_ < MyMath::Abs(owner->GetPosX()) || maxMovementRange_ < MyMath::Abs(owner->GetPosZ()))
			{
				owner->GetDir().Inverse();
				owner->GetVelocity().Inverse();
			}

			//�ړ�����p�x�؂�ւ����Ԍv��
			++directionChangeTimeCount_;

			if (directionChangeInterval_ <= directionChangeTimeCount_)
			{
				owner->SetDir(owner->GetDir() * Matrix3D::GetYawMatrix(MyMath::DegreesToRadian(GetRand(359))));

				//�p�x�؂�ւ��ݒ�
				owner->RotateYaw(owner->GetDir());

				//���x������
				owner->SetVelocity(MyMath::ZERO_VECTOR_3D);

				//�ړ�����p�x�؂�ւ����ԏ�����
				directionChangeTimeCount_ = 0;
			}

			//�v���C���[�����E�͈͓̔��ɋ��Ȃ��Ȃ�֐��E�o
			if (Vector3D::Dot(owner->GetDir(), owner->GetTargetPosition()) < 0.0f)
			{
				return;
			}

			//�v���C���[���߂��ɂ�����
			if ((owner->GetTargetPosition() - owner->GetPos()).SquareL2Norm() < squareFindOutRange_)
			{
				//�v���C���[������ԂɈڍs
				nextStateName_ = ENEMY_STATE::FIND_OUT;
				isTransitionToNextState_ = true;

				return;
			}
		}
	}
}