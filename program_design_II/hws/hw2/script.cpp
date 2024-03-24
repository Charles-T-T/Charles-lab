#include <iostream>
using namespace std;

int main()
{
    enum VarType
    {
        character,
        integer,
        floating
    };
    VarType v = character;
    char c;
    int i;
    float f;
    cin >> c >> i >> f;

    cout << "size of i: " << sizeof(i) << endl;
    cout << "size of c: " << sizeof(c) << endl;
    cout << "size of f: " << sizeof(f) << endl;

    string s = "sjsj";
    cout << "size of v: " << sizeof(v) << endl;
    return 0;
}