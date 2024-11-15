#include "KnockBack.h"
#include <Math/MyMath.h>

namespace BOUDAMA
{
	//�����������֐�
	void KnockBack::Enter(void)
	{

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

				owner->SetIsActive(false);

				return;
			}

			//�����̑��x���ʒu�ɉ��Z���A��ɏ㏸������
			Vector3D velocity = owner->GetVelocity();
			velocity.y += 9.5f;
			owner->MovePos(velocity);

			//��]������
			owner->Rotate(MyMath::INVERSE_TWO_PI, 0.0f, 0.0f);

			//�m�b�N�o�b�N��Ԃ̎��Ԍv��
			++timeCount_;
		}
	}

}