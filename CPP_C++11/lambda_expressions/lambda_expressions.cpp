#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
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
  lambda表达式类型是一个匿名函数对象
*/

// 简单应用
namespace SIMPLE_LAMBDA
{
  auto I = [] {
      cout << "hello world!" << endl;
  };

  int id = 0;
  auto F = [] {
    cout << "F()::id\t" << id << endl;
    ++id;
  };

  auto FF = []() mutable {
    cout << "FF()::id\t" << id << endl;
    ++id;
  };

  void TEST(){
    I();
    F();
    F();
    FF();
    FF();
    cout << "SIMPLE_LAMBDA::id\t" << id << endl;
  }
}

// 函数中应用
void FUNCTION_LAMBDA()
{
  int id = 0;
  // 有可选项时()必须要添加,否则存在编译错误
  // 对象以传值方式传入，但是在lambda定义的函数对象中通过mutable可以访问传入值
  auto f = [id] () mutable {
    cout << "FUNCTION_LAMBDA value :: id\t" << id << endl;
    ++id;
  };
  id = 42;

  auto ff = [&id] {
    cout << "FUNCTION_LAMBDA reference :: id\t" << id << endl;
    ++id;
  };

  f();
  f();
  f();
  cout << "out value id \t" << id << endl;
  ff();
  ff();
  ff();
  cout << "out reference id \t" << id << endl;
}

// 标准库应用
namespace STL_LAMBDA 
{
  class Compare {
  public:
    Compare() = default;
    Compare(int pre, int post) : _m(pre), _n(post){
    }

    // 大小比较
    bool operator()(int a, int b) {
      return a < b;
    }

    // 范围比较
    bool operator()(int a) {
      return (a > _m) && (a < _n);
    }

  private:
    int _m;
    int _n;
  };

  bool compare(int a, int b) {
    return a < b;
  }

  void TEST()
  {
    vector<int> vec{ 3, 2, 5, 7, 3, 2 };
    vector<int> ivec(vec);
    vector<int> iivec(vec);
    vector<int> iiivec(vec);
    vector<int> vvec(vec);

    for (auto  i : vec) { cout << i << ' '; }
    cout << endl;

    // first way
    sort(vec.begin(), vec.end(), compare);
    for (auto i : vec) { cout << i << ' '; }
    cout << endl;

    // second way
    sort(ivec.begin(), ivec.end(), Compare());
    for (auto i : ivec) { cout << i << ' '; }
    cout << endl;

    // third way
    sort(iivec.begin(), iivec.end(), [](int a, int b)->bool {return a < b; });
    for (auto i : iivec) { cout << i << ' '; }
    cout << endl;

    // erase some value
    // 序列式容器删除指定范围的数值
    // string 删除指定数值的字符
    int x = 4;
    int y = 6;
    iiivec.erase(remove_if(iiivec.begin(), iiivec.end(), [x, y](int a) {return (a > x) && (a < y); }),
                 iiivec.end());
    for (auto i : iiivec) { cout << i << ' '; }
    cout << endl;

    iiivec.erase(remove_if(iiivec.begin(), iiivec.end(), Compare(2, 5)), iiivec.end());
    for (auto i : iiivec) { cout << i << ' '; }
    cout << endl;

  }
}

int main()
{
  SIMPLE_LAMBDA::TEST();
  FUNCTION_LAMBDA();
  STL_LAMBDA::TEST();
}
