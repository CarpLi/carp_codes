#include <iostream>

using namespace std;


template <typename T> void TempFun(T a) {
    cout << a << endl;
}

int main()
{
    TempFun(100);
    TempFun<double>(1.23456);
    TempFun('a');

    return 0;
}