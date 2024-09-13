#pragma once

#include "Vector/Vector3D.h"
#include <type_traits>

//�G�̒�`���

//�_���}
namespace ENEMY
{
	//�G�̃p�X
	constexpr char PATH[] = "Data/Model/Enemy/darumaEnemy.x";

	//�G�̍ő吔
	constexpr int MAX_NUM = 40;

	//�n�[�h���[�h���G���h���X���[�h�̓G�̍ő吔
	constexpr int HARD_MAX_NUM = 80;

	//���a
	constexpr float RADIUS = 50.0f;

	//����
	constexpr float SPEED = 7.5f;

	//�d��
	constexpr float GRAVITY = 7.5f;

	//�����ʒu
	constexpr Vector3D INIT_POS = { 0.0f,100.0f,3750.0f };

	//�G��X���̏����ʒu
	constexpr float INIT_POS_X = 500.0f;

	//�G��Z���̏����ʒu
	constexpr float INIT_POS_Z = 3150.0f;

	//X����Z���ōs����ő�̈ʒu
	constexpr float MAX_POS_X_Z = 7000.0f;

	//�G��X���̏o���͈�
	constexpr int INIT_MAX_APPEAR_RANGE_X = 1000;

	//�G��Z���̏o���͈�
	constexpr int INIT_MAX_APPEAR_RANGE_Z = 100;

	//�ZF���Ƃɏo������
	constexpr int APPEAR_MAX_TIME = 30;

	//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
	constexpr unsigned int ADD_SCORE_NUM = 300;

}

//����
namespace ENEMY_MONSTER
{
	//�G�̃p�X
	constexpr char PATH[] = "Data/Model/Enemy/MonsterEnemy.x";

	//�G�̍ő吔
	constexpr int MAX_NUM = 5;

	//�n�[�h���[�h���G���h���X���[�h�̓G�̍ő吔
	constexpr int HARD_MAX_NUM = 10;

	//�ړ�����p�x�؂�ւ�����
	constexpr int MOVEANGLE_CHANGE_MAX_NUM = 180;

	//�ړ�����p�x�؂�ւ�����
	constexpr int REACTION_MAX_TIME = 120;

	//�U�����ߍő厞��
	constexpr int ATTACK_CHARGE_MAX_TIME = 60;

	//�U�����Ԃ̍ő�l
	constexpr int ATTACK_MAX_TIME = 60;

	//�ZF���Ƃɏo������
	constexpr int APPEAR_MAX_TIME = 90;

	//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
	constexpr unsigned int ADD_SCORE_NUM = 500;

	//X����Z���ōs����ő�̈ʒu
	constexpr float MAX_POS_X_Z = 7000.0f;

	//�n�ʂɒ��n�����Ƃ��̈ʒu
	constexpr float GROUND_POS_Y = 35.0f;

	//�m�b�N�o�b�N�̂Ƃ��ɁZ���㏸������
	constexpr float KNOCKBACK_Y_POWER = 6.5f;

	//���a
	constexpr float RADIUS = 80.0f;

	//����
	constexpr float SPEED = 1.25f;

	//�ǂ������鑬��
	constexpr float CHASE_SPEED = 6.75f;

	//�U������Ƃ��̑���
	constexpr float ATTACK_SPEED = 8.5f;

	//�ő�̑���
	constexpr float MAX_SPEED = 30.0f;

	//�G�𔭌��ł���͈�
	constexpr float FIND_OUT_RANGE = 800.0f;

	//�G�𔭌��ł���͈͂̓��
	constexpr float SQUARE_FIND_OUT_RANGE = FIND_OUT_RANGE * FIND_OUT_RANGE;


	//������ʒu
	constexpr Vector3D INIT_POS = { 0.0f,5.0f,1450.0f };

}

//���e��
namespace ENEMY_BOMBER
{
	//�G�̃p�X
	constexpr char PATH[] = "Data/Model/";

	//�G�̍ő吔
	constexpr int MAX_NUM = 0;

	//�n�[�h���[�h���G���h���X���[�h�̓G�̍ő吔
	constexpr int HARD_MAX_NUM = 0;


	//�ړ�����p�x�؂�ւ�����
	constexpr int MOVEANGLE_CHANGE_MAX_NUM = 180;

	//�ړ�����p�x�؂�ւ�����
	constexpr int REACTION_MAX_TIME = 120;


