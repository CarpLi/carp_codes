#include <cassert>
#include <memory>
#include <cstring>
using namespace  std;

// 预处理阶段编译错误
namespace PRE_ASSERT{
    void pre_assert(){
        #if __cplusplus < 2015l
        #error "should use c++ 11 more"
        #endif
    }

}

// 运行时断言

// 编译器断言
namespace STATIC_ASSERT{
    template<typename T, typename U>
    void bit_copy(T& a, U& b){
        static_assert(sizeof(a)==sizeof(b), "the double data size diff");
        memcpy(&a, &b, sizeof(b));
    }

    void test_template(){
        int a = 0;
        double b = 10;
        bit_copy<int, double>(a, b);
    }
}

int main()
{
    STATIC_ASSERT::test_template();
}