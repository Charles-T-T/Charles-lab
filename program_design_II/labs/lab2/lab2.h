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

    int MenuChoose(); // �û�ѡ��˵��ϵĹ���
    void OpenFile(); // ���ļ�
    void WordsCount(); // ͳ�ƴ�Ƶ
    void WriteResult(); // д����

private:
    ifstream readFile;                        // ��������ļ�
    ofstream writeFile;                       // д�����ݽ�����ļ�
    string readPath, writePath;               // ��ȡ��д����ļ���ַ
    unordered_map<string, int> wordsCountMap; // ͳ�ƴ�Ƶ�Ĺ�ϣ��
    vector<string> topVec;                    // ��һ��vector�洢��������ڰ�˳��չʾ
};

int FileProc::MenuChoose(){
    cout << "----------------------------" << endl;
    cout << "           ���˵�           " << endl;
    cout << "----------------------------" << endl;
    cout << "1. ͳ�ƴ�Ƶ: ��������ǰ50��" << endl;
    cout << "2. ��ʾ����ѯ����������Ϣ" << endl;

    int choice;
    cout << "----------------------------" << endl;
    cout << "������Ҫ���еĲ���(1-2): ";
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

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq; // �������ȶ���ͳ�ƴ�Ƶ��ߵ��ַ���
    for (const auto &pair : wordsCountMap)
    {
        pq.push(make_pair(pair.second, pair.first));
        if (pq.size() > 50) // pop��50��������ַ���
            pq.pop();
    }

    while (!pq.empty())
    {
        topVec.push_back(pq.top().second); // ����֮�󰴴Ӵ�С˳���ӡ
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