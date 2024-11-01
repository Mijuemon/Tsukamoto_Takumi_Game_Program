#pragma once

#include <memory>
#include <unordered_map>
#include "StateBase.h"

namespace BOUDAMA
{
	//状態管理用クラス
	template<class T>
	class StateMachine final
	{
	public:
		using StateType = StateBase<T>;

	private:
		//状態一覧のリスト
		std::vector<std::unique_ptr<StateType>> stateVector_;

		//現在の状態
		int currentState_;



	public:
		StateMachine() = default;
		~StateMachine() = default;

		//void Step(void)
		//{
		//	if (!currentState_)
		//	{
		//		return;
		//	}

		//	//現在の状態の処理
		//	currentState_->Step();

		//	if (currentState_->CanTransitionToNextState())
		//	{
		//		ChangeState();

		//		if (currentState_)
		//		{
		//			//遷移後の状態の初期化
		//			currentState_->Init();

		//			return;
		//		}
		//	}
		//}

		////状態を新しく登録する
		//void Register(T name, const std::shared_ptr<StateBase<T>>& state)
		//{
		//	//stateMap_.insert(std::make_pair(name, state));

		//	stateVector_.emplace_back(std::make_unique<StateBase<T>>());
		//	stateVector_[0];

		//}

		////最初から始める状態を設定
		//void SetStartState(T startStateName)
		//{
		//	const auto& it = stateMap_.find(registerName);

		//	if (it == stateMap_.end())
		//	{
		//		return;
		//	}

		//	currentState_ = it->second.lock();

		//	currentState_->Init();
		//}

		////状態を変更する
		//void ChangeState(void)
		//{
		//	const auto& it = stateMap_.find(currentState_->GetNextState());

		//	if (it == stateMap_.end())
		//	{
		//		return;
		//	}

		//	currentState_ = it->second.lock();
		//}

		////登録したものを削除する
		//void Deregistration(T eraseStateName)
		//{
		//	const auto& it = stateMap_.find(eraseStateName);

		//	if (it == stateMap_.end())
		//	{
		//		return;
		//	}

		//	stateMap_.erase(it);
		//}

		////すべての登録を削除する
		//void AllDeregistration(void)
		//{
		//	stateMap_.clear();
		//}

	};
}
