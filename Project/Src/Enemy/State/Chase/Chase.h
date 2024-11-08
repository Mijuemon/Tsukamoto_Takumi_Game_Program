#pragma once

#include "StateMachine/StateBase.h"
#include "Enemy/State/StateParameter.h"

namespace BOUDAMA
{
	//�ǔ����
	class Chase final : public StateBase<ENEMY_STATE>
	{
	public:
		constexpr Chase() = default;
		explicit constexpr Chase(const ENEMY_STATE stateName) : StateBase<ENEMY_STATE>(stateName) {}
		~Chase() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
