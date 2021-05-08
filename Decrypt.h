#pragma once

#include <iostream>
#include <fstream>

#define Block 1

// ���O��Ԓ�`
using namespace std;

class Decrypt
{
public:
	
	/*
	@brief	�R���X�g���N�^
	@param	_openFileName�@�J���t�@�C���̖��O�̃|�C���^
	@param _writeFileName�@�����o������t�@�C���̖��O�̃|�C���^
	*/
	Decrypt(char* _openFileName, char* _writeFileName);
	
	/*
	@brief	�f�X�g���N�^
	*/
	~Decrypt();

	/*
	@brief	�t�@�C�����J��
	@return true : ���� , false : ���s
	*/
	bool OpenFile();
	
	/*
	@brief  �����x�N�g���̐����ƍŏ��̃u���b�N�̕�����
	*/
	void FirstWriteDecrypt();

	/*
	@brief  �S�Ẵu���b�N�̕�����
	*/
	void AllWriteDecrypt();

private:

	/*
	@brief  ���������s���֐�
	@param	_dst�@����������u���b�N�̃|�C���^
	*/
	void Decode(char* _dst);

	// �J���t�@�C����
	string openFileName;

	// �����o�����s���t�@�C����
	string writeFileName;

	// �J�����t�@�C���̏���ǂݍ��ރt�@�C��
	ifstream* ifsFile;

	// �����o�����s���t�@�C��
	ofstream* ofsFile;

	// �ǂݍ��݃f�[�^
	// ifs���R�s�[���锠
	char data[Block];

	// �������x�N�g��
	char initialData[Block];

	// �ꎞ�ۑ��ǂݍ��݃f�[�^
	char dataTemp[Block];

	// 1�O�̕����u���b�N
	char cipherBlockPre[Block];

	// �����u���b�N
	char decodeBlock[Block];

	// ������
	char cipherBlockTemp[Block];
};

