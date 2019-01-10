#include <iostream>
#include <string>
#include <list>
using namespace std;

/*
  Subject：目标，知道它的观察者,提供注册和删除观察者对象的接口
  Observer：观察者,为那些在目标发生改变时需获得通知的对象定义一个更新接口
  ConcreteSubject：具体目标,存储对象状态,状态改变时,向各个观察者发出通知
  ConcreteObserver：具体观察者,维护一个指向ConcreteSubject对象的引用,存储有关状态,实现更新接口update,使自身状态与目标的状态保持一致
*/

/*
  抽象主题（Subject）角色：
    主题角色把所有对观察考对象的引用保存在一个聚集里,每个主题都可以有任何数量的观察者。
    抽象主题提供一个接口,可以增加和删除观察者对象,主题角色又叫做抽象被观察者（Observable）角色,一般用一个抽象类或者一个接口实现。
  抽象观察者（Observer）角色：
    为所有的具体观察者定义一个接口,在得到主题的通知时更新自己,这个接口叫做更新接口。
    抽象观察者角色一般用一个抽象类或者一个接口实现。
    在这个示意性的实现中，更新接口只包含一个方法（即Update()方法）,这个方法叫做更新方法。
  具体主题（ConcreteSubject）角色：
    将有关状态存入具体现察者对象,在具体主题的内部状态改变时,给所有登记过的观察者发出通知。
    具体主题角色又叫做具体被观察者角色（Concrete Observable）,具体主题角色通常用一个具体子类实现。
  具体观察者（ConcreteObserver）角色：
    存储与主题的状态自恰的状态。具体现察者角色实现抽象观察者角色所要求的更新接口,以便使本身的状态与主题的状态相协调。
    如果需要,具体现察者角色可以保存一个指向具体主题对象的引用。
    具体观察者角色通常用一个具体子类实现。
*/
#ifndef NBB_ULONG 
#define NBB_ULONG unsigned long
#endif // !NBB_ULONG 

class MplsObserver;

class MplsSubject {
public:
  MplsSubject() = default;
  virtual ~MplsSubject() {}; // TODO
  virtual void registerObserver(MplsObserver* observer) = 0;
  virtual void removeObserver(MplsObserver* observer) = 0;
  virtual void notifyObserver(const string &message) = 0;
};

class MplsObserver {
public:
  MplsObserver() = default;
  virtual ~MplsObserver() {};
  virtual NBB_ULONG  getEvent() = 0;
protected:
  MplsObserver() {}; // TODO
};


// 
int main()
{
  cout << "the observer pattern " << endl;

}

