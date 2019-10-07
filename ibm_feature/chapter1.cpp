#include <random>
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

// bind
// bind嵌套

// bind的目的是什么,生成一个转发器，将f包装为另外一个东西
void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}

int g(int n1) {
    return n1 > 100 ? 1 : 0;
}

class Foo{
public:
    void print_sum(int n1, int n2){
        cout << n1+n2 << endl;
    }
    int data = 10;
};

int main()
{
    using namespace std::placeholders;
    int n = 77;
    auto f1 = bind(f, _2, 44, _1, cref(n), n);
    f1(55,33,66);

    auto f2 = bind(f, _3, bind(g, 1001), 44, 55,66);
    f2(100,200,33);

    Foo foo;
    auto f3 = bind(&Foo::print_sum, &foo, _1, 100);
    f3(1);

    auto f4 = bind(&Foo::data, _1);
    cout << f4(foo) << endl;
}