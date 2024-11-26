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
		const int maxReactionTimeCount_;

		//�u�I�v�̉摜��\������ۂ̋���
		const Vector3D exclamationMarkDistance_;

	public:
		explicit constexpr FindOut(const auto stateName, int maxTime, Vector3D exclamationMarkDistance) :
			EnemyState(stateName), reactionTimeCount_(0), maxReactionTimeCount_(maxTime), exclamationMarkDistance_(exclamationMarkDistance) {}

		explicit constexpr FindOut(const auto myState, const auto nextState, int maxTime, Vector3D exclamationMarkDistance) :
			EnemyState(myState, nextState), reactionTimeCount_(0), maxReactionTimeCount_(maxTime), exclamationMarkDistance_(exclamationMarkDistance) {}

		~FindOut() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
