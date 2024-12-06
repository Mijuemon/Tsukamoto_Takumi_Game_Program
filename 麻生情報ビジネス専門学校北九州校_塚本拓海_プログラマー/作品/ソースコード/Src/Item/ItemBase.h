#pragma once

#include <memory>
#include "Object/Object.h"

namespace BOUDAMA
{
	//�A�C�e���p���N���X
	class ItemBase : public Object
	{
	protected:
		std::weak_ptr<Object> owner_;

	public:
		//�R���X�g���N�^
		ItemBase() {}

		//�f�X�g���N�^
		virtual ~ItemBase() = default;

		//�ǂݍ��ݏ����֐�
		virtual void Load(const int originalHandle)
		{
			if (handle_ == -1)
			{
				handle_ = MV1DuplicateModel(originalHandle);
			}
		}

		//�o�������֐�
		virtual void AppearanceRequest(void) = 0;

		//�A�C�e���̌��ʎ��s
		virtual void EffectExecute(const std::shared_ptr<Object>& targetObject) = 0;

		//���L�Ҏ擾
		inline std::weak_ptr<Object> GetOwner(void) const { return owner_; }

		//���L�Ґݒ�
		inline void SetOwner(const std::shared_ptr<Object>& owner) { owner_ = owner; }

	};
}
