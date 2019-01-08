#include <string>
#include <iostream>
using namespace std;

// LAMBDA FUNCTION
/*
  声明式编程风格：就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或者函数对象
  简洁：不需要额外再写一个函数或者函数对象，避免了代码膨胀和功能分散，让开发者更加集中精力在手边的问题
  在需要的时间和地点实现功能闭包，使程序更灵活

  [...]   (...)   mutable(可选)   throwSpec(可选) ->  retType(可选) {...}

  [...]   lambda引入器 在lambda内访问外部非静态对象
          诸如std::cout的静态对象可被使用
          可以指定一个caputure去访问一个外部区域数据，但不传入一个参数
  [=]     意味着外部范围以传值的方式传入lambda
  [&]     意味着外部范围以传引用的方式传入lambda
  [=,&y]  意味着y以传引用的方式，其他以传引用的方式 
  
  mutable 以传值的方式传入对象，但在lambda定义的函数对象内部，拥有对值传入对象的写权限
  retType 没有指定任意返回类型的定义，它将从返回值进行推断
*/

/*
  lambda是能在函数和表达式内部定义的函数式定义
  lambda可被当做inline函数使用
  最小lambda函数没有参数并简单的做一些事情
*/

namespace SIMPLE_LAMBDA
{
  auto I = [] {
      cout << "hello world!" << endl;
  };

  void TEST(){
    I();
  }
}

int main()
{
  SIMPLE_LAMBDA::TEST();
}
