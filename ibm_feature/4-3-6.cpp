#include <iostream>
using namespace std;


template <typename T, typename U>
void Sum(T& t, U& u, decltype(t+u) &s) {
    s = t + u;
}

void Sum(int a[], int b[], int c[]) {
    cout << "sum array." << endl;
}

int main()
{
    int a[5], b[5], c[5];
    Sum(a, b, c);

    int d = 1;
    int e = 3;
    int f;
    Sum(d, e, f);
    cout << "Sum template: f = " << f << endl;
}