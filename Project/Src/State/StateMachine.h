#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "State.h"

//��ԊǗ��p�N���X
class StateMachine
{
private:
    //��Ԉꗗ�̃n�b�V���}�b�v
    std::unordered_map<std::string, std::shared_ptr<State>> stateMap_;
    std::shared_ptr<State> nowState_;

public:
    StateMachine() : nowState_() { }

    void Step(void)
    {
        nowState_->Step();

        if (nowState_->CanGoToNextState())
        {
            nowState_->Init();
        }
    }

    //��Ԃ�V�����o�^����
    void Register(const std::string& name, const std::shared_ptr<State> state)
    {
        stateMap_.insert(std::make_pair(name, state));
    }

    //�ŏ�����n�߂��Ԃ�ݒ�
    void SetStartState(const std::string& registerName)
    {
        const auto& it = stateMap_.find(registerName);

        if (it == stateMap_.end())
        {
            return;
        }

        nowState_ = it->second;
        nowState_->Init();

    }

    //��Ԃ�ύX����
    void ChangeState(void)
    {
       const auto& it = stateMap_.find(nowState_->GetNextState());

        if (it == stateMap_.end())
        {
            return;
        }

        nowState_ = it->second;
    }

    //�o�^�������̂��폜����
    void Deregistration(const std::string& registerName)
    {
        const auto& it = stateMap_.find(registerName);

        if (it == stateMap_.end())
        {
            return;
        }

        stateMap_.erase(it);
    }

    //���ׂĂ̓o�^���폜����
    void AllDeregistration(void)
    {
        stateMap_.clear();
    }

};
