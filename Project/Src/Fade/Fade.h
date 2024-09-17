#pragma once

#include <vector>
#include "FadeParameter.h"

//�t�F�[�h�C���E�t�F�[�h�A�E�g�p�֐�
class Fade
{
private:
	//���
	FADE::STATE state_;

	//���l(���ߓx)
	int alphaValue_;

	//�ʒu
	int posX_;

	//�摜�̓Y����
	int handleIndex_;

	//�摜�n���h����ۑ�����x�N�^�[
	std::vector<int> syobonHandles_;

	//��]�p�x
	float rotAngle;

	//�t�F�[�h�C���E�t�F�[�h�A�E�g�������I�������
	bool isEnd_;

public:
	//�R���X�g���N�^
	Fade();

	//�f�X�g���N�^
	~Fade();

	//�����������֐�
	void Init(void);

	//�ǂݍ��ݏ����֐�
	void Load(void);

	//�X�V�����֐�
	void Step(void);

	//�`�揈��
	void Draw(void);

	//�j�������֐�
	void Fin(void);

	//�t�F�[�h�̏�ԕύX
	void Change(void);

	//�t�F�[�h�C�����t�F�[�h�A�E�g���I�����������
	bool IsEnd(void) const noexcept;
};