#include "FindOut.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//�����������֐�
	void FindOut::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void FindOut::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetDir(owner->GetTargetPosition() - owner->GetPos());

			//�p�x�؂�ւ��ݒ�
			owner->RotateYaw(owner->GetDir());
		}
	}
}