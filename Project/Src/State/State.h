#pragma once

#include <memory>
#include <string>
#include "StateBase.h"

//�X�e�[�g�}�V���Ŏg����Ԑ؂�ւ��p�N���X
class State final
{
private:
    //��Ԏ��s�p�ϐ�
    std::shared_ptr<StateBase> state_;

    //���ɍs����Ԃ̖��O
    std::string nextStateName_;

public:
    State() = default;
    State(const std::shared_ptr<StateBase> state, const std::string& nextStateName) noexcept :
        state_(state), nextStateName_(nextStateName)  {}

    ~State() = default;

    //�����������֐�
    void Init(void);

    //�s�������֐�
    void Step(void);

    //����Ԉڍs���f�p�֐�
    bool CanGoToNextState(void);

    //��Ԃ�ύX����Ƃ��Ɏg���֐�
    void ChangeState(void);

    //���̏�Ԏ擾
    std::string GetNextState(void) const noexcept;
};
