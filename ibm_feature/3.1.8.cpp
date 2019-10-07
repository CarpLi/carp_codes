#include <iostream>
using namespace std;


class A{
public:
    A(int) {
        cout << "A constructor" << endl;
    }
};

class B : public A {
public:
    using A::A;

};

int main()
{
    B b(10);
}