#include "lab2.h"

int main()
{
  FileProc fp;
  fp.OpenFile();
  cout << "�����������˵�" << endl;
  system("pause");
  system("cls");

  while (1)
  {
    int choice = fp.MenuChoose();
    switch (choice)
    {
    case 0:
      cout << "�����˳������ټ���" << endl;
      exit(0);
      break;

    case 1:
      fp.WordsCount();
      cout << "��ӡ�����������������˵�" << endl;
      system("pause");
      system("cls");
      break;

    case 2:
      fp.LinesWithT();
      cout << "��ӡ�����������������˵�" << endl;
      system("pause");
      system("cls");
      break;

    default:
      break;
    }
  }

  return 0;
}