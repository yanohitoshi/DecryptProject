#include <iostream>
#include "Decrypt.h"

/*
@enum 何番目の引数なのか判別するためのnameTag
*/
enum ArgumentName
{
    PASS = 0,
    FIRST = 1,
    SECOND = 2,
    THIRD = 3,
    FOURTH = 4,
    OVER = 5
};

/*
@brief	コマンドライン引数チェックする関数
@param _count　何番目の引数なのかの数
@param _argv　文字列のポインタ
@param	_isAbridgementOption　省略されているかのフラグ
@return true : 成功 , false : 失敗
*/
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
    else if (argc > OVER) // 引数が必要以上に入っていないか
    {
        cout << "ERROR::コマンドライン引数が許容範囲を超えています::ERROR" << endl;
        cout << "Enterキーで終了" << endl;
        getchar();
        return 0;
    }

    // オプションが省略して使われているかチェックフラグ変数
    string firstArg = argv[FIRST];

    // 省略チェック用フラグ
    bool isAbridgementOption = false;

    // 1つ目の変数に省略オプションが入っているかチェック
    if (firstArg == "-oi" || firstArg == "-io")
    {
        // 省略されていたら省略チェック用フラグをtrue
        isAbridgementOption = true;
        // この場合にコマンドライン引数が必要以上に入っていたらエラー通知後終了

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
        // 省略されていなかったら省略チェック用フラグをfalse
        isAbridgementOption = false;
        // この場合にコマンドライン引数が必要以上に入っていたらエラー通知後終了
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
        // trueもしくはfalseを返すコマンドライン引数をチェック関数呼び出し
        argumentChack = ChackArgument(chackCount, argv[chackCount], isAbridgementOption);
    }

    // 先に入力ファイル名が入っているかどうか
    bool isFirstInput = false;

    // 入力オプションが先に来ているかチェック
    if (firstArg == "-i" || firstArg == "-io")
    {
        isFirstInput = true;
    }

    // 変数チェックが成功していたら
    if (argumentChack)
    {
        // 復号化クラスのポインタ
        Decrypt* decrypt;

        // 入力が先に来ていたら入力ファイルネームを先に渡す
        if (isFirstInput)
        {
            // 省略されていたら
            if (isAbridgementOption)
            {
                // 省略された形で引数にファイルネームを渡す
                decrypt = new Decrypt(argv[SECOND], argv[THIRD]);
            }
            else // 省略されていなかったら
            {
                // 省略されていない形で引数にファイルネームを渡す
                decrypt = new Decrypt(argv[SECOND], argv[FOURTH]);
            }
        }
        else // 出力が先に来ていたら入力ファイルネームを先に渡す
        {
            // 省略されていたら
            if (isAbridgementOption)
            {
                // 省略された形で引数にファイルネームを渡す
                decrypt = new Decrypt(argv[THIRD], argv[SECOND]);
            }
            else // 省略されていなかったら
            {
                // 省略されていない形で引数にファイルネームを渡す
                decrypt = new Decrypt(argv[FOURTH], argv[SECOND]);
            }
        }

        // ファイルを開く関数を呼び出す
        // ファイルが開けていたらtrueを変えす
        bool success = decrypt->OpenFile();

        // 成功していたら
        if (success)
        {
            // 初期化ベクトルと最初の復号文の生成
            decrypt->FirstWriteDecrypt();

            // 残りの全暗号化を復号化する関数を呼び出す
            decrypt->AllWriteDecrypt();

            // ポインタの後処理
            delete decrypt;

            // 終了通知
            cout << "終了しました。" << endl;

            // 終了
            return 0;
        }
        else
        {
            // キー入力で終了をコンソール描画
            cout << "Enterキーで終了" << endl;
            getchar();

            // ポインタの後処理
            delete decrypt;

            // 終了
            return 0;
        }
    }
}

bool ChackArgument(int _count, char* _argv, bool _isAbridgementOption)
{
    // nullチェック用フラグ
    bool nullChack = false;

    // nullじゃなかったら
    if (_argv != nullptr)
    {
        // nullチェック用フラグをtrueに
        nullChack = true;
    }

    // エラーチェック用フラグ
    bool erroeChack = false;

    // nullチェックがtrueだったら
    if (nullChack)
    {
        // コマンドライン引数のチェック用string変数
        string chackArgument = _argv;

        // 何個目の引数なのかを見る
        switch (_count)
        {
        case FIRST:

            // オプションが入って無ければエラーを返す
            if (chackArgument != "-o" && chackArgument != "-i" &&
                chackArgument != "-oi" && chackArgument != "-io")
            {
                cout << "ERROR::オプションを入力してください::ERROR" << endl;
                cout << "Enterキーで終了" << endl;
                getchar();

                // エラーフラグをfalse
                erroeChack = false;
            }

            // エラーフラグをtrue
            erroeChack = true;
            break;

        case SECOND:

            // オプションが入っていたらエラーを返す
            if (chackArgument == "-o" || chackArgument == "-i" ||
                chackArgument == "-oi" || chackArgument == "-io")
            {
                cout << "ERROR::ファイル名を入力してください::ERROR" << endl;
                cout << "Enterキーで終了" << endl;
                getchar();

                // エラーフラグをfalse
                erroeChack = false;
            }

            // エラーフラグをtrue
            erroeChack = true;
            break;

        case THIRD:

            // 省略されていなかったら
            if (!_isAbridgementOption)
            {
                // オプションが入って無ければエラーを返す
                if (chackArgument != "-o" && chackArgument != "-i" &&
                    chackArgument != "-oi" && chackArgument != "-io")
                {
                    cout << "ERROR::オプションを入力してください::ERROR" << endl;
                    cout << "Enterキーで終了" << endl;
                    getchar();

                    // エラーフラグをfalse
                    erroeChack = false;
                }
            }

            // エラーフラグをtrue
            erroeChack = true;
            break;

        case FOURTH:

            // オプションが入っていたらエラーを返す
            if (chackArgument == "-o" || chackArgument == "-i" ||
                chackArgument == "-oi" || chackArgument == "-io")
            {
                cout << "ERROR::ファイル名を入力してください::ERROR" << endl;
                cout << "Enterキーで終了" << endl;
                getchar();

                // エラーフラグをfalse
                erroeChack = false;
            }

            // エラーフラグをtrue
            erroeChack = true;

            break;
        }
    }

    // 成功もしくは失敗を返す
    return erroeChack;

}
