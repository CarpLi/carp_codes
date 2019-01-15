// alais_template.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include "pch.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

// using的三种用途
// case 1. 直接使用命名空间和命名空间成员的使用声明
// case 2. 类成员声明
// case 3. 类型别名声明和模板别名声明

// case 3 模板别名处理:可以用来隐藏模板的默认参数
template <typename T> using Vec = vector<T, allocator<T>>;

const unsigned long SIZE = 100;

// 问题本质在于如何传入模板参数
// 模板模板
// AIM
template<typename T, template <typename> class Vec>
void test_template(T t, Vec<T> c) {
  for (int i = 0; i < SIZE; i++) {
    c.insert(c.end(), i);
  }

  for (auto i : c) {
    cout << i << '\t';
  }
}

int main()
{
  std::cout << "Hello World!\n";   // case 1

  using INT = int;                 // case 3
  INT a = 100; 
  std::cout << a << std::endl; 

  using VEC = vector<INT, allocator<INT>>;  // case 3

  int test = 10;
  Vec<int> testVec;

  test_template<int, Vec>(test, testVec);
}

