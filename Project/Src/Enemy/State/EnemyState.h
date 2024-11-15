#pragma once

#include "StateMachine/StateBase.h"
#include "StateParameter.h"

namespace BOUDAMA
{
	//�G�̏�Ԑ�p�̊��N���X
	class EnemyState : public StateBase<ENEMY_STATE>
	{
	public:
		explicit constexpr EnemyState(const ENEMY_STATE stateName) noexcept : StateBase(stateName) {}

		virtual ~EnemyState() noexcept = default;

		//���̏�Ԃɓ������u�Ԃɂ������s����֐�
		virtual void Enter(void) override = 0;

		//�s�������֐�
		virtual void Execute(void) override = 0;
	};
}
