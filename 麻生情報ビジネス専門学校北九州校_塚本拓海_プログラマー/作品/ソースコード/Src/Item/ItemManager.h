#pragma once

#include <vector>
#include <memory>
#include "ItemBase.h"
#include "ItemParameter.h"

#ifdef _DEBUG

#include <iostream>
#include <intrin.h>

#endif

namespace BOUDAMA
{
	//�A�C�e���p�Ǘ��N���X
	class ItemManager
	{
	private:
		//�A�C�e���p�x�N�^�[
		std::vector<std::shared_ptr<ItemBase>> items_;

	public:
		//�R���X�g���N�^
		ItemManager();

		//�f�X�g���N�^
		~ItemManager();

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�s�������֐�
		void Step();

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);

		void AppearanceRequest(const ITEM::ITEM_LIST itemNum);

		const auto& SearchItem(const ITEM::ITEM_LIST itemNum) const
		{
			int vectorItemIndex = 0;

			int intItemNum = static_cast<int>(itemNum);

			//�A�C�e���̈ʒu�T��
			for (int index = 0; index < intItemNum; ++index)
			{
				vectorItemIndex += ITEM::ITEM_MAX_NUM_LIST[index];
			}

			int maxNum = ITEM::ITEM_MAX_NUM_LIST[intItemNum];

			for (int num = 0; num < maxNum; ++num, ++vectorItemIndex)
			{
				if (items_[vectorItemIndex]->GetIsActive())
				{
					continue;
				}

				items_[vectorItemIndex]->SetIsActive(true);

				return items_[vectorItemIndex];
			}

#ifdef _DEBUG
			std::cerr << "Debug break : �A�C�e�����������܂���ł����I" << std::endl;
			__debugbreak();
#endif // _DEBUG

			return *items_.begin();
		}


		inline const std::vector<std::shared_ptr<ItemBase>>& GetItem() { return items_; }

	};
}
