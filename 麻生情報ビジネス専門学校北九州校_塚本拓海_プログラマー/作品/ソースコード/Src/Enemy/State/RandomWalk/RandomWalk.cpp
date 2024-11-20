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
			owner->GetDir().Normalize();
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void RandomWalk::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->MovePos(owner->GetDir() * moveSpeed_);

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
		}
	}
}