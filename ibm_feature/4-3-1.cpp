#include <iostream>
#include <typeinfo>

using namespace std;

class White{};
class Black{};

int main()
{
    White w;
    Black b;

    cout << typeid(w).name() << endl;
    cout << typeid(b).name() << endl;

}