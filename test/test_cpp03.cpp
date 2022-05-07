#include <iostream>
using namespace std;
class Distance{
    private:
        int feet;
        int inches;
    public:
        Distance(int f, int i){
            feet = f;
            inches = i;
        }
        friend ostream& operator<<(ostream &output, Distance &D);        
        friend istream& operator>>(istream &input, Distance &D);        
};

ostream& operator<< (ostream &output, Distance &D){
    output << "feet = " << D.feet << " inches = " << D.inches << endl;
    return output;
}

istream& operator>> (istream &input, Distance &D){
    input >> D.feet >> D.inches;
    return input;
}

void test(){
    Distance D1(2, 3), D2(2, 5);
    cin >> D1 >> D2;
    cout << "the distance is  " << D1 << endl;  
    cout << "the distance is  " << D2 << endl;  
}
int main(){
    test();
}