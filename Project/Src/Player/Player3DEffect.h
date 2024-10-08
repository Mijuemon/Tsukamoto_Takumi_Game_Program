#pragma once

#include <vector>
#include <type_traits>

#include <Vector/Vector3D.h>
#include "Player.h"

//�v���C���[�Ɋւ���3D�G�t�F�N�g��`�悷��N���X
class Player3DEffect
{
private:
	//�Q�Ƃ���v���C���[�̃|�C���^
	Player* playerPointer_;

	//�Ăяo�����G�t�F�N�g�̃n���h����ۑ�����ϐ�
	std::vector<int> effectHandle_;

	//�G�t�F�N�g���Ăяo���Ƃ��Ɏg���ϐ�
	std::vector<int> effectCallNum_;

public:
	//�R���X�g���N�^
	Player3DEffect(Player* const player) : playerPointer_(player) {};

	//�f�X�g���N�^
	~Player3DEffect() {};

	//�����������֐�
	void Init(void);

	//�ǂݍ��ݏ����֐�
	void Load(void);

	//�s�������֐�
	void Step(void);

	//�`�揈���֐�
	void Draw(void);

	//�j�������֐�
	void Fin(void);

	//�G�t�F�N�g�\��
	void EffectRequest(EFFECT_3D effectNum);
};

//�G�t�F�N�g�z��̓Y����
enum EFFECT_3D
{
	CHARGE,
	ACCELERATOR,
};

//�G�t�F�N�g���̂�ۑ����Ă���z��̓Y�������Ăяo�����Ɏg���ԍ�
enum class EFFECT_CALL
{
	CHARGE = EFFECT::CHARGE,
	ACCELERATOR = EFFECT::ACCELERATOR,

	ALL_NUM
};

constexpr EFFECT_CALL begin(EFFECT_CALL) { return EFFECT_CALL::CHARGE; }

constexpr EFFECT_CALL end(EFFECT_CALL) { return EFFECT_CALL::ALL_NUM; }

constexpr EFFECT_CALL operator*(EFFECT_CALL dir) { return dir; }

constexpr EFFECT_CALL operator++(EFFECT_CALL& dir)
{
	return dir = EFFECT_CALL(std::underlying_type_t<EFFECT_CALL>(dir) + 1);
}
