class Data
{
private:
    int num;//普通成员变量
    static int data;//静态成员变量(类内声明)
public:
    //普通成员函数 依赖于 对象的 必须对象调用
    int getData(void)
    {
        return data;
    }
};

//定义的时候 不需要加static
int Data::data=100;//类外定义+初始化

void test01()
{
    //cout<<Data::data<<endl;//err 静态data是私有的 类外不能直接访问
    //cout<< Data::getData()<<endl;//err getData() 必须对象调用

    Data ob;
    cout<<ob.getData()<<endl;
    //存在问题：data静态的 在创建对象之前 就已经存在
    //如果类没有实例化对象 难道 就不能使用data了吗？ 
    //解决上述问题 就要用到静态成员函数
}
