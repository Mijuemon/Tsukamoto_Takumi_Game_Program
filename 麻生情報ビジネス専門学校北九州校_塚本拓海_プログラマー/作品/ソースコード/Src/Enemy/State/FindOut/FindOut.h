#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	class FindOut : public EnemyState<EnemyBase>
	{
	private:
		//��Ԃ̎��Ԃ��v������ϐ�
		int reactionTimeCount_;

		//�ő�p������
		int maxReactionTimeCount_;

		//�u�I�v�̉摜�n���h��
		int exclamationMarkHandle_;

	public:
		explicit constexpr FindOut(const auto stateName, int maxTime) : EnemyState(stateName), reactionTimeCount_(0), maxReactionTimeCount_(maxTime) {}
		explicit constexpr FindOut(const auto myState, const auto nextState, int maxTime) : EnemyState(myState, nextState), reactionTimeCount_(0), maxReactionTimeCount_(maxTime) {}

		~FindOut() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}