#include <iostream>

using namespace std;

int main(){
    unsigned int n;
    cin >> n;
    unsigned int high = 0xffff0000 & n, low = 0xffff & n; // ��ȡ�ߵ�λ
    cout << (high >> 16) + (low << 16) << endl;

    return 0;
}