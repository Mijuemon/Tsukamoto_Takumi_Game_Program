#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	//�����������֐�
	void KnockBack::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			Vector3D knockBackDirection = owner->GetPos() - owner->GetTargetPosition();
			owner->SetVelocity(knockBackDirection.Normalize() * KNOCK_BACK::SPEED);
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

				nextStateName_ = ENEMY_STATE::CHASE;
				isTransitionToNextState_ = true;

				return;
			}

			//�����̑��x���ʒu�ɉ��Z���A��ɏ㏸������
			Vector3D velocity = owner->GetVelocity();
			velocity.y += KNOCK_BACK::SPEED;
			owner->MovePos(velocity);

			//�m�b�N�o�b�N��Ԃ̎��Ԍv��
			++timeCount_;
		}
	}

}