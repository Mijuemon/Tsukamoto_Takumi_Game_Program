#include "Heal.h"

#include "DxLib.h"

#include <Item/ItemParameter.h>

void Heal::Init(void)
{
	healValue_ = HEAL::HEAL_VALUE;
}

void Heal::Step(void)
{
	//�������Ă��Ȃ���Ύ��s���Ȃ�
	if (!isAlive_)
	{
		return;
	}

	//�A�C�e�������ɗ����Ă���ꍇ
	if (owner_.expired())
	{
		pos_.y - HEAL::GRAVITY > HEAL::GROUND_POS ? pos_.y -= HEAL::GRAVITY : pos_.y = HEAL::GROUND_POS;

		return;
	}

	const std::shared_ptr<Object>& owner = owner_.lock();

	pos_ = owner->GetPos() + HEAL::UP_DISTANCE;
}

//�o�������֐�
void Heal::AppearanceRequest(void)
{
	isAlive_ = true;

	if (owner_.expired())
	{
		pos_ = { HEAL::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM),
			0.0f,
			HEAL::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM) };
	}
}

//�A�C�e�����g�p�������̌��ʎ��s�֐�
void Heal::EffectExecute(const std::shared_ptr<Object>& subjectObject)
{
	//HP��
	subjectObject->AddHP(healValue_);
}
