#include "Player/Player2DEffect.h"
#include <DxLib.h>
#include "Player.h"
#include "PlayerParameter.h"
#include <FileLoader/CSVFileLoader.h>

namespace BOUDAMA
{
	using IMAGE = PLAYER_EFFECT::IMAGE;

	//�����������֐�
	void Player2DEffect::Init(void)
	{
		concentrationLineIndex_ = IMAGE::CONCENTRATION_LINE_1;
		damageEffectAlpha_ = 0;
	}

	//�ǂݍ��ݏ����֐�
	void Player2DEffect::Load(void)
	{
		CSV_LOADER::LoadHandle(PLAYER_EFFECT::PATH, handles_);
	}

	//�s�������֐�
	void Player2DEffect::Step(void)
	{
		if (damageEffectAlpha_ > 0)
		{
			damageEffectAlpha_ -= 3;
		}
	}

	//�`�揈���֐�
	void Player2DEffect::Draw(int playerHP, const Vector3D& velocity)
	{
		//HP�ɉ�����HP�o�[�̒�����ς���
		for (int HP = 0; HP < playerHP; ++HP)
		{
			DrawRotaGraph(PLAYER_EFFECT::HP_POS_X + PLAYER_EFFECT::HP_SIZE * HP, PLAYER_EFFECT::HP_POS_Y, 1.0f, 0.0f, handles_[IMAGE::HP], true);
		}

		//�uHP�v�̕����̉摜�\��
		DrawRotaGraph(PLAYER_EFFECT::HP_CHARA_POS_X, PLAYER_EFFECT::HP_CHARA_POS_Y, 0.5f, 0.0f, handles_[IMAGE::HP_CHARA], true);

		if (velocity.SquareL2Norm() >= PLAYER::KILL_SPEED)
		{
			//�W�����`��
			DrawGraph(0, 0, handles_[concentrationLineIndex_], true);

			//�W�����̌J��Ԃ�����
			concentrationLineIndex_ >= IMAGE::CONCENTRATION_LINE_END ?
				concentrationLineIndex_ = IMAGE::CONCENTRATION_LINE_1 : ++concentrationLineIndex_;
		}

		//�_���[�W���󂯂����̃G�t�F�N�g�`��
		if (damageEffectAlpha_ > 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, damageEffectAlpha_);
			DrawGraph(0, 0, handles_[IMAGE::DAMAGE], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	//�j�������֐�
	void Player2DEffect::Fin(void)
	{
		for (auto&& image : handles_)
		{
			DeleteGraph(image);
		}
	}

	void Player2DEffect::EffectRequest(void)
	{
		damageEffectAlpha_ = 255;
	}
}
