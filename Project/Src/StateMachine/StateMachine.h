#pragma once

#include <memory>
#include <vector>
#include "StateBase.h"

namespace BOUDAMA
{
	//��ԊǗ��p�N���X
	template<class StateType>
	class StateMachine final
	{
	private:
		//��Ԉꗗ
		std::vector<std::unique_ptr<StateType>> stateVector_;

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
		template<class State, class... Args>
		void MakeState(Args&&... args)
		{
			stateVector_.emplace_back(std::make_unique<State>(args...));
		}

		//���ׂĂ̏�Ԃ̏��L�Ґݒ�
		void SetAllStateOwner(const auto& owner)
		{
			for (const auto& state : stateVector_)
			{
				state->SetOwner(owner);
			}
		}

		//�ŏ�����n�߂��Ԃ�ݒ�
		void SetStartState(const auto startStateName)
		{
			for (int index = 0; const auto& state : stateVector_)
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

		//���̏�ԂɑJ�ڂ���
		void ChangeState(void)
		{
			const auto nextState = stateVector_[currentStateIndex_]->GetNextState();

			for (int index = 0; const auto& state : stateVector_)
			{
				if (state->GetMyState() == nextState)
				{
					currentStateIndex_ = index;
					return;
				}

				++index;
			}
		}

		/// <summary>
		/// �����̏�ԂɑJ�ڂ�����
		/// </summary>
		/// <param name="changeStateName">
		/// �J�ڐ�̏��
		/// </param>
		void ChangeState(const auto changeStateName)
		{
			for (int index = 0; const auto& state : stateVector_)
			{
				if (state->GetMyState() == changeStateName)
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
			stateVector_.shrink_to_fit();
		}

	};
}
