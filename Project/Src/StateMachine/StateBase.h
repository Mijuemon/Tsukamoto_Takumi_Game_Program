#pragma once

#include <memory>
#include "Vector/Vector3D.h"
#include "Object/Object.h"

namespace BOUDAMA
{
	//�ŗL�̏�ԂɌp�������钊�ۃN���X
	template<class Ty>
	class StateBase
	{
	public:
		using Type = Ty;

		constexpr StateBase(void) noexcept : myStateName_(), nextStateName_(), isTransitionToNextState(false) {};
		explicit constexpr StateBase(const Type initState) noexcept : myStateName_(initState), nextStateName_(initState), isTransitionToNextState(false) {};

		virtual ~StateBase() noexcept = default;

	protected:
		//��Ԃ̏��L��
		std::weak_ptr<Object> owner_;

		//�������g�̏�Ԃ̖��O
		Type myStateName_;

		//���ɍs����Ԃ̖��O
		Type nextStateName_;

		//���̏�ԂɑJ�ڂ��邩�H
		bool isTransitionToNextState;

	public:
		//���̏�Ԃɓ������u�Ԃɂ������s����֐�
		virtual void Enter(void) = 0;

		//�s�������֐�
		virtual void Execute(void) = 0;

		/// <summary>
		/// ���̏�ԑJ�ڂ��邩?
		/// </summary>
		/// <returns>
		/// true : ���̏�ԂɑJ�ڂ���
		/// false : ���݂̏�Ԃ��ێ�����
		/// </returns>
		inline bool IsTransitionToNextState(void) const noexcept
		{
			return isTransitionToNextState;
		}

		//�������g�̂̏�Ԃ��擾
		inline Type GetMyState(void) const noexcept
		{
			return myStateName_;
		}

		//�J�ڐ�̏�Ԃ��擾
		inline Type GetNextState(void) const noexcept
		{
			return nextStateName_;
		}

		//��Ԃ̏��L��
		void SetOwner(const auto& owner) noexcept
		{
			owner_ = owner;
		}

	};
}
