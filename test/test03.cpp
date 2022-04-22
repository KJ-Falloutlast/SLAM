#include <iostream>
using namespace std;
class Distance{
    private:
        double feet, inch;
    public:
        Distance(double f = 0, double i = 0){
            feet = f;
            inch = i;
        }
        void showDistance(){
            cout << "F =" << feet << "  I = " << inch << endl;
        }
        
        Distance operator- (){
            feet = -feet;
            inch = -inch;
            return Distance(feet, inch);
        }
    
};
void test(){
    Distance d(1, 3);
    -d;
    d.showDistance();
}
int main(){
    test();
}