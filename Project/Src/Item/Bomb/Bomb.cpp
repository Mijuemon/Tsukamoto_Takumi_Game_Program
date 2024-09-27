#include "Bomb.h"
#include <Math/MyMath.h>

//�����������֐�
void Bomb::Init(void)
{
	//������
	handle_ = -1;
	state_ = BOMB::STATE::NORMAL;
	isAlive_ = true;
	hp_ = 1;
	radius_ = BOMB::RADIUS;
	pos_ = MY_MATH::ZERO_VECTOR_3D;
	velocity_ = MY_MATH::ZERO_VECTOR_3D;
	rot_ = MY_MATH::ZERO_VECTOR_3D;

	countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;
}

//�s�������֐�
void Bomb::Step(void)
{
	(this->*MoveFunctionPointer[state_])();
}

//�o�������֐�
void Bomb::AppearanceRequest(void)
{
	isAlive_ = true;

	if (owner_.expired())
	{
		pos_ = { BOMB::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM),
			0.0f,
			BOMB::INIT_POS_X_Z + GetRand(BOMB::INIT_POS_XZ_RAND_MAX_NUM) };
	}
}

//�A�C�e���̌��ʎ��s
void Bomb::EffectExecute(const std::shared_ptr<Object>& subjectObject)
{
	subjectObject->SubHP(BOMB::ATTACK_POWER);
}

//���������Ƃ��̏���
void Bomb::HitCalculation(void)
{
	state_ = BOMB::STATE::EXPLOSION;
	isAlive_ = false;
}

void Bomb::MoveNormal(void)
{
	//�������Ă��Ȃ���Ύ��s���Ȃ�
	if (!isAlive_)
	{
		return;
	}

	//��������܂ł̎��Ԍv��
	--countExplodeTimeLimit_;

	//�����܂ł̃J�E���g�_�E����0�ɂȂ�����
	if (countExplodeTimeLimit_ <= 0)
	{
		//���̏�Ŕ�����ԂɑJ��
		state_ = BOMB::STATE::EXPLOSION;
		isAlive_ = false;

		countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;

		radius_ = BOMB::EXPLODE_RADIUS;

		return;
	}

	//�N�����������g���擾�����Ƃ��̏���
	if (!owner_.expired())
	{
		const auto& owner = owner_.lock();

		pos_ = owner->GetPos() + BOMB::HELD_UP_DISTANCE;
		rot_.y = owner->GetRotY();

		//���W�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

		return;
	}

	//Y���̂��邮���]���鏈��
	rot_.y = rot_.y >= MY_MATH::TWO_PI - MY_MATH::PI_OVER_TWENTY ? 0.0f : rot_.y + MY_MATH::PI_OVER_TWENTY;

	//���W�ݒ�
	MV1SetPosition(handle_, pos_);
	MV1SetRotationXYZ(handle_, rot_);
}

//������ꂽ�Ƃ��̏���
void Bomb::MoveThrow(void)
{
	//��������܂ł̎��Ԍv��
	--countExplodeTimeLimit_;

	//dir_.x = -sinf(rot_.y) * BOMB::THROW_SPEED;
	//dir_.z = -cosf(rot_.y) * BOMB::THROW_SPEED;

	pos_ += dir_;

	dir_ *= 0.9f;

	//�d�͏���
	pos_.y - BOMB::GRAVITY > BOMB::GROUND_POS ? pos_.y -= BOMB::GRAVITY : pos_.y = BOMB::GROUND_POS;


	//��ʊO�ɏo���ꍇ�A���S����
	if (MyMath::Abs(pos_.x) > BOMB::MAX_POS_X_Z || MyMath::Abs(pos_.z) > BOMB::MAX_POS_X_Z)
	{
		isAlive_ = false;
		dir_ = MY_MATH::ZERO_VECTOR_3D;
	}

	//�ʒu�E�p�x�ݒ�
	MV1SetPosition(handle_, pos_);
	MV1SetRotationXYZ(handle_, rot_);
}

//�������Ă���Ƃ��̏���
void Bomb::MoveExplosion(void)
{
	//�������̎��Ԍv��
	++explosionTime_;
	
	//�������Ԃ��ő�܂ōs������
	if (explosionTime_ >= BOMB::MAX_EXPLOSION_TIME)
	{
		state_ = BOMB::STATE::NORMAL;
		explosionTime_ = 0;
		radius_ = BOMB::RADIUS;
	}
}
