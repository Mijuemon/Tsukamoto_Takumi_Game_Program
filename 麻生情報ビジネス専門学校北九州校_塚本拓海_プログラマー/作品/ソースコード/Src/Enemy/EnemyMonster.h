#pragma once

#include "EnemyBase.h"

namespace BOUDAMA
{
	//�G�N���X
	class EnemyMonster : public EnemyBase
	{
	private:
		//�ړ�����p�x�؂�ւ����Ԍv���p�ϐ�
		int moveAngleChangeCount_;

		//�v���C���[�𔭌������Ƃ��̔������Ԍv���p�ϐ�
		int findOutReactionCount_;

		//�U�����J�n����܂ł̎��Ԍv���p�ϐ�
		int attackChargeCount_;

		//�U�����Ԍv���p�ϐ�
		int attackTimeCount_;

	public:
		//�R���X�g���N�^
		EnemyMonster();

		//�f�X�g���N�^
		~EnemyMonster() override;

		//�����������֐�
		void Init(void) override;

		//�s�������֐�
		void Step(const Vector3D& playerPos) override;

		//�`�揈���֐�
		void Draw(void) override;

		//�o�������֐�
		void AppearanceRequest(void) override;
	};
}
