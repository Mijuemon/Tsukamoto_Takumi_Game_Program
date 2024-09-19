#pragma once

#include <Vector/Vector2D.h>

//�}�E�X���͗p�N���X
class InputMouse
{
private:
	//���A�N���b�N���Ă��邩����
	static inline bool isCurrentClick_;

	//1�t���[���O�ɃN���b�N���Ă���������
	static inline bool isPreClick_;

	//���݈ʒu
	static inline int currentPosX_,currentPosY_;

	//1�t���[���O�̈ʒu
	static inline int prePosX_, prePosY_;

public:
	//�����������֐�
	static void Init(void);

	//���͏����֐�
	static void Step(void);

	/// <summary>
	/// ���݂̃t���[���ō��N���b�N���ꂽ��
	/// </summary>
	/// <returns>
	/// true : ���݂̃t���[���ŉ����ꂽ
	/// false : ���݂̃t���[���ŉ�����Ă��Ȃ�
	/// </returns>
	static inline bool IsClickDown(void) { return isCurrentClick_ && !isPreClick_; }

	/// <summary>
	/// ���݂̃t���[���ŗ����ꂽ��
	/// </summary>
	/// <returns>
	/// true : ���݂̃t���[���ŗ����ꂽ
	/// false : ���݂̃t���[���ŗ�����Ă��Ȃ�
	/// </returns>
	static inline bool IsClickRelease(void) { return !isCurrentClick_ && isPreClick_; }

	//�}�E�X���ړ��������l���擾
	static inline Vector2D GetMoveValue(void) { return Vector2D(static_cast<float>(currentPosX_ - prePosX_), static_cast<float>(currentPosY_ - prePosY_)); }

	//�}�E�X���������Ɉړ��������l���擾
	static inline float GetMoveValueX(void) { return static_cast<float>(currentPosX_ - prePosX_); }

	//�}�E�X���c�����Ɉړ��������l���擾
	static inline float GetMoveValueY(void) { return static_cast<float>(currentPosY_ - prePosY_); }
};
