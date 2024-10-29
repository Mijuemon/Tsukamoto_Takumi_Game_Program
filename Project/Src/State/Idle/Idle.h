#pragma once

#include "State/StateBase.h"

class Idle : public StateBase
{
public:
	Idle();
	~Idle();

private:

	//初期化処理関数
	void Init(void) override;

	//行動処理関数
	void Step(void) override;
};

Idle::Idle()
{
}

Idle::~Idle()
{
}