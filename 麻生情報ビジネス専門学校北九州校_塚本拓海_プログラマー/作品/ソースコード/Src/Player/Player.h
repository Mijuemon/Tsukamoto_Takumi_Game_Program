#pragma once

#include <memory>
#include "Object/Object.h"
#include "Bullet/BulletManager.h"
#include <Substance/SubstanceBase.h>
#include "Combo/Combo.h"
#include "Player2DEffect.h"
#include "Player3DEffect.h"

namespace BOUDAMA
{
	//�v���C���[�N���X
	class Player final : public Object
	{
	private:
		//��������������ۑ�����ϐ�
		std::vector<std::weak_ptr<SubstanceBase>> attachedSubstances_;

		//�v���C���[�Ɋւ���摜��`�悷��
		Player2DEffect player2dEffect_;

		//�v���C���[�Ɋւ���3D�G�t�F�N�g��`�悷��
		Player3DEffect player3dEffect_;

		//�R���{�v���p�ϐ�
		Combo combo_;

		//���񂾂Ƃ��Ɏ��Ԍv������Ƃ��Ɏg���ϐ�
		int deathTimeCount_;

	public:
		//�R���X�g���N�^
		Player();

		//�f�X�g���N�^
		~Player();

		//�����������֐�
		void Init(void) override;

		//�ǂݍ��ݏ����֐�
		void Load(void) override;

		//�s�������֐�
		void Step(void) override;

		//�`�揈���֐�
		void Draw(void) override;

		//�j�������֐�
		void Fin(void) override;

		//�����蔻�菈��
		void HitCalculation(void) override;

		//�ړ��v�Z����
		void MoveCalculation(void);

		//��]�v�Z����
		void RotateCalculation(void);

		//�^�[�{�𗭂߂�
		void TurboCharge(void);

		//���S�C�x���g
		void DeathEvent(void);

		//���S�C�x���g���I�������
		bool IsEndDeathEvent(void);

		//���G���ǂ���
		bool IsInvincible(void);

		//�������������擾
		inline std::vector<std::weak_ptr<SubstanceBase>>& GetAttachedSubstance(void) { return attachedSubstances_; }

		//�������������ǉ�
		inline void AddAttachedSubstance(const std::shared_ptr<SubstanceBase>& substance) { attachedSubstances_.emplace_back(substance); }

		//�R���{�ǉ�
		inline void AddComboNum(void) { combo_.AddComboNum(); }
	};
}
