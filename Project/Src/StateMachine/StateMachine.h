#pragma once

#include <memory>
#include "StateBase.h"

namespace BOUDAMA
{
	//��ԊǗ��p�N���X
	template<class T>
	class StateMachine final
	{
	private:
		using State = StateBase<T>;

		//��Ԉꗗ
		std::vector<std::unique_ptr<State>> stateVector_;

		//���݂̏�Ԃ̔z��̓Y����
		int currentStateIndex_;

	public:
		constexpr StateMachine(void) noexcept : currentStateIndex_(0) {};

		StateMachine(const StateMachine&) = delete;
		StateMachine& operator=(const StateMachine&) = delete;

		~StateMachine() noexcept = default;

		void Step(void)
		{
			//���݂̏�Ԃ̏���
			stateVector_[currentStateIndex_]->Execute();

			if (stateVector_[currentStateIndex_]->CanTransitionToNextState())
			{
				ChangeState();

				//�J�ڌ�̏�Ԃ̏�����
				stateVector_[currentStateIndex_]->Enter();

				return;
			}
		}

		//��Ԃ�V�����쐬����
		template<class Ty>
		void MakeState(const T stateName)
		{
			stateVector_.emplace_back(std::make_unique<Ty>(stateName));
		}

		//�ŏ�����n�߂��Ԃ�ݒ�
		void SetStartState(const T startStateName)
		{
			for (int index = 0; const auto & state : stateVector_)
			{
				if (state->GetMyState() == startStateName)
				{
					currentStateIndex_ = index;
					break;
				}

				++index;
			}

			stateVector_[currentStateIndex_]->Enter();
		}

		//��Ԃ�ύX����
		void ChangeState(void)
		{
			const auto nextState = stateVector_[currentStateIndex_]->GetNextState();

			for (int index = 0; const auto & state : stateVector_)
			{
				if (state->GetMyState() == nextState)
				{
					currentStateIndex_ = index;
					return;
				}

				++index;
			}
		}

		//���ׂĂ̏�Ԃ��폜����
		void AllClear(void)
		{
			stateVector_.clear();
		}

	};
}
