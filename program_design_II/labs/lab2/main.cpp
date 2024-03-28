#include "lab2.h"

int main()
{
    FileProc fp;
    fp.OpenFile();
    cout << "即将进入主菜单" << endl;
    system("pause");
    system("cls");

    while (1)
    {
        int choice = fp.MenuChoose();
        switch (choice)
        {
        case 0:
            cout << "即将退出程序，再见！" << endl;
            exit(0);
            break;

        case 1:
        {
            fp.WordsCount();
            string ifWrite;
            cout << "是否需要将该结果写入其他文件（1：是，0：否）：";
            getline(cin, ifWrite);
            if (LegalChoice(ifWrite, 0, 1))
                fp.WriteResult();
            cout << "即将返回主菜单" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 2:
            fp.LinesWithT();
            cout << "即将返回主菜单" << endl;
            system("pause");
            system("cls");
            break;

        default:
            break;
        }
    }

    return 0;
}