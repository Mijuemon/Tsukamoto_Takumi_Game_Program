#pragma once
#include <Vector/Vector3D.h>

//�J�������N���X
class CameraBase
{
protected:
	//�ʒu
	Vector3D pos_;

	//�����_
	Vector3D target_;

	//�����
	Vector3D up_;

	//��]
	Vector3D rot_;

	//�J�����̐��ʕ����x�N�g��
	Vector3D dir_;

public:
	//�R���X�g���N�^
	CameraBase() {}

	//�f�X�g���N�^
	virtual ~CameraBase() {}

	//�����������֐�
	virtual void Init(void) = 0;

	//�ړ������֐�
	virtual void Step(const Vector3D& playerPos) = 0;

	//�X�V�֐�
	virtual void UpDate(void) = 0;

	//XYZ���W�擾
	inline Vector3D GetPos(void) const { return pos_; }

	//XYZ���W�ݒ�
	inline void SetPos(float x, float y, float z) { pos_.x = x; pos_.y = y; pos_.z = z; }

	//XYZ���W�ݒ�
	inline void SetPos(const Vector3D& pos) { pos_ = pos; }

	//X���擾
	inline float GetPosX(void) const { return pos_.x; }

	//X���ݒ�
	inline void SetPosX(float x) { pos_.x = x; }

	//Y���擾
	inline float GetPosY(void) const { return pos_.y; }

	//Y���ݒ�
	inline void SetPosY(float y) { pos_.y = y; }

	//Z���擾
	inline float GetPosZ(void) const { return pos_.z; }

	//Z���ݒ�
	inline void SetPosZ(float z) { pos_.z = z; }


	//�����_�擾
	inline Vector3D GetTarget(void) const { return target_; }

	//�����_�擾
	inline void SetTarget(const Vector3D& target) { target_ = target; }


	//������擾
	inline Vector3D GetUp(void) const { return up_; }

	//������ݒ�
	inline void SetUp(const Vector3D& up) { up_ = up; }


	//��]���擾
	inline Vector3D GetRot(void) const { return rot_; }

	//��]���ݒ�
	inline void SetRot(const Vector3D& rot) { rot_ = rot; }

	//X���擾
	inline float GetRotX(void) const { return rot_.x; }

	//X���ݒ�
	inline void SetRotX(float x) { rot_.x = x; }

	//Y���擾
	inline float GetRotY(void) const { return rot_.y; }

	//Y���ݒ�
	inline void SetRotY(float y) { rot_.y = y; }

	//Z���擾
	inline float GetRotZ(void) const { return rot_.z; }

	//Z���ݒ�
	inline void SetRotZ(float z) { rot_.z = z; }


	//�����x�N�g���擾
	inline Vector3D GetDir(void) const { return dir_; }

	//�����x�N�g���ݒ�
	inline void SetDir(const Vector3D& dir) { dir_ = dir; }

};