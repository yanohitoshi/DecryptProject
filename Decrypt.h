#pragma once

#include <iostream>
#include <fstream>

#define Block 1

// 名前空間定義
using namespace std;

class Decrypt
{
public:
	
	/*
	@brief	コンストラクタ
	@param	_openFileName　開くファイルの名前のポインタ
	@param _writeFileName　書き出しするファイルの名前のポインタ
	*/
	Decrypt(char* _openFileName, char* _writeFileName);
	
	/*
	@brief	デストラクタ
	*/
	~Decrypt();

	/*
	@brief	ファイルを開く
	@return true : 成功 , false : 失敗
	*/
	bool OpenFile();
	
	/*
	@brief  初期ベクトルの生成と最初のブロックの復号化
	*/
	void FirstWriteDecrypt();

	/*
	@brief  全てのブロックの復号化
	*/
	void AllWriteDecrypt();

private:

	/*
	@brief  復号化を行う関数
	@param	_dst　復号化するブロックのポインタ
	*/
	void Decode(char* _dst);

	// 開くファイル名
	string openFileName;

	// 書き出しを行うファイル名
	string writeFileName;

	// 開いたファイルの情報を読み込むファイル
	ifstream* ifsFile;

	// 書き出しを行うファイル
	ofstream* ofsFile;

	// 読み込みデータ
	// ifsをコピーする箱
	char data[Block];

	// 初期化ベクトル
	char initialData[Block];

	// 一時保存読み込みデータ
	char dataTemp[Block];

	// 1つ前の復号ブロック
	char cipherBlockPre[Block];

	// 復号ブロック
	char decodeBlock[Block];

	// 復号鍵
	char cipherBlockTemp[Block];
};

