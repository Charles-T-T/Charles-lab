#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class FileProc{
public:
    OpenFile(); // ���ļ�

private:
    ifstream readFile;                        // ��������ļ�
    ofstream writeFile;                       // д�����ݽ�����ļ�
    string readPath, writePath;               // ��ȡ��д����ļ���ַ
    unordered_map<string, int> wordsCountMap; // ͳ�ƴ�Ƶ�Ĺ�ϣ��
    vector<string> topVec;                    // ��һ��vector�洢��������ڰ�˳��չʾ
};

FileProc::OpenFile()
{
    readFile.open(readPath);
    if (readFile.is_open())
        cout << readPath << " opened successfully!" << endl;
    else
    {
        while (1)
        {
            cout << "Fail to open the file, please input the correct path to the file again: ";
            cin >> readPath;
            readFile.open(readPath);
            if (readFile.is_open())
            {
                cout << "File opened successfully!" << endl;
                return;
            }
        }
    }
};