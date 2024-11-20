#include "Corpse.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//�����������֐�
	void Corpse::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			owner->SetVelocity(knockBackDirection.Normalize() * CORPSE::SPEED);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void Corpse::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//�m�b�N�o�b�N��Ԃ̏������ő�񐔂���Ă�����
			if (CORPSE::MAX_CORPSE_TIME_COUNT < timeCount_)
			{
				//����������
				timeCount_ = 0;

				owner->SetIsActive(false);

				return;
			}

			//�����̑��x���ʒu�ɉ��Z���A��ɏ㏸������
			Vector3D velocity = owner->GetVelocity();
			velocity.y += CORPSE::SPEED;
			owner->MovePos(velocity);

			//X����]������
			owner->RotatePitch(MyMath::INVERSE_TWO_PI);

			//�m�b�N�o�b�N��Ԃ̎��Ԍv��
			++timeCount_;
		}
	}
}
