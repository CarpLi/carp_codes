
#include "test.h"
template void func<int>(const int &t);

void test1() {
    func(111);
}