#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//�����_���E�H�[�N���
	class RandomWalk : public EnemyState<EnemyBase>
	{
	private:
		//�ړ����x
		float moveSpeed_;

		//�ő�ړ����x
		float maxMoveSpeed_;

		//�ő�ړ����x�̓��
		float squareMaxMoveSpeed_;

		//�ړ��\�Ȕ͈�
		float maxMovementRange_;

		//�����x�N�g����ς��鎞�Ԃ��v��ϐ�
		int directionChangeTimeCount_;

		//�����x�N�g����ύX����Ԋu
		int directionChangeInterval_;

	public:
		explicit constexpr RandomWalk(const auto stateName, float moveSpeed, float maxMoveSpeed,
			float maxMovementRange, int moveAngleChangeCount_, int directionChangeInterval) :
			EnemyState(stateName), moveSpeed_(moveSpeed), maxMoveSpeed_(maxMoveSpeed), squareMaxMoveSpeed_(maxMoveSpeed * maxMoveSpeed),
			maxMovementRange_(maxMovementRange), directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}

		explicit constexpr RandomWalk(const auto myState, const auto nextState, float moveSpeed, float maxMoveSpeed,
			float maxMovementRange, int moveAngleChangeCount_, int directionChangeInterval) :
			EnemyState(myState, nextState), moveSpeed_(moveSpeed), maxMoveSpeed_(maxMoveSpeed), squareMaxMoveSpeed_(maxMoveSpeed * maxMoveSpeed), 
			maxMovementRange_(maxMovementRange), directionChangeTimeCount_(0), directionChangeInterval_(directionChangeInterval) {}


		~RandomWalk() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
