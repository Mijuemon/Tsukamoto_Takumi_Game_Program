#include "Collision.h"
#include <Enemy/EnemyManager.h>
#include <Player/PlayerParameter.h>
#include <Effekseer/Effekseer.h>
#include <Score/Score.h>
#include <Sound/Sound.h>

namespace BOUDAMA
{
	//�����̐��l�𒆐S�Ƃ��������`�̓����蔻��֐�
	bool Collision::IsHitSquare(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius)
	{
		//�����`�̓����蔻��֐�
		return vec2.x - vec2radius < vec1.x + vec1radius &&
			vec2.x + vec2radius > vec1.x - vec1radius &&
			vec2.y + vec2radius > vec1.y - vec1radius &&
			vec2.y - vec2radius < vec1.y + vec1radius;
	}

	//�����̐��l�𒆐S�Ƃ����~�̓����蔻��
	bool Collision::IsHitCircle(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius)
	{
		//�~�̓����蔻��
		return (vec1radius + vec2radius) * (vec1radius + vec2radius) >
			(vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y);
	}

	bool Collision::IsHitSphere(const Vector3D& vec1, const Vector3D& vec2, float vec1radius, float vec2radius)
	{
		// 2�_�Ԃ������Z����
		Vector3D dist = vec1 - vec2;
		// 2�_�Ԃ̋�����2����v�Z����
		float length = (dist.x * dist.x) + (dist.y * dist.y)
			+ (dist.z * dist.z);
		// ��̋��̔��a�𑫂���2�悷��
		float radius = (vec1radius + vec2radius) * (vec1radius + vec2radius);

		// �ŏI�I�ȓ����蔻��
		return length < radius;
	}


