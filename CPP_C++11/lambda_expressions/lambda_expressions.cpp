#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
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
  struct Person
  {
    //// 错误 error C2678: 二进制“<”: 没有找到接受“const card”类型的左操作数的运算符(或没有可接受的转换)
    //bool operator <(const Person &rhs) {
    //  return this->firstname < rhs.firstname || (this->firstname == rhs.firstname && this->lastname < rhs.lastname);
    //}

    bool operator <(const Person &rhs) const {
      return this->firstname < rhs.firstname || (this->firstname == rhs.firstname && this->lastname < rhs.lastname);
    }

    Person(int first, int last) :firstname(first), lastname(last) {
    }

    friend ostream& operator<< (ostream& os, const Person& person) {
      os << person.firstname << ' ' << person.lastname << endl;
      return os;
    }

    friend istream& operator>> (istream& is, Person& person) {
      is >> person.firstname >> person.lastname;
      return is;
    }

    Person() = default;

    int firstname;
    int lastname;
  };

  struct  Student
  {
    bool operator<(const Student &rhs) const {
      return this->id < rhs.id;
    }

    friend  ostream& operator<< (ostream& os, const Student& student) {
      os << student.id << ' ' << student.age << endl;
      return os;
    }

    friend istream& operator>> (istream& is, Student& student) {
      is >> student.id >> student.age;
      return is;
    }

    Student(int _id, int _age) :id(_id), age(_id) {
    }

    Student() = default;

    int id;
    int age;
  };

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

    // 比较人类
    bool operator()(const Person &p1, const Person &p2) const {
    return (p1.firstname < p2.firstname) || (p1.firstname == p2.firstname && p1.lastname < p2.lastname);
    }

    // 比较学生
    bool operator()(const Student &s1, const Student &s2) const {
    return s1.id < s2.id;
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

    cout << "pass a lambda as hash function or ordering or sort criterion to sequence container" << endl;
    for (auto i : vec) { cout << i << ' '; }
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

    cout << "pass a lambda as hash function or ordering or sort criterion to associative or unordered container" << endl;
    // first way
    Person p1(1, 1);
    Person p2(2, 2);
    Person p3(3, 3);
    Person p4(4, 4);
    set<Person> s_default{ p4,p3,p2,p1 };
    for (auto s : s_default) {
      cout << s;
    }

    // second way: 必须要如此定义才可以
    // bool operator()(const Person &p1, const Person &p2) const
    set<Person, Compare> s_user;
    s_user.insert(p4);
    s_user.insert(p3);
    s_user.insert(p2);
    s_user.insert(p1);
    for (auto s : s_user)
    {
      cout << s;
    }
  }
}

/*
  隐式捕获
  上面的值捕获和引用捕获都需要我们在捕获列表中显示列出Lambda表达式中使用的外部变量。除此之外，我们还可以让编译器根据函数体中的代码来推断需要捕获哪些变量，这种方式称之为隐式捕获。隐式捕获有两种方式，分别是[=]和[&]。[=]表示以值捕获的方式捕获外部变量，[&]表示以引用捕获的方式捕获外部变量。
  隐式值捕获示例：

  int main()
  {
    int a = 123;
    auto f = [=] { cout << a << endl; };    // 值捕获
    f(); // 输出：123
  }
*/
int main()
{
  SIMPLE_LAMBDA::TEST();
  FUNCTION_LAMBDA();
  STL_LAMBDA::TEST();
}
