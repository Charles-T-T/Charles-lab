#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <sstream>
#include <regex>

#define DEBUG_MOOD 0

using namespace std;

class FileProc
{
public:
    FileProc() : readPath("nullPath"), writePath("nullPath") {}
    FileProc(const string &readPath, const string &writePath) : readPath(readPath), writePath(writePath) {}
    ~FileProc()
    {
        if (readFile.is_open())
            readFile.close();
        if (writeFile.is_open())
            writeFile.close();
    }

    int MenuChoose();   // 用户选择菜单上的功能
    void OpenFile();    // 打开文件
    void RestartRead(); // 重新从头处理readFile

    /* 功能1 */
    void WordsCount();  // 统计词频
    void WriteResult(); // 写入结果

    /* 功能2 */
    void LinesWithT(); // 显示带查询词所在的行

private:
    ifstream readFile;                        // 待处理的文件
    ofstream writeFile;                       // 写入数据结果的文件
    string readPath, writePath;               // 读取、写入的文件地址
    unordered_map<string, int> wordsCountMap; // 统计词频的哈希表
    vector<string> topVec;                    // 用一个vector存储结果，便于按顺序展示
};

int LegalChoice(string choice, int low, int high); // 检查输入选项是否合法
int FileProc::MenuChoose()
{
    cout << "----------------------------" << endl;
    cout << "           主菜单           " << endl;
    cout << "----------------------------" << endl;
    cout << "1. 打印出现最多的前50词" << endl;
    cout << "2. 显示待查询词所在行信息" << endl;
    cout << "0. 退出程序" << endl;

    string choice;
    cout << "----------------------------" << endl;
    cout << "请选择要进行的操作(0-2): ";
    getline(cin, choice);

    return LegalChoice(choice, 0, 2);
}

void FileProc::OpenFile()
{
    if (readPath == "nullPath")
    {
        cout << "请输入待打开文件的路径：";
        getline(cin, readPath);
    }
    readFile.open(readPath);
    while (!readFile.is_open())
    {
        cout << "文件打开失败，请重新输入文件路径: ";
        getline(cin, readPath);
        readFile.open(readPath);
    }
    cout << readPath << "打开成功!" << endl;
}

void FileProc::RestartRead()
{
    readFile.clear();
    readFile.seekg(0);
}

void FileProc::WordsCount()
{
    this->RestartRead();
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
    cout << "     TOP50 高频词" << endl;
    cout << "-----------------------" << endl;
    for (int i = topVec.size() - 1; i >= 0; i--)
        cout << topVec[i] << ":\t\t" << wordsCountMap[topVec[i]] << endl;
    cout << "-----------------------" << endl;
}

void FileProc::WriteResult()
{
    if (writePath == "nullPath")
    {
        cout << "请输入待写入文件的路径：";
        getline(cin, writePath);
    }
    writeFile.open(writePath);
    while (!writeFile.is_open())
    {
        cout << "文件打开失败，请重新输入文件路径：";
        getline(cin, writePath);
    }
    cout << "结果正在写入" << writePath << "..." << endl;
    for (int i = topVec.size() - 1; i >= 0; i--){
        // TODO 检查是否写入成功
        if (DEBUG_MOOD){
            cout << "writing " << i << endl;
        }
        writeFile << topVec[i] << ":\t\t" << wordsCountMap[topVec[i]] << "\n";
    }
    writeFile.close();

    cout << "结果写入成功!" << endl;
}

void FileProc::LinesWithT()
{
    this->RestartRead();
    string target, line, word;
    vector<string> lines;
    int lineCount = 0;
    cout << "请输入待查询词：";
    getline(cin, target);
    string ifFuzzy;
    cout << "是否开启模糊查询（1：是，0：否）：";
    getline(cin, ifFuzzy);
    switch (LegalChoice(ifFuzzy, 0, 1))
    {
    case 0:
        while (getline(readFile, line))
        {
            stringstream ss(line);
            while (ss >> word)
            {
                if (word == target)
                {
                    lines.push_back(line);
                    lineCount++;
                    break;
                }
            }
        }
        break;

    case 1:
    {
        regex pattern(".*" + target + ".*");
        while (getline(readFile, line))
        {
            if (regex_match(line, pattern))
            {
                lines.push_back(line);
                lineCount++;
            }
        }
        break;
    }

    default:
        break;
    }

    cout << "-----------------------" << endl;
    cout << "出现次数：" << lineCount << endl;
    for (int i = 0; i < lines.size(); i++)
        cout << "[" << i + 1 << "] " << lines[i] << endl;
    cout << "-----------------------" << endl;

    cout << "打印完毕，是否继续查询（1：是，0：否）：";
    string choice;
    getline(cin, choice);
    int choiceNum = LegalChoice(choice, 0, 1);
    if (choiceNum)
        return FileProc::LinesWithT();
    else
        return;
}

// 检测输入值是否为整数
bool IsInt(string input)
{
    if (input.size() > 2)
        return false;
        
    for (char const &i : input)
        if (!isdigit(i))
        {
            return false;
        }
    return true;
}

int LegalChoice(string choice, int low, int high)
{
    while (!IsInt(choice) || stoi(choice) < low || stoi(choice) > high)
    {
        printf("输入有误，请输入一个%d到%d之间的整数：", low, high);
        getline(cin, choice);
    }
    return stoi(choice);
}