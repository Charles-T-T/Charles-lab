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

struct FileProc
{
    ifstream readFile;                        // 待处理的文件
    ofstream writeFile;                       // 写入数据结果的文件
    string readPath, writePath;               // 读取、写入的文件地址
    unordered_map<string, int> wordsCountMap; // 统计词频的哈希表
    vector<string> topVec;                    // 用一个vector存储结果，便于按顺序展示

    void OpenFile()
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

    void WordsCount()
    {
        // 统计所有词的词频
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

    void WriteResult()
    {
        writeFile.open(writePath);
        cout << "Writing the result to " << writePath << "..." << endl;
        for (int i = topVec.size() - 1; i >= 0; i--)
            writeFile << topVec[i] << ": " << wordsCountMap[topVec[i]] << "\n";
        cout << "Result written successfully!" << endl;
    }
};

int main(int argc, char *argv[])
{
    /**
     * 生成的可执行程序接受 待读文件地址 和 待写文件地址 两个参数
     * files/flickr-tags.txt files/result.txt
    */
    FileProc FP;
    FP.readPath = argv[1], FP.writePath = argv[2];
    FP.OpenFile();
    FP.WordsCount();
    FP.WriteResult();

    return 0;
}

