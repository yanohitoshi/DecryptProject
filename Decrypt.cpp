#include "Decrypt.h"

Decrypt::Decrypt(char* _openFileName, char* _writeFileName)
    : openFileName(_openFileName)
    , writeFileName(_writeFileName)
{
}

Decrypt::~Decrypt()
{
    // 後片付け
    delete ifsFile;
    delete ofsFile;
}

bool Decrypt::OpenFile()
{
    // ファイルを開く
    ifsFile = new ifstream(openFileName, ios::binary);

    // ファイルが開けていなかったらエラー通知
    if (!ifsFile)
    {
        // コンソールにエラー描画
        cout << "ファイルが開けませんでした。" << endl;

        // 失敗した場合falseを返す
        return false;
    }

    // 成功していたらtrueを返す
    return true;
}

void Decrypt::FirstWriteDecrypt()
{
    // 何も書かれていないファイルを出力
    ofsFile = new ofstream(writeFileName, ios::app | ios::binary);

    // 初期化ベクトルを生成
    memset(initialData, 'I', Block);

    // 復号化する平文データを読み込み
    ifsFile->read(data, Block);

    // 1つ前の復号ブロックに復号化されているブロックを格納
    memcpy(cipherBlockPre, data, Block);

    // 復号化関数呼び出し
    Decode(data);

    // ブロック長ごとに処理
    for (int i = 0; i < Block; i++)
    {
        decodeBlock[i] = data[i] ^ initialData[i];
    }

    // 復号化したブロックを出力
    ofsFile->write(decodeBlock, Block);
}

void Decrypt::AllWriteDecrypt()
{
    // 先に作った復号ブロックを用いてファイルの終わりまでループ
    do
    {
        // データを読込み
        ifsFile->read(data, Block);
        memcpy(dataTemp, data, Block);

        //復号化関数呼び出し
        Decode(data);

        //ブロック長ごとに処理
        for (int i = 0; i < Block; i++)
        {
            decodeBlock[i] = data[i] ^ cipherBlockPre[i];
        }

        //復号化したブロックを出力
        ofsFile->write(decodeBlock, Block);

        //1つ前の復号ブロックに復号化されているブロックを格納
        memcpy(cipherBlockPre, dataTemp, Block);

    } while (!ifsFile->eof());
}

void Decrypt::Decode(char* _dst)
{
    // 復号カギを生成
    memset(cipherBlockTemp, 'S', Block);

    //ブロック長ごとに処理
    for (int i = 0; i < Block; i++)
    {
        // XOR演算を行い復号化
        _dst[i] = _dst[i] ^ cipherBlockTemp[i];
    }

    return;
}