	//�U�����ߍő厞��
	constexpr int ATTACK_CHARGE_MAX_TIME = 90;

	//�ZF���Ƃɏo������
	constexpr int APPEAR_MAX_TIME = 90;


	//�|���ꂽ�Ƃ��ɃX�R�A�ɉ��Z�����_��
	constexpr unsigned int ADD_SCORE_NUM = 550;

	//�����ʒu
	constexpr Vector3D INIT_POS = { 0.0f,10.0f,3150.0f };

	//X����Z���ōs����ő�̈ʒu
	constexpr float MAX_POS_X_Z = 7000.0f;

	//1�t���[���ňړ����鑬��
	constexpr float SPEED = 1.25f;

	//�ő�̑���
	constexpr float MAX_SPEED = 30.0f;

	//�ǂ������鑬��
	constexpr float CHASE_SPEED = 3.75f;


	//���a
	constexpr float RADIUS = 50.0f;


	//�G�𔭌��ł���͈�
	constexpr float FIND_OUT_RANGE = 850.0f;

	//�G�𔭌��ł���͈͂̓��
	constexpr float SQUARE_FIND_OUT_RANGE = FIND_OUT_RANGE * FIND_OUT_RANGE;


	//�G�𔭌������Ƃ��ɋ߂Â��ŏ��͈̔�
	constexpr float CHASE_MIN_RANGE = 750.0f;

	//�G�𔭌������Ƃ��ɋ߂Â��ŏ��͈̔͂̓��
	constexpr float SQUARE_CHASE_MIN_RANGE = CHASE_MIN_RANGE * CHASE_MIN_RANGE;

}

/*
	�G�Ǘ��N���X�̏��
	�����艺��
	namespace �Z�Z(�G�̏��)
	�������ƃG���[���N����̂Œǉ����Ȃ�
*/
namespace ENEMY_MANAGER
{
	//�Q�[���J�n���ɗN�����鐔
	constexpr int INIT_APPEAR_NUM = 15;

	//�G�́ZF���Ƃɏo������
	constexpr int MAX_APPEAR_TIME = 20;

	//�G�̏�ɏo������u�I�v�̉摜�̃p�X
	constexpr char EXCLAMATION_PATH[] = { "Data/Image/Exclamation_Mark.PNG" };

	//�G�̏�ɏo������u�I�v�̋���(X��,Y��,Z��)
	constexpr Vector3D ADD_EXCLAMATION_DISTANCE = { 0.0f, 75.0f, 0.0f };


	//�G�ꗗ
	enum class ENEMY_LIST
	{
		NORMAL,
		MONSTER,
		BOMBER,

		ALL_NUM
	};

	//�ʏ�̓G�̐�
	constexpr int MAX_NUM_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
	{
		ENEMY::MAX_NUM,
		ENEMY_MONSTER::MAX_NUM,
		ENEMY_BOMBER::MAX_NUM
	};

	//�n�[�h���[�h���G���h���X���[�h�̓G�̐�
	constexpr int HARD_MAX_NUM_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
	{
		ENEMY::HARD_MAX_NUM,
		ENEMY_MONSTER::HARD_MAX_NUM,
		ENEMY_BOMBER::HARD_MAX_NUM
	};

	//�G�̏o���Ԋu�ꗗ�\
	constexpr int APPEAR_MAX_TIME_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
	{
		ENEMY::APPEAR_MAX_TIME,
		ENEMY_MONSTER::APPEAR_MAX_TIME,
		ENEMY_BOMBER::APPEAR_MAX_TIME
	};

	//�G�̃p�X�ꗗ�\
	constexpr const char* PATH_LIST[static_cast<int>(ENEMY_LIST::ALL_NUM)] =
	{
		ENEMY::PATH,
		ENEMY_MONSTER::PATH,
		ENEMY_BOMBER::PATH
	};



	//�͈�for���ł�������
	constexpr ENEMY_LIST begin(ENEMY_LIST) { return ENEMY_LIST::NORMAL; }

	constexpr ENEMY_LIST end(ENEMY_LIST) { return ENEMY_LIST::ALL_NUM; }

	constexpr ENEMY_LIST operator*(ENEMY_LIST dir) { return dir; }

	constexpr ENEMY_LIST operator++(ENEMY_LIST& dir)
	{
		return dir = ENEMY_LIST(std::underlying_type<ENEMY_LIST>::type(dir) + 1);
	}

}
