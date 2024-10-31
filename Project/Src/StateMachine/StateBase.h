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
	protected:
		//��Ԃ̏��L��
		std::weak_ptr<Object> owner_;

		//���ɍs����Ԃ̖��O
		T nextStateName_;

	public:
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

		//�J�ڐ�̏�Ԃ��擾
		virtual T GetNextState(void) const = 0 ;

	};
}
