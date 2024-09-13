#pragma once

#include <vector>
#include "Object/Object.h"
#include "BulletBase.h"

//�e���Ǘ��p�N���X
class BulletManager
{
public:
	//�R���X�g���N�^
	BulletManager();
	//�f�X�g���N�^
	~BulletManager();

	//�����������֐�
	void Init(void);

	//�ǂݍ��ݏ����֐�
	void Load(void);

	//�s�������֐�
	void Step(void);

	//�`�揈���֐�
	void Draw(void);

	//�j�������֐�
	void Fin(void);

	//�e���ˏ����֐�
	void RequestBullet(const Vector3D& firePos, const Vector3D& rot, int playerType, Object* player);

	//�e���ˏ����֐�
	//void RequestEnemyBullet(const Vector3D& enemyVec);
	
	//�e�擾
	inline std::vector<BulletBase*> &GetBullet() { return bullets_; }

	//�G�e�擾
	//inline std::vector<Object*> GetEnemyBullet() { return m_enemyBullet; }

private:
	//�e�̃x�N�^�[
	std::vector<BulletBase*> bullets_;

};
