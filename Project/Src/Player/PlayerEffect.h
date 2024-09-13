#pragma once

#include <vector>
#include "Vector/Vector3D.h"

namespace PLAYER_EFFECT
{
	constexpr char PATH[] = "Data/Image/Player/ImageList.csv";
		
	//�摜�p
	enum IMAGE
	{
		//HP�\���p�̃n���h��
		HP,

		//"HP"�̉摜�̃n���h��
		HP_CHARA,

		//�W����
		CONCENTRATION_LINE_1,
		CONCENTRATION_LINE_2,
		CONCENTRATION_LINE_3,
		CONCENTRATION_LINE_END,

		//�_���[�W���󂯂��Ƃ��ɉ�ʂɕ\������_���[�W�G�t�F�N�g�摜
		DAMAGE,

		//�摜�̑���
		ALL_NUM
	};

	//HP�o�[�̑傫��
	constexpr int HP_SIZE = 16;

	//HP�o�[�̕\���ʒu
	constexpr int HP_POS_X = 96;
	constexpr int HP_POS_Y = 32;

	//HP�̕\���ʒu
	constexpr int HP_CHARA_POS_X = 48;
	constexpr int HP_CHARA_POS_Y = 32;
}

//�v���C���[�Ɋւ���摜��`�悷��N���X
class PlayerEffect
{
private:
	//�摜�ꗗ�\
	std::vector<int> handles_;

	//���`�悵�Ă���W�����̔ԍ�
	int concentrationLineIndex_;

	//�_���[�W�摜�̃��l
	int damageEffectAlpha_;

	//�`���[�W��ԃG�t�F�N�g�̃n���h��
	int chargeEffectHandle;

	//�^�[�{��ԃG�t�F�N�g�̃n���h��
	int turboEffectHandle;

public:
	//�R���X�g���N�^
	PlayerEffect();
	//�f�X�g���N�^
	~PlayerEffect();

	//�����������֐�
	void Init(void);

	//�ǂݍ��ݏ����֐�
	void Load(void);

	//�s�������֐�
	void Step(void);

	//�`�揈���֐�
	void HPDraw(int playerHP);
	void LineDraw(void);
	void DamageDraw(void);

	//�j�������֐�
	void Fin(void);

	void DamageEffectRequest(void);
	void ChargeEffectRequest(const Vector3D& appearPos, float rotY);
	void TurboEffectRequest(const Vector3D& appearPos, float rotY);

};
