#include <iostream>
#include "Decrypt.h"

/*
@enum ���Ԗڂ̈����Ȃ̂����ʂ��邽�߂�nameTag
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
@brief	�R�}���h���C�������`�F�b�N����֐�
@param _count�@���Ԗڂ̈����Ȃ̂��̐�
@param _argv�@������̃|�C���^
@param	_isAbridgementOption�@�ȗ�����Ă��邩�̃t���O
@return true : ���� , false : ���s
*/
bool ChackArgument(int _count, char* argv, bool _isAbridgementOption);


int main(int argc, char* argv[])
{
    // �R�}���h���C����������łȂ����`�F�b�N
    if (argc <= 1)
    {
        cout << "ERROR::�R�}���h���C����������ł�::ERROR" << endl;
        cout << "Enter�L�[�ŏI��" << endl;
        getchar();
        return 0;
    }
    else if (argc > OVER) // �������K�v�ȏ�ɓ����Ă��Ȃ���
    {
        cout << "ERROR::�R�}���h���C�����������e�͈͂𒴂��Ă��܂�::ERROR" << endl;
        cout << "Enter�L�[�ŏI��" << endl;
        getchar();
        return 0;
    }

    // �I�v�V�������ȗ����Ďg���Ă��邩�`�F�b�N�t���O�ϐ�
    string firstArg = argv[FIRST];

    // �ȗ��`�F�b�N�p�t���O
    bool isAbridgementOption = false;

    // 1�ڂ̕ϐ��ɏȗ��I�v�V�����������Ă��邩�`�F�b�N
    if (firstArg == "-oi" || firstArg == "-io")
    {
        // �ȗ�����Ă�����ȗ��`�F�b�N�p�t���O��true
        isAbridgementOption = true;
        // ���̏ꍇ�ɃR�}���h���C���������K�v�ȏ�ɓ����Ă�����G���[�ʒm��I��

        isAbridgementOption = true;
        if (argc > 4)
        {
            cout << "ERROR::�I�v�V�����ɑ΂��Ĉ����������ł�::ERROR" << endl;
            cout << "Enter�L�[�ŏI��" << endl;
            getchar();
            return 0;
        }
    }
    else if (firstArg == "-i" || firstArg == "-o")
    {
        // �ȗ�����Ă��Ȃ�������ȗ��`�F�b�N�p�t���O��false
        isAbridgementOption = false;
        // ���̏ꍇ�ɃR�}���h���C���������K�v�ȏ�ɓ����Ă�����G���[�ʒm��I��
        if (argc <= 4)
        {
            cout << "ERROR::�I�v�V�����ɑ΂��Ĉ��������Ȃ��ł�::ERROR" << endl;
            cout << "Enter�L�[�ŏI��" << endl;
            getchar();
            return 0;
        }
    }

    // �R�}���h���C�������`�F�b�N�p�t���O�ϐ�
    bool argumentChack = false;

    // �S�R�}���h���C���������`�F�b�N
    for (int chackCount = 1; chackCount < argc; chackCount++)
    {
        // true��������false��Ԃ��R�}���h���C���������`�F�b�N�֐��Ăяo��
        argumentChack = ChackArgument(chackCount, argv[chackCount], isAbridgementOption);
    }

    // ��ɓ��̓t�@�C�����������Ă��邩�ǂ���
    bool isFirstInput = false;

    // ���̓I�v�V��������ɗ��Ă��邩�`�F�b�N
    if (firstArg == "-i" || firstArg == "-io")
    {
        isFirstInput = true;
    }

    // �ϐ��`�F�b�N���������Ă�����
    if (argumentChack)
    {
        // �������N���X�̃|�C���^
        Decrypt* decrypt;

        // ���͂���ɗ��Ă�������̓t�@�C���l�[�����ɓn��
        if (isFirstInput)
        {
            // �ȗ�����Ă�����
            if (isAbridgementOption)
            {
                // �ȗ����ꂽ�`�ň����Ƀt�@�C���l�[����n��
                decrypt = new Decrypt(argv[SECOND], argv[THIRD]);
            }
            else // �ȗ�����Ă��Ȃ�������
            {
                // �ȗ�����Ă��Ȃ��`�ň����Ƀt�@�C���l�[����n��
                decrypt = new Decrypt(argv[SECOND], argv[FOURTH]);
            }
        }
        else // �o�͂���ɗ��Ă�������̓t�@�C���l�[�����ɓn��
        {
            // �ȗ�����Ă�����
            if (isAbridgementOption)
            {
                // �ȗ����ꂽ�`�ň����Ƀt�@�C���l�[����n��
                decrypt = new Decrypt(argv[THIRD], argv[SECOND]);
            }
            else // �ȗ�����Ă��Ȃ�������
            {
                // �ȗ�����Ă��Ȃ��`�ň����Ƀt�@�C���l�[����n��
                decrypt = new Decrypt(argv[FOURTH], argv[SECOND]);
            }
        }

        // �t�@�C�����J���֐����Ăяo��
        // �t�@�C�����J���Ă�����true��ς���
        bool success = decrypt->OpenFile();

        // �������Ă�����
        if (success)
        {
            // �������x�N�g���ƍŏ��̕������̐���
            decrypt->FirstWriteDecrypt();

            // �c��̑S�Í����𕜍�������֐����Ăяo��
            decrypt->AllWriteDecrypt();

            // �|�C���^�̌㏈��
            delete decrypt;

            // �I���ʒm
            cout << "�I�����܂����B" << endl;

            // �I��
            return 0;
        }
        else
        {
            // �L�[���͂ŏI�����R���\�[���`��
            cout << "Enter�L�[�ŏI��" << endl;
            getchar();

            // �|�C���^�̌㏈��
            delete decrypt;

            // �I��
            return 0;
        }
    }
}

