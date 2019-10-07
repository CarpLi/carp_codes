#include <vector>
#include <iostream>

using namespace std;


int main() {

    vector<int> vec{1,2,3,4,5};

    using vectype = decltype(vec.begin());

    for (vectype i = vec.begin(); i != vec.end(); i++) {
        cout << *i << "\t";
    }
    cout << endl;

    for(decltype(vec)::iterator i = vec.begin(); i != vec.end(); i++) {
        cout << *i << "\t";
    }
    cout << endl;
}