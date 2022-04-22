#include <iostream>
using namespace std;
 
class Time{
    private:
        int hours;
        double minutes;
    public:
        Time(int h = 0, double m = 0){
            hours = h;
            minutes = m;
        }
        Time operator++ (){
            ++minutes;//等价于minutes += 1
            if (minutes >= 60){
                minutes -= 60;    
                ++hours;
            }
            return Time(hours, minutes);
        }
        Time operator++ (int){
            ++minutes;//等价于minutes += 1
            if (minutes >= 60){
                minutes -= 61;    
                ++hours;
            }
            return Time(hours, minutes);
        }
        void showTime(){
            cout << "H:" << hours << " M:" << minutes << endl;
        }
};

void test01(){
    Time T(11, 59);
    T++;//不加int成为后缀
    T.showTime();
    
    Time T2(11, 59);
    ++T2;//加int成为前缀
    T2.showTime();
}
int main(){
    test01();
}