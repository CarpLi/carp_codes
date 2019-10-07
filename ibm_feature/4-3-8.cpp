#include <type_traits>
#include <iostream>

using namespace std;

typedef double (*func)();

int main() {
    result_of<func()>::type f;

    cout << typeid(f).name() << endl;

}