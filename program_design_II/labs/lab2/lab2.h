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
    OpenFile(); // 打开文件

private:
    ifstream readFile;                        // 待处理的文件
    ofstream writeFile;                       // 写入数据结果的文件
    string readPath, writePath;               // 读取、写入的文件地址
    unordered_map<string, int> wordsCountMap; // 统计词频的哈希表
    vector<string> topVec;                    // 用一个vector存储结果，便于按顺序展示
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