#include "ItemManager.h"
#include "ItemParameter.h"
#include "Item/Bomb/Bomb.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	ItemManager::ItemManager()
	{

	}

	//�f�X�g���N�^
	ItemManager::~ItemManager()
	{

	}

	//�����������֐�
	void ItemManager::Init(void)
	{
		for (int index = 0; index < BOMB::MAX_NUM; ++index)
		{
			items_.emplace_back(std::make_shared<Bomb>());
		}
	}

	//�ǂݍ��ݏ����֐�
	void ItemManager::Load(void)
	{
		const int origineHandle = MV1LoadModel(BOMB::PATH);

		for (const auto& item : items_)
		{
			item->Load(origineHandle);
		}

		MV1DeleteModel(origineHandle);
	}

	//�s�������֐�
	void ItemManager::Step()
	{
		for (const auto& item : items_)
		{
			item->Step();
		}
	}

	//�`�揈���֐�
	void ItemManager::Draw(void)
	{
		for (const auto& item : items_)
		{
			item->Draw();
		}
	}

	//�j�������֐�
	void ItemManager::Fin(void)
	{
		for (auto&& itemItr = items_.cbegin(); itemItr != items_.cend();)
		{
			(*itemItr)->Fin();
			itemItr = items_.erase(itemItr);
		}

		items_.clear();
		items_.shrink_to_fit();
	}

	//�o������
	void ItemManager::AppearanceRequest(const std::shared_ptr<Object>& owner, const ITEM::ITEM_LIST itemNum)
	{
		int sumItemPos = 0;

		int intItemNum = static_cast<int>(itemNum);

		//�A�C�e���̈ʒu�T��
		for (int index = 0; index < intItemNum; ++index)
		{
			sumItemPos += ITEM::ITEM_MAX_NUM_LIST[index];
		}

		//�A�C�e���̈ʒu�ݒ�
		auto&& itemBeginPos = items_.begin() + sumItemPos;

		//�A�C�e���̏o���ő吔�擾
		const int maxNum = ITEM::ITEM_MAX_NUM_LIST[intItemNum];

		//�o�����Ă��Ȃ��A�C�e����T��
		for (int count = 0; count < maxNum; ++count)
		{
			//���ɏo�����Ă���Ȃ���s���Ȃ�
			if ((*itemBeginPos)->GetIsActive())
			{
				++itemBeginPos;
				continue;
			}

			if (owner)
			{
				//���L�Ґݒ�
				(*itemBeginPos)->SetOwner(owner);
				(*itemBeginPos)->SetPos(owner->GetPos());
			}

			(*itemBeginPos)->AppearanceRequest();

			return;
		}
	}
}
