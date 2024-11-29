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
		//ENEMY::STATE state_;
		//��ԑJ�ڗp�ϐ�
		std::unique_ptr<StateMachineType> stateMachine_;

		//�_���Ă��镨�̂̈ʒu
		Vector3D targetPosition_;

		//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
		int scoreNum_;

		//�����蔻��L���t���O
		bool isCollisionEnabled_;

		//���G���H
		bool isInvincible_;

	public:
		//�R���X�g���N�^
		constexpr EnemyBase() : scoreNum_(0), isCollisionEnabled_(true), isInvincible_(false) {}

		//�f�X�g���N�^
		virtual ~EnemyBase() = default;

		//�s�������֐�
		virtual void Step(const Vector3D& playerPos);

		//�ǂݍ��ݏ����֐�
		virtual void Load(int originalHandle);

		//�o�������֐�
		virtual void AppearanceRequest(void);

		virtual void HitCalculation(void) override;

		virtual void DeathCalculation(const Vector3D& hitObjectVelocity);

		//��Ԏ擾
		//inline ENEMY::STATE GetState(void) const { return state_; }

		inline Vector3D GetTargetPosition(void) const noexcept { return targetPosition_; }

		inline void SetTargetPosition(const Vector3D& targetPos) noexcept { targetPosition_ = targetPos; }

		//�|���ꂽ���ɉ��Z�����_���擾
		inline int GetScoreNum(void) const { return scoreNum_; }

		inline bool IsCollisionEnabled(void) const noexcept { return isCollisionEnabled_; }
		inline void SetIsCollisionEnabled(bool isInCollision) noexcept { isCollisionEnabled_ = isInCollision; }

		//���G���H
		inline bool IsInvincible(void) const noexcept { return isInvincible_; };
		inline void SetIsInvincible(bool isInvincible) noexcept { isInvincible_ = isInvincible; }

		void SetStateMachineOwner(const auto& owner)
		{
			stateMachine_->SetAllStateOwner(owner);
		}
	};
}
