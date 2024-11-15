#pragma once

#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	class KnockBack : public EnemyState
	{
	private:
		//�m�b�N�o�b�N���Ă��鎞�Ԃ��v������ϐ�
		int timeCount_;

		//�ő�m�b�N�o�b�N�p������
		int maxTimeCount_;

	public:
		explicit constexpr KnockBack(const auto stateName, int maxTime) : EnemyState(stateName), timeCount_(0), maxTimeCount_(maxTime) {}

		~KnockBack() noexcept override = default;

		//�����������֐�
		void Enter(void) override;

		//�s�������֐�
		void Execute(void) override;
	};
}
