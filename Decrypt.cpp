#include "Decrypt.h"

Decrypt::Decrypt(char* _openFileName, char* _writeFileName)
    : openFileName(_openFileName)
    , writeFileName(_writeFileName)
{
}

Decrypt::~Decrypt()
{
    // ��Еt��
    delete ifsFile;
    delete ofsFile;
}

bool Decrypt::OpenFile()
{
    // �t�@�C�����J��
    ifsFile = new ifstream(openFileName, ios::binary);

    // �t�@�C�����J���Ă��Ȃ�������G���[�ʒm
    if (!ifsFile)
    {
        // �R���\�[���ɃG���[�`��
        cout << "�t�@�C�����J���܂���ł����B" << endl;

        // ���s�����ꍇfalse��Ԃ�
        return false;
    }

    // �������Ă�����true��Ԃ�
    return true;
}

void Decrypt::FirstWriteDecrypt()
{
    // ����������Ă��Ȃ��t�@�C�����o��
    ofsFile = new ofstream(writeFileName, ios::app | ios::binary);

    // �������x�N�g���𐶐�
    memset(initialData, 'I', Block);

    // ���������镽���f�[�^��ǂݍ���
    ifsFile->read(data, Block);

    // 1�O�̕����u���b�N�ɕ���������Ă���u���b�N���i�[
    memcpy(cipherBlockPre, data, Block);

    // �������֐��Ăяo��
    Decode(data);

    // �u���b�N�����Ƃɏ���
    for (int i = 0; i < Block; i++)
    {
        decodeBlock[i] = data[i] ^ initialData[i];
    }

    // �����������u���b�N���o��
    ofsFile->write(decodeBlock, Block);
}

void Decrypt::AllWriteDecrypt()
{
    // ��ɍ���������u���b�N��p���ăt�@�C���̏I���܂Ń��[�v
    do
    {
        // �f�[�^��Ǎ���
        ifsFile->read(data, Block);
        memcpy(dataTemp, data, Block);

        //�������֐��Ăяo��
        Decode(data);

        //�u���b�N�����Ƃɏ���
        for (int i = 0; i < Block; i++)
        {
            decodeBlock[i] = data[i] ^ cipherBlockPre[i];
        }

        //�����������u���b�N���o��
        ofsFile->write(decodeBlock, Block);

        //1�O�̕����u���b�N�ɕ���������Ă���u���b�N���i�[
        memcpy(cipherBlockPre, dataTemp, Block);

    } while (!ifsFile->eof());
}

void Decrypt::Decode(char* _dst)
{
    // �����J�M�𐶐�
    memset(cipherBlockTemp, 'S', Block);

    //�u���b�N�����Ƃɏ���
    for (int i = 0; i < Block; i++)
    {
        // XOR���Z���s��������
        _dst[i] = _dst[i] ^ cipherBlockTemp[i];
    }

    return;
}
