#include "Player/PlayerEffect.h"
#include <DxLib.h>
#include "PlayerParameter.h"
#include <FileLoader/CSVFileLoader.h>
#include <Effekseer/Effekseer.h>

#define IMAGE PLAYER_EFFECT::IMAGE

//�R���X�g���N�^
PlayerEffect::PlayerEffect()
{
	concentrationLineIndex_ = 0;
	damageEffectAlpha_ = 0;
	chargeEffectHandle = 0;
	turboEffectHandle = 0;
}

//�f�X�g���N�^
PlayerEffect::~PlayerEffect()
{

}

//�����������֐�
void PlayerEffect::Init(void)
{
	concentrationLineIndex_ = IMAGE::CONCENTRATION_LINE_1;
	damageEffectAlpha_ = 0;
	chargeEffectHandle = 0;
	turboEffectHandle = 0;
}

//�ǂݍ��ݏ����֐�
void PlayerEffect::Load(void)
{
	CSV_LOADER::LoadHandle(PLAYER_EFFECT::PATH, handles_);
}

//�s�������֐�
void PlayerEffect::Step(void)
{
	if (damageEffectAlpha_ > 0)
	{
		damageEffectAlpha_ -= 3;
	}
}

//�`�揈���֐�
void PlayerEffect::HPDraw(int playerHP)
{
	//HP�ɉ�����HP�o�[�̒�����ς���
	for (int HP = 0; HP < playerHP; ++HP)
	{
		DrawRotaGraph(PLAYER_EFFECT::HP_POS_X + PLAYER_EFFECT::HP_SIZE * HP, PLAYER_EFFECT::HP_POS_Y, 1.0f, 0.0f, handles_[IMAGE::HP], true);
	}

	//�uHP�v�̕����̉摜�\��
	DrawRotaGraph(PLAYER_EFFECT::HP_CHARA_POS_X, PLAYER_EFFECT::HP_CHARA_POS_Y, 0.5f, 0.0f, handles_[IMAGE::HP_CHARA], true);

}

//�W�����`��֐�
void PlayerEffect::LineDraw(void)
{
	//�W�����`��
	DrawGraph(0, 0, handles_[concentrationLineIndex_], true);

	//�W�����̌J��Ԃ�����
	concentrationLineIndex_ >= IMAGE::CONCENTRATION_LINE_END ? 
		concentrationLineIndex_ = IMAGE::CONCENTRATION_LINE_1 : ++concentrationLineIndex_;
}

//�_���[�W���󂯂����̃G�t�F�N�g�`��֐�
void PlayerEffect::DamageDraw(void)
{
	if (damageEffectAlpha_ > 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, damageEffectAlpha_);
		DrawGraph(0, 0, handles_[IMAGE::DAMAGE], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//�j�������֐�
void PlayerEffect::Fin(void)
{
	for (auto&& image : handles_)
	{
		DeleteGraph(image);
	}
}

void PlayerEffect::DamageEffectRequest(void)
{
	damageEffectAlpha_ = 255;
}

void PlayerEffect::ChargeEffectRequest(const Vector3D& appearPos, float rotY)
{
	chargeEffectHandle = CEffekseerCtrl::Request(3, appearPos, false);
	CEffekseerCtrl::SetRot(chargeEffectHandle, VECTOR(0.0f, rotY, 0.0f));
}

void PlayerEffect::TurboEffectRequest(const Vector3D& appearPos, float rotY)
{
	turboEffectHandle = CEffekseerCtrl::Request(4, appearPos, false);
	CEffekseerCtrl::SetRot(turboEffectHandle, VECTOR(0.0f, rotY, 0.0f));
	CEffekseerCtrl::SetPosition(turboEffectHandle, appearPos);
}
