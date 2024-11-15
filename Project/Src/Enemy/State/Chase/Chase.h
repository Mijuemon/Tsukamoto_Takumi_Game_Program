#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	//�ǔ����
	class Chase final : public EnemyState
	{
	private:
		//�ړ����x
		float moveSpeed_;

	public:
		explicit constexpr Chase(const auto stateName, float moveSpeed) noexcept : EnemyState(stateName), moveSpeed_(moveSpeed) {}
		~Chase() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
