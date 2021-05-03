#include <iostream>
#include "Decrypt.h"


int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        cout << "�R�}���h���C����������ł��B" << endl;
        cout << "Enter�L�[�ŏI��" << endl;
        getchar();
        return 0;
    }


    Decrypt* decrypt;
    decrypt = new Decrypt(argv[1], argv[3]);

    bool success = decrypt->OpenFile();

    if (success)
    {
        decrypt->FirstWriteDecrypt();
        decrypt->AllWriteDecrypt();

        delete decrypt;

        return 0;
    }
    else
    {
        cout << "�t�@�C�����J���܂���ł����B" << endl;
        cout << "Enter�L�[�ŏI��" << endl;
        getchar();

        delete decrypt;

        return 0;
    }

}
