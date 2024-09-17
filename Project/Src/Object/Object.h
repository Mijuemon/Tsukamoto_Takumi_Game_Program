#pragma once

#include "Vector/Vector3D.h"

//�ėp���N���X
class Object
{
protected:
	//�n���h��
	int handle_;

	//�̗�
	int hp_;

	//���a
	float radius_;

	//�ʒu
	Vector3D pos_;

	//����
	Vector3D dir_;

	//���x
	Vector3D velocity_;

	//�p�x��
	Vector3D rot_;

	//��������
	bool isAlive_;

public:
	//�R���X�g���N�^
	Object()
	{
		handle_ = -1;
		hp_ = 0;
		radius_ = 0.0f;
		isAlive_ = false;
	}

	//�f�X�g���N�^
	virtual ~Object() {}

	//�����������֐�
	virtual void Init(void);

	//�ǂݍ��ݏ����֐�
	virtual void Load(void);

	//�s�������֐�
	virtual void Step(void);

	//�`�揈���֐�
	virtual void Draw(void);

	//�j�������֐�
	virtual void Fin(void);

	//�����蔻�菈��
	virtual void HitCalculation(void);

public:
	//�n���h���擾
	inline int GetHandle(void) const noexcept { return handle_; }

	
	//HP���Z
	inline void AddHP(int addNum) { hp_ += addNum; }

	//HP���Z
	inline void SubHP(int subNum) { hp_ += subNum; }

	//HP�擾
	inline int GetHP(void) const noexcept { return hp_; }

	//HP�ݒ�
	inline void SetHP(int HP) { hp_ = HP; }


	//���a�擾
	inline float GetRadius(void) const noexcept { return radius_; }

	//���a�ݒ�
	inline void SetRadius(float radius) { radius_ = radius; }


	/// <summary>
	/// ��������擾
	/// </summary>
	/// <returns>
	/// true : �������Ă���
	/// false : �������Ă��Ȃ�
	/// </returns>
	inline bool GetIsActive(void) const noexcept { return isAlive_; }

	//��������ݒ�
	inline void SetIsActive(bool authenticity) { isAlive_ = authenticity; }


	//���݂̈ʒu(XYZ���W)�擾
	inline Vector3D GetPos(void) const noexcept { return pos_; }

	//�ʒu(XYZ���W)�ݒ�
	inline void SetPos(const Vector3D& pos) { pos_ = pos; }

	//�ʒu(XYZ���W)�ݒ�
	inline void SetPos(float x, float y, float z) { pos_.x = x; pos_.y = y; pos_.z = z; }


	//X���擾
	inline float GetPosX(void) const noexcept { return pos_.x; }

	//X���ݒ�
	inline void SetPosX(float x) { pos_.x = x; }


	//Y���擾
	inline float GetPosY(void) const noexcept { return pos_.y; }

	//Y���ݒ�
	inline void SetPosY(float y) { pos_.y = y; }


	//Z���擾
	inline float GetPosZ(void) const noexcept { return pos_.z; }

	//Z���ݒ�
	inline void SetPosZ(float z) { pos_.z = z; }


	//�����x�N�g���擾
	inline Vector3D GetDir(void) const noexcept { return dir_; }

	//�����x�N�g���ݒ�
	inline void SetDir(const Vector3D& dir) { dir_ = dir; }


	//���x�x�N�g���擾
	inline Vector3D GetVelocity(void) const noexcept { return velocity_; }

	//���x�x�N�g���ݒ�
	inline void SetVelocity(const Vector3D& velocity) { velocity_ = velocity; }

	//���x�x�N�g�����Z
	inline void AddVelocity(const Vector3D& addVelocity) { velocity_ += addVelocity; }

	//���x�x�N�g�����Z
	inline void SubVelocity(const Vector3D& subVelocity) { velocity_ -= subVelocity; }


	//X���擾
	inline float GetVelocityX(void) const noexcept { return velocity_.x; }

	//X���ݒ�
	inline void SetVelocityX(float x) { velocity_.x = x; }


	//Y���擾
	inline float GetVelocityY(void) const noexcept { return velocity_.y; }

	//Y���ݒ�
	inline void SetVelocityY(float y) { velocity_.y = y; }


	//Z���擾
	inline float GetVelocityZ(void) const noexcept { return velocity_.z; }

	//Z���ݒ�
	inline void SetVelocityZ(float z) { velocity_.z = z; }


	//��]���擾
	inline Vector3D GetRot(void) const noexcept { return rot_; }

	//��]���ݒ�
	inline void SetRot(const Vector3D& rot) { rot_ = rot; }


	//X���擾
	inline float GetRotX(void) const noexcept { return rot_.x; }

	//X���ݒ�
	inline void SetRotX(float x) { rot_.x = x; }


	//Y���擾
	inline float GetRotY(void) const noexcept { return rot_.y; }

	//Y���ݒ�
	inline void SetRotY(float y) { rot_.y = y; }


	//Z���擾
	inline float GetRotZ(void) const noexcept { return rot_.z; }

	//Z���ݒ�
	inline void SetRotZ(float z) { rot_.z = z; }

};
