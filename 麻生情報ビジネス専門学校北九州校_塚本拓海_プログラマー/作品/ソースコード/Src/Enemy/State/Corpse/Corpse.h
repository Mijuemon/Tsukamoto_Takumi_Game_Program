#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//���̏��
	class Corpse final : public EnemyState<EnemyBase>
	{
	private:
		//���̏�ԂŐ�����΂���Ă��鎞�Ԃ��v������ϐ�
		int timeCount_;

		//���̏�ԂŐ�����΂����ő厞��
		const int maxTimeCount_;

	public:
		explicit constexpr Corpse(const auto stateName, int maxTime) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}
		explicit constexpr Corpse(const auto myState, const auto nextState, int maxTime) : EnemyState(myState, nextState), timeCount_(0), maxTimeCount_(maxTime) {}

		~Corpse() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};

}
