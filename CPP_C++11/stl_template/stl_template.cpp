// stl_template.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <vector>
#include <list>
#include <unordered_set>
#include <iostream>
using namespace std;

/******** 偏特化综述 ********/ 
// 模板的特例化是模板中精髓的东西
// 有函数模板特例化，类模板特例化
// 特例化分为全特化与偏特化
// 主要用于对于特定的类型指定特定的处理方式
// 就相当于普通编程中的if-else这样的方式
// 编译阶段确定如果是某个特化类型，就用特化的模板
// 如果都不是，就用最一般的模板

/******** 注意点 ********/
// 特例化本质上是我们顶替了编译器的工作，我们帮编译器做了类型推导
// 全特化本质上是一个实例，而偏特化本质上还是一个模板，只是原来模板的一个子集
// 所以全特化的函数模板，本质上是实例，从而不会与函数模板产生二义性
// 若想让用户能使用特例化版本，特例化版本必须与模板定义在同一个.h头文件中

/**** 偏特化在STL中最重要的两个应用 ****/
// 应用在迭代器设计中，为了使迭代器既可以萃取出值类型，又可以包容原生指针
// 迭代器萃取技术的两个核心是：
//  １）在每个迭代器类中定义value_type值类型的类型成员，这样直接通过迭代器的value_type类型成员就可以知道值类型。
//  ２）问题就在于，迭代器必须兼容原生指针，而原生指针很难被重新定义，即要在原生指针的类中添加value_type的值类型的类型成员。
//      这时候靠的就是类模板的偏特化了。新添加一层iterator_traits类，专门萃取迭代器的属性，然后再对iterator_traits类设计原生指针与原生引用的偏特化版本，就解决了这个棘手的问题。
// type_traits类型萃取，对待特殊类型，特殊处理，提高效率
//      对于没有构造函数，析构函数等的内置类型，如果与复杂类型一样，执行同样的操作，显然是效率不高的
//      先实现一个对所有类型都设置一个最保守值的type_traits模板类，然后再对每个内置类型设置偏特化版本，内置类型设置一个更为激进的值，表明可以采取更为高效的操作来提高效率+

/* 函数模板 */
template <typename T>
T add(const T val1, const T val2)
{
  return val1 + val2;
}

// 函数模板全特化
// __STL_TEMPLATE_NULL(class template explict specialization)
template <>
double add(double val1, double val2)
{
  return val1 * val2;
}

// 函数模板偏特化或者函数模板重载
template<typename T>
T add(T *val1, T *val2)
{
  return *val1 + *val2;
}

/* 类模板 */
template <typename T>
class A
{
public:
  explicit A(T val) : t(val) {}

  T add(T x) { return x + t; }

private:
  T t;
};

// 类模板全特化和函数模板全特化一样，全特化是一个实例，当编译器匹配时会优先匹配参数一致的实例
template <>
class A<char>
{
public:
  //explicit A(){}

  void add() { cout << "__STL_TEMPLATE_NULL char " << endl; }

private:
  char t;
};

/* 类模板偏特化 */
// 类模板偏特化本质上都是指定部分类型，让偏特化版本成为普通版本的子集
// 若实例化参数类型为指定的类型，则优先调用特例化版本

// Case1：多参数类模板,特化部分参数
template <typename T, typename TT>
class CASEA
{
public:
  void out() { cout << "CASEA: normal template" << endl; }
};

template<typename TT>
class CASEA<int, TT>
{
public:
  void out() { cout << "CASEA: partial specialization" << endl; }
};

// Case2：单参数模板,特化为不同参数类型
template <typename T>
class CASEB
{
public:
  void out() { cout << "CASEB: normal template" << endl; }
};

template <typename T>
class CASEB<T*>
{
public:
  void out() { cout << "CASEB: T* partial template" << endl; }
};

template <typename T>
class CASEB<T&>
{
public:
  void out() { cout << "CASEB: T& partial template" << endl; }
};

template <typename T>
class CASEB<const T*>
{
public:
  void out() { cout << "CASEB: cosnt T* partial template" << endl; }
};

// Case3：

// in-class static constant integer initialization
template <typename T>
class testClass
{
public:
  static const int _datai = 5;
  static const long _datal = 3l;
  static const char _datac = 'c';
};

int main()
{
  int a = 1;
  int b = 3;
  double c = 1.1;
  double d = 2.2;

  cout << add(a, b) << endl;
  cout << add(c, d) << endl;
  cout << add(&c, &d) << endl;

  A<int> obj(10);
  cout << obj.add(5) << endl;

  A<char> obj_null;
  obj_null.add();;

  /* 多参数类模板,特化部分参数 */
  CASEA<char, int> obj_casea;
  obj_casea.out();

  CASEA<int, int> obj_casea_partial;
  obj_casea_partial.out();

  /* 单参数类模板,特化不同参数类型 */
  CASEB<int> obj_caseb;
  obj_caseb.out();

  CASEB<int*> obj_caseb_point;
  obj_caseb_point.out();

  CASEB<int&> obj_caseb_reference;
  obj_caseb_reference.out();

  CASEB<const int*> obj_caseb_const;
  obj_caseb_const.out();

  cout << testClass<int>::_datai << endl;
  cout << testClass<int>::_datal << endl;
  cout << testClass<int>::_datac << endl;


  cout << __cplusplus << endl;


  return 0;
}
