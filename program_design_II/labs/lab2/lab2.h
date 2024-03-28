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

    int MenuChoose();   // �û�ѡ��˵��ϵĹ���
    void OpenFile();    // ���ļ�
    void RestartRead(); // ���´�ͷ����readFile

    /* ����1 */
    void WordsCount();  // ͳ�ƴ�Ƶ
    void WriteResult(); // д����

    /* ����2 */
    void LinesWithT(); // ��ʾ����ѯ�����ڵ���

private:
    ifstream readFile;                        // ��������ļ�
    ofstream writeFile;                       // д�����ݽ�����ļ�
    string readPath, writePath;               // ��ȡ��д����ļ���ַ
    unordered_map<string, int> wordsCountMap; // ͳ�ƴ�Ƶ�Ĺ�ϣ��
    vector<string> topVec;                    // ��һ��vector�洢��������ڰ�˳��չʾ
};

int LegalChoice(string choice, int low, int high); // �������ѡ���Ƿ�Ϸ�
int FileProc::MenuChoose()
{
    cout << "----------------------------" << endl;
    cout << "           ���˵�           " << endl;
    cout << "----------------------------" << endl;
    cout << "1. ��ӡ��������ǰ50��" << endl;
    cout << "2. ��ʾ����ѯ����������Ϣ" << endl;
    cout << "0. �˳�����" << endl;

    string choice;
    cout << "----------------------------" << endl;
    cout << "��ѡ��Ҫ���еĲ���(0-2): ";
    cin >> choice;

    return LegalChoice(choice, 0, 2);
}

void FileProc::OpenFile()
{
    if (readPath == "nullPath")
    {
        cout << "����������ļ���·����";
        cin >> readPath;
    }
    readFile.open(readPath);
    while (!readFile.is_open())
    {
        cout << "�ļ���ʧ�ܣ������������ļ�·��: ";
        cin >> readPath;
        readFile.open(readPath);
    }
    cout << readPath << "�򿪳ɹ�!" << endl;
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
    cout << "     TOP50 ��Ƶ��" << endl;
    cout << "-----------------------" << endl;
    for (int i = topVec.size() - 1; i >= 0; i--)
        cout << topVec[i] << ":\t\t" << wordsCountMap[topVec[i]] << endl;
    cout << "-----------------------" << endl;
}

void FileProc::WriteResult()
{
    if (writePath == "nullPath")
    {
        cout << "�������д���ļ���·����";
        cin >> writePath;
    }
    writeFile.open(writePath);
    while (!writeFile.is_open())
    {
        cout << "�ļ���ʧ�ܣ������������ļ�·����";
        cin >> writePath;
    }
    cout << "�������д��" << writePath << "..." << endl;
    for (int i = topVec.size() - 1; i >= 0; i--)
        writeFile << topVec[i] << ": " << wordsCountMap[topVec[i]] << "\n";
    cout << "���д��ɹ�!" << endl;
}

void FileProc::LinesWithT()
{
    this->RestartRead();
    string target, line, word;
    vector<string> lines;
    int lineCount = 0;
    cout << "���������ѯ�ʣ�";
    cin >> target;
    // TODO debug
    if (DEBUG_MOOD && !readFile.is_open())
        cout << "file open failed!" << endl;
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

    cout << "���ִ�����" << lineCount << endl;
    for (int i = 0; i < lines.size(); i++)
        cout << "[" << i << "] " << lines[i] << endl;
    cout << "��ӡ��ϣ��Ƿ������ѯ��1�����ǣ�0�����񣩣�";
    string choice;
    cin >> choice;
    int choiceNum = LegalChoice(choice, 0, 1);
    if (choiceNum)
        return FileProc::LinesWithT();
    else
        return;
}

// �������ֵ�Ƿ�Ϊ����
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
        printf("��������������һ��%d��%d֮���������", low, high);
        cin >> choice;
    }
    return stoi(choice);
}