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
    FileProc() {}
    FileProc(const string &readPath, const string &writePath) : readPath(readPath), writePath(writePath) {}
    ~FileProc() {
        if (readFile.is_open())
            readFile.close();
        if (writeFile.is_open())
            writeFile.close();
    }

    int MenuChoose(); // 用户选择菜单上的功能
    void OpenFile(); // 打开文件
    void WordsCount(); // 统计词频
    void WriteResult(); // 写入结果

private:
    ifstream readFile;                        // 待处理的文件
    ofstream writeFile;                       // 写入数据结果的文件
    string readPath, writePath;               // 读取、写入的文件地址
    unordered_map<string, int> wordsCountMap; // 统计词频的哈希表
    vector<string> topVec;                    // 用一个vector存储结果，便于按顺序展示
};

int FileProc::MenuChoose(){
    cout << "----------------------------" << endl;
    cout << "           主菜单           " << endl;
    cout << "----------------------------" << endl;
    cout << "1. 统计词频: 出现最多的前50词" << endl;
    cout << "2. 显示待查询词所在行信息" << endl;

    int choice;
    cout << "----------------------------" << endl;
    cout << "请输入要进行的操作(1-2): ";
    cin >> choice;
    return choice;
}

void FileProc::OpenFile()
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
}

void FileProc::WordsCount(){
    string line, word;
    while (getline(readFile, line))
    {
        stringstream ss(line);
        while (ss >> word)
        {
            wordsCountMap[word]++;
        }
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq; // 利用优先队列统计词频最高的字符串
    for (const auto &pair : wordsCountMap)
    {
        pq.push(make_pair(pair.second, pair.first));
        if (pq.size() > 50) // pop掉50名以外的字符串
            pq.pop();
    }

    while (!pq.empty())
    {
        topVec.push_back(pq.top().second); // 便于之后按从大到小顺序打印
        pq.pop();
    }

    cout << "-----------------------" << endl;
    cout << "TOP50 Frequent Strings" << endl;
    cout << "-----------------------" << endl;
    for (int i = topVec.size() - 1; i >= 0; i--)
        cout << topVec[i] << ": " << wordsCountMap[topVec[i]] << endl;
    cout << "-----------------------" << endl;
}

void FileProc::WriteResult()
{
    writeFile.open(writePath);
    cout << "Writing the result to " << writePath << "..." << endl;
    for (int i = topVec.size() - 1; i >= 0; i--)
        writeFile << topVec[i] << ": " << wordsCountMap[topVec[i]] << "\n";
    cout << "Result written successfully!" << endl;
}