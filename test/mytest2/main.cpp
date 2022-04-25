#include <iostream>
using namespace std;
namespace A{
    int a = 1;
    namespace B{
        int a = 2;
    }
    
}
int a = 3;

int main(){
    cout << "a = " <<  a << endl;
    cout << "A::a = " <<  A::a << endl;
    cout << "A::B::a = " <<  A::B::a << endl;
    
    // using namespace A;
    // cout << "a = " <<  a << endl;
    // cout << "A::a = " <<  ::a << endl;
    
    int a = 1;
    using namespace A;
    cout << "a = " <<  a << endl;
    cout << "::a = " <<  ::a << endl;
    
}