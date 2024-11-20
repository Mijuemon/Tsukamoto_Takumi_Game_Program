#pragma once

#include "Enemy/State/EnemyState.h"
#include "Enemy/EnemyBase.h"

namespace BOUDAMA
{
	//�m�b�N�o�b�N���
	class KnockBack : public EnemyState<EnemyBase>
	{
	private:
		//�m�b�N�o�b�N���Ă��鎞�Ԃ��v������ϐ�
		int timeCount_;

		//�ő�m�b�N�o�b�N�p������
		int maxTimeCount_;

	public:
		explicit constexpr KnockBack(const auto stateName, int maxTime) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}
		explicit constexpr KnockBack(const auto myState, const auto nextState, int maxTime) : EnemyState(myState, nextState), timeCount_(0), maxTimeCount_(maxTime) {}

		~KnockBack() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};

	namespace KNOCK_BACK
	{
		constexpr float SPEED = 1.0f;
	}
}
