#include <iostream>

using namespace std;

class HasPtrMember {
public:
    HasPtrMember():ptr(new int(111)){
        cout << "default constructor: " << endl;
    }
    HasPtrMember(const HasPtrMember& rhs) : ptr(new int(*rhs.ptr)){
        cout << "copy constructor: " << ptr << "\t" << *ptr << endl;
    }

    int* ptr;
};

int main()
{
    HasPtrMember origPtr;
    HasPtrMember dstPtr(origPtr);

}