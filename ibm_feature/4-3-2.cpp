#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    int ii;
    decltype(ii) jj = 0;

    cout << typeid(ii).name() << endl;
    cout << typeid(jj).name() << endl;

    float a;
    double b;

    decltype(a+b) c;
    cout << typeid(c).name() << endl;
}