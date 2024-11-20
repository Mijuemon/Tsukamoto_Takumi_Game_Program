#pragma once

#include <memory>
#include <vector>

#include "Object/Object.h"
#include "StateMachine/StateMachine.h"
#include "Enemy/State/EnemyState.h"

namespace BOUDAMA
{
	namespace ENEMY
	{
		//�G�̏��
		enum class STATE
		{
			//�v���C���[�T��
			SEARCH,

			//�v���C���[����
			FIND_OUT,

			//�v���C���[�ǐ�
			CHASE,

			//�U������
			CHARGE,

			//�U����
			ATTACK,

			//�m�b�N�o�b�N
			KNOCK_BACK,

			//����
			NUM
		};

		//������΂����Ƃ��ɑ��x�Ɋ|����(�X�J���[�{����)�W��
		constexpr float KNOCK_BACK_BOOST = 1.75f;
	}


	//�S�Ă̓G�̊��N���X
	class EnemyBase : public Object
	{
	protected:
		using StateMachineType = StateMachine<ENEMY_STATE, EnemyBase>;

		//���
		ENEMY::STATE state_;
		//��ԑJ�ڗp�ϐ�
		std::unique_ptr<StateMachineType> stateMachine_;

		//�_���Ă��镨�̂̈ʒu
		Vector3D targetPosition_;

		//������΂���ď�����܂ł̎��Ԍv��
		int knockBackTimeCount_;

		//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
		int scoreNum_;

		//�������Ă��邩���肷��t���O
		bool isInCollision_;

	public:
		//�R���X�g���N�^
		constexpr EnemyBase() : scoreNum_(0), isInCollision_(false) {}

		//�f�X�g���N�^
		virtual ~EnemyBase() = default;

		//�s�������֐�
		virtual void Step(const Vector3D& playerPos);

		//�ǂݍ��ݏ����֐�
		virtual void Load(int originalHandle);

		//�o�������֐�
		virtual void AppearanceRequest(void);

		virtual void HitCalculation(void) override;

		virtual void SetKnockBack(const Vector3D& hitObjectVelocity);

		//��Ԏ擾
		inline ENEMY::STATE GetState(void) const { return state_; }

		inline Vector3D GetTargetPosition(void) const noexcept { return targetPosition_; }

		inline void SetTargetPosition(const Vector3D& targetPos) noexcept { targetPosition_ = targetPos; }

		//�|���ꂽ���ɉ��Z�����_���擾
		inline int GetScoreNum(void) const { return scoreNum_; }

		inline bool IsInCollision(void) const noexcept { return isInCollision_; }
		inline bool SetIsInCollision(bool isInCollision) noexcept { isInCollision_ = isInCollision; }

		void SetStateMachineOwner(const auto& owner)
		{
			stateMachine_->SetAllStateOwner(owner);
		}
	};
}
