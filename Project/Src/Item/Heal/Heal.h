#pragma once

#include "Item/ItemBase.h"

class Heal : public ItemBase
{
private:
	//�񕜂�����l
	int healValue_;

public:
	Heal() { healValue_ = 0; }

	~Heal(){}

	void Init(void) override;

	void Step(void) override;

	//�o�������֐�
	void AppearanceRequest(void) override;

	
	void EffectExecute(const std::shared_ptr<Object>& subjectObject);
};