	bool Collision::IsHitTriangleXY(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
	{
		// �O�p�`�̕ӂɉ������x�N�g��
		Vector3D vecAB = vertexB - vertexA; vecAB.z = 0.0f;
		Vector3D vecBC = vertexC - vertexB; vecBC.z = 0.0f;
		Vector3D vecCA = vertexA - vertexC; vecCA.z = 0.0f;

		// �e���_����Ώۂ܂ł̃x�N�g��
		Vector3D vecAP = point - vertexA; vecAP.z = 0.0f;
		Vector3D vecBP = point - vertexB; vecBP.z = 0.0f;
		Vector3D vecCP = point - vertexC; vecCP.z = 0.0f;

		// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
		Vector3D vecABAP = Vector3D::Cross(vecAB, vecAP);
		Vector3D vecBCBP = Vector3D::Cross(vecBC, vecBP);
		Vector3D vecCACP = Vector3D::Cross(vecCA, vecCP);

		// �e�O�ς�Z������0�ȉ��ł���Γ������Ă���
		if (vecABAP.z >= 0 && vecBCBP.z >= 0 && vecCACP.z >= 0)
		{
			return true;
		}

		if (vecABAP.z <= 0 && vecBCBP.z <= 0 && vecCACP.z <= 0)
		{
			return true;
		}

		return false;
	}

	bool Collision::IsHitTriangleXZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
	{
		// �O�p�`�̕ӂɉ������x�N�g��
		Vector3D vecAB = vertexB - vertexA; vecAB.y = 0.0f;
		Vector3D vecBC = vertexC - vertexB; vecBC.y = 0.0f;
		Vector3D vecCA = vertexA - vertexC; vecCA.y = 0.0f;

		// �e���_����Ώۂ܂ł̃x�N�g��
		Vector3D vecAP = point - vertexA; vecAP.y = 0.0f;
		Vector3D vecBP = point - vertexB; vecBP.y = 0.0f;
		Vector3D vecCP = point - vertexC; vecCP.y = 0.0f;

		// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
		Vector3D vecABAP = Vector3D::Cross(vecAB, vecAP);
		Vector3D vecBCBP = Vector3D::Cross(vecBC, vecBP);
		Vector3D vecCACP = Vector3D::Cross(vecCA, vecCP);

		// �e�O�ς�Y������0�ȉ��ł���Γ������Ă���
		if (vecABAP.y >= 0 && vecBCBP.y >= 0 && vecCACP.y >= 0)
		{
			return true;
		}

		if (vecABAP.y <= 0 && vecBCBP.y <= 0 && vecCACP.y <= 0)
		{
			return true;
		}


		return false;
	}

	bool Collision::IsHitTriangleYZ(const Vector3D& point, const Vector3D& vertexA, const Vector3D& vertexB, const Vector3D& vertexC)
	{
		// �O�p�`�̕ӂɉ������x�N�g��
		Vector3D vecAB = vertexB - vertexA; vecAB.x = 0.0f;
		Vector3D vecBC = vertexC - vertexB; vecBC.x = 0.0f;
		Vector3D vecCA = vertexA - vertexC; vecCA.x = 0.0f;

		// �e���_����Ώۂ܂ł̃x�N�g��
		Vector3D vecAP = point - vertexA; vecAP.x = 0.0f;
		Vector3D vecBP = point - vertexB; vecBP.x = 0.0f;
		Vector3D vecCP = point - vertexC; vecCP.x = 0.0f;

		// �Ή�����x�N�g���ǂ����ĊO�ς��v�Z����
		Vector3D vecABAP = Vector3D::Cross(vecAB, vecAP);
		Vector3D vecBCBP = Vector3D::Cross(vecBC, vecBP);
		Vector3D vecCACP = Vector3D::Cross(vecCA, vecCP);

		// �e�O�ς�X������0�ȉ��ł���Γ������Ă���
		if (vecABAP.x >= 0 && vecBCBP.x >= 0 && vecCACP.x >= 0)
		{
			return true;
		}

		if (vecABAP.x <= 0 && vecBCBP.x <= 0 && vecCACP.x <= 0)
		{
			return true;
		}

		return false;
	}


	void Collision::IsHitBulletToPlayer(std::vector<BulletBase*>& bullet, std::shared_ptr<Player>& player)
	{
		for (const auto& bullet : bullet)
		{
			if (!bullet->GetIsActive())
			{
				continue;
			}

			if (!player->GetIsActive())
			{
				continue;
			}

			if (Collision::IsHitSphere(bullet->GetPos(), player->GetPos(), bullet->GetRadius(), player->GetRadius()))
			{
				player->HitCalculation();
				bullet->HitCalculation();
			}

		}
	}

	void Collision::IsHitBulletToEnemy(std::vector<BulletBase*>& bullet, std::vector<EnemyBase*>& enemy, EnemyManager& enemymanager)
	{
		for (const auto& bullet : bullet)
		{
			if (!bullet->GetIsActive())
			{
				continue;
			}

			for (const auto& enemy : enemy)
			{
				if (!enemy->GetIsActive())
				{
					continue;
				}

				if (Collision::IsHitSphere(bullet->GetPos(), enemy->GetPos(), bullet->GetRadius(), enemy->GetRadius()))
				{
					enemy->HitCalculation();
					bullet->HitCalculation();

					if (enemy->GetHP() > 0)
					{
						continue;
					}

					//���S���v��
					enemymanager.AddEnemyDeathCount();
				}
			}
		}
	}

	//�v���C���[�ƓG�̓����蔻��
	void Collision::IsHitPlayerToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager)
	{
		if (!player->GetIsActive())
		{
			return;
		}

		for (const auto& enemy : enemyManager.GetEnemy())
		{
			//�������Ă��Ȃ��Ȃ���s���Ȃ�
			if (!enemy->GetIsActive())
			{
				continue;
			}

			//�m�b�N�o�b�N��ԂȂ玟��
			if (enemy->GetState() == ENEMY::STATE::KNOCK_BACK)
			{
				continue;
			}

			if (Collision::IsHitSphere(player->GetPos(), enemy->GetPos(), player->GetRadius(), enemy->GetRadius()))
			{
				//�ڐG�����G���U����ԂȂ�v���C���[�𐁂���΂�
				if (enemy->GetState() == ENEMY::STATE::ATTACK)
				{
					player->HitCalculation();

					player->AddVelocity(0.625f * enemy->GetVelocity());

					enemy->HitCalculation();

					continue;
				}

				if (player->GetVelocity().SquareL2Norm() < PLAYER::KILL_SPEED)
				{
					player->HitCalculation();
					enemy->HitCalculation();

					continue;
				}

				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::ENEMY_DEATH, DX_PLAYTYPE_BACK);

				player->AddComboNum();
				Score::AddScore(enemy->GetScoreNum());

				enemy->SetCorpseState(player->GetVelocity());

				substanceManager.FlyAppearCalculation(enemy->GetPos());
			}
		}

	}

	void Collision::IsHitItemToPlayer(std::vector<ItemBase*>& item, std::vector<Player*>& player)
	{
		for (const auto& item : item)
		{
			if (!item->GetIsActive())
			{
				continue;
			}

			for (const auto& player : player)
			{
				if (!player->GetIsActive())
				{
					continue;
				}

				if (Collision::IsHitSphere(item->GetPos(), player->GetPos(), item->GetRadius(), player->GetRadius()))
				{
					item->HitCalculation();
				}

			}
		}
	}

	void Collision::IsHitPlayerToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager)
	{
		for (const auto& substance : substanceManager.GetSubstance())
		{
			//�������Ă�������s���Ȃ�
			if (!substance->IsOwnerExpired())
			{
				continue;
			}

			if (!substance->GetIsActive())
			{
				continue;
			}


			if (Collision::IsHitSphere(substance->GetPos(), player->GetPos(), substance->GetRadius(), player->GetRadius()))
			{
				substance->AttachToObject(player);

				player->AddAttachedSubstance(substance);

				Score::AddScore(substance->GetAddScoreNum());

				continue;
			}


			if (Collision::IsHitSphere(substance->GetPos(), player->GetPos(), 2.5f * substance->GetRadius(), player->GetRadius()))
			{
				substance->ChasePosCalculation(player->GetPos());

				continue;
			}
		}
	}

	void Collision::IsHitSubstanceToEnemy(const std::shared_ptr<Player>& player, EnemyManager& enemyManager, SubstanceManager& substanceManager)
	{
		for (const auto& substance : substanceManager.GetSubstance())
		{
			//�������Ă��Ȃ��Ȃ珈�����Ȃ�
			if (substance->IsOwnerExpired())
			{
				continue;
			}

			//�������Ă��Ȃ��Ȃ���s���Ȃ�
			if (!substance->GetIsActive())
			{
				continue;
			}

			for (const auto& enemy : enemyManager.GetEnemy())
			{
				if (!enemy->GetIsActive())
				{
					continue;
				}

				//�m�b�N�o�b�N��ԂȂ瓖���蔻��̏������Ȃ�
				if (enemy->GetState() == ENEMY::STATE::KNOCK_BACK)
				{
					continue;
				}

				if (!Collision::IsHitSphere(substance->GetPos(), enemy->GetPos(), substance->GetRadius(), enemy->GetRadius()))
				{
					continue;
				}

				//�G���U����ԂȂ�
				if (enemy->GetState() == ENEMY::STATE::ATTACK)
				{
					player->HitCalculation();

					player->SubVelocity(enemy->GetVelocity());

					enemy->SetCorpseState(substance->GetOwner()->GetVelocity());

					continue;
				}

				//���G��Ԃł͂Ȃ��ꍇ
				if (substance->IsOwnerNotInvincible())
				{
					player->HitCalculation();
					enemy->SetCorpseState(-enemy->GetDir());

					continue;
				}

				SoundManager::GetInstance()->PlaySoundData(SOUND::SE::ENEMY_DEATH, DX_PLAYTYPE_BACK);

				player->AddComboNum();
				Score::AddScore(enemy->GetScoreNum());

				enemy->SetCorpseState(substance->GetOwner()->GetVelocity());

				substanceManager.RandomFlyAppearCalculation(enemy->GetPos());

				return;

			}
		}
	}

	void Collision::IsHitSubstanceToSubstance(const std::shared_ptr<Player>& player, SubstanceManager& substanceManager)
	{
		for (const auto& playerSubstance : player->GetAttachedSubstance())
		{
			if (const auto& substance = playerSubstance.lock())
			{
				for (const auto& hitSubstance : substanceManager.GetSubstance())
				{
					//�������̂��r���悤�Ƃ��Ă���ꍇ�͎��ɍs��
					if (substance == hitSubstance)
					{
						continue;
					}

					//�������Ă������΂�
					if (!hitSubstance->IsOwnerExpired())
					{
						continue;
					}

					if (!hitSubstance->GetIsActive())
					{
						continue;
					}

					if (Collision::IsHitSphere(substance->GetPos(), hitSubstance->GetPos(), substance->GetRadius(), hitSubstance->GetRadius()))
					{
						//�ʒu���d�Ȃ�Ȃ��悤�ɂ���
						Vector3D substanceToSubstanceVector = hitSubstance->GetPos() - substance->GetPos();
						hitSubstance->SetPos(substance->GetPos() + substanceToSubstanceVector.Normalize() * (substance->GetRadius() + hitSubstance->GetRadius()));

						//�������Ă�����
						if (substance->IsOwnerExpired())
						{
							hitSubstance->AttachToObject(substance);
						}
						else
						{
							hitSubstance->AttachToObject(substance->GetOwner());
						}

						Score::AddScore(100);
					}


					if (Collision::IsHitSphere(substance->GetPos(), hitSubstance->GetPos(), 2.5f * substance->GetRadius(), hitSubstance->GetRadius()))
					{
						substance->ChasePosCalculation(hitSubstance->GetPos());

						continue;
					}

				}
			}
		}
	}
}
