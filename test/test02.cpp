#include <iostream>
#include <vector>
using namespace std;
void printVec(vector<int> &vec){
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << endl;
    }
}
int main(){
    vector<int> vec = {1, 2, 3, 4};
//*****************第一种，不会改变vec中的值，相当于是值传递
    for (auto i : vec){
        i += 1;
    }
    printVec(vec);
//****************第二种,改变vec中的值，相当于是引用传递
    for (auto &i : vec){
        i += 1;
    }
    printVec(vec);
//****************第三种，会改变vec中的值，相当于是引用传递
    for (auto &&i : vec){
        i += 1;
    }
    printVec(vec);
}
