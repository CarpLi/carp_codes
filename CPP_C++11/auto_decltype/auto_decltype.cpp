
#include <iostream>

#define BEGIN_AUTO_PRE_MACRO_NAMESPACE \
        namespace auto_pre_macro{      \

#define END_ATUO_PRE_MACRO_NAMESPACE   \
        }                              \

BEGIN_AUTO_PRE_MACRO_NAMESPACE

void test_auto_pre_macro() {
#if __cplusplus >= 201103L
  std::cout << "new version" << "\t" << __cplusplus;
#else
  std::cout << "old version" << "\t" << __cplusplus;
#endif
}

END_ATUO_PRE_MACRO_NAMESPACE

int main() 
{
  auto_pre_macro::test_auto_pre_macro();
}