#pragma once

#include <memory>
#include "Vector/Vector3D.h"
#include "Object/Object.h"

//�ŗL�̏�Ԃ̒��ۃN���X
class StateBase
{
protected:
	//��Ԃ̏��L��
	std::weak_ptr<Object> owner_;

public:
	StateBase() = default;
	StateBase(const std::shared_ptr<Object>& owner) : owner_(owner) {};

	~StateBase() = default;

	//�����������֐�
	virtual void Init(void) = 0;

	//�s�������֐�
	virtual void Step(void) = 0;

};
