#include "Idle.h"
#include "Math/MyMath.h"

namespace BOUDAMA
{
	//�����������֐�
	void Idle::Enter(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->SetVelocity(MyMath::ZERO_VECTOR_3D);
		}
	}

	//�s�������֐�
	void Idle::Execute(void)
	{
		//�������Ȃ�
	}
}
