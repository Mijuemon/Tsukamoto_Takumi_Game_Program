#include <functional>
#include "DxLib.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "EnemyMonster.h"
#include "EnemyBomber.h"
#include "Player/Player.h"
#include "Common/Common.h"
#include <Input/GamePad/GamePad.h>
#include <Input/InputParameter.h>
#include <Effekseer/Effekseer.h>
#include <Effekseer/EffekseerParameter.h>

namespace BOUDAMA
{
	//�R���X�g���N�^
	EnemyManager::EnemyManager()
	{
		exclamationMarkHandle_ = 0;
		appearCountTime_[0] = 0;
		deathCount_ = 0;
		feverTimeCount_ = 0;
		isFeverTime_ = false;
	}

	//�f�X�g���N�^
	EnemyManager::~EnemyManager()
	{

	}

	//�G��񏉊���
	void EnemyManager::Init(const SCENE difficulty)
	{
		for (auto& countTime : appearCountTime_)
		{
			countTime = 0;
		}

		feverTimeCount_ = 0;

		isFeverTime_ = false;

		enemies_.clear();
		enemies_.shrink_to_fit();

		//�G�ꗗ�Ɛ������@�𑝂₷�����őS�Ă̓G���쐬�ł���悤�ɂ���
		const std::function<std::shared_ptr<EnemyBase>()> enemyList[static_cast<int>(ENEMY_MANAGER::ENEMY_LIST::ALL_NUM)] =
		{
			//�Ԃ��_���}�^�̓G
			[]() { return std::make_shared<Enemy>(); },
			//���̊ۂ������^�̓G
			[]() { return std::make_shared<EnemyMonster>(); },
			//�l�^�̔��e�𓊂���G
			[]() { return std::make_shared<EnemyBomber>(); },
		};

		//���ꂼ��̓G�̍ő吔���A�̈�m�ۂ���
		for (const auto enemyKindNum : ENEMY_MANAGER::ENEMY_LIST())
		{
			//�m�[�}�����[�h�Ȃ�ʏ�̐��A����ȊO�Ȃ瑽������
			int maxEnemyNum =
				(difficulty == SCENE::NORMAL_PLAY) ?
				ENEMY_MANAGER::MAX_NUM_LIST[static_cast<int>(enemyKindNum)] :
				ENEMY_MANAGER::HARD_MAX_NUM_LIST[static_cast<int>(enemyKindNum)];

			//�L���̈�m��
			for (int enemyIndex = 0; enemyIndex < maxEnemyNum; ++enemyIndex)
			{
				const auto& enemy = enemies_.emplace_back(enemyList[static_cast<int>(enemyKindNum)]());
				//������
				enemy->Init();
				enemy->SetStateMachineOwner(enemy);
			}
		}


		//�ŏ��ɓG���o�������Ă���
		for (int appearNum = 0; const auto& enemy : enemies_)
		{
			enemy->AppearanceRequest();
			++appearNum;

			if (ENEMY_MANAGER::INIT_APPEAR_NUM <= appearNum)
			{
				break;
			}
		}
	}

	//�ǂݍ��ݏ����֐�
	void EnemyManager::Load(const SCENE difficulty)
	{
		auto&& enemy = enemies_.begin();

		//���ꂼ��̓G�̍ő吔���A���f���ǂݍ���
		for (const auto enemyKindNum : ENEMY_MANAGER::ENEMY_LIST())
		{
			//�����f���ǂݍ��ݏ���
			const int origineHandle = MV1LoadModel(ENEMY_MANAGER::PATH_LIST[static_cast<int>(enemyKindNum)]);

			//�m�[�}�����[�h�Ȃ�ʏ�̐��A����ȊO�Ȃ瑽������
			int maxEnemyNum =
				(difficulty == SCENE::NORMAL_PLAY ?
					ENEMY_MANAGER::MAX_NUM_LIST[static_cast<int>(enemyKindNum)] :
					ENEMY_MANAGER::HARD_MAX_NUM_LIST[static_cast<int>(enemyKindNum)]);

			//�������f���ǂݍ��ݏ���
			for (int enemyIndex = 0; enemyIndex < maxEnemyNum; ++enemyIndex)
			{
				(*enemy)->Load(origineHandle);

				++enemy;
			}

			MV1DeleteModel(origineHandle);
		}

		exclamationMarkHandle_ = LoadGraph(ENEMY_MANAGER::EXCLAMATION_PATH);

	}

