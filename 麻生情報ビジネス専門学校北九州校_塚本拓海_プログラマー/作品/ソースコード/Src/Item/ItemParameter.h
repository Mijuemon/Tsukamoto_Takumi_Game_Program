#pragma once

#include "Vector/Vector3D.h"

namespace BOUDAMA
{
	namespace BOMB
	{
		//�摜�p�X
		constexpr char PATH[] = "Data/Model/Bomb/Beta_Bomb.x";

		//�����ꂽ�Ƃ��ɏ�Ɉړ�������l
		constexpr Vector3D HELD_UP_DISTANCE = { 0.0f,50.0f,0.0f };

		//�n�ʂ̈ʒu
		constexpr float GROUND_POS = 20.5f;

		//�d��
		constexpr float GRAVITY = 5.75f;

		//�����̑���
		constexpr float THROW_SPEED = 20.0f;

		//���a
		constexpr float RADIUS = 55.0f;

		//�����̉��̔��a
		constexpr float EXPLODE_RADIUS = 300.0f;

		//������ʒu
		constexpr float INIT_POS_X_Z = -1000.0f;

		//X����Z���ōs����ő�̈ʒu
		constexpr float MAX_POS_X_Z = 7000.0f;

		//�U����
		constexpr int ATTACK_POWER = 5;

		//�����_���Ŕz�u����Ƃ��ɏ�����ʒu�ɑ����ő�l
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);

		//�����ɏo���ł���ő�l
		constexpr int MAX_NUM = 3;

		//��������܂ł̐�������
		constexpr int MAX_EXPLODE_TIME_LIMIT = 600;

		//�������Ă��鎞��
		constexpr int MAX_EXPLOSION_TIME = 90;

		enum STATE
		{
			NORMAL,
			THROW,
			EXPLOSION,

			NUM
		};
	}

	using BOMB_STATE = BOMB::STATE;


	namespace HEAL
	{
		//�ő吔
		constexpr int MAX_NUM = 3;

		//�񕜂�����l
		constexpr int HEAL_VALUE = 5;

		//�n�ʂ̈ʒu
		constexpr float GROUND_POS = 20.5f;

		//�d��
		constexpr float GRAVITY = 6.0f;

		//������ʒu
		constexpr float INIT_POS_X_Z = -1000.0f;

		//�����_���Ŕz�u����Ƃ��ɏ�����ʒu�ɑ����ő�l
		constexpr int INIT_POS_XZ_RAND_MAX_NUM = 2 * static_cast<int>(-INIT_POS_X_Z);


		//��Ɉړ�������l
		constexpr Vector3D UP_DISTANCE = { 0.0f,60.0f,0.0f };

	}

	namespace ITEM
	{
		enum class ITEM_LIST
		{
			BOMB,

			HEAL,

			ALL_NUM
		};


		constexpr int ITEM_MAX_NUM_LIST[static_cast<int>(ITEM_LIST::ALL_NUM)] =
		{
			BOMB::MAX_NUM,
			HEAL::MAX_NUM
		};
	}
}
