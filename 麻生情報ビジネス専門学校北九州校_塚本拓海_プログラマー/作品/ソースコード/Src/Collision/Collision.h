#pragma once

#include <memory>
#include <vector>
#include "Vector/Vector3D.h"
#include "Player/Player.h"
#include <Bullet/BulletBase.h>
#include <Enemy/EnemyBase.h>
#include "Enemy/EnemyManager.h"
#include <Item/ItemBase.h>
#include <Substance/SubstanceManager.h>

namespace BOUDAMA
{
	class Collision final
	{
	public:
		//�����̐��l�𒆐S�Ƃ��������`�̓����蔻��֐�
		static bool IsHitSquare(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		//�����̐��l�𒆐S�Ƃ����~�̓����蔻��
		static bool IsHitCircle(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		static bool IsHitSphere(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius);

		static bool IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		static bool IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);

		static bool IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC);;

		//�e�ƃv���C���[�̓����蔻��
		static void IsHitBulletToPlayer(std::vector<BulletBase*>& bullet, std::shared_ptr<Player>& player);

		//�e�ƓG�̓����蔻��
		static void IsHitBulletToEnemy(std::vector<BulletBase*>& bullet, std::vector<EnemyBase*>& enemy, EnemyManager& enemymanager);

		//�v���C���[�ƓG�̓����蔻��
		static void IsHitPlayerToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager);

		//�����ƓG�̓����蔻��
		static void IsHitSubstanceToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager);

		//�A�C�e���ƓG�̓����蔻��
		static void IsHitItemToPlayer(std::vector<ItemBase*>& item, std::vector<Player*>& player);

		//�v���C���[�ƕ����̓����蔻��
		static void IsHitPlayerToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);

		//�������m�̓����蔻��
		static void IsHitSubstanceToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager);
	};
}
