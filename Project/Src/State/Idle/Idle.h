#pragma once

#include "State/StateBase.h"

class Idle : public StateBase
{
public:
	Idle();
	~Idle();

private:

	//�����������֐�
	void Init(void) override;

	//�s�������֐�
	void Step(void) override;
};

Idle::Idle()
{
}

Idle::~Idle()
{
}