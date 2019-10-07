#include "test.h"
extern template void func<int>(const int &t);

void test2() {
    func(222);
}