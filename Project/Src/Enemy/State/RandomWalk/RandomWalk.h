#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	class RandomWalk : public EnemyState
	{
	public:
		explicit constexpr RandomWalk(const auto stateName) : EnemyState(stateName) {}

		~RandomWalk() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
