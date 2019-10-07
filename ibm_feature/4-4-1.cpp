#include <iostream>
#include <type_traits>

using namespace std;

template <typename T, typename U>
auto Sum(const T& t, const U& u) -> decltype(t + u) {
    return t + u;
}

template <typename T, typename U>
auto Mul(const T& t, const U& u) -> decltype(t * u) {
    return t * u;
}

int main() {
    auto a = 3;
    auto b = 4l;
    auto pi = 3.14;

    auto c = Sum(a, b);
    cout << " c typeid " << typeid(c).name() << "\t" << c << endl;
    auto d = Mul(c,pi);
    cout << " d typeid " << typeid(d).name() << "\t" << c << endl;
}