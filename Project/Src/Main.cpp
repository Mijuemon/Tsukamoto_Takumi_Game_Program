/*
	�������r�W�l�X���w�Z �k��B�Z
	�w�Дԍ��F2209423
	�����F�˖{��C
	�v���O���}�[
*/

#include "Game/System.h"

//���C���֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̋N��
	GameSystem::Start();

	//�Q�[���̃��[�v
	GameSystem::MainLoop();

	//�Q�[���̏I��
	GameSystem::Fin();

	//�v���O�����̏I��
	return 0;

}//WinMain�֐��I��芇��
