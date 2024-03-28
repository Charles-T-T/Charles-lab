#include <iostream>
using namespace std;

//声明定期储蓄类
class TimeSavings;

//声明活期储蓄类
class CurrentSavings
{
private:
    int balance;

public:
    CurrentSavings (int balance);
    void printTotalSavings(TimeSavings &ts);
};

//声明定期储蓄类
class TimeSavings
{
private:
    int balance;

public:
    TimeSavings(int balance);

    //声明一个友元类CurrentSavings
    // ____qcodep____
    friend class CurrentSavings;
};

//CurrentSavings类的构造函数的实现
CurrentSavings::CurrentSavings(int balance)
{
    this->balance = balance;
}

//TimeSavings类的构造函数的实现
TimeSavings::TimeSavings(int balance )
{
    this->balance = balance;
}

//显示当前客户的各类存款余额及总余额，即打印CurrentSavings类中的私有成员和TimeSavings的私有成员
void CurrentSavings::printTotalSavings(TimeSavings &ts)
{
    // ____qcodep____
    cout << this->balance << endl;
    cout << ts.balance << endl;
    cout << this->balance + ts.balance << endl;
}

int main(void)
{
    int cs, ts;
    cin >> cs >> ts;

    CurrentSavings cs1(cs);
    TimeSavings ts1(ts);

    // 打印账户余额
    cs1.printTotalSavings(ts1);
    return 0;
}
