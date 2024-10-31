#pragma once

#include <vector>
#include <memory>
#include "EnemyParameter.h"
#include "Player/Player.h"
#include "EnemyBase.h"
#include <Item/ItemManager.h>
#include <Scene/Scene.h>

namespace BOUDAMA
{
	//�G���Ǘ��N���X
	class EnemyManager
	{
	private:
		//�G�̔z��
		std::vector<std::shared_ptr<EnemyBase>> enemies_;

		//�G�o�����Ԍv��
		int appearCountTime_[static_cast<int>(ENEMY_MANAGER::ENEMY_LIST::ALL_NUM)];

		//�u�I�v�̉摜�n���h��
		int exclamationMarkHandle_;

		//���S��
		int deathCount_;

		//�t�B�[�o�[�^�C���v��
		int feverTimeCount_;

		//�G�����X�Əo������u�t�B�[�o�[�^�C���v���ǂ���
		bool isFeverTime_;

	public:
		//�R���X�g���N�^
		EnemyManager();

		//�f�X�g���N�^
		~EnemyManager();

		//�����������֐�
		void Init(const SCENE difficulty);

		//�ǂݍ��ݏ����֐�
		void Load(const SCENE difficulty);

		//�s�������֐�
		void Step(const Vector3D& playerPos);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);

		//�G���擾
		inline std::vector<std::shared_ptr<EnemyBase>>& GetEnemy(void) { return enemies_; }

		inline int GetEnemyDeathCount(void) const { return deathCount_; }

		inline void AddEnemyDeathCount(void) { ++deathCount_; }

	private:
		//�o��������Z�߂��֐�
		void AppearanceProcess(void);
	};
}