	//�G��������
	void EnemyManager::Step(const Vector3D& playerPos)
	{
		//�s������
		for (const auto& enemy : enemies_)
		{
			enemy->Step(playerPos);
		}

		//�o�������v�Z
		AppearanceCountProcess();

	}

	//�G�����`��
	void EnemyManager::Draw(void)
	{
		//�G�`��
		for (const auto& enemy : enemies_)
		{
			enemy->Draw();

			//�v���C���[������ԂȂ�u�I�v�̉摜��\������
			if (enemy->GetState() == ENEMY::STATE::FIND_OUT)
			{
				DrawBillboard3D(enemy->GetPos() + ENEMY_MANAGER::ADD_EXCLAMATION_DISTANCE, 0.5f, 0.0f, 128.0f, 0.0f, exclamationMarkHandle_, true);
			}
		}
	}

	//�G���j��
	void EnemyManager::Fin(void)
	{
		//�j������
		DeleteGraph(exclamationMarkHandle_);
		exclamationMarkHandle_ = -1;

		//��������
		for (auto&& itr = enemies_.cbegin(); itr != enemies_.cend();)
		{
			//���f���f�[�^������
			(*itr)->Fin();
			//vector�������
			itr = enemies_.erase(itr);
		}

		//�m�ۂ����L���̈���č\�z
		enemies_.clear();
		enemies_.shrink_to_fit();
	}

	//�o��������Z�߂��֐�
	void EnemyManager::AppearanceCountProcess(void)
	{
		if (isFeverTime_)
		{
			AppearanceRequest();

			return;
		}

		//�G�̔z��̓Y�������w���Ƃ��Ɏg���ϐ�
		int enemyArrayIndex = 0;

		//�G�̏o������
		for (const auto enemyKindNum : ENEMY_MANAGER::ENEMY_LIST())
		{
			int kindNum = static_cast<int>(enemyKindNum);

			//���ꂼ��̓G�̎��ɏo������܂ł̎��Ԃ��v������
			++appearCountTime_[kindNum];

			//�o�߂��Ă��Ȃ��Ȃ���s���Ȃ�
			if (appearCountTime_[kindNum] < ENEMY_MANAGER::APPEAR_MAX_TIME_LIST[kindNum])
			{
				//���̓G�̔z��u���b�N�̐擪�ʒu���擾
				enemyArrayIndex += ENEMY_MANAGER::MAX_NUM_LIST[kindNum];

				continue;
			}

			//�v��������
			appearCountTime_[kindNum] = 0;

			//�o�߂��Ă�����
			AppearanceRequest(kindNum, enemyArrayIndex);
		}
	}

	//���ۂɏo��������֐�
	void EnemyManager::AppearanceRequest(int kindNum, int enemyArrayIndex)
	{
		//���ꂼ��̓G�̍ő吔��for�����񂷂��߂Ɍv�Z
		const int lastEnemyArrayIndex = enemyArrayIndex + ENEMY_MANAGER::MAX_NUM_LIST[kindNum];

		//�o����������
		for (int enemyIndex = enemyArrayIndex; enemyIndex < lastEnemyArrayIndex; ++enemyIndex)
		{
			//���łɏo�����Ă���ꍇ�͎��Ɉڂ�
			if (enemies_[enemyIndex]->GetIsActive())
			{
				continue;
			}

			//�G���o��������
			enemies_[enemyIndex]->AppearanceRequest();

			CEffekseerCtrl::Request(EFFECT::ENEMY_SPAWN, enemies_[enemyIndex]->GetPos(), false);

			break;
		}
	}
}
