#include <iostream>
#include "Decrypt.h"


int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        cout << "コマンドライン引数が空です。" << endl;
        cout << "Enterキーで終了" << endl;
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
        cout << "ファイルが開けませんでした。" << endl;
        cout << "Enterキーで終了" << endl;
        getchar();

        delete decrypt;

        return 0;
    }

}
