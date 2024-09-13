#pragma once

namespace SOUND
{
	//���ԍ����
	enum class BGM
	{
		//�^�C�g�����
		TITLE,
		//�Q�[���v���C��
		PLAY,

		//����
		NUM
	};

	//���ʉ�
	enum class SE
	{
		//���������̌��ʉ�
		ATTACHED = BGM::NUM,

		//�_���[�W���󂯂��Ƃ��̌��ʉ�
		DAMAGE,

		//�v���C���[�����񂾂Ƃ��̌��ʉ�
		PLAYER_DEATH,

		//�G�����񂾂Ƃ��̌��ʉ�
		ENEMY_DEATH,

		//����{�^�����������Ƃ��̌��ʉ�
		DESIDE,

		//�Q�[�����I��������̌��ʉ�
		GAME_FINISH,

		//�L�����Z����
		CANCEL,

		//����
		NUM
	};

	//���ʉ��̍��v
	constexpr int ALL_SOUND_NUM = static_cast<int>(SE::NUM);

	//�����p�X
	constexpr char PATH[] = "Data/Sound/SoundList.csv";

}