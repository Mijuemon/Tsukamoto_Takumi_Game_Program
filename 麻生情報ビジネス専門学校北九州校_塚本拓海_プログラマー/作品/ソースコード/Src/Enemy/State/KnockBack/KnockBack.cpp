#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	namespace KNOCK_BACK
	{
		constexpr float SPEED = 10.0f;
		constexpr float UP_SPEED = 3.0f;
	}

	//�����������֐�
	void KnockBack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			owner->SetVelocity(knockBackDirection.Normalize() * KNOCK_BACK::SPEED);

			owner->SetIsCollisionEnabled(false);
		}

		isTransitionToNextState_ = false;
	}

	//�s�������֐�
	void KnockBack::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			//�m�b�N�o�b�N��Ԃ̏������ő�񐔂���Ă�����
			if (maxTimeCount_ < timeCount_)
			{
				//����������
				timeCount_ = 0;

				//�ǔ���ԂɑJ��
				nextStateName_ = ENEMY_STATE::CHASE;
				isTransitionToNextState_ = true;
				owner->SetIsCollisionEnabled(true);

				return;
			}

			//�����̑��x���ʒu�ɉ��Z���A��ɏ㏸������
			Vector3D velocity = owner->GetVelocity();
			velocity.y += KNOCK_BACK::UP_SPEED;
			owner->MovePos(velocity);

			//�m�b�N�o�b�N��Ԃ̎��Ԍv��
			++timeCount_;
		}
	}

}