#include "State.h"

//�����������֐�
void State::Init()
{
	state_->Init();
}

//�s�������֐�
void State::Step()
{
	state_->Step();
}

//����Ԉڍs���f�p�֐�
bool State::CanGoToNextState()
{
	return false;
}

//��Ԃ�ύX����Ƃ��Ɏg���֐�
void State::ChangeState(void)
{

}

//���̏�Ԏ擾
std::string State::GetNextState(void) const noexcept
{
	return nextStateName_;
}
