#include <iostream>
using namespace std;
class testoverride
{
public:
    testoverride(void);
    ~testoverride(void);
    virtual void show() const = 0;
    virtual int infor() = 0;
    virtual void test() = 0;
    virtual int spell() = 0;
};

class B: public testoverride
{
public:
   virtual void show();     //1
   virtual void infor();    //2
   virtual void vmendd();   //3
   virtual void test(int x);//4
   virtual void splle();    //5 
};

class C: public testoverride
{
public:
    virtual void show() override;
    virtual void infor() override;   
    virtual void vmendd() override;
    virtual void test(int x) override;
    virtual void splle() override;
};