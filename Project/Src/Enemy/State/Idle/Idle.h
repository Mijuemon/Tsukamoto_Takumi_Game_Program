#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	//�ҋ@���
	class Idle final : public EnemyState
	{
	public:
		explicit constexpr Idle(const auto stateName) : EnemyState(stateName) {}

		~Idle() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
