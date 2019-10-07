#include <iostream>

using namespace std;

template <typename T, typename U = double>
void f(const T& t = 0, const U& u = 0) {
    cout << t << "\t" << u << endl;
}

void g(){
    f(111);
    f(222, 'c');
    f<int>();
    f<int, char>();
}

int main() {
    g();
    return 0;
}