bool ChackArgument(int _count, char* _argv, bool _isAbridgementOption)
{
    // null�`�F�b�N�p�t���O
    bool nullChack = false;

    // null����Ȃ�������
    if (_argv != nullptr)
    {
        // null�`�F�b�N�p�t���O��true��
        nullChack = true;
    }

    // �G���[�`�F�b�N�p�t���O
    bool erroeChack = false;

    // null�`�F�b�N��true��������
    if (nullChack)
    {
        // �R�}���h���C�������̃`�F�b�N�pstring�ϐ�
        string chackArgument = _argv;

        // ���ڂ̈����Ȃ̂�������
        switch (_count)
        {
        case FIRST:

            // �I�v�V�����������Ė�����΃G���[��Ԃ�
            if (chackArgument != "-o" && chackArgument != "-i" &&
                chackArgument != "-oi" && chackArgument != "-io")
            {
                cout << "ERROR::�I�v�V��������͂��Ă�������::ERROR" << endl;
                cout << "Enter�L�[�ŏI��" << endl;
                getchar();

                // �G���[�t���O��false
                erroeChack = false;
            }

            // �G���[�t���O��true
            erroeChack = true;
            break;

        case SECOND:

            // �I�v�V�����������Ă�����G���[��Ԃ�
            if (chackArgument == "-o" || chackArgument == "-i" ||
                chackArgument == "-oi" || chackArgument == "-io")
            {
                cout << "ERROR::�t�@�C��������͂��Ă�������::ERROR" << endl;
                cout << "Enter�L�[�ŏI��" << endl;
                getchar();

                // �G���[�t���O��false
                erroeChack = false;
            }

            // �G���[�t���O��true
            erroeChack = true;
            break;

        case THIRD:

            // �ȗ�����Ă��Ȃ�������
            if (!_isAbridgementOption)
            {
                // �I�v�V�����������Ė�����΃G���[��Ԃ�
                if (chackArgument != "-o" && chackArgument != "-i" &&
                    chackArgument != "-oi" && chackArgument != "-io")
                {
                    cout << "ERROR::�I�v�V��������͂��Ă�������::ERROR" << endl;
                    cout << "Enter�L�[�ŏI��" << endl;
                    getchar();

                    // �G���[�t���O��false
                    erroeChack = false;
                }
            }

            // �G���[�t���O��true
            erroeChack = true;
            break;

        case FOURTH:

            // �I�v�V�����������Ă�����G���[��Ԃ�
            if (chackArgument == "-o" || chackArgument == "-i" ||
                chackArgument == "-oi" || chackArgument == "-io")
            {
                cout << "ERROR::�t�@�C��������͂��Ă�������::ERROR" << endl;
                cout << "Enter�L�[�ŏI��" << endl;
                getchar();

                // �G���[�t���O��false
                erroeChack = false;
            }

            // �G���[�t���O��true
            erroeChack = true;

            break;
        }
    }

    // �����������͎��s��Ԃ�
    return erroeChack;

}
