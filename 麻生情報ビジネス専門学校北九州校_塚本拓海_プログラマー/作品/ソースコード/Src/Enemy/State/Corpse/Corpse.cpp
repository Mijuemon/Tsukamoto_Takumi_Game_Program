#include "Corpse.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	namespace CORPSE
	{
		constexpr int MAX_CORPSE_TIME_COUNT = 60;
		constexpr float SPEED = 8.5f;
		constexpr float UP_SPEED = 7.5f;
	}

	//�����������֐�
	void Corpse::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetIsCollisionEnabled(false);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void Corpse::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//���̏�Ԃ̏������ő�񐔂���Ă�����
			if (CORPSE::MAX_CORPSE_TIME_COUNT < timeCount_)
			{
				//����������
				timeCount_ = 0;

				owner->SetIsActive(false);

				return;
			}

			//�����̑��x���ʒu�ɉ��Z���A�΂ߏ�Ɉړ�������
			Vector3D velocity = owner->GetVelocity();
			velocity.y += CORPSE::UP_SPEED;
			owner->MovePos(velocity);

			//X����]������
			owner->RotatePitch(MyMath::INVERSE_TWO_PI);

			//���̏�Ԃ̎��Ԍv��
			++timeCount_;
		}
	}
}
