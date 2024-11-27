#pragma once

#include "EnemyBase.h"
#include "Item/Bomb/Bomb.h"

namespace BOUDAMA
{
	//���e���N���X
	class EnemyBomber : public EnemyBase
	{
	private:
		//�Q�Ƃ��锚�e
		std::weak_ptr<Bomb> bomb_;

		//�ړ�����p�x�؂�ւ����Ԍv��
		int moveAngleChangeCount_;

		//�v���C���[�𔭌������Ƃ��̔������Ԍv���p�ϐ�
		int findOutReactionCount_;

		//�U������
		int attackChargeCount_;

	public:
		//�R���X�g���N�^
		EnemyBomber();

		//�f�X�g���N�^
		~EnemyBomber();

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
