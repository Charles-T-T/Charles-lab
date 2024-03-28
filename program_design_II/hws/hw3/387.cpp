#include <iostream>
using namespace std;

// TODO1 ____qcodep____
class TimeSavings;

//声明活期储蓄类
class CurrentSavings
{
private:
    int balance;
   

public:
    CurrentSavings (int balance){
        // TODO2 ____qcodep____
        this->balance = balance;
    }
    // TODO3 ____qcodep____
    void print(){
        cout << this->balance << endl;
    }
    friend class TimeSavings;
};

//声明定期储蓄类
class TimeSavings
{
private:
    int balance;

public:
    TimeSavings(int balance){
        // TODO4 ____qcodep____
        this->balance = balance;
    }
    // TODO5 ____qcodep____
    int getTotal(CurrentSavings &cs){
        return cs.balance + this->balance;
    }
    void print()
    {
        cout << this->balance << endl;
    }
};


void printTotalSavings(TimeSavings &ts, CurrentSavings &cs)
{
    // TODO6 ____qcodep____
    cout << ts.getTotal(cs) << endl;
}

int main(void)
{
    int cs, ts;
    cin >> cs >> ts;

    CurrentSavings cs1(cs);
    TimeSavings ts1(ts);

    cs1.print();
    ts1.print();
    printTotalSavings(ts1, cs1);

    return 0;
}
