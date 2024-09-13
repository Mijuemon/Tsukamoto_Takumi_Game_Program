#pragma once

#include <Vector/Vector2D.h>

//�}�E�X���͗p�N���X
class InputMouse
{
private:

public:
	//���A�N���b�N���Ă��邩����
	static inline bool isCurrentClick_;

	//1�t���[���O�ɃN���b�N���Ă���������
	static inline bool isPreClick_;

	//���݈ʒu
	static inline int currentPosX_,currentPosY_;

	//1�t���[���O�̈ʒu
	static inline int prePosX_, prePosY_;

	//�����������֐�
	static void Init(void);

	//���͏����֐�
	static void Step(void);

	//
	static inline bool IsClick(void) { return isCurrentClick_ && !isPreClick_; }

	//
	static inline bool IsClickRelease(void) { return !isCurrentClick_ && isPreClick_; }


	static inline float GetMovePosX(void) { return static_cast<float>(currentPosX_ - prePosX_); }

	static inline float GetMovePosY(void) { return static_cast<float>(currentPosY_ - prePosY_); }
};
