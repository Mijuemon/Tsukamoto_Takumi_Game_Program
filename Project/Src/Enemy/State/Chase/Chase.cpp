#include "Chase.h"

namespace BOUDAMA
{
	//�����������֐�
	void Chase::Enter(void)
	{

	}

	//�s�������֐�
	void Chase::Execute(void)
	{
		if (const auto& owner = owner_.lock())
		{
			owner->AddVelocity(owner->GetDir());
			owner->MovePos(owner->GetVelocity());	
		}
	}
}
