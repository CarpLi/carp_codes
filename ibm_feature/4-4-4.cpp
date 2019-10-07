#include <iostream>

using namespace std;

double foo(int a) {
    return (double)a + 0.1;
}

int foo(double b) {
    return (int)b;
}

template <class T>
auto Forward(T t) -> decltype(foo(t)) {
    return foo(t);
}

int main() {
    cout << Forward(3) << endl;
    cout << Forward(1.3) << endl;

}