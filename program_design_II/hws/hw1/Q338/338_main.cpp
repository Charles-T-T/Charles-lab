#include <iostream>
#include <cmath>

using namespace std;

int getpower(int x, int y){
    if (y < 0)
        return 0;
    return pow(x, y);
}

double getpower(double x, int y){
    return pow(x, y);
}
