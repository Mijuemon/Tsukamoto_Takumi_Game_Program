#pragma once

#include <memory>
#include "Vector/Vector3D.h"
#include "Object/Object.h"

namespace BOUDAMA
{
	//�ŗL�̏�ԂɌp�������钊�ۃN���X
	template<class T>
	class StateBase
	{
	public:
		using Type = T;

	protected:
		//��Ԃ̏��L��
		std::weak_ptr<Object> owner_;

		//�������g�̏�Ԃ̖��O
		Type myStateName_;

		//���ɍs����Ԃ̖��O
		Type nextStateName_;


		StateBase() = default;

		StateBase(const std::shared_ptr<Object>& owner) : owner_(owner) {};

		virtual ~StateBase() = default;

		//�����������֐�
		virtual void Init(void) = 0;

		//�s�������֐�
		virtual void Step(void) = 0;
	
		/// <summary>
		/// ���̏�ԑJ�ڂł��邩?
		/// </summary>
		/// <returns>
		/// true : ���̏�ԂɑJ�ڂ���
		/// false : ���݂̏�Ԃ��ێ�����
		/// </returns>
		virtual bool CanTransitionToNextState(void) const = 0 ;

		//�������g�̂̏�Ԃ��擾
		virtual Type GetMyState(void) const = 0;

		//�J�ڐ�̏�Ԃ��擾
		virtual Type GetNextState(void) const = 0 ;

	};
}
