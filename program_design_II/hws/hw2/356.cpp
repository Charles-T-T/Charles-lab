#include <iostream>
using namespace std;

class Datatype {
public:
    void print();
    // ____qcodep____
    Datatype(char c) : _c(c), _vartype(character) {}
    Datatype(int i) : _i(i), _vartype(integer) {}
    Datatype(float f) : _f(f), _vartype(floating) {}

private:
    enum VarType
    {
        character,
        integer,
        floating
    };

    VarType _vartype;
    union
    {
        char _c;
        int _i;
        float _f;
    };
    
};

void Datatype::print() {
    switch (_vartype) {
    case character:
        cout << "char: " << _c << endl;
        break;
    case integer:
        cout << "int: " << _i << endl;
        break;
    case floating:
        cout << "float: " << _f << endl;
        break;
    }
}

int main() {
    char c;
    int i;
    float f;
    cin >> c >> i >> f;
    Datatype ii(i), cc(c), ff(f);
    if(8 == sizeof(ii) &&
       8 == sizeof(cc) &&
       8 == sizeof(ff) ) {
        cc.print();
        ii.print();
        ff.print();       
    }
    cout << "size of ii: " << sizeof(ii) << endl;
    cout << "size of cc: " << sizeof(cc) << endl;
    cout << "size of ff: " << sizeof(ff) << endl;

    string s = "sjsj";
    cout << "size of string: " << sizeof(s) << endl;
    return 0;
}