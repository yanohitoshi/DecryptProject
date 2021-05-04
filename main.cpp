#include <iostream>
#include "Decrypt.h"

bool ChackArgument(int _count, char* argv, bool _isAbridgementOption);

int main(int argc, char* argv[])
{
    // コマンドライン引数が空でないかチェック
    if (argc <= 1)
    {
        cout << "ERROR::コマンドライン引数が空です::ERROR" << endl;
        cout << "Enterキーで終了" << endl;
        getchar();
        return 0;
    }
    else if (argc > 5)
    {
        cout << "ERROR::コマンドライン引数が許容範囲を超えています::ERROR" << endl;
        cout << "Enterキーで終了" << endl;
        getchar();
        return 0;
    }

    // オプションが省略して使われているかチェックフラグ変数
    string firstArg = argv[1];
    bool isAbridgementOption = false;

    if (firstArg == "-oi" || firstArg == "-io")
    {
        isAbridgementOption = true;
        if (argc > 4)
        {
            cout << "ERROR::オプションに対して引数が多いです::ERROR" << endl;
            cout << "Enterキーで終了" << endl;
            getchar();
            return 0;
        }
    }
    else if (firstArg == "-i" || firstArg == "-o")
    {
        if (argc <= 4)
        {
            cout << "ERROR::オプションに対して引数が少ないです::ERROR" << endl;
            cout << "Enterキーで終了" << endl;
            getchar();
            return 0;
        }
    }

    // コマンドライン引数チェック用フラグ変数
    bool argumentChack = false;

    // 全コマンドライン引数をチェック
    for (int chackCount = 1; chackCount < argc; chackCount++)
    {
        argumentChack = ChackArgument(chackCount, argv[chackCount], isAbridgementOption);

        cout << "argumentChack" << endl;
        cout << argumentChack << endl;
    }

    // 先に入力ファイル名が入っているかどうか
    bool isFirstInput = false;

    if (firstArg == "-i" || firstArg == "-io")
    {
        isFirstInput = true;
    }

    if (argumentChack)
    {

        Decrypt* decrypt;

        if (isFirstInput)
        {
            cout << "入力が先" << endl;
        }

        if (isAbridgementOption)
        {
            cout << "省略" << endl;
        }

        if (isFirstInput)
        {
            if (isAbridgementOption)
            {
                decrypt = new Decrypt(argv[2], argv[3]);
            }
            else
            {
                decrypt = new Decrypt(argv[2], argv[4]);
            }
        }
        else
        {
            if (isAbridgementOption)
            {
                decrypt = new Decrypt(argv[3], argv[2]);
            }
            else
            {
                decrypt = new Decrypt(argv[4], argv[2]);
            }
        }


        bool success = decrypt->OpenFile();

        if (success)
        {
            decrypt->FirstWriteDecrypt();
            decrypt->AllWriteDecrypt();

            delete decrypt;

            cout << "終了しました。" << endl;

            return 0;
        }
        else
        {
            cout << "Enterキーで終了" << endl;
            getchar();

            delete decrypt;

            return 0;
        }
    }


}

bool ChackArgument(int _count, char* _argv, bool _isAbridgementOption)
{
    bool nullChack = false;

    if (_argv != nullptr)
    {
        nullChack = true;
    }

    bool erroeChack = false;

    if (nullChack)
    {
        // コマンドライン引数のチェック用string変数
        string chackArgument = _argv;

        switch (_count)
        {
        case 1:
            cout << "case1" << endl;
            cout << chackArgument << endl;
            // オプションが入って無ければエラーを返す
            if (chackArgument != "-o" && chackArgument != "-i" &&
                chackArgument != "-oi" && chackArgument != "-io")
            {
                cout << "ERROR::オプションを入力してください::ERROR" << endl;
                cout << "Enterキーで終了" << endl;
                getchar();
                erroeChack = false;
            }
            erroeChack = true;
            break;

        case 2:
            cout << "case2" << endl;
            cout << chackArgument << endl;
            // オプションが入っていたらエラーを返す
            if (chackArgument == "-o" || chackArgument == "-i" ||
                chackArgument == "-oi" || chackArgument == "-io")
            {
                cout << "ERROR::ファイル名を入力してください::ERROR" << endl;
                cout << "Enterキーで終了" << endl;
                getchar();
                erroeChack = false;
            }
            erroeChack = true;
            break;

        case 3:

            cout << "case3" << endl;
            cout << chackArgument << endl;
            cout << _isAbridgementOption << endl;

            if (!_isAbridgementOption)
            {
                // オプションが入って無ければエラーを返す
                if (chackArgument != "-o" && chackArgument != "-i" &&
                    chackArgument != "-oi" && chackArgument != "-io")
                {
                    cout << "ERROR::オプションを入力してください::ERROR" << endl;
                    cout << "Enterキーで終了" << endl;
                    getchar();
                    erroeChack = false;
                }

            }

            erroeChack = true;
            break;

        case 4:
            cout << "case4" << endl;
            cout << chackArgument << endl;
            // オプションが入っていたらエラーを返す
            if (chackArgument == "-o" || chackArgument == "-i" ||
                chackArgument == "-oi" || chackArgument == "-io")
            {
                cout << "ERROR::ファイル名を入力してください::ERROR" << endl;
                cout << "Enterキーで終了" << endl;
                getchar();
                erroeChack = false;
            }
            erroeChack = true;
            break;
        }
    }

    return erroeChack;

}
