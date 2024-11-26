#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyMonster.h"

namespace BOUDAMA
{
	//������p�̍U�����
	class Attack final : public EnemyState<EnemyMonster>
	{
	private:
		//�ړ����x
		float moveSpeed_;

		int attackTimeCount_;

		const int maxAttackTime_;

	public:
		explicit constexpr Attack(const auto stateName, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(stateName), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		explicit constexpr Attack(const auto myState, const auto nextState, float moveSpeed, int maxAttackTime) noexcept :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), attackTimeCount_(0), maxAttackTime_(maxAttackTime) {}

		~Attack() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
