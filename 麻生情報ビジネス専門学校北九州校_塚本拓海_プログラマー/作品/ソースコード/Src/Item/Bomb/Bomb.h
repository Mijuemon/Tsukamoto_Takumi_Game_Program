#pragma once

#include <memory>
#include "Item/ItemBase.h"
#include "Item/ItemParameter.h"

namespace BOUDAMA
{
	//���e�N���X
	class Bomb final : public ItemBase
	{
	private:
		//��ԊǗ��p�ϐ�
		BOMB::STATE state_;

		//��������܂ł̎���
		int countExplodeTimeLimit_;

		//��������
		int explosionTime_;

	public:
		//�R���X�g���N�^
		Bomb() { countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT; explosionTime_ = 0; }

		//�f�X�g���N�^
		~Bomb() {}

		//�����������֐�
		void Init(void) override;

		//�s�������֐�
		void Step(void) override;

		//�`�揈���֐�
		void Draw(void) override;

		//�o�������֐�
		void AppearanceRequest(void) override;

		//�A�C�e���̌��ʎ��s
		void EffectExecute(const std::shared_ptr<Object>& targetObject);

		//�����������̏���
		void HitCalculation(void) override;

		//���e�ɉ΂�����
		void IgniteBomb(void);

		/// <summary>
		/// ��������܂ł̎��Ԍv���p�ϐ����擾
		/// </summary>
		/// <returns>
		/// ��������܂ł̎���
		/// </returns>
		inline int GetCountExplodeTimeLimit(void) const noexcept { return countExplodeTimeLimit_; }

		/// <summary>
		/// �������Ă��鎞��(�����蔻�肪���鎞��)���v�����Ă���ϐ����擾
		/// </summary>
		/// <returns>
		/// �������Ă���ǂ̂��炢���Ԃ��o���Ă��邩
		/// </returns>
		inline int GetExplosionTime(void) const noexcept { return explosionTime_; }

		inline void SetOwnerPos(const Vector3D& pos) noexcept { pos_ = pos; }

	private:
		//�ʏ���
		void MoveNormal(void);

		//�������
		void MoveIgnition(void);

		//�������
		void MoveExplosion(void);

		//�֐��|�C���^
		const decltype(&Bomb::MoveNormal) MoveFunctionPointer[BOMB_STATE::NUM]
		{
			&Bomb::MoveNormal,
			&Bomb::MoveIgnition,
			&Bomb::MoveExplosion
		};
	};
}
