#include <iostream>

using namespace std;

void DefaultPara(int m = 3) {

}

template <typename T = int>
class DefalutClass{

};

template <typename T = int>
void DefaultFunc(){

}

int main()
{

    return 0;
}