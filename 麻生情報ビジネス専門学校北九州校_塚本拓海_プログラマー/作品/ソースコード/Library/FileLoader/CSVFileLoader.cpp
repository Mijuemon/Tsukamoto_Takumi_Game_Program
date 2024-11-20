#include "CSVFileLoader.h"
#include "DxLib.h"

#include <string>
#include <fstream>
#include <iostream>

/// <summary>
/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
/// </summary>
/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
void CSV_LOADER::LoadHandle(const char* path, std::vector<int>& data)
{
	//CSV�t�@�C�����J��
	std::ifstream imageList(path);

	//�摜�̃p�X
	std::string imagePath;

	//1�s���摜��ǂݍ���
	while (std::getline(imageList, imagePath))
	{
		data.emplace_back(LoadGraph(imagePath.c_str()));
	}
}


/// <summary>
/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
/// </summary>
/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
void CSV_LOADER::LoadHandle(const char* path, int* data)
{
	//CSV�t�@�C�����J��
	std::ifstream imageList(path);

	//�摜�̃p�X
	std::string imagePath;

	//�摜��ǂݍ��ޔz��̓Y����
	int imageIndex = 0;

	//1�s���摜��ǂݍ���
	while (std::getline(imageList, imagePath))
	{
		*(data + imageIndex) = LoadGraph(imagePath.c_str());

		++imageIndex;
	}
}


/// <summary>
/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
/// </summary>
/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
/// <param name="data">�F�ǂݍ��񂾉��f�[�^�n���h�����i�[����z��</param>
void CSV_LOADER::LoadSoundHandle(const char* path, std::vector<int>& data)
{
	//CSV�t�@�C�����J��
	std::ifstream imageList(path);

	//�摜�̃p�X
	std::string imagePath;

	//1�s���摜��ǂݍ���
	while (std::getline(imageList, imagePath))
	{
		data.emplace_back(LoadSoundMem(imagePath.c_str()));
	}
}