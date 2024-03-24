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
      fp.WordsCount();
      cout << "打印结束，即将返回主菜单" << endl;
      system("pause");
      system("cls");
      break;

    case 2:
      fp.LinesWithT();
      cout << "打印结束，即将返回主菜单" << endl;
      system("pause");
      system("cls");
      break;

    default:
      break;
    }
  }

  return 0;
}