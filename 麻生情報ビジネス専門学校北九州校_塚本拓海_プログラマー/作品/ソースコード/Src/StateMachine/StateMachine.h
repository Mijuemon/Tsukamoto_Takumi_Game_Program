#pragma once

#include <memory>
#include <vector>
#include "StateBase.h"

#ifdef _DEBUG

#include <iostream>
#include <intrin.h>

#endif

namespace BOUDAMA
{
	//��ԊǗ��p�N���X
	template<class StateType, class Owner>
	class StateMachine final
	{
	public:
		using State = StateBase<StateType, Owner>;

	private:
		//��Ԉꗗ
		std::vector<std::unique_ptr<State>> stateVector_;

		//���݂̏�Ԃ̔z��̓Y����
		int currentStateIndex_;

	public:
		constexpr StateMachine(void) noexcept : currentStateIndex_(-1) {}

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
		template<class StateElement, class StateNumber, class... Args>
		void AddState(const StateNumber num, Args&&... args)
		{
#ifdef _DEBUG
			//���ɒǉ�����Ă���Ȃ�߂�
			for (const auto& state : stateVector_)
			{
				if (state->GetMyState() == num)
				{
					std::cerr << "Debug break : ���ɒǉ����ꂽ��Ԃ�ǉ����Ă��܂��I" << std::endl;
					__debugbreak();
				}
			}
#endif // !_DEBUG

			stateVector_.emplace_back(std::make_unique<StateElement>(num, args...));
		}

		//���ׂĂ̏�Ԃ̏��L�Ґݒ�
		void SetAllStateOwner(const auto& owner)
		{
			for (const auto& state : stateVector_)
			{
				state->SetOwner(owner);
			}
		}

		//�w��̏�Ԃ̏��L�Ґݒ�
		void SetStateOwner(const auto stateName, const auto& owner)
		{
			for (const auto& state : stateVector_)
			{
				if (state->GetMyState() == stateName)
				{
					state->SetOwner(owner);
				}
			}
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

			//�J�ڐ�̏�Ԃ̏�����
			stateVector_[currentStateIndex_]->Enter();
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

			//�J�ڐ�̏�Ԃ̏�����
			stateVector_[currentStateIndex_]->Enter();
		}

		//���ׂĂ̏�Ԃ��폜����
		void AllClear(void)
		{
			stateVector_.clear();
			stateVector_.shrink_to_fit();
		}

	};
}
