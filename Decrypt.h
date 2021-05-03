#pragma once

#include <iostream>
#include <fstream>

#define Block 1

// 名前空間定義
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

	// 開くファイル名
	string openFileName;
	// 書き出しを行うファイル名
	string writeFileName;

	// 開いたファイルの情報を読み込むファイル
	ifstream* ifsFile;
	// 書き出しを行うファイル
	ofstream* ofsFile;

	//読み込みデータ
	// ifsをコピーする箱
	char data[Block];

	//初期化ベクトル
	char initialData[Block];

	//一時保存読み込みデータ
	char dataTemp[Block];

	//1つ前の暗号ブロック
	char cipherBlockPre[Block];

	//暗号ブロック
	char decodeBlock[Block];

};

