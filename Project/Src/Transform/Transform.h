#pragma once

#include "Vector/Vector3D.h"

//�ʒu�E�����E��]���������N���X
class Transform
{
protected:
	//�ʒu
	Vector3D pos_;

	//�����x�N�g��
	Vector3D dir_;

	//��]�p�x
	Vector3D rot_;

public:
	Transform() = default;
	virtual ~Transform() = default;

public:
	//���݂̈ʒu(XYZ���W)�擾
	inline Vector3D GetPos(void) const noexcept { return pos_; }

	//�ʒu(XYZ���W)�ݒ�
	inline void SetPos(const Vector3D& pos) noexcept { pos_ = pos; }

	//�ʒu(XYZ���W)�ݒ�
	inline void SetPos(float x, float y, float z) noexcept { pos_.x = x; pos_.y = y; pos_.z = z; }

	//�ʒu(XYZ���W)�𓮂���
	inline void MovePos(const Vector3D direction) noexcept { pos_ += direction; }
	inline void MovePos(float x, float y, float z) noexcept { pos_.x += x; pos_.y += y; pos_.z += z; }

	//������
	inline void ResetPos(void) { pos_ = { 0.0f,0.0f,0.0f }; }


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

	//������
	inline void ResetDir(void) { dir_ = { 0.0f,0.0f,0.0f }; }



	//��]������
	inline Vector3D Rotate(const Vector3D& angle) noexcept { rot_ += angle; }
	inline void Rotate(float x, float y, float z) noexcept { rot_.x += x; rot_.y += y; rot_.z += z; }

	//��]���擾
	inline Vector3D GetRot(void) const noexcept { return rot_; }

	//��]���ݒ�
	inline void SetRot(const Vector3D& rot) { rot_ = rot; }

	//������
	inline void ResetRot(void) { rot_ = { 0.0f,0.0f,0.0f }; }


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
