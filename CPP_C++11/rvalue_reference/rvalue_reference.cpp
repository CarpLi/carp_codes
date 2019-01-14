
#include <type_traits>
#include <iostream>
#include <string>
using namespace std;

/*
move语意  
  通过move方法来将左值转换为右值
  move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存拷贝
  将左值变为一个右值引用，然后应用move语义调用构造函数，避免了拷贝，提高了程序性能
  c++中所有容器都实现了move语义

perfect forwarding
  我们需要一种方法能按照参数原来的类型转发到另一个函数，这种转发叫做完美转发
  在函数模板中，完全依照模板的参数的类型（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。

forward
  为转发而生的，不管参数是T&&这种未定的引用还是明确的左值引用或者右值引用，它会按照参数本来的类型转发。
*/

namespace UNPERFECT_FORWARDING {

  void process(int& i) {
    cout << "process(int& i) " << i << endl;
  }

  void process(int&& i) {
    cout << "process(int&& i) " << i << endl;
  }

  void forward(int&& i) {
    cout << "forward(int&& i) " << i << endl;
    process(i);
  }

  void Test() {
    int a = 0;

    cout << "TEST PROCEESS ..." << endl;
    process(a);
    process(1);
    process(move(a));

    cout << "TEST FORWARD..." << endl;
    forward(2);
    forward(move(a));
  }
}

namespace PERFECT_FORWARDING {
  template<typename T>
  void print(T& t) {
    cout << "print lvaue: " << t << endl;
  }

  template<typename T>
  void print(T&& t) {
    cout << "print rvaue: " << t << endl;
  }

  template<typename T>
  void  TEST_FORWARD(T&& v) {
    print(v);     // v又变成了一个左值，因为在这里已经变成了一个具名的变量
    print(forward<T>(v));
    print(move(v));
  }

  /*
    TEST PROCEESS ...
    process(int& i) 0
    process(int&& i) 1
    process(int&& i) 0
    TEST FORWARD...
    forward(int&& i) 2
    process(int& i) 2
    forward(int&& i) 0
    process(int& i) 0
    print lvaue: 1
    print rvaue: 1
    print rvaue: 1
    print lvaue: 1
    print lvaue: 1
    print rvaue: 1
    print lvaue: 1
    print rvaue: 1
    print rvaue: 1
    print lvaue: 1
    print rvaue: 1
    print rvaue: 1
  */

  void TEST() {

    TEST_FORWARD(1);

    int x = 1;
    TEST_FORWARD(x);
    TEST_FORWARD(forward<decltype(x)>(x));
    TEST_FORWARD(move(x));
  }
}
namespace FUNCTION_WRAPPER
{

  template <class Function, class... Args>
  inline auto FunctionWrapper(Function&& f, Args&&... args)->decltype(f(forward<Args>(args)...)) {
    return f((forward<Args>(args))...);
  }

  void test0() {
    cout << "test0(): void" << endl;
  }

  int test1() {
    return 1;
  }

  int test2(int x) {
    return x;
  }

  string test3(string s1, string s2) {
    return s1 + s2;
  }

  void TEST() {
    FunctionWrapper(test0);

  }
}

int main()
{
  UNPERFECT_FORWARDING::Test();

  PERFECT_FORWARDING::TEST();

  FUNCTION_WRAPPER::TEST();
}