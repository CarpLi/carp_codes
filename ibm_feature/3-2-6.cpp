#include <list>
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

class TDConstructed{
public:
    template <typename T>
    TDConstructed(T first, T end) : l(first, end){} 
    list<int> l;

public:
    TDConstructed(vector<int> &v) : TDConstructed(v.begin(), v.end()) {
        cout << "vector::constructot. \t" << endl;
    }

     TDConstructed(deque<int> &v) : TDConstructed(v.begin(), v.end()) {
        cout << "deque::constructot. \t" << endl;
    }   
};

int main() {
    vector<int> ivec{1,2,3,4,5};
    deque<int> ideq{6,7,8,9,0};
    TDConstructed tdVec(ivec);
    TDConstructed tdDeq(ideq);

    for (auto a : tdVec.l) {
        cout << a << '\t';
    }
    cout << endl;

    for (auto d : tdDeq.l) {
        cout << d << '\t';
    }
    cout << endl;

    return 0;
}