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

    //�f�[�^�̓Ǎ���
    ifsFile->read(data, Block);

    //1�O�̈Í��u���b�N�ɈÍ�������Ă���u���b�N���i�[
    memcpy(cipherBlockPre, data, Block);

    //������
    Decode(data);
    //�u���b�N�����Ƃɏ���

    for (int i = 0; i < Block; i++)
    {
        decodeBlock[i] = data[i] ^ initialData[i];
    }

    //�Í��������u���b�N���o��
    ofsFile->write(decodeBlock, Block);
}

void Decrypt::AllWriteDecrypt()
{
    do
    {

        //�f�[�^�Ǎ�
        ifsFile->read(data, Block);

        //�f�[�^���Ȃ������ꍇ�I������B
        memcpy(dataTemp, data, Block);

        //������
        Decode(data);

        //�u���b�N�����Ƃɏ���
        for (int i = 0; i < Block; i++)
        {
            decodeBlock[i] = data[i] ^ cipherBlockPre[i];
        }

        //�Í��������u���b�N���o��
        ofsFile->write(decodeBlock, Block);

        //1�O�̈Í��u���b�N�ɈÍ�������Ă���u���b�N���i�[
        memcpy(cipherBlockPre, dataTemp, Block);

    } while (!ifsFile->eof());
}

void Decrypt::Decode(char* dst)
{
    //�Í���
    char cipherBlockTemp[Block];

    memset(cipherBlockTemp, 'S', Block);

    //�u���b�N�����Ƃɏ���
    for (int i = 0; i < Block; i++)
    {
        //XOR�Í�
        dst[i] = dst[i] ^ cipherBlockTemp[i];
    }

    return;
}
