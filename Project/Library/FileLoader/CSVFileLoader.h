#pragma once

#include <vector>

//CSV�t�@�C���ǂݍ��ݏ���
namespace CSV_LOADER
{
	/// <summary>
	/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
	/// </summary>
	/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
	/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
	void LoadHandle(const char* path, std::vector<int>& data);

	/// <summary>
	/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
	/// </summary>
	/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
	/// <param name="data">�F�ǂݍ��񂾃f�[�^���i�[����z��</param>
	void LoadHandle(const char* path, int* data);

	/// <summary>
	/// ������pathCSV�t�@�C����ǂݍ��݁A�n���h����data�ɓ����
	/// </summary>
	/// <param name="path">�F�ǂݍ���CSV�t�@�C���ւ̃p�X</param>
	/// <param name="data">�F�ǂݍ��񂾉��f�[�^�n���h�����i�[����z��</param>
	void LoadSoundHandle(const char* path, std::vector<int>& data);

};
