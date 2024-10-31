#pragma once

#include "StateMachine/StateBase.h"
#include "Enemy/State/StateParameter.h"

namespace BOUDAMA
{
	//�ҋ@���
	class Idle final : public StateBase<ENEMY_STATE>
	{
	public:
		Idle() = default;
		~Idle() override = default;

	private:
		//�����������֐�
		void Init(void) override;

		//�s�������֐�
		void Step(void) override;

		/// <summary>
		/// ���̏�ԂɑJ�ڂł��邩�H
		/// </summary>
		/// <returns>
		/// true : ���̏�ԂɑJ�ڂ���
		/// false : ���݂̏�Ԃ��ێ�����
		/// </returns>
		virtual bool CanTransitionToNextState(void) const override;
	};
}
