#include "Decrypt.h"

Decrypt::Decrypt(char* _openFileName, char* _writeFileName)
    : openFileName(_openFileName)
    , writeFileName(_writeFileName)
{
}

Decrypt::~Decrypt()
{
}

bool Decrypt::OpenFile()
{
    ifsFile = new ifstream(openFileName, ios::binary);

    if (!ifsFile)
    {
        return false;
    }

    return true;
}

void Decrypt::FirstWriteDecrypt()
{
    ofsFile = new ofstream(writeFileName, ios::app | ios::binary);

    memset(initialData, 'I', Block);

    //データの読込み
    ifsFile->read(data, Block);

    //1つ前の暗号ブロックに暗号化されているブロックを格納
    memcpy(cipherBlockPre, data, Block);

    //復号化
    Decode(data);
    //ブロック長ごとに処理

    for (int i = 0; i < Block; i++)
    {
        decodeBlock[i] = data[i] ^ initialData[i];
    }

    //暗号化したブロックを出力
    ofsFile->write(decodeBlock, Block);
}

void Decrypt::AllWriteDecrypt()
{
    do
    {

        //データ読込
        ifsFile->read(data, Block);

        //データがなかった場合終了する。
        memcpy(dataTemp, data, Block);

        //復号化
        Decode(data);

        //ブロック長ごとに処理
        for (int i = 0; i < Block; i++)
        {
            decodeBlock[i] = data[i] ^ cipherBlockPre[i];
        }

        //暗号化したブロックを出力
        ofsFile->write(decodeBlock, Block);

        //1つ前の暗号ブロックに暗号化されているブロックを格納
        memcpy(cipherBlockPre, dataTemp, Block);

    } while (!ifsFile->eof());
}

void Decrypt::Decode(char* dst)
{
    //暗号鍵
    char cipherBlockTemp[Block];

    memset(cipherBlockTemp, 'S', Block);

    //ブロック長ごとに処理
    for (int i = 0; i < Block; i++)
    {
        //XOR暗号
        dst[i] = dst[i] ^ cipherBlockTemp[i];
    }

    return;
}
