#pragma once

#include "StateMachine/StateBase.h"
#include "Enemy/State/StateParameter.h"
#include <Enemy/EnemyBase.h>

namespace BOUDAMA
{
	//待機状態
	class Idle final : public StateBase<ENEMY_STATE>
	{
	public:
		Idle() = default;
		~Idle() override = default;

	private:
		//初期化処理関数
		void Init(void) override;

		//行動処理関数
		void Step(void) override;

		/// <summary>
		/// 次の状態に遷移できるか？
		/// </summary>
		/// <returns>
		/// true : 次の状態に遷移する
		/// false : 現在の状態を維持する
		/// </returns>
		bool CanTransitionToNextState(void) const override;
	};
}
