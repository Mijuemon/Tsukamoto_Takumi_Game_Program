#pragma once

#include <memory>
#include <unordered_map>
#include "StateBase.h"

namespace BOUDAMA
{
	//��ԊǗ��p�N���X
	template<class T>
	class StateMachine final
	{
	private:
		//��Ԉꗗ�̃��X�g
		std::unordered_map<T, const std::shared_ptr<StateBase<T>>&> stateMap_;

		//���݂̏��
		std::weak_ptr<StateBase<T>> currentState_;

	public:
		StateMachine() = default;
		~StateMachine() = default;

		void Step(void)
		{
			if (!currentState_)
			{
				return;
			}

			//���݂̏�Ԃ̏���
			currentState_->Step();

			if (currentState_->CanTransitionToNextState())
			{
				ChangeState();

				if (currentState_)
				{

					//�J�ڌ�̏�Ԃ̏�����
					currentState_->Init();

					return;
				}
			}
		}

		//��Ԃ�V�����o�^����
		void Register(T name, const std::shared_ptr<StateBase<T>>& state)
		{
			stateMap_.insert(std::make_pair(name, state));
		}

		//�ŏ�����n�߂��Ԃ�ݒ�
		void SetStartState(T startStateName)
		{
			const auto& it = stateMap_.find(registerName);

			if (it == stateMap_.end())
			{
				return;
			}

			currentState_ = it->second.lock();

			currentState_->Init();
		}

		//��Ԃ�ύX����
		void ChangeState(void)
		{
			const auto& it = stateMap_.find(currentState_->GetNextState());

			if (it == stateMap_.end())
			{
				return;
			}

			currentState_ = it->second.lock();
		}

		//�o�^�������̂��폜����
		void Deregistration(T eraseStateName)
		{
			const auto& it = stateMap_.find(eraseStateName);

			if (it == stateMap_.end())
			{
				return;
			}

			stateMap_.erase(it);
		}

		//���ׂĂ̓o�^���폜����
		void AllDeregistration(void)
		{
			stateMap_.clear();
		}

	};
}
