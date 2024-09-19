#pragma once

#include "EnemyBase.h"

//�G�N���X
class Enemy : public EnemyBase
{
private:

public:
	//�R���X�g���N�^
	Enemy();

	//�f�X�g���N�^
	~Enemy();

	//�����������֐�
	void Init(void) override;

	//�s�������֐�
	void Step(const Vector3D& playerPos) override;

	//�`�揈���֐�
	void Draw(void) override;

	//�o�������֐�
	void AppearanceRequest(void) override;

	//�����蔻�菈��
	void HitCalculation(void) override;

};