
//#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
using namespace std;

// 核爆区域
// 模板参数个数发生变化
// 模板参数类型发生变化
// 利用参数个数逐一递减的特性，实现递归函数调用，适用function template 完成
// 利用参数个数逐一递减导致参数类型也逐一递减的特性，实现递归继承或者递归组合，以class template 完成
// https://stackoverflow.com/questions/3634379/variadic-templates

// 相同类型可以使用std::initializer_list<T>, 语法略有变化.
// 不同类型使用: template<class ... Types> void f(Types ... args); 参数包结构.

// 递归函数处理流程
namespace RECURSION_FUNCTION {
	// 结束递归处理
	void print() {
		cout << "end the loop of print" << endl;
	}

	template<class T, class ...Args>     // 模板参数包
	void print(T head, Args... rest) {   // 函数参数类型包
		cout << "parameters: " << head << "\t" << "rest: " << sizeof...(rest) << endl;
		print(rest...);                  // 函数参数包
	}
	
	void TEST() {
		cout << "------ RECURSION_FUNCTION TEST ------" << endl;
		print(1, "hello", 10.2, 3, "world");
	}
}

// variadic template max function
namespace RECURSION_MAXIMUM {
	inline int maximum(int argc) {
		return argc;
	}

	template<typename... Args>
	int maximum(int first, Args... args) {
		return std::max(first, maximum(args...));
	}

	void TEST() {
		cout << "------ RECURSION_MAXIMUM TEST ------" << endl;
		cout << "the recursion maxmum value is " << maximum(11, 12, 32, 24, 45, 36, 67, 48, 79, 10) << endl;
	}
}

namespace INITIALIZER_MAXIMUM {
	struct  _Iter_less_iter
	{
		template<typename _Iterator1, typename _Iterator2>
		bool operator()(_Iterator1 _iter1, _Iterator2 _iter2) const {
			return *_iter1 < *_iter2;
		}
	};

	inline _Iter_less_iter _iter_less_iter() {
		return _Iter_less_iter();
	}

	template<typename _ForwardIterator, typename _Compare>
	_ForwardIterator _max_element(_ForwardIterator _first, _ForwardIterator _last, _Compare _comp) {
		if (_first == _last) {
			return _first;
		}

		_ForwardIterator _result = _first;
		while (++_first != _last){
			if (_comp(_result, _first)) {
				_result = _first;
			}
		}

		return _result;
	}

	template<typename _ForwardIterator>
	inline _ForwardIterator max_element(_ForwardIterator _first, _ForwardIterator _last) {
		return _max_element(_first, _last, _iter_less_iter());
	}

	template <typename _Tp>
	inline _Tp max(initializer_list<_Tp> _I) {
		return *max_element(_I.begin(), _I.end());
	}

	void TEST(){
		cout << "------ INITIALIZER_MAXIMUM TEST ------" << endl;
		cout << "intializer_list： max value " << max({1,2,3,4,7,6,5}) << endl;
	}
}

// variadic template adder function
namespace RECURSION_ADDER {
	template <typename T>
	T adder(T v) {
		return v;
	}

	template <typename T, typename... Args>
	T adder(T first, Args... args) {
		T result = first + adder(args...);
		cout << __FUNCTION__ << "\t " << "adder value = " << result << "\t" << "sizeof...(Args) is " << sizeof...(Args) << endl;
		return result;
	}

	void TEST() {
		cout << "------ RECURSION_ADDER TEST ------" << endl;
		adder(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	}
}

// variadic template printf function
namespace RECURSION_PRINTF {
	void printf(const char *s) {
		while (*s){
			if (*s == '%' && *(++s) != '%')
				throw "invalid format string: missing arguments";
			std::cout << *s++;
		}
	}

	template<typename T, typename... Args>
	void printf(const char* s, T value, Args... args) {
		while (*s){
			if (*s == '%' && *(++s) != '%'){
				std::cout << value;
				printf(++s, args...); // call even when *s == 0 to detect extra arguments
				return;
			}
			std::cout << *s++;
		}
		throw "extra arguments provided to printf";
	}

	void TEST() {
		cout << "------ RECURSION_PRINTF TEST ------" << endl;
		cout << "recursion printf with variadic template ";
		printf("%s %s %s %d %d", "welcome", "come", "china", 100, 1000);
		cout << endl;
	}
}

// variadic template recursive inheritance
namespace RECURSION_INHERITANCE {
	template<typename... Values> class tuple;
	template<>  class tuple<> {};
	template <typename Head, typename... Tail>
	class tuple<Head, Tail...> : private tuple<Tail...>
	{
	public:
		typedef tuple<Tail...> inherited;
	protected:
		Head m_head;
	public:
		tuple() {}
		tuple(Head v, Tail... vtail) : m_head(v), inherited(vtail...) {
			cout << "the element is " << v << endl;
		}
		Head head() { return m_head; }
		inherited& tail() {	return *this; }
	};
	
	void TEST() {
		cout << "------ RECURSION_INHERITANCE TEST ------" << endl;
		tuple<int ,float, string> t(41, 6.3, "nico");
	}
}

// variadic template recursive composition
namespace RECURSION_COMPOSITION {
	template <typename... Values> class tup;
	template <> class tup<> {};
	template <typename Head, typename... Tail>
	class tup<Head, Tail...> {
		typedef tup<Tail...> composited;
	public:
		composited m_tail;
		Head m_head;
	public:
		tup() {}
		tup(Head v, Tail... vtail) : m_head(v), m_tail(vtail...){}

		Head head() { return m_head; }
		composited &tail() { return m_tail; }
	};

	void TEST() {
		tup<int, float, string> it1(41, 6.3, string("nico"));
		cout << sizeof(it1) << "\t" << it1.head() << "\t" << it1.tail().head() << "\t" << it1.tail().tail().head() << endl;
	}
}

int main()
{
  std::cout << "variadic template!\n";
  RECURSION_FUNCTION::TEST();
  RECURSION_MAXIMUM::TEST();
  RECURSION_ADDER::TEST();
  RECURSION_PRINTF::TEST();
  INITIALIZER_MAXIMUM::TEST();
  RECURSION_INHERITANCE::TEST();
  RECURSION_COMPOSITION::TEST();
}