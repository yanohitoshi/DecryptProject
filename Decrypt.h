#pragma once

#include <iostream>
#include <fstream>

#define Block 1

// ���O��Ԓ�`
using namespace std;

class Decrypt
{
public:

	Decrypt(char* _openFileName, char* _writeFileName);
	~Decrypt();

	bool OpenFile();
	void FirstWriteDecrypt();
	void AllWriteDecrypt();
private:

	void Decode(char* dst);

	// �J���t�@�C����
	string openFileName;
	// �����o�����s���t�@�C����
	string writeFileName;

	// �J�����t�@�C���̏���ǂݍ��ރt�@�C��
	ifstream* ifsFile;
	// �����o�����s���t�@�C��
	ofstream* ofsFile;

	//�ǂݍ��݃f�[�^
	// ifs���R�s�[���锠
	char data[Block];

	//�������x�N�g��
	char initialData[Block];

	//�ꎞ�ۑ��ǂݍ��݃f�[�^
	char dataTemp[Block];

	//1�O�̈Í��u���b�N
	char cipherBlockPre[Block];

	//�Í��u���b�N
	char decodeBlock[Block];

};

