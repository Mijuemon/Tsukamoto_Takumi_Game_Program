#pragma once

#include <memory>
#include "Item/ItemBase.h"
#include "Item/ItemParameter.h"

//���e�N���X
class Bomb : public ItemBase
{
private:
	//��ԊǗ��p�ϐ�
	BOMB::STATE state_;

	//��������܂ł̎���
	int countExplodeTimeLimit_;

	//��������
	int explosionTime_;

public:
	//�R���X�g���N�^
	Bomb() { countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT; explosionTime_ = 0; }

	//�f�X�g���N�^
	~Bomb() {}

	//�����������֐�
	void Init(void) override;

	//�s�������֐�
	void Step(void) override;

	//�o�������֐�
	void AppearanceRequest(void) override;

	//�A�C�e���̌��ʎ��s
	void EffectExecute(const std::shared_ptr<Object>& subjectObject);

	//
	void HitCalculation(void) override;

	inline int GetCountExplodeTimeLimit(void) const { return countExplodeTimeLimit_; }

	inline int GetExplosionTime(void) const { return countExplodeTimeLimit_; }

private:
	//�ʏ���
	void MoveNormal(void);

	//�������
	void MoveThrow(void);

	//�������
	void MoveExplosion(void);

	//�֐��|�C���^
	const decltype(&Bomb::MoveNormal) MoveFunctionPointer[BOMB_STATE::NUM]
	{
		&Bomb::MoveNormal,
		&Bomb::MoveThrow,
		&Bomb::MoveExplosion
	};
};